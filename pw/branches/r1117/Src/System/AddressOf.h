/**
  @copyright
 */

#ifndef SYSTEM_ADDRESS_OF_H__
#define SYSTEM_ADDRESS_OF_H__

namespace nival
{

template< class T >
T* getaddressof(T& arg) 
{
    return reinterpret_cast<T*>(
               &const_cast<char&>(
                  reinterpret_cast<const volatile char&>(arg)));
}

}

#endif // SYSTEM_ADDRESS_OF_H__
