#pragma once

#include "Vendor/DirectX/Include/d3d9types.h"
#include "renderprimitivetype.h"
#include "vertexelementtype.h"
#include "vertexelementusage.h"
#include "renderstates.h"
#include "renderformat.h"
#include "sampler.h"

namespace Render
{

/// Конвертирование типа примитивов рендера в d3d9
D3DPRIMITIVETYPE ConvertPrimitiveType(ERenderPrimitiveType type);
/// Конвертирование типа элемента вершины в его размер
UINT GetVertexElementSize(EVertexElementType type);
/// Конвертирование типа использования элемента вершины в d3d9
BYTE ConvertVertexElementUsage(EVertexElementUsage usage);
/// Конвертирование типа элемента вершины в d3d9
BYTE ConvertVertexElementType(EVertexElementType type);

/// Конвертирование типа использования элемента вершины из d3d9
EVertexElementUsage Convert2VertexElementUsage(BYTE usage);
/// Конвертирование типа элемента вершины из d3d9
EVertexElementType Convert2VertexElementType(BYTE type);

DWORD ConvertRenderLockType(ERenderLockType type);

/// 
D3DFORMAT ConvertRenderFormat(ERenderFormat format);

/// get format name
const char* D3DFormat2Str(DWORD _format);

/// get pool name
const char* D3DPool2Str(D3DPOOL _pool);

}; // namespace Render