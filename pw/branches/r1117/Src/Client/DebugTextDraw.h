#ifndef DEBUGTEXTDRAW_H_INCLUDED
#define DEBUGTEXTDRAW_H_INCLUDED

#include "../UI/TextComponent.h"
#include "../Render/DebugRenderer.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainLoop
{


class DebugTextDraw : public CObjectBase, public Render::DebugRenderer::IDebugTextProcessor
{
  OBJECT_BASIC_METHODS( DebugTextDraw );

public:
  DebugTextDraw();

  void Init();
  void Draw();

  //Render::DebugRenderer::IDebugTextProcessor
  virtual void On2DText( const wstring & text, const CVec2 & uiCoords, int size, const Render::Color & color, Render::DebugRenderer::ETextHAlign hAlign,  Render::DebugRenderer::ETextVAlign vAlign );
  virtual void On3DText( const wstring & text, const CVec3 & pos, int size, const Render::Color & color, const SHMatrix & projection, Render::DebugRenderer::ETextHAlign hAlign,  Render::DebugRenderer::ETextVAlign vAlign );

private:
  UI::TextComponent   textComponent;

  void DrawText( const wstring & text, const CVec2 & uiCoords, int size, const Render::Color & color, Render::DebugRenderer::ETextHAlign hAlign,  Render::DebugRenderer::ETextVAlign vAlign );
};

} //namespace NMainLoop

#endif //DEBUGTEXTDRAW_H_INCLUDED
