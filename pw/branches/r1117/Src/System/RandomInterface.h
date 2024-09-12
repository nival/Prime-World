#ifndef FOUNDATION_RANDOMINTERFACE_H_INCLUDED
#define FOUNDATION_RANDOMINTERFACE_H_INCLUDED

#include "System/Pointers/Pointers.h"
#include "System/types.h"
#include "System/nalgoritm.h"

namespace ni_rnd
{

class IGenerator : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IGenerator, IBaseInterfaceST );

public:
  virtual unsigned Next() = 0;
  
  int Next( int _min, int _max ) {
    if ( _min >= _max )
      return _min;
    return Next() % ( _max - _min + 1 ) + _min;
  }

  int Next( int _count ) {
    if ( _count <= 0 )
      return 0;
    return Next() % _count;
  }

  float NextFloat( float _min, float _max ) {
    const double t = (double)Next( 0, 1000000 ) / 1e6;
    return _min + t * ( _max - _min );
  }

  nival::uint64_t Next64() {
    return ( ( (nival::uint64_t)Next() ) << 32 ) | (nival::uint64_t)Next();
  }

  bool Roll( float _probabilityInPercents ) {
    NI_ASSERT( 0.0f <= _probabilityInPercents && _probabilityInPercents <= 100.0f, "Invalid probability value" );
    return NextFloat( 0.0f, 100.0f ) < _probabilityInPercents;
  }

  template <class TStlContainer>
  const typename TStlContainer::value_type & RollFromContainer( const TStlContainer & _cont, const typename TStlContainer::value_type & _default = TStlContainer::value_type() )
  {
    if ( !_cont.size() )
      return _default;

    unsigned index = Next() % (unsigned)_cont.size();
    typename TStlContainer::const_iterator it = _cont.begin();
    nstl::advance( it, index );
    return *it;
  }
};



class IFactory : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IFactory, IBaseInterfaceST );

public:
  virtual IGenerator * Produce( unsigned _seed ) = 0;
  virtual IGenerator * Produce() = 0;
};

} //namespace ni_rnd

#endif //FOUNDATION_RANDOMINTERFACE_H_INCLUDED
