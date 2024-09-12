#pragma once
#include "FileSystem.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined( NV_WIN_PLATFORM )
  #define BAD_FILE_VALUE      INVALID_HANDLE_VALUE
  #define FILE_HANDLE         HANDLE
#elif defined( NV_LINUX_PLATFORM )
  #define BAD_FILE_VALUE      -1
  #define FILE_HANDLE         int
#endif

class FileStream : public Stream, public CObjectBase
{
private:

	OBJECT_METHODS( 0x1E4A8B44, FileStream );

protected:

	char        *pBuffer;
	int         fileSize;
	int         offset;

	FILE_HANDLE hFile;
	FILE_HANDLE hMapping;

	FileStream(): pBuffer( 0 ), fileSize( 0 ), offset( 0 ), hFile( BAD_FILE_VALUE ), hMapping( BAD_FILE_VALUE )
	{}

	void MapFile();
	void UnMapFile();

	void SeekInternal( const int offset );
	void SetSizeInternal( const int size );

	int ReadInternal( void *pData, const int length );
	int WriteInternal( const void *pData, const int length );

public:

	FileStream( const string &fileName, EFileAccess access, EFileOpen options, bool bAutoMap = true);

	~FileStream()
	{
		Close();
	}

	int GetSize() const
	{
		return fileSize;
	}

	int GetPosition() const
	{
		return offset;
	}

	const char *GetBuffer() const
	{
		return pBuffer;
	}

	void Reserve( int _size )
	{
		SetSize( _size );
		Seek( 0, SEEKORIGIN_BEGIN );
	}

	void Close();

};

