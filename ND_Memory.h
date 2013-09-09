#ifndef ND_MEMORY_H
#define ND_MEMORY_H
#include "ND_LanguageC.h"
void memset(uint8_t *dest, uint8_t val, uint32_t len);
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);
#endif
