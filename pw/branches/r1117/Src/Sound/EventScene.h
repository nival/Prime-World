#pragma once
#include "DBSound.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace FMOD
{
	class Event;
  class EventGroup;
	class System;
}
namespace NDb
{
  struct SoundCamera;
  struct SoundEnvironment;
  struct DBFMODEventDesc;
  struct DBFMODSimpleEventDesc;
}

namespace NScene
{
struct IScene;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NSoundScene
{
  class FMODEvent
  {
  public:
    FMODEvent() : isValid(false), soundEvent(0) {}
    ~FMODEvent() {}

    void Init( const NDb::DBFMODEventDesc &_desc );
    bool IsVaild() const;
    FMOD::Event* GetEvent() const;
    bool PlaySound();
    bool IsAllreadyPlayed() const;
    bool Stop( bool immediately );
    void Release();
    float GetDuration( bool isNeedMultiLanguageLength = true );

  private:
    bool isValid;

    FMOD::Event *soundEvent;
    NDb::DBFMODEventDesc desc;
  };

  class FMODGroup
  {
  public:
    FMODGroup() : isValid(false), eventGroup(0) {}
    ~FMODGroup() {}

    void Init( const nstl::string & project, const nstl::string & category );
    bool IsValid() const;
    FMOD::EventGroup* GetGroup() const;
    void Release();

  private:
    bool isValid;
    FMOD::EventGroup *eventGroup;
  };


	extern threading::Mutex fmodMutex;

  FMOD::Event* GetEvent( const NDb::DBFMODEventDesc & eventDesc );
  FMOD::Event* GetEvent( FMOD::EventGroup *pGroup,const nstl::string & _event);

  bool ReleaseEvent(FMOD::Event *pEvent);

  FMOD::EventGroup* GetGroup(const nstl::string & project, const nstl::string & category);
  bool LoadGroupSamplesAndStreams(FMOD::EventGroup *pGroup);
  void UnloadGroup(FMOD::EventGroup *pGroup);

  bool PreCacheGroup( const nstl::string& groupName, bool loadEventData = false );
  void UnloadGroup( const nstl::string& groupName );

	FMOD::Event* EventStart( const NDb::DBFMODEventDesc& eventDesc, const CVec3& pPosition );
	FMOD::Event* EventStart( const NDb::DBFMODEventDesc& eventDesc );

  bool EventStart(FMOD::Event *pEvent);
  bool EventStart(FMOD::Event *pEvent,CVec3 const *_pPosition );
  bool EventStop( FMOD::Event *pEvent, bool immediatly = false );

  bool EventPause(FMOD::Event *pEvent,bool _pause);

  bool EventSetParameter(FMOD::Event *pEvent, const char *name, float value);

  bool IsEventPlaying(FMOD::Event *pEvent);
  bool IsEventPaused(FMOD::Event *pEvent);
  
  bool GetEventLength( FMOD::Event *pEvent, int &_lenght, bool isNeedMultiLanguageLength );

	bool SetEventPos( FMOD::Event * pEvent, const CVec3 * pPosition );
	
  FMOD::System* EventSystemInit( const NDb::SoundEnvironment *_pSoundEnvironment, int maxNumberOfSounds, float unitsInMeter );
  void SetScene( NScene::IScene* scene );
	void EventSystemUpdate( float dt );
  void EventSystemRelease( );
  void EventSystemSetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up, CVec3 const &anchor );

  void ActivateSoundScene( int idx, bool force );
  void InitSoundScene( int idx, const NDb::SoundSceneDesc& soundSceneDesc );
  int GetActiveSoundScene();

  void PlayMusic( const NDb::MusicDesc& music );
  void StopMusic();
  void PauseMusic();
  void UnPauseMusic();

  void SetHeartBeatData(const NDb::DBFMODEventDesc& _heartBeatDesc, const nstl::string& _heartBeatParamName);
  void EnableHeartBeat(bool enable);
  void PlayHeartBeat(bool play);
  void StartHeartBeat();
  void StopHeartBeat();
  void UpdateHeartBeat(float value);

  void SetAmbientData(const NDb::DBFMODEventDesc& _ambientSoundDesc);
  void EnableAmbient(bool enable);
  void StartAmbient();
  void StopAmbient();
  void UpdateAmbient(const nstl::string& paramName, float paramValue);

  void SetMusicVolume( float volume );
  void SetSoundVolume( float volume );
  void SetMusicMultiplier( float multiplier );

  void ApplyReverb( nstl::string& presetName );
  void SetGlobalPitchCoeff( float val );

  void UpdateVolumes( float soundVol, float musicVol, float voiceVol, float commonVol );

  void SystemStop();
  void SystemResume();

  FMODEvent* CreateFMODEvent();
  void ReleaseFMODEvent( FMODEvent* fmodEvent );

  FMODGroup* CreateFMODGroup();
  void ReleaseFMODGroup( FMODGroup* fmodGroup );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
