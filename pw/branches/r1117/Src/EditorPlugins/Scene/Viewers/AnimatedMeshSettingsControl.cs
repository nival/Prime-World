using System;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.ObjectSelector;
using libdb.DB;
using Render.DBRender;


namespace EditorPlugins.Scene.Viewers
{
	public partial class AnimatedMeshSettingsControl : UserControl
	{
		private DBPtr<DBTypes.Skeleton> mesh = null;

		public AnimatedMeshSettingsControl()
		{
			InitializeComponent();
			meshTextBox.Text = DBID.Empty.Name;
			mesh = null;
		}

		public DBPtr<DBTypes.Skeleton> Mesh { get { return mesh; } }

		private void OnSelectMeshButtonClick(object sender, EventArgs e)
		{
			ObjectSelectorForm form = new ObjectSelectorForm();
			form.SetPossibleTypes(typeof(DBTypes.Skeleton));
			if (mesh != null && !DBID.IsNullOrEmpty(mesh.DBId))
				form.SetCurrentItem(mesh.DBId);

			if (form.ShowDialog() == DialogResult.OK)
				SetMeshName(form.SelectedObject);
		}

		internal event Operation MeshNameChangedEvent;

		internal void SetMeshName(DBID meshName)
		{
			DBPtr<DBTypes.Skeleton> oldMesh = mesh;
			mesh = DBID.IsNullOrEmpty(meshName) ? null : DataBase.Get<DBTypes.Skeleton>(meshName);
			if (mesh != oldMesh && MeshNameChangedEvent != null)
				MeshNameChangedEvent();

			if (mesh == null || DBID.IsNullOrEmpty(mesh.DBId))
				meshTextBox.Text = DBID.Empty.Name;
			else
				meshTextBox.Text = mesh.DBId.Name;
		}
	}
}
