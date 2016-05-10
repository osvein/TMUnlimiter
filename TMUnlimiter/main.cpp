#include "StdInc.h"


int __stdcall WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pszCmdLine, int iCmdShow )
{
	STARTUPINFO startInfo;
	PROCESS_INFORMATION procInfo;
	memset ( &startInfo, 0, sizeof(startInfo) );

	if ( !CreateProcess ( "TmForever.exe", NULL, NULL, NULL, false, 0, NULL, NULL, &startInfo, &procInfo ) )
	{
		MessageBox ( NULL, "Failed to find/start TmForever.exe", "", MB_ICONEXCLAMATION );
		return 0;
	}

	WaitForInputIdle ( procInfo.hProcess, INFINITE );

	ModuleInjector injector;
	if ( !injector.Inject ( procInfo.hProcess, "TMUnlimiterProbe.dll" ) )
	{
		MessageBox ( NULL, "Failed to inject TMUnlimiterProbe.dll", "", MB_ICONEXCLAMATION );
	}

	CloseHandle ( procInfo.hThread );
	CloseHandle ( procInfo.hProcess );
	return 0;
}
