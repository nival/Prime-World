using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Panels;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainHeightTool
{
	public partial class TerrainHeightPanel : EditorPanel
	{
		public TerrainHeightPanel()
		{
			InitializeComponent();
			TabText = "Terrain Height Tool";
			Enabled = false;
		}

		protected override bool Initialize( IEditorWinApplication application )
		{
			this.upButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.affectType = TerrainAffectType.Up;
			};
			this.downButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.affectType = TerrainAffectType.Down;
			};
			this.smoothButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.affectType = TerrainAffectType.Smooth;
			};
			this.flattenButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.affectType = TerrainAffectType.Flat;
			};
			this.quadAffectButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.brushType = TerrainBrushType.Quadatic;
			};
			this.flatAffectButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.brushType = TerrainBrushType.Flat;
			};
			this.brushSizeSlider.ValueChanged += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.radius = this.brushSizeSlider.Value;
			};
			this.pressureSlider.ValueChanged += delegate( object sender, EventArgs e )
			{
				EditorControl.TerrainHeightToolState.pressure = (float)this.pressureSlider.Value / (float)this.pressureSlider.Maximum;
			};

			return true;
		}

	}
}
