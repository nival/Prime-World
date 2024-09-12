#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../Scripts/lua.hpp"
#include "View.h"

namespace UI
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SProviderInfo
{
  TObjectViewProviderPtr provider;
  TObjectViewProviderNewFrame newFrame;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef hash_map<string,SProviderInfo> TObjectViewProviders;
TObjectViewProviders g_objectViewProviders;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterObjectViewProvider( string objectType, TObjectViewProviderPtr provider, TObjectViewProviderNewFrame newFrame )
{
  TObjectViewProviders::const_iterator it = g_objectViewProviders.find( objectType );
  NI_VERIFY( it == g_objectViewProviders.end(), "Same type of object view already registered!", return );
  NI_VERIFY( provider, "Invalid provider!", return );
  g_objectViewProviders[ objectType ].provider = provider;
  g_objectViewProviders[ objectType ].newFrame = newFrame;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObjectViewProviderBase *CreateObjectViewProvider( const string & objectType )
{
  TObjectViewProviders::const_iterator it = g_objectViewProviders.find( objectType );
  if ( it == g_objectViewProviders.end() )
    return 0;
  return it->second.provider();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewFrameForAllObjectViewProviders()
{
  for ( TObjectViewProviders::const_iterator it = g_objectViewProviders.begin(); it != g_objectViewProviders.end(); ++it )
  {
    TObjectViewProviderNewFrame func = it->second.newFrame;
    if ( func )
      func();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(ObjectView, Window)
  LUA_METHOD(SetRenderRate)
  LUA_METHOD(SetRenderTime)

  LUA_METHOD(SetViewObject)

  LUA_METHOD(GetViewObjectType)
  LUA_METHOD(GetViewObjectID)

  LUA_METHOD(CommandViewObject)
  LUA_METHOD(CommandViewObjectEx)
END_LUA_TYPEINFO(ObjectView)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::OnInit()
{
  Window::OnInit();

  needUpdate = true;

  NDb::UIViewLayout *pLayout = GetObjectViewLayout();
  SetViewObject( pLayout->provider, pLayout->address );

  // possible enviroment: pViewLayout->enviroment

  frameTime = 1.0f / Max( 1, pLayout->framesPerSecond );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ObjectView::ShouldUpdateInt() const
{
  for ( const Window * pWnd = this; pWnd; pWnd = pWnd->GetParent() )
    if( !pWnd->IsVisible() )
      return false;

  Rect rect = GetWindowRect();
  rect.Intersect( GetCropRect() );
  if ( rect.IsEmpty() )
    return false;

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::OnMovedSized()
{
  const bool croppedOut = !ShouldUpdateInt() || !provider;
  if ( ( lastCroppedOut && !croppedOut ) || GetSize().x != lastRenderXSize || GetSize().y != lastRenderYSize )
    needUpdate = true;
  else
    needUpdateRects = true;

  Window::OnMovedSized();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::OnRefresh( float deltaTime )
{
  if ( IsFullyEnabled() && provider )
  {
    if ( !timeLimited || timeLeft > 0 )
    {
      provider->Clock( deltaTime );

      if ( timeLeft <= deltaTime )
        timeLeft = 0;
      else
        timeLeft -= deltaTime;

      if ( frameTimeLeft <= deltaTime )
      {
        frameTimeLeft = 0;
        if ( frameTime > 0 )
        {
          if ( provider->CheckUpdate( waitingForUpdateRender ) )
          {
            //frameTimeLeft = frameTime - ( deltaTime % frameTime );
            //@todo Oleg
            frameTimeLeft = deltaTime;
            needUpdate = true;
          }
        }
      }
      else
        frameTimeLeft -= deltaTime;
    }
  }

  const bool shouldUpdate = ShouldUpdateInt();
  if ( lastCroppedOut && shouldUpdate )
    needUpdate = true;

  if ( needUpdate )
  {
    needUpdate = false;
    needUpdateRects = true;

    lastCroppedOut = !shouldUpdate;
    if ( shouldUpdate && provider )
    {
      lastRenderXSize = GetSize().x;
      lastRenderYSize = GetSize().y;
      view.SetImageTexture( Render::Texture2DRef(provider->UpdateTexture( lastRenderXSize, lastRenderYSize )) );
    }
  }

  if ( needUpdateRects )
  {
    needUpdateRects = false;

    view.SetDrawRect( GetWindowRect() );
    view.SetCropRect( GetCropRect() );
  }

  view.SetMaterialOpacity( GetOpacity() );

  //view.Update();

  Window::OnRefresh( deltaTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::Render()
{
  view.Render();

  Window::Render();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::SetViewObject( string type, string id )
{
  provider = CreateObjectViewProvider( type );
  objectType = type;
  NDb::UIViewLayout *pLayout = GetObjectViewLayout();
  if ( !provider )
  {
    provider = CreateObjectViewProvider( pLayout->provider );
    id = pLayout->address;
    objectType = pLayout->provider;
  }
  if ( provider )
    provider->SetObjectForView( id );
  objectID = id;
  view.SetImageTexture( Render::Texture2DRef() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::CommandViewObject( string cmd, float s )
{
  if ( !provider )
    return;
  provider->CommandObjectOfView( cmd, s, "" );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectView::CommandViewObjectEx( string cmd, string s, float n )
{
  if ( !provider )
    return;
  provider->CommandObjectOfView( cmd, n, s );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REGISTER_CONTROLTYPE( NDb::UIViewLayout, ObjectView );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
