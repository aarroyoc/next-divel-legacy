#include "ND_Error.h"
#include "ND_Screen.h"

void ND_Error_WriteString(const char* msg)
{
	ND_Screen_SetColor(0,2);
	ND_Screen_WriteString(msg);
	ND_Screen_ResetColor();
}
