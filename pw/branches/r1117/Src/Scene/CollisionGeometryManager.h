#pragma once

#include "../libdb/db.h"
#include "DBSceneBase.h"

namespace NScene
{
  class CollisionGeometry;

  struct CGHash
  {
    unsigned int operator()( const NDb::Ptr<NDb::CollisionGeometry>& a ) const
    {
      return __stl_hash_string(GetFormattedDbId(a->GetDBID()).c_str());
    }
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class CollisionGeometryManager
  {
    typedef nstl::hash_map<NDb::Ptr<NDb::CollisionGeometry>, CObj<CollisionGeometry>, CGHash>::iterator It;

    nstl::hash_map<NDb::Ptr<NDb::CollisionGeometry>, CObj<CollisionGeometry>, CGHash> cache;
  public:
    ~CollisionGeometryManager();
    CollisionGeometry* Create( const NDb::CollisionGeometry* pGeometry );
    void Clear();
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene