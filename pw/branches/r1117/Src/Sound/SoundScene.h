#pragma once


namespace NDb
{
  enum Sound3DSimultType;
}

namespace FMOD
{
	class System;
}
namespace NSoundScene
{

  _interface ISimpleSound: public IObjectBase
  {
    virtual void Play() = 0;
  };

	// order in this enum also defines default the category priority, going from most to least important
	// TODO: rearrange them in the order that makes sense
	enum ESoundCategory
	{
		SOUNDCATEGORY_MUSIC, // streamed from disk
		SOUNDCATEGORY_INTERFACE, // regular 2d-sound
		SOUNDCATEGORY_VOICE, // streamed from disk
		SOUNDCATEGORY_AMBIENT,	// regular 3d-sound
    SOUNDCATEGORY_3D,	// regular 3d-sound
		SOUNDCATEGORY_EFFECT, // regular mono-sound

		SOUNDCATEGORY_COUNT // keep it last
	};

  /*
  enum ECacheStrategy {
		PRECACHE,   // precache and never unload
		SMART,      // unload if not used for some period of time
		SINGLE,     // play and unload 
	};
  */
	struct SoundDescription
	{
		string soundFilename;
    ESoundCategory category;
    NDb::Sound3DSimultType simultType;
		bool looped;

    SoundDescription();
  	SoundDescription( const string & _fileName, ESoundCategory _category, bool _looped,  NDb::Sound3DSimultType _type);
	};

	static int const INVALID_SOUND_ID = -1;
	static float const INVALID_MIN_MAX_DISTANCE = -1.0f;

	// system
	bool Init( FMOD::System *fmodSystem, int maxNumberOfSounds, float unitsInMeter );
  bool InitWithCreatingSystem( int maxNumberOfSounds, float unitsInMeter );
	void Release();
	void Update();
	void SetVolume( float volume );
	void Pause( bool pause );
	void Clear();
	void SetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up );
  CVec3 GetListenerPos( void );

	// sound
	// int AddAmbientSound( const string &_project, const string &_group, const string &_event, CVec3 const *_pPosition, const int objectId );
	int AddAmbientSound( const SoundDescription& soundDescription, CVec3 const &position, float* time, const int objectId  );
	int PlaySound( const SoundDescription& soundDescription, float* time );
	int PlaySound( const SoundDescription& soundDescription, float* time, float startPos );
	int PlaySound( const SoundDescription& soundDescription, CVec3 const &position, float* time );

  //raw data. in this case its up to u to free memory after it
  ISimpleSound * CreateSimpleSoundFromData(const vector<unsigned char> & soundData, int rate, bool isStereo, int bitsPerSample);
 
	//int PlaySound( const SoundDescription& soundDescription, CVec3 const &position, float* time, float startPos );
	void PauseSound( int soundId, bool pause );
	void MoveSound( int soundId, CVec3 const &position );
	void DeleteSound( int soundId );
	bool IsSoundPlay( int soundId );
	void SetSoundVolume( int soundId, float vol );
	void Set3DMinMaxDistance( int soundId, ESoundCategory _category );
	void SetMinMaxDistance( ESoundCategory _category, float _min, float _max );
	void SetLinear( int soundId );
	float GetTime( int soundId );

	// category
	void SetPriority( ESoundCategory category, int priority );
	void SetGroupVolume( ESoundCategory category, float volume );
	
	void TryTurnOnSound();
	void TryTurnOffSound();
}

