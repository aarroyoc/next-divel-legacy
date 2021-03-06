/* Hardware text mode color constants. */
#include "ND_Terminal.h"
 
uint8_t ND_Terminal_MakeColor(enum ND_VGA_Color fg, enum ND_VGA_Color bg)
{
	return fg | bg << 4;
}
 
uint16_t ND_Terminal_MakeVGAEntry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
size_t ND_Terminal_Strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void ND_Terminal_Initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = ND_Terminal_MakeColor(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = ND_Terminal_MakeVGAEntry(' ', terminal_color);
		}
	}
}
 
void ND_Terminal_SetColor(uint8_t color)
{
	terminal_color = color;
}
 
void ND_Terminal_PutEntryAt(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = ND_Terminal_MakeVGAEntry(c, color);
}
 
void ND_Terminal_PutChar(char c)
{
	ND_Terminal_PutEntryAt(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row = 0;
		}
	}
}
 
void ND_Terminal_WriteString(const char* data)
{
	size_t datalen = ND_Terminal_Strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		ND_Terminal_PutChar(data[i]);
}
