#include "stdafx.h"

#include "../Render/FlashRendererInterface.h"

#include "FlashContainer2.h"
#include "Flash/GameSWFIntegration/FlashMovie.h"
#include "Flash/GameSWFIntegration/FlashPlayer.h"
#include "Flash/GameSWFIntegration/FlashEnterFunction.h"
#include "FlashFontsRender.h"

#include "../System/InlineProfiler.h"
#include "Resolution.h"

namespace UI
{

class DebugTestNameMap : public NNameMap::IMap, public BaseObjectST
{
  NAMEMAP_DECLARE
  NI_DECLARE_REFCOUNT_CLASS_2( DebugTestNameMap, NNameMap::IMap, BaseObjectST )

public:
  DebugTestNameMap() : fps( 33 ) {}

  void SetFps( int _fps ) { fps = _fps; }

private:
  int fps;
};

NAMEMAP_BEGIN( DebugTestNameMap )
  NAMEMAP_VAR_RO( fps )
NAMEMAP_END


BEGIN_LUA_TYPEINFO( FlashContainer2, Window )
  LUA_METHOD( CallMethod0 )
  LUA_METHOD( CallMethod1 )
  LUA_METHOD( CallMethod2 )
  LUA_METHOD( AdvanceOneFrame )
  LUA_METHOD( SetManualMode )
  LUA_METHOD( DumpControl )
END_LUA_TYPEINFO( FlashContainer2 )


FlashContainer2::FlashContainer2() :
  flashMovie( 0 ),
  garbageCollector( 0 ),
  manualMode(false),
  useOwnSize(false)
{

}



FlashContainer2::~FlashContainer2()
{
  Clear();
}



void FlashContainer2::Clear()
{
  if ( !garbageCollector )
  {
    NI_ASSERT( !flashMovie, "Flash Movie should be null" );
    return;
  }

  MMGC_ENTER_VOID
  MMGC_GCENTER( garbageCollector )

  if ( flashMovie )
    delete flashMovie;

  flashMovie = 0;
  flashStream = 0;

  if ( garbageCollector )
    mmfx_delete( garbageCollector );
  garbageCollector = 0;
}

void FlashContainer2::OnInit()
{
  Init();

  NameMappedWindow::OnInit();
}

void FlashContainer2::Init()
{
  NDb::UIFlashLayout2 *pLayout = GetFlashLayout();

  if ( pLayout )
  {
    Load( pLayout->srcFileName );
  }
}

void FlashContainer2::Load( const nstl::string& filename )
{
  NI_PROFILE_FUNCTION_MEM

  flash::FlashEnterFunction flashEnterFunction;

  Point controlSz = GetSize();
  Strong<FlashFontsRender> fontsRender = new FlashFontsRender;

  flash::Player::Get();
  MMGC_ENTER_VOID

  NI_ASSERT( !garbageCollector, "Garbage Collector should be null" ); 
  garbageCollector = mmfx_new( MMgc::GC( MMgc::GCHeap::GetGCHeap(), MMgc::GC::kIncrementalGC ) );

  MMGC_GCENTER( garbageCollector )

  flashMovie = new flash::Movie( this, garbageCollector, fontsRender, this );

  flashMovie->SetFlashRenderer( Render::GetUIRenderer()->GetFlashRenderer() );
  flashMovie->StoreNameMapInterface( this );

  float scaleCoeff =  GetUIScreenRatio()!=0?  1.0f/GetUIScreenRatio(): 1.0f;

  const Rect & winRect = GetWindowRect();
  flashMovie->SetViewport( winRect.minx, winRect.miny, winRect.GetSizeX(), winRect.GetSizeY(), scaleCoeff );

  if ( !filename.empty() )
  {
    flashStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

    flashMovie->LoadFile( flashStream, filename.c_str() );

    //nstl::list<string> props;
    //CollectPublicProperties(props);


    NDb::UIFlashLayout2 *pLayout = GetFlashLayout();

    useOwnSize = pLayout->useOwnSize;

    //TODO support exported properties!
    if ( pLayout )
    {
      nstl::vector<NDb::UIFlashProperties>::iterator it = pLayout->properties.begin();
      nstl::vector<NDb::UIFlashProperties>::iterator last = pLayout->properties.end();

      for ( ; it != last; ++it )
      {
        it->propertyValue.DropCache();
        flashMovie->SetLocalizationProperty( it->propertyName.c_str(), it->propertyValue.GetText().c_str() );
      }
      flashMovie->FinishLocalization();
    }

    
  }
}

void FlashContainer2::OnMovedSized()
{
  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )

