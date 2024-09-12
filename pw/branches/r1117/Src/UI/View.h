#pragma once
#include "Window.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CObjectViewProviderBase : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( CObjectViewProviderBase, BaseObjectST );
public:
  virtual bool SetObjectForView( const string & id ) { return  false; }
  virtual void CommandObjectOfView( const string & cmd, double n, const string & s ) {}
  virtual void Clock( float deltaTime ) {}
  virtual Render::Texture2D *UpdateTexture( int w, int h ) { return 0; }
  virtual bool CheckUpdate( bool & waitFlag ) { return false; }

  // TODO: provider-based lists (id -> visobjs)
  // TODO: set enviroment (id ~ type) and its params
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ObjectView : public Window
{
  NI_DECLARE_REFCOUNT_CLASS_1( ObjectView, Window );

  string objectType;
  string objectID;

  Strong<CObjectViewProviderBase> provider;
  //@iA@TODO: динамически обновлять стиль ImageComponent по pViewLayout->maskStyle
  ImageComponent view;

  bool needUpdate;
  bool needUpdateRects;

  bool timeLimited;
  float timeLeft;
  float frameTime;
  float frameTimeLeft;

  int lastRenderXSize;
  int lastRenderYSize;
  bool lastCroppedOut;
  bool waitingForUpdateRender;

  NDb::UIViewLayout * GetObjectViewLayout() { return GetLayoutClone<NDb::UIViewLayout>(); }

  bool ShouldUpdateInt() const;

protected:
  virtual void OnRefresh( float deltaTime );
  virtual void OnMovedSized();
  virtual void OnInit();
  virtual void Render();

public:
  ObjectView()
    : needUpdate( true )
    , needUpdateRects( true )
    , timeLimited( false )
    , timeLeft(0)
    , frameTime(0)
    , frameTimeLeft(0)
    , lastRenderXSize(0)
    , lastRenderYSize(0)
    , lastCroppedOut( true )
    , waitingForUpdateRender( false )
  {}

  static void NewFrameForAllProviders();

public:
  void SetRenderRate( int fps ) { frameTime = 1.f / Max(0,fps); }

  void SetRenderTime( float t ) { timeLimited = (t > 0); timeLeft = t; }

  void SetViewObject( string type, string id );

  string GetViewObjectType() { return objectType; }
  string GetViewObjectID() { return objectID; }

  void CommandViewObject( string cmd, float n );

  void CommandViewObjectEx( string cmd, string s, float n );

  DECLARE_LUA_TYPEINFO(ObjectView);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef CObjectViewProviderBase *(* TObjectViewProviderPtr)();
typedef void (* TObjectViewProviderNewFrame)();
void RegisterObjectViewProvider( string objectType, TObjectViewProviderPtr provider, TObjectViewProviderNewFrame newFrame );
#define REGISTER_OBJECTVIEW_PROVIDER( viewType, viewProvider, nmspace ) UI::CObjectViewProviderBase *UI_CreateObjectViewProvider_##viewProvider() { return new nmspace::viewProvider(); } void UI_NewFrameForObjectViewProvider_##viewProvider() { nmspace::viewProvider::NewFrame(); } struct CRegisterObjectViewProvider_##viewProvider { CRegisterObjectViewProvider_##viewProvider() { UI::RegisterObjectViewProvider( viewType, UI_CreateObjectViewProvider_##viewProvider, UI_NewFrameForObjectViewProvider_##viewProvider ); } } uiObjectViewRegistrator_##viewProvider;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace UI
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
