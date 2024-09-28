#include "stdafx.h"
#include "Utility.h"
#include "ResourceCache.h"
#include "../System/BSUtil.h"
#include "../libdb/DBResourceCache.h"
#include "../System/ConfigFiles.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace EditorNative;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace 
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditorFileWatcher : public IFileWatcher, public CObjectBase
{	
public:
  EditorFileWatcher() {}

  void AddChangedFile( const string& name )
  {
    changedFiles.insert( name );
  }

  virtual bool SomethingChanged( IFileWatcher::TChangedFileList* pRes )
  {
    if ( changedFiles.empty() )
      return false;

    pRes->insert( pRes->end(), changedFiles.begin(), changedFiles.end() );
    changedFiles.clear();
    return true;
  }
  virtual const string& GetPath() const  { static string empty; return empty; }
private:
  OBJECT_BASIC_METHODS( EditorFileWatcher )

    set<string> changedFiles;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditorDbResourceCache : public NDb::DbResourceCache
{
public:
  NDb::Ptr<NDb::DbResource> Create( const NDb::DBID &dbid, const char *typeName )
  {
    NI_ALWAYS_ASSERT( "Object creation is not supported in editor mode." );
    return 0;
  }

  void Reset( const NDb::DBID &dbid )
  {
    NDb::DbResourceCache::Reset( dbid );
  }

  static EditorDbResourceCache& GetInstance();

  EditorDbResourceCache() 
    : DbResourceCache( 0 )
  {
    fileWatcher = new EditorFileWatcher();
    RootFileSystem::GetChangesProcessor().SetFileWatcher( fileWatcher );
    SetFileSystemChangesProcessor( &RootFileSystem::GetChangesProcessor() );
  } 

  ~EditorDbResourceCache()
  {
    RootFileSystem::GetChangesProcessor().SetFileWatcher( 0 );
    SetFileSystemChangesProcessor( 0 );
  }

  virtual NDb::DbResource* Read( const NDb::DBID &dbid, IXmlSaver *_pSaver, const bool fullRead, const bool forceUseParamSaver )
  {
    if ( forceUseParamSaver || !dbid.IsInlined() || !IsValid( _pSaver ) )
    {
      array<Byte>^ data = libdb::DB::DataBase::SerializeToMemory( libdb::DB::DBID::FromString( FromMBCS( GetFormattedDbId( dbid ) ) ) );

      if ( !Object::ReferenceEquals( data, nullptr ) && data->Length > 0 )
      {
        pin_ptr<Byte> ptr = &data[0];
        CObj<Stream> pStream = new FixedMemoryStream( ptr, data->Length );
        return DbResourceCache::Read( dbid, CreateXmlSaver( pStream, true ), fullRead, true );
      }
      else
      {
        return nullptr;
      }
    }
    else
      return DbResourceCache::Read( dbid, _pSaver, fullRead, false );
  }

  NDb::Ptr<NDb::DbResource> Precache( const NDb::DBID& dbid, const int depth )
  {
    return Get( dbid, 0, true );
  }

private:
  CObj<EditorFileWatcher> fileWatcher;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static CObj<EditorDbResourceCache> pInstance;
EditorDbResourceCache& EditorDbResourceCache::GetInstance()
{
  if( pInstance == 0 )
    pInstance = new EditorDbResourceCache();

  return *pInstance;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}   // namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceCache::Initialize()
{

  NDb::SetResourceCache( &EditorDbResourceCache::GetInstance() );

  NBSU::InitUnhandledExceptionHandler();  
  SetMemoryLeaksDumpLevel( true );
  NBSU::SetIgnoreAll( true );
  NFile::InitBaseDir();
  NProfile::Init( "Primal Forces" );
  NGlobal::ExecuteConfig( "editor.cfg", NProfile::FOLDER_GLOBAL );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceCache::MarkAsDirty( libdb::DB::DBID^ dbId )
{
  EditorDbResourceCache::GetInstance().Reset( NDb::DBID( ToMBCS( dbId->FileName ), ToMBCS( dbId->Id ) ) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceCache::Release()
{
  pInstance = 0;
  NDb::SetResourceCache( nullptr );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
