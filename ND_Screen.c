#include "ND_Screen.h"
#include "ND_Bus.h"
// The VGA framebuffer starts at 0xB8000.
uint16_t *video_memory = (uint16_t *)0xB8000;
// Stores the cursor position.
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint8_t backColour = 0;
uint8_t foreColour = 15;

static void ND_Screen_MoveCursor()
{
   // The screen is 80 characters wide...
   uint16_t cursorLocation = cursor_y * 80 + cursor_x;
   ND_Bus_outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   ND_Bus_outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   ND_Bus_outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   ND_Bus_outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}
static void ND_Screen_Scroll()
{

   // Get a space character with the default colour attributes.
   uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(cursor_y >= 25)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = 24;
   }
} 
// Writes a single character out to the screen.
void ND_Screen_Put(char c)
{

   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   uint16_t attribute = attributeByte << 8;
   uint16_t *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.
   ND_Screen_Scroll();
   // Move the hardware cursor.
   ND_Screen_MoveCursor();
}
// Clears the screen, by copying lots of spaces to the framebuffer.
void ND_Screen_Clear()
{
   // Make an attribute byte for the default colours
   uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   ND_Screen_MoveCursor();
}
// Outputs a null-terminated ASCII string to the monitor.
void ND_Screen_WriteString(const char *c)
{
   int i = 0;
   while (c[i])
   {
       ND_Screen_Put(c[i++]);
   }
}
void ND_Screen_SetColor(uint8_t background, uint8_t foreground)
{
	backColour=background; //Default is 0 - Black
	foreColour=foreground; //Default to 15 - White
}
void ND_Screen_ResetColor()
{
	backColour=0;
	foreColour=15;
}
void ND_Screen_WriteHex(uint32_t n)
{
    int32_t tmp;

    ND_Screen_WriteString("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            ND_Screen_Put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            ND_Screen_Put( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        ND_Screen_Put (tmp-0xA+'a');
    }
    else
    {
        ND_Screen_Put (tmp+'0');
    }
}
void ND_Screen_WriteDec(uint32_t n)
{
   if (n == 0)
    {
        ND_Screen_Put('0');
        return;
    }

    int32_t acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    ND_Screen_WriteString(c2);
}
