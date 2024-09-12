using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using libdb.IO;
using System.Reflection;

namespace EditorLib.IO
{
	public partial class RootFileSystemConfigurator : Form
	{
		IEditorCommonApplication application = null;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public RootFileSystemConfigurator( IEditorCommonApplication _application )
		{
			InitializeComponent();
			application = _application;
			fileSystemListView.View = View.Details;
			ImageList images = new ImageList();
			images.Images.Add( EditorLib.EditorLibResources.write );
			fileSystemListView.SmallImageList = images;
			foreach ( IFileSystem fileSystem in application.FileSystem.FileSystems )
			{
				ListViewItem item = AddItemToList( fileSystem );
				item.Tag = fileSystem;
				if ( fileSystem == application.FileSystem.WriteFileSystem )
					item.ImageIndex = 0;
			}

			foreach ( KeyValuePair<string, ConstructorInfo> type in application.FileSystem.FileSystemTypes )
			{
				ToolStripItem item = addContextMenu.Items.Add( type.Key );
				item.Tag = type.Value;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void OnDeleteFileSystemButtonClick( object sender, EventArgs e )
		{
			if ( fileSystemListView.SelectedIndices.Count == 1 )
			{
				application.FileSystem.UnregisterFileSystem( fileSystemListView.SelectedItems[0].Tag as IConfigFileSystem );
				fileSystemListView.Items.RemoveAt( fileSystemListView.SelectedIndices[0] );
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void OnAddFileSystemButtonClick( object sender, EventArgs e )
		{
			addContextMenu.Show( addFileSystemButton, new Point( 0, 0 ) );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private ListViewItem AddItemToList( IFileSystem fileSystem )
		{
			ListViewItem item = null;
			item = new ListViewItem( new string[] { fileSystem.ToString(), fileSystem.UserFriendlyName } );
			item.Tag = fileSystem;
			fileSystemListView.Items.Add( item );
			return item;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void OnSetWritableClick( object sender, EventArgs e )
		{
			if ( fileSystemListView.SelectedIndices.Count == 1 )
			{
				application.FileSystem.WriteFileSystem = fileSystemListView.SelectedItems[0].Tag as IConfigFileSystem;
				foreach ( ListViewItem item in fileSystemListView.Items )
					item.ImageIndex = (item.Tag == application.FileSystem.WriteFileSystem) ? 0 : -1;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void OnCloseClick( object sender, EventArgs e )
		{
			DialogResult = DialogResult.Cancel;
			Close();
		}

		private void OnAddContextMenuItemClicked( object sender, ToolStripItemClickedEventArgs e )
		{
			ConstructorInfo constructor = e.ClickedItem.Tag as ConstructorInfo;
			if ( constructor == null )
				return;

			IConfigFileSystem fileSystem = constructor.Invoke( new object[0] ) as IConfigFileSystem;
			if ( fileSystem.Configure() )
			{
				application.FileSystem.RegisterFileSystem( fileSystem );
				ListViewItem newItem = AddItemToList( fileSystem );
				newItem.Tag = fileSystem;
			}
		}

		private void fileSystemListView_MouseDoubleClick( object sender, MouseEventArgs e )
		{
			if ( e.Button != MouseButtons.Left || fileSystemListView.SelectedItems.Count < 1 )
				return;
			
			var fs = (fileSystemListView.SelectedItems[0].Tag as IConfigFileSystem);
			if ( fs != null )
				fs.Configure();
			
		}

	}
}
