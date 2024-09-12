#pragma once

#include "SkeletalAnimationSampler.h"

namespace OC3Ent
{
	namespace Face
	{
		class FxActor;
		class FxActorInstance;
	};
};

namespace Render
{
	class SkeletonWrapper;
	///
	class SkeletalAnimationBlender
	{
		SkeletalAnimationSampler* pFirstSampler;
		SkeletalAnimationSampler* pNextSampler;
//		float leftCurrentTime;
//		float rightCurrentTime;

		float blendTimeTotal;
		float blendTimeLeft;
		bool blending;
		float currentAlpha;
	public:
		SkeletalAnimationBlender() : 
      pFirstSampler(0), pNextSampler(0), blending(false)
      { }

		~SkeletalAnimationBlender();

		void PlayFullSkeletalAnimation( SkeletalAnimationSampler *pAnimation )
		{
			NI_VERIFY( pAnimation, "Animation is null!", return );

			blending = false;
			pFirstSampler = pAnimation;
			pNextSampler = 0;
			blendTimeLeft = 0.f;
			currentAlpha = 0.f;
		}

		SkeletalAnimationSampler* GetFirstAnimationSampler() const { return pFirstSampler; }

		///
		void BlendTo( SkeletalAnimationSampler *pAnimation, float blendTime )
		{
			NI_VERIFY( pAnimation, "Animation is null!", return );

			if ( blending )
			{
				delete pFirstSampler;
				pFirstSampler = pNextSampler;
				pNextSampler = 0;
			}

			delete pNextSampler;
			pNextSampler = pAnimation;

			blending = true;
			blendTimeLeft = blendTime;
			blendTimeTotal = blendTime;
			currentAlpha = 0.f;
		}

		void Update( float delta, float absTime );

		float GetCurTime() const { return pFirstSampler->GetCurTime(); }
		float GetTotalTime() const { return pFirstSampler->GetTotalTime(); }

		void Update( float delta, float animFirstSpeed, float animNextSpeed, float curAlpha );
		void UpdateTime( float delta, float animFirstTime, float animNextTime, float curAlpha );

		void Sample( Matrix43* out );
	};
}; // 