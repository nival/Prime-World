using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;

namespace EditorLib.Scripts
{
  [ConfigObject( false )]
  public class ScriptsConfig : SimpleConfigObject
  {
    public List<string> scripts = new List<string>();
  }
}
