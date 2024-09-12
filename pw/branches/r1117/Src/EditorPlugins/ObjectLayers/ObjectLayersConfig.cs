using System.Collections.Generic;
using EditorLib.Settings;

namespace EditorPlugins.ObjectLayers
{
  [ConfigObject( false, "ObjectLayersPresets" )]
  public sealed class ObjectLayersConfig : SimpleConfigObject
  {
    public List<ObjectLayersPreset> Presets = new List<ObjectLayersPreset>();
  }
}
