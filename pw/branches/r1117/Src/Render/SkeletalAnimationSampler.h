#pragma once

#include "../MeshConverter/SkeletalAnimationHeader.h"
#include "../System/lerp.h"

namespace Render
{
	class SkeletalAnimationSampler
	{
		const SkeletalAnimationDataWrapper* pSkeletalAnimationData;
		float currentTime;
		float startTime;

	public:
		SkeletalAnimationSampler( float _startTime, const SkeletalAnimationDataWrapper* pAnimationData ) 
			: pSkeletalAnimationData( pAnimationData ), startTime( _startTime ), currentTime(0)
		{
			NI_VERIFY( pSkeletalAnimationData && pSkeletalAnimationData->GetData(), "Invalid pointer to SkeletalAnimationData is null; constructor crashed :)", return );
			NI_VERIFY( GetJointsCount() >= 0, "No bones in animation", return );
		}

		float GetTotalTime() const { return pSkeletalAnimationData->GetData()->maxTime - pSkeletalAnimationData->GetData()->minTime; }
		float GetStartTime() const { return startTime; }
		float GetEndTime() const { return GetStartTime()+GetTotalTime(); }
		float GetCurTime() const { return currentTime; }

		void Update( float delta )
		{
			//SetTime( currentTime + delta );
		}

		void SetTime(float time);

		float GetVPar()
		{
			float maxTime = GetTotalTime();
			return (GetCurTime()-GetStartTime())/(maxTime - pSkeletalAnimationData->GetData()->minTime);
		}

		void SetVPar(float rVPar);

		bool IsBoneActive( unsigned int boneIndex) const
		{
			return pSkeletalAnimationData->GetData()->tracks[boneIndex].IsActive();
		}

		void GetRotation( unsigned int boneIndex, CQuat& rotation );

		void GetTranslation( unsigned int boneIndex, CVec3& translation );

		void GetScale( unsigned int boneIndex, CVec3& scale );

		void Sample( Matrix43* out )
		{
			NI_VERIFY(out, "pointer is null!", return );
			unsigned int bonesCount = GetJointsCount();
			for ( unsigned int i = 0; i < bonesCount; i++ )
			{
				CQuat rotation;
				GetRotation( i, rotation );
				CVec3 translation;
				GetTranslation( i, translation );
				CVec3 scale;
				GetScale( i, scale );

				out[i].Set( rotation, translation, scale );
			}
		}

		unsigned int GetJointsCount() const
		{
			return pSkeletalAnimationData->GetData()->GetJointsCount(); 
		}
	};
}; // namespace Render
