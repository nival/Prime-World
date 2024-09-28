#pragma once

#include "IUpdateable.h"
#include "System/InlineProfiler.h"

namespace PF_Core
{

class ObjectInPool;

class ObjectsPool : public CObjectBase
{
  OBJECT_BASIC_METHODS( ObjectsPool );

public:
	ObjectsPool() 
		: objectsCreatedCount(0)
	{

  }
	//~ObjectsPool();

	int GetObjectsCreatedCount() const { return objectsCreatedCount; }

	template <class T>
	CObj<T> Retrieve()
	{
    NI_PROFILE_FUNCTION;

		if (pool.empty())
		{
			CObj<T> pObj(new T());
			pObj->SetPool(this);
			pObj->Init();
			objectsCreatedCount++;
			return pObj;
		}

		NI_ASSERT( dynamic_cast<T*>( pool.back() ) != 0, "Pool type usage is invalid" );
		CObj<T> pObj( static_cast<T*>( pool.back() ) );
		pool.pop_back();
		pObj->SetPool(this);
		pObj->Init();
		return pObj;
	}

	template <class T, class PARAM>
	CObj<T> Retrieve(const PARAM &param)
	{
    NI_PROFILE_FUNCTION;

		if (pool.empty())
		{
			CObj<T> pObj( new T(param) );
			pObj->SetPool(this);
      pObj->Init();
			objectsCreatedCount++;
			return pObj;
		}

		NI_ASSERT( dynamic_cast<T*>( pool.back().GetPtr() ) != 0, "Pool type usage is invalid" );
		CObj<T> pObj( static_cast<T*>( pool.back().GetPtr() ) );
		pool.pop_back();
		pObj->SetPool(this);
		pObj->Init();
		return pObj;
	}

private:
	int objectsCreatedCount;
	list<CObj<ObjectInPool> > pool;

	friend class ObjectInPool;
};

class ObjectInPool : public IUpdateable
{
public:
//TODO: "To think about update!")
  bool IsInPool() const { return !pPool; }

protected:
	ObjectInPool() : pPool(0) {}
	virtual ~ObjectInPool() {}

	void Release2Pool() 
	{ 
    NI_ASSERT( !IsInPool(), "Object already released!" );
    if( !IsInPool() )
    {
		  pPool->pool.push_back(CObj<ObjectInPool>(this)); 
		  pPool = 0; // Avoid circular reference
    }
		Unsubscribe();
	}

private:
	void SetPool(ObjectsPool* pPool_) { pPool = pPool_; }

	CPtr<ObjectsPool> pPool;

	friend class ObjectsPool;
};

}
