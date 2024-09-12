#pragma once

#include <Render/texture.h>

#include "../../FSCommandListner.h"

#include "Natives/display/DisplayObject.h"
#include "Natives/events/Event.h"

#include "FlashMovieAvmCore.h"
#include "DisplayTags.h"
#include "swf_parse.h"

namespace Render
{
  _interface IFlashRenderer;
}

namespace UI
{
  namespace EMButton { enum Enum; };
  _interface IWindowNameMapInterface;
  _interface IFSCommandListner;
}

namespace avmplus
{
  class MovieClipObject;
  class LoaderInfoObject;
  class StageObject;
  class DisplayObjectObject;
  class EventDispatcherObject;
  class ScriptObject;
  class EventObject;
}

namespace jpegreader
{
  _interface IInput;
}

namespace flash
{

class DisplayTag;
class PlaceObjectTag;
class BitmapCharacter;
_interface IStageProvider;
_interface IStageFocusHandler;

class FontsDictionary;
_interface IFontRender;

typedef nstl::map<int, Strong<PoolDataWrapper>> PoolDataByFrame;

class Movie: public flash::SafeGCRoot<Movie>
{
public:
  Movie( IStageProvider* _stageProvider, MMgc::GC *gc, IFontRender * _fontRender, IStageFocusHandler * _focusHandler );
  ~Movie();

  FlashMovieAvmCore * GetAvmCore() { return core; }

  const nstl::string& GetFileName() { return sourceFilename; }

  void SetFlashRenderer( Render::IFlashRenderer* _renderer );
  Render::IFlashRenderer* GetFlashRenderer() { return renderer; }

  bool LoadFile( const char* filename );
  bool LoadFile( Stream* stream, const char* filename );

  const SWFInfo& GetSWFInfo() const { return swfInfo; };

  void Advance(float deltaTime);

  void AddFSListner( UI::FlashContainer2* _parentWnd, const char* listnerId, UI::IFSCommandListner* _fsListner );
  void RemoveFSListner( const char* listnerId );

  void OnFSCommand( avmplus::AvmString command, avmplus::AvmString arg );

  void CollectLocalizationProperties( nstl::list<nstl::string>& _proplist );
  void SetLocalizationProperty( const char* _name, const wchar_t* _value );
  void FinishLocalization();
 
  avmplus::ScriptObject * GetFlashObject(const char * path);

  avmplus::DisplayObjectObject* FindDisplayObjectByInstance( const char* _instanceName );

  bool CallMethod(const char * path, char const* name, const vector<avmplus::Atom> & args);
  bool CallMethod( const char * path, char const* name );
  bool CallMethod( const char * path, char const* name, const char* arg1 );
  bool CallMethod( const char * path, char const* name, const char* arg1, const char* arg2 );
  bool CallMethod( const char * path, const char * name, int arg1, int arg2 );

  void DumpControl();

  void ChangeTexture( const char * path, const Render::Texture2DRef& _texture );

  bool GetDisplayObjectSize( const char * path, int& width, int& height, int& x, int& y );
  void SetTextureSmooth( const char * path, bool makeSmooth );

  bool OnMouseMove( const UI::Point & mouse );
  bool OnMouseOut( const UI::Point & mouse );
  bool OnMouseDown( UI::EMButton::Enum mbutton, const UI::Point & point, bool & captureFocus );
  bool OnMouseUp( UI::EMButton::Enum mbutton );
  bool OnDoubleClick( UI::EMButton::Enum mbutton, const UI::Point & point );

  bool OnScroll( int delta );

  bool IsMouseUnderDisplayObject();

  void OnChar( int ch );
  void OnKeyPressed( int code, bool down );

  void SetDraggedSprite( avmplus::SpriteObject* _sprite, bool lockCenter, bool _useDragRectangle = false, double minX =0, double maxX = 0, double minY = 0, double maxY = 0  );
  avmplus::SpriteObject* GetDraggedSprite() { return draggedSprite; }

  float GetPixelScale() const { return pixelScale; }

  void ReleaseFocus();

  void SetViewport( int x, int y, int width, int height, float scaleCoeff );
  void Render();

  PoolDataByFrame & GetPoolData(){ return poolDataByFrame;}
  
  avmplus::DisplayObjectObject* CreateObjectByCharacter( int characterId, PlaceObjectTag* _placeTag, avmplus::SpriteObject* _parentObject );
  
  BitmapCharacter* GetBitmapCharacter( int characterId );

  void MarkRepeatableBitmapCharacter( int characterId );
  bool IsBitmapCharacterRepeatable( int characterId ) const;

  ICharacter * GetCharacterByName(avmplus::AvmString name);
  
  float GetFrameTime() { return frameTime; }
  double GetTimeFromStart() { return timeFromStart; } // in seconds

