#include "NextKernel_ISR.h"
#include "ND_Screen.h"
void NextKernel_ISR_Handler(NextKernel_ISR_Registers regs)
{
   ND_Screen_WriteString("recieved interrupt: ");
   if(regs.int_no)
   {

   }
   /*monitor_write_dec(regs.int_no);
   monitor_put('\n');*/
} 
