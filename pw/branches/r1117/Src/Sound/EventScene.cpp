#include "stdafx.h"
#include "EventScene.h"
#include "../System/FastMath.h"
#include "../libdb/AnimatedWrapper.h"
#include "../System/InlineProfiler.h"
#include <fmod_errors.h>
#include <fmod_event_net.hpp>
#include "SoundScene.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneObject.h"
#include "../Scene/SoundSceneComponent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// global memory pool to use with FMOD
static void *lpMemoryPool = NULL;

// user configuration variables
static float g_musicVolume = 0.8f;
static float g_soundVolume = 0.8f;
static float g_voiceVolume = 0.8f;
static float g_commonVolume = 1.0f;

static float g_musicMultiplier = 1.0f;

static float multiplier = 1.0f;
static int soundCameraType = NDb::SOUNDCAMERATYPE_PERSPECTIVE;
static bool sound_enableProfile = false;

static bool g_networkSoundAudit = false;

static bool g_stopped = false;

static bool g_sound_background_enable = false;
static bool g_issound = true;
static string dev_language = "";


#define USE_SOUND_SCENE_MEMORY_HOOKS 1 // enable fmod memory hooks, could be used to set breakpoints in them or log memory operations
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this should come first as it's being used later on down the page
// it couldn't be joined with the rest of the namespace hanging below
namespace NSoundScene
{

threading::Mutex fmodMutex;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static hash_map<string, CObj<Stream>> g_soundBanksCache;

static FMOD::EventSystem *eventSystem = 0;
static FMOD::System *fmodSystem = 0;
static FMOD::MusicSystem *musicSystem = 0;
static FMOD::EventProject *g_eventProject = 0;

static FMOD_VECTOR g_listenerPosition = { 0, 0, 0 };
static FMOD_VECTOR g_listenerForward = { 1, 0, 0 };
static FMOD_VECTOR g_listenerUp = { 0, 0, 1 };

static nstl::hash_map<nstl::string, FMOD::EventGroup*> g_groupCache;

static NDebug::DebugVar<float> sound_CPUUsage_DSP( "CPUUsage_DSP", "Sound" );
static NDebug::DebugVar<float> sound_CPUUsage_Stream( "CPUUsage_Stream", "Sound" );
static NDebug::DebugVar<float> sound_CPUUsage_Update( "CPUUsage_Update", "Sound" );
static NDebug::DebugVar<float> sound_CPUUsage_Total( "CPUUsage_Total", "Sound" );
static NDebug::DebugVar<int> sound_RAM_CurrentAlloced( "RAM_CurrentAlloced", "Sound" );
static NDebug::DebugVar<int> sound_RAM_MaxAlloced( "RAM_MaxAlloced", "Sound" );
static NDebug::DebugVar<int> sound_RAM_Total( "RAM_Total", "Sound" );
static NDebug::DebugVar<int> sound_RAM_Used( "Sound_RAM_Used", "Sound" );
static NDebug::DebugVar<int> sound_File_Cache( "File_Cache_Size", "Sound" );

static int currentSoundScene = -1;
static nstl::vector<NDb::SoundSceneDesc> soundScenes;

static bool isSoundAvalible = true;

static bool isReverb = true;

static float globalPitchCoeff = 1.0f;

static NDb::DBFMODEventDesc heartBeatDesc;
static nstl::string heartBeatParamName;
static FMOD::Event *heartBeatEvent = 0;
static bool heartBeatEnable = false;
static bool heartBeatPlay = false;
static float heartBeatValue = 100.0f;

static NDb::DBFMODEventDesc ambientSoundDesc;
static FMOD::Event *ambientSoundEvent = 0;
static bool ambientSoundEnable = false;

static NScene::IScene* pScene = 0;

static nstl::vector<FMODEvent*> fmodEvents;
static nstl::vector<FMODGroup*> fmodGroups;

class SoundCategory
{
  nstl::string name;
  FMOD::EventCategory* category;

  float volume;
  float pitch;
  NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > volumeWrapper;

  FMOD::EventCategory* FindCategory( const char* name )
  {
		threading::MutexLock lock( fmodMutex );

    if ( !eventSystem )
      return 0;
    char buffer[128];
    char* pos = 0;
    char* start = buffer;
    NStr::Copy( buffer, name, 128 );
    FMOD::EventCategory *category = 0;
    do
    {
      pos = NStr::FindFirstChar( start, '/' );
      if ( pos )
        *pos = 0;
      FMOD_RESULT result;
      FMOD::EventCategory* newCategory = 0;
      if ( category )
        result = category->getCategory( start, &newCategory );
      else
        result = eventSystem->getCategory( start, &newCategory );

      if ( newCategory )
      {
        NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot acquire category \"%s\", failed on part \"%s\". %s (%d)", name, start, FMOD_ErrorString( result ), result ), return 0 );
        category = newCategory;
        start = pos + 1;
      }
      else
      {
        return category;
      }
    } while ( pos != 0 );
    return category;
  }

public:
  SoundCategory() : category(0), name(""), volume(0.0f), pitch(0.0f) {}
  SoundCategory( const nstl::string& _name, bool muted ) : name( _name ) 
  { 
    category = FindCategory( name.c_str() );
    SetVolume( NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>(  muted && (currentSoundScene != -1) ? 0.0f : 1.0f ) ); 
    SetPitch( 0.0f );
  }

  void Mute() { SetVolume( NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>( 0.0f ) ); }
  void SetVolume( const NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>& _volume )
  {
    volumeWrapper.Init( &volume, NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>( _volume ), 0.0f );    
    UpdateTime( 0.0f );
  }

  void SetPitch( float val )
  {
    pitch = val;
    UpdateTime( 0.0f );
  }

  void UpdateTime( float dt )
  {
		threading::MutexLock lock( fmodMutex );
    volumeWrapper.Step( dt );
    // set category volume to volume variable
    if ( category )
    {
      FMOD_RESULT res = category->setVolume( volume );
      NI_ASSERT( res == FMOD_OK, NStr::StrFmt( "FMOD::%s::setVolume returns error \"%s\" (%d)", name.c_str(), FMOD_ErrorString( res ), res ) );
      float realpitch = pitch * globalPitchCoeff;
      res = category->setPitch( realpitch, FMOD_EVENT_PITCHUNITS_TONES );
      NI_ASSERT( res == FMOD_OK, NStr::StrFmt( "FMOD::%s::setPitch returns error \"%s\" (%d)", name.c_str(), FMOD_ErrorString( res ), res ) );
    }
  }

  bool IsMuted() const { return volume == 0.0f && volumeWrapper.IsFinished(); }
  void StopAllEvents() const
  {
		threading::MutexLock lock( fmodMutex );
    if ( category )
      category->stopAllEvents();
  }

  const string& GetName() const { return name; }

	void Dump()
	{
		threading::MutexLock lock( fmodMutex );
		float realvol = 0.0f;
		if ( category )
			category->getVolume(&realvol);
		DebugTrace("SoundCategory: %s, volume = %f, realvolume = %f", name.c_str(), volume, realvol );
	}
};

