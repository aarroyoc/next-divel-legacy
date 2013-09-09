//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//

#include "ND_LanguageC.h"
#include "NextKernel_ISR.h"
#include "ND_Screen.h"
#include "ND_Bus.h"

isr_t interrupt_handlers[256];

void NextKernel_ISR_RegisterInterruptHandler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

// This gets called from our ASM interrupt handler stub.
void NextKernel_ISR_Handler(registers_t regs)
{
    ND_Screen_WriteString("received interrupt");

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

// This gets called from our ASM interrupt handler stub.
void NextKernel_IRQ_Handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        ND_Bus_outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    ND_Bus_outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

}
