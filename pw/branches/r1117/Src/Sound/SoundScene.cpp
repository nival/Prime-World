#include "stdafx.h"
#include "soundscene.h"
#include "../Scene/DBScene.h"
#include "../Render/DBRender.h"
#include "../Sound/SoundUI.h"
// this should come first as it's being used later on down the page
// it couldn't be joined with the rest of the namespace hanging below


namespace NSoundScene
{

struct SoundInfo
{
	string filename;
	bool isLooped;
	bool is3d;
	bool isStream;
	
	bool operator ==( SoundInfo const &that ) const
	{
		return filename == that.filename && isLooped == that.isLooped && is3d == that.is3d && isStream == that.isStream;
	}
};

SoundDescription::SoundDescription()
: category( SOUNDCATEGORY_AMBIENT )
, looped( false )
, simultType( NDb::SOUND3DSIMULTTYPE_INFINITE )
{}

SoundDescription::SoundDescription( const string & _fileName, ESoundCategory _category, bool _looped, NDb::Sound3DSimultType _type ) : soundFilename( _fileName )
, category( _category )
, looped( _looped )
, simultType( _type )
{

}
}

// this has to be defined within nstl namespace, that's why namespaces are kind of interleaved here
namespace nstl
{

template<> struct hash<NSoundScene::SoundInfo> 
{
	size_t operator ()( NSoundScene::SoundInfo const &key ) const
	{
		return ((__stl_hash_string( key.filename.c_str() ) * 5 + static_cast<size_t>(key.isLooped)) * 7 + 
			static_cast<size_t>(key.is3d)) * 11 + static_cast<size_t>(key.isStream);
	}
};

}


namespace NSoundScene
{

	struct MinMaxDistance
	{
		MinMaxDistance( float _minDistance, float _maxDistance ) : maxDistance(_maxDistance), minDistance(_minDistance) {}
		MinMaxDistance() : maxDistance(INVALID_MIN_MAX_DISTANCE), minDistance(INVALID_MIN_MAX_DISTANCE) {}
		float minDistance;
		float maxDistance;
	};

class SoundMap {
	typedef hash_map<SoundInfo, FMOD::Sound *> SoundMapItems;
	SoundMapItems items;
public:
	inline FMOD::Sound *find(const SoundInfo& info) {
		SoundMapItems::iterator soundIterator = items.find( info );
		if ( soundIterator == items.end() ) { 
			return 0;
		}
		return soundIterator->second;
	}

	inline FMOD::Sound *& operator [] (const SoundInfo& key) {
		return items[key];
	}

