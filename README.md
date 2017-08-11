# template-cc3200-cpp
Template for FreeRTOS or bare metal CC3200 projects in C++ 

## Quick Start

### Prerequisites
Before you start playing with this software, you should install:
* The [CC3200 SDK](http://www.ti.com/tool/cc3200sdk) provided from Texas Instruments.
* The [FreeRTOS](http://www.freertos.org/) source distribution - I tested this with version [9.0.0](https://sourceforge.net/projects/freertos/files/FreeRTOS/V9.0.0/FreeRTOSv9.0.0.zip/download)
* The GCC/G++ cross-compiler suite for ARM
* GNU Make
* The [cc3200tool](https://github.com/ALLTERCO/cc3200tool#installation), to write your program to the CC3200 flash (this wonderful tool actually does *much more* than this, but see its github page for details).

*Hint*: if you have an Ubuntu system you might find [this guide](https://hackpad.com/Using-the-CC3200-Launchpad-Under-Linux-Rrol11xo7NQ) handy to get you up and running with the compiler and tools (I used it with success, but skipped the *NuttxOS* part as I'm using *FreeRTOS* instead).

### Configure the build
Once the prerequisites are met, just make a copy/clone of the project, then edit the `Makefile` to enable/disable the different project features, depending on your needs:
 * `DEBUG`: set it to `1` if you need to debug your program.
 * `USE_FREERTOS`: set it to `1` if you want FreeRTOS compiled into your application.
 * `USE_LOGGER` (requires `USE_FREERTOS`): set it to `1` if you want to use an easier and multi-process log interface. This is especially useful if you are going to have more than one task writing to the console at the same time. 
 * `USE_SIMPLELINK`: set it to `1` if you are going to use Texas Instrument's *SimpleLink* facilities.
 * `USE_WIRELESS`: set it to `1` to enable wireless support. For this you also need to to configure the `WIRELESS_SSID` and `WIRELESS_PWD` in `include/defs.h`
 * `USE_LED`: set it to `1` to enable LED support.
 * `USE_MQTT`: set it to `1` to enable support for the MQTT protocol.

 Besides the aforementioned toggles, you also have to configure the following two variables:
 * `CC3200_SDK_ROOT`: point it to the main directory of the CC3200 SDK provided by Texas Instruments
 * `FREERTOS_SOURCE`: point it to the main `Source` folder of your copy of FreeRTOS

### Launch the build
Open a terminal, go to the `gcc` directory, and issue the following commands:
```
make clean
make
```
Please note that, whenever including the `simplelink` header files, the compiler may issue quite a few warnings about redefined symbols. This happens because `simplelink` has a compatibility layer that emulates parts of the POSIX stack, but for some reason the symbols are not "undefined" before being "redefined". It's a bit annoying as it clutters the build output, but fine enough for the purpose of this project (in future I might try solving this issue).

Finally, ensuring you got your MCU correctly connected, launch the
```
./flash
```
script and follow the instructions. If everything goes well, you have just uploaded your application to the CC3200.
If it's going to print something over the UART, you might want to launch
```
minicom -o -D /dev/ttyUSB1
```
(where `ttyUSB1` might actually be `ttyUSB0` or wherever your CC3200 attaches itself - btw if it changes you also need to update the `flash` script)

You are all set, enjoy!

## Disclaimer
This template has been developed on a GNU/Linux computer, using the GCC/G++ cross-compiler for ARM v. 4.9.3.
Though it *might* work with other configurations (such as MinGW, WSL, or other GCC versions) **I haven't tested it** other than on my configuration (Ubuntu 16.04 on x86).

Please feel free to contribute with better/improved hardware support, modularity, more platforms, or whatever you like.

