#include "stdafx.h"

#include "TestFileSystem.h"
#include "FilePath.h"
#include "FileUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static string Combine( const string &leftPath, const string &rightPath )
{
  string right = rightPath;

  NStr::TrimLeft( right, '\\' );
  NStr::TrimLeft( right, '/' );

  return leftPath + right;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TestFileSystem::TestFileSystem( const string &_root, const bool _writable, bool automapRoot )
{
  this->automapRoot = automapRoot;
  fileSystemRoot = _root;
  writable = _writable;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestFileSystem::GetDirectories( vector<string>*, const string& )
{
  NI_ALWAYS_ASSERT( "Not implemented in test filesystem" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestFileSystem::GetFiles( vector<string>*, const string&, const string&, bool recursive, int param )
{
  NI_ALWAYS_ASSERT( "Not implemented in test filesystem" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TestFileSystem::GetFileInfo( SFileInfo *info, const string &fileName )
{
  const string fullPath = Combine( fileSystemRoot, fileName );

  TFiles::iterator it = files.find( fullPath );
  if ( it == files.end() )
    return false;

  if ( info )
  {
    info->pOwner = this;
  }

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Stream* TestFileSystem::OpenFile( const string &fileName, EFileAccess access, EFileOpen options )
{
  if ( access == FILEACCESS_READ )
    NI_VERIFY( options != FILEOPEN_CREATE_NEW, "Cant create readonle file for writing", return 0 )
  else
    NI_VERIFY( writable, "Cant open readonle file for writing", return 0 );

  const string fullPath = Combine( fileSystemRoot, fileName );

  TFiles::iterator it = files.find( fullPath );
  if ( it == files.end() )
  {
    if ( options == FILEOPEN_CREATE_NEW )
    {
      files[ fullPath ] = new MemoryStream();
      it = files.find( fullPath );
    }
    else if (automapRoot)
    {
      CObj<FileStream> pStream = new FileStream( fullPath, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      if ( !pStream->IsOk() )
        return 0;

      files[ fullPath ] = pStream;
      return pStream;
    }
    else
      return 0;
  }

  Stream* stream = it->second;
  if ( stream == 0 || !stream->IsOk() )
  {
    files.erase( it );
    return 0;
  }

  stream->Seek( 0, SEEKORIGIN_BEGIN );
  ++usageCounts[ fullPath ];
  return stream;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IFileWatcher* TestFileSystem::CreateFileWatcher( const string& path )
{
  NI_ALWAYS_ASSERT( "Not implemented in test filesystem" );
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestFileSystem::SetFileWithContents( const string& fileName, const string& fileData )
{
  const string fullPath = Combine( fileSystemRoot, fileName );

  MemoryStream* pStream = new MemoryStream();
  pStream->WriteString( fileData );
  pStream->Seek( 0, SEEKORIGIN_BEGIN );
  files[ fullPath ] = pStream;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestFileSystem::AssignFileWithFile( const string& fileName, const string& realFileName )
{
  const string fullPath = Combine( fileSystemRoot, fileName );

  FileStream* pStream = new FileStream( realFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  files[ fullPath ] = pStream;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestFileSystem::ResetUsageCounts()
{
  usageCounts.clear();

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestFileSystem::GetUsageCount( const string& fileName )
{
  const string fullPath = Combine( fileSystemRoot, fileName );
  return usageCounts[ fullPath ];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( TestFileSystem );

