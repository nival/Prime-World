#include "StdAfx.h"

#include "RandomGen.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NRandom
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// global random data & functions
// TODO: need implement serialization foir statis memebers
static SSeed globalSeed;
static void Isaac( SSeed *pRnd );
// get random value
UINT Random()
{
	if ( globalSeed.randcnt-- == 0 )
	{
		Isaac( &globalSeed );
		globalSeed.randcnt = RANDSIZ - 1;
	}
	return globalSeed.randrsl[ globalSeed.randcnt ];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ind(mm,x)	(*(unsigned _int32 *)(( unsigned _int8 *)(mm) + ((x) & ((RANDSIZ-1)<<2))))
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define rngstep(mix,a,b,mm,m,m2,r,x) \
{ \
	x = *m;	\
	a = (a ^ (mix)) + *(m2++); \
	*(m++) = y = ind( mm, x ) + a + b; \
	*(r++) = b = ind( mm, y >> RANDSIZL ) + x; \
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define mix(a,b,c,d,e,f,g,h) \
{ \
	a ^= b << 11; d += a; b += c; \
	b ^= c >> 2;	e += b; c += d; \
	c ^= d << 8;	f += c; d += e; \
	d ^= e >> 16; g += d; e += f; \
	e ^= f << 10; h += e; f += g; \
	f ^= g >> 4;	a += f; g += h; \
	g ^= h << 8;	b += g; h += a; \
	h ^= a >> 9;	c += h; a += b; \
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// new random vals recalculation
static void Isaac( SSeed *pRnd )
{
	unsigned _int32 a, b, x, y, *m, *mm, *m2, *r, *mend;
	mm = pRnd->randmem; 
	r = pRnd->randrsl;
	a = pRnd->randa; 
	b = pRnd->randb + ( ++pRnd->randc );
	for ( m = mm, mend = m2 = m+(RANDSIZ/2); m<mend; )
	{
		rngstep( a<<13, a, b, mm, m, m2, r, x );
		rngstep( a>>6 , a, b, mm, m, m2, r, x );
		rngstep( a<<2 , a, b, mm, m, m2, r, x );
		rngstep( a>>16, a, b, mm, m, m2, r, x );
	}
	for ( m2 = mm; m2<mend; )
	{
		rngstep( a<<13, a, b, mm, m, m2, r, x );
		rngstep( a>>6 , a, b, mm, m, m2, r, x );
		rngstep( a<<2 , a, b, mm, m, m2, r, x );
		rngstep( a>>16, a, b, mm, m, m2, r, x );
	}
	pRnd->randb = b; 
	pRnd->randa = a;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetRandomSeed( const SSeed &_seed )
{
	globalSeed = _seed;
}
const SSeed &GetRandomSeed() { return globalSeed; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The purpose of this func is to fill randrsl[RANDSIZ] arrays
// with initial random values
// It uses first RANDSIZ values from random file for this
static void FillRandRsl( SSeed *pRes )
{
	srand( GetTickCount() );
	for ( int i = 0; i < RANDSIZ; i++ )
		pRes->randrsl[i] = rand();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void INTERMODULE_EXPORT SSeed::SFLB2_InitVariables()
{
	randa = randb = randc = 0;
	unsigned _int32 *m = randmem;
	unsigned _int32 *r = randrsl;
	unsigned _int32 a, b, c, d, e, f, g, h;
	a = b = c = d = e = f = g = h = 0x9e3779b9;	// the golden ratio
	// scramble it
	for ( int i = 0; i < 4; ++i )
		mix( a, b, c, d, e, f, g, h );
	// initialize using the contents of r[] as the seed
	for ( int i = 0; i < RANDSIZ; i += 8 )
	{
		a+=r[i	]; b+=r[i+1]; c+=r[i+2]; d+=r[i+3];
		e+=r[i+4]; f+=r[i+5]; g+=r[i+6]; h+=r[i+7];
		mix( a, b, c, d, e, f, g, h );
		m[i	]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
		m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
	}
	// do a second pass to make all of the seed affect all of m_
	for ( int i = 0; i < RANDSIZ; i += 8 )
	{
		a+=m[i	]; b+=m[i+1]; c+=m[i+2]; d+=m[i+3];
		e+=m[i+4]; f+=m[i+5]; g+=m[i+6]; h+=m[i+7];
		mix( a, b, c, d, e, f, g, h );
		m[i	]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
		m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
	}
	// fill in the first set of results
	Isaac( this );
	// prepare to use the first set of results
	randcnt = RANDSIZ;		
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SSeed::Init()
{
	FillRandRsl( this );
	SFLB2_InitVariables(	);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SSeed::InitByZeroSeed()
{
	Zero( randrsl );
	SFLB2_InitVariables();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// SSeed
////////////////////////////////////////////////////////////////////////////////////////////////////
SSeed::SSeed()
{
	Init();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void SSeed::Store( Stream *pStream )
{
	pStream->Write( &randcnt, sizeof(randcnt) );
	pStream->Write( &(randrsl[0]), sizeof(randrsl) );
	pStream->Write( &(randmem[0]), sizeof(randmem) );
	pStream->Write( &randa, sizeof(randa) );
	pStream->Write( &randb, sizeof(randb) );
	pStream->Write( &randc, sizeof(randc) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void SSeed::Restore( Stream *pStream )
{
	pStream->Read( &randcnt, sizeof(randcnt) );
	pStream->Read( &(randrsl[0]), sizeof(randrsl) );
	pStream->Read( &(randmem[0]), sizeof(randmem) );
	pStream->Read( &randa, sizeof(randa) );
	pStream->Read( &randb, sizeof(randb) );
	pStream->Read( &randc, sizeof(randc) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int SSeed::operator&( IBinSaver &saver )
{
	saver.Add( 1, &randcnt );
	saver.AddRawData( 2, &(randrsl[0]), sizeof(randrsl) );
	saver.AddRawData( 3, &(randmem[0]), sizeof(randmem) );
	saver.Add( 4, &randa );
	saver.Add( 5, &randb );
	saver.Add( 6, &randc );
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float RandomNormal( const float fMin, const float fMax )
{
	float sum = 0.f;

	for (int i = 0; i < 12; ++i)
	{
		sum += float( double(Random()) / double(0xffffffffUL) );
	}

	sum /= 12.f;

	return fMin + sum * (fMax - fMin);
}

} // NRandom
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
