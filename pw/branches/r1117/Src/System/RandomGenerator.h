#pragma once

#include "System/nalgoritm.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NRandom
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Seed
{
  DWORD x;
  DWORD y;
  DWORD z;
  DWORD w;

  Seed() : x( 123456789 ), y( 362436069 ), z( 521288629 ), w( 88675123 ) {}
  Seed( DWORD seed ) : x( seed ), y( 362436069 ), z( 521288629 ), w( 88675123 ) {}
  void operator=( const Seed &other ) { x = other.x; y = other.y; z = other.z; w = other.w; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RandomGenerator
{
  ZDATA
    Seed seed;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&seed); return 0; }

  RandomGenerator() : seed() {}
  RandomGenerator( DWORD _seed ) : seed( _seed ) {}

  void SetSeed( DWORD _seed ) { seed = Seed( _seed ); }

  DWORD Next()
  {
    DWORD t;
    t = ( seed.x ^ ( seed.x << 11 ) );
    seed.x = seed.y;
    seed.y = seed.z;
    seed.z = seed.w;
    seed.w = ( seed.w ^ ( seed.w >> 19 ) ) ^ ( t ^ ( t >> 8 ) );
    return seed.w;
  }

  // для вкусностей
  int Next( int min, int max )
  {
    if ( min >= max )
      return min;
    return Next() % ( max - min + 1 ) + min;
  }
  int Next( int count )
  {
    if ( count <= 0 )
      return 0;
    return Next() % count;
  }

  float NextF( float _min, float _max )
  {
    const double t = (double)Next() / (double)0xffffffff;
    return _min + t * ( _max - _min );
  }

  QWORD Next64()
  {
    return ( QWORD(Next()) << 32 ) | QWORD(Next());
  }

  template <class TStlContainer>
  const typename TStlContainer::value_type & RollFromContainer( const TStlContainer & _cont, const typename TStlContainer::value_type & _default = TStlContainer::value_type() )
  {
    if ( !_cont.size() )
      return _default;

    int index = Next() % (DWORD)_cont.size();
    typename TStlContainer::const_iterator it = _cont.begin();
    nstl::advance( it, index );
    return *it;
  }


  template<class TStlContainer, class G>
  const typename TStlContainer::value_type & RollFromContainerByWeight( const TStlContainer & _container, const G & weightGetter, const typename TStlContainer::value_type & _default = TStlContainer::value_type()  )
  {
    if ( !_container.size() )
      return _default;

    int probsTotal = 0;
    typename TStlContainer::const_iterator itEnd = _container.end();
    for ( typename TStlContainer::const_iterator it = _container.begin(); it != itEnd; ++it )
    {
      probsTotal += weightGetter(*it);
    }

    const int roll = Next( 0, probsTotal - 1 );

    int lowBound = 0;
    for ( typename TStlContainer::const_iterator it = _container.begin(); it != itEnd; ++it )
    {
      int highBound = lowBound + weightGetter(*it);
      if ( roll >= lowBound && roll < highBound )
      {
        return *it;
      }
      else
      {
        lowBound = highBound;
      }
    }
    return _default;
  }

  bool Roll( float _probabilityInPercents )
  {
    NI_ASSERT( 0.0f <= _probabilityInPercents && _probabilityInPercents <= 100.0f, "Invalid probability value" );
    return NextF( 0.0f, 100.0f ) < _probabilityInPercents;
  }
};


// Generate random number from given seed in range [nMix, max]
int RandomAndSeedFromSeed( int *pSeed, int min, int max);
int RandomFromSeed( int seed, int min, int max );

} //NRandom
