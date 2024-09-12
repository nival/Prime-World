using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using libdb.DB;
using EditorLib.PropertiesEditor;
using WeifenLuo.WinFormsUI.Docking;
using EditorLib.Panels;
using EditorLib.ObjectsBrowser;

namespace EditorLib.BacklinksInfo
{
	public partial class BacklinksInfo : DockContent
	{
		private IEditorWinApplication application = null;

		public BacklinksInfo( IEditorWinApplication application, DBID dbid, Dictionary<DBID, int> _backlinks )
		{
			InitializeComponent();

			this.application = application;
			Text = dbid.FileName;

			foreach ( KeyValuePair<DBID, int> pair in _backlinks )
				backlinks.Items.Add( pair.Key.Name ).Tag = pair.Key;

			backlinks.Columns[0].Width = -2;
		}

		private void OnBacklinksMouseDoubleClick( object sender, MouseEventArgs e )
		{
			if ( !( sender is ListView ) )
				return;

			DBID dbid = (sender as ListView).FocusedItem.Tag as DBID;
			ObjectsBrowserPanel panel = application.Panels.GetSingletonPanel<ObjectsBrowserPanel>();
			panel.SelectItem( dbid );
			Close();
		}

		protected override void OnClientSizeChanged( EventArgs e )
		{
			base.OnClientSizeChanged( e );
			backlinks.Columns[0].Width = -2;
		}
	}
}