    const Rect & winRect = GetWindowRect();

    float scaleCoeff =  GetUIScreenRatio()!=0?  1.0f/GetUIScreenRatio(): 1.0f;

    flashMovie->SetViewport( winRect.minx, winRect.miny, winRect.GetSizeX(), winRect.GetSizeY(), scaleCoeff );
  }
}

void FlashContainer2::LoadOnly( const nstl::string& filename, flash::IFontRender* fontRender )
{
  flash::FlashEnterFunction flashEnterFunction;

  flash::Player::Get();
  MMGC_ENTER_VOID

  NI_ASSERT( !garbageCollector, "Garbage Collector should be null" ); 
  garbageCollector = mmfx_new( MMgc::GC(MMgc::GCHeap::GetGCHeap(), MMgc::GC::kIncrementalGC) );

  MMGC_GCENTER( garbageCollector )

  flashMovie = new flash::Movie( this, garbageCollector, fontRender, this );

  if ( !filename.empty() )
  {
    flashStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    flashMovie->LoadFile( flashStream, filename.c_str() );
  }
}

void FlashContainer2::AddFSListner( const char* listerId, IFSCommandListner* _fsListner )
{
  if ( flashMovie )
    flashMovie->AddFSListner( this, listerId, _fsListner );
}

void FlashContainer2::RemoveFSListner( const char* listnerId )
{
  if ( flashMovie )
    flashMovie->RemoveFSListner( listnerId );
}

void FlashContainer2::CollectPublicProperties( nstl::list<nstl::string>& _proplist )
{
  if ( !flashMovie )
    return;

  FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )

  flashMovie->CollectLocalizationProperties( _proplist );
}

void FlashContainer2::Render()
{
  NI_PROFILE_FUNCTION_MEM

  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )
    flashMovie->Render();
  }

  NameMappedWindow::Render();
}


void FlashContainer2::Step( float deltaTime )
{
  NI_PROFILE_FUNCTION_MEM

  if ( !manualMode )
  {
    if ( flashMovie )
    {
      FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )
      flashMovie->Advance( deltaTime );
    }
  }

  NameMappedWindow::Step( deltaTime );
}

void FlashContainer2::AdvanceOneFrame()
{
  if ( !flashMovie )
    return;

  FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )

  flashMovie->Advance( flashMovie->GetFrameTime() );
}


void FlashContainer2::OnStageFocusGain()
{
  SetFocus(true);
}

void FlashContainer2::OnDataChanged()
{
  NameMappedWindow::OnDataChanged();

  Clear();
  Init();
}

bool FlashContainer2::OnMouseMove( const Point & point )
{
  if ( !flashMovie )
    return NameMappedWindow::OnMouseMove( point );

  FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), false );

  Point localPos( point.x - GetWindowRect().x1, point.y - GetWindowRect().y1 );
  return flashMovie->OnMouseMove( localPos );
}

void FlashContainer2::OnMouseOver( bool over, const Point & mouse )
{
  if ( over )
    return;

  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )
    Point localPos( mouse.x - GetWindowRect().x1, mouse.y - GetWindowRect().y1 );
    flashMovie->OnMouseOut( localPos );
  }

  NameMappedWindow::OnMouseOver( over, mouse );
}

bool FlashContainer2::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), false )

    Point localPos( point.x - GetWindowRect().x1, point.y - GetWindowRect().y1 );
    bool captureFocus = false;
    bool result = flashMovie->OnMouseDown( mbutton, localPos, captureFocus );
    if ( captureFocus )
      SetFocus( true );
    return result;
  }

  return NameMappedWindow::OnMouseDown( mbutton, point );
}

bool FlashContainer2::IsMouseUnderWindow()
{
  return flashMovie? flashMovie->IsMouseUnderDisplayObject(): false;
}


bool FlashContainer2::OnMouseUp( EMButton::Enum mbutton )
{
  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), false )
    return flashMovie->OnMouseUp( mbutton );
  }

  return NameMappedWindow::OnMouseUp( mbutton );
}



bool FlashContainer2::OnDoubleClick( EMButton::Enum mbutton, const Point & point )
{
  if ( flashMovie )
  {
	FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), false )
    Point localPos( point.x - GetWindowRect().x1, point.y - GetWindowRect().y1 );
    return flashMovie->OnDoubleClick( mbutton, localPos );
  }

  return NameMappedWindow::OnDoubleClick( mbutton, point );
}


bool UI::FlashContainer2::OnScroll( int delta )
{
  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), false )
    return flashMovie->OnScroll(delta);
  }

  return NameMappedWindow::OnScroll(delta );
}


