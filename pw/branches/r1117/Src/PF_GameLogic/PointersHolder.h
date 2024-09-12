#pragma once

#include "../System/ChunklessSaver.h"

namespace NWorld
{
class PFWorld;

class PointersHolder : public IPointerHolder, public CObjectBase
{
	OBJECT_METHODS( 0x8D7BD480, PointersHolder );
public:
	nstl::hash_map<int, CObj<CObjectBase>> objs;
	CPtr<PFWorld> pWorld;

	PointersHolder() {}
	PointersHolder( PFWorld* world, int num )
	{
		pWorld = world;
	}

	~PointersHolder()
	{
		for ( nstl::hash_map<int, CObj<CObjectBase>>::iterator it = objs.begin(); it != objs.end(); it++ )
		{
			it->second = 0;
		}
		objs.clear();
	}

	void Add( CObjectBase* obj, int id )
	{
		objs[id] = obj;
	}

	virtual int GetObjectID( CObjectBase *p )
	{
		if ( p == this )
			return PF_Core::WORLD_ID;

		for ( nstl::hash_map<int, CObj<CObjectBase>>::iterator it = objs.begin(); it != objs.end(); it++ )
		{
			if ( it->second.GetPtr() == p )
			{
				return it->first;
			}
		}
		return PF_Core::INVALID_OBJECT_ID;
	}

	virtual CObjectBase* GetObject ( int nID )
	{
		if( PF_Core::INVALID_OBJECT_ID == nID )
			return NULL;

		if ( nID == PF_Core::WORLD_ID )
			return pWorld.GetBarePtr();

		nstl::hash_map<int, CObj<CObjectBase>>::iterator object = objs.find(nID);
		return objs.end() == object ? NULL : object->second;
	}

	int GetObjectIdST( BaseObjectST* object )
	{
		NI_ALWAYS_ASSERT( "Not implemented" );
		return 0;
	}

	BaseObjectST* GetObjectST( int id )
	{
		NI_ALWAYS_ASSERT( "Not implemented" );
		return 0;
	}

	int GetObjectIdMT( BaseObjectMT* pObject )
	{
		NI_ALWAYS_ASSERT( "Not implemented" );
		return 0;
	}

	BaseObjectMT* GetObjectMT( int id )
	{
		NI_ALWAYS_ASSERT( "Not implemented" );
		return 0;
	}
};
}