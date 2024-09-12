using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;

namespace EditorLib.PropertiesEditor.PropertyPresets
{
  [ApplicableForDeriver]
  public class FilteredEnumProvider : TypedStandardValuesProvider<Enum>
  {
    public FilteredEnumProvider( IEditorWinApplication application ) : base( application ) { }

    public override bool IsStandardValuesExclusive( ITypeDescriptorContext context )
    {
      return true;
    }

    private Array GetEnumValues( Type type, AttributeCollection attributes )
    {
      HideEnumValuesAttribute hideAttribute = null;
      foreach ( var attribute in attributes )
      {
        if ( attribute is HideEnumValuesAttribute )
          hideAttribute = attribute as HideEnumValuesAttribute;
      }
      if ( hideAttribute == null )
        return Enum.GetValues( type );

      ArrayList result = new ArrayList( Enum.GetValues( type ) );
      for ( int i = result.Count - 1; i >= 0; --i )
      {
        if ( hideAttribute.Contains( result[i] as Enum ) )
          result.RemoveAt( i );
      }
      return result.ToArray();
    }

    public override TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext context )
    {
      Array values = GetEnumValues( context.PropertyDescriptor.PropertyType, context.PropertyDescriptor.Attributes );

      PropertyPresetConfig configSet = Application.Application.Settings.Get<PropertyPresetConfig>();
      if ( configSet.selectedPreset < 0 || configSet.selectedPreset >= configSet.configPresets.Count )
        return new TypeConverter.StandardValuesCollection( values );

      PropertyPresetConfig.PresetConfigItem config = configSet.configPresets[configSet.selectedPreset];

      List<string> hiddenValues;
      if ( !config.hiddenEnumValues.TryGetValue( context.PropertyDescriptor.PropertyType.Name, out hiddenValues ) )
        return new TypeConverter.StandardValuesCollection( values );

      List<Enum> filteredValues = new List<Enum>();
      foreach ( object item in values )
      {
        if ( !hiddenValues.Contains( item.ToString() ) )
          filteredValues.Add( item as Enum );
      }

      return new TypeConverter.StandardValuesCollection( filteredValues );
    }

    public override bool HasStandardValuesConvertor( ITypeDescriptorContext context )
    {
      return false;
    }

    public override Type GetStandardValuesType( ITypeDescriptorContext context )
    {
      throw new NotImplementedException();
    }

    protected override Enum ConvertFromStandardValueInternal( ITypeDescriptorContext context, object instance, object value )
    {
      throw new NotImplementedException();
    }
  }
}
