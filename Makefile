#
# stm32f4xx-bootloader
# Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
#

CROSS_COMPILE=/opt/arm-2012.03/bin/arm-none-eabi-

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
NM=$(CROSS_COMPILE)nm

# Special variables for Cortex-M4F
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp
OPENLPC_PATH := /home/cristovao/workspace/open-lpc-all/open-lpc

# Assembler flags
AFLAGS=-mthumb \
       $(CPU)  \
       $(FPU)  \
       -MD

# Include path
INCLUDEDIR+=-I. \
	-I$(OPENLPC_PATH)/include \
	-I$(OPENLPC_PATH)/ports/STM32F4xx/inc

# GCC C Flags
CFLAGS := -mthumb			\
		$(CPU)			\
		$(FPU)			\
		-Os			\
		-ffunction-sections	\
		-fdata-sections		\
		-MD			\
		-Wall   		\
		-c			\
		-DHSE_VALUE=8000000	\
		$(INCLUDEDIR)

# Linker flags
LDFLAGS := --gc-sections

OBJ+=openlpc_xmodem.o \
	system_stm32f4xx.o \
	startup_stm32f4xx.o \
	main.o

OPENLPC_OBJ+=$(OPENLPC_PATH)/ports/STM32F4xx/src/digital_io.o \
	$(OPENLPC_PATH)/ports/STM32F4xx/src/uart.o \
	$(OPENLPC_PATH)/ports/STM32F4xx/src/misc.o

PROJECT := stm32f4xx-bootloader

all: $(OBJ) $(OPENLPC_OBJ)
	@echo -e "\e[1;32mDone building object files\e[0m"
	@echo
	@echo -e "\e[1;33mLinking...\e[0m"
	${LD} $(LDFLAGS) -T stm32f4xx_linker.ld --entry Reset_Handler $(OBJ) -o $(PROJECT).elf
	@echo "Done. Generating bin file..."
	${OBJCOPY} -O binary $(PROJECT).elf $(PROJECT).bin
	@echo -e "\e[1;32mDone\e[0m"

clean:
	@echo -e "\e[1;33mCleaning object files...\e[0m"
	$(RM) $(OBJ) $(OPENLPC_OBJ)
	$(RM) $(shell find . -type f -iname "*.d")
	$(RM) $(PROJECT).elf $(PROJECT).bin
	@echo -e "\e[1;32mDone\e[0m"

elf-info:
	$(NM) -SC $(PROJECT).elf

