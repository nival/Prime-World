#include "stdafx.h"

#include "../UI/Flash/GameSWFIntegration/Image.h"

#include "UITextureCache.h"
#include "UITextureAtlasItem.h"

namespace
{
  static NDebug::DebugVar<int> flash_LGradientCount( "Linear Grad Bitmap Count", "Flash" );
  static NDebug::DebugVar<int> flash_RGradientCount( "Radial Grad Bitmap Count", "Flash" );

  static const int ATLAS_SIZE = 2048;
  static const int ATLAS_THRESHOLD = 1024;
  static const int CLAMP_THRESHOLD = 2048;
}

namespace Render
{


UITextureCache::UITextureCache()
{

}

UITextureCache::~UITextureCache()
{

}

bool UITextureCache::Release()
{
  gradientTextures2.clear();
  flash_LGradientCount.SetValue( 0 );
  flash_RGradientCount.SetValue( 0 );
  atlases.clear();

  return true;
}

Texture2DRef UITextureCache::CreateSimpleTexture( image::rgba* im, CVec2& uv1, CVec2& uv2 )
{
  Texture2DRef texture = Render::CreateTexture2D( im->m_width, im->m_height, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );

  LockedRect lockedRect = texture->LockRect( 0, LOCK_DEFAULT );

  for (int i = 0; i < im->m_width * im->m_height; i++)
  {
    lockedRect.data[ i*4 + 0 ] = im->m_data[ i*4 + 2 ];
    lockedRect.data[ i*4 + 1 ] = im->m_data[ i*4 + 1 ];
    lockedRect.data[ i*4 + 2 ] = im->m_data[ i*4 + 0 ];
    lockedRect.data[ i*4 + 3 ] = im->m_data[ i*4 + 3 ];
  }

  texture->UnlockRect( 0 );

  uv1 = CVec2( 0.f, 0.f );
  uv2 = CVec2( 1.f, 1.f );

  return texture;
}

Texture2DRef UITextureCache::CreateClampedTexture( image::rgba* source, CVec2& uv1, CVec2& uv2, int maxSize )
{
  int clampedWidth = min( source->m_width, maxSize );
  int clampedHeight = min( source->m_height, maxSize );

  Texture2DRef texture = Render::CreateTexture2D( clampedWidth, clampedHeight, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );

  LockedRect lockedRect = texture->LockRect( 0, LOCK_DEFAULT );

  for ( int i = 0; i < clampedWidth; ++i )
  {
    for ( int j = 0; j < clampedHeight; ++j )
    {
      int targetBase = j * clampedWidth + i;
      int sourceBase = j * source->m_width + i;

      lockedRect.data[ targetBase*4 + 0 ] = source->m_data[ sourceBase*4 + 2 ];
      lockedRect.data[ targetBase*4 + 1 ] = source->m_data[ sourceBase*4 + 1 ];
      lockedRect.data[ targetBase*4 + 2 ] = source->m_data[ sourceBase*4 + 0 ];
      lockedRect.data[ targetBase*4 + 3 ] = source->m_data[ sourceBase*4 + 3 ];
    }
  }

  texture->UnlockRect( 0 );

  uv1 = CVec2( 0.f, 0.f );
  uv2 = CVec2( source->m_width / clampedWidth, source->m_height / clampedHeight );

  return texture;
}

Texture2DRef UITextureCache::PlaceImageToAtlas( unsigned char* data, int width, int height, CVec2& uv1, CVec2& uv2, bool swizzle )
{
  if ( atlases.empty() )
    atlases.push_back( new UITextureAtlasItem( ATLAS_SIZE ) );

  Atlases::iterator it = atlases.begin();
  Atlases::iterator last = atlases.end();

  for ( ; it != last; ++it )
  {
    if ( (*it)->PlaceImage( data, width, height, uv1, uv2, swizzle ) )
      return (*it)->GetTexture();
  }

  atlases.push_back( new UITextureAtlasItem( ATLAS_SIZE ) );

  if ( !atlases.back()->PlaceImage( data, width, height, uv1, uv2, swizzle ) )
  {
    NI_ALWAYS_ASSERT( "Cannot place image into atlas" );
  }

  return atlases.back()->GetTexture();
}

Texture2DRef UITextureCache::PlaceImageToAtlas( image::rgba* source, CVec2& uv1, CVec2& uv2, bool repeatable )
{
  if ( repeatable )
    return CreateSimpleTexture( source, uv1, uv2 );

  if ( source->m_width > ATLAS_THRESHOLD || source->m_height > ATLAS_THRESHOLD )
  {
    if ( source->m_width > CLAMP_THRESHOLD || source->m_height > CLAMP_THRESHOLD )
      return CreateClampedTexture( source, uv1, uv2, ATLAS_THRESHOLD );
    else
      return CreateSimpleTexture( source, uv1, uv2 );
  }

  return PlaceImageToAtlas( source->m_data, source->m_width, source->m_height, uv1, uv2, true );
}

Texture2DRef UITextureCache::PlaceTextureToAtlas( const nstl::string& source, CVec2& uv1, CVec2& uv2 )
{
  Texture2DRef texture2D = Load2DTextureFromFile( source );

  return PlaceTextureToAtlas( texture2D, uv1, uv2 );
}

Texture2DRef UITextureCache::PlaceTextureToAtlas( const Texture2DRef& texture2D, CVec2& uv1, CVec2& uv2 )
{
  if ( !texture2D )
    return 0;

  if ( texture2D->GetWidth() > ATLAS_THRESHOLD || texture2D->GetHeight() > ATLAS_THRESHOLD )
    return texture2D;

  LockedRect lockedRect = texture2D->LockRect( 0, LOCK_DEFAULT );

  Texture2DRef atlasTexture; 

  if ( lockedRect.pitch == int( 4 * texture2D->GetWidth() ) )
  {
    atlasTexture = PlaceImageToAtlas( lockedRect.data, texture2D->GetWidth(), texture2D->GetHeight(), uv1, uv2, false );
  }
  else
  {
    NI_ALWAYS_ASSERT( "Texture for UI atlas has wrong pitch" );
  }

  texture2D->UnlockRect( 0 );

  return atlasTexture;
}

Texture2DRef UITextureCache::GetGradientTexture( const flash::SWF_GRADIENT& gradient )
{
  GradientTextures2::iterator it = gradientTextures2.find( gradient );

  if ( it != gradientTextures2.end() )
    return it->second;

  Texture2DRef texture;

  if ( gradient.type == flash::EGradientType::Linear )
    texture = CreateLinearGradient( gradient );
  else
    texture = CreateRadialGradient( gradient );

  gradientTextures2[gradient] = texture;

  return texture;
}

flash::SWF_RGBA UITextureCache::SampleGradient( const flash::SWF_GRADIENT& gradient, int ratio )
{
  if ( ratio < gradient.GradientRecords[0].Ratio )
    return gradient.GradientRecords[0].Color;		

  for ( int i = 1; i < gradient.GradientRecords.size(); ++i )
  {
    if ( gradient.GradientRecords[i].Ratio >= ratio )
    {
      const flash::SWF_GRADRECORD& gr0 = gradient.GradientRecords[i - 1];
      const flash::SWF_GRADRECORD& gr1 = gradient.GradientRecords[i];

      float	f = 0.0f;

      if ( gr0.Ratio != gr1.Ratio )
      {
        f = (ratio - gr0.Ratio) / float(gr1.Ratio - gr0.Ratio);
      }

      flash::SWF_RGBA	result;
      result.Lerp(gradient.GradientRecords[i - 1].Color, gradient.GradientRecords[i].Color, f);
      return result;
    }
  }
  return gradient.GradientRecords.back().Color;
}

Texture2DRef UITextureCache::CreateLinearGradient( const flash::SWF_GRADIENT& gradient )
{
  const int gradientSize = 256;
  Texture2DRef texture = Render::CreateTexture2D( gradientSize, 1, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );

  if( IsValidPtr(texture) )
  {
    flash_LGradientCount.AddValue( 1 );

    LockedRect lockedRect = texture->LockRect( 0, LOCK_DEFAULT );

    for (int i = 0; i < gradientSize; i++)
    {
      flash::SWF_RGBA sample = SampleGradient( gradient, i );

      lockedRect.data[ i * 4 + 0 ] = sample.b;//im->m_data[ i * 4 + 2 ];
      lockedRect.data[ i * 4 + 1 ] = sample.g;//im->m_data[ i * 4 + 1 ];
      lockedRect.data[ i * 4 + 2 ] = sample.r;//im->m_data[ i * 4 + 0 ];
      lockedRect.data[ i * 4 + 3 ] = sample.a;//im->m_data[ i * 4 + 3 ];
    }

    texture->UnlockRect( 0 );  
  }

  return texture;
}

static float QuadraticEquationSimple( float a, float b, float c )
{
  float D = b * b - 4.f * a * c;

  if ( D < 0.f )
    return 0.f;

  float x1 = ( -b - sqrt( D ) ) / ( 2.f * a );
  float x2 = ( -b + sqrt( D ) ) / ( 2.f * a );

  if ( x1 < 0.f ) 
    return x2;

  return x1;
}

Texture2DRef UITextureCache::CreateRadialGradient( const flash::SWF_GRADIENT& gradient )
{
  const int gradientWidth = 64;
  const int gradientHeight = 64;
  Texture2DRef texture = Render::CreateTexture2D( gradientWidth, gradientHeight, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );

  flash_RGradientCount.AddValue( 1 );

  LockedRect lockedRect = texture->LockRect( 0, LOCK_DEFAULT );

  float	radiusY = ( gradientHeight - 1) / 2.0f;
  float	radiusX = ( gradientWidth - 1) / 2.0f;
  float f = ( gradient.type == flash::EGradientType::Focal) ? gradient.FocalPoint : 0.f;

  for (int j = 0; j < gradientHeight; j++)
  {
    for (int i = 0; i < gradientWidth; i++)
    {
      float x = ( i - radiusX ) / radiusX;
      float y = ( j - radiusY ) / radiusY;

      float ratioF = QuadraticEquationSimple( f*f - 1.f, 2.f*x*f - 2.f*f*f, x*x - 2*x*f + f*f + y*y );
      int ratio = (int) floorf(255.5f * ratioF);

      if (ratio > 255)
      {
        ratio = 255;
      }

      flash::SWF_RGBA	sample = SampleGradient( gradient, ratio );

      int base = j * gradientWidth + i;

      lockedRect.data[ base * 4 + 0 ] = sample.b;//im->m_data[ i * 4 + 2 ];
      lockedRect.data[ base * 4 + 1 ] = sample.g;//im->m_data[ i * 4 + 1 ];
      lockedRect.data[ base * 4 + 2 ] = sample.r;//im->m_data[ i * 4 + 0 ];
      lockedRect.data[ base * 4 + 3 ] = sample.a;//im->m_data[ i * 4 + 3 ];
    }
  }

  texture->UnlockRect( 0 );  

  return texture;
}


} // namespace Render

