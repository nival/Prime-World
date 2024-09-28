#pragma once

namespace Render
{
	namespace ShaderConstantsBinder
	{
		///
		void BindPixelShaderConstants( ShaderConstantTable& table);
		///
		void BindVertexShaderConstants( ShaderConstantTable& table);
	}; // namespace ShaderConstantsBinder
}; // namespace Render