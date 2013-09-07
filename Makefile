#Makefile for build NextDivel OS
#Compiler
CC = gcc
NASM = nasm
LD = ld
OBJCOPY = objcopy
#source files
SOURCES_ASM := $(wildcard *.asm)
SOURCES_C   := $(wildcard *.c)
 
# object files
OBJS        := $(patsubst %.asm,%.o,$(SOURCES_ASM))
OBJS        += $(patsubst %.c,%.o,$(SOURCES_C))
 
# Build flags
DEPENDFLAGS := -MD -MP
NEXTFLAGS   := -DNEXT_DIVEL
INCLUDES    := -I include
BASEFLAGS   := -O2 -fpic -pedantic -pedantic-errors -nostdlib
BASEFLAGS   += -nostartfiles -ffreestanding -nodefaultlibs
BASEFLAGS   += -fno-builtin -fomit-frame-pointer
WARNFLAGS   := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings
WARNFLAGS   += -Wredundant-decls -Winline
WARNFLAGS   += -Wno-attributes -Wno-deprecated-declarations
WARNFLAGS   += -Wno-div-by-zero -Wno-endif-labels -Wfloat-equal
WARNFLAGS   += -Wformat=2 -Wno-format-extra-args -Winit-self
WARNFLAGS   += -Winvalid-pch -Wmissing-format-attribute
WARNFLAGS   += -Wmissing-include-dirs -Wno-multichar
WARNFLAGS   += -Wredundant-decls -Wshadow
WARNFLAGS   += -Wno-sign-compare -Wswitch -Wsystem-headers -Wundef
WARNFLAGS   += -Wno-pragmas -Wno-unused-but-set-parameter
WARNFLAGS   += -Wno-unused-but-set-variable -Wno-unused-result
WARNFLAGS   += -Wwrite-strings -Wdisabled-optimization -Wpointer-arith
WARNFLAGS   += -Werror
ASFLAGS     := -felf
CFLAGS      := $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(WARNFLAGS) $(NEXTFLAGS)
CFLAGS      += -std=gnu99
#Build
all: nextdivel.img
nextdivel.elf: $(OBJS) link.ld
	$(LD) $(OBJS) -Tlink.ld -o $@
 
nextdivel.img: nextdivel.elf
	$(OBJCOPY) nextdivel.elf -O binary nextdivel.img
 
clean:
	$(RM) -f $(OBJS) nextdivel.elf nextdivel.img
 
dist-clean: clean
	$(RM) -f *.d
test:
	qemu-system-i386 -kernel nextdivel.elf
# C.
%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@
 
# AS.
%.o: %.asm Makefile
	$(NASM) $(ASFLAGS) $< -o $@