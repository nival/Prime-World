#include "stdafx.h"

#include "EditorUIScene.h"
#include "EditorRender.h"
#include "Utility.h"

#include "../Render/renderresourcemanager.h"

#include "../UI/Window.h"
#include "../UI/WindowPointJob.h"
#include "../UI/SkinStyles.h"
#include "../UI/Resolution.h"
#include "../UI/FontRender.h"

#include "../UI/FlashContainer2.h"
#include "../UI/Flash/GameSWFIntegration/FlashPlayer.h"
#include "../UI/Flash/GameSWFIntegration/FontsRenderInterface.h"
#include "../System/Texts.h"

using namespace System;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{


class WindowContact
{
public:
  static void CallWindowStep( UI::Window * window, float deltaTime )
  {
    window->StepInternal( deltaTime );
  }

  static void CallWindowRender( UI::Window * window )
  {
    window->RenderInternal( 0 );
  }
};


//STL list
typedef  list< Weak<UI::Window> > WindowsList;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PickWindowsJob : public UI::WindowPointJob
{
public:
  PickWindowsJob( const UI::Point & _point ) : UI::WindowPointJob( _point ) {}
  
  virtual bool Act( UI::Window * target )
  {
    result.push_back( target );
    return false;
  }

  const WindowsList & Result() const { return result; }

private:
  WindowsList result;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FindWindowsJob : public UI::IWindowJob
{
public:
  FindWindowsJob( const NDb::DBID & _dbid ) : dbid( _dbid ) {}

  virtual UI::EWindowJobCode::Enum BeforeChildren( UI::Window * target )
  {
    if( target->GetWindowLayoutDBID() == dbid )
      return UI::EWindowJobCode::ReturnThis;
    return UI::EWindowJobCode::Ok;
  }

  virtual UI::EWindowJobCode::Enum AfterChildren( UI::Window * target ) { return UI::EWindowJobCode::ReturnNull; }

private:
  NDb::DBID dbid;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PickAllWindowBoundsJob : public UI::IWindowJob
{
public:
  PickAllWindowBoundsJob( ) {}

  virtual UI::EWindowJobCode::Enum BeforeChildren( UI::Window * target )
  { 
    result.push_back( target );
    return UI::EWindowJobCode::Ok;
  }
  virtual UI::EWindowJobCode::Enum AfterChildren( UI::Window * target ) { return UI::EWindowJobCode::ReturnNull; }
  const WindowsList & Result() const { return result; }
private:
  WindowsList result;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GatherWindowsByRectJob : public UI::IWindowJob
{
public:
  enum EMode { eIntersects, eIncludes };

  GatherWindowsByRectJob() : mode( eIntersects ) {}
  GatherWindowsByRectJob( EMode _mode, const UI::Rect & _rect ) : mode( _mode ), rect( _rect ) {}

  const WindowsList & Result() const { return result; }

private:
  EMode         mode;
  UI::Rect      rect;
  WindowsList   result;

  virtual UI::EWindowJobCode::Enum BeforeChildren( UI::Window * target )
  {
    return target->IsVisible() ? UI::EWindowJobCode::Ok : UI::EWindowJobCode::ReturnNull;
  }

  virtual UI::EWindowJobCode::Enum AfterChildren( UI::Window * target )
  {
    switch( mode )
    {
      case eIntersects:
        if( rect.IsIntersect( target->GetWindowRect() ) )
          result.push_back( target );
        break;
      case eIncludes:
        if( rect.IsInside( target->GetWindowRect() ) )
          result.push_back( target );
        break;
      default:
        ;
    }

    return UI::EWindowJobCode::ReturnNull;
  }
};






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorUIScene::EditorUIScene( IntPtr hWnd ) : 
Editor2DSceneBase( hWnd )
{
  pRootLayout = new Weak<UI::Window>;
  pScreenLogic = new Strong<UI::ScreenLogicBase>;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorUIScene::~EditorUIScene()
{
  this->!EditorUIScene();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorUIScene::!EditorUIScene()
{
  if ( pScreenLogic != nullptr )
  {
    delete pScreenLogic;
    pScreenLogic = nullptr;
  }

  if ( pRootLayout != nullptr )
  {
    delete pRootLayout;
    pRootLayout = nullptr;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI::Window* EditorUIScene::RootLayout::get()
{
  if ( pRootLayout != nullptr )
    return *pRootLayout;
  else
    return nullptr;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorUIScene::LoadLayout( libdb::DB::DBID^ dbId, System::String^ stateName )
{
  *pRootLayout = 0;
  *pScreenLogic = 0;

  ReloadTexts();

  NDb::Ptr<NDb::UILayout> pUILayout = GetObject<NDb::UILayout>( dbId );
  pUILayout.SetState( ToMBCS( stateName ) );

  UI::UpdateScreenResolution( 1280, 1024, true );
  *pScreenLogic = new UI::ScreenLogicBase();

  *pRootLayout = UI::CreateUIWindow( pUILayout, ToMBCS( stateName ).c_str(), *pScreenLogic, 0, "root", false );
  RootLayout->RefreshExternally();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorUIScene::DrawInternal( System::IntPtr hWnd, int width, int height )
{
  if ( RootLayout != nullptr )
  {
    WindowContact::CallWindowStep( RootLayout , 0.0f );
    WindowContact::CallWindowRender( RootLayout );
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorUIScene::TWindowsDbList^ EditorUIScene::PickWindows( int x, int y )
{
  TWindowsDbList^ result = gcnew TWindowsDbList();

  if( RootLayout != nullptr )
  {
    PickWindowsJob job( UI::Point( x , y ) );
    RootLayout->Traverse( &job );

    for( WindowsList::const_iterator it = job.Result().begin(); it != job.Result().end(); ++it )
    {
      const NDb::DBID & dbid = (*it)->GetWindowLayoutDBID();
      result->Add( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
    }
  }

  return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Collections::Generic::List<System::Drawing::Rectangle>^ EditorUIScene::GetAllWindowBounds()
{
  System::Collections::Generic::List<System::Drawing::Rectangle>^ result = gcnew System::Collections::Generic::List<System::Drawing::Rectangle>();

  if( RootLayout != nullptr )
  {
    PickAllWindowBoundsJob job;
    RootLayout->Traverse( &job );
    for( WindowsList::const_iterator it = job.Result().begin(); it != job.Result().end(); ++it )
    {
      const UI::Rect & winRect = (*it)->GetWindowRect();
      result->Add( System::Drawing::Rectangle( winRect.left, winRect.top, winRect.GetSize().x, winRect.GetSize().y ) );
    }
  }

  return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorUIScene::TWindowsDbList^ EditorUIScene::PickWindows( System::Drawing::Rectangle area )
{
  TWindowsDbList^ result = gcnew TWindowsDbList();

  if( RootLayout != nullptr )
  {
    UI::Rect rect( area.Left, area.Top, area.Right, area.Bottom );

    GatherWindowsByRectJob job( GatherWindowsByRectJob::eIncludes, rect );
    RootLayout->Traverse( &job );

    for( WindowsList::const_iterator it = job.Result().begin(); it != job.Result().end(); ++it )
    {
      const NDb::DBID & dbid = (*it)->GetWindowLayoutDBID();
      result->Add( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
    }
  }

  return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
libdb::DB::DBID^ EditorUIScene::GetWindowParent( libdb::DB::DBID^ wnd )
{
  UI::Window * window = FindWindow( wnd );
  if( !window )
    return nullptr;

  window = window->GetParent();

  if( !window )
    return nullptr;

  return libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( window->GetWindowLayoutDBID() ) ) );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Drawing::Rectangle EditorUIScene::GetWindowScreenPosition( libdb::DB::DBID^ wnd )
{
  UI::Window * window = FindWindow( wnd );
  if( window )
  {
    const UI::Rect & winRect = window->GetWindowRect();
    return System::Drawing::Rectangle( winRect.left, winRect.top, winRect.GetSize().x, winRect.GetSize().y );
  }

  return System::Drawing::Rectangle( 0, 0, 0, 0 );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI::Window * EditorUIScene::FindWindow( libdb::DB::DBID^ wnd )
{
  if( nullptr == RootLayout )
    return 0;

  NDb::DBID dbid( ToMBCS( wnd->Name ) );
  FindWindowsJob job( dbid );
  return RootLayout->Traverse( &job );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorUIScene::SetVisible( libdb::DB::DBID^ wnd, bool visible )
{
  UI::Window * window = FindWindow( wnd );
  if( window )
  {
    window->OverrideVisibility( visible ? UI::EVisibilityOverride::ForceVisible : UI::EVisibilityOverride::ForceInvisible );
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorUIScene::SetState( libdb::DB::DBID^ wnd, System::String^ stateName )
{
  UI::Window * window = FindWindow( wnd );
  if( window )
  {
    window->SetState( ToMBCS( stateName ).c_str() );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::String^ EditorUIScene::GetState( libdb::DB::DBID^ wnd )
{
  UI::Window * window = FindWindow( wnd );
  if( window )
    return FromMBCS( window->GetState() );
  else
    return System::String::Empty;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Collections::Generic::List<System::String^>^ EditorUIScene::GetFlashPublicFields( System::String^ source )
{
  System::Collections::Generic::List<System::String^>^ result = gcnew System::Collections::Generic::List<System::String^>();

  class MockFontInstance : public flash::IFontInstance, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MockFontInstance, flash::IFontInstance, BaseObjectST );
  public:
    MockFontInstance() {}
    virtual void RenderGlyph( wchar_t c, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color ) {}
    virtual void RenderText( const wchar_t * text, size_t length, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color, const flash::SWF_RECT & cropRect  ) {}
    virtual float GetStringLength( const wchar_t * text, unsigned length, float maxWidth, unsigned * charsFitIn, float additionalAdvance ) { if ( charsFitIn ) *charsFitIn = 1; return 10.f; };
    virtual float Height() const { return 10; } 
    virtual float Ascent() const { return 7; }
    virtual float Descent() const { return 1; }
    virtual float GapAbove() const { return 1; }
    virtual float GapUnder() const { return 1; }
    virtual float DefaultGlyphWidth() const { return 4; }
    virtual void  SetBevel( bool _drawBevel, const flash::SWF_RGBA& _color ) {}
  };

  class MockFontRender : public flash::IFontRender, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MockFontRender, flash::IFontRender, BaseObjectST );
  public:
    MockFontRender() {}

    virtual void SetViewport( int x, int y, int width, int height ) {}
    virtual void SetMovieRect( float x, float y, float width, float height ) {} //Flash twips
    virtual flash::IFontInstance * FindFont( const char * name, int height, bool bold, int italic, const flash::SFontMetricInfo * metric ) { return new MockFontInstance; }
    virtual void DebugLine( float x0, float y0, float x1, float y1, const flash::SWF_RGBA & color ) {}
  };

  MockFontRender mockFontRender;
  UI::FlashContainer2* container = new UI::FlashContainer2();
  
  container->LoadOnly( ToMBCS( source ), &mockFontRender );

  nstl::list<nstl::string> proplist;
  container->CollectPublicProperties( proplist );

  nstl::list<nstl::string>::iterator it = proplist.begin();
  nstl::list<nstl::string>::iterator last = proplist.end();

  for ( ; it != last; ++it )
  {
    result->Add( FromMBCS( *it ) );
  }

  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorUIScene::StoreTextsCache( System::String^ fileName )
{
  ::StoreTextsCache( ToMBCS( fileName ).c_str(), true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EditorUIScene::StoreTextsCache( System::String^ fileName, System::Collections::Generic::List<System::String^>^ textFiles )
{
  int result = 0;
  ::ReloadTexts();
  for each( System::String^ textFile in textFiles )
  {
    CTextRef text( ToMBCS( textFile ) );
    if ( !text.GetText().empty() )
      ++result;
  }
  ::StoreTextsCache( ToMBCS( fileName ).c_str(), false );

  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