	inline void erase(FMOD::Sound * pSound) {
		// find and delete sound from the map (for single-shot sounds only)
		for ( SoundMapItems::iterator i = items.begin(); i != items.end(); ++i )
		{
			if ( i->second == pSound )
			{
				items.erase( i );
				break;
			}
		}
	}
};

// sound pool
// @IgorKaa: remove to uniq file
#define SOUND3DSIMULTTYPE_COUNT NDb::SOUND3DSIMULTTYPE_INFINITE
static const int g_maxSimilarSound3d[SOUND3DSIMULTTYPE_COUNT] = {128, 128, 128};

class Sound3DPool
{
public:
  Sound3DPool();
  ~Sound3DPool();
  bool IsFreeSpace(NDb::Sound3DSimultType type);
  void AddSound(NDb::Sound3DSimultType type, int ID);
  void RemoveSound(int ID);
private:
  int counts[SOUND3DSIMULTTYPE_COUNT];
  vector<int> IDs[SOUND3DSIMULTTYPE_COUNT];
};

Sound3DPool::Sound3DPool()
{
  for (int type = 0; type < SOUND3DSIMULTTYPE_COUNT; ++type)
  {
    counts[type] = 0;
    IDs[type].resize(g_maxSimilarSound3d[type], INVALID_SOUND_ID);
  }
}

Sound3DPool::~Sound3DPool()
{
  for (int type = 0; type < SOUND3DSIMULTTYPE_COUNT; ++type)
  {
    counts[type] = 0;
    IDs[type].resize(0);
  }
}


bool Sound3DPool::IsFreeSpace(NDb::Sound3DSimultType type)
{
  if ((type < 0) || (type >= SOUND3DSIMULTTYPE_COUNT))
    return false;

  return g_maxSimilarSound3d[type] > counts[type];
}

void Sound3DPool::AddSound(NDb::Sound3DSimultType type, int ID)
{
  if ((type < 0) || (type >= SOUND3DSIMULTTYPE_COUNT))
    return;

  int i;
  for (i = 0; i < g_maxSimilarSound3d[type]; ++i)
    if (INVALID_SOUND_ID == IDs[type][i])
      break;

  if (g_maxSimilarSound3d[type] == i)
  {
    NI_ASSERT( false, "No enough space in pool to add sound" );
    return;
  }

  IDs[type][i] = ID;
  counts[type]++;
}

void Sound3DPool::RemoveSound(int id)
{
  if (INVALID_SOUND_ID == id)
    return;

  // search ID for all pool
  for (int type = 0; type < SOUND3DSIMULTTYPE_COUNT; ++type)
  {
    int i;
    for (i = 0; i < g_maxSimilarSound3d[type]; ++i)
      if (id == IDs[type][i])
        break;

    if (g_maxSimilarSound3d[type] > i)
    {
      NI_ASSERT( counts[type] > 0, "some sound3D logic error!!" );
      
      IDs[type][i] = INVALID_SOUND_ID;
      counts[type]--;

      break;
    }
  }

}

static Sound3DPool g_Sound3DPool;

inline int GetRefCount( FMOD::Sound * pSound )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	int refCount = 0;
	pSound->getUserData( reinterpret_cast<void **>(&refCount) ); // refCount is stored as void *
	return refCount;
}

int SetRefCount(FMOD::Sound * pSound, int refCount)
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	pSound->setUserData( reinterpret_cast<void *>(refCount) ); // refCount is stored as void *
	return refCount;
}

int AddRefCount(FMOD::Sound * pSound, int delta=1)
{
	int refCount = GetRefCount(pSound);
	return SetRefCount(pSound, refCount+delta);
}

int DecRefCount(FMOD::Sound * pSound) 
{
	return AddRefCount(pSound, -1);
}

typedef hash_map<int, FMOD::Channel *> ChannelMap;
//typedef hash_map<int, int> SoundMap;
	
// settings
static float _soundSceneToFmodUnitConversionRatio = 1.0f;
static int _catergoryPriorities[SOUNDCATEGORY_COUNT] = { 0, 0, 0, 0 };

// other locals
static FMOD::System *g_pSystem = 0;
static FMOD::ChannelGroup *g_pMasterGroup = 0;
static FMOD::ChannelGroup *g_pGroups[SOUNDCATEGORY_COUNT] = { 0, 0, 0, 0 };
static FMOD_VECTOR g_listenerPosition = { 0, 0, 0 };
static FMOD_VECTOR g_listenerForward = { 0, 0, 0 };
static FMOD_VECTOR g_listenerUp = { 0, 0, 0 };

// sounds, this holds all unique waveform data objects
static SoundMap g_sounds;
static MinMaxDistance maxMinDistance[ SOUNDCATEGORY_COUNT ];

// this is a list of non-looping sounds playing, it's an optimization since
// there probably will be thousands of looping sounds which should not be checked
// every frame for their playback status
static ChannelMap g_channels;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SoundMap soundMap;

// list of looping sounds
static ChannelMap g_loopedChannels;

static FMOD_MODE g_hwmode;

// next handle to use with _channels and _loopedChannels maps
// for looped sounds upper bit is set to 1
static int g_nextChannelHandle = 1;

static bool ok( FMOD_RESULT result )
{
	//NI_ASSERT( result == FMOD_OK, FMOD_ErrorString( result ) );
	return result == FMOD_OK;
}

// fmod memory hooks, could be used to set breakpoints in them or log memory operations
#ifdef SoundSceneMemoryHooks
static void *F_CALLBACK memoryAllocate( unsigned int size, FMOD_MEMORY_TYPE type )
{
	return malloc( size );
}

