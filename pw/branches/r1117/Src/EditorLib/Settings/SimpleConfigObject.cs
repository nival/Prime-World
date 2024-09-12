using System;
using System.Reflection;
using System.Xml;
using libdb.DB;

namespace EditorLib.Settings
{
  public abstract class SimpleConfigObject : IConfigObject
  {
    protected virtual void OnBeforeSerialize() { }
    protected virtual void OnAfterDeserialize() { }

    public void Serialize( XmlWriter writer, ConfigFile file )
    {
      var attr = TypeUtils.GetAttribute<ConfigObjectAttribute>( GetType(), false );
      if ( attr == null )
        return;

      OnBeforeSerialize();
      XmlSerializer serialize = new SimpleRegisteringXmlSerializerWithMemberFiltering( GetType(), file, file == null ? true : file.IsMatch( attr ) );
      serialize.Serialize( this, writer );
    }

    public bool Deserialize( XmlReader reader )
    {
      if ( reader.IsEmptyElement )
        reader.Skip();
      else
      {
        XmlSerializer serialize = new SimpleRegisteringXmlSerializer( GetType() );
        serialize.Deserialize( this, reader );
      }

      OnAfterDeserialize();
      return true;
    }
  }
}
