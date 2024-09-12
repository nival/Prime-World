#pragma once

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
	class MaterialSampler
	{
	public:
		///
		void SetPresentCondition(const MaterialSamplerPresentCondition& condition) { presentCondition = condition; }
		///
		bool IsPresent(const ShaderDefinesValues& values) const 
		{ 
			for (unsigned int i = 0; i < presentCondition.valuesCount; ++i)
			{
				if ( presentCondition.values[i] == values.GetDefineValue(presentCondition.defineIndex) ) return true;
			}
			return false;			
		}
		///
		const nstl::string& GetName() const { return name; }
		///
		void SetName(const nstl::string& _name) { name = _name; }

		///
		void SetSampler(const Sampler& _sampler) { sampler = _sampler; }
		///
		const Sampler& GetSampler() const { return sampler; }
	private:
		Sampler sampler;
		MaterialSamplerPresentCondition presentCondition;
		nstl::string name;
	};

}; // namespace Render