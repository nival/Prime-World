using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using System.Globalization;
using DBTypes;
using EditorLib;
using EditorLib.FieldProcessor;
using EditorNative;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Editors.FileRef
{
  public sealed class SwfFileRefEditor : TwoTypedValueEditor<string, SwfFileRefAttribute>
  {
    public SwfFileRefEditor( IEditorWinApplication _application, Attribute _attribute ) 
      : base( _application, _attribute ) { }

		public override bool IsDropDownResizable 
    { 
      get { return false; } 
    }

		public override UITypeEditorEditStyle EditorEditStyle 
    { 
      get { return UITypeEditorEditStyle.Modal; } 
    }

		protected override string EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, string value )
		{
		  UIFlashLayout flashLayout = instance as UIFlashLayout;
      Log.Assert( flashLayout != null, "You can use SwfFileRefAttribute only for UIFlashLayout" );

      if(flashLayout != null)
      {
        string fileName = FileRefHelper.GetFile( instance, value, Attribute.filenameExtension );

        //List<string> list = new List<string> { "testProp1", "testProp2" };

        List<string> list = EditorUIScene.GetFlashPublicFields( fileName );
       
        //clear unused properties
        for (int i = flashLayout.properties.Count - 1; i >= 0 ; i--)
        {
          UIFlashProperties prop = flashLayout.properties[i];

        	if(!list.Contains(prop.propertyName))
          {
            flashLayout.properties.Remove( prop );
          }
          else
          {
            list.Remove(prop.propertyName);
          }
        }

        //add new
        for (int i=0; i<list.Count; i++)
          flashLayout.properties.Add(new UIFlashProperties { propertyName = list[i] });

        return fileName;
      }  

  	  return value;
		}
  }

  public sealed class SwfFileRefStringConverter : TwoTypedStringConvertor<string, SwfFileRefAttribute>
  {
    public SwfFileRefStringConverter( IEditorWinApplication _application, Attribute _attribute ) 
      : base( _application, _attribute )
    {
    }

    public override bool SuppressProperties { get { return true; } }

    protected override string ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      if(string.IsNullOrEmpty(value))
      {
        UIFlashLayout flashLayout = instance as UIFlashLayout;
        Log.Assert( flashLayout != null, "You can use SwfFileRefAttribute only for UIFlashLayout" );

        if(flashLayout != null)
          flashLayout.properties.Clear();
      } 

      return value;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      return value;
    }
  }
}
