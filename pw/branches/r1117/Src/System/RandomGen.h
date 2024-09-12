#ifndef _RANDOMGEN_H_
#define _RANDOMGEN_H_

#include "System/config.h"
#include "System/stdafx.h"
#include "System/types.h"

#ifdef STATIC_LIB
  #define DO_NOT_USE_DLLMAIN
  #define INTERMODULE_EXPORT
#else
#if defined( NV_WIN_PLATFORM )
  #define INTERMODULE_EXPORT __declspec(dllexport)
#elif defined( NV_LINUX_PLATFORM )
  #define INTERMODULE_EXPORT
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Uses ISAAC random generator, (c) Bob Jenkins with
//with using random file for initial random seeds
//Written by Ivanov Evgeny
//Nival Interactive, 1998
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NRandom
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int RANDSIZL = 8;
const int RANDSIZ = 1 << RANDSIZL;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SSeed
{
private:
#if defined( NV_WIN_PLATFORM )
	void INTERMODULE_EXPORT SFLB2_InitVariables();
#elif defined( NV_LINUX_PLATFORM )
  void SFLB2_InitVariables();
#endif
public:
	nival::uint32_t randcnt;
	nival::uint32_t randrsl[RANDSIZ];
	nival::uint32_t randmem[RANDSIZ];
	nival::uint32_t randa;
	nival::uint32_t randb;
	nival::uint32_t randc;

	SSeed();
	
	void Init();
	void InitByZeroSeed();
	void Store( Stream *pStream );
	void Restore( Stream *pStream );
	int operator&( IBinSaver &saver );
};
// initialize random generator with random seed
void SetRandomSeed( const SSeed &_seed );
// get current random gen seed
const SSeed &GetRandomSeed();
// get random value
UINT Random();
// random w/o checks
__forceinline unsigned int Random( const unsigned int uMax ) { return Random() % uMax; }
__forceinline int Random( const int nMin, const int nMax ) { return nMin + (int)Random( (unsigned int)(nMax - nMin + 1) ); }
__forceinline float Random( const float fMin, const float fMax ) { return fMin + float( double(Random()) / double(0xffffffffUL) * double(fMax - fMin) ); }

float RandomNormal( const float fMin, const float fMax );

// random with checks
__forceinline unsigned int RandomCheck( const unsigned int uMax ) { return uMax == 0 ? 0 : Random( uMax ); }
__forceinline int RandomCheck( const int nMin, const int nMax ) { return nMax < nMin ? nMin : Random( nMin, nMax ); }
__forceinline int RandomCheck( const float fMin, const float fMax ) { return fMax < fMin ? fMin : Random( fMin, fMax ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SRandomFunc
{
	float operator()( float fMin, float fMax ) const { return Random( fMin, fMax ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

