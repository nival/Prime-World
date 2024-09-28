#pragma once

#include "Animated.h"
#include "AnimatedAlgorithms.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TAnimated>
class AnimatedWrapper
{
public:
	AnimatedWrapper() : dest( 0 ), time( 0.0f ) {}

	void Init( typename TAnimated::TAnimatedType* _dest, const TAnimated& _src, float startTime )
	{
		dest = _dest;
		src = _src;

		time = startTime;
		left = src.find( time );
    right = left+1;
    if ( right == src.end() )
      right = left;
		*dest = src.GetValue( time );
	}
	
	void SetStartTime( float startTime )
	{
		time = startTime;
		left = src.find( time );
    right = left+1;
    if ( right == src.end() )
      right = left;
		Evaluate();
	}

	void Step( float dt )
	{
		if ( !IsAnimated() )
			return;

		float key = src.ShiftKey( time, dt, &left, &right );
		*dest = src.GetValue( key, left, right );

		time += dt;
	}

	void Evaluate()
	{
		if ( IsAnimated() )
			*dest = src.GetValue( time );
	}

	bool IsAnimated() const
	{
		return src.IsAnimated();
	}

	float GetLength() const { return src.GetLength(); }

  bool IsFinished() const { return src.GetLength() < time; }

private:
	typename TAnimated::TAnimatedType* dest;
	TAnimated src;
	
	typename TAnimated::const_iterator right;
	typename TAnimated::const_iterator left;
	
	float time;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

