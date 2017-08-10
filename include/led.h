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
 * This    : LED Support - header file                                     *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ADM_UTIL_LED_H
#define ADM_UTIL_LED_H

#include "defs.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

namespace adm {
namespace util {

/*
 * Platform-independent interface
 * This is common to all implementations
 */

extern "C" void led_blinker_callback(TimerHandle_t);

class LedBlinker {
public:
    enum Status : unsigned {
        OFF,
        ON,
        FAST_BLINK =  250, // blink every quarter of a second
        SLOW_BLINK = 1000  // blink once a second
    };

    void   set(Status s) { status_ = s; }
    Status get() { return status_; }

    static LedBlinker& for_led(int led);

private:
    int             led_;
    volatile bool   light_;
    volatile Status status_;
    unsigned        tick_count_;

    static const unsigned SLOW_TO_FAST_MULT = SLOW_BLINK / FAST_BLINK;
    
    LedBlinker(int led);
    void fast_tick();

    LedBlinker(const LedBlinker&) = delete;
    LedBlinker& operator=(const LedBlinker&) = delete;

    friend void led_blinker_callback(TimerHandle_t);
};

/*
 * Platform-dependent interface
 * Every implementation must supply its own version of the functions below
 */
bool initialize_led(int led);
bool switch_led_on(int led);
bool switch_led_off(int led);

}
}

#endif