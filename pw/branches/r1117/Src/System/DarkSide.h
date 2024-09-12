/**
  @copyright
  
  Welcome to the Dark Side!

 */
#ifndef SYSTEM_DARK_SIDE_H__
#define SYSTEM_DARK_SIDE_H__

namespace DarkSide
{


template< typename IntType, typename PtrType >
IntType ptr2int( PtrType ptr )
{
  return *static_cast< IntType* >( static_cast< void* >( &ptr ) );
}

template< typename PtrType, typename IntType >
PtrType int2ptr( IntType ptr )
{
  return *static_cast< PtrType* >( static_cast< void* >( &ptr ) );
}

} // namespace DarkSide

#endif // SYSTEM_DARK_SIDE_H__
