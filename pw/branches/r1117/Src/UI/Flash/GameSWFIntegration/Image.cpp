#include "TamarinPCH.h"

#include "image.h"

namespace image
{
	flash::UI8*	scanline(image_base* surf, int y)
	{
		assert(surf);
		assert(y >= 0 && y < surf->m_height);
		return ((flash::UI8*) surf->m_data) + surf->m_pitch * y;
	}


	const flash::UI8*	scanline(const image_base* surf, int y)
	{
		assert(surf);
		assert(y >= 0 && y < surf->m_height);
		return ((const flash::UI8*) surf->m_data) + surf->m_pitch * y;
	}

	//
	// rgba
	//

	rgba::rgba(int width, int height)
		:
		image_base(0, width, height, width * 4)
	{
		assert(width > 0);
		assert(height > 0);
		assert(m_pitch >= m_width * 4);
		assert((m_pitch & 3) == 0);

		m_data = new flash::UI8[m_pitch * m_height];
	}

	rgba*	create_rgba(int width, int height)
	{
		rgba*	s = new rgba(width, height);

		return s;
	}
}

