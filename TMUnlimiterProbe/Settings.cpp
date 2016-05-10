#include "StdInc.h"

std::string Settings::GetString ( const char* pszSection, const char* pszKey )
{
	static char szBuffer[0x400];
	GetPrivateProfileString ( pszSection, pszKey, "", szBuffer, sizeof(szBuffer), GetIniPath () );
	return std::regex_replace ( std::string ( szBuffer ), std::regex ( "\\s*;.*" ), std::string ( "" ) );
}

int Settings::GetInt ( const char* pszSection, const char* pszKey, int iDefault )
{
	return GetPrivateProfileInt ( pszSection, pszKey, iDefault, GetIniPath () );
}

const char* Settings::GetIniPath ()
{
	static std::string strIniPath;
	if ( strIniPath.empty () )
	{
		char szCurrentPath[MAX_PATH];
		GetCurrentDirectory ( sizeof(szCurrentPath), szCurrentPath );

		strIniPath += szCurrentPath;
		if (strIniPath[strIniPath.size () - 1] != '\\' )
		{
			strIniPath += "\\";
		}
		strIniPath += INI_FILENAME;
	}
	return strIniPath.c_str ();
}