static void F_CALLBACK memoryFree( void *pBlock, FMOD_MEMORY_TYPE type )
{
	free( pBlock );
}

static void *F_CALLBACK memoryReallocate( void *pBlock, unsigned int size, FMOD_MEMORY_TYPE type )
{
	return realloc( pBlock, size );
}
#endif

//map fmod i/o to nival stream i/o (open file)
static FMOD_RESULT F_CALLBACK fileOpen( const char *pName, int unicode, unsigned int *pFileSize, void **pHandle, 
	void **pUserData )
{
	NI_ASSERT( !unicode, "Unicode is not supported in SoundScene file system" );

	Stream *pStream = RootFileSystem::OpenFile( pName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	if ( pStream == 0 || !pStream->IsOk() )
	{
		delete pStream;
		return FMOD_ERR_FILE_NOTFOUND;
	}

	*pFileSize = pStream->GetSize();
	*pHandle = pStream;
	*pUserData = 0;

	return FMOD_OK;
}

//map fmod i/o to nival stream i/o (close file)
static FMOD_RESULT F_CALLBACK fileClose( void *pHandle, void *pUserData )
{
	if ( pHandle == 0 )
	{
		return FMOD_ERR_INVALID_PARAM;
	}

	delete static_cast<Stream *>(pHandle); // handle passed to/from callback as void

	return FMOD_OK;
}

// map fmod i/o to nival stream i/o (read file)
static FMOD_RESULT F_CALLBACK fileRead( void *pHandle, void *pBuffer, unsigned int sizeBytes, unsigned int *pBytesRead, 
	void *pUserData )
{
	if ( pHandle == 0 )
	{
		return FMOD_ERR_INVALID_PARAM;
	}

	Stream *pStream = static_cast<Stream *>(pHandle); // handle passed to/from callback as void
	*pBytesRead = pStream->Read( pBuffer, sizeBytes );

	return *pBytesRead < sizeBytes ? FMOD_ERR_FILE_EOF : FMOD_OK;
}

// map fmod i/o to nival stream i/o (seek file)
static FMOD_RESULT F_CALLBACK fileSeek( void *pHandle, unsigned int pos, void *pUserData )
{
	if ( pHandle == 0 )
	{
		return FMOD_ERR_INVALID_PARAM;
	}

	Stream *pStream = static_cast<Stream *>(pHandle); // handle passed to/from callback as void
	pStream->Seek( pos, SEEKORIGIN_BEGIN );

	return FMOD_OK;
}

static FMOD_RESULT result = FMOD_OK;

// init the whole shebang
bool Init( FMOD::System *_fmodSystem, int maxNumberOfSounds, float unitsInMeter )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  if ( !_fmodSystem )
    return false;
#ifdef SoundSceneMemoryHooks
	FMOD::Memory_Initialize( 0, 0, memoryAllocate, memoryReallocate, memoryFree );
#endif

	g_pSystem = _fmodSystem;

  // create channel groups to control volume
  for ( int i = 0; i < SOUNDCATEGORY_COUNT; ++i )
  {
    _catergoryPriorities[i] = 0;
    g_pSystem->createChannelGroup( 0, g_pGroups + i );
    g_pMasterGroup->addGroup( g_pGroups[i] );
  }

  systemLog( NLogg::LEVEL_DEBUG ) << "FMOD Init OK" << endl;

	return true;

}


bool InitWithCreatingSystem( int maxNumberOfSounds, float unitsInMeter )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

#ifdef SoundSceneMemoryHooks
  FMOD::Memory_Initialize( 0, 0, memoryAllocate, memoryReallocate, memoryFree );
