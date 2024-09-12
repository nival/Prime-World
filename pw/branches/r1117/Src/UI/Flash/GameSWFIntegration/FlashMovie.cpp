#include "TamarinPCH.h"

#include "../../Defines.h"

#include "FlashMovie.h"

#include "Render/FlashRendererInterface.h"


#include "FontsRenderInterface.h"

#include "Natives/display/Loaderinfo.h"
#include "Natives/display/MovieClip.h"
#include "Natives/display/Bitmap.h"
#include "Natives/display/BitmapData.h"
#include "Natives/display/Shape.h"
#include "Natives/display/Stage.h"

#include "Natives/events/Event.h"
#include "Natives/events/EventTypes.h"
#include "Natives/events/MouseEvent.h"

#include "Natives/utils/Timer.h"

#include "Natives/ClassMacros.h"

#include "Characters.h"
#include "MorphCharacter.h"
#include "ButtonCharacter.h"
#include "DisplayTags.h"
#include "TextCharacter.h"
#include "EditTextCharacter.h"
#include "FontTags.h"
#include "FontsDict.h"
#include "FlashClassesCache.h"
#include "JPEGReader.h"

#include "FlashEnterFunction.h"

#include "System/InlineProfiler.h"
#include <Render/NullRenderSignal.h>

//FIXME: We dont have special place for these
NI_DEFINE_REFCOUNT( flash::IFontInstance );
NI_DEFINE_REFCOUNT( flash::IFontRender );

//TODO move this to a better place. but not in FlashRenderer.cpp cause its not in test solution
NI_DEFINE_REFCOUNT( Render::IFlashRenderer ); 

namespace 
{
  static bool g_DebugMouse = false;

  REGISTER_DEV_VAR( "flash_debug_mouse", g_DebugMouse, STORAGE_NONE );

  static NDebug::DebugVar<unsigned int> totalListenersCount( "TotalListenersCount", "PerfCnt" );
  static NDebug::DebugVar<unsigned int> totalAdvancersCount( "TotalAdvancersCount", "PerfCnt" );

  static const char * LocalizationProperty = "LocalizationResources";
  static const char * LocalizationCompleteMethod = "LocalizationComplete";

  DECLARE_NULL_RENDER_FLAG
}

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//forward declaration of the helper function
avmplus::ReadOnlyScriptBufferImpl * GetScriptBuffer(SwfStreamReader &parser, int taglen, MMgc::GC *gc);

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Movie::Movie( IStageProvider * _stageProvider, MMgc::GC * gc, IFontRender * _fontRender, IStageFocusHandler * _focusHandler  ):
  flash::SafeGCRoot<Movie>( gc ),
  fontRender( _fontRender ),
  stageProvider( _stageProvider ),
  stageFocusHandler(_focusHandler),
  frameTime( 1.f / 24.f ),
  currentFrameTime(0.f),
  timeFromStart(0.f),

  timers( GetGC() ),
  advanceList( GetGC() ),

  viewportX(0),
  viewportY(0),
  viewportWidth(100),
  viewportHeight(100),
  pixelScale(1.f),

  draggedStartX(0),
  draggedStartY(0),
  draggedMinX(0),
  draggedMaxX(0),
  draggedMinY(0),
  draggedMaxY(0),
  useDragRectangle(false),

  streamReader(*this),
  doubleClickRegistred(false),

  isUIBlocked(false),
  uiBlockAddColor( 0.f, 0.f, 0.f, 0.f ),
  blockingFade(0.f)
{
  FLASH_ENTER_FUNCTION_VOID( GetGC() ) // не двигаем выше

  core = new FlashMovieAvmCore( GetGC() );
  core->SetJITEnabled( true );
  core->Initialize();
  core->SetMovie( this );

  fonts = new FontsDictionary;

  InitLoaders();

  Identity( &uiBlockColorMatrix );
  Identity( &uiNonBlockColorMatrix );
}

Movie::~Movie()
{
  advanceList.clear();

  rootMovieClip = 0;
  loaderInfo = 0;
  stage = 0;

  topMostDisplayObject = 0;
  objectMouseDown = 0;

  characterDictionary.clear();
  poolDataByFrame.clear();

  if ( core )
    delete core;
  core = 0;
}

void Movie::SetFlashRenderer( Render::IFlashRenderer* _renderer ) 
{ 
  streamReader.SetFlashRenderer( _renderer );
  renderer = _renderer; 
}

bool Movie::LoadFile( Stream* stream, const char* filename )
{
  if ( !SWFParser::ParseSwf( stream, GetGC(), tags, swfInfo, streamReader ) )
    return false;

  sourceFilename = filename;

  CalculatePixelScale();

  return LoadFileInternal(streamReader);
}

bool Movie::LoadFile( const char* filename )
{
  sourceFilename = filename;

  CalculatePixelScale();

  if ( !SWFParser::ParseSwf(filename, GetGC(), tags, swfInfo , streamReader) )
    return false;
  
  /*TRY( this, avmplus::kCatchAction_ReportAsError )
  {
	  handleActionBlock(code, 0, domainEnv, topLevel, NULL, NULL /*gameCodeContext*/ /*, getAPI(NULL));
  }
  CATCH ( Exception *exception )
  {
	  PrintException(exception);
  }
  END_CATCH
	  END_TRY

  bool loadResult = */
  return LoadFileInternal(streamReader);
}

bool Movie::LoadFileInternal( SwfStreamReader & streamReader )
{
  //total frame  time. TODO do we need this?
  frameTime = 1.f / swfInfo.frameRate;
  timeFromStart = 0;

  CONSTRUCT_CACHE_OBJECT(loaderInfo, core, LoaderInfoClass, LoaderInfoObject);
  CONSTRUCT_CACHE_OBJECT(stage, core, StageClass, StageObject);

  stage->SetStageProvider( stageProvider );
  stage->SetStageFocusHandler(stageFocusHandler);
  stage->SetStageAndRoot( stage, stage, false );

  loaderInfo->SetFrameRate(swfInfo.frameRate);
  loaderInfo->SetWidth(swfInfo.rect.GetWidth());
  loaderInfo->SetHeight(swfInfo.rect.GetHeight());

  characterDictionary[0].character = new MovieCharacter();

  if ( !ProcessReadTags( streamReader, false ) )
    return false;

  if ( !ProcessReadTags( streamReader, true ) )
    return false;

  rootMovieClip = dynamic_cast< avmplus::SpriteObject* >( CreateObjectByCharacter( 0, 0, 0 ) );

  NI_ASSERT( rootMovieClip, "Cannot create root MovieClip" );

  {
    //TODO may be change this. stage.root should be stage
    stage->SetStageAndRoot(stage, rootMovieClip, false);
    stage->addChild( rootMovieClip );
    
    rootMovieClip->SetLoaderInfo(loaderInfo);
  }

  rootMovieClip->DumpHierarchy( 0 );

  loaderInfo->Fire_INIT();
  loaderInfo->Fire_COMPLETE();

  return true;
}

void Movie::CollectLocalizationProperties( nstl::list<nstl::string>& _proplist )
{
  avmplus::ScriptObject* localization = GetLocalizationObject() ;

  if (!localization )
    return;

  return CollectPropertiesFromObject(localization, _proplist);
}


void Movie::SetLocalizationProperty( const char* _name, const wchar_t* _value )
{
  avmplus::ScriptObject* localization = GetLocalizationObject() ;
  
  if (!localization )
    return;

  avmplus::Stringp name = core->internConstantStringLatin1( _name );
  avmplus::Stringp value = core->newStringUTF16( (const wchar *) _value );

  SetPropertyToObject(localization, name, value->atom());
}