static nstl::vector<SoundCategory> categories;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static FMOD_RESULT F_CALLBACK fileOpen( const char *pName, int unicode, unsigned int *pFileSize, void **pHandle, void **pUserData )
{
	NI_ASSERT( !unicode, "Unicode is not supported in SoundScene file system" );

  CObj<Stream> pStream = 0;

  hash_map<string, CObj<Stream>>::iterator it = g_soundBanksCache.find( pName );
  if ( it != g_soundBanksCache.end() )
  {
    pStream = it->second;
  }
  else
  {
    pStream = RootFileSystem::OpenFile( pName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    if ( pStream == 0 || !pStream->IsOk() )
    {
      return FMOD_ERR_FILE_NOTFOUND;
    }
    g_soundBanksCache[ pName ] = pStream;
    sound_File_Cache.AddValue( pStream->GetSize() );
  }

	*pFileSize = pStream->GetSize();
	*pHandle = pStream.GetPtr();
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

	//delete static_cast<Stream *>(pHandle); // handle passed to/from callback as void
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_SOUND_SCENE_MEMORY_HOOKS
static void *F_CALLBACK memoryAllocate( unsigned int size, FMOD_MEMORY_TYPE type, const char* sourcestr )
{
	return operator new( size );
}

static void F_CALLBACK memoryFree( void *pBlock, FMOD_MEMORY_TYPE type, const char* sourcestr )
{
	operator delete(pBlock);
}

static void *F_CALLBACK memoryReallocate( void *pBlock, unsigned int size, FMOD_MEMORY_TYPE type, const char* sourcestr )
{
	return Realloc( pBlock, size );
}
#endif //#ifdef USE_SOUND_SCENE_MEMORY_HOOKS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateDebugVar()
{
	threading::MutexLock lock( fmodMutex );

	if( !fmodSystem )
		return;
	static float dsp;
	static float stream; 
	static float update; 
  static float geometry; 
	static float total;
	static int currentalloced; 
	static int maxalloced; 
	static int totalMem;
  static int usedMemory;

	fmodSystem->getCPUUsage( &dsp, &stream, &geometry, &update, &total );
	sound_CPUUsage_DSP.SetValue( dsp );
	sound_CPUUsage_Stream.SetValue( stream );
	sound_CPUUsage_Update.SetValue( update );
	sound_CPUUsage_Total.SetValue( total );
  FMOD::Memory_GetStats( &usedMemory, 0, false );
  fmodSystem->getSoundRAM(&currentalloced, &maxalloced, &totalMem);
	sound_RAM_CurrentAlloced.SetValue( currentalloced );
	sound_RAM_MaxAlloced.SetValue( maxalloced );
	sound_RAM_Total.SetValue( totalMem );
  sound_RAM_Used.SetValue( usedMemory );
  //NI_ASSERT( usedMemory<155000000, NStr::StrFmt( "Out of sound memory: %d", usedMemory ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMOD::Event* GetEvent( const NDb::DBFMODEventDesc& eventDesc )
{
	threading::MutexLock lock( fmodMutex );

  if( !eventSystem || !isSoundAvalible )
    return 0;

  if ( !PreCacheGroup( eventDesc.groupName ) )
    return 0;

    FMOD::EventGroup *pEventGroup = g_groupCache[eventDesc.groupName];
  
  FMOD::Event *pEvent;
  FMOD_RESULT result = pEventGroup->getEvent(eventDesc.eventName.c_str(), FMOD_EVENT_DEFAULT, &pEvent);
  NI_DATA_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot get event %s/%s. %s", eventDesc.groupName.c_str(), eventDesc.eventName.c_str(), FMOD_ErrorString( result ) ), return 0 );

  return pEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMOD::Event* GetEvent( FMOD::EventGroup *pGroup, const nstl::string & _event )
{
	threading::MutexLock lock( fmodMutex );

  if( pGroup == 0 || !isSoundAvalible )
    return 0;

  FMOD::Event *pEvent;
  FMOD_RESULT result = pGroup->getEvent( _event.c_str(), FMOD_EVENT_DEFAULT, &pEvent );
  NI_DATA_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot get event %s. %s", _event.c_str(), FMOD_ErrorString( result ) ), return 0 );

  return pEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReleaseEvent(FMOD::Event *pEvent)
{
	threading::MutexLock lock( fmodMutex );

	if ( !isSoundAvalible )
		return true;

  if (pEvent)
  {
    FMOD_RESULT result = pEvent->release();
    if(result != FMOD_OK)
      return false;
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoadGroupSamplesAndStreams( FMOD::EventGroup *pGroup )
{
	threading::MutexLock lock( fmodMutex );

	if ( !isSoundAvalible )
		return false;

  NI_VERIFY( pGroup, "Invalid pGroup", return false );

  FMOD_RESULT result = pGroup->loadEventData(FMOD_EVENT_RESOURCE_STREAMS_AND_SAMPLES,FMOD_EVENT_NONBLOCKING);
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot load samples and streams for group. %s", FMOD_ErrorString( result ) ), return false );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnloadGroup(FMOD::EventGroup *pGroup)
{
	threading::MutexLock lock( fmodMutex );

	if ( !isSoundAvalible )
		return;

  if(pGroup == 0)
    return;

  pGroup->freeEventData(0,true);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMOD::EventGroup* GetGroup( const nstl::string& project, const nstl::string& category )
{
	threading::MutexLock lock( fmodMutex );

  if( !eventSystem || !isSoundAvalible )
    return 0;

  FMOD::EventGroup *pEventGroup;
  FMOD_RESULT result = g_eventProject->getGroup(category.c_str(), true, &pEventGroup );
  NI_DATA_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot get group %s:%s. %s", project.c_str(), category.c_str(), FMOD_ErrorString( result ) ), return 0 );

  return pEventGroup;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMOD::Event* EventStart( const NDb::DBFMODEventDesc& eventDesc )
{
  NI_PROFILE_FUNCTION;

	threading::MutexLock lock( fmodMutex );

  FMOD::Event* pEvent = GetEvent( eventDesc );
  if ( !pEvent )
    return 0;

	FMOD_RESULT result = pEvent->start();
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot start event %s/%s. %s", eventDesc.groupName.c_str(), eventDesc.eventName.c_str(), FMOD_ErrorString( result ) ), return 0 );

	return pEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMOD::Event* EventStart( const NDb::DBFMODEventDesc& eventDesc, const CVec3& pPosition )
{
  NI_PROFILE_FUNCTION;

	threading::MutexLock lock( fmodMutex );

  FMOD::Event* pEvent = GetEvent( eventDesc );
  if ( !pEvent )
    return 0;

	FMOD_VECTOR fmodPosition = { pPosition.x, pPosition.y, pPosition.z };
	FMOD_RESULT result = pEvent->set3DAttributes( &fmodPosition, 0 );
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot positioning event %s/%s. %s", eventDesc.groupName.c_str(), eventDesc.eventName.c_str(), FMOD_ErrorString( result ) ), return 0 );

  result = pEvent->start();
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "Cannot start event %s/%s. %s", eventDesc.groupName.c_str(), eventDesc.eventName.c_str(), FMOD_ErrorString( result ) ), return 0 );

	return pEvent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EventStart(FMOD::Event *pEvent)
{
  NI_PROFILE_FUNCTION;

	threading::MutexLock lock( fmodMutex );

	if ( !isSoundAvalible )
		return false;

  return EventStart( pEvent, ( const CVec3 *) 0 ); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EventStart( FMOD::Event *pEvent, CVec3 const *_pPosition )
{
	threading::MutexLock lock( fmodMutex );

  if( pEvent == 0 || !isSoundAvalible )
    return false;

  FMOD::EventGroup* group;
  FMOD_RESULT result1 = pEvent->getParentGroup( &group );
  if ( result1 != FMOD_OK )
    return false;

  if(_pPosition != 0)
  {
    FMOD_VECTOR fmodPosition = { _pPosition->x, _pPosition->y, _pPosition->z };
    pEvent->set3DAttributes( &fmodPosition, 0 );
  }   

  FMOD_RESULT result = pEvent->start();
  if(result != FMOD_OK)
    return false;

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GetEventLength( FMOD::Event *pEvent, int &_lenght, bool isNeedMultiLanguageLength )
{
	threading::MutexLock lock( fmodMutex );

  _lenght = 0;
  if( pEvent == 0 || !isSoundAvalible )
    return false;
  
  FMOD_EVENT_INFO eventInfo;
  memset(&eventInfo,0,sizeof(FMOD_EVENT_INFO));

  FMOD_RESULT result = pEvent->getInfo(0,0,&eventInfo);

  if(result != FMOD_OK)
  return false;

  _lenght = eventInfo.lengthms;

  if ( isNeedMultiLanguageLength )
  {
    FMOD::ChannelGroup* channelGroup(NULL);
    pEvent->getChannelGroup(&channelGroup);
    if (channelGroup)
    {
      int numChannels(0);
      channelGroup->getNumChannels(&numChannels);

      for (int i(0); i < numChannels; ++i)
      {
        FMOD::Channel* channel(NULL);
        channelGroup->getChannel(i, &channel);
        if (channel)
        {
          FMOD::Sound* s;
          channel->getCurrentSound( &s );
          if ( s )
          {
            unsigned int length = 0;
            s->getLength( &length, FMOD_TIMEUNIT_MS );
            _lenght = length;
          }
        }
      }
    }
  }

  return true;
}

bool EventStop( FMOD::Event * pEvent, bool immediatly )
{
	threading::MutexLock lock( fmodMutex );

	if( pEvent && isSoundAvalible )
	{
		FMOD_RESULT result = pEvent->stop(immediatly);

    FMOD::EventGroup* group;
    FMOD_RESULT result1 = pEvent->getParentGroup( &group );
    if ( result1 != FMOD_OK )
      return false;

    return result;
	}
	return false;
}

bool EventPause(FMOD::Event *pEvent,bool _pause)
{
	threading::MutexLock lock( fmodMutex );

  if( pEvent == 0 || !isSoundAvalible )
    return false;

  FMOD_RESULT result = pEvent->setPaused(_pause);
  if(result != FMOD_OK)
    return false;

  return true;
}

bool EventSetParameter(FMOD::Event *pEvent, const char *name, float value)
{
	threading::MutexLock lock( fmodMutex );

  if( pEvent == 0 || !isSoundAvalible )
    return false;

  FMOD::EventParameter *parameter;
  FMOD_RESULT result;

  result = pEvent->getParameter(name, &parameter);
  if(result != FMOD_OK)
    return false;

  result = parameter->setValue(value);
  if(result != FMOD_OK)
    return false;

  return true;
}

bool IsEventPlaying(FMOD::Event *pEvent)
{
	threading::MutexLock lock( fmodMutex );

  if( pEvent == 0 || !isSoundAvalible )
    return false;

  FMOD_EVENT_STATE eventState;

  FMOD_RESULT result = pEvent->getState(&eventState);
  if(result != FMOD_OK)
    return false;

  if((eventState & FMOD_EVENT_STATE_PLAYING) == FMOD_EVENT_STATE_PLAYING)
    return true;
  
  return false;
}

bool IsEventPaused(FMOD::Event *pEvent)
{
	threading::MutexLock lock( fmodMutex );

  if( pEvent == 0 || !isSoundAvalible )
    return false;

  bool isPaused = false;
  FMOD_RESULT result = pEvent->getPaused(&isPaused);
  if(result != FMOD_OK)
    return false;

  return isPaused;
}

bool EventCategoryMute( const string& name, bool mute )
{
	threading::MutexLock lock( fmodMutex );

	if ( !eventSystem || !isSoundAvalible )
		return false;

  FMOD::EventCategory *category;
  FMOD_RESULT result = eventSystem->getCategory(name.c_str(), &category);

  if( result != FMOD_OK)
    return false;

  result = category->setMute(mute);
  return true;
}

bool SetEventPos( FMOD::Event * pEvent, const CVec3 * pPosition )
{
	threading::MutexLock lock( fmodMutex );

  if( pEvent && pPosition && isSoundAvalible )
  {
    FMOD_VECTOR fmodPosition = { pPosition->x, pPosition->y, pPosition->z };
    FMOD_RESULT result = pEvent->set3DAttributes( &fmodPosition, 0 );

    return result;

  }
  return false;
}

void SetScene( NScene::IScene* scene )
{
  pScene = scene;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FMOD::System* EventSystemInit( const NDb::SoundEnvironment *pSoundEnvironment, int maxNumberOfSounds, float unitsInMeter )
{
	threading::MutexLock lock( fmodMutex );

	if ( !g_issound )
	{
		isSoundAvalible = false;
		return 0;
	}

  //@Ivn@TODO: Move this variables to parameters
  const char* mediaPath = "\\Audio\\";
  const char* projectName = "PrimeWorld";

  FMOD_RESULT result;
#ifdef USE_SOUND_SCENE_MEMORY_HOOKS
	FMOD::Memory_Initialize( 0, 0, memoryAllocate, memoryReallocate, memoryFree );
#else
  //int const nSize = 50 * 1024 * 1024;   // old value
  //int const nSize = 120 * 1024 * 1024;    // temporary new value
  //int const nSize = 140 * 1024 * 1024;    // newest value
	int const nSize = 150 * 1024 * 1024;    // newest value 2
  lpMemoryPool = VirtualAlloc(0, nSize, MEM_COMMIT, PAGE_READWRITE );
  result = FMOD::Memory_Initialize(lpMemoryPool, nSize, NULL, NULL, NULL);
  NI_ASSERT(result == FMOD_OK, "Errorness");
#endif

	if( pSoundEnvironment )
	{
		multiplier = pSoundEnvironment->soundCamera.multiplier;
		soundCameraType = pSoundEnvironment->soundCamera.type;
	}
	else
		return 0;

	result = FMOD::EventSystem_Create(&eventSystem);
  if ( result == FMOD_ERR_OUTPUT_NOHARDWARE )
  {
    isSoundAvalible = false;
    return 0;
  }
  if ( result != FMOD_OK )
  {
    NI_ASSERT( result == FMOD_ERR_OUTPUT_ENUMERATION || result == FMOD_ERR_OUTPUT_FORMAT || result == FMOD_ERR_OUTPUT_INIT || result == FMOD_ERR_OUTPUT_NOHARDWARE,
      NStr::StrFmt( "FMOD::EventSystem::getSystemObject returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    return 0;
  }
	result = eventSystem->getSystemObject(&fmodSystem);
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::getSystemObject returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    EventSystemRelease();
    return 0;
  }

	// set file callbacks
	result = fmodSystem->setFileSystem( fileOpen, fileClose, fileRead, fileSeek, 0, 0, 4096 );
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::setFileSystem returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    EventSystemRelease();
    return 0;
  }
  
  const FMOD_INITFLAGS initFlags = FMOD_INIT_3D_RIGHTHANDED | ( sound_enableProfile ? FMOD_INIT_ENABLE_PROFILE : 0 );
  result = eventSystem->init( maxNumberOfSounds, initFlags, 0, FMOD_EVENT_INIT_FAIL_ON_MAXSTREAMS );
  if ( result == FMOD_ERR_OUTPUT_INIT )
  {
    isSoundAvalible = false;
    EventSystemRelease();
    return 0;
  }
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::init returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    EventSystemRelease();
    return 0;
  }

  nstl::string soundLanguage = NStr::ToMBCS(pSoundEnvironment->language.GetText());
  const string& curLanguage = (dev_language.empty() || dev_language.length() < 2) ?  soundLanguage : dev_language;

  if ( soundLanguage.empty() )
  {
    if ( curLanguage.empty() )
    {
      NI_ALWAYS_ASSERT( "Missed language settings in /Audio/soundEnvironment.xdb Use default RU" );
    }
    else
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "Missed language settings in /Audio/soundEnvironment.xdb Use %s", curLanguage.c_str() ) );
    }
  }

  result = eventSystem->setLanguage( curLanguage.c_str() );
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::setLanguage returns error \"%s\" (%d), language = \"%s\"", FMOD_ErrorString( result ), result, curLanguage.c_str() ) );
    EventSystemRelease();
    return 0;
  }

  result = eventSystem->setMediaPath( mediaPath );
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::setMediaPath returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    EventSystemRelease();
    return 0;
  }

	for( vector<string>::const_iterator it = pSoundEnvironment->fevFiles.begin(); it != pSoundEnvironment->fevFiles.end(); ++it )
	{
		result = eventSystem->load( it->c_str(), 0, 0 );
    NI_DATA_ASSERT( result == FMOD_OK, NStr::StrFmt( "Cannot load events from file \"%s\" referenced from object \"%s\". %s (%d)", it->c_str(), NDb::GetFormattedDbId( pSoundEnvironment->GetDBID() ).c_str(), FMOD_ErrorString( result ), result ) );
	}
	
	eventSystem->set3DListenerAttributes( 0, &g_listenerPosition, 0, &g_listenerForward, &g_listenerUp );

  result = eventSystem->getProject( projectName, &g_eventProject );
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::getProject returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    EventSystemRelease();
    return 0;
  }

  result = eventSystem->getMusicSystem(&musicSystem);
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::EventSystem::getMusicSystem returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    EventSystemRelease();
    return 0;
  }

#ifndef _SHIPPING
  if ( g_networkSoundAudit )
  {
    result = FMOD::NetEventSystem_Init( eventSystem, 0 );
    if ( result != FMOD_OK )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::NetEventSystem_Init returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
      EventSystemRelease();
      return 0;
    }
  }
#endif

  UpdateVolumes( g_soundVolume, g_musicVolume, g_voiceVolume, g_commonVolume );
	isSoundAvalible = true;
  return fmodSystem;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventSystemUpdate( float dt )
{
	threading::MutexLock lock( fmodMutex );

  if ( eventSystem && isSoundAvalible )
  {
		eventSystem->update();

#ifndef _SHIPPING
		if ( g_networkSoundAudit )
		{
			FMOD_NetEventSystem_Update();
		}
#endif

    for ( int i = 0; i < categories.size(); i++ )
	  {
      categories[i].UpdateTime( dt );
	  }
  }

	UpdateDebugVar();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventSystemSetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up, CVec3 const &anchor )
{
	threading::MutexLock lock( fmodMutex );

	if ( !eventSystem || !isSoundAvalible ) 
		return;

	if( soundCameraType == NDb::SOUNDCAMERATYPE_PERSPECTIVE )
	{
		g_listenerPosition.x = multiplier * (position.x - anchor.x) + anchor.x;
		g_listenerPosition.y = multiplier * (position.y - anchor.y) + anchor.y;
		g_listenerPosition.z = multiplier * (position.z - anchor.z) + anchor.z;

		g_listenerForward.x = forward.x;
		g_listenerForward.y = forward.y;
		g_listenerForward.z = forward.z;

		g_listenerUp.x = up.x;
		g_listenerUp.y = up.y;
		g_listenerUp.z = up.z;
	}
	else if( soundCameraType == NDb::SOUNDCAMERATYPE_TOPDOWN )
	{
		g_listenerPosition.x = anchor.x;
		g_listenerPosition.y = anchor.y;
		g_listenerPosition.z = multiplier * (position.z - anchor.z) + anchor.z;

		g_listenerForward.x = 0;
		g_listenerForward.y = 0;
		g_listenerForward.z = -1;

		g_listenerUp.x = up.x/NMath::Sqrt(up.x*up.x+ up.y*up.y);
		g_listenerUp.y = up.y/NMath::Sqrt(up.x*up.x+ up.y*up.y);
		g_listenerUp.z = 0;
	}
	eventSystem->set3DListenerAttributes( 0, &g_listenerPosition, 0, &g_listenerForward, &g_listenerUp );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EventSystemRelease( )
{
	threading::MutexLock lock( fmodMutex );

  if ( musicSystem && isSoundAvalible )
  {
    musicSystem->reset();
    musicSystem = 0;
  }

  if ( eventSystem && isSoundAvalible )
  {
    eventSystem->release();
    eventSystem = 0;
#ifndef _SHIPPING
    if ( g_networkSoundAudit )
    {
      FMOD_NetEventSystem_Shutdown();
    }
#endif
  }

  if ( fmodSystem )
  {
    fmodSystem->release();
    fmodSystem = 0;
  }    

  if ( lpMemoryPool )
  {
    VirtualFree( lpMemoryPool, 0, MEM_RELEASE );
    lpMemoryPool = 0;
  }

  g_soundBanksCache.clear();
  sound_File_Cache.SetValue( 0 );
	isSoundAvalible = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PreCacheGroup( const nstl::string & groupName, bool loadEventData /*= false*/ )
{
	threading::MutexLock lock( fmodMutex );

  if ( !g_eventProject )
    return false;
  if ( g_groupCache.find(groupName) == g_groupCache.end() )
  {
    FMOD::EventGroup *pEventGroup;
    FMOD_RESULT result = g_eventProject->getGroup(groupName.c_str(), true, &pEventGroup );
    if( result != FMOD_OK)
    {
      return false;
    }
    
    if( loadEventData )
      pEventGroup->loadEventData();

    g_groupCache[groupName] = pEventGroup;
    return true;
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnloadGroup( const nstl::string & groupName )
{
	threading::MutexLock lock( fmodMutex );

  if ( g_groupCache.find(groupName) != g_groupCache.end() )
  {
    g_groupCache[groupName]->freeEventData(0,true);
    g_groupCache.erase( groupName );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ActivateSoundScene( int idx, bool force )
{
  NI_PROFILE_FUNCTION;

	threading::MutexLock lock( fmodMutex );

  if ( idx == currentSoundScene && !force )
    return;

  if ( idx >= soundScenes.size() )
    return;

  if( soundScenes[idx].cue.cueName.empty() )
    return;

  currentSoundScene = idx;

  for ( int k = 0; k < categories.size(); k++ )
  {
    categories[k].Mute();
    EventSystemUpdate(0.0f);
  }

  for ( int i = 0; i < soundScenes[currentSoundScene].soundSceneGroups.size(); i++ )
  {
    for ( int k = 0; k < categories.size(); k++ )
    {
      if ( categories[k].GetName() == soundScenes[currentSoundScene].soundSceneGroups[i].categoryName )
      {
        categories[k].SetVolume( soundScenes[currentSoundScene].soundSceneGroups[i].volume );
        categories[k].SetPitch( soundScenes[currentSoundScene].soundSceneGroups[i].pitch );
        EventSystemUpdate(0.0f);
      }
    }
  }

  StopMusic();
  PlayMusic( soundScenes[currentSoundScene].cue );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitSoundScene( int idx, const NDb::SoundSceneDesc& soundSceneDesc )
{
	threading::MutexLock lock( fmodMutex );

  NI_VERIFY( idx == soundScenes.size(), "Wrong order add SoundScenes", return );
  for ( int i = 0; i < soundSceneDesc.soundSceneGroups.size(); i++ )
  {
    bool isFound = false;
    for ( int k = 0; k < categories.size(); k++ )
    {
      if ( categories[k].GetName() == soundSceneDesc.soundSceneGroups[i].categoryName )
      {
        isFound = true;
        break;
      }
    }
    if ( !isFound )
    {
      SoundCategory toadd( soundSceneDesc.soundSceneGroups[i].categoryName, false );
      categories.push_back( toadd );
    }
  }
  soundScenes.push_back( soundSceneDesc );
}

int GetActiveSoundScene()
{
  return currentSoundScene;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayMusic( const NDb::MusicDesc& music )
{
	threading::MutexLock lock( fmodMutex );

  if ( !musicSystem )
    return;
  if ( soundScenes[currentSoundScene].cue.cueName != music.cueName )
    return;
  FMOD_MUSIC_ITERATOR it;
  FMOD_RESULT result = musicSystem->getCues( &it, music.cueName.c_str() );
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::getCues returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );

  if ( it.value )
  {
    FMOD::MusicPrompt* musicPrompt;
    result = musicSystem->prepareCue( it.value->id, &musicPrompt );
    NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::prepareCue returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );

    result = musicPrompt->begin();
    NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicPrompt::begin returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PauseMusic()
{
  threading::MutexLock lock( fmodMutex );

  if ( !musicSystem )
    return;

  bool paused;

  FMOD_RESULT result = musicSystem->getPaused( &paused );
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::getPaused returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );

  if( !paused )
  {
    result = musicSystem->setPaused( true );
    NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::setPaused returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnPauseMusic()
{
  threading::MutexLock lock( fmodMutex );

  if ( !musicSystem )
    return;

  bool paused;

  FMOD_RESULT result = musicSystem->getPaused( &paused );
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::getPaused returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );

  if( paused )
  {
    result = musicSystem->setPaused( false );
    NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::setPaused returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StopMusic()
{
	threading::MutexLock lock( fmodMutex );

  if ( !musicSystem )
    return;

  FMOD_RESULT result = musicSystem->reset();
  NI_VERIFY( result == FMOD_OK, NStr::StrFmt( "FMOD::MusicSystem::reset returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ), return );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetHeartBeatData(const NDb::DBFMODEventDesc& _heartBeatDesc, const nstl::string& _heartBeatParamName)
{
  heartBeatDesc      = _heartBeatDesc;
  heartBeatParamName = _heartBeatParamName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableHeartBeat(bool enable)
{
  heartBeatEnable = enable;

  if (heartBeatEnable)
    StartHeartBeat();
  else
    StopHeartBeat();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayHeartBeat(bool play)
{
  heartBeatPlay = play;

  if (heartBeatEvent)
  {
    if (heartBeatPlay)
      NSoundScene::EventStart(heartBeatEvent);
    else
      NSoundScene::EventStop(heartBeatEvent);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StartHeartBeat()
{
  if (heartBeatEnable && NSoundScene::isSoundAvalible )
  {
    if (!heartBeatEvent)
      heartBeatEvent = NSoundScene::GetEvent( heartBeatDesc );

    if (heartBeatEvent && heartBeatPlay)
    {
      NSoundScene::EventStart(heartBeatEvent);
      UpdateHeartBeat(heartBeatValue);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StopHeartBeat()
{
  if (heartBeatEvent)
  {
    EventStop(heartBeatEvent, true);
    ReleaseEvent(heartBeatEvent);
    heartBeatEvent = 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateHeartBeat(float value)
{
  heartBeatValue = value;

  if (heartBeatEvent)
  {
    NSoundScene::EventSetParameter(heartBeatEvent, heartBeatParamName.c_str(), value);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetAmbientData(const NDb::DBFMODEventDesc& _ambientSoundDesc)
{
  ambientSoundDesc = _ambientSoundDesc;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableAmbient(bool enable)
{
  ambientSoundEnable = enable;

  if (ambientSoundEnable)
    StartAmbient();
  else
    StopAmbient();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StartAmbient()
{
  if (ambientSoundEnable && NSoundScene::isSoundAvalible )
  {
    if (!ambientSoundEvent)
      ambientSoundEvent = NSoundScene::GetEvent( ambientSoundDesc );

    if (ambientSoundEvent)
      NSoundScene::EventStart(ambientSoundEvent);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StopAmbient()
{
  if (ambientSoundEvent)
  {
    NSoundScene::EventStop(ambientSoundEvent, true);
    NSoundScene::ReleaseEvent(ambientSoundEvent);
    ambientSoundEvent = 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateAmbient(const nstl::string& paramName, float paramValue)
{
  if (ambientSoundEvent)
    NSoundScene::EventSetParameter(ambientSoundEvent, paramName.c_str(), paramValue);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateVolumes( float soundVol, float musicVol, float voiceVol, float commonVol )
{
	threading::MutexLock lock( fmodMutex );

  if ( musicSystem )
    musicSystem->setVolume( musicVol * commonVol * g_musicMultiplier );
  if ( eventSystem )
  {
    int totalCategories = 0;
    eventSystem->getNumCategories( &totalCategories );
    FMOD::EventCategory* pMusicCategory;
    eventSystem->getMusicCategory( &pMusicCategory );
    for( int i = 0; i < totalCategories; ++i )
    {
      FMOD::EventCategory* pCategory;
      eventSystem->getCategoryByIndex( i, &pCategory );
      if ( pCategory == pMusicCategory )
        continue;
      int index = 0;
      char* name = "";
      pCategory->getInfo( &index, &name );
      nstl::string categoryName( name );
      if ( categoryName == nstl::string("voice") )
        pCategory->setVolume( voiceVol * commonVol );
      else
        pCategory->setVolume( soundVol * commonVol );
    }
  }
}

void SetMusicVolume( float volume )
{
  g_musicVolume = volume;
}

void SetMusicMultiplier( float multiplier )
{
  g_musicMultiplier = multiplier;

  threading::MutexLock lock( fmodMutex );

  if ( musicSystem )
    musicSystem->setVolume( g_musicVolume * g_commonVolume * g_musicMultiplier );
}

void SetSoundVolume( float volume )
{
  g_soundVolume = volume;
}

void SystemStop()
{
  if ( g_sound_background_enable )
    return;

  if ( !g_stopped )
  {
    UpdateVolumes( 0.0f, 0.0f, 0.0f, 0.0f );
    g_stopped = true;
  }
}

void SystemResume()
{
  if ( g_sound_background_enable )
    return;

  if ( g_stopped )
  {
    UpdateVolumes( g_soundVolume, g_musicVolume, g_voiceVolume, g_commonVolume );
    g_stopped = false;
  }
}

void ApplyReverb( nstl::string& presetName )
{
  if ( !isReverb )
    return;

  if ( !eventSystem || !isSoundAvalible )
    return;

  FMOD_RESULT result = FMOD_OK;
  FMOD_REVERB_PROPERTIES reverb = FMOD_PRESET_ROOM;
  memset( &reverb, 0, sizeof(FMOD_REVERB_PROPERTIES) );
  result = eventSystem->getReverbPreset( presetName.c_str(), &reverb, 0 );
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::getReverbPreset returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
  }

  result = eventSystem->setReverbProperties( &reverb );
  if ( result != FMOD_OK )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::setReverbAmbientProperties returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
  }
}

void SetGlobalPitchCoeff( float val )
{
  globalPitchCoeff = val;
}


void FMODEvent::Init( const NDb::DBFMODEventDesc &_desc )
{
  desc.projectName = _desc.projectName;
  desc.groupName   = _desc.groupName;
  desc.eventName   = _desc.eventName;

  isValid = true;
}

bool FMODEvent::IsVaild() const
{
  return isValid;
}

FMOD::Event* FMODEvent::GetEvent() const
{
  return soundEvent;
}

bool FMODEvent::PlaySound()
{
  if (!isValid)
    return false;

  soundEvent = EventStart(desc);
  return true;
}

bool FMODEvent::IsAllreadyPlayed() const
{
  threading::MutexLock lock( fmodMutex );

  FMOD_EVENT_STATE state;
  FMOD_RESULT  bOK;

  if ( !soundEvent )
    return false;

  bOK = soundEvent->getState(&state);

  if (FMOD_OK == bOK)
    return (state & FMOD_EVENT_STATE_PLAYING);

  return false;
}

bool FMODEvent::Stop( bool immediately )
{
  return EventStop( soundEvent, immediately );
}

void FMODEvent::Release()
{
  EventStop( soundEvent, true );
  ReleaseEvent( soundEvent );
  soundEvent = 0;
}

float FMODEvent::GetDuration( bool isNeedMultiLanguageLength )
{
  if (!soundEvent)
    return 0;

  int _length = 0;
  NSoundScene::GetEventLength(soundEvent, _length, isNeedMultiLanguageLength);

  float lenghtInSeconds = ((float)_length)/1000.0f;
  return   lenghtInSeconds;
}

FMODEvent* CreateFMODEvent()
{
  FMODEvent* event = new FMODEvent();
  fmodEvents.push_back( event );
  return event;
}

void ReleaseFMODEvent( FMODEvent* fmodEvent )
{
  nstl::vector<FMODEvent*>::iterator it = nstl::find( fmodEvents.begin(), fmodEvents.end(), fmodEvent );
  if ( it != fmodEvents.end() )
  {
    fmodEvents.erase( it );
    delete fmodEvent;
  }
}

FMODGroup* CreateFMODGroup()
{
  FMODGroup* group = new FMODGroup();
  fmodGroups.push_back( group );
  return group;
}

void ReleaseFMODGroup( FMODGroup* fmodGroup )
{
  nstl::vector<FMODGroup*>::iterator it = nstl::find( fmodGroups.begin(), fmodGroups.end(), fmodGroup );
  if ( it != fmodGroups.end() )
  {
    fmodGroups.erase( it );
    delete fmodGroup;
  }
}



void FMODGroup::Init( const nstl::string & project, const nstl::string & category )
{
  if ( !isValid )
  {
    eventGroup = NSoundScene::GetGroup( project, category );
    if ( eventGroup )
    {
      isValid = NSoundScene::LoadGroupSamplesAndStreams( eventGroup );
    }
  }
}

bool FMODGroup::IsValid() const
{
  return isValid;
}

FMOD::EventGroup* FMODGroup::GetGroup() const
{
  if ( isValid )
    return eventGroup;
  return 0;
}

void FMODGroup::Release()
{
  if ( isValid )
  {
    NSoundScene::UnloadGroup(eventGroup);
    eventGroup = 0;
    isValid = false;
  }
}
} //namespace NSoundScene
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool UpdateVolumes( const char *name, const vector<wstring> &params )
{
  NSoundScene::UpdateVolumes( g_soundVolume, g_musicVolume, g_voiceVolume, g_commonVolume );
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool DisableMusic( const char *name, const vector<wstring> &params )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

  if ( NSoundScene::musicSystem )
    NSoundScene::musicSystem->setVolume( 0.0f );
  return true;
}

static bool DumpSound( const char *name, const vector<wstring> &params )
{
	for ( int i = 0; i < NSoundScene::categories.size(); i++ )
	{
		NSoundScene::categories[i].Dump();
	}
	return true;
}

static void StopSoundComponents()
{
  if ( NSoundScene::pScene )
  {
    struct SoundStopperComponent : public NScene::FullTraverser
    {
      void operator()(NScene::SceneComponent *pSC)
      {
        if ( NScene::SoundSceneComponent* ssc = dynamic_cast<NScene::SoundSceneComponent*>(pSC) )
        {
          ssc->Deinit();
        }
      }
    };

    struct SoundStopperObject : public NScene::ISceneObjectFunctor
    {
      virtual void operator()( NScene::SceneObjectBase* so )
      {
        if ( NScene::SceneObject* sceneObj = dynamic_cast<NScene::SceneObject*>(so) )
        {
          SoundStopperComponent f;
          sceneObj->Traverse( f );
        }
      }
    } f;

    NSoundScene::pScene->ForAllSceneObjects( &f );
  }
}

static bool SetSoundLanguage( const char *name, const vector<wstring> &params )
{
  dev_language = NStr::ToMBCS( NGlobal::VariantValue( params[0] ).GetString() );

/*  if (!NSoundScene::eventSystem)
    return false;
  threading::MutexLock lock( NSoundScene::fmodMutex );
  NSoundScene::TryTurnOffSound();
  NSoundScene::TryTurnOnSound();
  */
  return true;
}

static bool RestartSound( const char *name, const vector<wstring> &params )
{
	threading::MutexLock lock( NSoundScene::fmodMutex );

	//Turn on sound
	if ( g_issound == 1 && !NSoundScene::isSoundAvalible )
	{
    StopSoundComponents();
    NSoundScene::g_groupCache.clear();
    NSoundScene::TryTurnOnSound();
		NSoundScene::StartAmbient();
		NSoundScene::StartHeartBeat();

    // Восстановление категорий и текущей звуковой сцены
    nstl::vector<NDb::SoundSceneDesc> soundScenesCache;
    for ( int i = 0; i < NSoundScene::soundScenes.size(); i++ )
    {
      soundScenesCache.push_back(NSoundScene::soundScenes[i]);
    }
    NSoundScene::soundScenes.clear();
    for ( int i = 0; i < soundScenesCache.size(); i++ )
      NSoundScene::InitSoundScene( i, soundScenesCache[i] );
    NSoundScene::currentSoundScene = NSoundScene::currentSoundScene^(-1);
    int soundScene = NSoundScene::currentSoundScene^(-1);
    NSoundScene::ActivateSoundScene( soundScene, false );
	}
	//Turn off sound
	else if ( g_issound == 0 && NSoundScene::isSoundAvalible )
	{
    StopSoundComponents();
    for ( int i = 0; i < NSoundScene::fmodEvents.size(); i++ )
    {
      NSoundScene::fmodEvents[i]->Release();
    }
    for ( int i = 0; i < NSoundScene::fmodGroups.size(); i++ )
    {
      NSoundScene::fmodGroups[i]->Release();
    }
		NSoundScene::StopHeartBeat();
		NSoundScene::StopAmbient();
		NSoundScene::StopMusic();
		NSoundScene::TryTurnOffSound();
    NSoundScene::g_groupCache.clear();
    NSoundScene::categories.clear();
	}
	return true;
}

static bool SwitchSound( const char *name, const vector<wstring> &params )
{
  g_issound = !g_issound;
  return RestartSound( name, params );
}

static bool ReverbOn( const char *name, const vector<wstring> &params )
{
  if ( !NSoundScene::isReverb )
  {
    NSoundScene::isReverb = true;
  }
  return true;
}
static bool ReverbOff( const char *name, const vector<wstring> &params )
{
  if ( !NSoundScene::eventSystem || !NSoundScene::isSoundAvalible )
    return true;

  if ( NSoundScene::isReverb )
  {
    FMOD_RESULT result = FMOD_OK;
    FMOD_REVERB_PROPERTIES reverbPreset = FMOD_PRESET_ROOM;
    memset( &reverbPreset, 0, sizeof(FMOD_REVERB_PROPERTIES) );
    result = NSoundScene::eventSystem->getReverbProperties( &reverbPreset );
    if ( result != FMOD_OK )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::getReverbPreset returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    }

    reverbPreset.Room = -10000.0f;

    result = NSoundScene::eventSystem->setReverbProperties( &reverbPreset );
    if ( result != FMOD_OK )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "FMOD::setReverbAmbientProperties returns error \"%s\" (%d)", FMOD_ErrorString( result ), result ) );
    }

    NSoundScene::isReverb = false;
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_VAR_PRED( "sound_volume", g_soundVolume, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0.0f, 1.0f) );
REGISTER_VAR_PRED( "music_volume", g_musicVolume, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0.0f, 1.0f) );
REGISTER_VAR_PRED( "voice_volume", g_voiceVolume, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0.0f, 1.0f) );
REGISTER_VAR_PRED( "common_volume", g_commonVolume, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0.0f, 1.0f) );

REGISTER_VAR( "sound_background_enable", g_sound_background_enable, STORAGE_USER );
REGISTER_DEV_VAR( "dev_sound", g_issound, STORAGE_USER );

REGISTER_DEV_VAR( "sound_enableProfile", sound_enableProfile, STORAGE_NONE );
REGISTER_DEV_VAR( "networkSoundAudit", g_networkSoundAudit, STORAGE_NONE );
REGISTER_DEV_VAR( "sound_multiplier", multiplier, STORAGE_NONE );
REGISTER_DEV_VAR( "soundCameraType", soundCameraType, STORAGE_NONE );

REGISTER_CMD( update_volume, UpdateVolumes );
REGISTER_DEV_CMD( disable_music, DisableMusic );
REGISTER_DEV_CMD( dump_sound, DumpSound );
REGISTER_DEV_CMD( restart_sound, RestartSound );
REGISTER_DEV_CMD( turn_reverb_on, ReverbOn );
REGISTER_DEV_CMD( turn_reverb_off, ReverbOff );
REGISTER_DEV_CMD( switch_sound, SwitchSound );
REGISTER_DEV_CMD( set_sound_language, SetSoundLanguage );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ChangeSoundStateIfNeed()
{
//  const bool newSoundState =  g_soundVolume > 0.01 || g_musicVolume > 0.01;

  NSoundScene::UpdateVolumes( g_soundVolume, g_musicVolume, g_voiceVolume, g_commonVolume );

//   if( newSoundState != g_issound )
//   {
//     g_issound = newSoundState;
//     NGlobal::RunCommand( L"restart_sound" );
//   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SoundVolumeVariable: public NGlobal::IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS( SoundVolumeVariable );
public:
  SoundVolumeVariable(): pVar(0) {}
  SoundVolumeVariable(float *pVar): pVar(pVar) {}
  
  virtual NGlobal::VariantValue Get() 
  {  
    NI_ASSERT(pVar != 0, ""); 
    return NGlobal::VariantValue(*pVar); 
  }
  
  virtual void Set( const NGlobal::VariantValue &val )
  {  
    NI_ASSERT(pVar != 0, ""); 
    *pVar = val.Get<float>(); 
    NGlobal::RunCommand( L"update_volume" );
    ChangeSoundStateIfNeed();
  }

private:
  float *pVar;            
};

REGISTER_VAR_INTERFACE( "pref_sound_volume", new SoundVolumeVariable(&g_soundVolume), STORAGE_NONE )
REGISTER_VAR_INTERFACE( "pref_music_volume", new SoundVolumeVariable(&g_musicVolume), STORAGE_NONE )
REGISTER_VAR_INTERFACE( "pref_voice_volume", new SoundVolumeVariable(&g_voiceVolume), STORAGE_NONE )
REGISTER_VAR_INTERFACE( "pref_common_volume", new SoundVolumeVariable(&g_commonVolume), STORAGE_NONE )