#endif

  // create fmod system
  if ( !ok( FMOD::System_Create( &g_pSystem ) ) )
  {
    g_pSystem = 0;
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't create FMOD::System" << endl;
    return false;
  }

  // check installed fmod version
  unsigned int version;
  if ( !ok( g_pSystem->getVersion( &version ) ) )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't get FMOD Version" << endl;
    g_pSystem = 0;
    return false;
  }

  if ( version < FMOD_VERSION )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Bad FMOD Version" << endl;
    g_pSystem = 0;
    return false;
  }

  FMOD_CAPS        caps;

  if ( !ok( g_pSystem->getDriverCaps(0, &caps, 0, 0) ) )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't get FMOD Caps" << endl;
    g_pSystem = 0;
    return false;
  }

  if ( caps & FMOD_CAPS_HARDWARE )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "FMOD Hardware" << endl;
    g_hwmode |= FMOD_HARDWARE;
  }
  else
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "FMOD Software" << endl;
    g_hwmode |= FMOD_SOFTWARE;
  }	

  if ( !ok( g_pSystem->setDSPBufferSize(1024, 5) ) )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't set FMOD buffer" << endl;
    g_pSystem = 0;
    return false;
  }

  if ( !ok( g_pSystem->setStreamBufferSize(2*128*1024, FMOD_TIMEUNIT_RAWBYTES) ) )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't set FMOD buffer" << endl;
    g_pSystem = 0;
    return false;
  }

  result = g_pSystem->init( maxNumberOfSounds, FMOD_INIT_3D_RIGHTHANDED, 0 );
  if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
  {
    g_pSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
    result = g_pSystem->init( maxNumberOfSounds, FMOD_INIT_3D_RIGHTHANDED, 0 );
  } 

  // initialized fmod system
  if ( !ok(result) )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't Init FMOD" << endl;
    g_pSystem = 0;
    return false;
  }

  // set unit scale
  g_pSystem->set3DSettings( 1.0f, unitsInMeter, 1.0f );

  // num of listeners
  g_pSystem->set3DNumListeners(1);

  // set file callbacks
  FMOD_RESULT hr = g_pSystem->setFileSystem( fileOpen, fileClose, fileRead, fileSeek, 0, 0, 4096 );
  if (!ok(hr)) 
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't set file system" << endl;
    g_pSystem = 0;
    return false;
  }

  // acquire master channel group
  if ( !ok( g_pSystem->getMasterChannelGroup( &g_pMasterGroup ) ) )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Can't get FMOD Master Chanel" << endl;
    g_pSystem = 0;
    return false;
  }

  // create channel groups to control volume
  for ( int i = 0; i < SOUNDCATEGORY_COUNT; ++i )
  {
    _catergoryPriorities[i] = 0;
    g_pSystem->createChannelGroup( 0, g_pGroups + i );
    g_pMasterGroup->addGroup( g_pGroups[i] );
  }

  systemLog( NLogg::LEVEL_DEBUG ) << "FMOD Init OK" << endl;

  return true;
}

// shutdown everything
void Release()
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	Clear();

	// destroy fmod system
	if ( g_pSystem != 0 )
	{
		g_pSystem->release();
		g_pSystem = 0;
	}

}
// update, should be called every frame
void Update()
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  if (!g_pSystem)
    return;

	// remove finished sounds
	for ( ChannelMap::iterator i = g_channels.begin(); i != g_channels.end(); )
	{
		bool playing;
		i->second->isPlaying( &playing );
		
		if ( !playing )
		{
      int id = (i++)->first;
			// update pool( delete sound if needed)
      g_Sound3DPool.RemoveSound( id );

      // delete sound
			DeleteSound( id );
		}
		else
		{
			++i;
		}
	}
	NI_VERIFY( result == FMOD_OK, "SoundEvent ogogo!", return);

  // @IgorKaa hack: sound starts playing ONLY after listener change position
  // see FMOD\example\3D: stop listener & pause/unpause any sounds
  //FMOD_VECTOR zero = { 0, 0, 0 };
  //g_pSystem->set3DListenerAttributes( 0, &zero, 0, 0, 0 );
  //g_pSystem->set3DListenerAttributes( 0, &g_listenerPosition, 0, &g_listenerForward, &g_listenerUp );
	g_pSystem->update();
}

// set global volume
void SetVolume( float volume )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	// simply change volume on the master channel group
	g_pMasterGroup->setVolume( ClampFast( volume, 0.0f, 1.0f ) );
}

