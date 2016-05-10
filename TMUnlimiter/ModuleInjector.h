#pragma once

class ModuleInjector
{
public:
	bool					Inject				( HANDLE hProcess, char* pszFileName );

private:
	enum { CODE_SIZE = 0xD };

	byte*					FindRemoteModule	( dword dwProcessID, char* pszModuleName );

	byte					m_LoaderCode[0x400];
};
