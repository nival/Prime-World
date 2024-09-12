#include "stdafx.h"

#include "ImageDDS.h"

#include "ImageInternal.h"
#include "ImageUnpackDXT.h"
#include "ImageFormatDDS.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NImage
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RecognizeFormatDDS( Stream *pStream )
{
	DWORD dwSignature = 0;;

	if ( pStream->GetPosition() + 4 >= pStream->GetSize() )
		return false;

	pStream->Read( &dwSignature, 4 );
	pStream->Seek( pStream->GetPosition() - 4, SEEKORIGIN_BEGIN );
	return dwSignature == SDDSFileHeader::SIGNATURE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DecompressARGB( DWORD *pRes, const SDDSHeader &hdr, const BYTE *pCompBytes )
{
	SPixelConvertInfo pci( hdr.ddspf.dwABitMask, hdr.ddspf.dwRBitMask, hdr.ddspf.dwGBitMask, hdr.ddspf.dwBBitMask );
	//
	switch ( hdr.ddspf.dwRGBBitCount ) 
	{
		case 16:
			{
				WORD *pSrc = (WORD*)pCompBytes;
				for ( DWORD i = 0; i < hdr.dwWidth * hdr.dwHeight; ++i )
					*pRes++ = pci.DecompColor( *pSrc++ );
			}
			break;
		case 24:
			for ( DWORD i = 0; i < hdr.dwWidth * hdr.dwHeight; ++i )
				*pRes++ = ( pCompBytes[i*3 + 0] << 16 ) | ( pCompBytes[i*3 + 1] << 8 ) | ( pCompBytes[i*3 + 2] );
			break;
		case 32:
			NI_ASSERT( false, "better read it directly to image" );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoadImageDDS( CArray2D<DWORD> *pResult, Stream *pStream )
{
	// skip signature
	pStream->Seek( 4, SEEKORIGIN_BEGIN );
	// read header
	SDDSHeader hdr;
	pStream->Read( &hdr, sizeof(hdr) );
	// check for sub-formats
	// DXT#
	if ( hdr.ddspf.dwFlags & DDS_FOURCC ) 
	{
		int nCompSize = 0, nDxt = 0;
		switch ( hdr.ddspf.dwFourCC ) 
		{
			case MAKEFOURCC('D','X','T','1'):
				nDxt = 1;
				nCompSize = hdr.dwWidth * hdr.dwHeight / 2;	// 4 BPP
				break;
			case MAKEFOURCC('D','X','T','2'):
				nDxt = 2;
				nCompSize = hdr.dwWidth * hdr.dwHeight;	// 8 BPP
				break;
			case MAKEFOURCC('D','X','T','3'):
				nDxt = 3;
				nCompSize = hdr.dwWidth * hdr.dwHeight;	// 8 BPP
				break;
			case MAKEFOURCC('D','X','T','4'):
				nDxt = 4;
				nCompSize = hdr.dwWidth * hdr.dwHeight;	// 8 BPP
				break;
			case MAKEFOURCC('D','X','T','5'):
				nDxt = 5;
				nCompSize = hdr.dwWidth * hdr.dwHeight;	// 8 BPP
				break;
		}
		// decompress
		if ( nCompSize > 0 ) 
		{

			BYTE *buffer = new BYTE[nCompSize];
			pStream->Read( buffer, nCompSize );
			UnpackDXT( nDxt, hdr.dwWidth, hdr.dwHeight, buffer, pResult );
			delete []buffer;
		}
		else
			return false;
	}
	else if ( ((hdr.ddspf.dwFlags & DDS_ARGB) == DDS_ARGB) || ((hdr.ddspf.dwFlags & DDS_ARGB) == DDS_RGB) ) 
	{
		pResult->SetSizes( hdr.dwWidth, hdr.dwHeight );
		if ( hdr.ddspf.dwRGBBitCount == 32 )	// directly read to image - this is ARGB8888
			pStream->Read( &(*pResult)[0][0], hdr.dwWidth * hdr.dwHeight * 4 );
		else
		{
			int nCompSize = hdr.dwWidth * hdr.dwHeight * hdr.ddspf.dwRGBBitCount / 8;
			BYTE *buffer = new BYTE[nCompSize];
			pStream->Read( buffer, nCompSize );
			DecompressARGB( &(*pResult)[0][0], hdr, buffer );
			delete []buffer;
		}
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
