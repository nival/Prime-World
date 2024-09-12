#include "stdafx.h"
#include "MemoryStream.h"
#include "ProtectedStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProtectedStream::ProtectedStream(): MemoryStream(), protectStatus(ACCESS_NO)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProtectedStream::ProtectedStream( const int initialSize ) : MemoryStream(), protectStatus(ACCESS_READWRITE)
{
  SetCanSeek( true );
  SetCanWrite( true );
  SetCanRead( true );
  SetBroken( false );

  SetSizeInternal( initialSize );
  NI_ASSERT(protectStatus == ACCESS_READWRITE, "");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProtectedStream::ProtectedStream( const ProtectedStream& other ): MemoryStream(other)
{
  protectStatus = other.protectStatus;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProtectedStream& ProtectedStream::operator = ( const ProtectedStream& other )
{
  MemoryStream::operator =(other);
  SetProtect(other.protectStatus);
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProtectedStream::operator == ( const ProtectedStream& other ) const
{
	return MemoryStream::operator ==(other) && other.protectStatus == protectStatus;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProtectedStream::SetSizeInternal( const int size )
{
  Protect nOldProtect = protectStatus;
  MemoryStream::SetSizeInternal(size, (MemoryStream::AllocBuff)&ProtectedStream::AllocateBuffer, (MemoryStream::FreeBuff)&ProtectedStream::FreeBuffer);
  SetProtect(nOldProtect);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ProtectedStream::ReadInternal( void *pData, const int length )
{
  NI_ASSERT((protectStatus & ACCESS_READ) == ACCESS_READ, "");
	return MemoryStream::ReadInternal(pData, length);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ProtectedStream::WriteInternal( const void *pData, const int length )
{
  NI_ASSERT((protectStatus & ACCESS_WRITE) == ACCESS_WRITE, "");
	return MemoryStream::WriteInternal(pData, length);;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * ProtectedStream::AllocateBuffer(size_t nSize)
{
  protectStatus = ACCESS_READWRITE;
#if defined( NV_WIN_PLATFORM )
	return (char *)VirtualAlloc( 0, nSize, MEM_COMMIT, PAGE_READWRITE );
#elif defined ( NV_LINUX_PLATFORM )
	return reinterpret_cast< char * >( malloc( nSize ) );
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProtectedStream::FreeBuffer(char *&pBuffer)
{
#if defined( NV_WIN_PLATFORM )
  VirtualFree(pBuffer, 0, MEM_RELEASE);
#elif defined( NV_LINUX_PLATFORM )
	if ( pBuffer )
		free( pBuffer );
#endif
  pBuffer = NULL;
  protectStatus = ACCESS_NO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProtectedStream::Close()
{
  MemoryStream::Close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProtectedStream::SetProtect(Protect prot)
{
#if defined( NV_WIN_PLATFORM )

	DWORD p = PAGE_NOACCESS;
	DWORD oldP;
	switch(prot)
	{
		case ACCESS_NO        : p = PAGE_NOACCESS ; break;        
		case ACCESS_WRITE     : p = PAGE_READWRITE; break;        
		case ACCESS_READ      : p = PAGE_READONLY ; break;        
		case ACCESS_READWRITE : p = PAGE_READWRITE; break;        
		default:
			NI_ALWAYS_ASSERT(".");
	}
	BOOL bRet = VirtualProtect(GetBuffer(), GetBufferSize(), p, &oldP);
	NI_ASSERT(bRet != 0, "VirtualProtect failed.");UNREFERENCED_PARAMETER(bRet);
	protectStatus = prot;

#elif defined( NV_LINUX_PLATFORM )

	// We can change protection for memory pages in linux also, but this will decrease the performance and increase the memory usage
	// For this we need to allocate memory block bigger than requested (requested + PAGE_SIZE - 1) and return the memory address aligned to PAGE_SIZE.
	// To change protection mode we need to use mprotect function in the future.

#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( ProtectedStream );

