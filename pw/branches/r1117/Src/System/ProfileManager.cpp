#include "stdafx.h"
#include "ProfileManager.h"

#include "FileSystem/FileUtils.h"
#include "FileSystem/FilePath.h"
#include "TimeUtils.h"
#include "Stream.h"
#undef _interface

#if defined( NV_WIN_PLATFORM )
	#include <shlobj.h>
#endif

#include <System/StrProc.h>
#include <System/ported/cwfn.h>

#include <time.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NProfile {

static string g_productName;
static string g_commonFolder;
static string g_playerFolder;
static wstring g_currentPlayer;

#if defined( NV_WIN_PLATFORM )

	static const string &GetCommonAppdataFolder()
	{
		static string appFolder;

		TCHAR buffer[MAX_PATH];
		HRESULT hResult = ::SHGetFolderPath( 0, CSIDL_COMMON_APPDATA, 0, SHGFP_TYPE_CURRENT, buffer );

		if ( hResult != S_OK )
			return NFile::GetBaseDir();

		string appPath( buffer );	// All Users\Application Data
		NStr::TrimBoth( appPath, " \\" );

		// g_productName - not changing from version to version ( GM, patch, addon )
		appFolder = NFile::Combine( NFile::Combine( appPath, "My Games" ), g_productName );
		NFile::AppendSlash( &appFolder );

		return appFolder;
	}

	static const string &GetUserFolder()
	{
		static string userFolder;

		TCHAR buffer[MAX_PATH];
		HRESULT hResult = ::SHGetFolderPath( 0, CSIDL_PERSONAL, 0, SHGFP_TYPE_CURRENT, buffer );

		if ( hResult != S_OK )
			return NFile::GetBaseDir();

		string personalPath( buffer );	// My Documents
		NStr::TrimBoth( personalPath, " \\" );

		// g_productName - not changing from version to version ( GM, patch, addon )
		userFolder = NFile::Combine( NFile::Combine( personalPath, "My Games" ), g_productName );
		NFile::AppendSlash( &userFolder );

		return userFolder;
	}

#else

	static const string & GetCommonAppdataFolder()
	{
		static string app_folder;

		if ( app_folder.empty() ) {

			// g_productName - not changing from version to version ( GM, patch, addon )
			app_folder = NFile::Combine( "/usr/games", g_productName );
			NFile::AppendSlash( &app_folder );

		}

		return app_folder;
	}

	static const string & GetUserFolder()
	{
		static string user_folder;

		if ( user_folder.empty() ) {

			// g_productName - not changing from version to version ( GM, patch, addon )
			user_folder = NFile::Combine( "~/games", g_productName );
			NFile::AppendSlash( &user_folder );

		}

		return user_folder;
	}

#endif

