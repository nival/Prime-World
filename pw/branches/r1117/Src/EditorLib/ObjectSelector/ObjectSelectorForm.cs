using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.IO;
using EditorLib.ObjectsBrowser;
using EditorLib.Settings;
using libdb.DB;

namespace EditorLib.ObjectSelector
{
  public partial class ObjectSelectorForm : Form
  {
    private static string lastOpenedFolder = string.Empty;

    public ObjectSelectorForm()
    {
      InitializeComponent();
      SetCurrentFolder( lastOpenedFolder );
    }

    public ObjectSelectorForm( DBID currentItem, Type rootType )
      : this()
    {
      SetPossibleTypes( rootType );
      SetCurrentItem( currentItem );
    }

    [Browsable( false )]
    public DBID SelectedObject
    {
      get { return objectsBrowser.SelectedObject; }
    }

    public void SetCurrentFolder( string folder )
    {
      objectsBrowser.CurrentFolder = folder;
      lastOpenedFolder = objectsBrowser.CurrentFolder;
    }

    public void SetCurrentItem( DBID dbid )
    {     
      objectsBrowser.SelectItem( dbid );
    }

    public void SetPossibleTypes( Type rootType )
    {
      objectsBrowser.FilterType = rootType;
    }

    private void OnChangeSelectedItem( ObjectsBrowser.ObjectsBrowser coltrol, DBID dbid )
    {
      object toSelect = null;

      if( !DBID.IsNullOrEmpty( dbid ) )
      {
        toSelect = DataBase.Get<DBResource>( dbid ).Get();
      }
      
      propertyGrid1.SelectedObject = toSelect;
    }

    private void OnOpenButtonClick( object sender, EventArgs e )
    {
      lastOpenedFolder = objectsBrowser.CurrentFolder;
      DialogResult = DialogResult.OK;
    }

    private void OnOpenItem( object sender, DBIDEventArgs e )
    {
      lastOpenedFolder = objectsBrowser.CurrentFolder;
      DialogResult = DialogResult.OK;
    }

    private void ObjectSelectorForm_Load( object sender, EventArgs e )
    {
      ObjectSelectorFormConfig conf = EditorCommonApplication.ApplicationSingleton.Settings.Get<ObjectSelectorFormConfig>();
      
      if ( conf.Width == 0 )
        return;
           
      Location = new Point( conf.X, conf.Y );
      Height = conf.Height;
      Width = conf.Width;

//      SetCurrentFolder( lastOpenedFolder );
      objectsBrowser.Select();
    }

    private void ObjectSelectorForm_FormClosing( object sender, FormClosingEventArgs e )
    {
      var conf = EditorCommonApplication.ApplicationSingleton.Settings.Get<ObjectSelectorFormConfig>();
      conf.X = this.Location.X;
      conf.Y = this.Location.Y;
      conf.Width = this.Size.Width;
      conf.Height = this.Size.Height;
    }

    #region ReadOnly PropertyGrid

    private void propertyGrid1_SelectedObjectsChanged( object sender, EventArgs e )
    {
      SetObjectAsReadOnly();
    }

    private void SetObjectAsReadOnly()
	  {
      if( propertyGrid1.SelectedObject != null )
      {
        TypeDescriptor.AddAttributes( propertyGrid1.SelectedObject, new Attribute[] { new ReadOnlyAttribute( true ) } );
         propertyGrid1.Refresh();
      }
    }

    #endregion
  }

  [ConfigObject( true )]
  public class ObjectSelectorFormConfig : SimpleConfigObject
  {
    public int X = 0, Y = 0, Width = 0, Height = 0;
  }
}
