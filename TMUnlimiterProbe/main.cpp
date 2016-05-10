#include "StdInc.h"

void InstallHooks ()
{
    dword dwOldProtect;
    VirtualProtect ( Address::Inst.CodeBase, Address::Inst.CodeSize, PAGE_EXECUTE_READWRITE, &dwOldProtect );

    static Hooks::Editor::BlockMixHooks blockMixHooks;
    static Hooks::Editor::EnvironmentMixHooks envMixHooks;
    blockMixHooks.Init ();
    envMixHooks.Init ();

    VirtualProtect ( Address::Inst.CodeBase, Address::Inst.CodeSize, dwOldProtect, &dwOldProtect );
}

BOOL __stdcall DllMain ( HINSTANCE hInstance, DWORD dwReason, void* pReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
            InstallHooks ();
			break;
		}
	}
	return TRUE;
}
