#                      `..--::::::--.``
#                  `-:/++:--.`      ``....``
#                .://+:.        ``..``    .-.`
#              `://+/`      .-//-.       .yss
#             `://+:      .://`         `so`y+
#             -///+      -//+           +y. :y:
#            `:////     `://:          :y:   +y.
#             :///+     `////         .yo    `ss
#             -///+.     -//+.        sy+/////oy+
#             `////+`     -//+-      +y-......./y:
#              `/////`     .///:`   -y/         +y.
#               `/////-      -///:.`++          `+/
#                 -////:.      .:///-.`                     `
#                  `:////:.       `-:/+/-..``     `..`     .
#                    .://///-`         .--:::::---.       .-
#                      `-/////:-.                       `::
#                         `-/+////:-.``              `.:/.
#                             .-:/+/////::--------::+/:.
#                                  .--::////////::-.`
#                           ADAMANTIC SOLUTIONS
#                     Copyright (C) 2017 Adamantic Srl
##########################################################################
# Adamantic Solutions for IoT
# Texas Instruments CC-3200 template makefile
# 
# This file is provided under the GNU Lesser General Public License v.3,
# Please read the LICENSE file provided with this source code distribution
##########################################################################

#
# BEGIN - BUILDING CONFIGURATION PART
#         Modify the variables
#


# VERBOSE
# -------
# Set to `1` if you want verbose output from the build script
VERBOSE=

# DEBUG
# -----
# Set to `1` if you want a debug-enabled build
DEBUG=

# USE FLAGS
# ---------
# Set these flags to `1` if you want the specific feature enabled
#
USE_FREERTOS=1
USE_LOGGER=1
USE_SIMPLELINK=1
USE_WIRELESS=1
USE_LED=1
USE_MQTT=1

# CC3200_SDK_ROOT
# -------
# Set this to the directory where the CC-3200 SDK is installed
# Currently supported version of the SDK : 1.2.0
CC3200_SDK_ROOT=/opt/cc3200-sdk

# FREERTOS_SOURCE
# -------
# Set this to the `Source` directory contained in your local copy of
# FreeRTOS 9.0.x.
# This property must be set if USE_FREERTOS is set to `1`
FREERTOS_SOURCE=/opt/FreeRTOSv9.0.0/FreeRTOS/Source


#
# END - BUILD CONFIGURATION PART
#         Do not modify lines below this disclaimer unless you know
#         exactly what you are doing


ifeq (${USE_LOGGER},1)
ifneq (${USE_FREERTOS},1)
$(error USE_LOGGER requires USE_FREERTOS)
endif
endif

ifeq (${USE_WIRELESS},1)
ifneq (${USE_SIMPLELINK},1)
$(error USE_WIRELESS requires USE_SIMPLELINK)
endif
endif

ifeq (${USE_MQTT},1)
ifneq (${USE_SIMPLELINK},1)
$(error USE_MQTT requires USE_SIMPLELINK)
endif
endif

ifeq (${USE_LED},1)
ifneq (${USE_FREERTOS},1)
$(error USE_LED requires USE_FREERTOS)
endif
endif


PROJBASE=../..

PREFIX=arm-none-eabi-

#
# Include the common make definitions.
#
include ./makedefs.mk

SCATTERgcc_myproject=myproject.ld
ENTRY_myproject=ResetISR

#
# Where to find source files that do not live in this directory.
#
VPATH=../src
VPATH+=${CC3200_SDK_ROOT}/driverlib
VPATH+=${CC3200_SDK_ROOT}/example/common

#
# Where to find header files that do not live in the source directory.
#

IPATH=../include
IPATH+=${CC3200_SDK_ROOT}/tools
IPATH+=${CC3200_SDK_ROOT}/inc
IPATH+=${CC3200_SDK_ROOT}/oslib
IPATH+=${CC3200_SDK_ROOT}/driverlib
IPATH+=${CC3200_SDK_ROOT}/example/common



#
# The default rule, which causes the driver library to be built.
#
all: ${OBJDIR} ${BINDIR}
all: ${BINDIR}/myproject.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${OBJDIR} ${wildcard *~}
	@rm -rf ${BINDIR} ${wildcard *~}


#
# The rule to create the target directories.
#
${OBJDIR}:
	@mkdir -p ${OBJDIR}

${BINDIR}:
	@mkdir -p ${BINDIR}


#
# Files to be built and linked to build the final solution.
#
${BINDIR}/myproject.axf: ${OBJDIR}/main.o     # main file
${BINDIR}/myproject.axf: ${OBJDIR}/init.o     # board initialization
${BINDIR}/myproject.axf: ${OBJDIR}/uart_if.o  # UART console
${BINDIR}/myproject.axf: ${OBJDIR}/pinmux.o   # TI PinMux configuration
${BINDIR}/myproject.axf: ${OBJDIR}/startup_gpp.o # GCC-C++ startup




