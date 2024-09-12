#pragma once
#include "SoundScene.h"
#include "EventScene.h"

namespace NSoundScene
{
	class SoundFX
	{
		SoundDescription soundDesc;
		EventDescription eventDesc;
		FMOD::Event * pEvent;
		int soundIdx;

		float oldTime;
		float currentTime;
		Matrix43 worldMatrix;

		int cycleCount;

		float durationTime;

		float volume;
		float minDist;
		float maxDist;

		float lastTime;

		bool is3D;
		bool isInvalid;

	public:

		SoundFX() { isInvalid = false; pEvent = 0;};
		~SoundFX();
		void Initialize( const Matrix43& _worldMatrix, const NDb::FMODEventInstance* _pDBPSoundInstance );

		float GetTotalTime() const { return durationTime; }
		void SetTime( float _time );
		void Stop();
		void Play( float _time );

		void SetWorldMatrix( const Matrix43& transform );// { worldMatrix = transform; }
		const Matrix43& GetWorldMatrix() const { return worldMatrix; }
	};
}