#ifndef NEXTKERNEL_GDT_H
#define NEXTKERNEL_GDT_H
#include "ND_LanguageC.h"

/* GDT Table */
typedef struct NextKernel_GDT_Entry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} NextKernel_GDT_Entry;
typedef struct NextKernel_GDT_Ptr
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} NextKernel_GDT_Ptr;
void NextKernel_GDT_Init();
/* IDT Table */
typedef struct NextKernel_IDT_Entry
{
   uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} NextKernel_IDT_Entry;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
typedef struct NextKernel_IDT_Ptr
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} NextKernel_IDT_Ptr;

//ASM Handlers
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
#endif
