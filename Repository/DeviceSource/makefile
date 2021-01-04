#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
# 
#  Modified by https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

#   MCU Types:
#     atmega16u2    for Arduino UNO R3
#     atmega32u4    for Arduino Micro, and Teensy 2.0
#     at90usb1286   for Teensy 2.0++

#   Set MCU and TARGET here:

ifeq ($(MCU),)
MCU := at90usb1286
endif
ifeq ($(TARGET),)
TARGET := TurboA
#TARGET := Sandbox
endif


################################################################################
#   Ignore all this stuff below.

#MCU          = atmega16u2
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
#TARGET       = TurboA
SRC          = $(TARGET).c
LUFA_PATH    = ./LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -I./ -ILUFA/ -Wno-unused-function -Werror



#   Framework
SRC += $(LUFA_SRC_USB)
SRC += CommonFramework/FrameworkSettings.c
SRC += DeviceFramework/DeviceSettings.c
SRC += DeviceFramework/HardwareLED.c
ifneq ("$(wildcard DeviceFramework/PushButtons.c)","")
SRC += CommonFramework/CRC32.c
SRC += DeviceFramework/uart.c
SRC += DeviceFramework/HardwareUSB.c
SRC += DeviceFramework/HardwareSerial.c
SRC += DeviceFramework/SwitchController.c
SRC += DeviceFramework/PushButtons.c
SRC += DeviceFramework/SwitchButtons.c
SRC += PokemonSwShLibraries/CodeEntry.c
else
LD_FLAGS += obj/obj-$(MCU)/CRC32.o
LD_FLAGS += obj/obj-$(MCU)/uart.o
LD_FLAGS += obj/obj-$(MCU)/HardwareUSB.o
LD_FLAGS += obj/obj-$(MCU)/HardwareSerial.o
LD_FLAGS += obj/obj-$(MCU)/SwitchController.o
LD_FLAGS += obj/obj-$(MCU)/PushButtons.o
LD_FLAGS += obj/obj-$(MCU)/SwitchButtons.o
LD_FLAGS += obj/obj-$(MCU)/CodeEntry.o
endif

#   Pokemon Sword/Shield
SRC += CommonPokemon/PokemonSettings.c
ifneq ("$(wildcard PokemonSwShLibraries/PokemonRoutines.c)","")
SRC += PokemonSwShLibraries/PokemonRoutines.c
else
LD_FLAGS += obj/obj-$(MCU)/PokemonRoutines.o
endif
ifneq ("$(wildcard PokemonSwShPrograms/$(TARGET)_Core.c)","")
SRC += PokemonSwShPrograms/$(TARGET)_Core.c
else ifneq ("$(wildcard obj/obj-$(MCU)/$(TARGET)_Core.o)","")
LD_FLAGS += obj/obj-$(MCU)/$(TARGET)_Core.o
endif


#   Must go at the end or it blows up memory if floating-point is used.
LD_FLAGS += -lm


# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
