#include "TamarinPCH.h"

#include "ear_clip_triangulate_impl.h"


namespace ear_clip_triangulate {
	void compute(
		nstl::vector<pair<float, int>>* results,
		int path_count,
		const nstl::vector<pair<float, int>> paths[],
		int debug_halt_step,
		nstl::vector<float>* debug_edges)
	{
		ear_clip_triangulate::compute_triangulation<float>(results, path_count, paths, debug_halt_step, debug_edges);
	}
}

