using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Panels;

namespace EditorPlugins.Scene.Editors.Drawing
{
	public partial class NatureMapPanel : EditorPanel
	{
		public NatureMapPanel()
		{
			InitializeComponent();
			TabText = "Nature Map Tool";
			Enabled = false;
		}

		protected override bool Initialize( IEditorWinApplication application )
		{
      this.fromAnyButton.Click += delegate( object sender, EventArgs e )
      {
        EditorControl.NatureMapToolState.affectedFaction = null;
      };
      this.fromNeutralButton.Click += delegate( object sender, EventArgs e )
      {
        EditorControl.NatureMapToolState.affectedFaction = DBTypes.EFaction.Neutral;
      };
      this.fromFreezeButton.Click += delegate( object sender, EventArgs e )
      {
        EditorControl.NatureMapToolState.affectedFaction = DBTypes.EFaction.Freeze;
      };
      this.fromBurnButton.Click += delegate( object sender, EventArgs e )
      {
        EditorControl.NatureMapToolState.affectedFaction = DBTypes.EFaction.Burn;
      };

			this.toNeutralButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.NatureMapToolState.newFaction = DBTypes.EFaction.Neutral;
			};
			this.toFreezeButton.Click += delegate( object sender, EventArgs e )
			{
        EditorControl.NatureMapToolState.newFaction = DBTypes.EFaction.Freeze;
			};
			this.toBurnButton.Click += delegate( object sender, EventArgs e )
			{
				EditorControl.NatureMapToolState.newFaction = DBTypes.EFaction.Burn;
			};
			this.brushSizeSlider.ValueChanged += delegate( object sender, EventArgs e )
			{
        EditorControl.NatureMapToolState.radius = Math.Max( this.brushSizeSlider.Value, 1 );
        this.brushSizeUpDown.Value = (decimal)EditorControl.NatureMapToolState.radius;
			};
      this.brushSizeUpDown.ValueChanged += delegate(object sender, EventArgs e)
      {
        EditorControl.NatureMapToolState.radius = (float)this.brushSizeUpDown.Value;
        this.brushSizeSlider.Value = (int)EditorControl.NatureMapToolState.radius;
      };

			return true;
		}

    private void radioButton4_CheckedChanged( object sender, EventArgs e )
    {

    }

    private void FactionGroupBox_Enter( object sender, EventArgs e )
    {

    }

	}
}
