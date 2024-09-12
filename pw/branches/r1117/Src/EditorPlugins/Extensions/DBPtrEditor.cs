using System;
using System.ComponentModel;
using System.Drawing.Design;
using System.Security.Permissions;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorLib.ObjectSelector;
using libdb;
using libdb.DB;
using libdb.IO;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  [PermissionSet( SecurityAction.Demand, Name="FullTrust" )]
  public class DBPtrEditor : TypedValueEditor<DBPtrBase>    
  {
    public DBPtrEditor( IEditorWinApplication application ) : base( application ) {}

    public override UITypeEditorEditStyle EditorEditStyle
    {
      get { return UITypeEditorEditStyle.Modal; }
    }

    public override bool IsDropDownResizable 
    {
      get { return true; } 
    }

    protected override DBPtrBase EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, DBPtrBase value )
    {
      ObjectSelectorForm selector = new ObjectSelectorForm();

      IOwnerable ownerable = null;
      DBResource resource = null;
      if ( value != null && !value.DBId.IsEmpty && !value.DBId.IsInlined )
        selector.SetCurrentItem( value.DBId );
			else if ( ( resource = instance as DBResource ) != null )
        selector.SetCurrentFolder( FileUtils.GetFolderName( resource.DBId.FileName ) );
			else if ( ( ownerable = instance as IOwnerable ) != null && ownerable.GetOwner() != null )
        selector.SetCurrentFolder( FileUtils.GetFolderName( ownerable.GetOwner().DBId.FileName ) );

      selector.SetPossibleTypes( TypeUtils.GetTypeFromPtr( context.PropertyDescriptor.PropertyType ) );
      if ( selector.ShowDialog() != DialogResult.OK )
        return value;

      if ( null != selector.SelectedObject )
      {
        value = DataBase.Get<DBResource>( selector.SelectedObject );
        if ( value != null && !DBID.IsNullOrEmpty( value.DBId ) )
          return value;    
      }

      return null;      
    }
  }
}
