using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorLib.PropertiesEditor;
using EditorLib;
using libdb.DB;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public sealed class FlagsEnumEditor : TwoTypedValueEditor<Enum, FlagsAttribute>
  {
    public FlagsEnumEditor( IEditorWinApplication application, Attribute attribute ) : base( application, attribute ) {}

    public override bool IsDropDownResizable { get { return false; } }
    public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.DropDown; } }

    protected override Enum EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, Enum value )
    {
      IWindowsFormsEditorService formEditor = provider.GetService( typeof( IWindowsFormsEditorService ) ) as IWindowsFormsEditorService;
      HideEnumValuesAttribute hideValues = null;
      foreach ( var attribute in context.PropertyDescriptor.Attributes )
      {
        if ( attribute is HideEnumValuesAttribute )
          hideValues = attribute as HideEnumValuesAttribute;
      }
      FlagsEnumControl flagsEnumControl = new FlagsEnumControl( value, hideValues );

      int height = flagsEnumControl.Items.Count * (flagsEnumControl.ItemHeight + 1);

      flagsEnumControl.Height = Math.Min( height, GetHeight( Cursor.Position.Y, flagsEnumControl ) );

      formEditor.DropDownControl( flagsEnumControl );
      return flagsEnumControl.Value;
    }

    private int GetHeight( int y, Control control )
    {
      Rectangle screen = Screen.GetBounds( control );
      Rectangle workingArea = Screen.GetWorkingArea( control );

      int taskBar = screen.Height - workingArea.Height;

      if ( y < ( screen.Height / 2 ) )
      {
        return screen.Height - taskBar - y - 40;
      }

      return y - taskBar - 40;
    }
  }
}