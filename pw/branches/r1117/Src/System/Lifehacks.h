#ifndef SYSTEM_LIFEHACKS_H_INCLUDED
#define SYSTEM_LIFEHACKS_H_INCLUDED

//
//Bright-coloured side
//

#include <vector>

namespace lifehack
{

template <typename TContainer>
typename TContainer::iterator StlErase( TContainer & _cont, typename TContainer::iterator _it )
{
  TContainer::iterator result = _it;
  ++result;
  _cont.erase( _it );
  return result;
}



template<typename T>
class EasyVector : public std::vector<T>
{
public:
  explicit EasyVector( T _x0 ) {
    push_back( _x0 );
  }

  EasyVector( T _x0, T _x1 ) {
    reserve( 2 );
    push_back( _x0 );
    push_back( _x1 );
  }

  EasyVector( T _x0, T _x1, T _x2 ) {
    reserve( 3 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3 ) {
    reserve( 4 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4 ) {
    reserve( 5 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5 ) {
    reserve( 6 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6 ) {
    reserve( 7 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7 ) {
    reserve( 8 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8 ) {
    reserve( 9 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9 ) {
    reserve( 10 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10 ) {
    reserve( 11 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11 ) {
    reserve( 12 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11, T _x12 ) {
    reserve( 13 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
    push_back( _x12 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11, T _x12, T _x13 ) {
    reserve( 14 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
    push_back( _x12 );
    push_back( _x13 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11, T _x12, T _x13, T _x14 ) {
    reserve( 15 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
    push_back( _x12 );
    push_back( _x13 );
    push_back( _x14 );
  }
};

} //namespace lifehack

#endif //SYSTEM_LIFEHACKS_H_INCLUDED
