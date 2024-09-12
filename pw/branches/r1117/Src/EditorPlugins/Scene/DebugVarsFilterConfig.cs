using System.Collections.Generic;
using EditorLib.Settings;

namespace EditorPlugins.Scene
{
  [ConfigObject( true )]
  public sealed class DebugVarsFilterConfig : SimpleConfigObject
	{
    [ConfigObjectField( false )]
		public List<string> CommonDebugVars = new List<string>();
    public List<string> UserDebugVars = new List<string>();
	}
}
