#include "stdafx.h"
#include "BitStreams.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int BitStream::nBitsMask[32] = {
	0x01,			 0x03,			 0x07,			 0x0F,				0x1F,			 0x3F,			 0x7F,			 0xFF,
	0x01FF,		 0x03FF,		 0x07FF,		 0x0FFF,			0x1FFF,		 0x3FFF,		 0x7FFF,		 0xFFFF,
	0x01FFFF,	 0x03FFFF,	 0x07FFFF,	 0x0FFFFF,		0x1FFFFF,	 0x3FFFFF,	 0x7FFFFF,	 0xFFFFFF,
	0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF,	0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF,
};
////////////////////////////////////////////////////////////////////////////////////////////////////
static void Free( MemoryStream *pData, int nShift )
{
	int nPos = pData->GetPosition() + nShift;
	pData->Seek( nPos, SEEKORIGIN_BEGIN );
}
static char *ReserveR( MemoryStream *pData, int nSize )
{
	ASSERT( pData->GetSize() - pData->GetPosition() >= nSize );
	return pData->GetBuffer() + pData->GetPosition();
}
static char *ReserveW( MemoryStream *pData, int nSize )
{
	int nPos = pData->GetPosition();
	pData->Seek( nPos + nSize, SEEKORIGIN_BEGIN );
	pData->Seek( nPos, SEEKORIGIN_BEGIN );
	return pData->GetBuffer() + nPos;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// BitLocker realization
////////////////////////////////////////////////////////////////////////////////////////////////////
BitLocker::~BitLocker() 
{
	FlushBits(); 
	if ( pData )
		::Free( pData, pCurrent - pBuffer );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitLocker::LockRead( MemoryStream &data, unsigned int nSize )
{
	ASSERT(!pData);
	pData = &data;
	pBuffer = ReserveR( pData, nSize );
	Init( pBuffer, read, nSize );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitLocker::LockWrite( MemoryStream &data, unsigned int nSize )
{
	ASSERT(!pData);
	pData = &data;
	pBuffer = ReserveW( pData, nSize );
	Init( pBuffer, write, nSize );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitLocker::ReserveRead( unsigned int nSize )
{
	ASSERT(pData);
	int nNewSize = pCurrent - pBuffer + nSize;
	char *pNewBuf;
	pNewBuf = ReserveR( pData, nNewSize );
#ifdef _DEBUG
	pReservedEnd = pNewBuf + nNewSize;
#endif
	int nFixup = pNewBuf - pBuffer;
	pCurrent += nFixup;
	pBitPtr += nFixup;
	pBuffer = pNewBuf;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitLocker::ReserveWrite( unsigned int nSize )
{
	ASSERT(pData);
	int nNewSize = pCurrent - pBuffer + nSize;
	char *pNewBuf;
	pNewBuf = ReserveW( pData, nNewSize );
#ifdef _DEBUG
	pReservedEnd = pNewBuf + nNewSize;
#endif
	int nFixup = pNewBuf - pBuffer;
	pCurrent += nFixup;
	pBitPtr += nFixup;
	pBuffer = pNewBuf;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitLocker::Free()
{ 
	ASSERT( pData );
	if ( pData ) 
	{ 
		FlushBits(); 
		::Free( pData, pCurrent - pBuffer );
		pData = 0; 
	} 
}
