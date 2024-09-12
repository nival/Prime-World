//--------------------------------------------------------------------------------------
// Functions for loading a DDS texture without using D3DX
// Partially based on DDSWithoutD3DX D3D SDK sample.
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "DDS.h"
#include "ReadDDS.h"

#ifndef V_RETURN
  #define V_RETURN(x) { hr = (x); if( FAILED(hr) ) return hr; }
#endif

namespace Render {

//--------------------------------------------------------------------------------------
// Return the BPP for a particular format
//--------------------------------------------------------------------------------------
static UINT BitsPerPixel( D3DFORMAT fmt )
{
  switch( (UINT)fmt )
  {
  case D3DFMT_A32B32G32R32F:
    return 128;

  case D3DFMT_A16B16G16R16:
  case D3DFMT_Q16W16V16U16:
  case D3DFMT_A16B16G16R16F:
  case D3DFMT_G32R32F:
    return 64;

  case D3DFMT_A8R8G8B8:
  case D3DFMT_X8R8G8B8:
  case D3DFMT_A2B10G10R10:
  case D3DFMT_A8B8G8R8:
  case D3DFMT_X8B8G8R8:
  case D3DFMT_G16R16:
  case D3DFMT_A2R10G10B10:
  case D3DFMT_Q8W8V8U8:
  case D3DFMT_V16U16:
  case D3DFMT_X8L8V8U8:
  case D3DFMT_A2W10V10U10:
  case D3DFMT_D32:
  case D3DFMT_D24S8:
  case D3DFMT_D24X8:
  case D3DFMT_D24X4S4:
  case D3DFMT_D32F_LOCKABLE:
  case D3DFMT_D24FS8:
  case D3DFMT_INDEX32:
  case D3DFMT_G16R16F:
  case D3DFMT_R32F:
    return 32;

  case D3DFMT_R8G8B8:
    return 24;

  case D3DFMT_A4R4G4B4:
  case D3DFMT_X4R4G4B4:
  case D3DFMT_R5G6B5:
  case D3DFMT_L16:
  case D3DFMT_A8L8:
  case D3DFMT_X1R5G5B5:
  case D3DFMT_A1R5G5B5:
  case D3DFMT_A8R3G3B2:
  case D3DFMT_V8U8:
  case D3DFMT_CxV8U8:
  case D3DFMT_L6V5U5:
  case D3DFMT_G8R8_G8B8:
  case D3DFMT_R8G8_B8G8:
  case D3DFMT_D16_LOCKABLE:
  case D3DFMT_D15S1:
  case D3DFMT_D16:
  case D3DFMT_INDEX16:
  case D3DFMT_R16F:
  case D3DFMT_YUY2:
    return 16;

  case D3DFMT_R3G3B2:
  case D3DFMT_A8:
  case D3DFMT_A8P8:
  case D3DFMT_P8:
  case D3DFMT_L8:
  case D3DFMT_A4L4:
    return 8;

  case D3DFMT_DXT1:
    return 4;

  case D3DFMT_DXT2:
  case D3DFMT_DXT3:
  case D3DFMT_DXT4:
  case D3DFMT_DXT5:
    return  8;

    // From DX docs, reference/d3d/enums/d3dformat.asp
    // (note how it says that D3DFMT_R8G8_B8G8 is "A 16-bit packed RGB format analogous to UYVY (U0Y0, V0Y1, U2Y2, and so on)")
  case D3DFMT_UYVY:
    return 16;

    // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/directshow/htm/directxvideoaccelerationdxvavideosubtypes.asp
  case MAKEFOURCC( 'A', 'I', '4', '4' ):
  case MAKEFOURCC( 'I', 'A', '4', '4' ):
    return 8;

  case MAKEFOURCC( 'Y', 'V', '1', '2' ):
    return 12;

  default:
    assert( FALSE ); // unhandled format
    return 0;
  }
}

//--------------------------------------------------------------------------------------
// Get surface information for a particular format
//--------------------------------------------------------------------------------------
static void GetSurfaceInfo( UINT width, UINT height, D3DFORMAT fmt, UINT* pNumBytes, UINT* pRowBytes, UINT* pNumRows )
{
  UINT rowBytes = 0;
  UINT numRows = 0;

  // From the DXSDK docs:
  //
  //     When computing DXTn compressed sizes for non-square textures, the 
  //     following formula should be used at each mipmap level:
  //
  //         max(1, width / 4) x max(1, height / 4) x 8(DXT1) or 16(DXT2-5)
  //
  //     The pitch for DXTn formats is different from what was returned in 
  //     Microsoft DirectX 7.0. It now refers the pitch of a row of blocks. 
  //     For example, if you have a width of 16, then you will have a pitch 
  //     of four blocks (4*8 for DXT1, 4*16 for DXT2-5.)"

  if( fmt == D3DFMT_DXT1 || fmt == D3DFMT_DXT2 || fmt == D3DFMT_DXT3 || fmt == D3DFMT_DXT4 || fmt == D3DFMT_DXT5 )
  {
    const UINT numBlocksWide =  width ? Max(1u, width/4) : 0;
    const UINT numBlocksHigh = height ? Max(1u, height/4 ) : 0;
    const UINT numBytesPerBlock = (fmt == D3DFMT_DXT1) ? 8 : 16;

    rowBytes = numBlocksWide * numBytesPerBlock;
    numRows = numBlocksHigh;
  }
  else
  {
    UINT bpp = BitsPerPixel(fmt);
    rowBytes = (width * bpp + 7) / 8; // round up to nearest byte
    numRows = height;
  }
  if(pNumBytes)
    *pNumBytes = rowBytes * numRows;
  if(pRowBytes)
    *pRowBytes = rowBytes;
  if(pNumRows)
    *pNumRows = numRows;
}

//--------------------------------------------------------------------------------------
#define ISBITMASK( r,g,b,a ) ( ddpf.dwRBitMask == r && ddpf.dwGBitMask == g && ddpf.dwBBitMask == b && ddpf.dwABitMask == a )

//--------------------------------------------------------------------------------------
static D3DFORMAT GetD3D9Format( const DDS_PIXELFORMAT& ddpf )
{
  if( ddpf.dwFlags & DDS_RGB )
  {
    switch (ddpf.dwRGBBitCount)
    {
    case 32:
      if( ISBITMASK(0x00ff0000,0x0000ff00,0x000000ff,0xff000000) )
        return D3DFMT_A8R8G8B8;
      if( ISBITMASK(0x00ff0000,0x0000ff00,0x000000ff,0x00000000) )
        return D3DFMT_X8R8G8B8;
      if( ISBITMASK(0x000000ff,0x0000ff00,0x00ff0000,0xff000000) )
        return D3DFMT_A8B8G8R8;
      if( ISBITMASK(0x000000ff,0x0000ff00,0x00ff0000,0x00000000) )
        return D3DFMT_X8B8G8R8;

      // Note that many common DDS reader/writers swap the
      // the RED/BLUE masks for 10:10:10:2 formats. We assumme
      // below that the 'correct' header mask is being used
      if( ISBITMASK(0x3ff00000,0x000ffc00,0x000003ff,0xc0000000) )
        return D3DFMT_A2R10G10B10;
      if( ISBITMASK(0x000003ff,0x000ffc00,0x3ff00000,0xc0000000) )
        return D3DFMT_A2B10G10R10;

      if( ISBITMASK(0x0000ffff,0xffff0000,0x00000000,0x00000000) )
        return D3DFMT_G16R16;
      if( ISBITMASK(0xffffffff,0x00000000,0x00000000,0x00000000) )
        return D3DFMT_R32F; // D3DX writes this out as a FourCC of 114
      break;

    case 24:
      if( ISBITMASK(0x00ff0000,0x0000ff00,0x000000ff,0x00000000) )
        return D3DFMT_R8G8B8;
      break;

    case 16:
      if( ISBITMASK(0x0000f800,0x000007e0,0x0000001f,0x00000000) )
        return D3DFMT_R5G6B5;
      if( ISBITMASK(0x00007c00,0x000003e0,0x0000001f,0x00008000) )
        return D3DFMT_A1R5G5B5;
      if( ISBITMASK(0x00007c00,0x000003e0,0x0000001f,0x00000000) )
        return D3DFMT_X1R5G5B5;
      if( ISBITMASK(0x00000f00,0x000000f0,0x0000000f,0x0000f000) )
        return D3DFMT_A4R4G4B4;
      if( ISBITMASK(0x00000f00,0x000000f0,0x0000000f,0x00000000) )
        return D3DFMT_X4R4G4B4;
      if( ISBITMASK(0x000000e0,0x0000001c,0x00000003,0x0000ff00) )
        return D3DFMT_A8R3G3B2;
      break;
    }
  }
  else if( ddpf.dwFlags & DDS_LUMINANCE )
  {
    if( 8 == ddpf.dwRGBBitCount )
    {
      if( ISBITMASK(0x0000000f,0x00000000,0x00000000,0x000000f0) )
        return D3DFMT_A4L4;
      if( ISBITMASK(0x000000ff,0x00000000,0x00000000,0x00000000) )
        return D3DFMT_L8;
    }

    if( 16 == ddpf.dwRGBBitCount )
    {
      if( ISBITMASK(0x0000ffff,0x00000000,0x00000000,0x00000000) )
        return D3DFMT_L16;
      if( ISBITMASK(0x000000ff,0x00000000,0x00000000,0x0000ff00) )
        return D3DFMT_A8L8;
    }
  }
  else if( ddpf.dwFlags & DDS_ALPHA )
  {
    if( 8 == ddpf.dwRGBBitCount )
    {
      return D3DFMT_A8;
    }
  }
  else if( ddpf.dwFlags & DDS_FOURCC )
  {
    if( MAKEFOURCC( 'D', 'X', 'T', '1' ) == ddpf.dwFourCC )
      return D3DFMT_DXT1;
    if( MAKEFOURCC( 'D', 'X', 'T', '2' ) == ddpf.dwFourCC )
      return D3DFMT_DXT2;
    if( MAKEFOURCC( 'D', 'X', 'T', '3' ) == ddpf.dwFourCC )
      return D3DFMT_DXT3;
    if( MAKEFOURCC( 'D', 'X', 'T', '4' ) == ddpf.dwFourCC )
      return D3DFMT_DXT4;
    if( MAKEFOURCC( 'D', 'X', 'T', '5' ) == ddpf.dwFourCC )
      return D3DFMT_DXT5;

    if( MAKEFOURCC( 'R', 'G', 'B', 'G' ) == ddpf.dwFourCC )
      return D3DFMT_R8G8_B8G8;
    if( MAKEFOURCC( 'G', 'R', 'G', 'B' ) == ddpf.dwFourCC )
      return D3DFMT_G8R8_G8B8;

    if( MAKEFOURCC( 'U', 'Y', 'V', 'Y' ) == ddpf.dwFourCC )
      return D3DFMT_UYVY;
    if( MAKEFOURCC( 'Y', 'U', 'Y', '2' ) == ddpf.dwFourCC )
      return D3DFMT_YUY2;

    // Check for D3DFORMAT enums being set here
    switch( ddpf.dwFourCC )
    {
    case D3DFMT_A16B16G16R16:
    case D3DFMT_Q16W16V16U16:
    case D3DFMT_R16F:
    case D3DFMT_G16R16F:
    case D3DFMT_A16B16G16R16F:
    case D3DFMT_R32F:
    case D3DFMT_G32R32F:
    case D3DFMT_A32B32G32R32F:
    case D3DFMT_CxV8U8:
      return (D3DFORMAT)ddpf.dwFourCC;
    }
  }

  return D3DFMT_UNKNOWN;
}

#pragma warning(disable: 4512) // assignment operator could not be generated

class NOVTABLE FaceHolder
{
  const BYTE* const pSrcBound;
  UINT mipCount;
  UINT m_width;
  UINT m_height;
  D3DFORMAT fmt;

