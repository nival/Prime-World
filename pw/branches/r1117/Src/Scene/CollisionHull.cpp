#include "stdafx.h"

#include "../Render/StaticMesh.h"
#include "RenderableScene.h"
#include "Scene.h"
#include "CollisionGeometry.h"
#include "CollisionMap.h"
#include "CollisionVolumeNode.h"
#include "CollisionHull.h"
#include "../Render/debugrenderer.h"
#include "../Render/aabb.h"
#include "SceneObject.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CollisionHull::~CollisionHull()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionHull::RefreshBounds()
{
	if ( !IsValid( pGeometry ) || floor < 0 )
		return;

	pGeometry->GetBounds( &bounds );
  boundsHalfBox = bounds.ptHalfBox * GetPosition().GetUniformScale();
	const float radius = sqrt( CalcRadius2( bounds, GetPosition() ) );
	CVec3 center = Transform( bounds.s.ptCenter, GetPosition() );
	bounds.SphereInit( center, radius );

	CollisionVolumeNode* pNewNode = pCollisionMap->GetNode( GetBounds(), floor );
	if ( pNewNode == pNode )
		return;

	// VolumeNode holds CObj to Hull so first we should AddHull and then RemoveHull
	const int newIndexInNode = pNewNode->AddHull( this );
	
	if ( IsValid( pNode ) )
		pNode->RemoveHull( indexInNode );
	
	pNode = pNewNode;
	indexInNode = newIndexInNode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionHull::SetPosition( const Matrix43& _position, const int _floor )
{
	if ( _position == position && floor == _floor )
		return;

	position = _position;
	floor = _floor;
	RefreshBounds(); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionHull::RemoveFromNodes()
{
	CObj<CollisionHull> pThis = this;
	if ( IsValid( pNode ) )
	{
		pNode->RemoveHull( indexInNode );
		pNode = 0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollisionHull::DebugRender( Render::IDebugRender* debugRender )
{
	pGeometry->DebugDraw( position, debugRender );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CollisionHull::SetEnabled( bool bEnabled_ ) 
{ 
  bEnabled = bEnabled_; 
}
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( NScene::CollisionHull );
