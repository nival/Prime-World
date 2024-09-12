#pragma once

#include "CollisionGeometry.h"
#include "CollisionMap.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
class CollisionVolumeNode;
class SceneObject;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionHull : public CObjectBase
{
	OBJECT_BASIC_METHODS( CollisionHull )

	SceneObject* pSceneObject;
	int pieceId;
	bool bEnabled;

	CObj<CollisionGeometry> pGeometry;
	Matrix43 position;
	int floor;

	CPtr<CollisionMap> pCollisionMap;
	CPtr<CollisionVolumeNode> pNode;
	int indexInNode;

	SBound bounds; //These bounds are rounded by sphere, and equal for each coordinate
  CVec3 boundsHalfBox; //Box with different value along each axis

	Render::Color visualColor;

	void RefreshBounds();

	CollisionHull() : indexInNode( -1 ) { };

public:
	CollisionHull( SceneObject* _pSceneObject, const int _pieceId, CollisionMap* _pCollisionMap ) 
		: pSceneObject( _pSceneObject ), pieceId( _pieceId ), bEnabled(true), pCollisionMap( _pCollisionMap ), indexInNode( -1 ), floor( -1 ),
    boundsHalfBox( 0, 0, 0 ),
		visualColor( 255, 255, 255, 255 )
	{
		Identity( &position );
	}
	
	virtual ~CollisionHull();

	SceneObject* GetSceneObject() const { return pSceneObject; }
	const int GetPieceId() const { return pieceId; }
	const CollisionGeometry* GetGeometry() const { return pGeometry; }
	CollisionGeometry* GetGeometry() { return pGeometry; }
	const Matrix43& GetPosition() const { return position; }
	const SBound& GetBounds() const { return bounds; }
  const CVec3& GetBoundsCenter() const { return bounds.s.ptCenter; }
  const CVec3 & GetBoundsHalfBox() const { return boundsHalfBox; }

	void SetEnabled( bool bEnabled_ );
	bool IsEnabled() const { return bEnabled; }

	void SetPosition( const Matrix43& _position, const int _floor );
	void SetGeometry( CollisionGeometry* _pGeometry ) { pGeometry = _pGeometry; RefreshBounds(); }

	void RemoveFromNodes();

	void DebugRender( Render::IDebugRender* debugRender );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
