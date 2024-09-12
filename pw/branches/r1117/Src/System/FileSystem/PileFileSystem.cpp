#include "stdafx.h"
#include "PileFileSystem.h"
#include "FilePath.h"
#include "FilePileLoader.h"
#include "FileUtils.h"


namespace fileSystem
{

PileFileSystem::PileFileSystem() 
{
  ScanForPiles();
}

PileFileSystem::PileFileSystem(IFileReadCallback* callback ) 
  : readCallback(callback)
{
  ScanForPiles();
}

bool PileFileSystem::GetFileInfo( SFileInfo *info, const string &fileName )
{
  for ( TPiles::iterator p = piles.begin(); p != piles.end(); ++p )
    if ( (*p)->HasFile( fileName ) )
    {
      info->pOwner = this;
      info->time = SWin32Time( 0 );
      return true;
    }

  return false;
}



void PileFileSystem::GetDirectories( vector<string> *pDirectories, const string &root )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
}



void PileFileSystem::GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive, int param /*= 0*/ )
{
  for ( TPiles::iterator p = piles.begin(); p != piles.end(); ++p )
    (*p)->FindFiles( pFiles, root, mask, recursive );
  //FIXME: pFiels will contain duplicate filenames
  //By now they will vanish in CombinerFilesystem
}



Stream * PileFileSystem::OpenFile( const string &fileName, EFileAccess access, EFileOpen options  )
{
  for ( TPiles::iterator p = piles.begin(); p != piles.end(); ++p )
  {
    Stream * stream = (*p)->ReadFile( fileName );
    if ( stream )
      return stream;
  }

  return 0;
}


namespace
{

struct SCompare
{
  bool operator () ( const string & left, const string & right )
  {
    return NStr::ICmp( left.c_str(), right.c_str() ) > 0;
  }
} compare;

}

bool PileFileSystem::ScanForPiles()
{
  list<string> files;
  //NFile::GetDirectoryFiles( NFile::GetBaseDir().c_str(), "*.pile", &files, false );
  NFile::GetDirectoryFiles( NFile::Combine( NFile::GetBaseDir(), "Packs/" ).c_str(), "*.pile", &files, false );
    
  // load the localized resources, based on the 'language' config value
  string selectedLanguage("ru-RU/"); // the default language
  if (!NGlobal::GetVar("language").GetString().empty())
  {
    selectedLanguage = NStr::ToMBCS(NGlobal::GetVar("language").GetString()) + "/";
  }
  
  list<string> i18nFiles;

  string langdir = NFile::Combine( NFile::GetBaseDir(), "Data/Localization/" + selectedLanguage);
  NFile::GetDirectoryFiles( langdir.c_str(), "*.pile", &i18nFiles, false );
  for ( list<string>::const_iterator it = i18nFiles.begin(); it != i18nFiles.end(); ++it )
  {
    files.push_back(*it);
  }
  
  sort( files.begin(), files.end(), compare );

  for ( list<string>::const_iterator it = files.begin(); it != files.end(); ++it )
  {
    DebugTrace( "Pile file '%s' found", it->c_str() );

    Strong<FilePileLoader> pile = new FilePileLoader;
    if ( pile->Init( *it, readCallback ) )
      piles.push_back( pile );
/*
    else
      if (IsValid(readCallback)) (*readCallback.GetPtr())(FR_CRC_FAIL, *it);
*/
  }
  return true;
}

} //namespace fileSystem
