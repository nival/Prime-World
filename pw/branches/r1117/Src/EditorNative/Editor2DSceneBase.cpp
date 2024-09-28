#include "stdafx.h"

#include "Editor2DSceneBase.h"
#include "EditorRender.h"
#include "../UI/Resolution.h"
#include "../UI/DebugDraw.h"

#include "../UI/Window.h"

using namespace System;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Editor2DSceneBase::Editor2DSceneBase( IntPtr hWnd )
: ppScene ( new CPtr<NScene::IScene>( NScene::CreateScene() ) )
{
  EditorRender::Initialize( (HWND)hWnd.ToPointer(), true );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Editor2DSceneBase::~Editor2DSceneBase()
{
	this->!Editor2DSceneBase();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Editor2DSceneBase::!Editor2DSceneBase()
{
  if ( ppScene != nullptr )
  {
    delete ppScene;
    ppScene = nullptr;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Editor2DSceneBase::DrawPoint( int x, int y, int size, System::Drawing::Color _color )
{
  UI::Debug::Color color( _color.R, _color.G, _color.B );
  UI::Debug::DrawPoint( UI::Point( x, y ), size, color );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Editor2DSceneBase::DrawLine( int x1, int y1, int x2, int y2, System::Drawing::Color _color )
{
	UI::Debug::Color color( _color.R, _color.G, _color.B );
  UI::Debug::DrawLine( UI::Point( x1, y1), UI::Point( x2, y2 ), color );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Editor2DSceneBase::Draw( System::IntPtr hWnd, int width, int height )
{
  if ( *ppScene != nullptr )
  {
    Render::Interface::Get()->RegisterSceneForRendering( (*ppScene)->GetRenderScene() );
  }

  Render::Interface::Get()->Clear();

  Render::GetUIRenderer()->BeginQueue();

  DrawInternal( hWnd, width, height );

  Render::GetUIRenderer()->EndQueue();

	Render::Interface::Get()->Render( true );
	Render::Rect rect( 0, width, 0, height );
	Render::Interface::Get()->Present( (HWND)hWnd.ToPointer(), rect, rect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}