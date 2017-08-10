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
 * This    : Logging basic support - header file                           *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ADM_UTIL_LOGGER_H
#define ADM_UTIL_LOGGER_H

#include <string>
#include <memory>
#include <cstdio>

#include "string_format.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

namespace adm {
namespace util {

extern "C" void rtos_logger_task(void* p);

class Logger {
public:
    using string = std::string;

    bool log(const string& msg, bool from_isr=false);

    template <bool from_isr=false, typename ... Args> void log(const char* fmt, Args ... args) {
        string s = format(fmt, args ...);
        log(s, from_isr);      
    }

    static Logger& i() {
        static Logger l;
        return l;
    }
    ~Logger();
private:
    friend void rtos_logger_task(void*);
    
    Logger(
        unsigned queue_size = LOGGER_QUEUE_SIZE,
        unsigned task_prio  = LOGGER_TASK_PRIORITY
    );

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    TaskHandle_t  task_;
    QueueHandle_t queue_;
};

}
}

#endif