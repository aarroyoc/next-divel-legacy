#ifndef ND_MEMORY_H
#define ND_MEMORY_H
#include "ND_LanguageC.h"
void ND_Memory_Memset(uint8_t *dest, uint8_t val, uint32_t len);
void ND_Memory_Memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);
uint32_t ND_Memory_AllocComplete(uint32_t sz, int align, uint32_t* physis );
uint32_t ND_Memory_Alloc(uint32_t size);
#endif
