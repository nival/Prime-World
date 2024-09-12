#pragma once

#include "CollisionGeometry.h"
#include "GeometryTracer.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	class SceneObject;
	_interface IScene;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
namespace nstl
{
	template<> struct hash<CPtr<NScene::SceneObject>>
	{
		size_t operator()(const CPtr<NScene::SceneObject>& s) const { return IsValid(s.GetPtr()) ? 0 : (int)(s.GetPtr());  }
	};
	template<> struct hash<CObj<NScene::SceneObject>>
	{
		size_t operator()(const CObj<NScene::SceneObject>& s) const { return IsValid(s.GetPtr()) ? 0 : (int)(s.GetPtr());  }
	};
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionHull;
class CollisionVolumeNode;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Intersection
{
	CPtr<CollisionHull> pHull;
	CVec3 enter;
	CVec3 exit;

	Intersection() {}
	Intersection( CollisionHull* _pHull, const CVec3& _enter, const CVec3& _exit ) : pHull( _pHull ), enter( _enter ), exit( _exit ) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct IntersectionFloat
{
  CPtr<CollisionHull> pHull;
  float enter;
  float exit;
  int sortIndex;

  bool operator> ( const IntersectionFloat& i2 ) { return enter > i2.enter; }
  bool operator< ( const IntersectionFloat& i2 ) { return i2.enter > enter; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionMap : public CObjectBase
{
	OBJECT_BASIC_METHODS( CollisionMap );

	struct IntersectionFloatSort
	{
		void operator()( IntersectionFloat* p1, IntersectionFloat* p2 )
		{
			const int tempIndex = p2->sortIndex;
			p2->sortIndex = p1->sortIndex;
			p1->sortIndex = tempIndex;
		}
	};

	//typedef vector<CObj<CollisionHull>> TObjectHulls;
	//typedef hash_map<CPtr<SceneObject>, TObjectHulls> THulls;
	//THulls hulls;

	vector<CObj<CollisionVolumeNode>> floors;
	int activeFloor;

	GeometryTracer tracer;
	nstl::vector<IntersectionFloat> floatIntersections;

  CVec3 floorBase; 
  float floorSize; 

	//CollisionHull* FindHull( const HullTag& tag ) const;
protected:
public:
	CollisionMap() : activeFloor( 0 ) {}
	virtual ~CollisionMap() {}

	void Initialize( int floorsCount, const CVec3& _floorBase, float _floorSize );
	const int GetActiveFloor() const { return activeFloor; }
	bool SetActiveFloor( int floor );

	CollisionHull* CreateHull( SceneObject* pSceneObject, const int pieceId, CollisionGeometry* pGeometry, const Matrix43& place, const int floor );
	bool RemoveHull( CollisionHull* pHull );

	CollisionVolumeNode* GetNode( const SBound& bounds, const int floor );

	//void AddHull( const HullTag& tag, CollisionGeometry* pGeometry, const int floor, const Matrix43& place );
	//void UpdateHull( const HullTag& tag, CollisionGeometry* pGeometry );
	//void MoveHull( const HullTag& tag, const int floor, const Matrix43& placement );
	//void RemoveHull( const HullTag& tag );
	//void RemoveHulls( SceneObject* pSceneObject );

	int Trace( Intersection *pIntersections, const int intersectionsSize, const CRay& ray, const bool onlyEnters, float fNear );
  int Trace( IntersectionFloat *pIntersections, const int intersectionsSize, const CRay& ray, const bool onlyEnters, float fNear );
	bool TraceRect( CollisionHull* pHull, const SHMatrix& viewAndProj, float fNear, int w, int h, CTRect<float> *pRect );
	
  void DebugRender( Render::IDebugRender* debugRender );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
