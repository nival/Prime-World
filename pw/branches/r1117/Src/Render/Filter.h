#pragma once
#ifndef _FILTER_H_
#define _FILTER_H_

namespace Render {
namespace Filter {

// reciprocal square root of 2 pi
static float const R_SQRT_2PI = 0.39894228040143267793994605993438f;
static float const FILTER_SUM_EPSILON = 1e-5f;

class Gaussian1D
{
public:
	Gaussian1D(float stdDev) : a(R_SQRT_2PI / stdDev), b(-1.0f / (2.0f * stdDev * stdDev)) {}

	float operator()(float x) const
	{
		return a * expf(b * x * x);
	}

private:
	float a;
	float b;
};

class ArrayFunc2D
{
private:
	float const* data;
	int w;
	int h;

public:
	ArrayFunc2D(float* p, int width, int height) : data(p + width/2 + height/2 * width), w(width), h(height) {
		ASSERT(w & 1);
		ASSERT(h & 1);
	}

	float operator()(float x, float y) const {
		int i = (int)y, j = (int)x;
		ASSERT(-w/2 <= j && j <= w/2);
		ASSERT(-h/2 <= i && i <= h/2);
		return data[w * i + j];
	}

	int width() const { return w; }
	int height() const { return h; }
};

inline void NormalizeKernel(CVec4* kernel, int length, float multiplier)
{
	float sum = kernel[0].z;
	for (int i = 1; i < length; i++)
		sum += kernel[i].z + kernel[i].w;
	if (sum > FILTER_SUM_EPSILON)
	{
		float norm = multiplier / sum;
		for (int i = 0; i < length; i++)
		{
			kernel[i].z *= norm;
			kernel[i].w *= norm;
		}
	}
}

template <class FUNCTOR> void FillKernel1D(FUNCTOR const& f, CVec4* kernel, int side, float dx, float dy)
{
	ASSERT(side & 1);
	for (int i = 0; i <= side / 2; i++)
	{
		float t = (float)i;
		kernel[i].x = t * dx;
		kernel[i].y = t * dy;
		kernel[i].z = f(t);
		kernel[i].w = f(-t);
	}
}

template <class FUNCTOR> void FillKernel1D(FUNCTOR const& f, CVec4* kernel, int side, float dx, float dy, float multiplier)
{
	ASSERT(side & 1);
	FillKernel1D(f, kernel, side, dx, dy);
	NormalizeKernel(kernel, 1 + side / 2, multiplier);
}

template <class FUNCTOR> void FillKernel2D(FUNCTOR const& f, CVec4* kernel, int side, float dx, float dy)
{
	ASSERT(side & 1);
	int k = 0;
	for (int i = 0; i <= side / 2; i++) {
		float ty = (float)i;
		for (int j = 0; j < side; j++) {
			float tx = (float)(j - side / 2);
			if (i == 0 && tx < 0.0f)
				continue; // skip leading values of central line (symmetry)
			kernel[k].x = tx * dx;
			kernel[k].y = ty * dy;
			kernel[k].z = f(tx, ty);
			kernel[k].w = f(-tx, -ty);
			k++;
		}
	}
	ASSERT(k == 1 + side * side / 2);
}

template <class FUNCTOR> void FillKernel2D(FUNCTOR const& f, CVec4* kernel, int side, float dx, float dy, float multiplier)
{
	ASSERT(side & 1);
	FillKernel2D(f, kernel, side, dx, dy);
	NormalizeKernel(kernel, 1 + side * side / 2, multiplier);
}

} // namespace Filter
} // namespace Render

#endif /* _FILTER_H_ */
