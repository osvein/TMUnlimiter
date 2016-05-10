#include "StdInc.h"

BOOL __stdcall DllMain ( HINSTANCE hInstance, DWORD dwReason, void* pReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			Hooks::Install ();
			break;
		}
	}
	return TRUE;
}
