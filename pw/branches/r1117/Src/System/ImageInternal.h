#ifndef __IMAGEINTERNAL_H__
#define __IMAGEINTERNAL_H__
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** pixel format conversion class
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SPixelConvertInfo
{
public:
	DWORD dwBitDepth;                     // bit depth of this format
	// Alpha channel info
	DWORD dwAMask;		                    // bit mask
	DWORD dwABits;		                    // # of bits in mask
	DWORD dwAShift;		                    // # of bits to shift down to canonical position
	// Red channel info
	DWORD dwRMask;		                    // bit mask
	DWORD dwRBits;		                    // # of bits in mask
	DWORD dwRShift;		                    // # of bits to shift down to canonical position
	// Green channel info
	DWORD dwGMask;		                    // bit mask
	DWORD dwGBits;		                    // # of bits in mask
	DWORD dwGShift;		                    // # of bits to shift down to canonical position
	// Blue channel Info
	DWORD dwBMask;		                    // bit mask
	DWORD dwBBits;		                    // # of bits in mask
	DWORD dwBShift;		                    // # of bits to shift down to canonical position
public:
	SPixelConvertInfo() {  }
	SPixelConvertInfo( DWORD dwABitMask, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask ) { InitMaskInfo( dwABitMask, dwRBitMask, dwGBitMask, dwBBitMask ); }
	// initialization
	bool InitMaskInfo( DWORD dwABitMask, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask );
	// color composition/decomposition (from ARGB, to ARGB)
	DWORD ComposeColor( DWORD dwColor ) const;
	DWORD ComposeColorSlow( DWORD dwColor ) const;
	DWORD DecompColor( DWORD dwColor ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGEINTERNAL_H__
