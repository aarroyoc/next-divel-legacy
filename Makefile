#Makefile for build NextDivel OS
#Compiler
CC = gcc
CC64 = gcc -m64
NASM = nasm
LD = ld
LD64 = ld -melf_86_64
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
BASEFLAGS   := -O2 -fpic -nostdlib
#BASEFLAGS   += -pedantic -pedantic-errors
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
WARNFLAGS   += -Wno-unused-parameter
ASFLAGS     := -felf
ASFLAGS64   := -felf64
CFLAGS      := $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) $(NEXTFLAGS) #$(WARNFLAGS)
CFLAGS      += -std=gnu99
#Build
all: nextdivel.img
all64: nextdivel64.img

nextdivel.elf: $(OBJS) link.ld
	$(LD) $(OBJS) -Tlink.ld -o $@
nextdivel64.elf: $(OBJS) link.ld
	$(LD) $(OBJS) -Tlink.ld -o $@

nextdivel.img: nextdivel.elf
	$(OBJCOPY) nextdivel.elf -O binary nextdivel.img
nextdivel64.img: nextdivel64.elf
	$(OBJCOPY) nextdivel64.elf -O binary nextdivel64.img
 
clean:
	$(RM) -f $(OBJS) nextdivel.elf nextdivel.img
clean64:
	$(RM) -f $(OBJS) nextdivel64.elf nextdivel64.img
dist-clean: clean
	$(RM) -f *.d
test:
	qemu-system-i386 -kernel nextdivel.elf
test64:
	qemu-system-x86_64 -kernel nextdivel64.elf
iso:
	mkdir -p isodir
	mkdir -p isodir/boot
	mkdir -p isodir/nextfs
	gcc -o tools/make_initrd tools/make_initrd.c
	tools/make_initrd README.md README.md
	cp nextdivel.elf isodir/boot/nextdivel.elf
	cp nextdivel64.elf isodir/boot/nextdivel64.elf
	cp initrd.img isodir/nextfs/nextfs.img
	mkdir -p isodir/boot/grub
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o nextdivel.iso isodir
testiso: nextdivel.iso
	qemu-system-i386 -cdrom nextdivel.iso
# C.
%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@
 
# AS.
%.o: %.asm Makefile
	$(NASM) $(ASFLAGS) $< -o $@
