#pragma once

namespace Render
{
	class OmniLight
	{
	public:
		HDRColor diffuseColor;
		HDRColor specularColor;
		float radius;
		CVec3 position;
		float GetAttenuation(float distance) const
		{
			NI_ASSERT(distance > 0, "distance should be positive");
			NI_ASSERT(radius > 0, "radius should be positive");
			return distance > radius ? 0 : (1.f - distance/radius);
		}
	};
};