#include "ND_Versions.h"
#include "ND_Terminal2.h"
#include "ND_Screen.h"

bool ND_Versions_CompatibilityCheck(int major, int minor, int patch)
{
	if(major<=ND_VERSIONS_MAJOR)
	{
		if(minor<=ND_VERSIONS_MINOR)
		{
			if(patch<=ND_VERSIONS_PATCH)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void ND_Versions_Startup()
{
	/*ND_Terminal_Initialize();
	ND_Terminal_WriteString("NextDivel 0.0.1 (C) Adrian Arroyo Calle 2013");*/
	/*ND_Terminal2_Clear();
	ND_Terminal2_WriteString("NextDivel 0.0.1 (C) Adrian Arroyo Calle 2013");*/
	ND_Screen_Clear();
	ND_Screen_WriteString("NextDivel 0.0.1\n(C) Adrian Arroyo Calle 2013\n");
}
