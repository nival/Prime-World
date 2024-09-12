#include "Anim.h"

struct partObj
{
	float fDur; // Duration of FX in seconds
	float fFPS; // Frame rate
	unsigned nParticles; // Particles in FX
};

struct particle 
{
	unsigned nStart;
	unsigned nEnd;

	TVTrack<3> pos;
	TVTrack<3> scr; // xy SCale + Rotation
	TVTrack<4> col;
	TVTrack<1> spr;
};

typedef stdext::hash_map<unsigned, particle> hmPartData;

