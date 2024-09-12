#ifndef IMAGE_UNPACK_DXT_H_
#define IMAGE_UNPACK_DXT_H_

namespace NImage
{
// DWORD == NGfx::SPixel8888
void UnpackDXT( int nDxt, int nXSize, int nYSize, const void *pData, CArray2D<DWORD> *pRes );
}


#endif

