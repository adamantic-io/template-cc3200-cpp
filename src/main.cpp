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
 * This    : Application Entry Point - implementation                      *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// Application includes
#include "defs.h"
#include "init.h"
#include "pinmux.h"
#include "uart_if.h"

#ifdef USE_FREERTOS
  #include "FreeRTOS.h"
  #include "task.h"
#endif

#ifdef USE_SIMPLELINK
  #include "simplelink_wrapper.h"
#endif

#ifdef USE_WIRELESS
  #include "wireless.h"
#endif

#ifdef USE_LED
  #include "led.h"
  #include "led_cc3200.h"
#endif

#ifdef USE_WIRELESS
    void wireless_management_task(void* p);
    TaskHandle_t g_wireless_man_task;
#endif

/**********************************************
Function: main : Start of application code
**********************************************/
int main()
 {
    /* Initailizing the board */
    BoardInit();

    /* Configure the pin multiplexer (handy tool PinMux from TI) */
    PinMuxConfig();

    /* Initializing the Terminal. */
    InitTerm();
    ClearTerm();

    #ifdef USE_SIMPLELINK
        //
        // Start the SimpleLink Host
        //
        Message("Starting SimpleLink task...\n\r");
        long lRetVal = VStartSimpleLinkSpawnTask(9);
        if(lRetVal < 0)
        {
            Message("Could not start the SimpleLink Task...\n\r");
            while(true) { }
        }
    #endif // USE_SIMPLELINK

    #ifdef USE_LOGGER
        adm::util::Logger::i(); // initializing the Logger...
    #endif // USE_LOGGER

    #ifdef USE_LED
        using adm::util::LedBlinker;
        using LedStatus = adm::util::LedBlinker::Status;
        using adm::util::CC3200LED;
        LedBlinker& red_led = LedBlinker::for_led(CC3200LED::RED);
        red_led.set(LedStatus::SLOW_BLINK);
    #endif
    #ifdef USE_WIRELESS
        xTaskCreate(wireless_management_task, "W-MAN", 
                    (WIRELESS_MANAGEMENT_TASK_STACK_BYTES / (sizeof( portSTACK_TYPE ))), 
                    NULL, 1, &g_wireless_man_task);
    #endif // USE_WIRELESS

    #ifdef USE_FREERTOS
        Message("Starting the scheduler...\n\r");
        vTaskStartScheduler();
        Message("I should never get here!\n\r");
    #endif // USE_FREERTOS
}



#ifdef USE_WIRELESS
    void wireless_management_task(void* p) {
        using WC = adm::net::WirelessConnection;
        MYLOG("Init wireless connection\n\r");
        std::string deviceIp;

        WC::on_connection_up([&]() {
            MYLOG("Connection established\n\r"); 
        });

        WC::on_connection_down([&](bool user_initiated) {
            MYLOG("Connection down\n\r");
        });

        WC::on_connection_fail([&]() {
            MYLOG("Connection failed\n\r"); 
        });

        WC::on_ip_acquired([&](const std::string& ip) {
            deviceIp = ip;
            Report("IP Acquired: %s\n\r", ip.c_str());
        });
        
        MYLOG("Connecting to wireless ...\n\r");
        WC::wlan_connect(WIRELESS_SSID, WIRELESS_PWD, WC::WPA_WPA2);

        while (true) {
            taskYIELD();
        }
    }
#endif