  void SubscribeForAdvance( avmplus::TimerObject * timer );
  void UnsubscribeForAdvance( avmplus::TimerObject * timer );
  void UnsubscribeForAdvanceByID( int timerID );

  void SubscribeForAdvanceMC( avmplus::MovieClipObject * mcObject );
  void UnsubscribeForAdvanceMC( avmplus::MovieClipObject * mcObject );

  IFontRender * FontRender() { return fontRender; }
  FontsDictionary * Fonts() { return fonts; }

  //Just to pass pointer to TextContainer
  void StoreNameMapInterface( UI::IWindowNameMapInterface * iface ) { nameMapInterface = iface; }
  UI::IWindowNameMapInterface * GetNameMapInterface() { return nameMapInterface; }

  jpegreader::IInput* GetCommonJPEGHeader() { return commonJPEGHeader; }

  const UI::Point& GetMousePoint() { return lastMousePos; }
  const void GetFlashMousePoint( SWF_POINT& flashPoint ) {  ConvertToFlashCoords( lastMousePos, flashPoint ); }

  int GetFrameNumber( const nstl::string& _label );

  bool IsBroadcastEvent( avmplus::Atom typeAtom );
  bool HasBroadcastListner( avmplus::Atom typeAtom, avmplus::EventDispatcherObject* object );
  void AddBroadcastListner( avmplus::Atom typeAtom, avmplus::FunctionObject* listener, avmplus::EventDispatcherObject* object );
  void RemoveBroadcastListner( avmplus::Atom typeAtom, avmplus::FunctionObject* listener, avmplus::EventDispatcherObject* object );
  void ClearBroadcastListners();
  void FireBroadcastEvent( avmplus::Atom typeAtom );

  // blocking
  void SetUIBlocked( bool _isUIBlocked ) { isUIBlocked = _isUIBlocked; }
  bool IsBlocked() const { return isUIBlocked; }
  bool IsMouseUnderUnblockedElement();

  void SetUIBlockFadeValue( float _fade, const CVec4& _fadeColor );
  void FadeBlockedColor( flash::SWF_RGBA& _color, bool _nonBlocked );
  const SHMatrix& GetUIBlockColorMatrix() const { return uiBlockColorMatrix; }
  const SHMatrix& GetUINonBlockColorMatrix() const { return uiNonBlockColorMatrix; }
  const CVec4& GetUIBlockAddColor() const { return uiBlockAddColor; }

private:
  struct CharacterDesc
  {
    nstl::string symbolClass;
    int frameNumberForCharacter;
    int currentParsingFrame;
    Strong<ICharacter> character;

    CharacterDesc() : frameNumberForCharacter(-1), currentParsingFrame(0) {}
  };

  typedef void (Movie::*LoaderMethod)( SwfStreamReader &, TagInfo &, int parentCharacterID );

  typedef map<SWFTags::SWFTagType, LoaderMethod> Loaders;

  typedef nstl::list<TagInfo> SwfTagInfos;

  typedef nstl::hash_map<int, CharacterDesc > CharacterDictionary;
  typedef nstl::hash_map<nstl::string, int > CharacterNameDictionary;

  typedef avmplus::List<avmplus::TimerObject*, avmplus::LIST_RCObjects> Timers;
  typedef avmplus::List<avmplus::MovieClipObject*, avmplus::LIST_RCObjects> MovieClipObjects;

  typedef nstl::hash_map<nstl::string, UI32> FrameLabels;

  struct CharacterHint
  {
    bool repeatableBitmap;

    CharacterHint() : repeatableBitmap(false) {}
  };

  typedef nstl::hash_map<int, CharacterHint> CharacterHints;

  //core is unmanaged memory structure.
  //so we have to care to delete it ourself
  FlashMovieAvmCore * core;

  Loaders loaders;
  SwfStreamReader streamReader;

  //swf data
  SwfTagInfos tags;
  SWFInfo swfInfo;

  // timing

  Timers timers;
  MovieClipObjects advanceList;

  double timeFromStart;
  float frameTime;
  float currentFrameTime;

  // labels
  FrameLabels sceneLables;
  FrameLabels frameLables;

  //avmplus classes
  DRC( avmplus::SpriteObject* ) rootMovieClip;
  DRC( avmplus::LoaderInfoObject * ) loaderInfo;
  DRC( avmplus::StageObject * ) stage;

  DRC( avmplus::DisplayObjectObject * ) topMostDisplayObject;
  DRC( avmplus::DisplayObjectObject * ) objectMouseDown;

  //dragging
  DRC( avmplus::SpriteObject* ) draggedSprite;
  double draggedStartX;
  double draggedStartY;

  double draggedMinX;
  double draggedMaxX;

