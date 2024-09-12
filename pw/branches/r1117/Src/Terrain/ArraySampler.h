#pragma once

#include "../System/lerp.h"

namespace ArraySampler {

template <typename VALUE> struct IdentityProxy
{
	typedef VALUE ArgType;
	typedef VALUE ValueType;
	ValueType operator()(ArgType x)
	{
		return x;
	}
};

template <typename ARRAY, typename PROXY> 
typename PROXY::ValueType Nearest(ARRAY const& map, float u, float v, PROXY proxy)
{
	int w = map.GetSizeX();
	int h = map.GetSizeY();
	float x = ClampFast(u, 0.0f, 1.0f) * float(w);
	float y = ClampFast(v, 0.0f, 1.0f) * float(h);
	float xInt = floorf(x);
	float yInt = ceilf(y)-1.0f; // smirnov [2008/12/9]: rounding differs for x/y axes because of flipped direction
	int col = ClampFast(Float2Int(xInt), 0, w - 1);
	int row = ClampFast(Float2Int(yInt), 0, h - 1);
	return proxy(map.Get(col, row));
}

template <typename ARRAY> 
typename ARRAY::ValueType Nearest(ARRAY const& map, float u, float v)
{
	return Nearest(map, u, v, IdentityProxy<typename ARRAY::ValueType>());
}

template <typename ARRAY, typename PROXY> 
typename PROXY::ValueType Bilinear(ARRAY const& map, float u, float v, PROXY proxy)
{
	int w = map.GetSizeX();
	int h = map.GetSizeY();
	float x = ClampFast(u, 0.0f, 1.0f) * float(w) - 0.5f;
	float y = ClampFast(v, 0.0f, 1.0f) * float(h) - 0.5f;
	float xInt = floorf(x);
	float yInt = floorf(y);
	x -= xInt;
	y -= yInt;
	int col = Max(Float2Int(xInt), 0);
	int row = Max(Float2Int(yInt), 0);
	int colNext = Min(col + 1, w - 1);
	int rowNext = Min(row + 1, h - 1);

	return BiLerp(
		proxy(map.Get(col, row)), proxy(map.Get(colNext, row)), 
		proxy(map.Get(col, rowNext)), proxy(map.Get(colNext, rowNext)), x, y);
}

template <typename ARRAY> 
typename ARRAY::ValueType Bilinear(ARRAY const& map, float u, float v)
{
	return Bilinear(map, u, v, IdentityProxy<typename ARRAY::ValueType>());
}

} // namespace ArraySampler
