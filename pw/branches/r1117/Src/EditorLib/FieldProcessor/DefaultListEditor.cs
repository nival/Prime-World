using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.Windows.Forms;
using System.Windows.Forms.Design;

namespace EditorLib.FieldProcessor
{
  public class DefaultListEditor : IValueEditor
  {
    private readonly IEditorWinApplication application;

    public DefaultListEditor( IEditorWinApplication _application )
    {
      application = _application;
    }

    public bool IsDropDownResizable
    {
      get { return false; }
    }

    public UITypeEditorEditStyle EditorEditStyle
    {
      get { return UITypeEditorEditStyle.DropDown; }
    }

    public IEditorWinApplication Application
    {
      get { return application; }
    }

    public object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
    {
      TypeConverter converter = context.PropertyDescriptor.Converter;
      IWindowsFormsEditorService formEditor = provider.GetService( typeof( IWindowsFormsEditorService ) ) as IWindowsFormsEditorService;
      TypeConverter.StandardValuesCollection valuesList = context.PropertyDescriptor.Converter.GetStandardValues( context );

      ListBox listBox = new ListBox();
      listBox.BorderStyle = BorderStyle.None;
      listBox.IntegralHeight = false;

      listBox.SelectedIndexChanged += delegate
      { 
        value = converter.ConvertFromString(listBox.SelectedItem as string );
      };

      listBox.MouseClick += delegate
      {
        formEditor.CloseDropDown();
      };

      foreach( object item in valuesList )
      {
        string str = converter.ConvertToString( item );
        listBox.Items.Add( str );
      }

      int height = listBox.Items.Count * ( listBox.ItemHeight + 2 );

      listBox.Height = Math.Min( height, GetHeight( Cursor.Position.Y, listBox ) );

      formEditor.DropDownControl( listBox );

      return value;
    }

    private int GetHeight( int y , Control control)
    {
      Rectangle screen = Screen.GetBounds( control );
      Rectangle workingArea = Screen.GetWorkingArea( control );

      int taskBar = screen.Height - workingArea.Height;

      if( y < ( screen.Height / 2 ) )
      {
        return screen.Height - taskBar - y - 40;
      }

      return y - taskBar - 40;
    }
  }
}
