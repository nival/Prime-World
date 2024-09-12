using System.Drawing.Design;
using System.Windows.Forms;
using EditorLib.ObjectSelector;
using libdb;
using libdb.DB;
using libdb.IO;

namespace EditorLib.PropertiesEditor
{
	[System.Security.Permissions.PermissionSet( System.Security.Permissions.SecurityAction.Demand, Name = "FullTrust" )]
	public class DBPtrEditor : System.Drawing.Design.UITypeEditor
	{
		public override System.Drawing.Design.UITypeEditorEditStyle GetEditStyle( System.ComponentModel.ITypeDescriptorContext context )
		{
			return UITypeEditorEditStyle.Modal;
		}

		public override object EditValue( System.ComponentModel.ITypeDescriptorContext context, System.IServiceProvider provider, object value )
		{
			DBPtrBase ptr = value as DBPtrBase;
			if ( ptr != null && ptr.DBId.IsInlined )
				return value;

			ObjectSelectorForm selector = new ObjectSelectorForm();

			IOwnerable ownerable = null;
			DBResource resource = null;
			if ( ptr != null )
				selector.SetCurrentItem( ptr.DBId );
			else if ( (resource = context.Instance as DBResource) != null )
				selector.SetCurrentFolder( FileUtils.GetFolderName( resource.DBId.FileName ) );
			else if ( (ownerable = context.Instance as IOwnerable) != null && ownerable.GetOwner() != null )
				selector.SetCurrentFolder( FileUtils.GetFolderName( ownerable.GetOwner().DBId.FileName ) );

			selector.SetPossibleTypes( TypeUtils.GetTypeFromPtr( context.PropertyDescriptor.PropertyType ) );
			if ( selector.ShowDialog() != DialogResult.OK )
				return value;

			ptr = DataBase.Get<DBResource>( selector.SelectedObject );
			if ( ptr == null || DBID.IsNullOrEmpty( ptr.DBId ) )
				return null;

			return ptr;
		}
	}
}
