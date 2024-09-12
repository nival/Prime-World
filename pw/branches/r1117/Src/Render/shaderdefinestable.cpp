#include "stdafx.h"

#include "shaderdefinestable.h"

namespace Render
{
///
unsigned int ShaderDefinesDescriptorsTable::GetVariationsCount() const
{
	unsigned int numVariations = 1;

	for (unsigned int i = 0; i < GetShaderDefineDescriptorsCount(); ++i)
	{
		const ShaderDefineDescriptor& descr = GetShaderDefineDescriptor(i);
		numVariations *= (descr.maxValue - descr.minValue + 1);
	}

	return numVariations;
}

///
Render::ShaderDefinesTable ShaderDefinesDescriptorsTable::GetDefineTableByIndex( unsigned int index ) const
{
	unsigned int count = GetShaderDefineDescriptorsCount();

	unsigned int pow = 1;
	for (unsigned int i = 0; i < count - 1; i++)
	{
		const ShaderDefineDescriptor& descr = GetShaderDefineDescriptor(i);
		pow *= descr.maxValue - descr.minValue + 1; 
	}

	nstl::vector<unsigned int> valuesInversed;
	valuesInversed.resize(count);

	unsigned int current = index;

	for (unsigned int i = 0; i < count; i++)
	{
		unsigned int value = current / pow;
		current -= pow * value;
		valuesInversed[i]	= value;
		if ( count - i >= 2) // FIXME SHAMANSTVO
		{
			const ShaderDefineDescriptor& descr = GetShaderDefineDescriptor(count - i - 2);
			pow /= descr.maxValue - descr.minValue + 1;
		}
		else pow = 1;
	}

	ShaderDefinesTable table;
	for (unsigned int i = 0; i < count; i++) table.AddShaderDefine( ShaderDefine(GetShaderDefineDescriptor(i).name, valuesInversed[count - i - 1]) );

	return table;
}

///
unsigned int ShaderDefinesValues::GetVariationIndex( const ShaderDefinesDescriptorsTable& descrTable ) const
{
	NI_ASSERT(descrTable.GetShaderDefineDescriptorsCount() == GetValuesCount(), "Invalid shader defines descriptors table!");

	unsigned int pow = 1;
	unsigned int index = 0;

	for (unsigned int i = 0; i < GetValuesCount(); i++)
	{
		unsigned int value = GetDefineValue(i);
		index += value * pow;

		const ShaderDefineDescriptor& defineDescr = descrTable.GetShaderDefineDescriptor(i);
		pow *= (defineDescr.maxValue - defineDescr.minValue + 1);
	}

	return index;
}
}; // namespace Render