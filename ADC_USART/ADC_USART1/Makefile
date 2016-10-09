#
# Simple makefile to compile the STM32Cube example code given for the STM32F0xx
# family of ARM processors. This file should be placed in the example/demo
# directory that you wish to compile.
#
# INCLUDEDIRS selects all folders in the package that have header files. Since
#             this is already an inclusive list, it should not need editing.
#
# LIBSOURCES contains all the Driver (HAL/BSP) files that need to be compiled
#            for this specific project. This should be updated with the help
#            of the dependencies file (main.d) generated on any (including
#            unsucessful) compilation.
#
# Note: The provided code sometimes uses windows backslashes (\) in include
#       paths. Update as needed.
#
# Note: When building the lists for LIBSOURCES, *_ex.c files must come before
#       the generic version of the file. This is necessary for linking to find
#       the extended (board-specific) version of the function.
#
# Example: These sources are meant for the CORTEXM_SysTick example. The file
#          should be saved at STM32Cube_FW_F0_V1.1.0/Projects/
#          STM32F072B-Discovery/Examples/Cortex/CORTEXM_SysTick/Makefile.
#
# Author: Ian Hartwig (ihartwig)
#
# Derived from szczys's makefile in
# www.github.com/szczys/stm32f0-discovery-basic-template/
#

# build environment
CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
AR = arm-none-eabi-ar
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
MAKE = make

# location of OpenOCD Board .cfg files (only used with 'make program')
# OPENOCD_BOARD_DIR=/usr/share/openocd/scripts/board
OPENOCD_BOARD_DIR=/usr/local/share/openocd/scripts/board

# Configuration (cfg) file containing programming directives for OpenOCD
OPENOCD_PROC_FILE=stm32f1-openocd.cfg

# project parameters
PROJ_NAME = ADC_USART1
CPU_FAMILY = STM32F10x
CPU_MODEL_GENERAL = STM32F103xE
CPU_MODEL_SPECIFIC = STM32F103VE

#if include file .h on Desktop
#INCLUDEDIRS +=../../../../../xuan/Desktop/include/


INCLUDEDIRS =
#INCLUDEDIRS +=../../../../../xuan/sopcast-player/include1
#INCLUDEDIRS +=../../../../../xuan/irc/include2
INCLUDEDIRS += include
INCLUDEDIRS += system/include/stm32f1-stdperiph
INCLUDEDIRS += system/include/cmsis

INCLUDEDIRS += FreeRTOS/include
INCLUDEDIRS += FreeRTOS/portable/RVDS/ARM_CM3

#INCLUDEDIRS += Drivers/CMSIS/Device/ST/STM32F1xx/Include

# -lc      : link to standard C library ( stdio.h and stdlib.h)
# -lg      : a debugging-enabled libc
# -lm      : link to math C library ( math.h )
# -lnosys  : non-semihosting
#            link to libnosys.a - The libnosys.a is used to satisfy all system call references,
#            although with empty calls. In this configuration, the debug output
#            is forwarded to the semihosting debug channel, vis SYS_WRITEC.
#            The application and redefine all syscall implementation functions, like _write(),
#            _read(), etc. When using libnosys.a, the startup files are not needed
#            Since 4.8, recommended -specs=nosys.specs instead
# -lrdimon : semihosting
#            link to librdimon.a - implements all system calls via the semihosting API with all
#            functionality provided by the host. When using librdimon.a, the startup files are
#            required to provide all specific initialisation, and the rdimon.specs
#            must be added to the linker
#            Since 4.8, recommended -specs=rdimon.specs instead
LIBSOURCES =
LIBSOURCES += system/src/stm32f1-stdperiph/misc.c
LIBSOURCES += system/src/stm32f1-stdperiph/stm32f10x_adc.c
LIBSOURCES += system/src/stm32f1-stdperiph/stm32f10x_dma.c
LIBSOURCES += system/src/stm32f1-stdperiph/stm32f10x_rcc.c
LIBSOURCES += system/src/stm32f1-stdperiph/stm32f10x_tim.c
LIBSOURCES += system/src/stm32f1-stdperiph/stm32f10x_gpio.c
LIBSOURCES += system/src/stm32f1-stdperiph/stm32f10x_usart.c

