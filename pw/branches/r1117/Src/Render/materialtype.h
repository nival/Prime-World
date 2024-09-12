#pragma once

#include "ubershader.h"

namespace Render
{
	///
	struct MaterialParameterDescriptor
	{
		string name;

		int presentDefineIndex;
		nstl::vector<int> presentValues;

		EShaderType shaderType;

		bool IsPresent(const ShaderDefinesValues& values) const
		{
			if ( presentValues.size() == 0 ) return true;

			int val = values.GetDefineValue(presentDefineIndex);
			for ( int i = 0; i < presentValues.size(); i++)
			{
				if ( val	== presentValues[i] ) return true;
			}
			return false;
		}
	};

	///
	class MaterialType
	{
	public:
		MaterialType( const nstl::string& filename, const ShaderDefinesDescriptorsTable& defineDescriptors )
		{
			/// FIXME
			MaterialParameterDescriptor pdescr;
			pdescr.name = "DiffuseMap";
			pdescr.presentDefineIndex = 1;
			pdescr.presentValues.push_back(0);
			samplersDescriptors.push_back(pdescr);

			MaterialParameterDescriptor pdescr2;
			pdescr2.name = "SpecularMap";
			pdescr2.presentDefineIndex = 1;
			//pdescr2.presentValues.push_back(0);
			samplersDescriptors.push_back(pdescr2);

			MaterialParameterDescriptor pdescr3;
			pdescr3.name = "NormalMap";
			pdescr3.presentDefineIndex = 1;
			//pdescr3.presentValues.push_back(0);
			samplersDescriptors.push_back(pdescr3);

			MaterialParameterDescriptor pdescr4;
			pdescr4.name = "SpecularCubeMap";
			pdescr4.presentDefineIndex = 1;
			//pdescr2.presentValues.push_back(0);
			samplersDescriptors.push_back(pdescr4);

			MaterialParameterDescriptor vdescr;
			vdescr.name = "SunLightDirection";
			vdescr.presentDefineIndex = 0;
			vdescr.shaderType = SHADER_VERTEX;
			vectorParametersDescriptors.push_back(vdescr);

			MaterialParameterDescriptor vdescr2;
			vdescr2.name = "SunLightColor";
			vdescr2.presentDefineIndex = 0;
			vdescr2.shaderType = SHADER_PIXEL;
			vectorParametersDescriptors.push_back(vdescr2);

			MaterialParameterDescriptor vdescr3;
			vdescr3.name = "CameraViewVector";
			vdescr3.presentDefineIndex = 2;
			vdescr3.shaderType = SHADER_VERTEX;
			vdescr3.presentValues.push_back(1);
			vdescr3.presentValues.push_back(2);
			vectorParametersDescriptors.push_back(vdescr3);
			////////////////////

			uberShader.CompileFromFile(filename, defineDescriptors);

			//unsigned int i;
			//uberShader.GetConstantRegisterByName(i, "OmniLightsColors", SHADER_PIXEL);
		}
		///
		UberShader& GetUberShader() { return uberShader; }
		///
		unsigned int GetSamplersDescriptorsCount() const { return samplersDescriptors.size(); }
		///
		const MaterialParameterDescriptor& GetSamplerDescriptor(unsigned int index) const { return samplersDescriptors[index]; }
		
		///
		unsigned int GetVectorParametersDescriptorsCount() const { return vectorParametersDescriptors.size(); }
		///
		const MaterialParameterDescriptor& GetVectorParameterDescriptor(unsigned int index) const { return vectorParametersDescriptors[index]; }

		///
		unsigned int GetFloatParametersDescriptorsCount() const { return floatParametersDescriptors.size(); }
		///
		const MaterialParameterDescriptor& GetFloatParameterDescriptor(unsigned int index) const { return floatParametersDescriptors[index]; }

		///
		const ShaderDefinesDescriptorsTable& GetShaderDefineDescriptors() const { return uberShader.GetShaderDefineDescriptorsTable(); }

		unsigned int GetDefineIndex( const nstl::string& name ) const { return uberShader.GetDefineIndex( name ); }


	protected:
		nstl::vector<MaterialParameterDescriptor> samplersDescriptors;

		nstl::vector<MaterialParameterDescriptor> floatParametersDescriptors;
		nstl::vector<MaterialParameterDescriptor> vectorParametersDescriptors;

		nstl::string shaderFileName;

		UberShader uberShader;
	};
}; // namespace Render