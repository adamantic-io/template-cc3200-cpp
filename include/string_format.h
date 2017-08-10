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
 * This    : String-formatting utilities                                   *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <memory>
#include <string>
#include <cstdio>

#ifndef ADM_UTIL_STRING_FMT_HPP
#define ADM_UTIL_STRING_FMT_HPP

namespace adm { namespace util { 


int constexpr length(const char* str)
{
    return *str ? 1 + length(str + 1) : 0;
}

template<int bufsize, typename ... Args>
std::string format_static( const char* fmt, Args ... args )
{
    using namespace std;
    char buf[bufsize];
    int effsz = snprintf( buf, bufsize, fmt, args ... );
    return string( buf, buf + effsz );
}


template<typename ... Args>
std::string format( const char* fmt, Args ... args )
{
    using namespace std;
    size_t size = snprintf( nullptr, 0, fmt, args ... ) + 1; // Extra space for '\0'
    unique_ptr<char[]> buf( new char[ size ] ); 
    snprintf( buf.get(), size, fmt, args ... );
    return string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}



}}

#endif
