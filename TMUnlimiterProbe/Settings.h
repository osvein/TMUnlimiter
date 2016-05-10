#pragma once

#define INI_FILENAME "TMUnlimiter.ini"
#define INI_TRACKSIZES "NewTrackSizes"

class Settings
{
public:
	static std::string				GetString			( const char* pszSection, const char* pszKey );
	static int						GetInt				( const char* pszSection, const char* pszKey, int iDefault );

private:
	static const char*				GetIniPath			();
};
