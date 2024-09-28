using libdb.DB;
using System;
using EditorLib.Extensions;
using System.Reflection;
using System.Collections;
using System.Collections.Generic;
using libdb;
using System.ComponentModel;
using EditorLib.Settings;

namespace EditorLib.FieldProcessor
{
  public class FieldDescriptor : FullTypePropertyDescriptor
  {
    private readonly DBFieldInfo field;

    # region cache of getting attributes

    private static Dictionary<DBFieldInfo, Attribute[]> attributeCache = new Dictionary<DBFieldInfo, Attribute[]>();
    private static Attribute[] GetAttributes( DBFieldInfo field, SettingsManager settings )
    {
      if ( attributeCache.ContainsKey( field ) )
        return attributeCache[field];

      Attribute[] attributes = TypeUtils.GetAttributes<Attribute>( field, true );
      string overrideDesc = settings.Get<DescriptionConfigObject>().GetDescription( field.DeclaringType, field.Name );
      if ( !string.IsNullOrEmpty( overrideDesc ) )
      {
        int targetIndex = -1;
        for ( int i = 0; i < attributes.Length; ++i )
        {
          if ( attributes[i] is DescriptionAttribute )
          {
            targetIndex = i;
            break;
          }
        }

        Attribute[] attrsAdjusted = null;
        if ( targetIndex < 0 )
        {
          attrsAdjusted = new Attribute[attributes.Length + 1];
          attributes.CopyTo( attrsAdjusted, 0 );
          targetIndex = attributes.Length;
        }
        else
          attrsAdjusted = attributes;

        attrsAdjusted[targetIndex] = new DescriptionAttribute( overrideDesc );
        attributes = attrsAdjusted;
      }

      attributeCache[field] = attributes;

      return attributes;
    }

    private static Attribute[] GetCombinedAttributes( DBFieldInfo field, SettingsManager settings )
    {
      List<Attribute> result = new List<Attribute>( TypeUtils.GetAttributes<Attribute>( field.FieldType, true ) );
      result.AddRange( GetAttributes( field, settings ) );
      return result.ToArray();
    }

    # endregion

    public FieldDescriptor( DBFieldInfo field, IEditorWinApplication application, string fieldSignature )
      : base( FullTypeDescriptor.Create( field.FieldType, application, GetAttributes( field, application.Application.Settings ), fieldSignature ), field.Name, GetCombinedAttributes( field, application.Application.Settings ) )
    {
      this.field = field;
    }

    public override Type ComponentType { get { return field.DeclaringType; } }

    public bool IsForcedReadOnly = false;
    public override bool IsReadOnly { get { return base.IsReadOnly || !field.CanWrite || IsForcedReadOnly; } }

    protected override object GetValueInternal( object component )
    {
      return field.GetValue( component );
    }

    protected override void SetValueInternal( object component, object value )
    {
      field.SetValue( component, value );
    }

    public override bool ShouldSerializeValue( object component )
    {
      if ( null == component )
        return false;

      ICompositeDBValue obj = null;
      if ( component is ICompositeDBValue )
        obj = component as ICompositeDBValue;
      else if ( component is DBPtrBase )
        obj = ( component as DBPtrBase ).Get<DBResource>();
      else
        return false;

      if ( obj == null || obj.IsFieldDerivedFromParent( Name ) )
        return false;
      else
        return true;
    }

    public override bool CanResetValue( object component )
    {
      return ShouldSerializeValue( component );
    }

    public override void ResetValue( object component )
    {
      if ( !( component is ICompositeDBValue ) )
        return;

      ICompositeDBValue obj = component as ICompositeDBValue;
      obj.ResetField( Name );
    }
  }
}