static const string &GetPlayerFolder()
{
	static string playerFolder;
	playerFolder = NFile::Combine( GetUserFolder(), g_playerFolder );
	NFile::AppendSlash( &playerFolder );
	return playerFolder;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const string &GetSaveFolder()
{
	static string saveFolder;
	saveFolder = NFile::Combine( GetPlayerFolder(), "Saves\\" );
	return saveFolder;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const string &GetScreenshotsFolder()
{
  static string shotsFolder;
#ifdef _SHIPPING
  shotsFolder = NFile::Combine( GetUserFolder(), "Screenshots\\" );
#else
  shotsFolder = NFile::Combine( NFile::GetBinDir(), "screenshots\\" );
#endif

  return shotsFolder;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const string &GetLogsFolder()
{
  static string sFolder = GetRootLogsFolder();
 
  struct tm t;
  GetOsUtcTime(&t);

  static string sCurrentSessionFolder = NFile::Combine( sFolder, NStr::StrFmt("%d.%02d.%02d-%02d.%02d.%02d", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec) );
  return sCurrentSessionFolder;
}

const string& GetRootLogsFolder()
{
  static string sFolder;
#ifdef _SHIPPING
  sFolder = NFile::Combine( GetUserFolder(), "Session\\Logs\\" );
#else
  sFolder = NFile::Combine( NFile::GetBinDir(), "logs\\" );
#endif
  return sFolder;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const string &GetReplaysFolder()
{
  static string replaysFolder;
#ifdef _SHIPPING
  replaysFolder = NFile::Combine( GetUserFolder(), "Replays\\" );
#else
  replaysFolder = GetLogsFolder();
#endif
  return replaysFolder;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Init( const string &productName )
{
	g_productName = productName;
	g_commonFolder = NFile::Combine( NFile::GetBaseDir(), "Profiles\\" );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static wstring GetPlayerName( const string &dirName )
{
	FileStream stream( NFile::Combine( NFile::Combine( GetUserFolder(), dirName ), "player_name.txt" ), FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

	if	( stream.IsOk() )
	{
		int length = stream.GetSize();
		if ( length > 0 )
		{
			wchar_t buffer[1280];
			int len = Min( ARRAY_SIZE(buffer)-1, length / sizeof( wchar_t ) );
			stream.Read( buffer, len * sizeof( wchar_t ) );
			buffer[len] = 0;
			wstring resName;
			resName.assign( &buffer[1], Max( 0, len - 1 ) );
			return resName;
		}
	}
	return NStr::ToUnicode( dirName );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static string GetFullPathToPlayerFolder( const wstring &playerName )
{
	string root = GetUserFolder();

	if ( NFile::IsValidDirName( NStr::ToMBCS( playerName ) ) )
	{
		root = NFile::Combine( root, NStr::ToMBCS( playerName ) );
		NFile::AppendSlash( &root );
		if ( !NFile::DoesFolderExist( root ) )
			root.clear();
		return root;
	}

	for ( NFile::CFileIterator it( ( root + "*.*" ) ); !it.IsEnd(); ++it )
	{
		if ( !it.IsDirectory() || it.IsDots() )
			continue;
		if ( !( playerName.compare( GetPlayerName( it.GetFileName() ) ) ) )
		{
			root = NFile::Combine( root, it.GetFileName() );
			NFile::AppendSlash( &root );
			return root;
		}
	}

	return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AddPlayer( const wstring &playerName )
{
	if ( !GetFullPathToPlayerFolder( playerName ).empty() )
		return true;

	const string root = GetUserFolder();

	if ( NFile::IsValidDirName( NStr::ToMBCS( playerName ) ) )
	{
		string resDir = NFile::Combine( root, NStr::ToMBCS( playerName ) );
		NFile::AppendSlash( &resDir );
		
		if ( NFile::DoesFileExist( NFile::Combine( resDir, "player_name.txt" ) ) )
			return true;
		
		NFile::CreatePath( resDir );
			// should not use file SZ_PROFILE_NAME_FILE to specify profile name since directory name is already
			// used as profile name

		// write name
		{
			FileStream stream( NFile::Combine( resDir, "player_name.txt" ), FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
			WORD wUnicodeMagic = 0xFEFF;
			stream.Write( &wUnicodeMagic, 2 );
			stream.Write( playerName.data(), sizeof(wchar_t) * playerName.size() );
		}
	}
	else
	{
		for ( NFile::CFileIterator it( ( root + "*.*" ) ); !it.IsEnd(); ++it )
		{
			if ( !it.IsDirectory() || it.IsDots() )
				continue;
			if ( GetPlayerName( it.GetFileName() ) == playerName )
				return true;
		}
		
		// create dir
		string resDir;
		GUID guid;
		CoCreateGuid( &guid );
		NStr::GUID2String( &resDir, guid );
		resDir = NFile::Combine( root, resDir );
		NFile::AppendSlash( &resDir );
		NFile::CreatePath( resDir );
		
		// write name
		{
			FileStream stream( NFile::Combine( resDir, "player_name.txt" ), FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
			WORD wUnicodeMagic = 0xFEFF;
			stream.Write( &wUnicodeMagic, 2 );
			stream.Write( playerName.data(), sizeof(wchar_t) * playerName.size() );
		}
	}
	
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ChangePlayer( const wstring &playerName )
{
	g_currentPlayer = playerName;

	if ( NFile::IsValidDirName( NStr::ToMBCS( playerName ) ) )
	{
		g_playerFolder = NStr::ToMBCS( playerName );
		return true;
	}
	
	for ( NFile::CFileIterator it( ( GetUserFolder() + "*.*" ) ); !it.IsEnd(); ++it )
	{
		if ( !it.IsDirectory() || it.IsDots() )
			continue;
		if ( GetPlayerName( it.GetFileName() ) == playerName )
		{
			g_playerFolder = it.GetFileName();
			return true;
		}
	}
		
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DeletePlayer( const wstring &playerName )
{
	NI_ASSERT( g_currentPlayer.compare( playerName ), "Programmers: can't remove the selected profile" );

	NFile::DeleteDirectory( GetFullPathToPlayerFolder( playerName ) );
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetPlayersList( vector<wstring> *pPlayers )
{
	int playersCount = 0;
	string root = GetUserFolder();

	if ( pPlayers )
		pPlayers->resize( 0 );

	for ( NFile::CFileIterator it( ( root + "*.*" ) ); !it.IsEnd(); ++it )
	{
		if ( !it.IsDirectory() || it.IsDots() )
			continue;

		++playersCount;
		if ( pPlayers )
			pPlayers->push_back( GetPlayerName( it.GetFileName() ) );
	}

	return playersCount;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string &GetFullFolderPath( const EProfileFolder folder )
{
	switch ( folder )
	{
		case FOLDER_GLOBAL:	return g_commonFolder;
    case FOLDER_COMMON_APPDATA: return GetCommonAppdataFolder();
		case FOLDER_USER:		return GetUserFolder();
		case FOLDER_PLAYER:	return GetPlayerFolder();
    case FOLDER_SAVE:		return GetSaveFolder();
    case FOLDER_SCREENSHOTS: return GetScreenshotsFolder();
    case FOLDER_LOGS: return GetLogsFolder();
    case FOLDER_REPLAYS: return GetReplaysFolder();
	}

	static string emptyString;
	return emptyString;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetFullFilePath( const string &fileName, const EProfileFolder folder )
{
	return NFile::Combine( GetFullFolderPath( folder ), fileName );
}
}

