#include "StdAfx.h"
#include "ImageInternal.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** pixel format conversion functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SPixelConvertInfo::InitMaskInfo( DWORD dwABitMask, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask )
{
	DWORD dwMask, dwBitShift, dwBitCount;
	//
	memset( this, 0, sizeof(*this) );
	// Get Alpha Mask info
	dwMask = dwABitMask;
	dwBitShift = dwBitCount = 0;
	if ( dwMask )
	{
		for ( ; (dwMask & 0x1) == 0; dwMask >>= 1 )
			dwBitShift++;
		for ( ; (dwMask & 0x1) == 1; dwMask >>= 1 )
			dwBitCount++;
	}
	dwAMask  = dwABitMask;
	dwABits  = dwBitCount;
	dwAShift = dwBitShift;
	// Get Red Mask info
	dwMask = dwRBitMask;
	dwBitShift = dwBitCount = 0;
	if ( dwMask )
	{
		for ( ; (dwMask & 0x1) == 0; dwMask >>= 1 )
			dwBitShift++;
		for ( ; (dwMask & 0x1) == 1; dwMask >>= 1 )
			dwBitCount++;
	}
	dwRMask  = dwRBitMask;
	dwRBits  = dwBitCount;
	dwRShift = dwBitShift;
	// Get Green Mask info
	dwMask = dwGBitMask;
	dwBitShift = dwBitCount = 0;
	if ( dwMask )
	{
		for ( ; (dwMask & 0x1) == 0; dwMask >>= 1 )
			dwBitShift++;
		for ( ; (dwMask & 0x1) == 1; dwMask >>= 1 )
			dwBitCount++;
	}
	dwGMask  = dwGBitMask;
	dwGBits  = dwBitCount;
	dwGShift = dwBitShift;
	// Get Blue Mask info
	dwMask = dwBBitMask;
	dwBitShift = dwBitCount = 0;
	if ( dwMask )
	{
		for ( ; (dwMask & 0x1) == 0; dwMask >>= 1 )
			dwBitShift++;
		for ( ; (dwMask & 0x1) == 1; dwMask >>= 1 )
			dwBitCount++;
	}
	dwBMask  = dwBBitMask;
	dwBBits  = dwBitCount;
	dwBShift = dwBitShift;
	//
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// convert color from (ARGB = 8888) format to specified by this pci
DWORD SPixelConvertInfo::ComposeColor( DWORD dwColor ) const
{
	// Convert Alpha component
	DWORD a = (dwColor >> 24) & 0xFF;
	a >>= (8 - dwABits);
	a <<= dwAShift;
	// Convert Red component
	DWORD r = (dwColor >> 16) & 0xFF;			// Convert to BYTE
	r >>= (8 - dwRBits);		              // throw away low precision bits
	r <<= dwRShift;					              // move to new position
	// Convert Green component
	DWORD g = (dwColor >> 8) & 0xFF;
	g >>= (8 - dwGBits);
	g <<= dwGShift;
	// Convert Blue component
	DWORD b = dwColor & 0xFF;
	b >>= (8 - dwBBits);
	b <<= dwBShift;
	// Return converted color
	return (r | g | b | a);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// more precise convert color from (ARGB = 8888) format to specified by this pci
DWORD SPixelConvertInfo::ComposeColorSlow( DWORD dwColor ) const
{
	// Convert Alpha component
	DWORD a = DWORD( double( ( dwColor >> 24 ) & 0xFF ) / double( 1 << (8 - dwABits) ) ) << dwAShift;
	// Convert Red component
	DWORD r = DWORD( double( ( dwColor >> 16 ) & 0xFF ) / double( 1 << (8 - dwRBits) ) ) << dwRShift;
	// Convert Green component
	DWORD g = DWORD( double( ( dwColor >>  8 ) & 0xFF ) / double( 1 << (8 - dwGBits) ) ) << dwGShift;
	// Convert Blue component
	DWORD b = DWORD( double( ( dwColor       ) & 0xFF ) / double( 1 << (8 - dwBBits) ) ) << dwBShift;
	// Return converted color
	return (r | g | b | a);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// convert color from current (specified by this pci) to (ARGB = 8888) format
DWORD SPixelConvertInfo::DecompColor( DWORD dwColor ) const
{
	// Convert Alpha component
	DWORD a = ((dwColor & dwAMask) >> dwAShift);
	a <<= (8 - dwABits);
	a <<= 24;
	// Convert Red component
	DWORD r = ((dwColor & dwRMask) >> dwRShift);
	r <<= (8 - dwRBits);
	r <<= 16;
	// Convert Green component
	DWORD g = ((dwColor & dwGMask) >> dwGShift);
	g <<= (8 - dwGBits);
	g <<= 8;
	// Convert Blue component
	DWORD b = ((dwColor & dwBMask) >> dwBShift);
	b <<= (8 - dwBBits);
	// Return converted color
	return (r | g | b | a);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
