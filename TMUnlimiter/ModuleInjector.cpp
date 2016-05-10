#include "StdInc.h"

bool ModuleInjector::Inject ( HANDLE hProcess, char* pszFileName )
{
	HMODULE hKernel32 = GetModuleHandle ( "kernel32.dll" );
	void* pLoadLibrary = GetProcAddress ( hKernel32, "LoadLibraryA" );
	uint uiLoadLibraryRVA = (uint)pLoadLibrary - (uint)hKernel32;

	byte* pRemoteKernel32 = FindRemoteModule ( GetProcessId ( hProcess ), "kernel32.dll" );
	if ( !pRemoteKernel32 )
		return false;

	byte* pRemoteLoadLibrary = pRemoteKernel32 + uiLoadLibraryRVA;

	byte* pRemoteMem = (byte *)VirtualAllocEx ( hProcess, NULL, sizeof(m_LoaderCode), MEM_COMMIT, PAGE_EXECUTE );
	if ( !pRemoteMem )
		return false;

	byte* pInstr = m_LoaderCode;

	// push szModuleName
	*pInstr = 0x68;
	pInstr++;
	*(dword *)pInstr = (dword)pRemoteMem + CODE_SIZE;
	pInstr += 4;

	// call LoadLibraryA
	*pInstr = 0xE8;
	pInstr++;
	*(dword *)pInstr = pRemoteLoadLibrary - (pInstr + 4 - m_LoaderCode + pRemoteMem);
	pInstr += 4;

	// retn 4
	*pInstr = 0xC2;
	pInstr++;
	*(word *)pInstr = 0x0004;
	pInstr += 2;

	strncpy_s ( (char *)&m_LoaderCode[CODE_SIZE], sizeof(m_LoaderCode) - CODE_SIZE, pszFileName, _TRUNCATE );
	
	WriteProcessMemory ( hProcess, pRemoteMem, m_LoaderCode, sizeof(m_LoaderCode), NULL );
	
	dword dwThreadId = 0;
	HANDLE hRemoteThread = CreateRemoteThread ( hProcess, NULL, 0, (PTHREAD_START_ROUTINE)pRemoteMem,
		NULL, 0, &dwThreadId );
	if ( !hRemoteThread )
	{
		VirtualFreeEx ( hProcess, pRemoteMem, 0, MEM_RELEASE );
		return false;
	}

	WaitForSingleObject ( hRemoteThread, INFINITE );
	VirtualFreeEx ( hProcess, pRemoteMem, 0, MEM_RELEASE );
	CloseHandle ( hRemoteThread );
	return true;
}

byte* ModuleInjector::FindRemoteModule ( dword dwProcessID, char* pszModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPMODULE, dwProcessID );
	if ( hSnapshot == INVALID_HANDLE_VALUE )
		return NULL;

	MODULEENTRY32 moduleEntry;
	moduleEntry.dwSize = sizeof(moduleEntry);
	if ( !Module32First ( hSnapshot, &moduleEntry ) )
	{
		CloseHandle ( hSnapshot );
		return NULL;
	}

	do
	{
		if ( !stricmp ( moduleEntry.szModule, pszModuleName ) )
		{
			CloseHandle ( hSnapshot );
			return moduleEntry.modBaseAddr;
		}
	} while ( Module32Next ( hSnapshot, &moduleEntry ) );
	
	CloseHandle ( hSnapshot );
	return NULL;
}