  virtual HRESULT LockRect(UINT n) = 0;
  virtual void  UnlockRect(UINT n) = 0;

protected:
  HRESULT hr;
  D3DLOCKED_RECT lockedRect;

  FaceHolder(UINT _mipCount, D3DFORMAT _fmt, UINT _width, UINT _height, const BYTE* _pSrcBound)
    : pSrcBound(_pSrcBound), mipCount(_mipCount), m_width(_width), m_height(_height), fmt(_fmt), hr(E_PENDING) {}
  ~FaceHolder() {}

public:
  const BYTE* Fill(const BYTE* _pSrcBits);
  HRESULT GetLastResult() const { return hr; }
};


class TextureHolder : public FaceHolder
{
  DXTextureRef pTexture;

  virtual HRESULT LockRect(UINT n) { return pTexture->LockRect(n, &lockedRect, NULL, 0); }
  virtual void  UnlockRect(UINT n) { pTexture->UnlockRect(n); }

public:
  TextureHolder(UINT _mipCount, D3DFORMAT _fmt, UINT _width, UINT _height, const BYTE* _pSrcBound)
    : FaceHolder(_mipCount, _fmt, _width, _height, _pSrcBound)
  {
    if( IDirect3DDevice9* const pDevice = GetDevice() )
    {
      IDirect3DTexture9* pTex = 0;
      hr = pDevice->CreateTexture(_width, _height, _mipCount, 0, _fmt, D3DPOOL_MANAGED, &pTex, NULL);
      pTexture.Attach(pTex);
    }
  }
  ~TextureHolder() {}

