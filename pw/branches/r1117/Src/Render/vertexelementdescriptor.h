#pragma once

#include "vertexelementusage.h"
#include "vertexelementtype.h"

namespace Render
{
	/// Описания формата элемента вершины
	struct VertexElementDescriptor
	{
		/// Конструктор 
		VertexElementDescriptor(): stream(0), offset(0), type(VERTEXELEMENTTYPE_FLOAT3), usage(VERETEXELEMENTUSAGE_POSITION), usageIndex(0) {}
		/// Конструктор 
		VertexElementDescriptor( unsigned int _stream, unsigned int _offset, EVertexElementType _type, EVertexElementUsage _usage, unsigned int _usageindex ): 
			stream(_stream), offset(_offset), type(_type), usage(_usage), usageIndex(_usageindex) {}

		bool operator == (const VertexElementDescriptor& other) const
		{
			return (stream == other.stream) && (offset == other.offset) && (type == other.type) && 
						 (usage == other.usage) && (usageIndex == other.usageIndex);
		}
		bool operator != (const VertexElementDescriptor& other) const { return !operator == (other); }


		/// Номер потока
		unsigned int stream;
		/// Смещение
		unsigned int offset;
		/// Тип 
		EVertexElementType type;
		/// Тип использования
		EVertexElementUsage usage;
		/// Индекс использования
		unsigned int usageIndex;
	};
}; // namespace Render