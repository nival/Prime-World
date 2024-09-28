#include "stdafx.h"
#include "SkeletalAnimationBlender.h"
#include "../MeshConverter/SkeletonHeader.h"
#include "SkeletonWrapper.h"

namespace Render
{

	void SkeletalAnimationBlender::Sample( Matrix43* out )
	{
		NI_VERIFY( out, "pointer is null!", return );

		unsigned int jointsCount = pFirstSampler->GetJointsCount();
		NI_VERIFY( !pNextSampler || pFirstSampler->GetJointsCount() == pNextSampler->GetJointsCount(), "animations appears to be not the same!", return );

		for ( unsigned int jointNumber = 0; jointNumber < jointsCount; jointNumber++ )
		{
			CQuat leftRot;
			pFirstSampler->GetRotation( jointNumber, leftRot );
			CVec3 leftTranslation;
			pFirstSampler->GetTranslation( jointNumber, leftTranslation );
			CVec3 leftScale;
			pFirstSampler->GetScale( jointNumber, leftScale );

			if ( blending )
			{
				CQuat rightRotation;
				pNextSampler->GetRotation( jointNumber, rightRotation );
				CVec3 rightTranslation;
				pNextSampler->GetTranslation( jointNumber, rightTranslation );
				CVec3 rightScale;
				pNextSampler->GetScale( jointNumber, rightScale );

				CQuat qrot;                          
				qrot.Interpolate( leftRot, rightRotation, currentAlpha );
				CVec3 trans = Lerp( leftTranslation, rightTranslation, currentAlpha );
				CVec3 scale = Lerp( leftScale, rightScale, currentAlpha );

        out[jointNumber].Set( qrot, trans, scale );
			}
      else
      {
        out[jointNumber].Set( leftRot, leftTranslation, leftScale );
      }
		}
	}

  SkeletalAnimationBlender::~SkeletalAnimationBlender()
	{
		if( pFirstSampler != pNextSampler ) 
			delete pNextSampler;
		delete pFirstSampler;
		pNextSampler = 0;
		pFirstSampler = 0;
	}

	void SkeletalAnimationBlender::Update( float delta, float absTime )
	{
		if ( !pFirstSampler )
			return;

		pFirstSampler->Update( delta );

		if ( !blending )
			return;

		pNextSampler->Update( delta );
		blendTimeLeft -= delta;

		if ( blendTimeLeft > 0 )
		{
			currentAlpha = 1.0f - blendTimeLeft / blendTimeTotal;
			return;
		}

		blending = false;
		blendTimeLeft = 0;
		delete pFirstSampler; 
		pFirstSampler = pNextSampler;
		pNextSampler = 0;
		currentAlpha = 0.f;

	}

	void SkeletalAnimationBlender::Update( float delta, float animFirstSpeed, float animNextSpeed, float curAlpha )
	{
		if ( !pFirstSampler )
			return;

		pFirstSampler->Update( delta * animFirstSpeed );

		if ( !blending )
			return;

		pNextSampler->Update( delta * animNextSpeed );

		currentAlpha = curAlpha;
		if ( curAlpha > 0.f )
			return;

		blending = false;
		blendTimeLeft = 0;
		delete pFirstSampler; 
		pFirstSampler = pNextSampler;
		pNextSampler = 0;
	}

	void SkeletalAnimationBlender::UpdateTime( float delta, float animFirstTime, float animNextTime, float curAlpha )
	{
		if ( !pFirstSampler )
			return;

		pFirstSampler->SetTime( animFirstTime );

		if ( !blending )
			return;

		pNextSampler->SetTime( animNextTime );

		currentAlpha = curAlpha;
		if ( curAlpha > 0.f )
			return;

		blending = false;
		blendTimeLeft = 0;
		delete pFirstSampler; 
		pFirstSampler = pNextSampler;
		pNextSampler = 0;
	}

};
