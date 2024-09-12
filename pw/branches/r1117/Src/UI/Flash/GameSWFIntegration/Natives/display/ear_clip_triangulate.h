// ear_clip_triangulate.h	-- Thatcher Ulrich 2006

// This source code has been donated to the Public Domain.  Do
// whatever you want with it.

// Code to triangulate 2D polygonal regions.
//
// see ear_clip_triangulate.cpp for more details.


#ifndef EAR_CLIP_TRIANGULATE_H
#define EAR_CLIP_TRIANGULATE_H

namespace ear_clip_triangulate
{
	// coord type float
	void compute(
		nstl::vector<pair<float, int>>* results,
		int path_count,
		const nstl::vector<pair<float, int>> paths[],
		int debug_halt_step = -1,
		nstl::vector<float>* debug_remaining_loop = NULL);
}


#endif // EAR_CLIP_TRIANGULATE_H
