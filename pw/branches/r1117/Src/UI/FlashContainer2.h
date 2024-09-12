#pragma once

#include "Flash/GameSWFIntegration/Natives/display/StageProvider.h"

#include "NameMappedWindow.h"
#include "IStageFocusHandler.h"

namespace avmplus
{
  class ScriptObject;
  typedef __int32	int32_t;
  typedef int32_t Atom;
}

namespace NDb
{
	struct UIFlashLayout2;
}

namespace MMgc
{
  class GC;
}

namespace flash
{
  class Movie;
  class Player;
  _interface IFontRender;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

_interface IFSCommandListner ;
class FlashFontsRender;
class DebugTestNameMap;

class FlashContainer2 : public NameMappedWindow, public flash::IStageProvider, flash::IStageFocusHandler
{
	NI_DECLARE_REFCOUNT_CLASS_3( FlashContainer2, NameMappedWindow, flash::IStageProvider, flash::IStageFocusHandler );

  DECLARE_LUA_TYPEINFO( FlashContainer2 );

public:
	FlashContainer2();
  ~FlashContainer2();

  void AddFSListner( const char* listnerId, IFSCommandListner* _fsListner );
  void RemoveFSListner( const char* listnerId );

  void Load( const nstl::string& filename );
  void LoadOnly( const nstl::string& filename, flash::IFontRender* fontRender );

  void CollectPublicProperties( nstl::list<nstl::string>& _proplist );

  avmplus::ScriptObject * GetFlashObject(const char * path);

  // Use numbers due to lua
  void CallMethod0( const char * path, const char * name );
  void CallMethod1( const char * path, const char * name, const char* arg1 );
  void CallMethod2( const char * path, const char * name, const char* arg1, const char* arg2 );

  void ChangeTexture( const char * path, const Render::Texture2DRef& _texture );

  bool GetDisplayObjectSize( const char * path, int& width, int& height, int& x, int& y );
  void SetTextureSmooth( const char * path, bool makeSmooth );

  void DumpControl();
  
  // from IStageProvider

  virtual int GetStageWidth() const;
  virtual int GetStageHeight() const;

  virtual void Invalidate() {}

  // from Window

  virtual void OnInit();
  virtual void Render();

  virtual void OnDataChanged();

  virtual bool OnMouseMove( const Point & mouse );
  virtual void OnMouseOver( bool over, const Point & mouse );
  virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
  virtual bool OnMouseUp( EMButton::Enum mbutton );
  virtual bool OnDoubleClick( EMButton::Enum mbutton, const Point & point );
  virtual bool OnScroll( int delta );

  bool IsMouseUnderWindow();

  virtual bool OnKeyboardFocus( bool gotFocus );
  virtual bool OnChar( int ch );
  virtual bool OnKeyPressed( int code, bool down );

  virtual void OnMovedSized();

  // Movie control
  void SetManualMode( bool _manual ) { manualMode = _manual; }
  void AdvanceOneFrame();

  //flash::IStageFocusHandler

  virtual void OnStageFocusGain();

  // blocking
  void SetUIBlocked( bool blocking );
  bool IsMouseUnderUnblockedElement();
  void SetBlockingFade( float _fade, const CVec4& _fadeColor );
  void SetNonBlockedDisplayObject( avmplus::Atom objectAtom, bool _nonBlocked );

protected:
  virtual void Step( float deltaTime ); // regular update on each frame

  //from NameMappedWindow
  virtual void OnNameMapChanged() {} //TODO: react on anme map changes related to this control

private:

  void Init();
  void Clear();

  flash::Movie * flashMovie; // MMgc::GCRoot - mast be row pointer
  MMgc::GC * garbageCollector;

  CObj<Stream> flashStream;
 
  bool manualMode;
	bool useOwnSize;

  NDb::UIFlashLayout2 * GetFlashLayout() { return GetLayoutClone<NDb::UIFlashLayout2>(); }
};

} // namespace UI

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
