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
 * This    : LED Support - CC-3200 specific - header file                  *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ADM_UTIL_LED_CC3200_H
#define ADM_UTIL_LED_CC3200_H

#include "led.h"

namespace adm {
namespace util {

enum CC3200LED {

    L1     = 9,
    RED    = 9,

    L2     = 10,
    ORANGE = 10,

    L3     = 11,
    GREEN  = 11
};

}
}

#endif