LIBSOURCES += FreeRTOS/croutine.c
LIBSOURCES += FreeRTOS/event_groups.c
LIBSOURCES += FreeRTOS/list.c
LIBSOURCES += FreeRTOS/queue.c
LIBSOURCES += FreeRTOS/tasks.c
LIBSOURCES += FreeRTOS/timers.c

LIBSOURCES += FreeRTOS/portable/MemMang/heap_1.c
LIBSOURCES += FreeRTOS/portable/MemMang/heap_2.c
LIBSOURCES += FreeRTOS/portable/MemMang/heap_3.c
LIBSOURCES += FreeRTOS/portable/MemMang/heap_4.c
LIBSOURCES += FreeRTOS/portable/RVDS/ARM_CM3/port.c



LIBOBJS = $(LIBSOURCES:.c=.o)

################################################################################
# auto-generated project paths
# SOURCES = main.c ADC.c SysTick.c Usart.c
SOURCES = $(shell find src -name *.c)
SOURCES += system/src/cmsis/system_stm32f10x.c
SOURCES += system/src/cmsis/startup_stm32f10x_hd.s # add assembly startup template

OBJ1 = $(SOURCES:.c=.o)
OBJ = $(OBJ1:.s=.o)

LDSCRIPT = -Wl,-T STM32F103VE_FLASH.ld

CFLAGS = -Wall -g -O0 -D $(CPU_MODEL_GENERAL) #-include stm32f1xx_hal_conf.h
CFLAGS += -mlittle-endian -mcpu=cortex-m3 -march=armv7-m -mthumb -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DHSE_VALUE=8000000
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(PROJ_NAME).map
CFLAGS +=  $(addprefix -I ,$(INCLUDEDIRS))



.PHONY: all

all: proj

proj: libstm32f1.a $(PROJ_NAME).elf

libstm32f1.a: $(LIBOBJS)
	@echo
	$(AR) -r $@ $(LIBOBJS)

%.o: %.c
	@echo
# $(eval AUTOINCLUDES = $(addprefix -include ,$(shell find $(dir $<) -name *.h)))
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJ_NAME).elf: $(SOURCES)
# -l : library search, applies in a special way to libraries used with the linker
#      (GNU Make - page 28 - 4.4.6 Directory Search for Link Libraries)
# -L : Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L.
#      Libraries (-lfoo) should be added to the LDLIBS variable instead.
#      (GNU Make - page 72 - 6.13 Suppressing Inheritance)
# -T : ld script file
#$(CC) $(CFLAGS) $^ -o $@ -L . -lstm32f1 $(LDSCRIPT) -MD
	@echo
	$(CC) $(CFLAGS) $^ -o $@ $(LIBOBJS) $(LDSCRIPT) --specs=nano.specs --specs=rdimon.specs -lc -lm -lrdimon
	rm $(LIBOBJS) || true
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf >$(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf

#program: proj
#	openocd -f $(OPENOCD_BOARD_DIR)/stm32f0discovery.cfg -f $(OPENOCD_PROC_FILE) -c "stm_flash `pwd`/$(PROJ_NAME).bin" -c shutdown

#openocd:
#	openocd -f $(OPENOCD_BOARD_DIR)/stm32f0discovery.cfg -f $(OPENOCD_PROC_FILE)

clean:
	#rm $(LIBOBJS) || true
	rm libstm32f1.a || true
	rm $(PROJ_NAME).d   || true
	rm $(PROJ_NAME).elf || true
	rm $(PROJ_NAME).hex || true
	rm $(PROJ_NAME).bin || true
	rm $(PROJ_NAME).map || true
	rm $(PROJ_NAME).lst || true
	
write:
	stm32flash -w $(PROJ_NAME).hex  -v -g 0x8000000 /dev/ttyUSB0	
