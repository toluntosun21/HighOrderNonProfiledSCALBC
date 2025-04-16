# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
#
# Makefile for ChipWhisperer SimpleSerial-AES Program
#
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension).
# This is the name of the compiled .hex file.
TARGET = simpleserial-dilithium
CRYPTO_TARGET = NONE


# List C source files here.
# Header files (.h) are automatically pulled in.
SRC += simpleserial-dilithium.c

# -----------------------------------------------------------------------------
SRC += sign.c
SRC += masked_sign.c
SRC += masking_interface.c
SRC += ntt.c
SRC += poly.c
SRC += polyvec.c
SRC += masked_polyvec_operations.c
SRC += reduce.c

SRC += fips202.c
SRC += symmetric-shake.c

SRC += randombytes.c


VPATH += src
VPATH += ../common


EXTRAINCDIRS += src
EXTRAINCDIRS += ../common

ifeq ($(REDUCTION),CWLITEARM)
  CDEFS += -DSTM32F3XX
endif

CDEFS += -DN_SHARES=$(NSHARES)



#Add simpleserial project to build
include $(FIRMWAREPATH)/simpleserial/Makefile.simpleserial

include $(FIRMWAREPATH)/Makefile.inc

