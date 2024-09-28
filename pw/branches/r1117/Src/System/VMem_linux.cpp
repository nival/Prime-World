/**
  @copyright
  Virtual memory functions
 */

#include "systemStdAfx.h"
#include "VMem.h"
#include <unistd.h>
#include <sys/mman.h>

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
  int prot = 0;
  switch ( access )
  {
    case READ_ONLY:          prot = PROT_READ; break;
    case READ_WRITE:         prot = PROT_READ | PROT_WRITE; break;
    case READ_WRITE_EXECUTE: prot = PROT_READ | PROT_WRITE | PROT_EXEC; break;
    default:                 assert( false );
  }
  void * ptr = ::mmap( 0, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
  if ( ptr == MAP_FAILED ) { return 0; }
}

/**
  Release and deallocate virtual memory
  @param ptr - [in] pointer to allocated memory
  @return true if succes, false otherwise
 */
bool VMemFree( void * ptr )
{
  if ( !ptr ) { return false; }
  return ( ::munmap( ptr, 0 ) == 0 );
}

} // namespace nival
