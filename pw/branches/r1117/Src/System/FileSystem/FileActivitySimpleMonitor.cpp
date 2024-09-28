#include "stdafx.h"
#include "FileActivitySimpleMonitor.h"
#include "System/LogFileName.h"
#include "FileUtils.h"

#if defined( NV_WIN_PLATFORM )

	FileActivitySimpleMonitor::FileActivitySimpleMonitor(): output( INVALID_HANDLE_VALUE )
	{}

	FileActivitySimpleMonitor::FileActivitySimpleMonitor( const char * logSuffix ): output( INVALID_HANDLE_VALUE )
	{
		if ( logSuffix ) {

			outputFilename = NDebug::GenerateDebugFileName( logSuffix, "txt" );
			NStr::TrimLeft( outputFilename, "/\\" );
			output = (HANDLE)NFile::CreateFileWithDir( outputFilename.c_str() );

		}
	}

	FileActivitySimpleMonitor::~FileActivitySimpleMonitor()
	{
		if ( output != INVALID_HANDLE_VALUE )
			CloseHandle( output );

		output = INVALID_HANDLE_VALUE;
	}

	void FileActivitySimpleMonitor::WriteEntry( const char * operation, NHPTimer::FTime timeSpent, unsigned size, const string & fileName )
	{
		threading::MutexLock lock( mutex );

		char buf[1024];
		sprintf_s( buf, "%-12s %-8.3f %-10u %s\r\n", operation, timeSpent, size, fileName.c_str() );

		if ( output != INVALID_HANDLE_VALUE ) {

			DWORD written = 0;
			WriteFile( output, buf, strlen( buf ), (DWORD*)&written, 0 );

		}

		OutputDebugString( "<FileSystem> " );
		OutputDebugString( buf );
	}

#elif defined( NV_LINUX_PLATFORM )

	#include <System/ported/cwfn.h>

	namespace filesystem {

		bool is_directory( char const * path )
		{
			assert( NULL != path );

			struct stat file = { 0 };
			return 0 == stat( path, &file ) && S_ISDIR( file.st_mode );
		}

		bool exists( char const * path )
		{
			assert( NULL != path );

			struct stat file = { 0 };
			return 0 == stat( path, &file );
		}

		bool create_full_path( char const * path )
		{
			assert( NULL != path );

			if ( '/' != *path )
				return false;

			char created_path[ PATH_MAX + 1 ];
			memset( &created_path, 0, sizeof( created_path ) );

			size_t index = 0;
			char c;

			while ( c = *path++ ) {

				if ( ( '/' == c || '\\' == c ) && index ) {

					if ( filesystem::exists( created_path ) ) {

						if ( filesystem::is_directory( created_path ) == false )
							return false;

					} else {

						if ( mkdir( created_path, S_IRWXU | S_IRWXG | S_IRWXO ) )
							return false;

					}

				}

				created_path[ index++ ] = c;

			}

			return true;
		}

	}

	FileActivitySimpleMonitor::FileActivitySimpleMonitor()
	{}

	FileActivitySimpleMonitor::FileActivitySimpleMonitor( const char * logSuffix )
	{
		assert( NULL != logSuffix );

		if ( logSuffix ) {

			outputFilename = NDebug::GenerateDebugFileName( logSuffix, "txt" );
			NStr::TrimLeft( outputFilename, "/\\" );

			filesystem::create_full_path( outputFilename.c_str() );
			m_output.open( outputFilename.c_str() );

		}
	}

	FileActivitySimpleMonitor::~FileActivitySimpleMonitor()
	{}

	void FileActivitySimpleMonitor::WriteEntry( const char * operation, NHPTimer::FTime timeSpent, unsigned size, const string & fileName )
	{
		threading::MutexLock lock( mutex );

		char buf[1024];
		std::snprintf( buf, sizeof( buf ), "%-12s %-8.3f %-10u %s\r\n", operation, timeSpent, size, fileName.c_str() );

		if ( m_output.is_open() ) {

			DWORD written = 0;
			m_output.write( buf, strlen( buf ) );

		}

		OutputDebugString( "<FileSystem> " );
		OutputDebugString( buf );
	}

#endif

void FileActivitySimpleMonitor::OnGetDirectories( const string & root, NHPTimer::FTime timeSpent )
{
  WriteEntry( "getdirs", timeSpent, 0, root );
}

void FileActivitySimpleMonitor::OnGetFiles( const string & root, NHPTimer::FTime timeSpent )
{
  WriteEntry( "getfiles", timeSpent, 0, root );
}

void FileActivitySimpleMonitor::OnGetFileInfo( const string & fileName, NHPTimer::FTime timeSpent )
{
  WriteEntry( "getinfo", timeSpent, 0, fileName );
}

void FileActivitySimpleMonitor::OnOpenFile( const string & fileName, NHPTimer::FTime timeSpent, unsigned size )
{
  WriteEntry( "openfile", timeSpent, size, fileName );
}

