using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;
using libdb.DB;

namespace EditorLib.FieldProcessor
{
	[ConfigObject( false, "PropertyDescriptions" )]
  public sealed class DescriptionConfigObject : SimpleConfigObject
  {
    public Dictionary<Type, Dictionary<string, string>> descriptions = new Dictionary<Type,Dictionary<string,string>>();

    protected override void OnAfterDeserialize()
    {
      base.OnAfterDeserialize();
    }

    private bool TryGetDescription( Type ownerType, string fieldName, ref string result )
    {
      if ( !descriptions.ContainsKey( ownerType ) )
        return false;

      Dictionary<string, string> typeSet = descriptions[ownerType];

      if ( !typeSet.ContainsKey( fieldName ) )
        return false;

      result = typeSet[fieldName];
      return !string.IsNullOrEmpty( result );
    }

    public string GetDescription( Type ownerType, string fieldName )
    {
      /*if ( descriptions.Count == 0 )
      {
        descriptions[typeof( DBResource )] = new Dictionary<string, string>();
        descriptions[typeof( DBResource )]["__parent"] = "Universal parent";
      }*/

      string result = string.Empty;

      Type type = ownerType;
      if ( type.IsSubclassOf( typeof(DBPtrBase) ) )
        type = TypeUtils.GetTypeFromPtr( type );
      while ( type != null )
      {
        if ( TryGetDescription( type, fieldName, ref result ) )
          break;

        type = type.BaseType;
      }

      return result;
    }
  }
}
