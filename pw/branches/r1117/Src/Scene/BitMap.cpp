#include "stdafx.h"

#include "../System/2Darray.h"
#include "../System/Bresenham.h"
#include "../System/ChunklessSaver.h"
#include "BitMap.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//namespace
//{
//#if _MSC_VER
//#pragma pack(push,1)
//#endif
//struct TGAHeader
//{
//	BYTE 	id_length, colormap_type, image_type;
//	unsigned short colormap_index, colormap_length;
//	BYTE	colormap_size;
//	unsigned short x_origin, y_origin;				// unused
//	unsigned short width, height;
//	BYTE	pixel_size, attributes;
//};
//#if _MSC_VER
//#pragma pack(pop)
//#endif
//
//void DumpToTga( const CArray2D1Bit& mask, const char* fileName )
//{
//	FILE *f;
//	fopen_s( &f, fileName, "wb" );
//	if ( !f )
//		return;
//
//	TGAHeader h;
//	memset( &h, 0, sizeof( h ) );
//	h.width      = mask.GetSizeX();
//	h.height     = mask.GetSizeY();
//	h.pixel_size = 8;		// 8-bit
//	h.image_type = 3;   // uncompressed, greyscale
//	fwrite( &h, sizeof( h ), 1, f );
//
//	BYTE *buf = new BYTE[mask.GetSizeX() * mask.GetSizeY()];
//	int i = 0;
//	for( int y = 0; y < mask.GetSizeY(); ++y )
//	{
//		for( int x = 0; x < mask.GetSizeX(); ++x, ++i )
//		{
//			buf[i] = mask.GetData( x, y ) > 0 ? 255 : 0;
//		}
//	}
//	fwrite( buf, mask.GetSizeX() * mask.GetSizeY(), 1, f );
//	delete[] buf;
//
//	fclose( f );
//}
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
BitMap::BitMap( const char* data, float mapSizeX, float mapSizeY, int maskSize )
{
	mult.x = (float)maskSize / mapSizeX;
	mult.y = (float)maskSize / mapSizeY;
	mask.SetSizes( maskSize, maskSize );
	mask.FillZero();
	int index = 0;
	for( int y = 0; y < maskSize; ++y )
	{
		for( int x = 0; x < maskSize; ++x, index += 4 )
		{
      // chech AdvMapEditor.cs and fillind with alpha = 64 brush
			if ( data[index] > 0 && data[index] <= 64 )
				mask.SetData( x, y );
		}
	}

	//DumpToTga( mask, "c:\\home\\watermap.tga" );
}

void BitMap::Store( const char* data, float mapSizeX, float mapSizeY, int maskSize, const string& fileName )
{
	NScene::BitMap bitMap( data, mapSizeX, mapSizeY, maskSize );

  CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open vertex color file for writing %s", fileName.c_str() ), return );

  CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, 0, false );
  pSaver->Add( 1, &bitMap );
}

} // namespace NScene
