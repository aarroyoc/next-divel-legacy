#include "ND_Terminal2.h"

unsigned char attrib = 0xF; // White text on black background
unsigned short *video = (unsigned short *)0xB8000;

void ND_Terminal2_Clear()
{
	int i = 0;
 
	for (i = 0; i < 80 * 25; i++)
		video[i] = (attrib << 8) | 0;
}
void ND_Terminal2_WriteString(const char* msg)
{
	int i = 0;
 
	for (i = 0; msg[i] != '\0'; i++)
		video[i] = (attrib << 8) | msg[i];
}
