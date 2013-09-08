#include "ND_Bus.h"
/*
 ASM _cdecl convention
 C:
 d = func(a,b,c);
 ASM:
 push [c]
 push [b]
 push [a]
 call func
 mov [d], eax
*/
// Write a byte out to the specified port.
void ND_Bus_outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t ND_Bus_inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t ND_Bus_inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
} 
