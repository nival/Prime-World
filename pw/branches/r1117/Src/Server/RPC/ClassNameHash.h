/**
  @copyright
 */
#ifndef SERVER_RPC_CLASSNAMEHASH_H__
#define SERVER_RPC_CLASSNAMEHASH_H__

#include "System/types.h"

namespace rpc
{

// Cross-platform class name hash type
typedef nival::int32_t class_name_hash_t;

/**
  Get hash of class name
 */
inline class_name_hash_t get_class_name_hash( const char * className )
{
  class_name_hash_t h = 0;
  for ( ; *className; ++className )
  {
    h = 5 * h + static_cast< class_name_hash_t >( *className );
  }
  return h;
}

} // namespace rpc

#endif // SERVER_RPC_CLASSNAMEHASH_H__
