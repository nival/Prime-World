#include "stdafx.h"
#include "Utility.h"
#include "EditorFileSystem.h"
#include <vcclr.h>

#undef CreateFile

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EditorNative;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
const int BUFFER_SIZE = 64 * 1024; //64Kb to avoid allocations in Large Object Heap

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditorWriteFileStream : public Stream, public CObjectBase
{
	OBJECT_METHODS( 0x49561300, EditorWriteFileStream );

private:
  mutable char* pBuffer;
	gcroot<System::IO::Stream^> stream;
  gcroot<array<System::Byte>^> buffer;

	EditorWriteFileStream() {}

public:
	EditorWriteFileStream( gcroot<System::IO::Stream^> _stream, bool readonly = false )
		: stream( _stream ), pBuffer( NULL )
	{
		SetBroken( false );
 		SetCanRead( stream->CanRead );
		SetCanWrite( stream->CanWrite && !readonly );
		SetCanSeek( stream->CanSeek );

    buffer = gcnew array<System::Byte>( BUFFER_SIZE );
	}

	~EditorWriteFileStream()
	{
		Close();
	}

	virtual void SeekInternal( const int offset )
	{
		stream->Seek( offset, System::IO::SeekOrigin::Begin );
	}

	virtual void SetSizeInternal( const int size )
	{
		stream->SetLength( size );
	}

	virtual int ReadInternal( void *pData, const int length )
	{
    int result = 0;
    while ( result < length )
    {
      const int toRead = min( BUFFER_SIZE, length - result );
		  const int readen = stream->Read( buffer, 0, toRead );
		  pin_ptr<System::Byte> ptr = &buffer[0];
		  memcpy( (char*)pData + result, ptr, readen );
      result += readen;
      if ( readen < toRead )
      {
  			SetBroken( true );
        break;
      }
    }

		return result;
	}

	virtual int WriteInternal( const void *pData, const int length )
	{
    int result = 0;
    while( result < length )
    {
      const int toWrite = min( BUFFER_SIZE, length - result );
      pin_ptr<System::Byte> ptr = &buffer[0];
		  memcpy( ptr, (const char*)pData + result, toWrite ); 
		  stream->Write( buffer, 0, toWrite );
      result += toWrite;
    }

		if ( result != length )
		{
			SetBroken( true );
		}

		return result;
	}

	virtual int GetSize() const
	{
		return stream->Length;
	}

	virtual int GetPosition() const
	{
		return stream->Position;
	}

	virtual const char *GetBuffer() const
	{
    EditorWriteFileStream* self = const_cast<EditorWriteFileStream *>( this );

    if( pBuffer == NULL )
    {
      const int pos = GetPosition();
      const int length = self->GetSize();
      self->Seek( 0, SEEKORIGIN_BEGIN );
      
      pBuffer = new char[length];
      self->ReadInternal( pBuffer, length );
      
      if ( IsOk() )
        self->Seek( pos, SEEKORIGIN_BEGIN );
    }

    return pBuffer;
	}

	virtual void Close()
	{
		stream->Close();
    
    if( pBuffer != NULL )
    {
      delete pBuffer;
      pBuffer = NULL;
    }
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditorFileSystemImpl : public IFileSystem, public CObjectBase
{
	OBJECT_METHODS( 0x49557C40, EditorFileSystemImpl );

private:
	gcroot<libdb::IO::IFileSystem^> pFileSystem;

	EditorFileSystemImpl() {}

public:
	EditorFileSystemImpl( gcroot<libdb::IO::IFileSystem^> fileSystem )
		: pFileSystem( fileSystem )
	{
	}

	bool GetFileInfo( SFileInfo *pInfo, const string &fileName )
	{
		libdb::IO::FileInformation^ pFileInfo = pFileSystem->GetFileInfo( FromMBCS( fileName ) );
		if ( pFileInfo == nullptr || !pFileInfo->IsFileExists )
			return false;

		if ( pInfo != nullptr )
		{
			pInfo->pOwner = this;
		}

		return true;
	}

	void GetDirectories( vector<string> *pDirectories, const string &root )
	{
    array<System::String^>^ folders = pFileSystem->GetFolders( FromMBCS( root ) );

    pDirectories->clear();
    for( int i = 0; i < folders->Length; ++i )
      pDirectories->push_back( ToMBCS( folders[i] ) );
	}

	void GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive, int param /*= 0*/ )
	{
    NI_ASSERT( !recursive, "Recursive GetFiles() not supported at the moment" );

    array<System::String^>^ files = pFileSystem->GetFiles( FromMBCS( root ), FromMBCS( mask ) );
  
    pFiles->clear();
    for( int i = 0; i < files->Length; ++i )
      pFiles->push_back( ToMBCS( files[i] ) );
	}

	Stream* OpenFile( const string &fileName, EFileAccess access, EFileOpen options )
	{
		if ( access == FILEACCESS_READ && options == FILEOPEN_OPEN_EXISTING )
		{
			if ( GetFileInfo( nullptr, fileName ) )
			{
        System::IO::Stream^ pStream = pFileSystem->OpenFile( FromMBCS( fileName ) );
				return new EditorWriteFileStream( pStream, true );
			}
			else
			{
				return nullptr;
			}
		}
		else if ( access == FILEACCESS_WRITE && options == FILEOPEN_CREATE_NEW )
		{
			return new EditorWriteFileStream( pFileSystem->CreateFile( FromMBCS( fileName ) ) );
		}
		else
		{
			return nullptr;
		}
	}

  virtual IFileWatcher *CreateFileWatcher( const string& szPath )
  {
    return 0; //TODO ?
  }

  virtual void SetFileReadCallback( IFileReadCallback* ) 
  {
    return; //TODO ?
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EditorFileSystem
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorFileSystem::Initialize( libdb::IO::IFileSystem^ pFileSystem )
{
	NFile::InitBaseDir();
	IFileSystem* fileSystem = new EditorFileSystemImpl( pFileSystem );
	RootFileSystem::RegisterFileSystem( fileSystem );
	RootFileSystem::SetWriteFileSystem( fileSystem );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorFileSystem::Release()
{
	RootFileSystem::ClearFileSystems();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( EditorFileSystemImpl );
REGISTER_SAVELOAD_CLASS( EditorWriteFileStream );
