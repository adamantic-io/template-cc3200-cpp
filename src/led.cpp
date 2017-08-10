/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                     `..--::::::--.``                                    *
 *                 `-:/++:--.`      ``....``                               *
 *               .://+:.        ``..``    .-.`                             *
 *             `://+/`      .-//-.       .yss                              *
 *            `://+:      .://`         `so`y+                             *
 *            -///+      -//+           +y. :y:                            *
 *           `:////     `://:          :y:   +y.                           *
 *            :///+     `////         .yo    `ss                           *
 *            -///+.     -//+.        sy+/////oy+                          *
 *            `////+`     -//+-      +y-......./y:                         *
 *             `/////`     .///:`   -y/         +y.                        *
 *              `/////-      -///:.`++          `+/                        *
 *                -////:.      .:///-.`                     `              *
 *                 `:////:.       `-:/+/-..``     `..`     .               *
 *                   .://///-`         .--:::::---.       .-               *
 *                     `-/////:-.                       `::                *
 *                        `-/+////:-.``              `.:/.                 *
 *                            .-:/+/////::--------::+/:.                   *
 *                                 .--::////////::-.`                      *
 *                            ADAMANTIC SOLUTIONS                          *
 *                      Copyright (C) 2017 ADAMANTIC srl                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Project : TI-CC3200 C++ Template                                        *
 * Author  : Domenico Barra <dom@adamantic.io>                             *
 * This    : LED Support - implementation                                  *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defs.h"
#include "led.h"
#include "FreeRTOS.h"
#include "timers.h"

#include <map>


using std::map;

namespace adm {
namespace util {

namespace {
    volatile bool led_blinker_timer_started = false;
    map<int, LedBlinker*> blinkers;
    TimerHandle_t fastblink_timer;

    inline void led_set(int led, bool on) {
        if (on) switch_led_on(led);
        else switch_led_off(led);
    }
}

extern "C" void led_blinker_callback(TimerHandle_t timer)
{
    for (auto it = blinkers.begin(); it != blinkers.end(); ++it) {
        it->second->fast_tick();
    }
}

LedBlinker& LedBlinker::for_led(int led) {
    taskENTER_CRITICAL();
    auto it = blinkers.find(led);
    if (it != blinkers.end()) {
        taskEXIT_CRITICAL();
        return *(it->second);
    } else {
        LedBlinker* new_blinker = new LedBlinker(led); // registers itself to global map 
        taskEXIT_CRITICAL();
        MYLOG("Registered new blinker for LED (%d)", led);
        return *new_blinker;
    }
}

LedBlinker::LedBlinker(int led) : led_(led), light_(false), status_(OFF), tick_count_(0) {
    taskENTER_CRITICAL();
    if (!led_blinker_timer_started) {

        fastblink_timer = xTimerCreate ("LED-Fastblink",           // name
                                        pdMS_TO_TICKS(Status::FAST_BLINK), // every 250 ms
                                        pdTRUE,                    // auto-reload
                                        (void *) 0,                // timer id
                                        led_blinker_callback       // callback
                                        );
        if (xTimerStart(fastblink_timer, 0) == pdPASS) {
            MYLOG("Led-Blink Timer Started!\n\r");
        } else {
            MYLOG("Could not start Led-Blink Timer!\n\r");
        }
        led_blinker_timer_started = true;

    }

    blinkers[led] = this;
    taskEXIT_CRITICAL();

    initialize_led((char) led_);
    switch_led_off(led_);

}

void LedBlinker::fast_tick() {
    ++tick_count_;
    bool invert = false;
    switch (status_) {
    case OFF:
        if (light_) invert = true;
        break;
    case ON:
        if (!light_) invert = true;
        break;
    case SLOW_BLINK:
        if (tick_count_ % SLOW_TO_FAST_MULT != 0) break;
    case FAST_BLINK:
        invert = true;
        break;
    }
    if (invert) {
        led_set(led_, (light_ = !light_));
    }
}


}
}