using System.Collections.Generic;
using System.Drawing;
using EditorLib.Settings;

namespace EditorLib.PropertiesEditor
{
  [ConfigObject( true )]
	public class PropertiesEditorConfig : SimpleConfigObject
	{
    public bool showOutliner = false;
    public float outlinerRelSize = -1.0f;

    public bool IsOutlinerColored = false;
    public List<Color> OutlinerColors = new List<Color>();
  }
}
