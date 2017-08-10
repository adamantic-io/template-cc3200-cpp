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
 * This    : Common project-wide definitions                               *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DEFS_H
#define DEFS_H

#ifdef USE_FREERTOS
  #include "FreeRTOS.h"
  #define TIMER_TASK_PRIORITY       configTIMER_TASK_PRIORITY
  #define DEFAULT_TASK_STACK_BYTES  4096

  #define DisableInterrupts()      taskENTER_CRITICAL()
  #define EnableInterrupts()       taskEXIT_CRITICAL()


#else
    /* 
        Standard ARM instructions to disable/enable interrupts
        it is preferrable to use the FreeRTOS-provided capability,
        so these are disabled for now.
    */
    #define DisableInterrupts()      __asm__("cpsid i")
    #define EnableInterrupts()       __asm__("cpsie i")
#endif

#ifdef USE_LOGGER 
  #define LOGGER_TASK_PRIORITY      1
  #define LOGGER_QUEUE_SIZE         16
  #define MYLOG adm::util::Logger::i().log
  #include "logger.h"
#else
  #include "uart_if.h"
  #define MYLOG Report
#endif

#ifdef USE_WIRELESS
  #define WIRELESS_MANAGEMENT_TASK_PRIORITY    1
  #define WIRELESS_MANAGEMENT_TASK_STACK_BYTES 2048
  #define WIRELESS_SSID "SSID"
  #define WIRELESS_PWD  "PASSWORD"
#endif

#define IS(x)                   ((x) == 1)

#define ASSERT(x)       \
do {                    \
   if ( ! ( x ) )       \
   {                    \
      ASSERT_STOP ( ) ; \
   }                    \
} while (0)

#define ASSERT_STOP()                                   \
do                                                      \
{                                                       \
    DisableInterrupts();                                \
    while(1);                                           \
} while (0)



#ifdef __cplusplus
    extern "C" {
#endif

unsigned long avail_heap(); // very platform-specific,
                            // defined in the compiler startup file.

#ifdef __cplusplus
    }
#endif

#endif

