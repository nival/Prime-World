//#include "Foundation.cs"

using System;
using System.Collections.Generic;
using libdb.DB;
using System.ComponentModel;

namespace Render.DBRender
{
	public enum EPixelFormat
	{
		RGBA = 0,
		DXT1,
		DXT5,
		L8,
	}

	[NoCode]
	public enum EPower2
	{
		// For cube map size definition. Needed for import settings
		_4 = 0,
		_8,
		_16,
		_32,
		_64,
		_128,
		_256,
		_512,
		_1024,
		_2048,
		_4096,
	}
	
	public class SamplerPinAttribute : DBAttribute
	{

	}

	public class PinAttribute : DBAttribute
	{
		public readonly List<object> enumList = new List<object>();
		public readonly bool bAlways = false;

		public PinAttribute( params object[] enumList ) 
		{
			this.enumList.AddRange( enumList );
		}

		public PinAttribute()
		{
			bAlways = true;
		}

		public override string ConstructorParameters
		{
			get
			{
				if ( bAlways )
					return String.Empty;
				List<string> enums = new List<string>();
				foreach (object e in enumList)
				{
					enums.Add( string.Format( "{0}.{1}", e.GetType().Name, ((System.Enum)(e)).ToString() ) );
				}
				return String.Join( ", ", enums.ToArray()); } }
	}



	public class ShaderDefineDescriptor
	{
		public string name;
		public int minValue;
		public int maxValue;
		public bool CanChangedInEditor;
		public List<string> definesValuesDescriptions;
	};

	public class ShaderDefinesDescriptorsTable
	{
		public List<ShaderDefineDescriptor> definesDescriptors;
	};

	public class MaterialParameterDescriptor
	{
		public string name;
		public int presentDefineIndex;
		public List<int> presentValues;
	};

  public enum ELightEnvironment
  {
    Day,
    Night,
  }
}
