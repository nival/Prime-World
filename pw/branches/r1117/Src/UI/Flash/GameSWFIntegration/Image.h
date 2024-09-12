#pragma once 

#include "SwfTypes.h"

namespace jpeg { struct input; };

namespace image
{
	struct image_base
	{
		flash::UI8*	m_data;
		int	m_width;
		int	m_height;
		int	m_pitch;	// byte offset from one row to the next

    image_base(flash::UI8* data, int width, int height, int pitch) :
      m_data(data),
      m_width(width),
      m_height(height),
      m_pitch(pitch)
    {
    }

		virtual ~image_base()
    {
      if (m_data) 
      {
        delete [] m_data;
        m_data = 0;
      }
    }
	};

	// 32-bit RGBA image.  Packed data, red byte first (RGBARGBA...)
	struct rgba : public image_base
	{
		rgba(int width, int height);
	};

	// Make a system-memory 32-bit bitmap surface.  Packed data,
	// red byte first.
	rgba*	create_rgba(int width, int height);


	flash::UI8*	scanline(image_base* surf, int y);
	const flash::UI8*	scanline(const image_base* surf, int y);
};
