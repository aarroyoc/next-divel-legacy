 /* Check if the compiler thinks if we are targeting the wrong operating system. */
#ifndef NEXT_DIVEL
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
/* Headers for description tables */
#include "NextKernel_GDT.h"
/* Headers for all system functions */
#include "NextDivel.h"
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
int NextKernel_Main(/*struct multiboot *mboot_ptr*/)
{
	NextKernel_GDT_Init();
	ND_Versions_Startup();
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
	
	asm volatile ("sti");
	ND_Timer_Init(50); //50 mhz

	return 0;
}