// global pause/unpause
void Pause( bool pause )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	// simply pause the master channel group
	g_pMasterGroup->setPaused( pause );
}

// stop (if needed) and remove all sounds from the system
void Clear()
{
	ChannelMap *pMaps[] = {&g_channels, &g_loopedChannels};

	for ( int i = 0; i < 2; ++i )
	{
		while ( !pMaps[i]->empty() )
		{
			DeleteSound( pMaps[i]->begin()->first );
		}
	}
}

// update listener position and orientation
void SetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up )
{
	// store for later, it's updates from NSoundScene::Update
	g_listenerPosition.x = position.x;
	g_listenerPosition.y = position.y;
	g_listenerPosition.z = position.z;

	g_listenerForward.x = forward.x;
	g_listenerForward.y = forward.y;
	g_listenerForward.z = forward.z;

	g_listenerUp.x = up.x;
	g_listenerUp.y = up.y;
	g_listenerUp.z = up.z;
}

CVec3 GetListenerPos( void )
{
  CVec3 pos;

  pos.x = g_listenerPosition.x;
  pos.y = g_listenerPosition.y;
  pos.z = g_listenerPosition.z;

  return pos;
}


static int getNextHandle( bool isLooped )
{
	return g_nextChannelHandle++ | (isLooped ? 0x80000000 : 0);
}

static bool isLoopedHandle( int handle )
{
	return (handle & 0x80000000) != 0;
}

static ChannelMap &getChannelMap( int handle )
{
	return isLoopedHandle( handle ) ? g_loopedChannels : g_channels;
}

static FMOD::Channel *getChannel( int handle )
{
	ChannelMap &channels = getChannelMap( handle );
	ChannelMap::iterator channelIterator = channels.find( handle );
	return channelIterator == channels.end() ? 0 : channelIterator->second;
}

int GetSound(FMOD::Sound ** sound, const SoundDescription &soundDescription, CVec3 const * pPosition, float startPos )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  SoundInfo info;
  info.filename = soundDescription.soundFilename;
  info.is3d = pPosition != 0;
  info.isLooped = soundDescription.looped;
  info.isStream = (soundDescription.category == SOUNDCATEGORY_MUSIC || soundDescription.category == SOUNDCATEGORY_VOICE);

  *sound = g_sounds.find( info );
  if ( !sound ) // sound needs to be created
  {
    // flags
    FMOD_MODE mode = FMOD_DEFAULT;
    if ( info.is3d )
    {
      mode |= FMOD_3D;
    }
    if ( info.isStream )
    {
      mode |= FMOD_CREATESTREAM;
    }

    if ( info.isStream )
    {
      int handle = getNextHandle( info.isLooped );
      FMOD::Channel *&pChannel	= (info.isLooped ? g_loopedChannels : g_channels)[handle];
      FMOD_MODE mode = g_hwmode | ( info.isLooped ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF ) | FMOD_2D;
      FMOD_RESULT hr = g_pSystem->createStream(soundDescription.soundFilename.c_str(), mode, 0, sound);
      if (!ok(hr)) {
        return INVALID_SOUND_ID;
      }

      g_pSystem->playSound(FMOD_CHANNEL_FREE, *sound, false, &pChannel);
      pChannel->setPosition( startPos*1000.f, FMOD_TIMEUNIT_MS );
      AddRefCount(*sound);

      g_sounds[info] = *sound;
      pChannel->setChannelGroup( g_pGroups[soundDescription.category] );
      pChannel->setPriority( _catergoryPriorities[soundDescription.category] * SOUNDCATEGORY_COUNT + soundDescription.category );
      return handle;
    }
    else
    {
      // create a sound
      FMOD_RESULT rez = g_pSystem->createSound( info.filename.c_str(), mode, 0, sound );
      if ( rez != FMOD_OK )
      {
        NI_VERIFY( rez != FMOD_ERR_FORMAT, NStr::StrFmt( "FMOD_ERR_FORMAT: %s (Unsupported file or audio format)!", info.filename.c_str() ),return INVALID_SOUND_ID)
          return INVALID_SOUND_ID;
      }
    }

    // set looping mode
    (*sound)->setMode( info.isLooped ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF );

    // reset ref count and add to the map (for single-shot sounds only)
    (*sound)->setUserData( 0 );
    if ( !info.isStream )
    {
      g_sounds[info] = *sound;
    }
  }
  
  return 0;
}

