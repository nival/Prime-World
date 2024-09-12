#pragma once

#include "smartrenderer.h"

namespace Render
{

	struct ShaderPair
	{
		DXVertexShaderRef pVertexShader;
		DXPixelShaderRef pPixelShader;
		void Bind() 
		{
			ASSERT(Get(pVertexShader) && Get(pPixelShader));
			Render::SmartRenderer::BindVertexShader(pVertexShader);
			Render::SmartRenderer::BindPixelShader(pPixelShader);
		}
	};

};
