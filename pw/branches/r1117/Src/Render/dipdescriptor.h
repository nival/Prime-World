#pragma once

#include "renderprimitivetype.h"

namespace Render
{

/// Описание DIP
struct DipDescriptor
{
	DipDescriptor() : minIndex(0) {}
  DipDescriptor(ERenderPrimitiveType _primType, int _base, UINT _minIndex,
                UINT _numVertices, UINT _startIndex, UINT _primCount)
    : primitiveType(_primType), baseVertexIndex(_base), minIndex(_minIndex)
    , numVertices(_numVertices), startIndex(_startIndex), primitiveCount(_primCount)
  {}

	/// Тип примитивов
	ERenderPrimitiveType primitiveType;
	/// Смещение индексов
	int baseVertexIndex;
	unsigned int minIndex;
	/// Количество вершин
	unsigned int numVertices;
	/// Номер индекса, начиная с которого начинается вывод
	unsigned int startIndex;
	/// Количество примитивов
	unsigned int primitiveCount;
};

UINT inline PrimCount2IndexCount(UINT _primitiveCount, ERenderPrimitiveType _primitiveType)
{
  switch(_primitiveType)
  {
  case RENDERPRIMITIVE_LINELIST:
    return _primitiveCount * 2;
  case RENDERPRIMITIVE_LINESTRIP:
    return _primitiveCount + 1;
  case RENDERPRIMITIVE_TRIANGLELIST:
    return _primitiveCount * 3;
  case RENDERPRIMITIVE_TRIANGLESTRIP:
    return _primitiveCount + 2;
  case RENDERPRIMITIVE_TRIANGLEFAN:
    return _primitiveCount + 2;
  default:
    NI_ASSERT(false, "Wrong _primitiveType in PrimCount2IndexCount!");
    return UINT_MAX;
  }
}

} // namespace Render