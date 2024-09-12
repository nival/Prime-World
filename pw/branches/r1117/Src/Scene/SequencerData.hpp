#pragma once
//#include "../Scene/DBScene.h"
//#include "../Render/DBRenderResources.h"
#include "TimedChannel.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
	struct Skeleton;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Animator: public CObjectBase
{
public:	
	virtual Time GetStartTime() const = 0;
	virtual Time GetEndTime() const = 0;
	virtual bool CanBlendPosition() const = 0;

	virtual void GetTransform( SHMatrix *pRes, Time time ) = 0;
	virtual Time GetAnimTime( Time time ) const = 0;
	virtual float GetAnimBlendFactor( Time time ) = 0;

	//obsolete
	virtual float GetAnimSpeed( Time time ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SAnimationInfo : public TimedChannelValueBase
{
	EAnimAction action;
	int animName;
	CObj<Animator> pAnimator;
	Time tPhase;
	float fSpeedFactor;
	bool essential;
	Time GetEndTime() const { return pAnimator ? pAnimator->GetEndTime() : startTime; }
	bool IsEssential() const { return essential; }

	SAnimationInfo() : action(AA_INVALID),	tPhase(0), animName(0) {}

	SAnimationInfo( Time _tStart, EAnimAction _action, const int &_animName, Animator *_pAnimator, float _fSpeedFactor ) 
		:	action(_action)
		, animName(_animName)
		, pAnimator(_pAnimator)
		,fSpeedFactor(_fSpeedFactor)
	{ 
		startTime = _tStart;
		essential = action != AA_IDLE && action != AA_NON_ESSENTIAL;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SPositionInfo : public TimedChannelValueBase
{
	EAnimAction action;
	CObj<Animator> pAnimator;
	bool essential;
	Time GetEndTime() const { return pAnimator ? pAnimator->GetEndTime() : startTime; }
	bool IsEssential() const { return essential; }

	SPositionInfo() : action(AA_IDLE) {}

	SPositionInfo( Time _tStart, EAnimAction _action, Animator *_pAnimator ) 
		:	action(_action)
		, pAnimator(_pAnimator)
	{ 
		startTime = _tStart;
		essential = action != AA_IDLE && action != AA_NON_ESSENTIAL;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SModelInfo : public TimedChannelValueBase
{
	//NDb::Ptr<NDb::Skeleton> pNewModel;
	int modelIndex;
	SModelInfo() : modelIndex(0) {}
	//SModelInfo( Time _tStart, const NDb::Skeleton* _pNewModel )
	//	: TimedChannelValueBase(_tStart), pNewModel(_pNewModel)
	//{}
	SModelInfo( Time _tStart, int _modelIndex ) : modelIndex(_modelIndex)
	{}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
