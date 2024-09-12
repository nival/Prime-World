#include "stdafx.h"

#include "../UI/Flash/GameSWFIntegration/Image.h"

#include "UITextureAtlasItem.h"

namespace Render
{

UITextureAtlasItem::UITextureAtlasItem( int _size ) :
  size(_size)
{
  freeSpace.resize( size, 0 );

  texture = Render::CreateTexture2D( size, size, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );
}

UITextureAtlasItem::~UITextureAtlasItem()
{

}

bool UITextureAtlasItem::PlaceImage( unsigned char* data, int width, int height, CVec2& uv1, CVec2& uv2, bool swizzle ) 
{
  int widthWithMargin = width + 1;
  int heightWithMargin = height + 1;

  if ( widthWithMargin > size )
    return false;

  int bestX = 0;
  int bestY = size;

  for ( int i = 0; i < size - widthWithMargin; ++i )
  {
    int maxY = 0;

    for ( int j = 0; j < widthWithMargin; ++j )
    {
      maxY = max( maxY, freeSpace[i + j] );
    }

    if ( maxY == 0 )
    {
      bestX = i;
      bestY = 0;
      break;
    }

    if ( maxY < bestY )
    {
      bestY = maxY;
      bestX = i;
    }
  }

  if ( ( bestY + heightWithMargin ) > size )
    return false;

  // margins
  bestY += 1;
  bestX += 1;

  if( IsValidPtr(texture) ) {
    LockedRect lockedRect = texture->LockRect( 0, LOCK_DEFAULT );

    for ( int i = 0; i < width; ++i )
    {
      for ( int j = 0; j < height; ++j )
      {
        int baseIndex = ( bestY + j ) * size + bestX + i; 

        lockedRect.data[ baseIndex * 4 + 0 ] = data[ (j * width + i ) * 4 + (swizzle ? 2 : 0) ];
        lockedRect.data[ baseIndex * 4 + 1 ] = data[ (j * width + i ) * 4 + (swizzle ? 1 : 1) ];
        lockedRect.data[ baseIndex * 4 + 2 ] = data[ (j * width + i ) * 4 + (swizzle ? 0 : 2) ];
        lockedRect.data[ baseIndex * 4 + 3 ] = data[ (j * width + i ) * 4 + 3 ];
      }

      freeSpace[ bestX + i ] = bestY + height;
    }

    texture->UnlockRect( 0 );
  }

  uv1.x = float( bestX ) / float( size );
  uv1.y = float( bestY ) / float( size );
  uv2.x = float( bestX + width ) / float( size );
  uv2.y = float( bestY + height ) / float( size );

  return true;
}

} // namespace Render

