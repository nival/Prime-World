using System;
using System.Windows.Forms;
using Pair = System.Collections.Generic.KeyValuePair<System.Windows.Forms.ToolStripButton, System.EventHandler>;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	public sealed partial class BrushSettingsControl : UserControl
	{
		#region Private members.

		public static int brushSize;

		private readonly LayersListBox listBox = new LayersListBox() { Dock = DockStyle.Fill };
		private ITerrainLayersBrushSettingsController controller;
    private int layerColorsValue = 0;
		
		#endregion

		#region Initialization.

		public BrushSettingsControl()
		{
			InitializeComponent();

			brushSizeTrackBar.ValueChanged += ( _1, _2 ) =>
				{
					brushSize = brushSizeTrackBar.Value * 2 + 1;
					brushSizeLabel.Text = string.Format( "Brush size ({0}):", brushSize );
				};

			EventHandler onStateChanged = ( _1, _2 ) => UpdateContollerState();

			brushSizeTrackBar.ValueChanged += onStateChanged;

			listBox.SelectedIndexChanged += onStateChanged;

			brushSizeTrackBar.Value = brushSizeTrackBar.Maximum;
			brushSizeTrackBar.Value = 0;

			tableLayoutPanel1.Controls.Add( listBox );
		}

		#endregion

		#region Internal properties.

		internal ITerrainLayersBrushSettingsController Controller
		{
			set
			{
				controller = value;

				if ( ControllerValid )
				{
					controller.LayersChanged += OnLayersChanged;
				}

				OnLayersChanged();
				UpdateContollerState();
			}
		}

		#endregion

		#region Event handlers.

		private void OnLayersChanged()
		{
			listBox.Layers = ControllerValid ? controller.Layers : null;
		}

		#endregion

		#region Private helper methods.

		private bool ControllerValid
		{
			get { return !ReferenceEquals( controller, null ); }
		}

		private void UpdateContollerState()
		{
			if ( ControllerValid )
			{
				controller.SelectedLayer = listBox.SelectedIndex;
				controller.BrushSize = brushSize;
        controller.DisplayLayerColors = layerColorsValue;
			}
		}

		#endregion

		private void layerColorsButton_CheckedChanged(object sender, EventArgs e)
		{
      layerColorsValue++;
      if ( layerColorsValue > 2 )
        layerColorsValue = 0;

      switch(layerColorsValue)
      {
      case 0:
        layerColorsButton.Text = "Normal Mode";
        layerColorsButton.ToolTipText = "Normal Mode";
        break;
      case 1:
        layerColorsButton.Text = "Debug Mode";
        layerColorsButton.ToolTipText = "Debug Mode";
        break;
      case 2:
        layerColorsButton.Text = "Debug Mode (Issues Only)";
        layerColorsButton.ToolTipText = "Debug Mode (Issues Only)";
        break;
      default:
        layerColorsButton.Text = "Normal Mode";
        layerColorsButton.ToolTipText = "Normal Mode";
        break;
      }

			UpdateContollerState();
		}
	}
}
