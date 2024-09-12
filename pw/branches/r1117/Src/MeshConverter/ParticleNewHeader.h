#pragma once


#pragma pack(push,1)
struct MayaPFXHeader
{
	char signature[4];
	float duration;
	float frameRate;
	unsigned int particlesCount;
};


struct MayaPFXTrackHeader
{
	unsigned int firstFrame;
	unsigned int lastFrame;
};

template<typename T>
struct MayaPFXKey
{
	unsigned int frameNumber;
	T Data;
};

typedef MayaPFXKey<CVec3> TMayaPFXPosition;
typedef MayaPFXKey<CVec3> TMayaPFXScaleRotation;
typedef MayaPFXKey<CVec4> TMayaPFXColor;
typedef MayaPFXKey<float> TMayaPFXSprite;

#pragma pack(pop)

template<typename T>
struct ParticleAnimationTrack
{
	StaticVector<T> trackData;
	StaticVector<float> timeData;
#ifdef TOOLSET_IS_PRESENT
	void resize( unsigned int _size, DummyAllocator* pAllocator )
	{
		NI_ASSERT(pAllocator, "ups");
		NI_ASSERT((_size > 1) && (_size < 1000), "ups");
		trackData.resize( _size, pAllocator );
		timeData.resize( _size, pAllocator );
	}
#endif
	unsigned int size() const { return timeData.size(); }

};

typedef ParticleAnimationTrack<CVec3> TParticlePositionTrack;
typedef ParticleAnimationTrack<CVec3> TParticleRotationAndScaleTrack;
typedef ParticleAnimationTrack<CVec4> TParticleColorTrack;
typedef ParticleAnimationTrack<float> TParticleUVTrack;

struct TParticleTracks
{
	float beginTime;
	float endTime;
	TParticlePositionTrack positionTrack;
	TParticleRotationAndScaleTrack rotationAndScaleTrack;
	TParticleColorTrack colorTrack;
	TParticleUVTrack uvTrack;
};

struct NewPFXHeader
{
	float duration;
};

struct NewPFXBinaryFile
{
	NewPFXHeader header;
	StaticVector<TParticleTracks> particlesTracks;
	int GetParticleCount() const { return particlesTracks.size(); }
};

struct PFXBinaryFileWrapper
{
public :
  typedef NewPFXBinaryFile value_type;

public :
  PFXBinaryFileWrapper( value_type const *ptr ) : m_ptr( ptr ) {}
  value_type const* GetData() const { return m_ptr; }
  void SetData( value_type const* newPtr ) 
  { 
    NI_VERIFY( m_ptr->GetParticleCount() == newPtr->GetParticleCount(), "Wrong particles count", return );
    m_ptr = newPtr; 
  }

private :
  value_type const *m_ptr;
};