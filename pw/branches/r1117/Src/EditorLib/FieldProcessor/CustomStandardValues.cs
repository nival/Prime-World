using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using libdb.DB;
using System.Reflection;
using libdb.Diagnostics;

namespace EditorLib.FieldProcessor
{
  public class CustomIntPropertyDescriptor : FullTypePropertyDescriptor
  {
    private readonly DBFieldInfo field;
    private readonly Type enumType;
    private readonly int index = 0;
    private readonly Type componentType = null;
    private string displayName = string.Empty;

    # region cache of getting attributes

    private static Dictionary<DBFieldInfo, Attribute[]> attributeCache = new Dictionary<DBFieldInfo, Attribute[]>();
    private static Attribute[] GetAttributes( DBFieldInfo field )
    {
      if ( attributeCache.ContainsKey( field ) )
        return attributeCache[field];

      Attribute[] attributes = TypeUtils.GetAttributes<Attribute>( field, true );
      attributeCache[field] = attributes;

      return attributes;
    }

    private static Attribute[] GetCombinedAttributes( DBFieldInfo field )
    {
      List<Attribute> result = new List<Attribute>( TypeUtils.GetAttributes<Attribute>( field.FieldType, true ) );
      result.AddRange( GetAttributes( field ) );
      return result.ToArray();
    }

    public static Attribute[] GetCombinedAttributes( Type type, Attribute[] attributes )
    {
      List<Attribute> result = new List<Attribute>( TypeUtils.GetAttributes<Attribute>( type, true ) );
      if ( null != attributes )
        result.AddRange( attributes );
      return result.ToArray();
    }

    # endregion

    public CustomIntPropertyDescriptor( DBFieldInfo field, IEditorWinApplication application, Type _enumType )
      : base( FullTypeDescriptor.Create( _enumType, application, GetAttributes( field ) ), field.Name, GetCombinedAttributes( field ) )
    {
      this.field = field;
      enumType = _enumType;
      displayName = field.Name;
    }

    public CustomIntPropertyDescriptor( int index, Type itemType, Type componentType, Attribute[] attributes, IEditorWinApplication application, Type _enumType )
      : base( FullTypeDescriptor.Create( _enumType, application, attributes ), index.ToString(), GetCombinedAttributes( itemType, attributes ) )
    {
      this.index = index;
      enumType = _enumType;
      this.componentType = componentType;
      displayName = index.ToString();
    }

    public CustomIntPropertyDescriptor( int index, string forceName, Type itemType, Type componentType, Attribute[] attributes, IEditorWinApplication application, Type _enumType )
      : base( FullTypeDescriptor.Create( _enumType, application, attributes ), forceName, GetCombinedAttributes( itemType, attributes ) )
    {
      this.index = index;
      enumType = _enumType;
      this.componentType = componentType;
      displayName = forceName;
    }

    public override Type ComponentType { get { return componentType == null ? field.DeclaringType : componentType; } }
    public override Type PropertyType { get { return enumType; } }
    public override string DisplayName { get { return displayName; } }

    public bool IsForcedReadOnly = false;
    public override bool IsReadOnly
    {
      get
      {
        if ( field != null )
          return !field.CanWrite || IsForcedReadOnly;
        return IsForcedReadOnly;
      }
    }

    protected override object GetValueInternal( object component )
    {
      object valueObj = null;
      if ( componentType == null )
      {
        valueObj = field.GetValue( component );
      }
      else
      {
        PropertyInfo itemProperty = TypeUtils.GetProperty( component.GetType(), "Item" );
        if ( null == itemProperty )
        {
          Log.TraceWarning( "Cannot find \"Item\" property in component with type \"{0}\"", component.GetType() );
          return null;
        }

        valueObj = itemProperty.GetValue( component, new object[1] { index } );
      }

      int value = System.Convert.ToInt32( valueObj );
      return Enum.Parse( enumType, value.ToString() );
    }

    protected override void SetValueInternal( object component, object value )
    {
      if ( componentType == null )
        field.SetValue( component, value );
      else
      {
        PropertyInfo itemProperty = TypeUtils.GetProperty( component.GetType(), "Item" );
        if ( null == itemProperty )
        {
          Log.TraceWarning( "Cannot find \"Item\" property in component with type \"{0}\"", component.GetType() );
          return;
        }

        //TODO: Do not throw exception when index outside of array's bounds
        itemProperty.SetValue( component, value, new object[1] { index } );
      }
    }

    public int Index { get { return index; } }

  }
}
