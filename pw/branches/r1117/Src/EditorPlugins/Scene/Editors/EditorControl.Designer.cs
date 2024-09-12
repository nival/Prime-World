namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
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
			if ( disposing && (components != null) )
			{
				components.Dispose();
			}
			base.Dispose( disposing );
		}

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditorControl));
      this.toolStrip = new System.Windows.Forms.ToolStrip();
      this.btnRelight = new System.Windows.Forms.ToolStripButton();
      this.btnImmediateLighting = new System.Windows.Forms.ToolStripButton();
      this.cboTerrainType = new System.Windows.Forms.ToolStripComboBox();
      this.btnNightLighting = new System.Windows.Forms.ToolStripButton();
      this.cboResolution = new System.Windows.Forms.ToolStripComboBox();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.btnLockObjects = new System.Windows.Forms.ToolStripButton();
      this.btnSplineSelection = new System.Windows.Forms.ToolStripButton();
      this.btnSnapToTerrain = new System.Windows.Forms.ToolStripButton();
      this.btnRandomRotateZ = new System.Windows.Forms.ToolStripButton();
      this.btnRandomScale = new System.Windows.Forms.ToolStripButton();
      this.txtMinScale = new System.Windows.Forms.ToolStripTextBox();
      this.txtMaxScale = new System.Windows.Forms.ToolStripTextBox();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      this.btnViewMode = new System.Windows.Forms.ToolStripButton();
      this.btnTerraFormingMode = new System.Windows.Forms.ToolStripButton();
      this.btnLayersMode = new System.Windows.Forms.ToolStripButton();
      this.btnNatureMapMode = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
      this.btnAlignTCV = new System.Windows.Forms.ToolStripButton();
      this.btnWeld = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
      this.btnFullLoad = new System.Windows.Forms.ToolStripButton();
      this.btnInlineSpawners = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
      this.btnManipulatorsMode = new System.Windows.Forms.ToolStripButton();
      this.btnGlobalLocal = new System.Windows.Forms.ToolStripButton();
      this.toolStrip.SuspendLayout();
      this.SuspendLayout();
      // 
      // toolStrip
      // 
      this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnRelight,
            this.btnImmediateLighting,
            this.btnNightLighting,
            this.cboTerrainType,
            this.cboResolution,
            this.toolStripSeparator1,
            this.btnLockObjects,
            this.btnSplineSelection,
            this.btnSnapToTerrain,
            this.btnRandomRotateZ,
            this.btnRandomScale,
            this.txtMinScale,
            this.txtMaxScale,
            this.toolStripSeparator2,
            this.btnViewMode,
            this.btnTerraFormingMode,
            this.btnLayersMode,
            this.btnNatureMapMode,
            this.toolStripSeparator3,
            this.btnAlignTCV,
            this.btnWeld,
            this.toolStripSeparator4,
            this.btnFullLoad,
            this.btnInlineSpawners,
            this.toolStripSeparator5,
            this.btnManipulatorsMode,
            this.btnGlobalLocal});
      this.toolStrip.Location = new System.Drawing.Point(0, 0);
      this.toolStrip.Name = "toolStrip";
      this.toolStrip.Size = new System.Drawing.Size(783, 25);
      this.toolStrip.TabIndex = 0;
      this.toolStrip.Text = "toolStrip";
      // 
      // btnRelight
      // 
      this.btnRelight.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnRelight.Image = global::EditorPlugins.EditorPluginResources.LightEnvironment;
      this.btnRelight.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnRelight.Name = "btnRelight";
      this.btnRelight.Size = new System.Drawing.Size(23, 22);
      this.btnRelight.Text = "Relight";
      this.btnRelight.Click += new System.EventHandler(this.OnRelightClick);
      // 
      // btnImmediateLighting
      // 
      this.btnImmediateLighting.CheckOnClick = true;
      this.btnImmediateLighting.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnImmediateLighting.Image = global::EditorPlugins.EditorPluginResources.ImmidiateLightning;
      this.btnImmediateLighting.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnImmediateLighting.Name = "btnImmediateLighting";
      this.btnImmediateLighting.Size = new System.Drawing.Size(23, 22);
      this.btnImmediateLighting.Text = "Immediate lighting";
      this.btnImmediateLighting.CheckedChanged += new System.EventHandler(this.OnImmediateLightingCheckedChanged);
      // 
      // cboTerrainType
      // 
      this.cboTerrainType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cboTerrainType.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.cboTerrainType.Name = "cboTerrainType";
      this.cboTerrainType.Size = new System.Drawing.Size(90, 25);
      this.cboTerrainType.SelectedIndexChanged += new System.EventHandler(this.OnTerrainTypeChanged);
      // 
      // btnNightLighting
      // 
      this.btnNightLighting.CheckOnClick = true;
      this.btnNightLighting.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnNightLighting.Image = global::EditorPlugins.EditorPluginResources.NightLightEnvironment;
      this.btnNightLighting.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnNightLighting.Name = "btnNightLighting";
      this.btnNightLighting.Size = new System.Drawing.Size(23, 22);
      this.btnNightLighting.Text = "Toggle night lighting";
      this.btnNightLighting.CheckedChanged += new System.EventHandler(this.OnNightLightingCheckedChanged);
      // 
      // cboResolution
      // 
      this.cboResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cboResolution.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.cboResolution.Name = "cboResolution";
      this.cboResolution.Size = new System.Drawing.Size(80, 25);
      this.cboResolution.SelectedIndexChanged += new System.EventHandler(this.OnResolutionSelected);
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
      // 
      // btnLockObjects
      // 
      this.btnLockObjects.CheckOnClick = true;
      this.btnLockObjects.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnLockObjects.Image = global::EditorPlugins.EditorPluginResources.LockObjects;
      this.btnLockObjects.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnLockObjects.Name = "btnLockObjects";
      this.btnLockObjects.Size = new System.Drawing.Size(23, 22);
      this.btnLockObjects.Text = "Lock Objects";
      this.btnLockObjects.Click += new System.EventHandler(this.OnLockObjectsClick);
      // 
      // btnSplineSelection
      // 
      this.btnSplineSelection.CheckOnClick = true;
      this.btnSplineSelection.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnSplineSelection.Image = global::EditorPlugins.EditorPluginResources.Spline;
      this.btnSplineSelection.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnSplineSelection.Name = "btnSplineSelection";
      this.btnSplineSelection.Size = new System.Drawing.Size(23, 22);
      this.btnSplineSelection.Text = "Spline Selection";
      this.btnSplineSelection.Click += new System.EventHandler(this.OnSplineSelectionClick);
      // 
      // btnSnapToTerrain
      // 
      this.btnSnapToTerrain.CheckOnClick = true;
      this.btnSnapToTerrain.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnSnapToTerrain.Image = global::EditorPlugins.EditorPluginResources.Snap;
      this.btnSnapToTerrain.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnSnapToTerrain.Name = "btnSnapToTerrain";
      this.btnSnapToTerrain.Size = new System.Drawing.Size(23, 22);
      this.btnSnapToTerrain.Text = "Snap Objects to Terrain";
      this.btnSnapToTerrain.CheckStateChanged += new System.EventHandler(this.OnSnapToTerrainCheckedChanged);
      // 
      // btnRandomRotateZ
      // 
      this.btnRandomRotateZ.CheckOnClick = true;
      this.btnRandomRotateZ.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnRandomRotateZ.Image = global::EditorPlugins.EditorPluginResources.Z_Rotation;
      this.btnRandomRotateZ.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnRandomRotateZ.Name = "btnRandomRotateZ";
      this.btnRandomRotateZ.Size = new System.Drawing.Size(23, 22);
      this.btnRandomRotateZ.Text = "Random Z Rotate";
      this.btnRandomRotateZ.CheckedChanged += new System.EventHandler(this.OnRotateZCheckedChanged);
      // 
      // btnRandomScale
      // 
      this.btnRandomScale.CheckOnClick = true;
      this.btnRandomScale.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnRandomScale.Image = global::EditorPlugins.EditorPluginResources.Z_Scale;
      this.btnRandomScale.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnRandomScale.Name = "btnRandomScale";
      this.btnRandomScale.Size = new System.Drawing.Size(23, 22);
      this.btnRandomScale.Text = "Random Scale";
      this.btnRandomScale.CheckedChanged += new System.EventHandler(this.OnRandomScaleCheckedChanged);
      // 
      // txtMinScale
      // 
      this.txtMinScale.AutoSize = false;
      this.txtMinScale.Enabled = false;
      this.txtMinScale.Name = "txtMinScale";
      this.txtMinScale.Size = new System.Drawing.Size(25, 21);
      this.txtMinScale.Leave += new System.EventHandler(this.OnMinScaleLeave);
      // 
      // txtMaxScale
      // 
      this.txtMaxScale.AutoSize = false;
      this.txtMaxScale.Enabled = false;
      this.txtMaxScale.Name = "txtMaxScale";
      this.txtMaxScale.Size = new System.Drawing.Size(25, 21);
      this.txtMaxScale.Leave += new System.EventHandler(this.OnMaxScaleLeave);
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
      // 
      // btnViewMode
      // 
      this.btnViewMode.Checked = true;
      this.btnViewMode.CheckState = System.Windows.Forms.CheckState.Checked;
      this.btnViewMode.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnViewMode.Image = global::EditorPlugins.EditorPluginResources.View;
      this.btnViewMode.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnViewMode.Name = "btnViewMode";
      this.btnViewMode.Size = new System.Drawing.Size(23, 22);
      this.btnViewMode.Text = "View";
      // 
      // btnTerraFormingMode
      // 
      this.btnTerraFormingMode.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnTerraFormingMode.Image = global::EditorPlugins.EditorPluginResources.TerraForming;
      this.btnTerraFormingMode.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnTerraFormingMode.Name = "btnTerraFormingMode";
      this.btnTerraFormingMode.Size = new System.Drawing.Size(23, 22);
      this.btnTerraFormingMode.Text = "Terraforming";
      // 
      // btnLayersMode
      // 
      this.btnLayersMode.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnLayersMode.Image = global::EditorPlugins.EditorPluginResources.Layers;
      this.btnLayersMode.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnLayersMode.Name = "btnLayersMode";
      this.btnLayersMode.Size = new System.Drawing.Size(23, 22);
      this.btnLayersMode.Text = "Layers";
      // 
      // btnNatureMapMode
      // 
      this.btnNatureMapMode.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnNatureMapMode.Image = global::EditorPlugins.EditorPluginResources.ShowTiles;
      this.btnNatureMapMode.ImageTransparentColor = System.Drawing.Color.Silver;
      this.btnNatureMapMode.Name = "btnNatureMapMode";
      this.btnNatureMapMode.Size = new System.Drawing.Size(23, 22);
      this.btnNatureMapMode.Text = "Nature map";
      // 
      // toolStripSeparator3
      // 
      this.toolStripSeparator3.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
      // 
      // btnAlignTCV
      // 
      this.btnAlignTCV.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnAlignTCV.Image = global::EditorPlugins.EditorPluginResources.Align_TCV;
      this.btnAlignTCV.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnAlignTCV.Name = "btnAlignTCV";
      this.btnAlignTCV.Size = new System.Drawing.Size(23, 22);
      this.btnAlignTCV.Text = "Align TCV";
      this.btnAlignTCV.Click += new System.EventHandler(this.OnAlignTcvClick);
      // 
      // btnWeld
      // 
      this.btnWeld.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnWeld.Image = global::EditorPlugins.EditorPluginResources.Weld;
      this.btnWeld.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnWeld.Name = "btnWeld";
      this.btnWeld.Size = new System.Drawing.Size(23, 22);
      this.btnWeld.Text = "Weld terrain vertices";
      this.btnWeld.Click += new System.EventHandler(this.OnWeldClick);
      // 
      // toolStripSeparator4
      // 
      this.toolStripSeparator4.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
      this.toolStripSeparator4.Name = "toolStripSeparator4";
      this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
      // 
      // btnFullLoad
      // 
      this.btnFullLoad.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnFullLoad.Image = global::EditorPlugins.EditorPluginResources.FullLoad;
      this.btnFullLoad.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnFullLoad.Name = "btnFullLoad";
      this.btnFullLoad.Size = new System.Drawing.Size(23, 22);
      this.btnFullLoad.Text = "Reload map with full assets";
      this.btnFullLoad.Click += new System.EventHandler(this.OnFullLoadClick);
      // 
      // btnInlineSpawners
      // 
      this.btnInlineSpawners.CheckOnClick = true;
      this.btnInlineSpawners.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnInlineSpawners.Image = global::EditorPlugins.EditorPluginResources.InlineSpawners;
      this.btnInlineSpawners.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnInlineSpawners.Name = "btnInlineSpawners";
      this.btnInlineSpawners.Size = new System.Drawing.Size(23, 22);
      this.btnInlineSpawners.Text = "Inline Spawners";
      this.btnInlineSpawners.CheckedChanged += new System.EventHandler(this.OnInlineSpawnersCheckedChanged);
      // 
      // toolStripSeparator5
      // 
      this.toolStripSeparator5.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
      this.toolStripSeparator5.Name = "toolStripSeparator5";
      this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
      // 
      // btnManipulatorsMode
      // 
      this.btnManipulatorsMode.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnManipulatorsMode.Image = global::EditorPlugins.EditorPluginResources.common_each_center;
      this.btnManipulatorsMode.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnManipulatorsMode.Name = "btnManipulatorsMode";
      this.btnManipulatorsMode.Size = new System.Drawing.Size(23, 22);
      this.btnManipulatorsMode.Text = "Common Selection Centers";
      this.btnManipulatorsMode.Click += new System.EventHandler(this.OnManipulatorsModeClick);
      // 
      // btnGlobalLocal
      // 
      this.btnGlobalLocal.Image = ((System.Drawing.Image)(resources.GetObject("btnGlobalLocal.Image")));
      this.btnGlobalLocal.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnGlobalLocal.Name = "btnGlobalLocal";
      this.btnGlobalLocal.Size = new System.Drawing.Size(53, 22);
      this.btnGlobalLocal.Text = "Global";
      this.btnGlobalLocal.Click += new System.EventHandler(this.OnLocalGlobalClick);
      // 
      // EditorControl
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add(this.toolStrip);
      this.Name = "EditorControl";
      this.Size = new System.Drawing.Size(783, 313);
      this.toolStrip.ResumeLayout(false);
      this.toolStrip.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

		}

		#endregion

    private System.Windows.Forms.ToolStrip toolStrip;
    private System.Windows.Forms.ToolStripButton btnRelight;
    private System.Windows.Forms.ToolStripButton btnImmediateLighting;
    private System.Windows.Forms.ToolStripComboBox cboTerrainType;
    private System.Windows.Forms.ToolStripComboBox cboResolution;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripButton btnLockObjects;
    private System.Windows.Forms.ToolStripButton btnSplineSelection;
    private System.Windows.Forms.ToolStripButton btnSnapToTerrain;
    private System.Windows.Forms.ToolStripButton btnRandomRotateZ;
    private System.Windows.Forms.ToolStripButton btnRandomScale;
    private System.Windows.Forms.ToolStripTextBox txtMinScale;
    private System.Windows.Forms.ToolStripTextBox txtMaxScale;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
    private System.Windows.Forms.ToolStripButton btnViewMode;
    private System.Windows.Forms.ToolStripButton btnTerraFormingMode;
    private System.Windows.Forms.ToolStripButton btnLayersMode;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
    private System.Windows.Forms.ToolStripButton btnAlignTCV;
    private System.Windows.Forms.ToolStripButton btnWeld;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
    private System.Windows.Forms.ToolStripButton btnFullLoad;
    private System.Windows.Forms.ToolStripButton btnInlineSpawners;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
    private System.Windows.Forms.ToolStripButton btnManipulatorsMode;
    private System.Windows.Forms.ToolStripButton btnGlobalLocal;
    private System.Windows.Forms.ToolStripButton btnNatureMapMode;
    private System.Windows.Forms.ToolStripButton btnNightLighting;

	}
}
