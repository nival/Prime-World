#include "stdafx.h"

#pragma once

#include "shaderconstantsbinder.h"
#include "renderer.h"

namespace Render
{
namespace ShaderConstantsBinder
{
///
void BindPixelShaderConstants( ShaderConstantTable& table)
{
	if ( table.maxChangedRegister < table.minChangedRegister ) return;
	Renderer::SetPixelShaderConstants( table.minChangedRegister, table.maxChangedRegister - table.minChangedRegister + 1, reinterpret_cast<const unsigned char*>( &table[table.minChangedRegister] ) );
	table.ClearChangedIndexes();
}
///
void BindVertexShaderConstants( ShaderConstantTable& table)
{
	if ( table.maxChangedRegister < table.minChangedRegister ) return;
	Renderer::SetVertexShaderConstants( table.minChangedRegister, table.maxChangedRegister - table.minChangedRegister + 1, reinterpret_cast<const unsigned char*>( &table[table.minChangedRegister] ) );
	table.ClearChangedIndexes();
}
}; // namespace ShaderConstantsBinder
}; // namespace Render