  double draggedMinY;
  double draggedMaxY;
  
  bool useDragRectangle;

  UI::Point draggedStartPos;


  UI::Point lastMousePos;

  bool doubleClickRegistred;

  CharacterDictionary characterDictionary;
  CharacterNameDictionary characterNameDictionary;
  CharacterHints characterHints;

  Strong<FontsDictionary> fonts;
  Strong<IFontRender> fontRender;

  Weak<UI::IWindowNameMapInterface> nameMapInterface;

  typedef nstl::hash_map<nstl::string, Weak<UI::IFSCommandListner>> FSListners;
  FSListners fsListners;

  Weak<UI::FlashContainer2> parentWnd;

  //Parsed pools
  //NOTE that not every frame can contain abc data. so for now its map. usually its one to two elements
  PoolDataByFrame poolDataByFrame;

  Weak<IStageProvider> stageProvider;
  Weak<IStageFocusHandler> stageFocusHandler;

  int viewportX;
  int viewportY;
  int viewportWidth;
  int viewportHeight;

  float pixelScale;

  nstl::string sourceFilename;
  
  Strong<jpegreader::IInput> commonJPEGHeader;

  Weak<Render::IFlashRenderer> renderer;

  bool isUIBlocked;
  SHMatrix uiBlockColorMatrix;
  SHMatrix uiNonBlockColorMatrix;
  CVec4 uiBlockAddColor;
  float blockingFade;


  struct FunctionObjectGCRoot: public MMgc::GCRoot
  {
    FunctionObjectGCRoot( MMgc::GC * gc, avmplus::FunctionObject * _function, avmplus::EventDispatcherObject* _object ) 
      : MMgc::GCRoot(gc), function(_function), object(_object), markToRemove(false) {} 

    DRC(avmplus::FunctionObject*) function;
    DRC(avmplus::EventDispatcherObject*) object;
    bool markToRemove;
  };

  struct EventObjectGCRoot : public MMgc::GCRoot
  {
    EventObjectGCRoot( MMgc::GC * gc, avmplus::EventObject * _event ) 
      : MMgc::GCRoot(gc), event(_event) {} 

    DRC(avmplus::EventObject*) event;
  };

  typedef avmplus::GCRootWrapper<FunctionObjectGCRoot> FunctionWrapper;
  typedef avmplus::GCRootWrapper<EventObjectGCRoot> EventWrapper;

  typedef nstl::list<Strong<FunctionWrapper>> BroadcastSubscribers;
  typedef nstl::map<avmplus::Atom, BroadcastSubscribers> BroadcastDictionary;
  typedef nstl::map<avmplus::Atom, Strong<EventWrapper>> BroadcastEvents;

  BroadcastDictionary broadcastDictionary;
  BroadcastEvents broadcastEvents;

  //parsing functions
  //basic parsing
  void ParseSymbolClass( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDoABC( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseShowFrame( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineSceneAndFrameLabelData( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseFrameLabel( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  
  //shapes sprites etc
  void ParseDefineShape( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineSprite( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineJPEGTables( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineBitmap( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineMorphShape( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineButton( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParsePlaceObject( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseRemoveObject( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );

  //text
  void ParseDefineText( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );
  void ParseDefineEditText( SwfStreamReader & streamReader, TagInfo & tagInfo, int parentCharacterID );

  //fonts
  void ParseDefineFont3( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID );
  void ParseDefineFontName( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID );
  void ParseDefineFontAlignZones( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID );
  void ParseCsmTextSettings( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID );

  void ParseDefineScaleGrid( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID );

  //sound
  void ParseDefineSound( SwfStreamReader & streamReader, TagInfo & tagInfo, int characterID );

  void ParseCharacter( SwfStreamReader & streamReader, TagInfo & tagInfo, ICharacter* character );

  void InitLoaders();

  bool ProcessReadTags( SwfStreamReader & streamReader, bool imagePass );

  bool LoadFileInternal(SwfStreamReader & streamReader);

  bool IsImageTag( SWFTags::SWFTagType tagType ) const;

  void CalculatePixelScale();

  void ConvertToFlashCoords( const UI::Point & screenPoint, SWF_POINT& flashPoint );
  void ConvertFromFlashCoords( const SWF_POINT& flashPoint, UI::Point &screenPoint );

  void UpdateDraggedSprite();

  bool SimpleMouseEvent( avmplus::DisplayObjectObject * _object, UI::EMButton::Enum mbutton, const char* eventType, bool & captureFocus );

  bool TryCaptureFocus();

  avmplus::EventObject* GetBroadcastEvent( avmplus::Atom typeAtom );

  avmplus::ScriptObject * GetLocalizationObject();
};

} //namespace flash
