#pragma once

//#include "dbmaterial.h"

namespace Render
{
	///
	struct ShaderDefine
	{
		ShaderDefine(): value(0) {}
		ShaderDefine(const nstl::string& _name, unsigned int _value): name(_name), value(_value) {}

		nstl::string name;
		unsigned int value;
	};

	class ShaderDefinesValues;
	class ShaderDefinesTable;

	///
	struct ShaderDefineDescriptor
	{
		string name;
		int minValue;
		int maxValue;

		bool bCanChangedInEditor;
		nstl::vector< nstl::string > definesValuesDescriptions;
	};

	///
	class ShaderDefinesDescriptorsTable
	{
	public:
		ShaderDefinesDescriptorsTable() {}

		///
		const ShaderDefineDescriptor& GetShaderDefineDescriptor(unsigned int i) const { NI_ASSERT(i < GetShaderDefineDescriptorsCount(), "Invalid shader define descriptor index!"); return definesDescriptors[i]; }
		///
		unsigned int GetShaderDefineDescriptorsCount() const { return definesDescriptors.size(); }
		///
		unsigned int GetVariationsCount() const;
		///
		ShaderDefinesTable GetDefineTableByIndex(unsigned int index) const;
		void AddDefineDescriptor( const ShaderDefineDescriptor& descr ) { definesDescriptors.push_back(descr); }

	protected:
		nstl::vector<ShaderDefineDescriptor> definesDescriptors;
	};

	///
	class ShaderDefinesValues
	{
	public:
		///
		ShaderDefinesValues() { values.reserve(64); }

		bool operator == (const ShaderDefinesValues& other) const
		{
			unsigned int valuesCount = GetValuesCount();
			if ( valuesCount != other.GetValuesCount() ) return false;
			else
			{
				for (unsigned int i = 0; i < valuesCount; i++) 
				{
					if ( values[i] != other.values[i] ) return false;
				}
				return true;
			}
		}
		bool operator != (const ShaderDefinesValues& other) const { return !operator == (other); }

		///
		void AddDefineValue(unsigned int value) 
		{ 
			values.push_back(value);
		}
		///
		unsigned int GetDefineValue(unsigned int i) const { NI_ASSERT(i < GetValuesCount(), "Invalid define value index!"); return values[i]; }
		///
		unsigned int GetValuesCount() const { return values.size(); }
		///
		unsigned int GetVariationIndex(const ShaderDefinesDescriptorsTable& descrTable) const;
		void SetDefineValue(unsigned int index, unsigned int value)
		{
			values[index] = value;
		}

	private:
		nstl::vector<unsigned int> values;
		typedef nstl::vector<unsigned int>::iterator ValuesIterator;
	};

	///
	class ShaderDefinesTable
	{
	public:
		ShaderDefinesTable() { shaderDefines.reserve(64); }
		///
		void AddShaderDefine(const ShaderDefine& define) { shaderDefines.push_back(define); }
		///
		unsigned int GetDefinesCount() const { return shaderDefines.size(); }
		///
		const ShaderDefine& GetShaderDefine(unsigned int i) const { NI_ASSERT(i < GetDefinesCount(), "Invalid shade define index!"); return shaderDefines[i]; }

		///
		void Set(const ShaderDefinesDescriptorsTable& descrTable, const ShaderDefinesValues& shaderDefinesValues)
		{
			NI_ASSERT(descrTable.GetVariationsCount() == shaderDefinesValues.GetValuesCount(), "Invalid shader defines values and descripotrs tables!");

			for (unsigned int i = 0; i < descrTable.GetShaderDefineDescriptorsCount(); ++i)
			{
				AddShaderDefine( ShaderDefine( descrTable.GetShaderDefineDescriptor(i).name, shaderDefinesValues.GetDefineValue(i) ) );
			}
		}
	private:
		///
		nstl::vector<ShaderDefine> shaderDefines;
	};
}; // namespace Render