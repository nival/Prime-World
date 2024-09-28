#include "stdafx.h"
#include "../System/lerp.h"
#include "skeletonanimation.h"

#include <xmmintrin.h>


namespace Render
{
///
void SkeletonAnimation::LoadBonesKeys( BoneKeys& keys, unsigned char* data, unsigned char*& pEnd, bool flip )
{
	unsigned int curPos = 0;

	unsigned int keysCount = *reinterpret_cast< unsigned int* >( &data[curPos] );
	curPos += 4;
	
	keys.resize( keysCount );
	for ( unsigned int i = 0; i < keysCount; i++ )
	{
		AnimationChannelKey key;
		key.time = float( *reinterpret_cast< const unsigned int* >( &data[curPos] ) ) * ( 1.0f / 30.0f );
		curPos += 4;

		if (flip) key.value = -(*reinterpret_cast< const float* >( &data[curPos] )); // FIXME
		else key.value = *reinterpret_cast< const float* >( &data[curPos] );
		curPos += 4;

		keys[i] = key;
	}

	pEnd = &data[curPos];
}

///
void SkeletonAnimation::LoadFromFile( const nstl::string& filename )
{
	FILE* stream = 0;
	if(fopen_s(&stream, filename.c_str(), "rb"))
	{
		NI_ALWAYS_ASSERT("can't fine such file");
	};

	fseek(stream, 0, SEEK_END);

	fpos_t pos;
	fgetpos(stream, &pos);

	fseek(stream, 0, SEEK_SET);

	unsigned int size = pos;
	unsigned char* data = new unsigned char [size];
	fread( reinterpret_cast<void*>(data), size, 1, stream );

	//unsigned int animFlags = *reinterpret_cast< unsigned int* >( &data[4] );
	bonesCount = *reinterpret_cast< unsigned int* >( &data[8] );

	//bool isTranslation = animFlags & 1;
	//bool isRotation = animFlags & 2;
	//bool isScale = animFlags & 4;

	posXKeys.resize( bonesCount );
	posYKeys.resize( bonesCount );
	posZKeys.resize( bonesCount );

	rotXKeys.resize( bonesCount );
	rotYKeys.resize( bonesCount );
	rotZKeys.resize( bonesCount );
	rotWKeys.resize( bonesCount );

	scaleXKeys.resize( bonesCount );
	scaleYKeys.resize( bonesCount );
	scaleZKeys.resize( bonesCount );

	unsigned char* pCurPos = &data[12];
	for ( unsigned int boneIndex = 0; boneIndex < bonesCount; boneIndex++ )
	{
		LoadBonesKeys( posXKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( posYKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( posZKeys[boneIndex], pCurPos, pCurPos );

		LoadBonesKeys( rotXKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( rotYKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( rotZKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( rotWKeys[boneIndex], pCurPos, pCurPos );

		LoadBonesKeys( scaleXKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( scaleYKeys[boneIndex], pCurPos, pCurPos );
		LoadBonesKeys( scaleZKeys[boneIndex], pCurPos, pCurPos );
	}

	fclose(stream);
	delete[] data;
}

///
void SkeletonAnimation::GetRotationInTime( float time, unsigned int boneIndex, CQuat& rot, CachedKeyIndexes4& ind )
{
	rot.x = GetKeyValueInTime( time, rotXKeys[boneIndex], ind.x );
	rot.y = GetKeyValueInTime( time, rotYKeys[boneIndex], ind.y );
	rot.z = GetKeyValueInTime( time, rotZKeys[boneIndex], ind.z );
	rot.w = GetKeyValueInTime( time, rotWKeys[boneIndex], ind.w );
}

///
void SkeletonAnimation::GetTranslationInTime( float time, unsigned int boneIndex, CVec3& trans, CachedKeyIndexes3& ind )
{
	trans.x = GetKeyValueInTime( time, posXKeys[boneIndex], ind.x );
	trans.y = GetKeyValueInTime( time, posYKeys[boneIndex], ind.y );
	trans.z = GetKeyValueInTime( time, posZKeys[boneIndex], ind.z );
}

///
void SkeletonAnimation::GetScaleInTime( float time, unsigned int boneIndex, CVec3& scale, CachedKeyIndexes3& ind )
{
	scale.x = GetKeyValueInTime( time, scaleXKeys[boneIndex], ind.x);
	scale.y = GetKeyValueInTime( time, scaleYKeys[boneIndex], ind.y );
	scale.z = GetKeyValueInTime( time, scaleZKeys[boneIndex], ind.z );
}

///
__forceinline float SkeletonAnimation::GetKeyValueInTime( const float time, const BoneKeys& keys, unsigned int& ind )
{
	if ( time == 0 ) return keys.begin()->value;

	BoneKeys::const_iterator it = keys.begin() + ind;

	if ( it->time > time ) 
		it = keys.begin();

	//const BoneKeys::const_iterator it_end = keys.end();

	for ( ;; ++it )
	{
		_mm_prefetch((const char*) it, _MM_HINT_NTA ); 
		const float curTime = it->time;

		if ( curTime > time ) 
		{
			const float value = it->value;
			BoneKeys::const_iterator it_prev = it - 1;
			const float prevValue = it_prev->value;
			const float prevTime = it_prev->time;

			ind = it_prev - keys.begin();

			return Lerp( prevValue, value, ( time - prevTime ) / ( curTime - prevTime ) );
		}
	}

	NI_ALWAYS_ASSERT("Invalid time");
	return 0.0f;
}
}; // namespace Render