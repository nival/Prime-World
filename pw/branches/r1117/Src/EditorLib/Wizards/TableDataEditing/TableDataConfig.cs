using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;

namespace EditorLib.Wizards.TableDataEditing
{
	[ConfigObject( true )]
	public class TableDataConfig : SimpleConfigObject
	{
		public List<ConfigEntry> entries = new List<ConfigEntry>();
	}

	public class ColumnConfig
	{
		public string name;
		public int index;
		public int width;
	}

	public class ConfigEntry
	{
		public string presetName;
		public List<ColumnConfig> columns = new List<ColumnConfig>();
	}
}
