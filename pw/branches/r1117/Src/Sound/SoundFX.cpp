#include "stdafx.h"
#include "SoundFX.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NDebug::DebugVar<CVec3> sound_SoundFXPosition( "SoundFXPosition", "Sound" );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NSoundScene
{
#define SOUND_LOG( user_text )  { systemLog( NLogg::LEVEL_DEBUG ) <<"Sound: "<< user_text << endl; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundFX::Initialize( const Matrix43& _worldMatrix, const NDb::FMODEventInstance* _pDBPSoundInstance )
{

	worldMatrix = _worldMatrix;
	currentTime = 0.0f;
	oldTime = 0.0f;
	cycleCount = 200;
	durationTime = 10.f;
	if( _pDBPSoundInstance && _pDBPSoundInstance->fmodGroup.project)
	{
		eventDesc.eventName = _pDBPSoundInstance->name;
		eventDesc.groupName = _pDBPSoundInstance->fmodGroup.fmodGroup;
		eventDesc.projectName = _pDBPSoundInstance->fmodGroup.project->name;
		const CVec3 soundPosition( worldMatrix._14, worldMatrix._24, worldMatrix._34 );
		pEvent = NSoundScene::EventStart(eventDesc, &soundPosition);
	}
	else
	{
		SOUND_LOG("No Sound for this Event");
	}
	
	
// 	volume = _pDBPSoundInstance->volume;
// 	is3D = _pDBPSoundInstance->is3DSound;
// 	soundDesc.soundFilename = _pDBPSoundInstance->soundFile;
// 	
// 	soundDesc.category = is3D ? SOUNDCATEGORY_AMBIENT : SOUNDCATEGORY_MUSIC;
// 	soundDesc.looped = true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundFX::~SoundFX()
{
	//NSoundScene::EventStop( pEvent );

// 	if ( IsSoundPlay( soundIdx ) )
// 	{
// 		DeleteSound( soundIdx );
// 	}
}

void SoundFX::SetWorldMatrix( const Matrix43& transform )
{
	
	worldMatrix = transform;
	if(pEvent)
	{
		const CVec3 soundPosition( worldMatrix._14, worldMatrix._24, worldMatrix._34 );
		NSoundScene::SetEventPos( pEvent, &soundPosition);
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundFX::SetTime( float _time )
{
	float deltaTime = _time - lastTime;
	if(deltaTime < 0.001f) return;
	if( isInvalid )
		return;

	oldTime = currentTime;
	currentTime += deltaTime;

	const CVec3 soundPosition( worldMatrix._14, worldMatrix._24, worldMatrix._34 );
	sound_SoundFXPosition.SetValue( soundPosition );

	if ( cycleCount && _time > durationTime * cycleCount )
	{
		Stop();
	}

	if ( IsSoundPlay( soundIdx ) )
	{
		if ( is3D )
		{
			MoveSound( soundIdx, soundPosition );
		}
	}
	else if ( !cycleCount || _time < durationTime * cycleCount )
	{
		if ( is3D )
		{
			soundIdx = PlaySound( soundDesc, soundPosition, &durationTime );
			//cycleLength = durationTime - offset;
			SetLinear( soundIdx );
			Set3DMinMaxDistance(soundIdx, NSoundScene::SOUNDCATEGORY_EFFECT );
			SetSoundVolume( soundIdx, volume );
		}
		else
		{
			soundIdx = PlaySound( soundDesc, &durationTime );
			SetSoundVolume( soundIdx, volume );
		}
	}

	isInvalid = soundIdx == NSoundScene::INVALID_SOUND_ID;
	lastTime = _time;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundFX::Stop()
{
	//NSoundScene::EventStop( pEvent );
// 	if ( IsSoundPlay( soundIdx ) )
// 	{
// 		DeleteSound( soundIdx );
// 	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundFX::Play( float _time )
{
	if ( IsSoundPlay( soundIdx ) )
	{
		DeleteSound( soundIdx );
	}

	if ( _time < durationTime )
	{
		if ( is3D )
		{
			soundIdx = PlaySound( soundDesc, CVec3( worldMatrix._14, worldMatrix._24, worldMatrix._34 ), &durationTime, _time );
			SetLinear( soundIdx );
			Set3DMinMaxDistance(soundIdx, NSoundScene::SOUNDCATEGORY_EFFECT );
			SetSoundVolume( soundIdx, volume );
		}
		else
		{
			soundIdx = PlaySound( soundDesc, &durationTime, _time );
			SetSoundVolume( soundIdx, volume );
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NSoundScene