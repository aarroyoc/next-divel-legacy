#ifndef NEXTKERNEL_ISR_H
#define NEXTKERNEL_ISR_H
#include "ND_LanguageC.h"
typedef struct NextKernel_ISR_Registers
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} NextKernel_ISR_Registers; 
#endif