void Movie::FinishLocalization()
{
  avmplus::ScriptObject* localization = GetLocalizationObject() ;

  if (!localization )
    return;

  avmplus::Atom argv[1];
  argv[0] = localization->atom();
  avmplus::Atom result;  
  avmplus::FlashScriptObject::CallMethodI( localization, LocalizationCompleteMethod, 0, argv, result );
}


avmplus::ScriptObject * Movie::GetLocalizationObject()
{
  if (!rootMovieClip)
    return 0;

  avmplus::Atom atom = GetMultinamePropertyFromObject( rootMovieClip, LocalizationProperty );

  if ( atom == avmplus::AtomConstants::nullObjectAtom )
    return 0;

  return core->atomToScriptObject( atom ) ;
}

bool Movie::ProcessReadTags( SwfStreamReader & streamReader, bool imagePass )
{
  if ( tags.size() <= 0 ) 
    return false;

  for (SwfTagInfos::iterator curTag = tags.begin(); curTag!=tags.end();++curTag)
  {
    TagInfo & tag = *curTag;
    NI_ASSERT(tag.parserPos+tag.tagLen <= swfInfo.swflen, "we are out of stream bounds!")
    //this code will automatically skip all tags that we don't process

    if ( tag.parserPos < streamReader.swf.getSize() )
      streamReader.SetPos( tag.parserPos );

    if ( IsImageTag( tag.tagType ) ^ imagePass )
      continue;

    if (loaders.find(tag.tagType) != loaders.end())
    {
      //DebugTrace( "Parse SWF tag %d (%s)", (int)tag.tagType, SWFTags::EnumToString((SWFTags::SWFTagType)tag.tagType) );

      LoaderMethod method =  loaders[tag.tagType];
      (this->*method)(streamReader, tag, 0);

      int posDiff = streamReader.GetPos() - (tag.parserPos + tag.tagLen);
      NI_ASSERT( posDiff <= 0, NStr::StrFmt("Tag parsed with error. Position difference: %d", posDiff ) );
    }
    else
    {
      //DebugTrace( "Unsupported SWF tag %d (%s)", (int)tag.tagType, SWFTags::EnumToString((SWFTags::SWFTagType)tag.tagType) );
    }
  }

  return true;
}


// The SymbolClass tag creates associations between symbols in the SWF file
// and ActionScript 3.0 classes.;
void Movie::ParseSymbolClass(SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID) 
{
  int num_symbols = streamReader.readUI16();
  
  for (int i = 0; i < num_symbols; i++)
  {
    int	character_id = streamReader.readUI16();

    nstl::string className;
    streamReader.readString( className );

    int lastPointPos = className.find_last_of('.');
    className = (lastPointPos ==-1)? className: className.substr(lastPointPos+1);

    characterDictionary[character_id].symbolClass = className;
    characterDictionary[character_id].frameNumberForCharacter = characterDictionary[characterID].currentParsingFrame;
    characterNameDictionary[className] = character_id;

   /* char debugStr[1000];
    sprintf_s(debugStr,1000,"%s characterId=%d\n",className.c_str(),character_id);
    OutputDebugString(debugStr);*/
  }
}

void Movie::ParseDoABC(SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID )
{
  avmplus::PoolObject * poolObject = core->ParseBlock(GetScriptBuffer(streamReader, tagInfo.tagLen, GetGC()));
  avmplus::ScriptEnv * scriptEnv = core->PreparePool(poolObject);
  scriptEnv->initGlobal();
  scriptEnv->coerceEnter(scriptEnv->global->atom());

  PoolData * poolData = new PoolData(GetGC());
  poolData->pool = poolObject;
  poolData->scriptEnv = scriptEnv;
 
  CharacterDesc & charDesc = characterDictionary[ characterID ];
  NI_ASSERT( charDesc.character, "Character ID is not created" );

  poolDataByFrame[charDesc.currentParsingFrame] = new PoolDataWrapper(poolData);
}

void Movie::ParseCharacter( SwfStreamReader & streamReader, TagInfo & tagInfo, ICharacter* character )
{
  UI16 characterID = streamReader.readUI16();
//  DebugTrace(" ---------------------------------------> CARACTER: %d", characterID);

  NI_ASSERT( character, "Character is null" ); 
  NI_ASSERT( characterID > 0, "Character ID should be > 0" );
  CharacterDesc & charDesc = characterDictionary[ characterID ];
  NI_ASSERT( !charDesc.character, "Character ID already used" );

  charDesc.character = character;
  character->Load( streamReader, tagInfo, characterID );
}

void Movie::ParseDefineShape( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<ShapeCharacter> shapeCharacter = new ShapeCharacter;
  ParseCharacter( streamReader, tagInfo, shapeCharacter );
}

void Movie::ParseDefineBitmap( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<BitmapCharacter> character = new BitmapCharacter();
  character->SetMovie( this );
  ParseCharacter( streamReader, tagInfo, character );
}

void Movie::ParseDefineJPEGTables( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  NI_ASSERT( !commonJPEGHeader, "There can be only one JPEG Table" );

  if ( tagInfo.tagLen > 0 )
    commonJPEGHeader = jpegreader::CreateHeaderOnly( &streamReader );
}

void Movie::ParseDefineMorphShape( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<MorphCharacter> character = new MorphCharacter();
  ParseCharacter( streamReader, tagInfo, character );
}

void Movie::ParseDefineButton( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<ButtonCharacter> character = new ButtonCharacter();
  ParseCharacter( streamReader, tagInfo, character );
}

