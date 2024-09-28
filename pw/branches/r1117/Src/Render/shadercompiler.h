#pragma once

#include "DxIntrusivePtr.h"
#include "shaderdefinestable.h"

namespace Render
{
	///
	DXPixelShaderRef CompilePixelShaderFromFile(const char* filename, const ShaderDefinesTable& definesTable = ShaderDefinesTable());
	///
	DXVertexShaderRef CompileVertexShaderFromFile(const char* filename, const ShaderDefinesTable& definesTable = ShaderDefinesTable());
}; // namespace Render