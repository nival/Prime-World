#include "stdafx.h"
#include "SkeletalAnimationSampler.h"

namespace Render
{
	static const float FPS = 30.0f;

	template <typename T>
	static void GetIndexAndAlpha( const T& track, float currentTime, int* prevIdx, int* nextIdx, float* alpha )
	{
		*prevIdx = (int)(currentTime*FPS) % track.trackData.size();
		*nextIdx = (*prevIdx + 1) % track.trackData.size();

		*alpha = currentTime*FPS - (int)(currentTime*FPS);
	}

	void SkeletalAnimationSampler::GetRotation( unsigned int boneIndex, CQuat& rotation )
	{
		const TBoneRotationTrack& track = pSkeletalAnimationData->GetData()->tracks[boneIndex].rotationTrack;

		if ( track.trackData.size() == 1 )
		{
			rotation = track.trackData[0];
			return;
		}

		int prevIndex = 0;
		int nextIndex = 0;
		float alpha = 0.0f;

		GetIndexAndAlpha( track, currentTime, &prevIndex, &nextIndex, &alpha );

		rotation.Slerp( alpha, track.trackData[prevIndex], track.trackData[nextIndex] );
	}

	void SkeletalAnimationSampler::GetTranslation( unsigned int boneIndex, CVec3& translation )
	{
		const TBonePositionTrack& track = pSkeletalAnimationData->GetData()->tracks[boneIndex].positionTrack;

		if ( track.trackData.size() == 1 )
		{
			translation = track.trackData[0];
			return;
		}

		int prevIndex = 0;
		int nextIndex = 0;
		float alpha = 0.0f;

		GetIndexAndAlpha( track, currentTime, &prevIndex, &nextIndex, &alpha );

		translation = Lerp( track.trackData[prevIndex], track.trackData[nextIndex], alpha );
	}

	void SkeletalAnimationSampler::GetScale( unsigned int boneIndex, CVec3& scale )
	{
		const TBoneScaleTrack& track = pSkeletalAnimationData->GetData()->tracks[boneIndex].scaleTrack;

		if ( track.trackData.size() == 1 )
		{
			scale = track.trackData[0];
			return;
		}

		int prevIndex = 0;
		int nextIndex = 0;
		float alpha = 0.0f;

		GetIndexAndAlpha( track, currentTime, &prevIndex, &nextIndex, &alpha );

		scale = Lerp( track.trackData[prevIndex], track.trackData[nextIndex], alpha );
	}

	void SkeletalAnimationSampler::SetVPar( float rVPar )
	{
		NI_VERIFY(0.0f <= rVPar && rVPar <= 1.0f, "Invalid animation time!", currentTime = pSkeletalAnimationData->GetData()->minTime;);
		float length = GetTotalTime();
		float rT = pSkeletalAnimationData->GetData()->minTime;
		rT += length * rVPar;
		SetTime(rT);
	}

	void SkeletalAnimationSampler::SetTime( float time )
	{
		NI_VERIFY( time >= pSkeletalAnimationData->GetData()->minTime, "Invalid animation time!", currentTime = pSkeletalAnimationData->GetData()->minTime; return; );
		const float maxTime = GetTotalTime();
		if ( maxTime < FP_EPSILON )
			currentTime = 0.0f;
		else
		{
			//VLADIK: is time = fmodf(time, maxTime); really meant here?
			while ( time > maxTime )
				time -= maxTime;
			currentTime = time;
		}
	}
}