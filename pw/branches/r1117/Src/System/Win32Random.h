#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWin32Random
{
	void Seed( const int nSeed );
	int GetSeed();
	unsigned int Random();
	__forceinline unsigned int Random( const unsigned int uMax ) { return NWin32Random::Random() % uMax; }
	__forceinline int Random( const int nMin, const int nMax ) { return nMin + (int)NWin32Random::Random( (const unsigned int)(nMax - nMin + 1) ); }
	__forceinline float Random( const float fMin, const float fMax ) { return fMin + float( float(NWin32Random::Random()) / float(RAND_MAX) * (fMax - fMin) ); }

	__forceinline unsigned int RandomCheck( const unsigned int uMax ) { return uMax == 0 ? 0 : NWin32Random::Random( uMax ); }
	__forceinline int RandomCheck( const int nMin, const int nMax ) { return nMax < nMin ? nMin : NWin32Random::Random( nMin, nMax ); }
	__forceinline float RandomCheck( const float fMin, const float fMax ) { return fMax < fMin ? fMin : NWin32Random::Random( fMin, fMax ); }

	struct SRandomFunc
	{
		float operator()( float fMin, float fMax ) const { return Random( fMin, fMax ); }
	};
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