int PlaySoundWithSource( FMOD::Sound * pSound, bool isLooped, float startPos, ESoundCategory category, CVec3 const * pPosition = 0,  float* pTime =0  )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  if ( pTime )
  {
    unsigned int timems;
    pSound->getLength( &timems, FMOD_TIMEUNIT_MS );
    *pTime = (float)timems / 1000.f;
  }

  int handle = getNextHandle( isLooped );
  FMOD::Channel *&pChannel	= (isLooped ? g_loopedChannels : g_channels)[handle];

  // start playing sound (initially paused)
  g_pSystem->playSound( FMOD_CHANNEL_FREE, pSound, true, &pChannel );
  pChannel->setPosition( startPos*1000.f, FMOD_TIMEUNIT_MS );

  // add ref
  AddRefCount(pSound);
  // put channel into corresponding group
  pChannel->setChannelGroup( g_pGroups[category] );

  // and set priority which is based on value set by user with SetPriority
  // if categories have the same priority then it's based on category id
  pChannel->setPriority( _catergoryPriorities[category] * SOUNDCATEGORY_COUNT + category );

  // position sound if it's 3d
  if ( pPosition != 0)
  {
    MoveSound( handle, *pPosition );
  }

  // unpause
  pChannel->setPaused( false );

  return handle;
}


// internal version of PlaySound, it does everything
static int playSound( const SoundDescription& soundDescription, CVec3 const *pPosition, float* pTime, float startPos )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  FMOD::Sound * pSound;
  if (FMOD_OK!=GetSound(&pSound, soundDescription, pPosition, startPos))
    return INVALID_SOUND_ID;

  return PlaySoundWithSource(pSound, soundDescription.looped, startPos, soundDescription.category, pPosition, pTime);
}

// int AddAmbientSound( const string &_project, const string &_group, const string &_event, CVec3 const *_pPosition, const int objectId )
// {
// 	return EventStart( _project, _group, _event, _pPosition );
// }
int AddAmbientSound( const SoundDescription& soundDescription, CVec3 const &position, float* time, const int objectId  )
{
// 	SoundMap::const_iterator it = soundMap.find(objectId);
// 	if( it == soundMap.end())
// 	{
// 		soundMap[objectId]=PlaySound( soundDescription, position, time );
// 		Set3DMinMaxDistance( soundMap[objectId], SOUNDCATEGORY_EFFECT );
// 		SetLinear( soundMap[objectId] );
// 		return soundMap[objectId];
// 	}
	return INVALID_SOUND_ID;
}
// play 2d sound
int PlaySound( const SoundDescription& soundDescription, float* time )
{
	return playSound( soundDescription, 0, time, 0.f );

}
// play 2d sound
int PlaySound( const SoundDescription& soundDescription, float* time, float startPos )
{
	return playSound( soundDescription, 0, time, startPos );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// play 3d sound
int PlaySound( SoundDescription const &soundDescription, CVec3 const &position, float* time )
{
	//systemLog( NLogg::LEVEL_DEBUG ) << "PlaySound position:" <<position.x <<", " << position.y <<", "<< position.z << endl;

  int soundID = INVALID_SOUND_ID;

  if (SOUND3DSIMULTTYPE_COUNT == soundDescription.simultType)
    return playSound( soundDescription, &position, time, 0.f );

  // check free space in corresponded pool
  bool free = g_Sound3DPool.IsFreeSpace(soundDescription.simultType);

  if (free)
    soundID = playSound( soundDescription, &position, time, 0.f );

  if (INVALID_SOUND_ID != soundID)
  {
    // add sound to pool
    g_Sound3DPool.AddSound(soundDescription.simultType, soundID);
  }

  return soundID;
}

// play 3d sound

/*int PlaySound( SoundDescription const &soundDescription, CVec3 const &position, float* time, float startPos )
{
	
	return playSound( soundDescription, &position, time, startPos );
} */

// pause sound
void PauseSound( int soundId, bool pause )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		return;
	}
	
	FMOD::Channel *pChannel = getChannel( soundId );
	NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );

	pChannel->setPaused( pause );
}

