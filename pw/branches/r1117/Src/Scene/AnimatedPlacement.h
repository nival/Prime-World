#pragma once

#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../libdb/AnimatedWrapper.h"
#include "../libdb/Animated2Spline.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class AnimatedPlacement : public NonCopyable
{
public:

  AnimatedPlacement() : base(NULLPLACEMENT), locator(NULLPLACEMENT) {}

	void Init( const NDb::AnimatedPlacement& src, float startTime )
	{
		aPos.Init( &original.pos, src.pos, startTime );
		aRot.Init( &original.rot, src.rot, startTime );
		aScale.Init( &original.scale, src.scale, startTime );

    result = locator + base + original;
	}

	void SetPlacement( const Placement& _placement )
	{
		original = _placement;

    result = locator + base + original;
	}

  void SetBase( const CVec3& basePos, const CQuat& baseRot, const CVec3& baseScale )
  {
		base.pos = basePos;
		base.rot = baseRot;
		base.scale = baseScale;

		aPos.Evaluate();
		aRot.Evaluate();
		aScale.Evaluate();

    result = locator + base + original;
  }

  void SetLocator( const CVec3& basePos, const CQuat& baseRot, const CVec3& baseScale )
  {
    locator.pos = basePos;
    locator.rot = baseRot;
    locator.scale = baseScale;

    aPos.Evaluate();
    aRot.Evaluate();
    aScale.Evaluate();

    result = locator + base + original;
  }

  const Placement& GetBase() const
  {
    return base;
  }

  const Placement& GetLocator() const
  {
    return locator;
  }

  const Placement& GetOriginal() const
  {
    return original;
  }

	void SetStartTime( float startTime )
	{
		aPos.SetStartTime( startTime );
		aRot.SetStartTime( startTime );
		aScale.SetStartTime( startTime );

    result = locator + base + original;
	}

	void Step( float dt )
	{
		aPos.Step( dt );
		aRot.Step( dt );
		aScale.Step( dt );
		
    result = locator + base + original;
	}

	float EvaluateAnimationLength() const
	{
		float len = 0.0f;
		if (aPos.IsAnimated())
			len = Max(len, aPos.GetLength());
		if (aRot.IsAnimated())
			len = Max(len, aRot.GetLength());
		if (aScale.IsAnimated())
			len = Max(len, aScale.GetLength());
		return len;
	}

	bool IsValid() const { return result.IsValid(); }

	operator const Placement&() const { return result; }
	const Placement& GetPlacement() const { return result; }

private:
	NDb::AnimatedWrapper<NDb::Animated<CVec3, NDb::AnimatedAlgorithms::Linear> > aPos;
	NDb::AnimatedWrapper<NDb::Animated<CQuat, NDb::AnimatedAlgorithms::Linear> > aRot;
	NDb::AnimatedWrapper<NDb::Animated<CVec3, NDb::AnimatedAlgorithms::Linear> > aScale;

	Placement original;
	Placement base;
	Placement result;
  Placement locator;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}