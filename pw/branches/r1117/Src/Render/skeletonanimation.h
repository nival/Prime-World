#pragma once

namespace Render
{
	///
	struct AnimationChannelKey
	{
		AnimationChannelKey(): time(0), value(0) {}
		AnimationChannelKey( float _time, float _value ): time(_time), value(_value) {}

		float time;
		float value;
	};

	struct CachedKeyIndexes3
	{
		unsigned int x;
		unsigned int y;
		unsigned int z;
	};
	struct CachedKeyIndexes4
	{
		unsigned int x;
		unsigned int y;
		unsigned int z;
		unsigned int w;
	};

	///
	class SkeletonAnimation
	{
	public:
		///
		SkeletonAnimation()	{}
		///
		virtual ~SkeletonAnimation() {}

		///
		void LoadFromFile( const nstl::string& filename );

		///
		unsigned int GetBonesCount() { return bonesCount; }

		///
		float GetTotalTime() const
		{ 
			float end = posXKeys[0].back().time;
			float start = posXKeys[0].front().time;
			return end - start;
		}

		///
		void GetRotationInTime( float time, unsigned int boneIndex, CQuat& rot, CachedKeyIndexes4& ind );
		///
		void GetTranslationInTime( float time, unsigned int boneIndex, CVec3& trans, CachedKeyIndexes3& ind );
		///
		void GetScaleInTime( float time, unsigned int boneIndex, CVec3& scale, CachedKeyIndexes3& ind );

	protected:
		typedef nstl::vector< AnimationChannelKey > BoneKeys;
		typedef nstl::vector< BoneKeys > BonesKeys;

		///
		__forceinline void LoadBonesKeys( BoneKeys& keys, unsigned char* data, unsigned char*& pEnd, bool flip = false );
		///
		float GetKeyValueInTime( float time, const BoneKeys& keys, unsigned int& ind );
		unsigned int bonesCount;

		BonesKeys posXKeys;
		BonesKeys posYKeys;
		BonesKeys posZKeys;

		BonesKeys rotXKeys;
		BonesKeys rotYKeys;
		BonesKeys rotZKeys;
		BonesKeys rotWKeys;

		BonesKeys scaleXKeys;
		BonesKeys scaleYKeys;
		BonesKeys scaleZKeys;
	};
}; // namespace Render
