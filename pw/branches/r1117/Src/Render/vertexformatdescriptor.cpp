#include "stdafx.h"
#include "vertexformatdescriptor.h"

namespace Render
{
/// Конструктор
VertexFormatDescriptor::VertexFormatDescriptor()
{
	vertexElementDescriptors.reserve(32);
}
/// Добавление описания элемента вершины
void VertexFormatDescriptor::AddVertexElement(const VertexElementDescriptor& descr)
{
	vertexElementDescriptors.push_back(descr);
}
void VertexFormatDescriptor::AssignVertexElements( const VertexElementDescriptor& descr, int count )
{
	//assign of range is not exist in nstl, couse I used to memcpy
	vertexElementDescriptors.resize(count);
	memcpy(&vertexElementDescriptors[0], &descr, sizeof(VertexElementDescriptor)*count );
}
/// Получение описания элемента вершины
const VertexElementDescriptor& VertexFormatDescriptor::GetVertexElement(unsigned int index) const
{
	NI_ASSERT(index < GetVertexElementsCount(), "Invalid vertex element index!");
	return vertexElementDescriptors[index];
}
/// Получение количества элементов вершины
unsigned int VertexFormatDescriptor::GetVertexElementsCount() const
{
	return vertexElementDescriptors.size();
}
///
int VertexFormatDescriptor::FindMaxUsageIndex(EVertexElementUsage usage) const
{
	int usageIndex = -1;	
	const int size = vertexElementDescriptors.size();
	for (int i = 0; i < size; ++i)
		if (vertexElementDescriptors[i].usage == usage)
			usageIndex = max(usageIndex, int(vertexElementDescriptors[i].usageIndex));
	return usageIndex;
}
}; // namespace Render