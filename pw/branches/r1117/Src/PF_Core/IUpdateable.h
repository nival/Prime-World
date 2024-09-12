#pragma once

#include "../System/Ring.h"

namespace PF_Core
{

class IUpdateable;

struct IUpdateableFunc
{
	virtual void operator()(IUpdateable *pObj) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IUpdateable : public CObjectBase
{
public:
	enum
	{
		PRIORITY_NA          = -1,
		PRIORITY_DEFAULT     = 2,
		PRIORITY_COUNT       = 4
	};

	virtual void Update(float timeDelta) = 0;
	virtual void OnDestroyContents();

	void Subscribe(int priority = PRIORITY_DEFAULT); 
	void Unsubscribe();

	static void ProceedUpdate(float timeDelta);
	static void ForcedClear();
	static void ForAll(IUpdateableFunc &func);

protected:
	IUpdateable(bool bAutoAdd = false, int priority = PRIORITY_DEFAULT) 
	{
		if (bAutoAdd)
			Subscribe(priority);
	}

	seDECLARE_COBJRING( IUpdateable, part, Ring );

private:
	static Ring					s_objects[PRIORITY_COUNT];
	static IUpdateable *s_pUpdateIterator;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IUpdateableAfterScene
{
public:
	static void ProceedUpdate(float timeDelta);

	virtual void UpdateAfterScene(float timeDelta) = 0;

	void SubscribeAfterScene();
	void UnsubscribeAfterScene();

protected:
	seDECLARE_RING( IUpdateableAfterScene, part, Ring );

private:
	static Ring s_objects;
};

}