void FlashContainer2::CallMethod0( const char * path, char const* name )
{
  if ( flashMovie )
    flashMovie->CallMethod( path, name );
}

void FlashContainer2::CallMethod1( const char * path, char const* name, const char* arg1 )
{
  if ( flashMovie )
    flashMovie->CallMethod( path, name, arg1 );
}

void FlashContainer2::CallMethod2( const char * path, char const* name, const char* arg1, const char* arg2 )
{
  if ( flashMovie )
    flashMovie->CallMethod( path, name, arg1, arg2 );
}

void FlashContainer2::DumpControl()
{
  if ( !flashMovie )
    return;

  FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )

  flashMovie->DumpControl();
}

void FlashContainer2::ChangeTexture( const char * path, const Render::Texture2DRef& _texture )
{
  if ( !flashMovie )
    return;

  FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )

  flashMovie->ChangeTexture( path, _texture );
}

bool FlashContainer2::GetDisplayObjectSize( const char * path, int& width, int& height, int& x, int& y )
{
  if ( !flashMovie )
    return false;

  FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), false )
  return flashMovie->GetDisplayObjectSize( path, width, height, x, y );
}

void FlashContainer2::SetTextureSmooth( const char * path, bool makeSmooth )
{
  if ( !flashMovie )
    return;

  FLASH_ENTER_FUNCTION_VOID( flashMovie->GetGC() )

  flashMovie->SetTextureSmooth( path, makeSmooth );
}


int FlashContainer2::GetStageWidth() const 
{ 
  if ( useOwnSize && flashMovie )
    return TWIPS_TO_PIXELS( flashMovie->GetSWFInfo().rect.GetWidth() ); 

  return GetWindowRect().Width(); 
}

int FlashContainer2::GetStageHeight() const 
{ 
  if ( useOwnSize && flashMovie )
    return TWIPS_TO_PIXELS( flashMovie->GetSWFInfo().rect.GetHeight() ); 

  return GetWindowRect().Height(); 
}

bool FlashContainer2::OnKeyboardFocus( bool gotFocus )
{
  bool result = NameMappedWindow::OnKeyboardFocus( gotFocus );

  if ( !gotFocus )
  {
    if ( flashMovie )
    {
      FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), result );
      flashMovie->ReleaseFocus();
    }
  }

  return result;
}



bool FlashContainer2::OnChar( int ch )
{
  if ( !flashMovie )
    return NameMappedWindow::OnChar( ch );

  FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), true );

  flashMovie->OnChar( ch );
  return true;
}



bool FlashContainer2::OnKeyPressed( int code, bool down )
{
  if ( flashMovie )
  {
    FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), true )

    flashMovie->OnKeyPressed( code, down );
    return true;
  }


  return NameMappedWindow::OnKeyPressed( code, down );
}



avmplus::ScriptObject * FlashContainer2::GetFlashObject( const char * path )
{
  if ( !flashMovie )
    return 0;

  FLASH_ENTER_FUNCTION_RETURN( flashMovie->GetGC(), 0 );

  return flashMovie->GetFlashObject(path);
}



void FlashContainer2::SetUIBlocked( bool blocking )
{
  if ( flashMovie )
    flashMovie->SetUIBlocked( blocking );
}



bool UI::FlashContainer2::IsMouseUnderUnblockedElement()
{
  if (flashMovie)
    return flashMovie->IsMouseUnderUnblockedElement();

  return false;
}




void FlashContainer2::SetBlockingFade( float _fade, const CVec4& _fadeColor )
{
  if ( flashMovie )
    flashMovie->SetUIBlockFadeValue( _fade, _fadeColor );
}

void FlashContainer2::SetNonBlockedDisplayObject( avmplus::Atom objectAtom, bool _nonBlocked )
{
  if ( flashMovie )
  {
    avmplus::ScriptObject* scriptObject = flashMovie->GetAvmCore()->atomToScriptObject( objectAtom );
    avmplus::DisplayObjectObject* displayObject = dynamic_cast<avmplus::DisplayObjectObject*>( scriptObject );

    if ( displayObject )
      displayObject->SetNonBlocked( _nonBlocked );
  }
}



REGISTER_CONTROLTYPE( NDb::UIFlashLayout2, FlashContainer2 );

} //namespace UI

NI_DEFINE_REFCOUNT( UI::DebugTestNameMap );
NI_DEFINE_REFCOUNT( UI::FlashContainer2 );
NI_DEFINE_REFCOUNT( flash::IStageFocusHandler );


