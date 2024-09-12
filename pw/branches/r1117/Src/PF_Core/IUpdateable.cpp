#pragma once

#include "stdafx.h"
#include "IUpdateable.h"
#include "../System/InlineProfiler.h"

static NDebug::DebugVar<int> perfCounters_ObjectsUpdated( "Objects updated", "PerfCnt" );

namespace PF_Core
{

IUpdateable::Ring IUpdateable::s_objects[IUpdateable::PRIORITY_COUNT];
IUpdateable *IUpdateable::s_pUpdateIterator = 0;

IUpdateableAfterScene::Ring IUpdateableAfterScene::s_objects;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateable::ForAll(IUpdateableFunc &func)
{
	for (int i = 0; i < PRIORITY_COUNT; i++)
		ring::ForAll(s_objects[i], func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateable::ProceedUpdate(float timeDelta)
{
  NI_PROFILE_FUNCTION

	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		if (s_objects[i].empty())
			continue;

		s_pUpdateIterator = s_objects[i].first();
		IUpdateable *pTerminator = s_objects[i].last();
		do 
		{
			// Perform update
			s_pUpdateIterator->Update(timeDelta);
			// s_pUpdateIterator could have been changed in update
			if (s_pUpdateIterator == pTerminator)
				break;
			// Get to the next
			s_pUpdateIterator = s_pUpdateIterator->part.next;
		} while (s_pUpdateIterator != pTerminator);
	}

	s_pUpdateIterator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateable::ForcedClear()
{
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		ring::Clear(s_objects[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateable::Subscribe(int priority)
{
	NI_ASSERT(PRIORITY_NA < priority && priority < PRIORITY_COUNT, "Invalid update priority given");
	s_objects[priority].addLast(this);
	perfCounters_ObjectsUpdated.AddValue(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateable::Unsubscribe() 
{ 
	if (this == s_pUpdateIterator)
	{
		// Get to the next object
		s_pUpdateIterator = s_pUpdateIterator->part.next;
	}
	Ring::safeRemove(this); 
	perfCounters_ObjectsUpdated.DecValue(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateable::OnDestroyContents()
{
	Unsubscribe();
	CObjectBase::OnDestroyContents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableAfterScene::ProceedUpdate(float timeDelta)
{
  NI_PROFILE_FUNCTION

  for (ring::Range<Ring> it(s_objects); it;)
	{
		IUpdateableAfterScene *pObj = &(*it);
		++it;
		pObj->UpdateAfterScene(timeDelta);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableAfterScene::SubscribeAfterScene() 
{ 
	s_objects.addLast(this); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IUpdateableAfterScene::UnsubscribeAfterScene() 
{ 
	Ring::safeRemove(this); 
}





}
