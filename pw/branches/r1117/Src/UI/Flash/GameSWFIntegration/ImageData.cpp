#include "TamarinPCH.h"

#include <Vendor/zlib/include/zlib.h>
#include <Render/FlashRendererInterface.h>

#include "Image.h"
#include "ImageData.h"
#include "JPEGReader.h"
#include "FlashMovie.h"

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageData::Load( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool repeatable )
{
  switch( tagInfo.tagType )
  {
  case SWFTags::SWFTAGS_DEFINEBITS:
    LoadJPEG( movie, streamReader, tagInfo, repeatable );
    break;

  case SWFTags::SWFTAGS_DEFINEBITSJPEG3:
    LoadJPEG3( movie, streamReader, tagInfo, repeatable );
    break;

  case SWFTags::SWFTAGS_DEFINEBITSLOSSLESS:
    LoadLOSSLESS2( movie, streamReader, tagInfo, false, repeatable );
    break;

  case SWFTags::SWFTAGS_DEFINEBITSLOSSLESS2:
    LoadLOSSLESS2( movie, streamReader, tagInfo, true, repeatable );
    break;

  case SWFTags::SWFTAGS_DEFINEBITSJPEG2:
  case SWFTags::SWFTAGS_DEFINEBITSJPEG4:
    NI_ALWAYS_ASSERT("Not yet implemented");
    break;
  default:
    NI_ALWAYS_ASSERT("Wrong Tag Type");
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageData::LoadJPEG( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool repeatable )
{
  Strong<jpegreader::IInput> jpegInput = movie->GetCommonJPEGHeader();   


  if ( jpegInput )
  {
    jpegInput->DiscardPartialBuffer();
    jpegInput->StartImage();
  }
  else
  {
    jpegInput = jpegreader::Create( &streamReader );
  }

  image::rgba * intermediateImage = image::create_rgba( jpegInput->GetWidth(), jpegInput->GetHeight() );

  NI_ASSERT( jpegInput->GetWidth() <= 4096, "We does not support texture size greater as 4096" );

  UI8 line[16384];

  for (int y = 0; y < jpegInput->GetHeight(); y++) 
  {
    jpegInput->ReadScanline(line);

    UI8*	data = scanline(intermediateImage, y);
    for (int x = 0; x < jpegInput->GetWidth(); x++) 
    {
      data[4*x+0] = line[3*x+0];
      data[4*x+1] = line[3*x+1];
      data[4*x+2] = line[3*x+2];
      data[4*x+3] = 255;
    }
  }

  jpegInput->FinishImage();

  if ( movie->GetFlashRenderer() )
    bitmapInfo = movie->GetFlashRenderer()->CreateBitmapInfoRgba( intermediateImage, repeatable );

  streamReader.SetPos( tagInfo.parserPos + tagInfo.tagLen );

  delete intermediateImage;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageData::LoadJPEG3( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool repeatable )
{
  UI32 jpegSize = streamReader.readUI32();
  int saveStreamPos = streamReader.GetPos();
  
  Strong<jpegreader::IInput> jpegInput = jpegreader::CreateHeaderOnly( &streamReader );

  jpegInput->StartImage();

  image::rgba * intermediateImage = image::create_rgba( jpegInput->GetWidth(), jpegInput->GetHeight() );

  NI_ASSERT( jpegInput->GetWidth() <= 4096, "We does not support texture size greater as 4096" );

  UI8 line[16384];

  for (int y = 0; y < jpegInput->GetHeight(); y++) 
  {
    jpegInput->ReadScanline(line);

    UI8*	data = scanline(intermediateImage, y);
    for (int x = 0; x < jpegInput->GetWidth(); x++) 
    {
      data[4*x+0] = line[3*x+0];
      data[4*x+1] = line[3*x+1];
      data[4*x+2] = line[3*x+2];
      data[4*x+3] = 255;
    }
  }

  jpegInput->FinishImage();

  int	bufferBytes = intermediateImage->m_width * intermediateImage->m_height;
  UI8 *	buffer = new UI8[bufferBytes];

  uLongf dlen = bufferBytes;

  streamReader.SetPos( saveStreamPos + jpegSize );

  int e = uncompress(buffer, &dlen, (UI8*)streamReader.swf + saveStreamPos + jpegSize, streamReader.swf.getSize() - streamReader.GetPos() );

  NI_ASSERT( e == Z_OK, "Uncompression error" );

  if ( e == Z_OK )
  {
    NI_ASSERT( dlen == uLongf(bufferBytes), "Uncompression error" );

    for (int i = 0; i < bufferBytes; i++)
    {
      intermediateImage->m_data[4*i+3] = buffer[i];
    }
  }

  streamReader.SetPos( tagInfo.parserPos + tagInfo.tagLen );

  if ( movie->GetFlashRenderer() )
    bitmapInfo = movie->GetFlashRenderer()->CreateBitmapInfoRgba( intermediateImage, repeatable );

  delete[] buffer;
  delete intermediateImage;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageData::LoadLOSSLESS2( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool withAlpha, bool repeatable )
{
  UI8 bitmap_format = streamReader.readUI8();	// 3 == 8 bit, 4 == 16 bit, 5 == 32 bit
  UI16  width = streamReader.readUI16();
  UI16	height = streamReader.readUI16();

  image::rgba*	image = image::create_rgba(width, height);

  if ( bitmap_format == 3 )
    LoadLOSSLESS2_8( movie, streamReader, tagInfo, width, height, image );
  else if ( bitmap_format == 4 )
    LoadLOSSLESS2_16( movie, streamReader, tagInfo, width, height, image, withAlpha );
  else if ( bitmap_format == 5 )
    LoadLOSSLESS2_32( movie, streamReader, tagInfo, width, height, image, withAlpha );

  if ( movie->GetFlashRenderer() )
    bitmapInfo = movie->GetFlashRenderer()->CreateBitmapInfoRgba( image, repeatable );

  delete image;

  streamReader.SetPos( tagInfo.parserPos + tagInfo.tagLen );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageData::LoadLOSSLESS2_8( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, int width, int height, image::rgba* _image )
{
  int	color_table_size = streamReader.readUI8() + 1; // !! SWF stores one less than the actual size

  const int compCount = 3;
  const int bytes_per_pixel = 1;

  int	pitch = (width * bytes_per_pixel + 3) & ~3;

  int	bufferBytes = color_table_size * compCount + pitch * height;
  UI8* buffer = new UI8[bufferBytes];

  uLongf dlen = bufferBytes;
  int e = uncompress(buffer, &dlen, (UI8*)streamReader.swf + streamReader.GetPos(), streamReader.swf.getSize() - streamReader.GetPos() );

  NI_ASSERT( e == Z_OK, "Uncompression error" );

  if ( e == Z_OK )
  {
    NI_ASSERT( dlen == uLongf(bufferBytes), "Uncompression error" );

    UI8*	color_table = buffer;

    for (int j = 0; j < height; j++)
    {
      UI8*	image_in_row = buffer + color_table_size * compCount + j * pitch;
      UI8*	image_out_row = image::scanline(_image, j);
      for (int i = 0; i < width; i++)
      {
        UI8	pixel = image_in_row[i * bytes_per_pixel];
        image_out_row[i * 4 + 0] = color_table[pixel * compCount + 0];
        image_out_row[i * 4 + 1] = color_table[pixel * compCount + 1];
        image_out_row[i * 4 + 2] = color_table[pixel * compCount + 2];
        image_out_row[i * 4 + 3] = 255;
      }
    }
  }

  delete [] buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageData::LoadLOSSLESS2_16( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, int width, int height, image::rgba* _image, bool withAlpha )
{
  // 16 bits / pixel
  const int	bytes_per_pixel = 2;
  int	pitch = (width * bytes_per_pixel + 3) & ~3;

  int compCount = withAlpha ? 4 : 3;

  int	bufferBytes = pitch * height;
  UI8* buffer = new UI8[bufferBytes];

  uLongf dlen = bufferBytes;
  int e = uncompress(buffer, &dlen, (UI8*)streamReader.swf + streamReader.GetPos(), streamReader.swf.getSize() - streamReader.GetPos() );

  NI_ASSERT( e == Z_OK, "Uncompression error" );

  if ( e == Z_OK )
  {
    NI_ASSERT( dlen == uLongf(bufferBytes), "Uncompression error" );

    for (int j = 0; j < height; j++)
    {
      UI8*	image_in_row = buffer + j * pitch;
      UI8*	image_out_row = image::scanline(_image, j);
      for (int i = 0; i < width; i++)
      {
        UI16	pixel = image_in_row[i * 2] | (image_in_row[i * 2 + 1] << 8);

        // @@ How is the data packed???	 I'm just guessing here that it's 565!
        image_out_row[i * compCount + 0] = 255;			// alpha
        image_out_row[i * compCount + 1] = (pixel >> 8) & 0xF8;	// red
        image_out_row[i * compCount + 2] = (pixel >> 3) & 0xFC;	// green
        image_out_row[i * compCount + 3] = (pixel << 3) & 0xF8;	// blue
      }
    }
  }

  delete [] buffer;
}

void ImageData::LoadLOSSLESS2_32( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, int width, int height, image::rgba* _image, bool withAlpha )
{
  int compCount = 4;//withAlpha ? 4 : 3;

  // 32 bits / pixel, input is ARGB format
  int	bufferBytes = width * height * compCount;

  uLongf dlen = bufferBytes;
  int e = uncompress(_image->m_data, &dlen, (UI8*)streamReader.swf + streamReader.GetPos(), streamReader.swf.getSize() - streamReader.GetPos() );

  NI_ASSERT( e == Z_OK, "Uncompression error" );

  if ( e == Z_OK )
  {
    NI_ASSERT( dlen == uLongf(bufferBytes), "Uncompression error" );


    // Need to re-arrange ARGB into RGBA.
    for (int j = 0; j < height; j++)
    {
      UI8*	image_row = image::scanline( _image, j );

      for (int i = 0; i < width; i++)
      {
        UI8	a = image_row[i * compCount + 0];
        UI8	r = image_row[i * compCount + 1];
        UI8	g = image_row[i * compCount + 2];
        UI8	b = image_row[i * compCount + 3];

        if ( a > 0 )
        {
          float revAlpha = float( a ) / 255.f;

          r = UI8( float( r ) / revAlpha );
          g = UI8( float( g ) / revAlpha );
          b = UI8( float( b ) / revAlpha );
        }

        image_row[i * compCount + 0] = r;
        image_row[i * compCount + 1] = g;
        image_row[i * compCount + 2] = b;
        image_row[i * compCount + 3] = a;
      }
    }
  }
}

} //namespace flash
