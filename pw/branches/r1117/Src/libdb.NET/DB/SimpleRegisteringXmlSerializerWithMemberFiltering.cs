using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;

namespace libdb.DB
{
  public class SimpleRegisteringXmlSerializerWithMemberFiltering : SimpleRegisteringXmlSerializer
  {
    private readonly ConfigFile file;
    private readonly Type type;
    private readonly bool includeAllFields;

    public SimpleRegisteringXmlSerializerWithMemberFiltering( Type type, ConfigFile file, bool includeAllFields ) :
      base( type )
    {
      this.file = file;
      this.type = type;
      this.includeAllFields = includeAllFields;
    }

    protected override DBFieldInfo[] GetFields( Type type, bool inherit )
    {
      if ( this.type != type )
        return base.GetFields( type, inherit );

      var res = new List<DBFieldInfo>();
      if ( file != null )
      {
        foreach ( var f in base.GetFields( type, inherit ) )
        {
          var attr = TypeUtils.GetAttribute<ConfigObjectFieldAttribute>( f, inherit );
          if ( ( attr == null && includeAllFields ) || ( attr != null && file.IsMatch( attr ) ) )
            res.Add( f );
        }
      }
      return res.ToArray();
    }

  }
}
