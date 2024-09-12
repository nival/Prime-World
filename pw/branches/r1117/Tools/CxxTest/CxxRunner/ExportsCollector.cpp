#include <windows.h>
#include <vector>
#include <string>
using namespace std;

#include "ExportsCollector.h"
#include "FileGuard.h"
#include "Log.h"
#include "ErrorFormatter.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INVALID_ADDRESS 0xFFFFFFFF
static DWORD ConvertRVAToOffset( const DWORD dwVirtualAddress, const vector<IMAGE_SECTION_HEADER> &sectionHeaders )
{
	for ( vector<IMAGE_SECTION_HEADER>::const_iterator it = sectionHeaders.begin(); it != sectionHeaders.end(); ++it )
	{
		if ( dwVirtualAddress >= it->VirtualAddress && dwVirtualAddress < it->VirtualAddress + it->Misc.VirtualSize )
			return dwVirtualAddress - it->VirtualAddress + it->PointerToRawData;
	}
	
	return INVALID_ADDRESS;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NExports
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollectFunctionsNames( vector<string> *pFunctionsNames, const char *szDllFile )
{
	if ( !pFunctionsNames )
		return false;

	NHelpers::CFileGuard file( szDllFile, false );
	if ( !file.IsValid() )
	{
		log( LEVEL_CRITICAL ) << "Cannot open file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}

	IMAGE_DOS_HEADER imageDosHeader;
	if ( !file.Read( &imageDosHeader ) )
	{
		log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}

	if ( imageDosHeader.e_magic != IMAGE_DOS_SIGNATURE )
	{
		log( LEVEL_CRITICAL ) << "\"" << szDllFile << "\" is not valid library file (invalid DOS signature)" << endl;
		return false;
	}

	IMAGE_NT_HEADERS32 imageNTHeader;
	if ( !file.Seek( imageDosHeader.e_lfanew ) || !file.Read( &imageNTHeader ) )
	{
		log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}

	if ( imageNTHeader.Signature != IMAGE_NT_SIGNATURE )
	{
		log( LEVEL_CRITICAL ) << "\"" << szDllFile << "\" is not valid library file (invalid PE signature)" << endl;
		return false;
	}
		
	vector<IMAGE_SECTION_HEADER> sectionHeaders;
	for ( int i = 0; i < imageNTHeader.FileHeader.NumberOfSections; ++i )
	{
		IMAGE_SECTION_HEADER sectionHeader;
		if ( !file.Read( &sectionHeader ) )
		{
			log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
			return false;
		}
		sectionHeaders.push_back( sectionHeader );
	}
	
	const DWORD dwExportTable = ConvertRVAToOffset( imageNTHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, sectionHeaders );
	if ( dwExportTable == INVALID_ADDRESS )
	{
		log( LEVEL_MESSAGE ) << "Export table not found in file \"" << szDllFile << "\"" << endl;
		return true;
	}
		
	IMAGE_EXPORT_DIRECTORY exportDirectory;
	if ( !file.Seek( dwExportTable ) || !file.Read( &exportDirectory ) )
	{
		log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}
		
	if ( exportDirectory.NumberOfNames == 0 )
	{
		log( LEVEL_MESSAGE ) << "Symbolic exports not found in file \"" << szDllFile << "\"" << endl;
		return true;
	}
		
	const DWORD dwNamesOffset = ConvertRVAToOffset( exportDirectory.AddressOfNames, sectionHeaders );
	if ( dwNamesOffset == INVALID_ADDRESS )
	{
		log( LEVEL_CRITICAL ) << "Invalid pointer to export functions names found in file \"" << szDllFile << "\"" << endl;
		return false;
	}
		
	if ( !file.Seek( dwNamesOffset ) )
	{
		log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}

	vector<int> addresses;
	addresses.resize( exportDirectory.NumberOfNames );
	if ( !file.Read( &(*(addresses.begin())), sizeof( int ) * exportDirectory.NumberOfNames ) )
	{
		log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
		return false;
	}

	for ( vector<int>::const_iterator it = addresses.begin(); it != addresses.end(); ++it )
	{
		if ( !file.Seek( ConvertRVAToOffset( *it, sectionHeaders ) ) )
		{
			log( LEVEL_CRITICAL ) << "Cannot read from file \"" << szDllFile << "\". " << NHelpers::GetLastError() << endl;
			return false;
		}

		string szFunctionName;
		if ( !file.ReadString( &szFunctionName ) )
		{
			log( LEVEL_CRITICAL ) << "Cannot read from file \"" << "\". " << NHelpers::GetLastError() << endl;
			return false;
		}

		pFunctionsNames->push_back( szFunctionName );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}