// set volume sound
void SetSoundVolume( int soundId, float vol )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		return;
	}

	FMOD::Channel *pChannel = getChannel( soundId );
	NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );

	pChannel->setVolume( vol );
}

// set volume sound
float GetTime( int soundId )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		NI_ALWAYS_ASSERT("bad sound");
		return 0.f;
	}

	FMOD::Channel *pChannel = getChannel( soundId );
	NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return 0.f );

	unsigned int value;
	pChannel->getPosition( &value, FMOD_TIMEUNIT_MS );
	return (float)value / 1000.f;
}

// move 3d sound in the world
void MoveSound( int soundId, CVec3 const &position )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  NI_ALWAYS_ASSERT("obsolette");

	if ( soundId == INVALID_SOUND_ID )
	{
		return;
	}

	FMOD::Channel *pChannel = getChannel( soundId );
	NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );
	
	FMOD_VECTOR fmodPosition = { position.x, position.y, position.z };
	pChannel->set3DAttributes( &fmodPosition, 0 );
}

bool IsSoundPlay( int soundId )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		return false;
	}

	FMOD::Channel *pChannel = getChannel( soundId );
	if ( pChannel )
	{
		return true;
	}

	return false;
}

// stop (if needed) and delete sound from the system
void DeleteSound( int soundId )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		return;
	}

	// find channel
	ChannelMap &channels = getChannelMap( soundId );
	ChannelMap::iterator channelIterator = channels.find( soundId );
	NI_VERIFY( channelIterator != channels.end(), "Invalid sound handle provided", return );
	FMOD::Channel *pChannel = channelIterator->second;

	// get associated sound
	FMOD::Sound *pSound = 0;
	pChannel->getCurrentSound( &pSound );

	// stop and remove channel
	pChannel->stop();
	channels.erase( soundId );

	// then we need to check if sound needs to be deleted as well
	if ( !pSound )
		return;
	NI_VERIFY( pSound != 0, "Internal error, sound should not be 0", return );

	int refCount = DecRefCount(pSound);
	if ( refCount == 0 )
	{
		g_sounds.erase(pSound);
		// kill sound
		pSound->release();
	}
}

// set priority for specific category
// priority should be within [0, 256 / SOUNDCATEGORY_COUNT - 1] (fmod limitation on priority)
void SetPriority( ESoundCategory category, int priority )
{
	NI_VERIFY( category >= 0 && category < SOUNDCATEGORY_COUNT, "Category is out of range", return );
	NI_VERIFY( priority >= 0 && priority * SOUNDCATEGORY_COUNT + category <= 256, "Priority is out of range", return );

	_catergoryPriorities[category] = priority;
}

// set volume for specific category
void SetGroupVolume( ESoundCategory category, float volume )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	NI_VERIFY( category >= 0 && category < SOUNDCATEGORY_COUNT, "Category is out of range", return );
	g_pGroups[category]->setVolume( ClampFast( volume, 0.0f, 1.0f ) );
}

void SetMinMaxDistance( ESoundCategory _category, float _min, float _max )
{
	if( _category < SOUNDCATEGORY_COUNT )
	{
		maxMinDistance[ _category ] = MinMaxDistance( _min, _max );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Set3DMinMaxDistance( int soundId, ESoundCategory _category )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		return;
	}

	FMOD::Channel *pChannel = getChannel( soundId );
	NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );
	NI_VERIFY( maxMinDistance[_category].minDistance != INVALID_MIN_MAX_DISTANCE && maxMinDistance[_category].maxDistance != INVALID_MIN_MAX_DISTANCE, "Invalid min max Distance", return );

	if ( !ok( pChannel->set3DMinMaxDistance( maxMinDistance[_category].minDistance, maxMinDistance[_category].maxDistance ) ) )
	{
		NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );
	}
