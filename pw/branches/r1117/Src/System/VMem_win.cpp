/**
  @copyright
  Virtual memory functions
 */

#include "systemStdAfx.h"
#include "VMem.h"

namespace nival
{

/**
  Allocate and commit virtual memory
  @param size - [in] size to allocate in bytes
  @param access - [in] memory access flag
  @return address of allocated memory, 0 if failed
 */
void * VMemAlloc( size_t size, VMemAccess access )
{
  DWORD prot = 0;
  switch ( access )
  {
    case READ_ONLY:          prot = PAGE_READONLY; break;
    case READ_WRITE:         prot = PAGE_READWRITE; break;
    case READ_WRITE_EXECUTE: prot = PAGE_EXECUTE_READWRITE; break;
    default:                 assert( false );
  }
  return ::VirtualAlloc( 0, size, MEM_COMMIT, prot );
}

/**
  Release and deallocate virtual memory
  @param ptr - [in] pointer to allocated memory
  @return true if succes, false otherwise
 */
bool VMemFree( void * ptr )
{
  if ( !ptr ) { return false; }
  return ( ::VirtualFree( ptr, 0, MEM_RELEASE ) != FALSE );
}

} // namespace nival
