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
 * This    : Wrapper for Simplelink main header file                       *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ADM_TI_SIMPLELINK_WRAPPER_HPP
#define ADM_TI_SIMPLELINK_WRAPPER_HPP

/*
   CAUTION!!!
     A bug in TI's simplelink.h header (at least in version 1.0.1.6) causes an
     extern "C" declaration to be opened once and closed twice within that
     file. Here we work around this problem by using nesting, so we open an
     extern "C" before including "simplelink.h", and then test the specific
     SimpleLink version to check if we need to close it.
   NOTE: this is solved in version 1.0.1.11 of SimpleLink (SDK 1.3.0 for CC3200)
 */
extern "C" {
#include "simplelink.h"
#if (! (SL_MAJOR_VERSION_NUM==1L && SL_MINOR_VERSION_NUM==0L && SL_VERSION_NUM==1L && SL_SUB_VERSION_NUM==6L ))
    } // close extern "C"
#endif

#endif // ADM_TI_SIMPLELINK_WRAPPER_HPP

