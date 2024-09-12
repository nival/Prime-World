/**
  @copyright
  Virtual memory functions
 */

#ifndef SYSTEM_VMEM_H__
#define SYSTEM_VMEM_H__

namespace nival
{

/**
  Access modes
 */
enum VMemAccess
{
  READ_ONLY = 1,
  READ_WRITE,
  READ_WRITE_EXECUTE
};

/**
  Allocate and commit virtual memory
  @param size - [in] size to allocate in bytes
  @param access - [in] memory access flag
  @return address of allocated memory, 0 if failed
 */
void * VMemAlloc( size_t size, VMemAccess access );

/**
  Release and deallocate virtual memory
  @param ptr - [in] pointer to allocated memory
  @return true if succes, false otherwise
 */
bool VMemFree( void * ptr );

} // namespace nival

#endif // SYSTEM_VMEM_H__
