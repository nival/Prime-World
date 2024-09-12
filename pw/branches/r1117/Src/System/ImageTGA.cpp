#include "stdafx.h"

#include "ImageTGA.h"

namespace NImage
{

#pragma pack( push, 1 )
struct TGAHeader
{
	BYTE idLength;
  BYTE colormapType;
  BYTE imageType;

  WORD colormapIndex;
  WORD colormapLength;
	BYTE colormapSize;

  WORD x;
  WORD y;
	WORD width;
  WORD height;
	BYTE pixelSize;
  BYTE attributes;

  TGAHeader() :
    idLength( 0 ),
    colormapType( 0 ),
    imageType( 0 ),
    colormapIndex( 0 ),
    colormapLength( 0 ),
    colormapSize( 0 ),
    x( 0 ),
    y( 0 ),
    width( 0 ),
    height( 0 ),
    pixelSize( 0 ),
    attributes( 0 )
  {
  }
};
#pragma pack( pop )

namespace TGAImageType
{
  enum Enum
  {
    NoImage = 0,
    UncompressedColorMapped = 1,
    UncompressedTrueColor = 2,
    UncompressedGrayscale = 3,
    RLEColorMapped = 9,
    RLETrueColor = 10,
    RLEGrayscale = 11,
  };
}

namespace TGAAttributes
{
  enum Enum
  {
    RightOriented = 0x10,
    TopOriented = 0x20,
  };
}


void WriteImageTGA( Stream* stream, const CArray2D<Render::Color>& image )
{
  TGAHeader h;
  h.imageType = TGAImageType::UncompressedTrueColor;
  h.width = image.GetSizeX();
	h.height = image.GetSizeY();
	h.pixelSize = 24;
  h.attributes = TGAAttributes::TopOriented;
  stream->Write( &h, sizeof( h ) );

  vector<BYTE> data( image.GetSizeX() * 3 );
  for( int y = 0; y < image.GetSizeY(); ++y )
  {
    for( int x = 0; x < image.GetSizeX(); ++x )
    {
      const int offset = 3 * x;
      data[offset + 0] = image[y][x].B;
      data[offset + 1] = image[y][x].G;
      data[offset + 2] = image[y][x].R;
    }
		stream->Write( &data[0], data.size() );
  }
}

} // namespace NImage