  IDirect3DTexture9* Detach() { return pTexture.Detach(); }
};


class CubeTextureHolder : public FaceHolder
{
  DXCubeTextureRef pTexture;
  D3DCUBEMAP_FACES face;

  virtual HRESULT LockRect(UINT n) { return pTexture->LockRect(face, n, &lockedRect, NULL, 0); }
  virtual void  UnlockRect(UINT n) { pTexture->UnlockRect(face, n); }

public:
  CubeTextureHolder(UINT _mipCount, D3DFORMAT _fmt, UINT _width, UINT _height, const BYTE* _pSrcBound)
    : FaceHolder(_mipCount, _fmt, _width, _height, _pSrcBound), face()
  {
    if( IDirect3DDevice9* const pDevice = GetDevice() )
    {
      NI_VERIFY(_width == _height, "Wrong cubemap: width not equal to height", hr = D3DXERR_INVALIDDATA; return);

      IDirect3DCubeTexture9* pTex = 0;
      hr = pDevice->CreateCubeTexture(_width, _mipCount, 0, _fmt, D3DPOOL_MANAGED, &pTex, NULL);
      pTexture.Attach(pTex);
    }
  }
  ~CubeTextureHolder() {}

  void ChooseFace(UINT _face)      { face = (D3DCUBEMAP_FACES)_face; }
  IDirect3DCubeTexture9* Detach()  { return pTexture.Detach(); }
};


const BYTE* FaceHolder::Fill(const BYTE* _pSrcBits)
{
  UINT width = m_width;
  UINT height = m_height;

  // Lock, fill, unlock
  for(UINT i = 0; i < mipCount; ++i) {
    UINT rowBytes, numRows;
    GetSurfaceInfo(width, height, fmt, NULL, &rowBytes, &numRows);

    if( SUCCEEDED(LockRect(i)) )
    {
      NI_VERIFY(UINT(lockedRect.Pitch) >= rowBytes, "Something is wrong in FaceHolder::Fill()", hr = E_FAIL; break);
      NI_VERIFY(_pSrcBits + rowBytes <= pSrcBound, "Corrupted DDS", hr = D3DXERR_INVALIDDATA; break);
      BYTE* pDestBits = (BYTE*)lockedRect.pBits;
      // Copy stride line by line
      for(UINT h = 0; h < numRows; h++) {
        CopyMemory(pDestBits, _pSrcBits, rowBytes);
        pDestBits += lockedRect.Pitch;
        _pSrcBits += rowBytes;
      }
      UnlockRect(i);
    }

    width = Max(width >> 1, 1u);
    height = Max(height >> 1, 1u);
  }
  return _pSrcBits;
}


//--------------------------------------------------------------------------------------
static HRESULT CreateTextureFromDDS(const DDS_HEADER* pHeader, const BYTE* pBitData, UINT bitSize, UINT skipMipLevels,
                                    PDIRECT3DBASETEXTURE9* ppTex)
{
  HRESULT hr = S_OK;

  UINT width = pHeader->dwWidth;
  UINT height = pHeader->dwHeight;
  UINT mipCount = pHeader->dwMipMapCount;
  if( 0 == mipCount )
    mipCount = 1;

  NI_VERIFY(!(pHeader->dwHeaderFlags & DDS_HEADER_FLAGS_VOLUME), "Volume textures are not supported yet", return E_FAIL);

  D3DFORMAT fmt = GetD3D9Format(pHeader->ddspf);

  // skip LODs
  UINT start = 0;
  const UINT startLevel = Min(skipMipLevels, mipCount - 1);
  for(UINT i = 0; i < startLevel; ++i) {
    UINT rowBytes, numRows;
    GetSurfaceInfo(width, height, fmt, NULL, &rowBytes, &numRows);
    start += rowBytes * numRows;
    width = Max(width >> 1, 1u);
    height = Max(height >> 1, 1u);
  }
  mipCount -= startLevel;
  const BYTE* pSrcBits = pBitData + start;
  NI_VERIFY(start < bitSize, "Corrupted DDS", return D3DXERR_INVALIDDATA);
  const BYTE* const pSrcBound = pBitData + bitSize;
  if(pHeader->dwCubemapFlags != 0)
  { // texture is cubemap
    if(pHeader->dwCubemapFlags != DDS_CUBEMAP_ALLFACES)
      DebugTrace("Non-standard cubemap: some faces missed");
    
    CubeTextureHolder texHolder(mipCount, fmt, width, height, pSrcBound);
    V_RETURN( texHolder.GetLastResult() );

    UINT cubemapFlags = pHeader->dwCubemapFlags >> 9;
    for(UINT i = 0; i < 6; ++i)
      if((cubemapFlags >>= 1) & 1) {
        texHolder.ChooseFace(i);
        pSrcBits = texHolder.Fill(pSrcBits) + start;
        V_RETURN( texHolder.GetLastResult() );
      }
    // Set the result
    *ppTex = texHolder.Detach();
    return hr;
  }

  // Create the texture
  TextureHolder texHolder(mipCount, fmt, width, height, pSrcBound);
  V_RETURN( texHolder.GetLastResult() );

  texHolder.Fill(pSrcBits);

  // Set the result
  *ppTex = texHolder.Detach();
  return hr;
}

//--------------------------------------------------------------------------------------
HRESULT CreateTextureFromDDSFileInMemory(const char *_data, UINT _dataSize, UINT _skipMipLevels, PDIRECT3DBASETEXTURE9* _ppTex)
{
  // Need at least enough data for header and magic number to be a valid DDS
  if( !_ppTex || !_data || _dataSize < sizeof(DDS_HEADER)+sizeof(DWORD) )
    return E_INVALIDARG;

  // DDS files always start with the same magic number ("DDS ")
  if(*(DWORD*)_data != DDS_MAGIC)
    return E_FAIL;

  const DDS_HEADER* pHeader = reinterpret_cast<const DDS_HEADER*>( _data + sizeof(DWORD) );
  // Verify header to validate DDS file
  if( pHeader->dwSize != sizeof(DDS_HEADER) || pHeader->ddspf.dwSize != sizeof(DDS_PIXELFORMAT) )
    return E_FAIL;

  // setup the pointers in the process request
  const BYTE* pBitData = reinterpret_cast<const BYTE*>(pHeader + 1);
  const UINT  BitSize = _dataSize - sizeof(DWORD) - sizeof(DDS_HEADER);

  return CreateTextureFromDDS(pHeader, pBitData, BitSize, _skipMipLevels, _ppTex);
}

} // namespace Render
