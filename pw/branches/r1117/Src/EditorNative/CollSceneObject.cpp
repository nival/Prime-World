#include "stdafx.h"
#include "EditorScene.h"
#include "Utility.h"
#include "CollSceneObject.h"
#include "../Scene/EditorSceneObject.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/CollisionGeometry.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollSceneObject::CollSceneObject( DBID^ _dbId )
:	EditorSceneObject( _dbId )
{
  NScene::CollisionGeometry::GetCollisionManager().Clear();
  colGeom = NScene::CollisionGeometry::GetCollisionManager().Create( GetObject<NDb::CollisionGeometry>( _dbId ) );
}

void CollSceneObject::Draw( NScene::IScene& scene )
{
  if ( colGeom )
  {
    for ( vector<NScene::CollisionGeometry::Edge>::const_iterator it = colGeom->GetEdges().begin(); it != colGeom->GetEdges().end(); ++it )
    {
      CVec3 p1 = colGeom->GetPoints()[it->start];
      CVec3 p2 = colGeom->GetPoints()[it->finish];
      Render::DebugRenderer::DrawLine3D(p1, p2, Render::Color((unsigned long)0xFF00FF00), Render::Color((unsigned long)0xFF00FF00), false);
    }
  }
}