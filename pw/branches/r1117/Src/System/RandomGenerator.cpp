#include "stdafx.h"
#include "RandomGenerator.h"

namespace NRandom
{

//////////////////////////////////////////////////////////////////////////////////////////////////
static int RandomAndSeedFromSeed( int *pSeed )
{
  NI_ASSERT( pSeed, "invalid pointer to seed" );

  int &seed = *pSeed;

  seed = seed * 214013L + 2531011L;
  int res = seed >> 7;
  seed = seed * 214013L + 2531011L;
  res ^= seed << 6;
  return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate random number from given seed in range [nMix, max]
int RandomAndSeedFromSeed( int *pSeed, int min, int max)
{
  if ( max < min + 1 )
    return min;
  const unsigned int uMax = max - min + 1;
  const int value = uMax ? ( (unsigned int)RandomAndSeedFromSeed( pSeed ) % uMax ) : 0;
  return value + min;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int RandomFromSeed( int seed, int min, int max )
{
  return RandomAndSeedFromSeed( &seed, min, max );
}

} //NRandom
