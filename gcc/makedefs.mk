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
# Texas Instruments CC-3200 "make definitions"
# 
# This file is provided under the GNU Lesser General Public License v.3,
# Please read the LICENSE file provided with this source code distribution
##########################################################################

OBJDIR?=obj
BINDIR?=exe

ifeq (${PREFIX}, arm-none-eabi-)

AFLAGS=-mthumb \
       -mcpu=cortex-m4  \
       -MD
 

CFLAGS= -ffunction-sections \
        -specs=nano.specs \
        -specs=nosys.specs \
		-fno-common \
    	-fmessage-length=0 \
        -fdata-sections     \
        -mcpu=cortex-m4 \
        -fno-builtin \
        -pedantic \
        -std=c11 \
        -mthumb \
        -MD \
        -Wall



CPPFLAGS= \
    -ffunction-sections \
    -specs=nano.specs \
    -fno-exceptions \
    -fno-rtti \
    -specs=nosys.specs \
    -fno-common \
    -fmessage-length=0 \
    -fdata-sections \
    -mcpu=cortex-m4 \
    -fno-builtin \
    -std=c++14 \
    -pedantic \
    -mthumb \
    -Wall \
    -MD \
    -c \

DEFINES= -Dcc3200


LDFLAGS= 	-ffunction-sections \
            -specs=nano.specs \
    		-fno-exceptions \
    		-fno-rtti \
			-specs=nosys.specs \
    		-fno-common \
    		-fmessage-length=0 \
    		-fdata-sections \
    		-mcpu=cortex-m4 \
    		-fno-builtin \
    		-std=c++14 \
    		-pedantic \
    		-mthumb \
    		-Wall \
    		-MD \
			-Wl,--gc-sections,--no-wchar-size-warning \
         	-static

ifeq (${DEBUG},1)
CFLAGS+=-O1
CFLAGS+=-g
CPPFLAGS+=-O1
CPPFLAGS+=-g
LDFLAGS+=-O1
LDFLAGS+=-g
DEFINES+=-DDEBUG
else
CFLAGS+=-Os
CPPFLAGS+=-Os
LDFLAGS+=-Os
DEFINES+=-DNDEBUG
endif

CC=${ARM_GCC}
CPP=${ARM_GPP}
AR=${ARM_AR}
LD=${ARM_LD}
OBJCOPY=${ARM_OBJCOPY}

else 
# The flags passed to the compiler when we are not using arm-none-eabi tools.
CFLAGS= -pedantic \
        -std=c11 \
        -Wall \
        -O1 \
        -g \
        -c

CPPFLAGS= \
    -std=c++14 \
    -pedantic \
    -Wall \
    -c 

#LDFLAGS+=	-lpthread \
#			-lcrypto

CPP=$(CXX)

endif

CC=${PREFIX}gcc
CPP=${PREFIX}g++
AR=${PREFIX}ar
LD=${PREFIX}ld
OBJCOPY=${PREFIX}objcopy

# Add the include file paths to AFLAGS and CFLAGS.
AFLAGS+=${patsubst %,-I%,${subst :, ,${IPATH}}}
CFLAGS+=${patsubst %,-I%,${subst :, ,${IPATH}}}
CPPFLAGS+=${patsubst %,-I%,${subst :, ,${IPATH}}}


${OBJDIR}/%.o: %.cpp
	@if [ 'x${VERBOSE}' = x ];                            \
	 then                                                 \
	     echo "  CPP   ${<}";                             \
	 else                                                 \
		 echo ${CPP} ${CPPFLAGS} ${DEFINES} -o ${@} ${<}; \
	 fi
	 @${CPP} ${CPPFLAGS} ${DEFINES} -o ${@} ${<}

${OBJDIR}/%.o: %.c
	@if [ 'x${VERBOSE}' = x ];                            \
	 then                                                 \
	     echo "  CC    ${<}";                             \
	 else                                                 \
	     echo ${CC} ${CFLAGS} ${DEFINES} -c -Dgcc -o ${@} ${<}; \
	 fi
	@${CC} ${CFLAGS} ${DEFINES} -c -Dgcc -o ${@} ${<}

${OBJDIR}/%.o: %.S
	@if [ 'x${VERBOSE}' = x ];                            \
	 then                                                 \
	     echo "  AS    ${<}";                             \
	 else                                                 \
	     echo ${CC} ${AFLAGS} ${DEFINES} -Dgcc -o ${@} -c ${<}; \
	 fi
	@${CC} ${AFLAGS} ${DEFINES} -Dgcc -o ${@} -c ${<}

${BINDIR}/%.a:
	@if [ 'x${VERBOSE}' = x ];                            \
	 then                                                 \
	     echo "  AR    ${<}";                             \
	 else                                                 \
		 echo ${AR} -cr ${@} ${^};                        \
	 fi
	@${AR} -cr ${@} ${^};


${BINDIR}/%.axf:
	@if [ 'x${VERBOSE}' = x ];                            \
	 then                                                 \
	     echo "  LD    ${@}";                             \
	 else                                                 \
	     echo ${CPP} -T ${SCATTERgcc_myproject} ${LDFLAGS} --entry ResetISR -o ${@} $(filter %.o %.a, ${^}) \
	 -lgcc -lm -lc -lstdc++ -lsupc++ ;             \
	 fi
	@${CPP} -T ${SCATTERgcc_myproject} ${LDFLAGS} --entry ResetISR -o ${@} $(filter %.o %.a, ${^}) \
	 -lgcc -lm -lc -lstdc++ -lsupc++ 
	@${OBJCOPY} -O binary ${@} ${@:.axf=.bin}

${BINDIR}/%.bin:
	@echo "LD ${@}"
	@${CPP} ${LDFLAGS} ${DEFINES} -o ${@} $(filter %.o %.a, ${^})
