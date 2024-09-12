using System;
using System.Drawing;
using System.Windows.Forms;

namespace EditorPlugins.ObjectLayers
{
  class ColouredCheckedListBox : CheckedListBox
  {
    protected override void OnDrawItem( DrawItemEventArgs e )
    {
      bool selectable = true;
      if ( this.Items.Count > 0 )
      {
        ObjectLayersPreset preset = this.Items[e.Index] as ObjectLayersPreset;
        if( preset != null )
        {
          selectable = preset.Selectable;
        }
      }

      DrawItemEventArgs e2 =
            new DrawItemEventArgs
          (
              e.Graphics,
              e.Font,
              new Rectangle( e.Bounds.Location, e.Bounds.Size ),
              e.Index,
              e.State,
              selectable ? SystemColors.WindowText : Color.Red,
              e.BackColor
          );

      base.OnDrawItem( e2 );
    }
  }

  partial class ObjectLayersPanel
  {
    private ColouredCheckedListBox lstPresets;

    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose( bool disposing )
    {
      if ( disposing && ( components != null ) )
      {
        components.Dispose();
      }
      base.Dispose( disposing );
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( ObjectLayersPanel ) );
      this.chkCheckAll = new System.Windows.Forms.CheckBox();
      this.btnNewPreset = new System.Windows.Forms.ToolStripButton();
      this.btnDeletePreset = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.btnShowInPE = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      this.btnUp = new System.Windows.Forms.ToolStripButton();
      this.btnDown = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
      this.chkEffects = new System.Windows.Forms.ToolStripButton();
      this.chkTiles = new System.Windows.Forms.ToolStripButton();
      this.chkAttackSpace = new System.Windows.Forms.ToolStripButton();
      this.chkRenderSH = new System.Windows.Forms.ToolStripButton();
      this.Selection = new System.Windows.Forms.ToolStripButton();
      this.SelectElements = new System.Windows.Forms.ToolStripButton();
      this.toolStrip1 = new System.Windows.Forms.ToolStrip();
      this.SelectionAll = new System.Windows.Forms.ToolStripButton();
      this.lstPresets = new EditorPlugins.ObjectLayers.ColouredCheckedListBox();
      this.toolStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // chkCheckAll
      // 
      this.chkCheckAll.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.chkCheckAll.AutoSize = true;
      this.chkCheckAll.Location = new System.Drawing.Point( 10, 338 );
      this.chkCheckAll.Name = "chkCheckAll";
      this.chkCheckAll.Size = new System.Drawing.Size( 70, 17 );
      this.chkCheckAll.TabIndex = 6;
      this.chkCheckAll.Text = "Check all";
      this.chkCheckAll.UseVisualStyleBackColor = true;
      this.chkCheckAll.CheckedChanged += new System.EventHandler( this.OnCheckAllCheckedChanged );
      // 
      // btnNewPreset
      // 
      this.btnNewPreset.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnNewPreset.Image = global::EditorPlugins.EditorPluginResources.add_create;
      this.btnNewPreset.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnNewPreset.Name = "btnNewPreset";
      this.btnNewPreset.Size = new System.Drawing.Size( 23, 22 );
      this.btnNewPreset.Text = "Add New Preset";
      this.btnNewPreset.Click += new System.EventHandler( this.OnNewPresetClick );
      // 
      // btnDeletePreset
      // 
      this.btnDeletePreset.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnDeletePreset.Image = global::EditorPlugins.EditorPluginResources.delete_cross;
      this.btnDeletePreset.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnDeletePreset.Name = "btnDeletePreset";
      this.btnDeletePreset.Size = new System.Drawing.Size( 23, 22 );
      this.btnDeletePreset.Text = "Delete Preset";
      this.btnDeletePreset.Click += new System.EventHandler( this.OnDeletePresetClick );
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
      // 
      // btnShowInPE
      // 
      this.btnShowInPE.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnShowInPE.Image = global::EditorPlugins.EditorPluginResources.settings;
      this.btnShowInPE.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnShowInPE.Name = "btnShowInPE";
      this.btnShowInPE.Size = new System.Drawing.Size( 23, 22 );
      this.btnShowInPE.Text = "Show Preset in Properties Editor";
      this.btnShowInPE.Click += new System.EventHandler( this.OnShowInPEClick );
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size( 6, 25 );
      // 
      // btnUp
      // 
      this.btnUp.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnUp.Image = global::EditorPlugins.EditorPluginResources.move_up;
      this.btnUp.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnUp.Name = "btnUp";
      this.btnUp.Size = new System.Drawing.Size( 23, 22 );
      this.btnUp.Text = "Move Up";
      this.btnUp.Click += new System.EventHandler( this.OnUpClick );
      // 
      // btnDown
      // 
      this.btnDown.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnDown.Image = global::EditorPlugins.EditorPluginResources.move_down;
      this.btnDown.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnDown.Name = "btnDown";
      this.btnDown.Size = new System.Drawing.Size( 23, 22 );
      this.btnDown.Text = "Move Down";
      this.btnDown.Click += new System.EventHandler( this.OnDownClick );
      // 
      // toolStripSeparator3
      // 
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new System.Drawing.Size( 6, 25 );
      // 
      // chkEffects
      // 
      this.chkEffects.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.chkEffects.Enabled = false;
      this.chkEffects.Image = global::EditorPlugins.EditorPluginResources.fire;
      this.chkEffects.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.chkEffects.Name = "chkEffects";
      this.chkEffects.Size = new System.Drawing.Size( 23, 22 );
      this.chkEffects.Text = "Effects";
      this.chkEffects.Click += new System.EventHandler( this.OnSceneButtonClick );
      // 
      // chkTiles
      // 
      this.chkTiles.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.chkTiles.Enabled = false;
      this.chkTiles.Image = global::EditorPlugins.EditorPluginResources.tiles;
      this.chkTiles.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.chkTiles.Name = "chkTiles";
      this.chkTiles.Size = new System.Drawing.Size( 23, 22 );
      this.chkTiles.Text = "Tiles";
      this.chkTiles.Click += new System.EventHandler( this.OnSceneButtonClick );
      // 
      // chkAttackSpace
      // 
      this.chkAttackSpace.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.chkAttackSpace.Enabled = false;
      this.chkAttackSpace.Image = global::EditorPlugins.EditorPluginResources.attack_space;
      this.chkAttackSpace.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.chkAttackSpace.Name = "chkAttackSpace";
      this.chkAttackSpace.Size = new System.Drawing.Size( 23, 22 );
      this.chkAttackSpace.Text = "Attack Space";
      this.chkAttackSpace.Click += new System.EventHandler( this.OnSceneButtonClick );
      // 
      // chkRenderSH
      // 
      this.chkRenderSH.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.chkRenderSH.Enabled = false;
      this.chkRenderSH.Image = global::EditorPlugins.EditorPluginResources.sh;
      this.chkRenderSH.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.chkRenderSH.Name = "chkRenderSH";
      this.chkRenderSH.Size = new System.Drawing.Size( 23, 22 );
      this.chkRenderSH.Text = "Render SH";
      this.chkRenderSH.Click += new System.EventHandler( this.OnSceneButtonClick );
      // 
      // Selection
      // 
      this.Selection.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.Selection.Image = ( (System.Drawing.Image)( resources.GetObject( "Selection.Image" ) ) );
      this.Selection.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.Selection.Name = "Selection";
      this.Selection.Size = new System.Drawing.Size( 23, 22 );
      this.Selection.Text = "toolStripButton1";
      this.Selection.ToolTipText = "Block object selection from current layer";
      this.Selection.Click += new System.EventHandler( this.OnSelection );
      // 
      // SelectElements
      // 
      this.SelectElements.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.SelectElements.Image = ( (System.Drawing.Image)( resources.GetObject( "SelectElements.Image" ) ) );
      this.SelectElements.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.SelectElements.Name = "SelectElements";
      this.SelectElements.Size = new System.Drawing.Size( 23, 22 );
      this.SelectElements.Text = "toolStripButton2";
      this.SelectElements.ToolTipText = "Select objects in current layers";
      this.SelectElements.Click += new System.EventHandler( this.OnSelectElements );
      // 
      // toolStrip1
      // 
      this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.toolStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.btnNewPreset,
            this.btnDeletePreset,
            this.toolStripSeparator1,
            this.btnShowInPE,
            this.toolStripSeparator2,
            this.btnUp,
            this.btnDown,
            this.toolStripSeparator3,
            this.chkEffects,
            this.chkTiles,
            this.chkAttackSpace,
            this.chkRenderSH,
            this.Selection,
            this.SelectionAll,
            this.SelectElements} );
      this.toolStrip1.Location = new System.Drawing.Point( 0, 0 );
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new System.Drawing.Size( 328, 25 );
      this.toolStrip1.TabIndex = 7;
      this.toolStrip1.Text = "toolStrip1";
      // 
      // SelectionAll
      // 
      this.SelectionAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.SelectionAll.Image = ( (System.Drawing.Image)( resources.GetObject( "SelectionAll.Image" ) ) );
      this.SelectionAll.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.SelectionAll.Name = "SelectionAll";
      this.SelectionAll.Size = new System.Drawing.Size( 23, 22 );
      this.SelectionAll.Text = "toolStripButton2";
      this.SelectionAll.ToolTipText = "Toggle block selection all layers";
      this.SelectionAll.Click += new System.EventHandler( this.OnSelectionAll );
      // 
      // lstPresets
      // 
      this.lstPresets.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.lstPresets.FormattingEnabled = true;
      this.lstPresets.IntegralHeight = false;
      this.lstPresets.Location = new System.Drawing.Point( 10, 28 );
      this.lstPresets.Name = "lstPresets";
      this.lstPresets.Size = new System.Drawing.Size( 306, 304 );
      this.lstPresets.TabIndex = 4;
      this.lstPresets.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler( this.OnItemCheck );
      // 
      // ObjectLayersPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 328, 367 );
      this.Controls.Add( this.toolStrip1 );
      this.Controls.Add( this.chkCheckAll );
      this.Controls.Add( this.lstPresets );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.Name = "ObjectLayersPanel";
      this.Text = "ObjectLayersPanel";
      this.toolStrip1.ResumeLayout( false );
      this.toolStrip1.PerformLayout();
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.CheckBox chkCheckAll;
    private ToolStripButton btnNewPreset;
    private ToolStripButton btnDeletePreset;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnShowInPE;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripButton btnUp;
    private ToolStripButton btnDown;
    private ToolStripSeparator toolStripSeparator3;
    private ToolStripButton chkEffects;
    private ToolStripButton chkTiles;
    private ToolStripButton chkAttackSpace;
    private ToolStripButton chkRenderSH;
    private ToolStripButton Selection;
    private ToolStripButton SelectElements;
    private ToolStrip toolStrip1;
    private ToolStripButton SelectionAll;
  }
}