#pragma once

#include "shaderpair.h"

namespace Render
{
	namespace Materials
	{
		class MultiShader
		{
			struct ShaderObjInfo* pInfo;
			nstl::vector<ShaderPair> pairs;
			nstl::string fileName;
			bool OpenFile();
		public:
			static void InitializeDefaultShaderPair();
			static void ReleaseDefaultShaderPair();
			const nstl::string& GetShaderName() const;
			MultiShader( const nstl::string& fileName );
			
			Render::ShaderPair& GetShaderPairByIndex( unsigned int index );

			void ReloadShaders();

			~MultiShader();

			void Destroy();
		};
	};
};
