using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.Panels;
using libdb.DB;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	public sealed class TerrainLayersEditorPanel : EditorPanel
	{
		private readonly BrushSettingsControl brushControl = new BrushSettingsControl() { Dock = DockStyle.Fill };

		public TerrainLayersEditorPanel()
		{
			TabText = "Terrain Layers";
			Controls.Add( brushControl );
			Enabled = false;
		}

		protected override bool Initialize( IEditorWinApplication application )
		{
			return true;
		}

		internal ITerrainLayersBrushSettingsController Controller
		{
			set { brushControl.Controller = value; }
		}
	}
}
