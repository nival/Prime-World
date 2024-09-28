#pragma once


#include "../System/systemStdAfx.h"
#include "../System/dummyallocator.h"
#include "../System/staticvector.h"

//////////////////////////////////////////////////////////////////////////
// maya's headers

#pragma pack(push,1)
struct MayaSkeletalAnimationHeader
{
	char signature[4];
	unsigned __int32 animationType;
	unsigned __int32 boneCount;
};


template<typename T>
struct MayaKey
{
	unsigned int frameNumber;
	T Data;
};

typedef MayaKey<CVec3> TMayaPosition;
typedef MayaKey<CVec4> TMayaRotation;
typedef MayaKey<CVec3> TMayaScale;

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////
// h6 headers

template<typename T>
struct SkeletalAnimationTrack
{
	StaticVector<T> trackData;
#ifdef TOOLSET_IS_PRESENT
	void resize( unsigned int _size, DummyAllocator* pAllocator )
	{
		trackData.resize( _size, pAllocator );
	}
#endif
	unsigned int size() const { return trackData.size(); }
  unsigned int getMemorySize() const { return trackData.size(); }
};

typedef SkeletalAnimationTrack<CVec3> TBonePositionTrack;
typedef SkeletalAnimationTrack<CVec4> TBoneRotationTrack;
typedef SkeletalAnimationTrack<CVec3> TBoneScaleTrack;

struct TBoneTracks
{
	TBonePositionTrack positionTrack;
	TBoneRotationTrack rotationTrack;
	TBoneScaleTrack    scaleTrack;
  //bool               bActive;
  bool IsActive() const
  {
    //should return false for partial skeleton animation
    return true;
  }
};

struct SkeletalAnimationData
{
	char signature[4];
	float minTime;
	float maxTime;
	StaticVector<TBoneTracks> tracks;

	unsigned int GetJointsCount() const
	{
		return tracks.size();
	}
  unsigned int size() const
  {
    int nSize = sizeof(signature) + sizeof(minTime) + sizeof(maxTime);

    return nSize + tracks.getMemorySize();
  }
};

struct SkeletalAnimationDataWrapper
{
public :
  typedef SkeletalAnimationData value_type;

public :
  SkeletalAnimationDataWrapper( value_type const *ptr ) : m_ptr( ptr ), compressed(true) 
  {
    CheckCompression();
  }

  value_type const* GetData() const { return m_ptr; }

  void SetData( value_type const* newPtr ) 
  { 
    NI_ASSERT( m_ptr->GetJointsCount() == newPtr->GetJointsCount(), "Wrong joints count" );
    m_ptr = newPtr; 
  }

  bool IsCompressed() const { return compressed; }

  void CheckCompression()
  {
    compressed = false;
  }

private :
  value_type const *m_ptr;
  bool compressed; 
};


struct GeometryReindex
{
	StaticVector< StaticVector<unsigned short> > reindex;
};