// 	for( SoundMap::iterator it = soundMap.begin(); it != soundMap.end(); ++it )
// 	{
// 		FMOD::Channel *pChannel = getChannel( soundId );
// 		if ( !ok( pChannel->set3DMinMaxDistance( maxMinDistance[_category].minDistance, maxMinDistance[_category].maxDistance ) ) )
// 		{
// 			NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );
// 		}
// 		float  mindistance;
// 		float  maxdistance;
// 		pChannel->get3DMinMaxDistance(
// 			&mindistance, 
// 			&maxdistance
// 			);
// 
// 		mindistance = maxdistance;
// 	}
}

void SetLinear( int soundId )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	if ( soundId == INVALID_SOUND_ID )
	{
		return;
	}

	FMOD::Channel *pChannel = getChannel( soundId );
	NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );

	if ( !ok( pChannel->setMode( FMOD_3D_LINEARROLLOFF ) ) )
	{
		NI_VERIFY( pChannel != 0, "Invalid sound handle provided", return );
	}
}

class SimpleSound: public ISimpleSound, public CObjectBase
{
  OBJECT_BASIC_METHODS(SimpleSound)
  SimpleSound() {}

  FMOD::Sound * sound;

public:

 SimpleSound(FMOD::Sound * _sound):sound(_sound) {}

 virtual void Play()
 {
   if (sound)
    PlaySoundWithSource(sound, false, 0, SOUNDCATEGORY_INTERFACE);
 }

 virtual void OnDestroyContents()
 {
	 threading::MutexLock lock( NSoundScene::fmodMutex );

   if (sound)
     sound->release();
 }
};

   



ISimpleSound * CreateSimpleSoundFromData( const vector<unsigned char> & soundData, int rate, bool isStereo, int bitsPerSample )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  FMOD::Sound * sound;

  FMOD_CREATESOUNDEXINFO exinfo;

  int dataSize = soundData.size();
  memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
  exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
  exinfo.length = dataSize;
  exinfo.defaultfrequency = rate;
  exinfo.numchannels = isStereo? 2:1;
  
  NI_VERIFY(bitsPerSample==16 || bitsPerSample==8, "wrong bits per sample in stream", return 0);
  //for now only 16 and 8
  exinfo.format = bitsPerSample == 16? FMOD_SOUND_FORMAT_PCM16 : FMOD_SOUND_FORMAT_PCM8;

  /* Will ignore file format and treat as raw pcm.  Use FMOD_CREATESOUNDEXINFO to specify format.  
  Requires at least defaultfrequency, numchannels and format to be specified before it will open.  Must be little endian data. */
  //NI_VERIFY(g_pSystem,"not initilized FMOD", return 0;)

  if (!g_pSystem)
    return 0;
  
  result = g_pSystem->createSound((char *)&(soundData[0]), FMOD_2D | FMOD_HARDWARE | FMOD_OPENRAW | FMOD_OPENMEMORY, &exinfo, &sound);

  NI_VERIFY(result==FMOD_OK, "sound was not created in FMOD", return 0);
  sound->setMode( FMOD_2D );
  sound->setMode( FMOD_LOOP_OFF );

  return new SimpleSound(sound);//sound;
}

void TryTurnOnSound()
{
	if (NDb::Ptr<NDb::SoundEnvironment> pSndEnv = NDb::Get<NDb::SoundEnvironment>(NDb::DBID("Audio/soundEnvironment")))
		NSoundScene::Init( NSoundScene::EventSystemInit( pSndEnv, 4000, 1.0f ), 4000, 1.0f );
}

void TryTurnOffSound()
{
	NSoundScene::EventSystemRelease();
	NSoundScene::Release();
}
}


BASIC_REGISTER_CLASS(NSoundScene::ISimpleSound)
BASIC_REGISTER_CLASS(NSoundScene::SimpleSound)
