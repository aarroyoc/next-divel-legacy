 /* Check if the compiler thinks if we are targeting the wrong operating system. */
#ifndef NEXT_DIVEL
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* Headers for all system functions */
#include "NextDivel.h"
 
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void NextKernel_Main()
{
	ND_Versions_Startup();
}
