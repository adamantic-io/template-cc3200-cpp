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
 * This    : Logging basic support - implementation                        *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defs.h"
#include "logger.h"
#include "uart_if.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <cstring>

namespace adm {
namespace util {

using namespace std;

namespace {
  volatile bool RTOS_LOGGER_TASK_STARTED = false;
}

extern "C" void rtos_logger_task(void* p)
{
  RTOS_LOGGER_TASK_STARTED = true;
	Logger* lptr = static_cast<Logger*>(p);
	const char* mptr;
	while(1) {
		if(xQueueReceive( lptr->queue_, &mptr, portMAX_DELAY)) {
			Message(mptr);
			delete[] mptr;
		}
	}
}

Logger::Logger(unsigned queue_size, unsigned task_prio) {
	
	queue_ = xQueueCreate(queue_size, sizeof(const char*));
	xTaskCreate(rtos_logger_task, "LOGGER", 
                (DEFAULT_TASK_STACK_BYTES / (sizeof( portSTACK_TYPE ))), 
                this, task_prio, &task_);

}

Logger::~Logger() {
	// TODO: nothing for now, will leave the task and the queue 
}

bool Logger::log(const string& msg, bool from_isr) {

  if (!RTOS_LOGGER_TASK_STARTED) {
    // we are probably still in the initialisation phase, so
    // don't rely on OS and shorcut to the UART directly
    Message(msg.c_str());
    return true;
  }

	size_t size = msg.length()+1;
	char* data = new char[size];
	memcpy(data, msg.c_str(), size);

	bool rv;
	if (from_isr) {
		BaseType_t higher_prio_woken;
		rv = ( xQueueSendFromISR(queue_, data, &higher_prio_woken) == pdTRUE );
		if (higher_prio_woken) taskYIELD();
	} else {
		rv = ( xQueueSend(queue_, &data, ( TickType_t ) 0) == pdTRUE );
	}
	return rv;
}

}
}