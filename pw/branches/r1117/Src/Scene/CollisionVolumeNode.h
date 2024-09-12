#pragma once

#include "OcTree.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MINIMAL_OCTREE_NODE 4
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionVolumeNode : public OctreeNode<CollisionVolumeNode, MINIMAL_OCTREE_NODE>
{
	OBJECT_BASIC_METHODS( CollisionVolumeNode ); // registration can be found in CollisionMap.cpp

public:
	struct HullInfo
	{
		CObj<CollisionHull> pHull;
		int nextFreeIndex;
	};
	
private:
	vector<HullInfo> hulls;
	int firstFreeIndex;

public:
	CollisionVolumeNode() : firstFreeIndex( -1 ) { }

	int AddHull( CollisionHull* pHull )
	{
		int place;
		if ( firstFreeIndex < 0 )
		{
			hulls.resize( hulls.size() + 1 );
			place = hulls.size() - 1;
		}
		else
		{
			place = firstFreeIndex;
			firstFreeIndex = hulls[firstFreeIndex].nextFreeIndex;
		}
		// store data
		HullInfo& info = hulls[place];
		info.pHull = pHull;
		info.nextFreeIndex = 0;
		return place;
	}

	void RemoveHull( int index )
	{
		hulls[index].pHull = 0;
		hulls[index].nextFreeIndex = firstFreeIndex;
		firstFreeIndex = index;
	}
	
	virtual bool IsEmpty() const
	{
		for( vector<HullInfo>::const_iterator it = hulls.begin(); it != hulls.end(); ++it )
		{
			if ( IsValid( it->pHull ) )
				return false;
		}

		return true;
	}

	template<typename TVisitor>
	void VisitHulls( TVisitor* pVisitor )
	{
		if ( !pVisitor->Test( this ) )
			return;

		for( vector<HullInfo>::const_iterator it = hulls.begin(); it != hulls.end(); ++it )
		{
			if ( IsValid( it->pHull ) )
				pVisitor->Visit( it->pHull );
		}

		for( int i = 0; i < 8; ++i )
		{
			CollisionVolumeNode* pNode = GetNode( i );
			if ( IsValid( pNode ) )
				pNode->VisitHulls( pVisitor );
		}
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene
