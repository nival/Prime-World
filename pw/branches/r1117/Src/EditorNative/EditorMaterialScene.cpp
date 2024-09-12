#include "stdafx.h"

#include "EditorMaterialScene.h"
#include "EditorRender.h"
#include "Utility.h"

#include "../UI/Window.h"
#include "../UI/SkinStyles.h"
#include "../UI/Resolution.h"
#include "../UI/FontRender.h"

using namespace System;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EditorNative
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorMaterialScene::EditorMaterialScene( IntPtr hWnd ) : 
  Editor2DSceneBase( hWnd ),
  pTextureImageComponent( nullptr ), 
  pSampleImageComponent( nullptr ),
  pRootShapeComponent( nullptr ),
  pTextComponent( nullptr ),
  shapeVisible( false )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorMaterialScene::~EditorMaterialScene()
{
	this->!EditorMaterialScene();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorMaterialScene::!EditorMaterialScene()
{
	if ( pTextureImageComponent != nullptr )
	{
		delete pTextureImageComponent;
		pTextureImageComponent = nullptr;
	}

  if ( pSampleImageComponent != nullptr )
  {
    delete pSampleImageComponent;
    pSampleImageComponent = nullptr;
  }

  if ( pRootShapeComponent != nullptr )
	{
		delete pRootShapeComponent;
		pRootShapeComponent = nullptr;
	}

  if ( pTextComponent != nullptr )
	{
		delete pTextComponent;
		pTextComponent = nullptr;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EditorMaterialScene::GetWidth()
{
	return textureWidth;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EditorMaterialScene::GetHeight()
{
	return textureHeight;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::LoadMaterial( libdb::DB::DBID^ dbId )
{
	if ( dbId->IsEmpty)
		return;

  if ( pTextureImageComponent == nullptr )
    pTextureImageComponent = new UI::ImageComponent();

  if ( pSampleImageComponent == nullptr )
    pSampleImageComponent = new UI::ImageComponent();

  if ( pRootShapeComponent == nullptr )
    pRootShapeComponent = new UI::ImageComponent();

  NDb::Ptr<NDb::BaseUIMaterial> pUIMaterial = GetObject<NDb::BaseUIMaterial>( dbId );

	if ( pUIMaterial != nullptr )
	{
    Render::UIRenderMaterial renderMaterial;
    renderMaterial.SetDBMaterial( pUIMaterial, 0 );

    Render::Texture2DRef diffuseTexture( dynamic_cast<Render::Texture2D*>( renderMaterial.GetRenderMaterial()->GetDiffuseMap()->GetTexture().GetPtr() ) );

    pTextureImageComponent->SetImageTexture( diffuseTexture );
    pTextureImageComponent->SetRenderable( true );
    pTextureImageComponent->UpdateStyleTexture();

    pSampleImageComponent->SetImageMaterial( pUIMaterial, 0, true );

    pRootShapeComponent->SetShapeMaterial( pUIMaterial );
    Render::Color c0(0,0,0,128);
    Render::Color c1(255,255,255,128);
    pRootShapeComponent->SetImageTextureFromShape( c0, c1 );

		textureWidth = pTextureImageComponent->GetTextureSize().x;
		textureHeight = pTextureImageComponent->GetTextureSize().y;

		UI::UpdateScreenResolution( 1280, 1024, true );
	}

	string dbidstr = ToMBCS( dbId->ToString() );
	systemLog( NLogg::LEVEL_DEBUG ) << "EditorUIScene::LoadMaterial(" << dbidstr << ")" << endl;
}

//////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::ReloadMaterial( libdb::DB::DBID^ dbId )
{
  if( pTextureImageComponent != nullptr )
  {
	  NDb::Ptr<NDb::BaseUIMaterial> pUIMaterial = GetObject<NDb::BaseUIMaterial>( dbId );
    
    if ( pUIMaterial != nullptr )
    {
      Render::UIRenderMaterial renderMaterial;
      renderMaterial.SetDBMaterial( pUIMaterial, 0 );

      Render::Texture2DRef diffuseTexture( dynamic_cast<Render::Texture2D*>( renderMaterial.GetRenderMaterial()->GetDiffuseMap()->GetTexture().GetPtr() ) );

      pTextureImageComponent->SetImageTexture( diffuseTexture );
      pTextureImageComponent->UpdateStyleTexture();

      pSampleImageComponent->SetImageMaterial( pUIMaterial, 0, true );

      pRootShapeComponent->SetShapeMaterial( pUIMaterial );
      Render::Color c0(0,0,0,128);
      Render::Color c1(255,255,255,128);
      pRootShapeComponent->SetImageTextureFromShape( c0, c1 );

      textureWidth = pTextureImageComponent->GetTextureSize().x;
      textureHeight = pTextureImageComponent->GetTextureSize().y;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::LoadText( libdb::DB::DBID^ dbId, System::String^ toDisplay, int x, int y )
{
  if ( pTextComponent == nullptr )
    pTextComponent = new UI::TextComponent();

  NDb::Ptr<NDb::UIFontStyle> pUIFont = GetObject<NDb::UIFontStyle>( dbId );
  if ( pUIFont != nullptr )
  {
    pTextComponent->SetFontStyle( pUIFont );
    pTextComponent->SetText( ToUnicodeCS( toDisplay ) );

    UI::Rect rect( x, y, 1280, 1024 );
    pTextComponent->SetDrawRect( rect );
    pTextComponent->SetCropRect( rect );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::SetShapeRect( int x, int y, int width, int height)
{
	if ( pRootShapeComponent != nullptr )
	{
    UI::Rect rect(x, y, width + x, height + y );

    pRootShapeComponent->SetDrawRect( rect );
		pRootShapeComponent->SetCropRect( rect );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::SetTextureRect( int x, int y, int width, int height )
{
	if ( pTextureImageComponent != nullptr )
	{
    UI::Rect rect(x, y, width + x, height + y );

		pTextureImageComponent->SetDrawRect( rect );
		pTextureImageComponent->SetCropRect( rect );
	}

  SetShapeRect( x, y, width, height );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::SetSampleRect( int x, int y, int width, int height )
{
  if ( pSampleImageComponent != nullptr )
  {
    UI::Rect rect(x, y, width + x, height + y );

    pSampleImageComponent->SetDrawRect( rect );
    pSampleImageComponent->SetCropRect( rect );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorMaterialScene::DrawInternal( System::IntPtr hWnd, int width, int height )
{
	if ( pTextureImageComponent != nullptr )
		pTextureImageComponent->Render();

  if ( pSampleImageComponent != nullptr )
    pSampleImageComponent->Render();

  if ( pRootShapeComponent != nullptr && shapeVisible )
		pRootShapeComponent->Render();

	if ( pTextComponent != nullptr )
		pTextComponent->Render();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
