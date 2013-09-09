// timer.c -- Initialises the PIT, and handles clock updates.
//            Written for JamesM's kernel development tutorials.

#include "ND_Timer.h"
#include "NextKernel_ISR.h"
#include "ND_Screen.h"
#include "ND_Bus.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;
    ND_Screen_WriteString("Tick: ");
}

void ND_Timer_Init(uint32_t frequency)
{
    // Firstly, register our timer callback.
    NextKernel_ISR_RegisterInterruptHandler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / frequency;

    // Send the command byte.
    ND_Bus_outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    ND_Bus_outb(0x40, l);
    ND_Bus_outb(0x40, h);
}
