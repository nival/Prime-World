#include "stdafx.h"

#include "CollisionGeometryManager.h"
#include "CollisionGeometry.h"
#include "../System/BinChunkSerializer.h"

namespace NScene
{
  CollisionGeometry* CollisionGeometryManager::Create( const NDb::CollisionGeometry* _pGeometry )
  {
    NDb::Ptr<NDb::CollisionGeometry> pGeometry = _pGeometry;

    if ( !IsValid( pGeometry ) || pGeometry->fileName.empty() )
      return 0;

    It it = cache.find( pGeometry );
    if ( it != cache.end() )
    {
      return it->second;
    }

    CollisionGeometry* pCG = new CollisionGeometry();
    
    CObj<Stream> pGeometryStream = RootFileSystem::OpenFile( pGeometry->fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    NI_VERIFY( IsValid( pGeometryStream ), NStr::StrFmt( "Cannot open file \"%s\" with collision geometry", pGeometry->fileName.c_str() ), return 0 );

    CObj<IBinSaver> pSaver = CreateReadBinSaver( pGeometryStream, 0 );
    (*pCG)&( *pSaver );

    cache[pGeometry] = pCG;

    return pCG;
  }

  CollisionGeometryManager::~CollisionGeometryManager()
  {
    Clear();
  }

  void CollisionGeometryManager::Clear()
  {
    cache.clear();
  }
}