using System;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.ObjectSelector;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers
{
	public partial class BackgroundMeshSettingsControl : UserControl
	{
		private DBPtr<StaticMesh> mesh = null;

		public BackgroundMeshSettingsControl()
		{
			InitializeComponent();
			meshTextBox.Text = DBID.Empty.Name;
			mesh = null;
		}

		public DBPtr<StaticMesh> Mesh { get { return mesh; } }

		private void OnSelectMeshButtonClick( object sender, EventArgs e )
		{
			ObjectSelectorForm form = new ObjectSelectorForm();
			form.SetPossibleTypes( typeof( StaticMesh ) );
			if ( mesh != null && !DBID.IsNullOrEmpty( mesh.DBId ) )
				form.SetCurrentItem( mesh.DBId );

			if ( form.ShowDialog() == DialogResult.OK )
				SetMeshName( form.SelectedObject );
		}

		internal event Operation MeshNameChangedEvent;

		internal void SetMeshName( DBID meshName )
		{
			DBPtr<StaticMesh> oldMesh = mesh;
			mesh = DBID.IsNullOrEmpty( meshName ) ? null : DataBase.Get<StaticMesh>( meshName );
			if ( mesh != oldMesh && MeshNameChangedEvent != null )
				MeshNameChangedEvent();

			if ( mesh == null || DBID.IsNullOrEmpty( mesh.DBId ) )
				meshTextBox.Text = DBID.Empty.Name;
			else
				meshTextBox.Text = mesh.DBId.Name;
		}
	}
}
