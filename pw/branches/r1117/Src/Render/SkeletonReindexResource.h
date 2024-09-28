#pragma once
#include "../System/staticvector.h"
namespace Render
{
	struct SkeletonFragmentReindex
	{
		//unsigned int meshCheckSum[4]; //128-bit
		StaticVector< unsigned __int32 > originalIndices;
	};
};