ifeq (${USE_FREERTOS},1)

# Currently using a GCC/ARM_CM3 port of FreeRTOS 9.0.0, as the ports for
# ARM_CM4 don't seem to work yet (waiting for official TI support), given
# that the CM4 shipped in CC3200 has no FPU.

FREERTOS_PORT=${FREERTOS_SOURCE}/portable/GCC/ARM_CM3
#
# Adding the USE_FREERTOS flag to the compiler
#
CFLAGS+=-DUSE_FREERTOS
CFLAGS+=-DSL_PLATFORM_MULTI_THREADED

CPPFLAGS+=-DUSE_FREERTOS
CPPFLAGS+=-DSL_PLATFORM_MULTI_THREADED

VPATH+=${FREERTOS_SOURCE}
VPATH+=${FREERTOS_PORT}
VPATH+=${FREERTOS_SOURCE}/portable/MemMang

IPATH+=${FREERTOS_SOURCE}
IPATH+=${FREERTOS_SOURCE}/include
IPATH+=${FREERTOS_PORT}

${BINDIR}/myproject.axf: ${OBJDIR}/port.o     # FreeRTOS port
${BINDIR}/myproject.axf: ${OBJDIR}/queue.o    # FreeRTOS queues
${BINDIR}/myproject.axf: ${OBJDIR}/tasks.o    # FreeRTOS tasks
${BINDIR}/myproject.axf: ${OBJDIR}/timers.o   # FreeRTOS software timers
${BINDIR}/myproject.axf: ${OBJDIR}/list.o     # FreeRTOS lists
${BINDIR}/myproject.axf: ${OBJDIR}/heap_3.o   # FreeRTOS memory allocator
${BINDIR}/myproject.axf: ${OBJDIR}/osi_freertos.o   # FreeRTOS OSI indirection

endif


ifeq (${USE_SIMPLELINK},1)
CFLAGS+=-DUSE_SIMPLELINK
CPPFLAGS+=-DUSE_SIMPLELINK

IPATH+=${CC3200_SDK_ROOT}/simplelink/include
IPATH+=${CC3200_SDK_ROOT}/simplelink_extlib/include
IPATH+=${CC3200_SDK_ROOT}/simplelink_extlib/provisioninglib

# will include libsimplelink.a at the end as it needs to be after all the .o
endif


ifeq (${USE_MQTT},1)
CFLAGS+=-DUSE_MQTT
CPPFLAGS+=-DUSE_MQTT

IPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/platform
IPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/common
IPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/include
IPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/client

VPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/common
VPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/client
VPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/platform
VPATH+=${CC3200_SDK_ROOT}/netapps/mqtt/sl

${BINDIR}/myproject.axf: ${OBJDIR}/mqtt_common.o
${BINDIR}/myproject.axf: ${OBJDIR}/mqtt_client.o
${BINDIR}/myproject.axf: ${OBJDIR}/sl_mqtt_client.o
${BINDIR}/myproject.axf: ${OBJDIR}/cc3200_platform.o
${BINDIR}/myproject.axf: ${OBJDIR}/cc31xx_sl_net.o
endif

ifeq (${USE_LOGGER},1)
CFLAGS+=-DUSE_LOGGER
CPPFLAGS+=-DUSE_LOGGER
${BINDIR}/myproject.axf: ${OBJDIR}/logger.o            # Serial logger
endif

ifeq (${USE_WIRELESS},1)
CFLAGS+=-DUSE_WIRELESS
CPPFLAGS+=-DUSE_WIRELESS
${BINDIR}/myproject.axf: ${OBJDIR}/wireless.o          # WiFi system
endif

ifeq (${USE_LED},1)
CFLAGS+=-DUSE_LED
CPPFLAGS+=-DUSE_LED
${BINDIR}/myproject.axf: ${OBJDIR}/led.o        # Generic LED handling
${BINDIR}/myproject.axf: ${OBJDIR}/led_cc3200.o # LED specifics for CC3200
${BINDIR}/myproject.axf: ${OBJDIR}/gpio_if.o    # Simplified GPIO interface
endif


ifeq (${USE_SIMPLELINK},1)
${BINDIR}/myproject.axf: ${CC3200_SDK_ROOT}/simplelink/gcc/${BINDIR}/libsimplelink.a
endif
${BINDIR}/myproject.axf: ${CC3200_SDK_ROOT}/driverlib/gcc/${BINDIR}/libdriver.a


#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${OBJDIR}/*.d} __dummy__
endif
