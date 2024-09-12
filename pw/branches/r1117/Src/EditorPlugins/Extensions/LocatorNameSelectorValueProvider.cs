using System;
using System.Collections.Generic;
using System.ComponentModel;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;

namespace EditorPlugins.Extensions
{
  public sealed class LocatorNameSelectorValueProvider : TwoTypedStandardValuesProvider<string, LocatorNameSelectorAttribute>
  {
    public LocatorNameSelectorValueProvider( IEditorWinApplication _application, Attribute _attribute ) 
      : base( _application, _attribute ) { }

    public override TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext _context )
    {
      List<string> result = new List<string>();
      result.Add( string.Empty );

      AttachedSceneComponent attach = FullTypePropertyDescriptor.GetInstanceFromContext( _context ) as AttachedSceneComponent;
      
      if(attach != null)
      {
        DBSceneComponent owner = attach.GetOwner() as DBSceneComponent;

        if( owner != null && owner.locatorList != null)
        {
          LocatorList list = owner.locatorList.Get();

          if(list != null)
          {
            foreach( var locator in list.locators )
            {
              result.Add( locator.name );
            }

            result.Sort(1, result.Count-1, StringComparer.CurrentCulture);
          }
        }
      }
      
      return new TypeConverter.StandardValuesCollection( result );
    }

    public override bool HasStandardValuesConvertor( ITypeDescriptorContext _context ) { return false; }
    
    protected override string ConvertFromStandardValueInternal( ITypeDescriptorContext _context, object _instance, object _value ) 
    { 
      return _value as string; 
    }
    
    public override bool IsStandardValuesExclusive( ITypeDescriptorContext _context ) { return true; }
    
    public override Type GetStandardValuesType( ITypeDescriptorContext _context ) { return typeof( string ); }
  }

  [ApplicableForDeriver]
  public sealed class LocatorNameSelectorStringConvertor : TwoTypedStringConvertor<string, LocatorNameSelectorAttribute>
  {
    public LocatorNameSelectorStringConvertor( IEditorWinApplication _application, Attribute _attribute )
      : base( _application, _attribute ) { }

    public override bool SuppressProperties { get { return true; } }

    protected override string ConvertFromStringInternal( ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
    {
      if( value == "None" )
        return string.Empty;

      return value;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
    {
      if( string.IsNullOrEmpty( value ) )
        return "None";

      return value;
    }
  }
}
