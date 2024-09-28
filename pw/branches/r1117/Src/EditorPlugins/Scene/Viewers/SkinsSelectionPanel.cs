using System.Collections.Generic;
using libdb.Diagnostics;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.Panels;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers
{
	public partial class SkinsSelectionPanel : EditorPanel
	{
		#region class SkinPartInfo.

		private class SkinPartInfo
		{
			public readonly string name = string.Empty;
			public readonly string selection = string.Empty;
			public readonly int index = -1;

			internal SkinPartInfo(SkinPart skinPart, int index)
			{
				this.name = skinPart.srcFileName.FileName;
				this.selection = skinPart.selection;
				this.index = index;
			}

			public override string ToString()
			{
				return name + ":" + selection;
  		}
		}

		#endregion

		#region Private members.

		private ISkinsSelectionPanelExtension controller;
		private Dictionary<DBID, List<string>> selectedSkins = new Dictionary<DBID, List<string>>();
		private bool refreshing = false;

		#endregion

		#region Initialization.

		public SkinsSelectionPanel()
		{
			InitializeComponent();
		}

		protected override bool Initialize(IEditorWinApplication application)
		{
			DataBase.RenameDBResourceEvent += OnRenameDBResourceEvent;
			DataBase.DeleteDBResourceEvent += OnDeleteDBResourceEvent;
			return true;
		}

		public override void Terminate(IEditorWinApplication application)
		{
			DataBase.RenameDBResourceEvent -= OnRenameDBResourceEvent;
			DataBase.DeleteDBResourceEvent -= OnDeleteDBResourceEvent;
		}

		#endregion

		#region Event handlers.

		private void OnRenameDBResourceEvent(DBID dbid, DBID oldDbid)
		{
			if (selectedSkins.ContainsKey(oldDbid))
			{
				selectedSkins[dbid] = selectedSkins[oldDbid];
				selectedSkins.Remove(oldDbid);
			}
		}

		private void OnDeleteDBResourceEvent(DBID dbid)
		{
			if (selectedSkins.ContainsKey(dbid))
			{
				selectedSkins.Remove(dbid);
			}
		}

		private void OnItemCheck(object sender, ItemCheckEventArgs e)
		{
			if (refreshing || e.Index < 0 || e.Index >= skinsListBox.Items.Count || !IsValid)
				return;

			SkinPartInfo skin = skinsListBox.Items[e.Index] as SkinPartInfo;
			if ( skin != null )
				controller.ShowSkin( skin.index, e.NewValue == CheckState.Checked );
		}

		private void OnResourceChanged()
		{
			RebuildSkinsList();
		}

		#endregion

		#region Internal methods and properties.

		internal ISkinsSelectionPanelExtension Controller
		{
			set
			{
  			controller = value;
				RebuildSkinsList();
			}
		}

		internal void SelectStartSkins(int number)
		{
			if (IsValid && skinsListBox.Items.Count >= number)
			{
				skinsListBox.BeginUpdate();
        for (int i = 0; i < skinsListBox.Items.Count; ++i)
        {
          skinsListBox.SetItemCheckState(i, CheckState.Unchecked);
          controller.ShowSkin(i, false);
        }
        for (int i = 0; i < number; ++i)
				{
					skinsListBox.SetItemCheckState(i, CheckState.Checked);
					controller.ShowSkin(i, true);
				}
				skinsListBox.EndUpdate();
			}
		}

		internal void SelectSkins(List<int> skins)
		{
			if (IsValid)
			{
				skinsListBox.BeginUpdate();
        for (int i = 0; i < skins.Count; ++i)
				{
          skinsListBox.SetItemCheckState(skins[i], CheckState.Checked);
          controller.ShowSkin(skins[i], true);
				}
				skinsListBox.EndUpdate();
			}
		}

		#endregion

		#region Private helper methods and properties.

		public void RebuildSkinsList()
		{
			if (IsValid)
			{
				refreshing = true;

				noResourceLabel.Visible = false;
				noResourceLabel.Enabled = false;
				skinsListBox.Visible = true;
				skinsListBox.Enabled = true;

				skinsListBox.BeginUpdate();
				skinsListBox.Items.Clear();

				var skins = controller.Items;

				for (int i = 0; i < skins.Count; ++i)
				{
					SkinPartInfo skin = new SkinPartInfo( skins[i], i );
					skinsListBox.Items.Add( skin );
				}

				refreshing = false;
				skinsListBox.EndUpdate();
			}
			else
			{
				noResourceLabel.Visible = true;
				noResourceLabel.Enabled = true;
				skinsListBox.Visible = false;
				skinsListBox.Enabled = false;
			}
		}

		private bool IsValid
		{
			get { return !ReferenceEquals(controller, null) && !ReferenceEquals(controller.Items, null); }
		}

		#endregion
	}
}
