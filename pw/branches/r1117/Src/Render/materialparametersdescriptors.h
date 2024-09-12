#pragma once

#include "sampler.h"

namespace Render
{
	///
	struct MaterialSamplerPresentCondition
	{
		unsigned int defineIndex;
		unsigned int values[8];
		unsigned int valuesCount;
	};

	///
	struct MaterialSampler : public NDb::MaterialSampler
	{
		bool IsPresent(const ShaderDefinesValues& values) const 
		{ 
			for (unsigned int i = 0; i < presentCondition.valuesCount; ++i)
			{
				if ( presentCondition.values[i] == values.GetDefineValue(presentCondition.defineIndex) ) return true;
			}
			return false;			
		}
	};
}; // namespace Render