void Movie::ParseDefineSprite(SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  UI16 spriteID = streamReader.readUI16();
//  DebugTrace(" ---------------------------------------> CARACTER: %d", spriteID);

  UI16 FrameCount = streamReader.readUI16();
  FrameCount;

  Strong<SpriteCharacter> spriteCharacter;

  spriteCharacter = new MovieCharacter();

//   if ( FrameCount > 1 )
//     spriteCharacter = new MovieCharacter();
//   else
//     spriteCharacter = new SpriteCharacter();

  NI_ASSERT( spriteID > 0, "Character ID should be > 0" );
  NI_ASSERT( !characterDictionary[spriteID].character, "Character ID already used" );
  characterDictionary[spriteID].character = spriteCharacter;

  TagInfo innerTag;

  do 
  {
    streamReader.readTagInfo( innerTag );

    switch ( innerTag.tagType )
    {
    case SWFTags::SWFTAGS_PLACEOBJECT:
    case SWFTags::SWFTAGS_PLACEOBJECT2:
    case SWFTags::SWFTAGS_PLACEOBJECT3: 
      ParsePlaceObject( streamReader, innerTag, spriteID );
      break;
    case SWFTags::SWFTAGS_REMOVEOBJECT:
    case SWFTags::SWFTAGS_REMOVEOBJECT2:
      ParseRemoveObject( streamReader, innerTag, spriteID );
      break;
    case SWFTags::SWFTAGS_SHOWFRAME:
      ParseShowFrame( streamReader, innerTag, spriteID );
      break;
    case SWFTags::SWFTAGS_FRAMELABEL:
      ParseFrameLabel( streamReader, innerTag, spriteID );
      break;
    default:
      streamReader.ignore( innerTag.tagLen );
    }

    //DebugTrace( "  INNER Parsed SWF tag %d (%s)", (int)innerTag.tagType, SWFTags::EnumToString((SWFTags::SWFTagType)innerTag.tagType) );

    NI_ASSERT( streamReader.GetPos() == innerTag.parserPos + innerTag.tagLen, "Tag parsed with error" );

  } while ( innerTag.tagType != SWFTags::SWFTAGS_END );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineText( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<TextCharacter> character = new TextCharacter( fonts );
  ParseCharacter( streamReader, tagInfo, character );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineEditText( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<EditTextCharacter> character = new EditTextCharacter( fonts );
  ParseCharacter( streamReader, tagInfo, character );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineFont3( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  Strong<SwfFont> tag = new SwfFont;
  tag->LoadDefineFont3( streamReader, tagInfo );

  fonts->Put( tag );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineFontName( SwfStreamReader & swf, TagInfo & tagInfo, int characterID )
{
  swf.clearBitreader( true );

  UI16 fontId = swf.readUI16();
  string name, copyrite;
  swf.readString( name );
  swf.readString( copyrite );

  swf.clearBitreader( false );

  SwfFont * font = fonts->GetFontById( fontId );
  NI_VERIFY( font, NStr::StrFmt( "DefineFontName: unknown font id %d (%s)", fontId, name.c_str() ), return );

  font->SetFontName( name, copyrite );

  fonts->FontNameUpdated( fontId );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineFontAlignZones( SwfStreamReader & swf, TagInfo & tagInfo, int characterID )
{
  swf.clearBitreader( true );

  UI16 fontId = swf.readUI16();

  UI32 CSMTableHint = swf.readUBits( 2 );

  UI32 reserved = swf.readUBits( 6 );
  NI_ASSERT( reserved == 0, "" );

  SwfFont * font = fonts->GetFontById( fontId );
  NI_VERIFY( font, NStr::StrFmt( "DefineFontAlignZones: unknown font id %d", fontId ), return );

  font->LoadAlignZonesRecords( swf, CSMTableHint );

  swf.clearBitreader( false );
}


void Movie::ParseCsmTextSettings( SwfStreamReader & swf, TagInfo & tagInfo, int characterID )
{
  swf.clearBitreader( true );

  UI16 textCharId = swf.readUI16();

  CharacterDictionary::iterator it = characterDictionary.find( textCharId );
  NI_VERIFY( it != characterDictionary.end(), NStr::StrFmt( "CSMTextSettings: unknown text character %d", textCharId ), return );

  BasicTextCharacter * textChar = dynamic_cast<BasicTextCharacter *>( it->second.character.Get() );
  if ( textChar )
    textChar->LoadCsmSettings( swf );

  swf.clearBitreader( false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineSound( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID )
{
  Strong<SoundCharacter> character = new SoundCharacter();
  ParseCharacter( streamReader, tagInfo, character );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParsePlaceObject(SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID )
{
  Strong<PlaceObjectTag> tag = new PlaceObjectTag();
  tag->Load( streamReader, tagInfo );

  CharacterDesc & charDesc = characterDictionary[ characterID ];
  NI_ASSERT( charDesc.character, "Character ID is not created" );
  charDesc.character->AddDisplayTag( tag );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseRemoveObject(SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID )
{
  Strong<RemoveObjectTag> tag = new  RemoveObjectTag();
  tag->Load( streamReader, tagInfo );

  CharacterDesc & charDesc = characterDictionary[ characterID ];
  NI_ASSERT( charDesc.character, "Character ID is not created" );
  charDesc.character->AddDisplayTag( tag );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineScaleGrid( SwfStreamReader & streamReader, TagInfo & tagInfo, int _characterID )
{
  UI16 _charID = streamReader.readUI16();

  SWF_RECT scaleGridRect;
  streamReader.readRect( scaleGridRect );

  CharacterDesc & charDesc = characterDictionary[ _charID ];
  NI_ASSERT( charDesc.character, "Character ID is not created" );
  charDesc.character->SetScale9Grid( scaleGridRect );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseShowFrame(SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID )
{
  Strong<ShowFrameTag> tag = new ShowFrameTag();

  CharacterDesc & charDesc = characterDictionary[ characterID ];
  NI_ASSERT( charDesc.character, "Character ID is not created" );
  charDesc.character->AddDisplayTag( tag );

  charDesc.currentParsingFrame++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseDefineSceneAndFrameLabelData( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID )
{
  UI32 SceneCount = streamReader.readUI32Encoded();
  nstl::string label;

  for ( UI32 i = 0; i < SceneCount; ++i )
  {
    UI32 offset = streamReader.readUI32Encoded();
    streamReader.readString( label );   
    sceneLables[ label ] = offset;
  }

  UI32 LablesCount = streamReader.readUI32Encoded();

  for ( UI32 i = 0; i < LablesCount; ++i )
  {
    UI32 offset = streamReader.readUI32Encoded();
    streamReader.readString( label );   
    frameLables[ label ] = offset;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ParseFrameLabel( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID )
{
  nstl::string label;
  streamReader.readString( label );   

  CharacterDesc & charDesc = characterDictionary[ characterID ];
  NI_ASSERT( charDesc.character, "Character ID is not created" );
  charDesc.character->AddFrameLabel( charDesc.currentParsingFrame + 1, label );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Movie::GetFrameNumber( const nstl::string& _label )
{
  FrameLabels::iterator it = frameLables.find( _label );

  if ( it != frameLables.end() )
    return it->second;

  return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Movie::IsBroadcastEvent( avmplus::Atom typeAtom )
{
  bool isBroadcast = 
    ( typeAtom == core->GetEventTypes().kFRAME_CONSTRUCTED ) || 
    ( typeAtom == core->GetEventTypes().kENTER_FRAME ) ||
    ( typeAtom == core->GetEventTypes().kEXIT_FRAME ) ||
    ( typeAtom == core->GetEventTypes().kRENDER );

  return isBroadcast;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Movie::HasBroadcastListner( avmplus::Atom typeAtom, avmplus::EventDispatcherObject* object )
{
  BroadcastDictionary::const_iterator dictIt = broadcastDictionary.find( typeAtom );

  if ( dictIt == broadcastDictionary.end() )
    return false;

  BroadcastSubscribers::iterator it = dictIt->second.begin();
  BroadcastSubscribers::iterator last = dictIt->second.end();

  for ( ; it != last; ++it )
  {
    if ( (*it)->Get()->object == object )
      return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::AddBroadcastListner( avmplus::Atom typeAtom, avmplus::FunctionObject* listener, avmplus::EventDispatcherObject* object )
{
  BroadcastSubscribers& subscribers = broadcastDictionary[ typeAtom ];

  BroadcastSubscribers::iterator it = subscribers.begin();

  for ( ; it != subscribers.end(); ++it )
  {
    if ( (*it)->Get()->function == listener && (*it)->Get()->object == object )
    {
      if ( (*it)->Get()->markToRemove )
        (*it)->Get()->markToRemove = false;

      return;
    }
  }

  Strong<FunctionWrapper> objectWrapper = new FunctionWrapper(new FunctionObjectGCRoot(core->GetGC(), listener, object));
  subscribers.push_back( objectWrapper );

  totalListenersCount.AddValue(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::RemoveBroadcastListner( avmplus::Atom typeAtom, avmplus::FunctionObject* listener, avmplus::EventDispatcherObject* object )
{
  BroadcastDictionary::const_iterator dictIt = broadcastDictionary.find( typeAtom );

  if ( dictIt == broadcastDictionary.end() )
    return;

  BroadcastSubscribers::iterator it = dictIt->second.begin();
  BroadcastSubscribers::iterator last = dictIt->second.end();

  for ( ; it != last; ++it )
  {
    if ( (*it)->Get()->function == listener && (*it)->Get()->object == object )
    {
      (*it)->Get()->markToRemove = true;
      return;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::ClearBroadcastListners()
{
  BroadcastDictionary::iterator dictIt = broadcastDictionary.begin();
  BroadcastDictionary::iterator dictLast = broadcastDictionary.end();

  for ( ; dictIt != broadcastDictionary.end(); ++dictIt )
  {
    BroadcastSubscribers::iterator it = dictIt->second.begin();

    for ( ; it != dictIt->second.end(); )
    {
      if ( (*it)->Get()->markToRemove )
      {
        it = dictIt->second.erase( it );
        totalListenersCount.DecValue(1);
      }
      else
      {
        ++it;
      }
    }
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::EventObject* Movie::GetBroadcastEvent( avmplus::Atom typeAtom )
{
  BroadcastEvents::iterator it = broadcastEvents.find( typeAtom );

  if ( it != broadcastEvents.end() )
    return it->second->Get()->event;

  avmplus::EventObject* event = core->CreateSimpleEvent( typeAtom );

  Strong<EventWrapper> objectWrapper = new EventWrapper( new EventObjectGCRoot( core->GetGC(), event ) );
  broadcastEvents[ typeAtom ] = objectWrapper;

  return objectWrapper->Get()->event;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::FireBroadcastEvent( avmplus::Atom typeAtom )
{
  BroadcastDictionary::const_iterator dictIt = broadcastDictionary.find( typeAtom );

  if ( dictIt == broadcastDictionary.end() )
    return;

  BroadcastSubscribers::iterator it = dictIt->second.begin();
  BroadcastSubscribers::iterator last = dictIt->second.end();
  
  avmplus::EventObject* event = GetBroadcastEvent( typeAtom );

  for ( ; it != last; ++it )
  {
    if ( (*it)->Get()->markToRemove )
      continue;

    event->SetCurrentTarget( (*it)->Get()->object );
    event->SetTarget( (*it)->Get()->object );

    avmplus::Atom argv[2] = { (*it)->Get()->function->atom(), event->atom() };
    int argc = 1;

    (*it)->Get()->function->call(argc, argv);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Movie::Advance( float deltaTime )
{
  timeFromStart += deltaTime;
  currentFrameTime += deltaTime;

  if (currentFrameTime >= frameTime )
  {
    int numFrame = int( currentFrameTime / frameTime );
    currentFrameTime = fmodf( currentFrameTime, frameTime );

    for ( int j = 0; j < numFrame; ++j )
    {
      FireBroadcastEvent( core->GetEventTypes().kFRAME_CONSTRUCTED );

      for ( uint i = 0; i < advanceList.size(); ++i )
      {
        advanceList[i]->AdvanceNextFrame();
      }

      FireBroadcastEvent( core->GetEventTypes().kENTER_FRAME );

      for ( uint i = 0; i < advanceList.size(); ++i )
      {
        advanceList[i]->RunThisFrameScript();
      }

      FireBroadcastEvent( core->GetEventTypes().kEXIT_FRAME );
      FireBroadcastEvent( core->GetEventTypes().kRENDER );
      ClearBroadcastListners();
    }
  }

  {
    static nstl::vector<avmplus::TimerObject*> timerCache;
    timerCache.resize( timers.size() );

    for ( uint i = 0; i < timers.size(); ++i )
    {
      timerCache[i] = timers[i];
    }

    for ( int i = 0; i < timerCache.size(); ++i )
    {
      timerCache[i]->Advance( deltaTime );
    }
  }
}

void Movie::ConvertToFlashCoords( const UI::Point & screenPoint, SWF_POINT& flashPoint )
{
  float rx = float( screenPoint.x ) / float( viewportWidth );
  float ry = float( screenPoint.y ) / float( viewportHeight );

  if ( stageProvider )
  {
    flashPoint.X = rx * stageProvider->GetStageWidth() * 20.f;
    flashPoint.Y = ry * stageProvider->GetStageHeight() * 20.f;
  }
  else
  {
    flashPoint.X = rx * swfInfo.rect.GetWidth() * 20.f;
    flashPoint.Y = ry * swfInfo.rect.GetHeight() * 20.f;
  }
}

void Movie::ConvertFromFlashCoords( const SWF_POINT& flashPoint, UI::Point &screenPoint )
{
  float rx = float( flashPoint.X ) * float( viewportWidth );
  float ry = float( flashPoint.Y ) * float( viewportHeight );

  if ( stageProvider )
  {
    screenPoint.x = rx / stageProvider->GetStageWidth() / 20.f;
    screenPoint.y = ry / stageProvider->GetStageHeight() / 20.f;
  }
  else
  {
    screenPoint.x = rx / swfInfo.rect.GetWidth() / 20.f;
    screenPoint.y = ry / swfInfo.rect.GetHeight() / 20.f;
  }
}

void Movie::AddFSListner( UI::FlashContainer2* _parentWnd, const char* listnerId, UI::IFSCommandListner* _fsListner )
{
  FSListners::iterator it = fsListners.find( listnerId );

  NI_VERIFY( it == fsListners.end(), "FS listner with such a name already inserted", return );

  fsListners[ listnerId ] = _fsListner;

  parentWnd = _parentWnd;
}

void Movie::RemoveFSListner( const char* listnerId )
{
  fsListners.erase( listnerId );
}

void Movie::OnFSCommand( avmplus::AvmString listnerId, avmplus::AvmString arg )
{
  avmplus::StUTF8String listnerIdT( listnerId );
   
  FSListners::iterator it = fsListners.find( listnerIdT.c_str() );

  if ( it == fsListners.end() )
    return;

  UI::IFSCommandListner * listener = it->second;

  NI_VERIFY(listener, NStr::StrFmt( "listener for key %s somehow died", listnerIdT.c_str() ), return);

  avmplus::StUTF8String argT( arg );
  avmplus::StUTF16String argTW( arg );
  
  listener->OnFSCommand( parentWnd, listnerIdT.c_str(), argT.c_str(), (wchar_t*)argTW.c_str() );
  
}

void Movie::UpdateDraggedSprite()
{
  if ( draggedSprite && draggedSprite->get_parent() )
  {
    SWF_POINT flashPointStart;
    SWF_POINT flashPoint; 
    SWF_POINT flashPointStartLocal;
    SWF_POINT flashPointLocal; 

    ConvertToFlashCoords( draggedStartPos, flashPointStart );
    ConvertToFlashCoords( lastMousePos, flashPoint );

    draggedSprite->get_parent()->GlobalToLocal( flashPointLocal, flashPoint );
    draggedSprite->get_parent()->GlobalToLocal( flashPointStartLocal, flashPointStart );

    double newX = draggedStartX - ( flashPointStartLocal.X - flashPointLocal.X ) / flash::TWIP ;
    double newY = draggedStartY - ( flashPointStartLocal.Y - flashPointLocal.Y ) / flash::TWIP ;

    if (useDragRectangle)
    {
      newX = max (min(draggedMaxX, newX), draggedMinX);
      newY = max (min(draggedMaxY, newY), draggedMinY);
    }

    draggedSprite->set_x( newX );
    draggedSprite->set_y( newY );
  }
}

bool Movie::IsMouseUnderDisplayObject()
{
  return (topMostDisplayObject != 0 && topMostDisplayObject != stage);
}


bool Movie::OnMouseMove( const UI::Point & point )
{
  avmplus::MouseEventClass * mouseEventClass = core->GetClassCache().GetClass<avmplus::MouseEventClass>( EFlashClassID::MouseEventClass );

  if ( stage )
  {
    SWF_POINT flashPoint;
    SWF_POINT localPoint; 

    ConvertToFlashCoords( lastMousePos, flashPoint );

    UpdateDraggedSprite();

    {
      avmplus::DisplayObjectObject* newTopMostObject = stage->GetTopMostObject( flashPoint );

      //TODO Sasha LOOK at it :)
      if (!newTopMostObject )
        newTopMostObject = stage;

      if ( draggedSprite )
        draggedSprite->SetDropTarget( newTopMostObject );

      if ( newTopMostObject != topMostDisplayObject )
      {
        if ( topMostDisplayObject && ( !IsBlocked() || topMostDisplayObject->IsNonBlocked() ) )
        {
          topMostDisplayObject->GlobalToLocal( localPoint, flashPoint );

          avmplus::MouseEventObject* mouseOut = mouseEventClass->CreateMouseEvent( "mouseOut", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, 0 ); 
          avmplus::MouseEventObject* rollOut = mouseEventClass->CreateMouseEvent( "rollOut", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, newTopMostObject ); 

          topMostDisplayObject->dispatchEventFunction( mouseOut );
          topMostDisplayObject->dispatchEventFunction( rollOut );
        }

        avmplus::DisplayObjectObject* oldTopMostDisplayObject = topMostDisplayObject;
        topMostDisplayObject = newTopMostObject;

        if ( topMostDisplayObject && ( !IsBlocked() || topMostDisplayObject->IsNonBlocked() ) )
        {
          topMostDisplayObject->GlobalToLocal( localPoint, flashPoint );

          avmplus::MouseEventObject* mouseOver = mouseEventClass->CreateMouseEvent( "mouseOver", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, 0 ); 
          avmplus::MouseEventObject* rollOver = mouseEventClass->CreateMouseEvent( "rollOver", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, oldTopMostDisplayObject ); 

          topMostDisplayObject->dispatchEventFunction( mouseOver );
          topMostDisplayObject->dispatchEventFunction( rollOver );
        }
      }
    }

    if ( topMostDisplayObject && lastMousePos != point && ( !IsBlocked() || topMostDisplayObject->IsNonBlocked() ))
    {
      avmplus::MouseEventObject* mouseMove = mouseEventClass->CreateMouseEvent( "mouseMove", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, 0 ); 

      topMostDisplayObject->dispatchEventFunction( mouseMove );
    }

    lastMousePos = point;
  }

  //TODO Sasha LOOK at it :)
  return IsMouseUnderDisplayObject();
}

bool Movie::OnMouseOut( const UI::Point & point )
{
  avmplus::MouseEventClass * mouseEventClass = core->GetClassCache().GetClass<avmplus::MouseEventClass>( EFlashClassID::MouseEventClass );

  if ( stage )
  {
    SWF_POINT flashPoint;
    SWF_POINT localPoint; 

    ConvertToFlashCoords( lastMousePos, flashPoint );

    if ( topMostDisplayObject && ( !IsBlocked() || topMostDisplayObject->IsNonBlocked() ) )
    {
      topMostDisplayObject->GlobalToLocal( localPoint, flashPoint );

      avmplus::MouseEventObject* mouseOut = mouseEventClass->CreateMouseEvent( "mouseOut", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, 0 ); 
      avmplus::MouseEventObject* rollOut = mouseEventClass->CreateMouseEvent( "rollOut", flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, true, 0 ); 

      topMostDisplayObject->dispatchEventFunction( mouseOut );
      topMostDisplayObject->dispatchEventFunction( rollOut );

      topMostDisplayObject = 0;
    }

    lastMousePos = point;
  }

  return true;
}

bool Movie::OnMouseDown( UI::EMButton::Enum mbutton, const UI::Point & point, bool & captureFocus )
{
  SimpleMouseEvent( topMostDisplayObject, mbutton, (mbutton == UI::EMButton::Left) ? "mouseDown" : "mouseRightDown", captureFocus );

  objectMouseDown = topMostDisplayObject;

  if ( g_DebugMouse && topMostDisplayObject )
  {
    avmplus::AvmString name = topMostDisplayObject->get_name();
    avmplus::StUTF8String nameT( name );

    DebugTrace( " DisplayObject clicked: %s", nameT.c_str() );
  }

  return IsMouseUnderDisplayObject();
}


bool Movie::OnScroll( int delta )
{
  if ( !topMostDisplayObject )
    return false;

  avmplus::MouseEventClass * mouseEventClass = core->GetClassCache().GetClass<avmplus::MouseEventClass>( EFlashClassID::MouseEventClass );
  avmplus::MouseEventObject* mouseEvent = mouseEventClass->CreateMouseEvent( "mouseWheel", 0, 0, 0, 0, false, 0, -delta ); 

  topMostDisplayObject ->dispatchEventFunction( mouseEvent );

  return IsMouseUnderDisplayObject();
}


bool Movie::OnMouseUp( UI::EMButton::Enum mbutton )
{
  bool captureFocus = false;

//   if ( draggedSprite )
//   {
//     SimpleMouseEvent( draggedSprite, mbutton, (mbutton == UI::EMButton::Left) ? "mouseUp" : "mouseRightUp", captureFocus );
//     return true;
//   }

  SimpleMouseEvent( topMostDisplayObject, mbutton, (mbutton == UI::EMButton::Left) ? "mouseUp" : "mouseRightUp", captureFocus );

  if ( objectMouseDown == topMostDisplayObject )
  {
    if ( doubleClickRegistred )
      SimpleMouseEvent( topMostDisplayObject, mbutton, (mbutton == UI::EMButton::Left) ? "doubleClick" : "doubleRightClick", captureFocus );
    else
      SimpleMouseEvent( topMostDisplayObject, mbutton, (mbutton == UI::EMButton::Left) ? "click" : "clickRight", captureFocus );
}

  doubleClickRegistred = false;

  objectMouseDown = 0;

  return IsMouseUnderDisplayObject();
}


bool Movie::OnDoubleClick( UI::EMButton::Enum mbutton, const UI::Point & point )
{
  bool captureFocus = false;
  doubleClickRegistred = true;
  return OnMouseDown( mbutton, point, captureFocus );
}


void Movie::SetDraggedSprite( avmplus::SpriteObject* _sprite, bool lockCenter, bool _useDragRectangle, double minX , double maxX , double minY , double maxY )
{
  if ( !_sprite )
  {
     draggedSprite = 0;
     return;
  }


 
  if ( lockCenter )
  {
    SWF_POINT flashPoint; 
    SWF_POINT flashPointLocal; 

    if ( _sprite->get_parent() )
    {
      ConvertToFlashCoords( lastMousePos, flashPoint );
      _sprite->get_parent()->GlobalToLocal( flashPointLocal, flashPoint );
    }

    draggedStartX = flashPointLocal.X / flash::TWIP;
    draggedStartY = flashPointLocal.Y / flash::TWIP;

    _sprite->set_x( draggedStartX );
    _sprite->set_y( draggedStartY );
  }
  else
  {
    draggedStartX = _sprite->get_x();
    draggedStartY = _sprite->get_y();
  }

  draggedStartPos = lastMousePos;

  useDragRectangle = _useDragRectangle;

  draggedMinX = minX;
  draggedMaxX = maxX;

  draggedMinY = minY;
  draggedMaxY = maxY;

  draggedSprite = _sprite;
}


void Movie::OnChar( int ch )
{
  if ( stage->get_focus() )
  {
    stage->get_focus()->OnChar( ch );
  }
}


void Movie::OnKeyPressed( int code, bool down )
{
  if ( stage->get_focus() )
  {
    stage->get_focus()->OnKeyPressed( code, down );
  }
}


bool Movie::SimpleMouseEvent( avmplus::DisplayObjectObject * _object, UI::EMButton::Enum mbutton, const char* eventType, bool & captureFocus )
{
  //DebugTrace( "Flash Mouse Event: %s", eventType );

  captureFocus = TryCaptureFocus();

  if ( _object && ( !IsBlocked() || _object->IsNonBlocked() ) )
  {
    SWF_POINT flashPoint;
    SWF_POINT localPoint; 

    ConvertToFlashCoords( lastMousePos, flashPoint );
    _object->GlobalToLocal( localPoint, flashPoint );

    bool primaryButton = (mbutton == UI::EMButton::Left);

    avmplus::MouseEventClass * mouseEventClass = core->GetClassCache().GetClass<avmplus::MouseEventClass>( EFlashClassID::MouseEventClass );
    avmplus::MouseEventObject* mouseUp = mouseEventClass->CreateMouseEvent( eventType, flashPoint.X, flashPoint.Y, localPoint.X, localPoint.Y, primaryButton, 0 ); 

    _object->dispatchEventFunction( mouseUp );
  }

  return true;
}


bool Movie::TryCaptureFocus()
{
  if ( topMostDisplayObject )
  {
    avmplus::DisplayObjectObject * dobj = topMostDisplayObject;
    avmplus::InteractiveObjectObject * io = dynamic_cast<avmplus::InteractiveObjectObject *>( dobj );
    if ( io )
    {
      avmplus::InteractiveObjectObject * prev = stage->get_focus();

      if ( prev )
        io->OnFocusLoss( io );

      if ( io->OnFocusGain( prev ) )
      {
        //TODO: create events
        stage->set_focus( io );
        return true;
      }
    }
  }

  return false;
}


void Movie::ReleaseFocus()
{
  avmplus::InteractiveObjectObject * f = stage->get_focus();
  if ( f )
  {
    f->OnFocusLoss( 0 );
    stage->set_focus( 0 );
  }
}


void Movie::SetViewport( int x, int y, int width, int height, float scaleCoeff )
{
  viewportX = x;
  viewportY = y;
  viewportWidth = width;
  viewportHeight = height;

  DebugTrace("Movie::SetViewport (w,h) = (%d, %d)", width, height);

  if ( fontRender )
  {
    fontRender->SetViewport( viewportX, viewportY, viewportWidth, viewportHeight ); 

    float movieX1 = swfInfo.rect.X1;
    float movieY1 = swfInfo.rect.Y1;
    float movieX2 = swfInfo.rect.X2;
    float movieY2 = swfInfo.rect.Y2;

    if ( stageProvider )
    {
      movieX1 = 0.f;
      movieY1 = 0.f;
      movieX2 = PIXELS_TO_TWIPS( stageProvider->GetStageWidth() );
      movieY2 = PIXELS_TO_TWIPS( stageProvider->GetStageHeight() );
    }

    fontRender->SetMovieRect( movieX1, movieY1, movieX2 - movieX1, movieY2 - movieY1 );
  }

  CalculatePixelScale();

  if ( stage )
  {
    stage->FireResolutionScaleCoeff(scaleCoeff);
    stage->OnMovedSized();
    stage->Fire_RESIZE();
  }
}

void Movie::CalculatePixelScale()
{
  float movieWidth = float( swfInfo.rect.GetWidth() );
  float movieHeight = float( swfInfo.rect.GetHeight() );

  if ( stageProvider )
  {
    movieWidth = stageProvider->GetStageWidth();
    movieHeight = stageProvider->GetStageHeight();
  }

  float	scale_x = float( viewportWidth ) / TWIPS_TO_PIXELS( movieWidth );
  float	scale_y = float( viewportHeight ) / TWIPS_TO_PIXELS( movieHeight );
  pixelScale = max( scale_x, scale_y );
}

void Movie::Render()
{
  if(RENDER_DISABLED)
    return;

  NI_ASSERT( renderer, "Flash renderer is null" );

  float movieX1 = swfInfo.rect.X1;
  float movieY1 = swfInfo.rect.Y1;
  float movieX2 = swfInfo.rect.X2;
  float movieY2 = swfInfo.rect.Y2;

  if ( stageProvider )
  {
    movieX1 = 0.f;
    movieY1 = 0.f;
    movieX2 = PIXELS_TO_TWIPS( stageProvider->GetStageWidth() );
    movieY2 = PIXELS_TO_TWIPS( stageProvider->GetStageHeight() );
  }

  renderer->BeginDisplay(
    viewportX, viewportY,
    viewportWidth, viewportHeight,
    movieX1, movieX2,
    movieY1, movieY2, true);

  if ( stage )
  {
    SWF_MATRIX matrix; 
    SWF_CXFORMWITHALPHA cxform;

    stage->Render( renderer, matrix, cxform, EFlashBlendMode::NORMAL, false );
  }

  renderer->EndDisplay();
}

void Movie::InitLoaders()
{
  loaders[SWFTags::SWFTAGS_SYMBOLCLASS] = &Movie::ParseSymbolClass; 
  loaders[SWFTags::SWFTAGS_DOABC] = &Movie::ParseDoABC;
  loaders[SWFTags::SWFTAGS_DEFINESCENEANDFRAMELABELDATA] = &Movie::ParseDefineSceneAndFrameLabelData;
  loaders[SWFTags::SWFTAGS_FRAMELABEL] = &Movie::ParseFrameLabel;

  loaders[SWFTags::SWFTAGS_DEFINESHAPE]  = &Movie::ParseDefineShape;
  loaders[SWFTags::SWFTAGS_DEFINESHAPE2] = &Movie::ParseDefineShape;
  loaders[SWFTags::SWFTAGS_DEFINESHAPE3] = &Movie::ParseDefineShape;
  loaders[SWFTags::SWFTAGS_DEFINESHAPE4] = &Movie::ParseDefineShape;

  loaders[SWFTags::SWFTAGS_DEFINESPRITE] = &Movie::ParseDefineSprite;

  loaders[SWFTags::SWFTAGS_JPEGTABLES] = &Movie::ParseDefineJPEGTables;
  loaders[SWFTags::SWFTAGS_DEFINEBITS] = &Movie::ParseDefineBitmap;
  loaders[SWFTags::SWFTAGS_DEFINEBITSJPEG2] = &Movie::ParseDefineBitmap;
  loaders[SWFTags::SWFTAGS_DEFINEBITSJPEG3] = &Movie::ParseDefineBitmap;
  loaders[SWFTags::SWFTAGS_DEFINEBITSJPEG4] = &Movie::ParseDefineBitmap;
  loaders[SWFTags::SWFTAGS_DEFINEBITSLOSSLESS] = &Movie::ParseDefineBitmap;
  loaders[SWFTags::SWFTAGS_DEFINEBITSLOSSLESS2] = &Movie::ParseDefineBitmap;

  loaders[SWFTags::SWFTAGS_DEFINEMORPHSHAPE] = &Movie::ParseDefineMorphShape;
  loaders[SWFTags::SWFTAGS_DEFINEMORPHSHAPE2] = &Movie::ParseDefineMorphShape;

  loaders[SWFTags::SWFTAGS_DEFINEBUTTON] = &Movie::ParseDefineButton;
  loaders[SWFTags::SWFTAGS_DEFINEBUTTON2] = &Movie::ParseDefineButton; 

  loaders[SWFTags::SWFTAGS_PLACEOBJECT]  = &Movie::ParsePlaceObject;
  loaders[SWFTags::SWFTAGS_PLACEOBJECT2] = &Movie::ParsePlaceObject;
  loaders[SWFTags::SWFTAGS_PLACEOBJECT3] = &Movie::ParsePlaceObject;
  loaders[SWFTags::SWFTAGS_REMOVEOBJECT] = &Movie::ParseRemoveObject;
  loaders[SWFTags::SWFTAGS_REMOVEOBJECT2] = &Movie::ParseRemoveObject;
  loaders[SWFTags::SWFTAGS_SHOWFRAME] = &Movie::ParseShowFrame;

  loaders[SWFTags::SWFTAGS_DEFINETEXT] = &Movie::ParseDefineText;
  loaders[SWFTags::SWFTAGS_DEFINETEXT2] = &Movie::ParseDefineText;
  loaders[SWFTags::SWFTAGS_DEFINEEDITTEXT] = &Movie::ParseDefineEditText;

  loaders[SWFTags::SWFTAGS_DEFINEFONT3] =           &Movie::ParseDefineFont3;
  loaders[SWFTags::SWFTAGS_DEFINEFONTNAME] =        &Movie::ParseDefineFontName;
  loaders[SWFTags::SWFTAGS_DEFINEFONTALIGNZONES] =  &Movie::ParseDefineFontAlignZones;
  loaders[SWFTags::SWFTAGS_CSMTEXTSETTINGS] =       &Movie::ParseCsmTextSettings;

  loaders[SWFTags::SWFTAGS_DEFINESOUND] = &Movie::ParseDefineSound;

  loaders[SWFTags::SWFTAGS_DEFINESCALINGGRID] = &Movie::ParseDefineScaleGrid;
  
}

bool Movie::IsImageTag( SWFTags::SWFTagType tagType ) const
{
  switch( tagType )
  {
  case SWFTags::SWFTAGS_JPEGTABLES:
  case SWFTags::SWFTAGS_DEFINEBITS:
  case SWFTags::SWFTAGS_DEFINEBITSJPEG2:
  case SWFTags::SWFTAGS_DEFINEBITSJPEG3:
  case SWFTags::SWFTAGS_DEFINEBITSJPEG4:
  case SWFTags::SWFTAGS_DEFINEBITSLOSSLESS:
  case SWFTags::SWFTAGS_DEFINEBITSLOSSLESS2:
    return true;
  }

  return false;
}

avmplus::DisplayObjectObject* Movie::CreateObjectByCharacter( int characterId, PlaceObjectTag* _placeTag, avmplus::SpriteObject* _parentObject )
{
  NI_PROFILE_FUNCTION

  CharacterDictionary::iterator it = characterDictionary.find( characterId );

  NI_VERIFY( it != characterDictionary.end(), "Unknown character", return 0 ); 

  avmplus::ClassClosure * classClosure = 0;
  CharacterDesc& desc = it->second;

  NI_VERIFY( desc.character, "Null character pointer", return 0 );

  if ( desc.frameNumberForCharacter != -1 )
  {
    PoolDataByFrame::iterator itF = poolDataByFrame.find( desc.frameNumberForCharacter );
    NI_VERIFY( itF != poolDataByFrame.end(), "Unknown pool to create character", return 0 ); 

    avmplus::PoolObject * poolObject = poolDataByFrame[ desc.frameNumberForCharacter ]->Get()->pool;
    avmplus::ScriptEnv * scriptEnv = poolDataByFrame[ desc.frameNumberForCharacter ]->Get()->scriptEnv; 

    if ( !desc.symbolClass.empty() )
    {
      avmplus::Traits * traits = poolObject->getBuiltinTraits(core->internConstantStringLatin1(desc.symbolClass.c_str()));

      if (traits) 
        classClosure = core->GetClassByTraits(traits, scriptEnv);
    }
  }

  avmplus::DisplayObjectObject * newDisplayObject = 0;

  {
    if ( classClosure )
    {
      avmplus::ScriptObject* scriptObject = classClosure->newInstance();
      newDisplayObject = dynamic_cast<avmplus::DisplayObjectObject *>( scriptObject );

      if ( !newDisplayObject )
      {
        classClosure = desc.character->GetDefaultDisplayClass( core );
        newDisplayObject = dynamic_cast<avmplus::DisplayObjectObject *>( classClosure->newInstance() );
        NI_ASSERT( newDisplayObject, " GetDefaultDisplayClass must return DisplayObject based object" );

        desc.character->InitWithNonDisplayObject( newDisplayObject, scriptObject );
      }
    }
    else
    {
      classClosure = desc.character->GetDefaultDisplayClass( core );
      newDisplayObject = dynamic_cast<avmplus::DisplayObjectObject *>( classClosure->newInstance() );
      
      NI_ASSERT( newDisplayObject, " GetDefaultDisplayClass must return DisplayObject based object" );
    }
  }

  newDisplayObject->SetCharacterID( characterId );
  desc.character->InitObject( newDisplayObject );

  // set default name
  {
    static char name[100];
    sprintf_s( name, "Character_%d", characterId );
    newDisplayObject->set_name( core->newStringLatin1( name ) );
  }
  
  if ( _placeTag )
    _placeTag->InitalizeObject( newDisplayObject, _parentObject );

  {
    using avmplus::ExceptionFrame;
    using avmplus::Exception;

    TRY( core, avmplus::kCatchAction_ReportAsError )
    {
      //call ctor
      avmplus::Atom args[] = {newDisplayObject->atom()};
      classClosure->ivtable()->init->coerceEnter(0, args);
    }
     CATCH ( Exception *exception )
     {
       core->PrintException(exception);
     }
     END_CATCH
     END_TRY
  }

  //initialize properties before ctor
  return newDisplayObject;
}

BitmapCharacter* Movie::GetBitmapCharacter( int characterId )
{
  CharacterDictionary::iterator it = characterDictionary.find( characterId );
  
  if ( it == characterDictionary.end() )
    return 0;

  BitmapCharacter * bitmapCharacter = nival_cast<BitmapCharacter>( it->second.character.Get() );

  return bitmapCharacter;
}

void Movie::MarkRepeatableBitmapCharacter( int characterId )
{
  characterHints[ characterId ].repeatableBitmap = true;
}

bool Movie::IsBitmapCharacterRepeatable( int characterId ) const
{
  if ( characterHints.find( characterId ) ==  characterHints.end() )
    return false;

  return characterHints[ characterId ].repeatableBitmap;
}


ICharacter * Movie::GetCharacterByName(avmplus::AvmString name)
{
  avmplus::StIndexableUTF8String utf8Name(name);
  //name
  //TODO convert name to string
  nstl::string nstlName (utf8Name.c_str()); 

  
  //remove namespaces
  int lastPointPos = nstlName.find_last_of(':');
  nstlName = (lastPointPos ==-1)? nstlName: nstlName.substr(lastPointPos+1);

  //if (nstlName != "MovieClip")
  //  DebugTrace(nstlName.c_str());

  //if (nstlName == "TestInputText")
  //{
  //  int a=0;
  //  a++;
  //}

  //TODO:: САша З проверь пожалуйста строчки выше. там формат такой EscMenu::TestInputText
  //так что это скорее подпорка
  CharacterNameDictionary::iterator nameIter = characterNameDictionary.find(nstlName);

  if (nameIter == characterNameDictionary.end())
  {
    return 0;
  }

  int charID = nameIter->second;
  CharacterDictionary::iterator iter = characterDictionary.find(charID);
  if (iter == characterDictionary.end())
    return 0;

  return iter->second.character;
}

void Movie::SubscribeForAdvance( avmplus::TimerObject * timer )
{
  timers.add( timer );
}

void Movie::UnsubscribeForAdvance( avmplus::TimerObject * timer )
{
  int id = timers.indexOf( timer );

  if ( id != -1 )
    timers.removeAt( id );
}

void Movie::SubscribeForAdvanceMC( avmplus::MovieClipObject * mcObject )
{
  int id = advanceList.indexOf( mcObject );

  if ( id == -1 )
  {
    advanceList.add( mcObject );
    totalAdvancersCount.AddValue(1);
  }
}

void Movie::UnsubscribeForAdvanceMC( avmplus::MovieClipObject * mcObject )
{
  int id = advanceList.indexOf( mcObject );
  
  if ( id != -1 )
  {
    advanceList.removeAt( id );
    totalAdvancersCount.DecValue(1);
  }
}

void Movie::UnsubscribeForAdvanceByID( int timerID )
{
  int indexToRemove = -1;

  for ( int i = 0; i < (int)timers.size(); ++i )
  {
    if ( timers[i]->GetTimerID() == timerID )
    {
      indexToRemove = i;
      break;
    }
  }

  if ( indexToRemove != -1 )
    timers.removeAt( indexToRemove );
}

bool Movie::CallMethod( const char * path, char const* name )
{
  FLASH_ENTER_FUNCTION_RETURN( GetGC(), false ) // не двигаем выше

  if ( rootMovieClip )
    return rootMovieClip->CallMethod( path, name );

  return false;
}

bool Movie::CallMethod( const char * path, char const* name, const char* arg1 )
{
  FLASH_ENTER_FUNCTION_RETURN( GetGC(), false ) // не двигаем выше

  if ( rootMovieClip )
    return rootMovieClip->CallMethod( path, name, arg1 );

  return false;
}

bool Movie::CallMethod( const char * path, char const* name, const char* arg1, const char* arg2 )
{
  FLASH_ENTER_FUNCTION_RETURN( GetGC(), false ) // не двигаем выше

  if ( rootMovieClip )
    return rootMovieClip->CallMethod( path, name, arg1, arg2 );

  return false;
}

bool Movie::CallMethod( const char * path, const char * name, int arg1, int arg2 )
{
  FLASH_ENTER_FUNCTION_RETURN( GetGC(), false ) // не двигаем выше

  if ( rootMovieClip )
    return rootMovieClip->CallMethod( path, name, arg1, arg2 );

  return false;
}

bool Movie::CallMethod( const char * path, char const* name, const vector<avmplus::Atom> & args )
{
  FLASH_ENTER_FUNCTION_RETURN( GetGC(), false ) // не двигаем выше

  if ( rootMovieClip )
    return rootMovieClip->CallMethod( path, name, args );

  return false;
}

void Movie::DumpControl()
{
  //if ( rootMovieClip )
    //rootMovieClip->DumpHierarchy( 0 );

  for ( int i = 10; i > 0; --i )
  {
    if ( int(advanceList.size()) - i >= 0 )
    {
      avmplus::MovieClipObject* mc = advanceList[ advanceList.size() - i ];

      if ( mc )
        DebugTrace( " AL: %d from %d ( %s ), frame %d playing: %d", int(advanceList.size()), int(advanceList.size()) - i, mc->GetNameDebug().c_str(), mc->get_currentFrame(), int(mc->IsPlaying()) );
    }
  }
}

void Movie::ChangeTexture( const char * path, const Render::Texture2DRef& _texture )
{
  if ( rootMovieClip )
  {
    avmplus::BitmapObject* bitmap = dynamic_cast<avmplus::BitmapObject*>( avmplus::FlashScriptObject::FindChild( rootMovieClip, path ) );

    if ( bitmap )
      bitmap->SetTexture( _texture );
  }
}

bool Movie::GetDisplayObjectSize( const char * path, int& width, int& height, int& x, int& y )
{
  if ( rootMovieClip )
  {
    avmplus::DisplayObjectObject* object = dynamic_cast<avmplus::DisplayObjectObject*>( avmplus::FlashScriptObject::FindChild( rootMovieClip, path ) );

    if ( object )
    {
      flash::SWF_MATRIX worldMatrix;
      object->GetWorldMatrix( worldMatrix );

      width = object->get_width() * worldMatrix.GetXScale();
      height = object->get_height() * worldMatrix.GetYScale();

      flash::SWF_RECT rect3;
      object->GetWorldBounds( rect3 );

      flash::SWF_POINT fpnt1( rect3.X1, rect3.Y1 );
      UI::Point rpnt1;
      ConvertFromFlashCoords( fpnt1, rpnt1 );

      x = rpnt1.x;
      y = rpnt1.y;

      return true;
    }
  }

  return false;
}

void Movie::SetTextureSmooth( const char * path, bool makeSmooth )
{
  if ( rootMovieClip )
  {
    avmplus::BitmapObject* object = dynamic_cast<avmplus::BitmapObject*>( avmplus::FlashScriptObject::FindChild( rootMovieClip, path ) );

    if ( object )
      object->SetTextureSmoothing( makeSmooth );
  }
}

avmplus::ScriptObject * Movie::GetFlashObject( const char * path )
{
  if ( rootMovieClip )
  {
    return avmplus::FlashScriptObject::FindChild(rootMovieClip, path);
  }

  return 0;
}

avmplus::DisplayObjectObject* Movie::FindDisplayObjectByInstance( const char* _instanceName )
{
  FLASH_ENTER_FUNCTION_RETURN( GetGC(), 0 ); // не двигаем выше

  if ( rootMovieClip )
  {
    return rootMovieClip->FindDisplayObjectByInstance( _instanceName );
  }

  return 0;
}



bool Movie::IsMouseUnderUnblockedElement()
{
  if( !IsBlocked())
    return false;

  if (topMostDisplayObject)
    return topMostDisplayObject->IsNonBlocked();

  return false;
}



void Movie::SetUIBlockFadeValue( float _fade, const CVec4& _fadeColor )
{
  blockingFade = _fade;

  float rLum = 0.2225f;
  float gLum = 0.7169f;
  float bLum = 0.0606f;

  float r0 = Lerp( rLum, 0.f, _fade );
  float r1 = Lerp( rLum, 1.f, _fade );
  float g0 = Lerp( gLum, 0.f, _fade );
  float g1 = Lerp( gLum, 1.f, _fade );
  float b0 = Lerp( bLum, 0.f, _fade );
  float b1 = Lerp( bLum, 1.f, _fade );

  float cr = Lerp( _fadeColor.r, 1.f, _fade );
  float cg = Lerp( _fadeColor.g, 1.f, _fade );
  float cb = Lerp( _fadeColor.b, 1.f, _fade );

  uiBlockColorMatrix.Set( 
    r1 * cr,  g0 * cr,  b0 * cr,  0.f,
    r0 * cg,  g1 * cg,  b0 * cg,  0.f,
    r0 * cb,  g0 * cb,  b1 * cb,  0.f,
    0.f, 0.f, 0.f, 1.f 
  );

  float br = 1.f;// + 0.7f * ( 1.f - _fade );
  float bg = 1.f;// + 0.1f * ( 1.f - _fade );
  float bb = 1.f;// + 0.1f * ( 1.f - _fade );

  uiNonBlockColorMatrix.Set( 
    br,  0.f, 0.f,  0.f,
    0.f,  bg, 0.f,  0.f,
    0.f, 0.f,  bb,  0.f,
    0.f, 0.f, 0.f,  1.f 
  );
}

void Movie::FadeBlockedColor( flash::SWF_RGBA& _color, bool _nonBlocked )
{
  CVec3 source( _color.r, _color.g, _color.b );
  CVec3 result;

  if ( _nonBlocked )
    uiNonBlockColorMatrix.Transform( &result, source );
  else
    uiBlockColorMatrix.Transform( &result, source );

  _color.r = Clamp( result.r, 0.f, 255.f );
  _color.g = Clamp( result.g, 0.f, 255.f );
  _color.b = Clamp( result.b, 0.f, 255.f );
}


//implementation of the helper function.
avmplus::ReadOnlyScriptBufferImpl * GetScriptBuffer(SwfStreamReader &parser, int taglen, MMgc::GC *gc)
{
  int tagstart = parser.GetPos();
  const int kDoAbcLazyInitializeFlag = 1;
  kDoAbcLazyInitializeFlag;

  uint32_t flags = parser.readUI32();
  flags;
  AvmAssert(flags&kDoAbcLazyInitializeFlag);

  // skip the abc name
  //TODO may be read it actually?
  parser.skipString();

  // parse and execute the abc.
  int abclen = taglen - (parser.GetPos() - tagstart);
  avmplus::ReadOnlyScriptBufferImpl* abcbuf = new (gc) avmplus::ReadOnlyScriptBufferImpl(&parser.swf[parser.GetPos()], abclen);

  parser.ignore( abclen );

  return abcbuf;
}

} //namespace flash
