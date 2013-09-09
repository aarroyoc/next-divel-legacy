/* NextDivel Memory*/

/* NextDivel Memory functions */
// Copy len bytes from src to dest.
#include "ND_Memory.h"
extern uint32_t end; //In the Linker Script 
uint32_t placement_address=(uint32_t)&end;

void ND_Memory_Memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
    const uint8_t *sp = (const uint8_t *)src;
    uint8_t *dp = (uint8_t *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void ND_Memory_Memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
//Basic function for memory management in NextDivel
uint32_t ND_Memory_AllocComplete(uint32_t sz, int align, uint32_t* phys)
{
if (align == 1 && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys)
  {
    *phys = placement_address;
  }
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
}
/*
 This function reserves memory for basic tasks ans is the recomended function for apps
*/
uint32_t ND_Memory_Alloc(uint32_t size)
{
	return ND_Memory_AllocComplete(size,0,0);
}
