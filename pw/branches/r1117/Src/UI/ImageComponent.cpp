#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ImageComponent.h"

#include "Root.h"
#include "SkinStyles.h"

#include "../Render/Renderer.h"
#include "../Render/TextureManager.h"
#include "../Render/UIRenderer.h"
#include "../Render/MaterialSpec.h"

#include "../System/InlineProfiler.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImageComponent::ImageComponent() :
renderable( false ),
skinTag(-1),
drawRect(0,0,0,0),
cropRect(0,0,0,0),
color(255,255,255,255),
opacity( 255 ),
needUpdateStyle( false ),
hTiles(0),
vTiles(0),
ext( false ),
angle( 0 ),
scale( 0 ),
useShape( false )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImageComponent::~ImageComponent()
{
  material.Release();
  shapeMaterial.Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::UpdateMaterialParams()
{
	materialParams.color0 = color;
	materialParams.color0.A = ( int( materialParams.color0.A ) * opacity ) / 255;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::SetMaterialColor( const Render::Color & _color )
{
	color = _color;
	UpdateMaterialParams();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::SetMaterialOpacity( int _opacity )
{
	opacity = Clamp( _opacity, 0, 255 );
	UpdateMaterialParams();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::SetMaterialCoef3( float c3 )
{
	materialParams.coef3 = c3;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::SetMaterialCoef4( float c4 )
{
	materialParams.coef4 = c4;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::SetExtended( const Point & _pivot, float _angle, float _scale )
{
	ext = true;
	pivot.x = _pivot.x;
	pivot.y = _pivot.y;
	angle = _angle;
	scale = _scale;
  needUpdateStyle = true; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::SetImageTexture(const Render::Texture2DRef& _pTexture)
{
	needUpdateStyle = false;		// ensure not updated from style (null)

	if ( !_pTexture )
		return;

  if ( !material.GetRenderMaterial() )
  {
    material.CreateDefaultMaterial();
    material.GetRenderMaterial()->ModifyColor( Render::HDRColor(1,1,1,1), Render::HDRColor(1,1,1,1) );
    material.GetRenderMaterial()->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );
  }

  material.GetRenderMaterial()->GetDiffuseMap()->SetTexture( _pTexture );

	const int tw = _pTexture->GetWidth();
	const int th = _pTexture->GetHeight();

	textureSize.x = tw;
	textureSize.y = th;

	uvTextureSize.x = tw;
	uvTextureSize.y = th;

	imgUV.x = 0;
	imgUV.y = 0;
	imgUVL.x = tw;
	imgUVL.y = th;

	uvPoint.u = (float)imgUV.x / textureSize.x;
	uvPoint.v = (float)imgUV.y / textureSize.y;
	uvlPoint.u = (float)imgUVL.x / textureSize.x;
	uvlPoint.v = (float)imgUVL.y / textureSize.y;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImageComponent::SetImageMaterial( const NDb::BaseUIMaterial * _material, ScreenLogicBase * logicAsTexturePool, bool forceReload /*= false*/ )
{
  if ( _material )
  {
    PushDXPoolGuard dxPool("UI");

    material.SetDBMaterial( _material, logicAsTexturePool, forceReload );
    needUpdateStyle = true;
    renderable = true;

    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImageComponent::SetImageMaterial( const string& _resourceName, ScreenLogicBase * logicAsTexturePool, bool forceReload /*= false*/ )
{
  return SetImageMaterial( NDb::Get<NDb::BaseUIMaterial>( NDb::DBID( _resourceName ) ), logicAsTexturePool, forceReload );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::UpdateStyleTexture()
{
  if ( !needUpdateStyle )
		return;

  needUpdateStyle = false;

  Render::BaseMaterial* renderMaterial = material.GetRenderMaterial();
  NDb::Ptr<NDb::BaseUIMaterial> dbMaterial = material.GetDBMaterial();

	if ( !renderMaterial || !dbMaterial || renderMaterial->GetDiffuseMap() == 0 )
		return;

  //$TODO check about dynamic_cast
  Render::Texture2D* diffuseTexture = dynamic_cast<Render::Texture2D*>( renderMaterial->GetDiffuseMap()->GetTexture().GetPtr() );

  if ( !diffuseTexture )
    return;

	textureSize.x = diffuseTexture->GetWidth();
	textureSize.y = diffuseTexture->GetHeight();

  bool autosize = (dbMaterial->UseAutosize == NDb::BOOLEANPIN_PRESENT);

  uvTextureSize.x = (autosize ? textureSize.x : dbMaterial->imageSize.x);
	uvTextureSize.y = (autosize ? textureSize.y : dbMaterial->imageSize.y);

	drawLeft = drawRight = drawTop = drawBottom = true;

	uvTileTextureSize.x = (autosize ? textureSize.x : dbMaterial->imageTileSize.x);
	uvTileTextureSize.y = (autosize ? textureSize.y : dbMaterial->imageTileSize.y);

  imgUV.Set( autosize ? CTPoint<int>( 0, 0 ) : dbMaterial->textureShift );
	imgUVL.x = imgUV.x + (autosize ? textureSize.x : dbMaterial->imageSize.x);
	imgUVL.y = imgUV.y + (autosize ? textureSize.y : dbMaterial->imageSize.y);

  imgTileUV.x = (autosize ? 0 : dbMaterial->imageTileShift.x);
	imgTileUV.y = (autosize ? 0 : dbMaterial->imageTileShift.y);
	imgTileUVL.x = imgTileUV.x + (autosize ? textureSize.x : dbMaterial->imageTileSize.x);
	imgTileUVL.y = imgTileUV.y + (autosize ? textureSize.y : dbMaterial->imageTileSize.y);

	uvPoint.u = (float)imgUV.x / textureSize.x;
	uvPoint.v = (float)imgUV.y / textureSize.y;
	uvlPoint.u = (float)imgUVL.x / textureSize.x;
	uvlPoint.v = (float)imgUVL.y / textureSize.y;

	uvTile.u = (float)imgTileUV.x / textureSize.x;
	uvTile.v = (float)imgTileUV.y / textureSize.y;
	uvlTile.u = (float)imgTileUVL.x / textureSize.x;
	uvlTile.v = (float)imgTileUVL.y / textureSize.y;

	if ( dbMaterial->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_TILE || dbMaterial->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_STRETCHEDTILE )
	{
		if ( !uvTileTextureSize.y || dbMaterial->verticalDrawMode == NDb::UIIMAGEDRAWMODE_NORMAL || dbMaterial->verticalDrawMode == NDb::UIIMAGEDRAWMODE_CENTER )
			imgTileUVL.y = imgTileUV.y = imgUVL.y;
		if ( dbMaterial->verticalDrawMode == NDb::UIIMAGEDRAWMODE_STRETCH )
			imgTileUVL.y = imgTileUV.y = imgUV.y + drawRect.y2 - drawRect.y1;
		if ( imgTileUVL.y == imgTileUV.y )
		{
			uvTile.v = uvlTile.v = uvlPoint.v;
			drawTop = true;
			drawBottom = false;
		}
	}

	if ( dbMaterial->verticalDrawMode == NDb::UIIMAGEDRAWMODE_TILE || dbMaterial->verticalDrawMode == NDb::UIIMAGEDRAWMODE_STRETCHEDTILE )
	{
		if ( !uvTileTextureSize.x || dbMaterial->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_NORMAL || dbMaterial->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_CENTER )
			imgTileUVL.x = imgTileUV.x = imgUVL.x;
		if ( dbMaterial->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_STRETCH )
			imgTileUVL.x = imgTileUV.x = imgUV.x + drawRect.x2 - drawRect.x1;
		if ( imgTileUVL.x == imgTileUV.x )
		{
			uvTile.u = uvlTile.u = uvlPoint.u;
			drawLeft = true;
			drawRight = false;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::DrawLine( const Point &_tlPoint, const Point &_brPoint, Point *tlPoint, Point *brPoint, CVec2 *uv, CVec2 *uvl, CVec2 *muv, CVec2 *muvl, const CVec2 & scaleRectToMask, NDb::EUIImageDrawMode horizMode )
{
	const int leftWidth = drawLeft ? (imgTileUV.x - imgUV.x) : 0;
	const int rightWidth = drawRight ? (imgUVL.x - imgTileUVL.x) : 0;
	const int tileStep = imgTileUVL.x - imgTileUV.x;
  const int middleWidth = drawRect.GetSizeX() - leftWidth - rightWidth;

	if ( drawLeft )
	{
		brPoint->x = tlPoint->x + leftWidth;
		uv->u = uvPoint.u;
		uvl->u = uvTile.u;

		muv->u = 0;
		muvl->u = ( brPoint->x - _tlPoint.x ) * scaleRectToMask.x;

		Render::UIQuad quad( *tlPoint, *brPoint, *uv, *uvl, *muv,*muvl );
    Render::GetUIRenderer()->AddQuad( quad, material.GetRenderMaterial(), materialParams );
		
		tlPoint->x += leftWidth;
	}

  if ( NDb::UIIMAGEDRAWMODE_STRETCHEDTILE == horizMode )
  {
    brPoint->x = tlPoint->x + middleWidth;
    uv->u = uvTile.u;
    uvl->u = uvlTile.u;

    muv->u = ( tlPoint->x - _tlPoint.x ) * scaleRectToMask.x;
    muvl->u = ( brPoint->x - _tlPoint.x ) * scaleRectToMask.x;

    Render::UIQuad quad( *tlPoint, *brPoint, *uv, *uvl, *muv,*muvl );
    Render::GetUIRenderer()->AddQuad( quad, material.GetRenderMaterial(), materialParams );

    tlPoint->x += middleWidth;
  }
  else
  {
    if ( hTiles > 0 )
    {
      brPoint->x = tlPoint->x + tileStep;
      uv->u = uvTile.u;
      uvl->u = uvlTile.u;

      NI_ASSERT( hTiles < 1024, NStr::StrFmt( "Too many h-tiles (%i) in image component!", hTiles ) );

      for (int i = 0; i < hTiles; ++i)
      {
        muv->u = ( tlPoint->x - _tlPoint.x ) * scaleRectToMask.x;
        muvl->u = ( brPoint->x - _tlPoint.x ) * scaleRectToMask.x;

        Render::UIQuad quad( *tlPoint, *brPoint, *uv, *uvl, *muv,*muvl );
        Render::GetUIRenderer()->AddQuad( quad, material.GetRenderMaterial(), materialParams );

        tlPoint->x += tileStep;
        brPoint->x += tileStep;
      }
    }
  }

	if ( drawRight )
	{
    if ( NDb::UIIMAGEDRAWMODE_STRETCHEDTILE != horizMode )
    {
		  const int restX = middleWidth - hTiles * tileStep;
		  if ( restX > 0 )
		  {
			  brPoint->x = tlPoint->x + restX;
			  uv->u = uvTile.u;
			  uvl->u = textureSize.x > 0 ? (uv->u + float(restX)/textureSize.x) : uvlTile.u;

			  muv->u = ( tlPoint->x - _tlPoint.x ) * scaleRectToMask.x;
			  muvl->u = ( brPoint->x - _tlPoint.x ) * scaleRectToMask.x;

			  Render::UIQuad quad( *tlPoint, *brPoint, *uv, *uvl, *muv,*muvl );
        Render::GetUIRenderer()->AddQuad( quad, material.GetRenderMaterial(), materialParams );

			  tlPoint->x += restX;
		  }
    }

		brPoint->x = tlPoint->x + rightWidth;
		uv->u = uvlTile.u;
		uvl->u = uvlPoint.u;

		muv->u = ( tlPoint->x - _tlPoint.x ) * scaleRectToMask.x;
		muvl->u = 0;

		Render::UIQuad quad( *tlPoint, *brPoint, *uv, *uvl, *muv,*muvl );
    Render::GetUIRenderer()->AddQuad( quad, material.GetRenderMaterial(), materialParams );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::DrawTile( const Point &_tlPoint, const Point &_brPoint, const CVec2 & scaleRectToMask, NDb::EUIImageDrawMode vertMode, NDb::EUIImageDrawMode horizMode )
{
	Point	tlPoint, brPoint;
	CVec2 uv, uvl;
	CVec2 muv, muvl;

	const int topHeight = drawTop ? (imgTileUV.y - imgUV.y) : 0;
	const int bottomHeight = drawBottom ? (imgUVL.y - imgTileUVL.y) : 0;
	const int tileStep = imgTileUVL.y - imgTileUV.y;
  const int middleHeight = drawRect.GetSizeY() - topHeight - bottomHeight;

	if ( drawTop )
	{
		tlPoint.x = _tlPoint.x;
		tlPoint.y = _tlPoint.y;
		brPoint.y = tlPoint.y + topHeight;
		uv.v = uvPoint.v;
		uvl.v = uvTile.v;
		muv.v = 0;
		muvl.v = ( brPoint.y - _tlPoint.y ) * scaleRectToMask.y;
		DrawLine( _tlPoint, _brPoint, &tlPoint, &brPoint, &uv, &uvl, &muv, &muvl, scaleRectToMask, horizMode );
	}

  if ( NDb::UIIMAGEDRAWMODE_STRETCHEDTILE == vertMode )
  {
    tlPoint.x = _tlPoint.x;
    tlPoint.y = _tlPoint.y + topHeight;
    brPoint.y = tlPoint.y + middleHeight;
    uv.v = uvTile.v;
    uvl.v = uvlTile.v;
    muv.v = ( tlPoint.y - _tlPoint.y ) * scaleRectToMask.y;
    muvl.v = ( brPoint.y - _tlPoint.y ) * scaleRectToMask.y;
    DrawLine( _tlPoint, _brPoint, &tlPoint, &brPoint, &uv, &uvl, &muv, &muvl, scaleRectToMask, horizMode );
  }
  else
  {
    NI_ASSERT( vTiles < 1024, NStr::StrFmt( "Too v-many tiles (%i) in image component!", vTiles ) );

    for (int j = 0; j < vTiles; ++j)
    {
      tlPoint.x = _tlPoint.x;
      tlPoint.y = _tlPoint.y + topHeight + j * tileStep;
      brPoint.y = tlPoint.y + tileStep;
      uv.v = uvTile.v;
      uvl.v = uvlTile.v;
      muv.v = ( tlPoint.y - _tlPoint.y ) * scaleRectToMask.y;
      muvl.v = ( brPoint.y - _tlPoint.y ) * scaleRectToMask.y;
      DrawLine( _tlPoint, _brPoint, &tlPoint, &brPoint, &uv, &uvl, &muv, &muvl, scaleRectToMask, horizMode );
    }
  }

	if ( drawBottom )
	{
    if ( NDb::UIIMAGEDRAWMODE_STRETCHEDTILE != vertMode )
    {
      const int restY = middleHeight - vTiles * tileStep;
      if ( restY > 0 )
      {
        tlPoint.x = _tlPoint.x;
        tlPoint.y = _tlPoint.y + topHeight + vTiles * tileStep;
        brPoint.y = tlPoint.y + restY;
        uv.v = uvTile.v;
        uvl.v = textureSize.y > 0 ? (uv.v + float(restY)/textureSize.y) : uvlTile.v;
        muv.v = ( tlPoint.y - _tlPoint.y ) * scaleRectToMask.y;
        muvl.v = ( brPoint.y - _tlPoint.y ) * scaleRectToMask.y;
        DrawLine( _tlPoint, _brPoint, &tlPoint, &brPoint, &uv, &uvl, &muv, &muvl, scaleRectToMask, horizMode );
      }
    }

		tlPoint.x = _tlPoint.x;
		tlPoint.y = brPoint.y;
		brPoint.y = tlPoint.y + bottomHeight;
		uv.v = uvlTile.v;
		uvl.v = uvlPoint.v;
		muv.v = ( tlPoint.y - _tlPoint.y ) * scaleRectToMask.y;
		muvl.v = 0;
		DrawLine( _tlPoint, _brPoint, &tlPoint, &brPoint, &uv, &uvl, &muv, &muvl, scaleRectToMask, horizMode );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageComponent::Render() 
{
  NI_PROFILE_FUNCTION

  if ( !renderable )
		return;

	UpdateStyleTexture();

	Render::GetUIRenderer()->PushCrop( cropRect );

	Point	tlPoint( 0, 0 ), brPoint( 0, 0 );

	switch ( material.GetDBMaterial() ? material.GetDBMaterial()->horizontalDrawMode : NDb::UIIMAGEDRAWMODE_STRETCH )
	{
		case NDb::UIIMAGEDRAWMODE_NORMAL:
			tlPoint.x = drawRect.x1;
			brPoint.x = tlPoint.x + uvTextureSize.x;
			break;
		case NDb::UIIMAGEDRAWMODE_CENTER:
			tlPoint.x = drawRect.x1 + ( drawRect.GetSizeX() - uvTextureSize.x ) / 2;
			brPoint.x = tlPoint.x + uvTextureSize.x;
			break;
		case NDb::UIIMAGEDRAWMODE_STRETCH:
			tlPoint.x = drawRect.x1;
			brPoint.x = drawRect.x2;
			break;
		case NDb::UIIMAGEDRAWMODE_TILE:
    case NDb::UIIMAGEDRAWMODE_STRETCHEDTILE:
			tlPoint.x = drawRect.x1;
			brPoint.x = drawRect.x2;
			if ( uvTileTextureSize.x )
				hTiles = ( drawRect.GetSizeX() - (uvTextureSize.x - uvTileTextureSize.x) ) / uvTileTextureSize.x;
			break;
	}

	switch ( material.GetDBMaterial() ? material.GetDBMaterial()->verticalDrawMode : NDb::UIIMAGEDRAWMODE_STRETCH )
	{
		case NDb::UIIMAGEDRAWMODE_NORMAL:
			tlPoint.y = drawRect.y1;
			brPoint.y = tlPoint.y + uvTextureSize.y;
			break;
		case NDb::UIIMAGEDRAWMODE_CENTER:
			tlPoint.y = drawRect.y1 + ( drawRect.GetSizeY() - uvTextureSize.y ) / 2;
			brPoint.y = tlPoint.y + uvTextureSize.y;
			break;
		case NDb::UIIMAGEDRAWMODE_STRETCH:
			tlPoint.y = drawRect.y1;
			brPoint.y = drawRect.y2;
			break;
		case NDb::UIIMAGEDRAWMODE_TILE:
    case NDb::UIIMAGEDRAWMODE_STRETCHEDTILE:
			tlPoint.y = drawRect.y1;
			brPoint.y = drawRect.y2;
			if ( uvTileTextureSize.y )
				vTiles = ( drawRect.GetSizeY()- ( uvTextureSize.y-uvTileTextureSize.y ) ) / uvTileTextureSize.y;
			break;
	}

	if (   material.GetDBMaterial() && 
       ( material.GetDBMaterial()->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_TILE || 
         material.GetDBMaterial()->verticalDrawMode == NDb::UIIMAGEDRAWMODE_TILE ||
         material.GetDBMaterial()->horizontalDrawMode == NDb::UIIMAGEDRAWMODE_STRETCHEDTILE || 
         material.GetDBMaterial()->verticalDrawMode == NDb::UIIMAGEDRAWMODE_STRETCHEDTILE 
         ) )
	{
		CVec2 scaleRectToMask;
		scaleRectToMask.x = drawRect.GetSizeX() <= 0 ? 0 : ( 1.0f / drawRect.GetSizeX() );
		scaleRectToMask.y = drawRect.GetSizeY() <= 0 ? 0 : ( 1.0f / drawRect.GetSizeY() );
		DrawTile( tlPoint, brPoint, scaleRectToMask, material.GetDBMaterial()->verticalDrawMode, material.GetDBMaterial()->horizontalDrawMode );
	}
	else
	{
		CVec2 uv(uvPoint), uvl(uvlPoint);
		Render::UIQuad quad( tlPoint, brPoint, uv, uvl, CVec2( 0, 0 ), CVec2( 0, 0 ) );

		if ( ext )
			quad.SetExtParams( pivot, angle, scale );

    Render::GetUIRenderer()->AddQuad( quad, material.GetRenderMaterial(), materialParams );
	}

	Render::GetUIRenderer()->PopCrop();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImageComponent::SetShapeMaterial( const NDb::BaseUIMaterial * _material )
{
	if ( !_material )
		return false;

  NDb::Ptr<NDb::UIBaseMaterial> baseMaterial = dynamic_cast<const NDb::UIBaseMaterial*>( _material );

  if ( !baseMaterial )
    return false;

  shapeMaterial.SetDBMaterial( baseMaterial, 0 );

  NDb::Ptr<NDb::UITexture> uiTexture = dynamic_cast<const NDb::UITexture*>( baseMaterial->DiffuseMap.texture.GetPtr() );

	if ( !uiTexture )
    return false;
    
  if ( uiTexture->shapeAlphaThreshold <= 0 )
		return false;

	const string & fileName = uiTexture->shapeFileName;

	if ( fileName.empty() )
		return false;

	CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "UI::ImageComponent: Cannot open file to load shape from '%s'!", fileName.c_str() ), return false; );

	int size = pStream->GetSize();
	vector<char> buf;
	buf.resize( size, 0 );
	pStream->Read( &buf[0], size );

	useShape = shape.Set( buf );

	return useShape;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImageComponent::HitTest( int x, int y ) const
{
	//if ( x < 0 || y < 0 || x >= imageRect.GetSizeX() || y >= imageRect.GetSizeY() )
	//	return false;

	if ( !useShape )
		return true;

	return shape.HitTest( x, y, drawRect.GetSizeX(), drawRect.GetSizeY(), shapeMaterial.GetDBMaterial() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImageComponent::SetImageTextureFromShape( const Render::Color & c0, const Render::Color & c1 )
{
	CArray2D<Render::Color> bitmap;

	bitmap.SetSizes( 1,1 );
	bitmap[0][0] = Render::Color(255,255,255,255);
	
	if ( useShape )
		shape.FillBitmap( &bitmap, drawRect.GetSizeX(), drawRect.GetSizeY(), shapeMaterial.GetDBMaterial(), c0, c1 );

	SetImageTexture( Render::Create2DTextureFromArray2D( bitmap ) );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageShape::FillBitmap( CArray2D<Render::Color> *pBitmap, int iw, int ih, const NDb::BaseUIMaterial* _material, const Render::Color & c0, const Render::Color & c1 ) const
{
	NI_VERIFY( IsCorrect(), "UI::ImageShape: Shape format invalid!", return );
	if ( !pBitmap )
		return;

	if ( iw <= 0 || ih <= 0 )
		return;

	pBitmap->SetSizes( iw, ih );

	for ( int y = 0; y < ih; ++y )
		for ( int x = 0; x < iw; ++x )
			(*pBitmap)[y][x] = HitTest( x, y, iw, ih, _material ) ? c1 : c0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImageShape::HitTest( int x, int y, int iw, int ih, const NDb::BaseUIMaterial* _material ) const
{
	NI_VERIFY( IsCorrect(), "Shape format invalid!", return true );

		// check image rect
	if ( iw <= 0 || ih <= 0 || !_material )
		return false;

		// start read shape
	WORD *p = (WORD *)&data[0];
	WORD w = p[2];
	WORD h = p[3];

		// declare aliases
	const int x1 = _material->textureShift.x;
	const int x2 = x1 + _material->imageSize.x;
	const int y1 = _material->textureShift.y;
	const int y2 = y1 + _material->imageSize.y;

	const int tx1 = x1 + _material->imageTileShift.x;
	const int tx2 = tx1 + _material->imageTileSize.x;
	const int ty1 = y1 + _material->imageTileShift.y;
	const int ty2 = ty1 + _material->imageTileSize.y;

		// convert test coordinates, according to style's drawing modes
	switch ( _material->horizontalDrawMode )
	{
		case NDb::UIIMAGEDRAWMODE_NORMAL:
			if ( x > x2-x1 )
				return false;
			break;
		case NDb::UIIMAGEDRAWMODE_CENTER:
		{
			int ww = x2-x1;
			int xx = (iw-ww)/2;
			if ( x < xx || x >= xx+ww )
				return false;
			x -= xx;
			break;
		}
		case NDb::UIIMAGEDRAWMODE_STRETCH:
			x = (x * (x2-x1)) / iw;
			break;
		case NDb::UIIMAGEDRAWMODE_TILE:
		{
			if ( tx2-tx1 <= 0 )
				return true;
			const int ix1 = tx1-x1;
			const int ix2 = iw-(x2-tx2);
			if ( x >= ix2 )
				x = (tx2-x1)+(x-ix2);
			else if ( x >= ix1 && x < ix2 )
				x = ix1 + ((x-ix1) % (tx2-tx1));
			break;
		}
	}

	switch ( _material->verticalDrawMode )
	{
		case NDb::UIIMAGEDRAWMODE_NORMAL:
			if ( y > y2-y1 )
				return false;
			break;
		case NDb::UIIMAGEDRAWMODE_CENTER:
		{
			int hh = y2-y1;
			int yy = (ih-hh)/2;
			if ( y < yy || y >= yy+hh )
				return false;
			y -= yy;
			break;
		}
		case NDb::UIIMAGEDRAWMODE_STRETCH:
			y = (y * (y2-y1)) / ih;
			break;
		case NDb::UIIMAGEDRAWMODE_TILE:
		{
			if ( ty2-ty1 <= 0 )
				return true;
			const int iy1 = ty1-y1;
			const int iy2 = ih-(y2-ty2);
			if ( y >= iy2 )
				y = (ty2-y1)+(y-iy2);
			if ( y >= iy1 && y < iy2 )
				y = iy1 + ((y-iy1) % (ty2-ty1));
			break;
		}
	}

	x += x1;
	y += y1;

		// test shape
	if ( x < 0 || x >= w || y < 0 || y >= h )
		return false;

	WORD offset = p[4+y];
	if ( offset == 0xFFFF )
		return false;

	NI_VERIFY( offset <= data.size()-2, "Shape format offset error!", return false );

	bool opaque = false;
	int col = 0;
	p = (WORD *)&data[ offset ];
	while ( offset <= data.size()-2 )
	{
		WORD len = *p;
		if ( len == 0xFFFF )
		{
			col = w;
			if ( x < col )
				return opaque;
			return false;
		}

		col += len;
		if ( x < col )
			return opaque;

		opaque = !opaque;
		++p;
		offset += 2;
	}

	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
