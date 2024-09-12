#pragma once

#include <windows.h>
#include <string>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NHelpers
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFileGuard
{
	HANDLE hFile;
	bool createForWrite;
	CFileGuard() : hFile( INVALID_HANDLE_VALUE ) {}

public:
	CFileGuard( const char *szFileName, bool _createForWrite )
	{
		createForWrite = _createForWrite;

		hFile = CreateFile( szFileName, createForWrite ? GENERIC_WRITE | GENERIC_READ : GENERIC_READ, FILE_SHARE_READ, 0,
			createForWrite ? CREATE_ALWAYS : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
	}

	~CFileGuard()
	{
		Clear();
	}

	void Clear()
	{
		if ( IsValid() )
		{
			CloseHandle( hFile );
			hFile = INVALID_HANDLE_VALUE;
		}
	}

	bool Read( void *pBuffer, const DWORD nBytesToRead )
	{
		if ( !IsValid() )
			return false;
		
		DWORD nNumberOfBytesRead;
		if ( ReadFile( hFile, pBuffer, nBytesToRead, &nNumberOfBytesRead, 0 ) == FALSE )
			return false;

		return nBytesToRead == nNumberOfBytesRead;
	}

	bool ReadString( string *pString )
	{
		if ( !pString )
			return false;

		if ( !IsValid() )
			return false;

		char szBuffer[256] = {0};
		DWORD nNumberOfBytesRead;

		do
		{
			if ( ReadFile( hFile, szBuffer, sizeof( szBuffer ) - 1, &nNumberOfBytesRead, 0 ) == FALSE )
				return false;

			szBuffer[nNumberOfBytesRead] = 0;
			*pString += szBuffer;
		} while ( nNumberOfBytesRead == strlen( szBuffer ) && nNumberOfBytesRead == sizeof( szBuffer ) - 1 );

		return true;
	}

	template<typename T>
	bool Read( T *pData )
	{
		return Read( pData, sizeof(T) );
	}

	bool Write( const void *pBuffer, const DWORD nBytesToWrite )
	{
		if ( !IsValid() || !createForWrite )
			return false;
		
		DWORD nNumberOfBytesWritten;
		if ( WriteFile( hFile, pBuffer, nBytesToWrite, &nNumberOfBytesWritten, 0 ) == FALSE )
			return false;

		return nBytesToWrite == nNumberOfBytesWritten;
	}

	bool WriteString( const char* szString )
	{
		const size_t nLength = strlen( szString );
		if ( nLength == 0 )
			return true;

		return Write( szString, nLength );
	}

	bool Seek( const LONG nPosition )
	{
		if ( !IsValid() )
			return false;

		return SetFilePointer( hFile, nPosition, 0, FILE_BEGIN ) != INVALID_SET_FILE_POINTER;
	}
	
	bool IsValid() const { return hFile != INVALID_HANDLE_VALUE; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}