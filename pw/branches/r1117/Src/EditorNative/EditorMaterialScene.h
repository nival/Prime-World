#pragma once
#include "../UI/Window.h"
#include "Editor2DSceneBase.h"
#include "../UI/TextComponent.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class EditorMaterialScene sealed : public Editor2DSceneBase
{
private:
	UI::ImageComponent * pTextureImageComponent;
  UI::ImageComponent * pSampleImageComponent;
	UI::ImageComponent * pRootShapeComponent;
  UI::TextComponent *pTextComponent;
	bool shapeVisible;
	int textureWidth;
	int textureHeight;
	int dX;
	int dY;

protected:
  virtual void DrawInternal( System::IntPtr hWnd, int width, int height ) override;

public:
	EditorMaterialScene( System::IntPtr hWnd );
	~EditorMaterialScene();
	!EditorMaterialScene();

	int GetWidth();
	int GetHeight();
	void LoadMaterial( libdb::DB::DBID^ dbId );
  void ReloadMaterial( libdb::DB::DBID^ dbId );
	void SetShapeVisible( bool _visible) { shapeVisible = _visible; }

  void SetSampleRect( int x, int y, int width, int height );
	void SetTextureRect( int x, int y, int width, int height );
	void SetShapeRect( int x, int y, int width, int height );

  void LoadText( libdb::DB::DBID^ dbId, System::String^ toDisplay, int x, int y );

	delegate void UpdateStyleEventHandler();
	static event UpdateStyleEventHandler ^ UpdateStyleEvent;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}