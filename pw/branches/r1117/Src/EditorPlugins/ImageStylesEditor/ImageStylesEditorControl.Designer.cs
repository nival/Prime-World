namespace EditorPlugins.ImageStylesEditor
{
	
	partial class ImageStylesEditorControl
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ImageStylesEditorControl));
      this.toolBox = new System.Windows.Forms.ToolStrip();
      this.ToolZoomCombo = new System.Windows.Forms.ToolStripComboBox();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
      this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
      this.ToolShapeAlphaThreshold = new System.Windows.Forms.ToolStripComboBox();
      this.toolZoom = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.splitContainer1 = new System.Windows.Forms.SplitContainer();
      this.imageStyleView = new EditorPlugins.ImageStylesEditor.ImageStyleView();
      this.Tiling = new System.Windows.Forms.GroupBox();
      this.SampleHeight = new System.Windows.Forms.TextBox();
      this.label6 = new System.Windows.Forms.Label();
      this.SampleWidth = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.groupBox2 = new System.Windows.Forms.GroupBox();
      this.label9 = new System.Windows.Forms.Label();
      this.label8 = new System.Windows.Forms.Label();
      this.label7 = new System.Windows.Forms.Label();
      this.TileBottomMargin = new System.Windows.Forms.TextBox();
      this.label5 = new System.Windows.Forms.Label();
      this.TileTopMargin = new System.Windows.Forms.TextBox();
      this.label4 = new System.Windows.Forms.Label();
      this.TileLeftMargin = new System.Windows.Forms.TextBox();
      this.TileRightMargin = new System.Windows.Forms.TextBox();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.AutosizeCheck = new System.Windows.Forms.CheckBox();
      this.SizeFromTexture = new System.Windows.Forms.Button();
      this.TextureX = new System.Windows.Forms.TextBox();
      this.TextureHeight = new System.Windows.Forms.TextBox();
      this.label3 = new System.Windows.Forms.Label();
      this.TextureY = new System.Windows.Forms.TextBox();
      this.TextureWidth = new System.Windows.Forms.TextBox();
      this.label2 = new System.Windows.Forms.Label();
      this.toolStripComboBox1 = new System.Windows.Forms.ToolStripComboBox();
      this.ToolHLeft = new System.Windows.Forms.ToolStripButton();
      this.ToolHStretch = new System.Windows.Forms.ToolStripButton();
      this.ToolHCenter = new System.Windows.Forms.ToolStripButton();
      this.ToolHTile = new System.Windows.Forms.ToolStripButton();
      this.ToolHStretchedTile = new System.Windows.Forms.ToolStripButton();
      this.ToolVTop = new System.Windows.Forms.ToolStripButton();
      this.ToolVStretch = new System.Windows.Forms.ToolStripButton();
      this.ToolVCenter = new System.Windows.Forms.ToolStripButton();
      this.ToolVTile = new System.Windows.Forms.ToolStripButton();
      this.ToolVStretchedTile = new System.Windows.Forms.ToolStripButton();
      this.ToolShowShape = new System.Windows.Forms.ToolStripButton();
      this.toolBox.SuspendLayout();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.Tiling.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // toolBox
      // 
      this.toolBox.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolZoomCombo,
            this.toolStripSeparator2,
            this.ToolHLeft,
            this.ToolHStretch,
            this.ToolHCenter,
            this.ToolHTile,
            this.ToolHStretchedTile,
            this.toolStripSeparator3,
            this.ToolVTop,
            this.ToolVStretch,
            this.ToolVCenter,
            this.ToolVTile,
            this.ToolVStretchedTile,
            this.toolStripSeparator4,
            this.ToolShowShape,
            this.ToolShapeAlphaThreshold});
      this.toolBox.Location = new System.Drawing.Point(0, 0);
      this.toolBox.Name = "toolBox";
      this.toolBox.Size = new System.Drawing.Size(926, 25);
      this.toolBox.TabIndex = 0;
      this.toolBox.Text = "toolStrip1";
      // 
      // ToolZoomCombo
      // 
      this.ToolZoomCombo.FlatStyle = System.Windows.Forms.FlatStyle.Standard;
      this.ToolZoomCombo.Items.AddRange(new object[] {
            "Fit In Window",
            "25%",
            "50%",
            "100%",
            "200%",
            "400%"});
      this.ToolZoomCombo.Name = "ToolZoomCombo";
      this.ToolZoomCombo.Size = new System.Drawing.Size(121, 25);
      this.ToolZoomCombo.ToolTipText = "Zoom";
      this.ToolZoomCombo.SelectedIndexChanged += new System.EventHandler(this.toolZoomCombo_SelectedIndexChanged);
      this.ToolZoomCombo.KeyUp += new System.Windows.Forms.KeyEventHandler(this.toolZoomCombo_KeyUp);
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
      // 
      // toolStripSeparator3
      // 
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
      // 
      // toolStripSeparator4
      // 
      this.toolStripSeparator4.Name = "toolStripSeparator4";
      this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
      // 
      // ToolShapeAlphaThreshold
      // 
      this.ToolShapeAlphaThreshold.FlatStyle = System.Windows.Forms.FlatStyle.Standard;
      this.ToolShapeAlphaThreshold.Items.AddRange(new object[] {
            "0%",
            "10%",
            "20%",
            "30%",
            "40%",
            "50%",
            "60%",
            "70%",
            "80%",
            "90%",
            "100%"});
      this.ToolShapeAlphaThreshold.MaxDropDownItems = 11;
      this.ToolShapeAlphaThreshold.Name = "ToolShapeAlphaThreshold";
      this.ToolShapeAlphaThreshold.Size = new System.Drawing.Size(121, 25);
      this.ToolShapeAlphaThreshold.ToolTipText = "Shape Alpha Threshold";
      this.ToolShapeAlphaThreshold.SelectedIndexChanged += new System.EventHandler(this.toolShapeAlphaThreshold_SelectedIndexChanged);
      this.ToolShapeAlphaThreshold.KeyUp += new System.Windows.Forms.KeyEventHandler(this.toolShapeAlphaThreshold_KeyUp);
      // 
      // toolZoom
      // 
      this.toolZoom.Name = "toolZoom";
      this.toolZoom.Size = new System.Drawing.Size(23, 23);
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
      // 
      // splitContainer1
      // 
      this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.splitContainer1.Location = new System.Drawing.Point(0, 25);
      this.splitContainer1.Name = "splitContainer1";
      // 
      // splitContainer1.Panel1
      // 
      this.splitContainer1.Panel1.AccessibleName = "leftPanel";
      this.splitContainer1.Panel1.AutoScroll = true;
      this.splitContainer1.Panel1.Controls.Add(this.imageStyleView);
      // 
      // splitContainer1.Panel2
      // 
      this.splitContainer1.Panel2.Controls.Add(this.Tiling);
      this.splitContainer1.Panel2.Controls.Add(this.groupBox2);
      this.splitContainer1.Panel2.Controls.Add(this.groupBox1);
      this.splitContainer1.Size = new System.Drawing.Size(926, 347);
      this.splitContainer1.SplitterDistance = 617;
      this.splitContainer1.TabIndex = 1;
      // 
      // imageStyleView
      // 
      this.imageStyleView.AutoScroll = true;
      this.imageStyleView.Dock = System.Windows.Forms.DockStyle.Fill;
      this.imageStyleView.Location = new System.Drawing.Point(0, 0);
      this.imageStyleView.Margin = new System.Windows.Forms.Padding(0);
      this.imageStyleView.Name = "imageStyleView";
      this.imageStyleView.Size = new System.Drawing.Size(617, 347);
      this.imageStyleView.TabIndex = 0;
      this.imageStyleView.TabStop = false;
      // 
      // Tiling
      // 
      this.Tiling.Controls.Add(this.SampleHeight);
      this.Tiling.Controls.Add(this.label6);
      this.Tiling.Controls.Add(this.SampleWidth);
      this.Tiling.Controls.Add(this.label1);
      this.Tiling.Dock = System.Windows.Forms.DockStyle.Top;
      this.Tiling.Location = new System.Drawing.Point(0, 237);
      this.Tiling.Name = "Tiling";
      this.Tiling.Size = new System.Drawing.Size(305, 75);
      this.Tiling.TabIndex = 14;
      this.Tiling.TabStop = false;
      this.Tiling.Text = "Sample parameters";
      // 
      // SampleHeight
      // 
      this.SampleHeight.Location = new System.Drawing.Point(82, 45);
      this.SampleHeight.Name = "SampleHeight";
      this.SampleHeight.Size = new System.Drawing.Size(76, 20);
      this.SampleHeight.TabIndex = 21;
      this.SampleHeight.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.SampleHeight.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(11, 48);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(41, 13);
      this.label6.TabIndex = 20;
      this.label6.Text = "Height:";
      // 
      // SampleWidth
      // 
      this.SampleWidth.Location = new System.Drawing.Point(82, 19);
      this.SampleWidth.Name = "SampleWidth";
      this.SampleWidth.Size = new System.Drawing.Size(76, 20);
      this.SampleWidth.TabIndex = 19;
      this.SampleWidth.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.SampleWidth.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(11, 22);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(38, 13);
      this.label1.TabIndex = 18;
      this.label1.Text = "Width:";
      // 
      // groupBox2
      // 
      this.groupBox2.Controls.Add(this.label9);
      this.groupBox2.Controls.Add(this.label8);
      this.groupBox2.Controls.Add(this.label7);
      this.groupBox2.Controls.Add(this.TileBottomMargin);
      this.groupBox2.Controls.Add(this.label5);
      this.groupBox2.Controls.Add(this.TileTopMargin);
      this.groupBox2.Controls.Add(this.label4);
      this.groupBox2.Controls.Add(this.TileLeftMargin);
      this.groupBox2.Controls.Add(this.TileRightMargin);
      this.groupBox2.Dock = System.Windows.Forms.DockStyle.Top;
      this.groupBox2.Location = new System.Drawing.Point(0, 122);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new System.Drawing.Size(305, 115);
      this.groupBox2.TabIndex = 13;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Tiling";
      // 
      // label9
      // 
      this.label9.AutoSize = true;
      this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.label9.Location = new System.Drawing.Point(1, 94);
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size(299, 13);
      this.label9.TabIndex = 26;
      this.label9.Text = "Tip: To move tile margins with mouse, press <Shift>";
      this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // label8
      // 
      this.label8.AutoSize = true;
      this.label8.Location = new System.Drawing.Point(118, 47);
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size(70, 13);
      this.label8.TabIndex = 25;
      this.label8.Text = "Right Margin:";
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.Location = new System.Drawing.Point(50, 68);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(78, 13);
      this.label7.TabIndex = 24;
      this.label7.Text = "Bottom Margin:";
      // 
      // TileBottomMargin
      // 
      this.TileBottomMargin.Location = new System.Drawing.Point(130, 66);
      this.TileBottomMargin.Name = "TileBottomMargin";
      this.TileBottomMargin.Size = new System.Drawing.Size(35, 20);
      this.TileBottomMargin.TabIndex = 19;
      this.TileBottomMargin.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TileBottomMargin.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(6, 47);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(63, 13);
      this.label5.TabIndex = 23;
      this.label5.Text = "Left Margin:";
      // 
      // TileTopMargin
      // 
      this.TileTopMargin.Location = new System.Drawing.Point(130, 21);
      this.TileTopMargin.Name = "TileTopMargin";
      this.TileTopMargin.Size = new System.Drawing.Size(35, 20);
      this.TileTopMargin.TabIndex = 18;
      this.TileTopMargin.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TileTopMargin.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(51, 25);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(64, 13);
      this.label4.TabIndex = 22;
      this.label4.Text = "Top Margin:";
      // 
      // TileLeftMargin
      // 
      this.TileLeftMargin.Location = new System.Drawing.Point(72, 43);
      this.TileLeftMargin.Name = "TileLeftMargin";
      this.TileLeftMargin.Size = new System.Drawing.Size(35, 20);
      this.TileLeftMargin.TabIndex = 20;
      this.TileLeftMargin.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TileLeftMargin.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // TileRightMargin
      // 
      this.TileRightMargin.Location = new System.Drawing.Point(189, 43);
      this.TileRightMargin.Name = "TileRightMargin";
      this.TileRightMargin.Size = new System.Drawing.Size(35, 20);
      this.TileRightMargin.TabIndex = 21;
      this.TileRightMargin.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TileRightMargin.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.AutosizeCheck);
      this.groupBox1.Controls.Add(this.SizeFromTexture);
      this.groupBox1.Controls.Add(this.TextureX);
      this.groupBox1.Controls.Add(this.TextureHeight);
      this.groupBox1.Controls.Add(this.label3);
      this.groupBox1.Controls.Add(this.TextureY);
      this.groupBox1.Controls.Add(this.TextureWidth);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
      this.groupBox1.Location = new System.Drawing.Point(0, 0);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(305, 122);
      this.groupBox1.TabIndex = 12;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Tiling parameters";
      // 
      // AutosizeCheck
      // 
      this.AutosizeCheck.AutoSize = true;
      this.AutosizeCheck.Location = new System.Drawing.Point(20, 98);
      this.AutosizeCheck.Name = "AutosizeCheck";
      this.AutosizeCheck.Size = new System.Drawing.Size(66, 17);
      this.AutosizeCheck.TabIndex = 13;
      this.AutosizeCheck.Text = "Autosize";
      this.AutosizeCheck.UseVisualStyleBackColor = true;
      this.AutosizeCheck.CheckedChanged += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // SizeFromTexture
      // 
      this.SizeFromTexture.Location = new System.Drawing.Point(18, 71);
      this.SizeFromTexture.Name = "SizeFromTexture";
      this.SizeFromTexture.Size = new System.Drawing.Size(147, 21);
      this.SizeFromTexture.TabIndex = 12;
      this.SizeFromTexture.Text = "Take sizes from texture";
      this.SizeFromTexture.UseVisualStyleBackColor = true;
      this.SizeFromTexture.Click += new System.EventHandler(this.SizeFromTexture_Click);
      // 
      // TextureX
      // 
      this.TextureX.Location = new System.Drawing.Point(89, 19);
      this.TextureX.Name = "TextureX";
      this.TextureX.Size = new System.Drawing.Size(35, 20);
      this.TextureX.TabIndex = 0;
      this.TextureX.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TextureX.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // TextureHeight
      // 
      this.TextureHeight.Location = new System.Drawing.Point(130, 45);
      this.TextureHeight.Name = "TextureHeight";
      this.TextureHeight.Size = new System.Drawing.Size(35, 20);
      this.TextureHeight.TabIndex = 3;
      this.TextureHeight.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TextureHeight.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(15, 45);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(67, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "Texture size:";
      // 
      // TextureY
      // 
      this.TextureY.Location = new System.Drawing.Point(130, 19);
      this.TextureY.Name = "TextureY";
      this.TextureY.Size = new System.Drawing.Size(35, 20);
      this.TextureY.TabIndex = 1;
      this.TextureY.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TextureY.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // TextureWidth
      // 
      this.TextureWidth.Location = new System.Drawing.Point(89, 45);
      this.TextureWidth.Name = "TextureWidth";
      this.TextureWidth.Size = new System.Drawing.Size(35, 20);
      this.TextureWidth.TabIndex = 2;
      this.TextureWidth.Leave += new System.EventHandler(this.UpdateDataOnLeave);
      this.TextureWidth.KeyUp += new System.Windows.Forms.KeyEventHandler(this.UpdateDataOnKeyUp);
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(15, 19);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(68, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Texture shift:";
      // 
      // toolStripComboBox1
      // 
      this.toolStripComboBox1.Name = "toolStripComboBox1";
      this.toolStripComboBox1.Size = new System.Drawing.Size(121, 21);
      // 
      // ToolHLeft
      // 
      this.ToolHLeft.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolHLeft.Image = global::EditorPlugins.LayoutEditor.Resource.HLeft;
      this.ToolHLeft.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolHLeft.Name = "ToolHLeft";
      this.ToolHLeft.Size = new System.Drawing.Size(23, 22);
      this.ToolHLeft.Text = "Align Left";
      this.ToolHLeft.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolHStretch
      // 
      this.ToolHStretch.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolHStretch.Image = global::EditorPlugins.LayoutEditor.Resource.HStretch;
      this.ToolHStretch.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolHStretch.Name = "ToolHStretch";
      this.ToolHStretch.Size = new System.Drawing.Size(23, 22);
      this.ToolHStretch.Text = "Horizobtal Stretch";
      this.ToolHStretch.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolHCenter
      // 
      this.ToolHCenter.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolHCenter.Image = global::EditorPlugins.LayoutEditor.Resource.HRight;
      this.ToolHCenter.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolHCenter.Name = "ToolHCenter";
      this.ToolHCenter.Size = new System.Drawing.Size(23, 22);
      this.ToolHCenter.Text = "Align Horizontal Center";
      this.ToolHCenter.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolHTile
      // 
      this.ToolHTile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolHTile.Image = global::EditorPlugins.LayoutEditor.Resource.HTile;
      this.ToolHTile.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolHTile.Name = "ToolHTile";
      this.ToolHTile.Size = new System.Drawing.Size(23, 22);
      this.ToolHTile.Text = "Horizontal Tile";
      this.ToolHTile.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // toolHStretchedTile
      // 
      this.ToolHStretchedTile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolHStretchedTile.Image = ((System.Drawing.Image)(resources.GetObject("toolHStretchedTile.Image")));
      this.ToolHStretchedTile.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolHStretchedTile.Name = "toolHStretchedTile";
      this.ToolHStretchedTile.Size = new System.Drawing.Size(23, 22);
      this.ToolHStretchedTile.Text = "Horizontal Stretched Tile";
      this.ToolHStretchedTile.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolVTop
      // 
      this.ToolVTop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolVTop.Image = global::EditorPlugins.LayoutEditor.Resource.VTop;
      this.ToolVTop.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolVTop.Name = "ToolVTop";
      this.ToolVTop.Size = new System.Drawing.Size(23, 22);
      this.ToolVTop.Text = "Align Up";
      this.ToolVTop.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolVStretch
      // 
      this.ToolVStretch.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolVStretch.Image = global::EditorPlugins.LayoutEditor.Resource.VStretch;
      this.ToolVStretch.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolVStretch.Name = "ToolVStretch";
      this.ToolVStretch.Size = new System.Drawing.Size(23, 22);
      this.ToolVStretch.Text = "Vertical Stretch";
      this.ToolVStretch.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolVCenter
      // 
      this.ToolVCenter.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolVCenter.Image = global::EditorPlugins.LayoutEditor.Resource.VBottom;
      this.ToolVCenter.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolVCenter.Name = "ToolVCenter";
      this.ToolVCenter.Size = new System.Drawing.Size(23, 22);
      this.ToolVCenter.Text = "Align Verical Center";
      this.ToolVCenter.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolVTile
      // 
      this.ToolVTile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolVTile.Image = global::EditorPlugins.LayoutEditor.Resource.VTile;
      this.ToolVTile.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolVTile.Name = "ToolVTile";
      this.ToolVTile.Size = new System.Drawing.Size(23, 22);
      this.ToolVTile.Text = "Vertical Tile";
      this.ToolVTile.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // toolVStretchedTile
      // 
      this.ToolVStretchedTile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolVStretchedTile.Image = ((System.Drawing.Image)(resources.GetObject("toolVStretchedTile.Image")));
      this.ToolVStretchedTile.ImageTransparentColor = System.Drawing.Color.Transparent;
      this.ToolVStretchedTile.Name = "toolVStretchedTile";
      this.ToolVStretchedTile.Size = new System.Drawing.Size(23, 22);
      this.ToolVStretchedTile.Text = "Vertical Stretched Tile";
      this.ToolVStretchedTile.Click += new System.EventHandler(this.UpdateDataOnLeave);
      // 
      // ToolShowShape
      // 
      this.ToolShowShape.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ToolShowShape.Image = global::EditorPlugins.EditorPluginResources.Pause;
      this.ToolShowShape.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.ToolShowShape.Name = "ToolShowShape";
      this.ToolShowShape.Size = new System.Drawing.Size(23, 22);
      this.ToolShowShape.Text = "Show Shape";
      this.ToolShowShape.Click += new System.EventHandler(this.toolShowShape_Click);
      // 
      // ImageStylesEditorControl
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add(this.splitContainer1);
      this.Controls.Add(this.toolBox);
      this.Name = "ImageStylesEditorControl";
      this.Size = new System.Drawing.Size(926, 372);
      this.toolBox.ResumeLayout(false);
      this.toolBox.PerformLayout();
      this.splitContainer1.Panel1.ResumeLayout(false);
      this.splitContainer1.Panel2.ResumeLayout(false);
      this.splitContainer1.ResumeLayout(false);
      this.Tiling.ResumeLayout(false);
      this.Tiling.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ToolStrip toolBox;
		private System.Windows.Forms.ToolStripButton toolZoom;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripButton ToolHLeft;
		private System.Windows.Forms.ToolStripButton ToolHStretch;
		private System.Windows.Forms.ToolStripButton ToolHTile;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripButton ToolVTop;
		private System.Windows.Forms.ToolStripButton ToolVStretch;
		private System.Windows.Forms.ToolStripButton ToolVCenter;
		private System.Windows.Forms.ToolStripButton ToolVTile;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
    private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.ToolStripButton ToolHCenter;
    private EditorPlugins.ImageStylesEditor.ImageStyleView imageStyleView;
		private System.Windows.Forms.ToolStripComboBox ToolShapeAlphaThreshold;
		private System.Windows.Forms.ToolStripButton ToolShowShape;
		private System.Windows.Forms.ToolStripComboBox toolStripComboBox1;
    private System.Windows.Forms.ToolStripComboBox ToolZoomCombo;
		private System.Windows.Forms.TextBox TextureHeight;
		private System.Windows.Forms.TextBox TextureWidth;
		private System.Windows.Forms.TextBox TextureY;
    private System.Windows.Forms.TextBox TextureX;
		private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.GroupBox groupBox2;
    private System.Windows.Forms.CheckBox AutosizeCheck;
    private System.Windows.Forms.Button SizeFromTexture;
    private System.Windows.Forms.GroupBox Tiling;
    private System.Windows.Forms.TextBox SampleHeight;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.TextBox SampleWidth;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.TextBox TileBottomMargin;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.TextBox TileTopMargin;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.TextBox TileLeftMargin;
    private System.Windows.Forms.TextBox TileRightMargin;
    private System.Windows.Forms.Label label8;
    private System.Windows.Forms.Label label9;
    private System.Windows.Forms.ToolStripButton ToolHStretchedTile;
    private System.Windows.Forms.ToolStripButton ToolVStretchedTile;
	}
	
}
