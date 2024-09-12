#include "stdafx.h"

#include "DebugTextDraw.h"
#include "../UI/Resolution.h"
#include "../UI/SkinStyles.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainLoop
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DebugTextDraw::DebugTextDraw()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugTextDraw::Init()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugTextDraw::Draw()
{
  textComponent.EnableWordWrap( false );
  textComponent.SetStretchText( false );
  textComponent.SetVAlign( NDb::UITEXTVALIGN_CENTER );
  textComponent.SetHAlign( NDb::UITEXTHALIGN_CENTER );

  Render::DebugRenderer::ImplementationProcessDebugText( this );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugTextDraw::On2DText( const wstring & text, const CVec2 & uiCoords, int size, const Render::Color & color, Render::DebugRenderer::ETextHAlign hAlign,  Render::DebugRenderer::ETextVAlign vAlign )
{
  DrawText( text, uiCoords, size, color, hAlign, vAlign );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugTextDraw::On3DText( const wstring & text, const CVec3 & pos, int size, const Render::Color & color, const SHMatrix & projection, Render::DebugRenderer::ETextHAlign hAlign,  Render::DebugRenderer::ETextVAlign vAlign )
{
  UI::Point point;
  UI::GetWindowPlacement( &point, 0, pos, 0.0f, projection );

  DrawText( text, CVec2( point.x, point.y ), size, color, hAlign, vAlign );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugTextDraw::DrawText( const wstring & text, const CVec2 & uiCoords, int size, const Render::Color & color, Render::DebugRenderer::ETextHAlign hAlign, Render::DebugRenderer::ETextVAlign vAlign )
{
  UI::Point Resolution = UI::GetUIScreenResolution();
  if (uiCoords.x < 0 || uiCoords.y < 0 || uiCoords.x > Resolution.x || uiCoords.y > Resolution.y)
    return; // out of screen

  UI::IFontStyle * style = UI::GetFontRenderer()->GetDebugFontStyle( size );
  if ( style )
    textComponent.OverrideFontStyle( style );

  textComponent.SetDefaultColor( color );

  int pos = 0, x = 0, y = 0;
  bool firstLine = true;
  while (true)
  {
	  size_t cr = text.find('\n', pos);
		if (cr != wstring::npos)
	  {
			wstring line = text.substr(pos, cr - pos);
			textComponent.SetText(line);
			pos = cr + 1;
		}
		else if (firstLine)
		{
			textComponent.SetText(text);
		}
		else
		{
			wstring line = text.substr(pos);
			textComponent.SetText(line);
		}

	  float width = textComponent.GetTextWidth();
		float height = textComponent.GetTextHeight();
		if (firstLine)
		{
      switch( hAlign )
      {
      case Render::DebugRenderer::HA_Center:
        x = (int)( uiCoords.x - 0.5f * width ) - 2;
        break;
      case Render::DebugRenderer::HA_Left:
        x = (int)( uiCoords.x ) - 2;
        break;
      case Render::DebugRenderer::HA_Right:
        x = (int)( uiCoords.x - width ) - 2;
        break;
      }
		    
      switch( vAlign )
      {
      case Render::DebugRenderer::VA_Center: 
        y = (int)( uiCoords.y ) + 2;
        break;
      case Render::DebugRenderer::VA_Top: 
        y = (int)( uiCoords.y - 0.5f * height ) + 2;
        break;
      case Render::DebugRenderer::VA_Bottom: 
        y = (int)( uiCoords.y - height ) + 2;
        break;
      }
      		  
			firstLine = false;
		}

	  UI::Rect r( x, y, x + width, y + height );
	  y += height;

	  textComponent.SetDrawRect( r );
		textComponent.SetCropRect( r );
    
	  textComponent.Render();

		if (cr == wstring::npos)
			break;
  }
}

} //namespace NMainLoop
