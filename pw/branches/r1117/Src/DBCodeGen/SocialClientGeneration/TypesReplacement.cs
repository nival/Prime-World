using System;
using System.Collections.Generic;
using libdb.DB;

namespace DBCodeGen.SocialClientCodeGeneration
{
  internal sealed class TypesReplacement
  {
    private static Dictionary<string, string> _replacementTable = new Dictionary<string, string>()
    {
      {"TextRef","string"},
      {"List<TextRef>","List<string>"},
      {"Texture","string"},
      {"TextureBase","string"},
      {"ExecutableFloatString","string"},
      {"ExecutableIntString","string"},
      {"ExecutableBoolString","string"},
      {"List<ExecutableFloatString>","List<string>"},
      {"List<ExecutableIntString>","List<string>"},
      {"List<ExecutableBoolString>","List<string>"},
      {"List<Texture>","List<string>"}
      //{typeof(DBPtrBase),typeof(string)}
    };

    public static bool IsReplaceType( string type )
    {
      return _replacementTable.ContainsKey( type );
    }

    public static string TryToReplace(string type)
    {
      if (_replacementTable.ContainsKey(type))
        return _replacementTable[type];
      //if (_replacementTable.ContainsKey(type.BaseType))
      //  return _replacementTable[type.BaseType];
      return type;
    }
  }
}
