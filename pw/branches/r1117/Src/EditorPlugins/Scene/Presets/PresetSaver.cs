using System.Collections.Generic;
using EditorLib.Settings;
using libdb.DB;

namespace EditorPlugins.Scene.Presets
{
	[ConfigObject( true )]
	public sealed class PresetSaver : SimpleConfigObject
	{
		public class PresetInfo
		{
			public string typeName = string.Empty;
			public string name = string.Empty;
		}

		public Dictionary<string, PresetInfo> values = new Dictionary<string,PresetInfo>();

		public void Modify(DBResource resource, PresetInfo preset)
		{
			values[resource.GetType().Name] = preset;
		}

		public PresetInfo Get(DBResource resource)
		{
			if (values.ContainsKey(resource.GetType().Name))
			{
				return values[resource.GetType().Name];
			}
			return null;
		}
	}
}