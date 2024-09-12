#pragma once

#include <windows.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NHelpers
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLibraryGuard
{
	HMODULE hLibrary;
public:
	CLibraryGuard() : hLibrary( 0 ) {}
	CLibraryGuard( const char *szLibName )
	{
		Create( szLibName );
	}
	
	~CLibraryGuard()
	{
		Clear();
	}

	bool Create( const char *szLibName )
	{
		hLibrary = LoadLibraryEx( szLibName, 0, 0 );
		return IsValid();
	}

	void Clear()
	{
		if ( IsValid() )
		{
			FreeLibrary( hLibrary );
			hLibrary = 0;
		}
	}

	FARPROC GetProcAddress( const char *szProcName )
	{
		if ( !IsValid() )
			return 0;

		return ::GetProcAddress( hLibrary, szProcName );
	}

	const bool IsValid() const { return hLibrary != 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}