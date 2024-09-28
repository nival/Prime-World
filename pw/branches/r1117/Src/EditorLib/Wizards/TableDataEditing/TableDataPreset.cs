using System;
using System.Collections.Generic;
using EditorLib.Settings;

namespace EditorLib.Wizards.TableDataEditing
{
	[ConfigObject(false, "TableDataPresets")]
	public sealed class TableDataPresetConfig : SimpleConfigObject
	{
		public List<TableDataPreset> Presets = new List<TableDataPreset>();
	}

	[Serializable]
  public class TableDataPreset : ICloneable
  {
    public string Name { get; set; }
    public Type BaseType { get; set; }
    public string RootFolder { get; set; }
		public List<TableDataProperty> Properties { get; set; }

    public TableDataPreset()
    {
			Properties = new List<TableDataProperty>();
    }

		public List<TableDataProperty> GetAllProperies()
		{
			return new List<TableDataProperty>(GetAllProperies(Properties));
		}

		private static IEnumerable<TableDataProperty> GetAllProperies(IEnumerable<TableDataProperty> properties)
		{
			foreach (TableDataProperty property in properties)
			{
				if (property.Index >= 0)
					yield return property;

				foreach (TableDataProperty child in GetAllProperies(property.Properties))
				{
					yield return child;
				}
			}
		}

		public TableDataPreset Clone()
		{
			var result = new TableDataPreset();
			result.Name = Name;
			result.BaseType = BaseType;
			result.RootFolder = RootFolder;

			foreach(TableDataProperty property in Properties)
			{
				result.Properties.Add(property.Clone());
			}

			return result;
		}

		object ICloneable.Clone()
		{
			return Clone();
		}
  }

	[Serializable]
	public class TableDataProperty : ICloneable
	{
		public string Name { get; set; }
		public string Path { get; set; }
		public Type PropertyType { get; set; }
		public string Filter { get; set; }
		public int Index { get; set; }//if index < 0 property don't showing in table
    public List<Type> ArrayTypes { get; set; }
		public List<TableDataProperty> Properties { get; set; }

		public TableDataProperty()
		{
			Properties = new List<TableDataProperty>();
		  ArrayTypes = new List<Type>();
		}

		public TableDataProperty(string name, Type type, string path, int index) 
			: this(name, type, path, index, string.Empty){}

		public TableDataProperty( string name, Type type, string path, int index, string filter )
		{
			Name = name;
			Path = path;
			Filter = filter;
			Index = index;
			PropertyType = type;
			Properties = new List<TableDataProperty>();
			ArrayTypes = new List<Type>();
		}

		public TableDataProperty Clone()
		{
			var result = new TableDataProperty(Name, PropertyType, Path, Index, Filter);
			result.ArrayTypes = new List<Type>(ArrayTypes);
			result.Properties = new List<TableDataProperty>();

			foreach(TableDataProperty p in Properties)
			{
				result.Properties.Add(p.Clone());
			}

			return result;
		}

		object ICloneable.Clone()
		{
			return Clone();
		}

	}
}
