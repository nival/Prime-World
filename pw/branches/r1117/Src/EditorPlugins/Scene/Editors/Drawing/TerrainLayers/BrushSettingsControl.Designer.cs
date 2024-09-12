namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	partial class BrushSettingsControl
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( BrushSettingsControl ) );
      this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
      this.brushSizeTrackBar = new System.Windows.Forms.TrackBar();
      this.brushSizeLabel = new System.Windows.Forms.Label();
      this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
      this.toolStrip1 = new System.Windows.Forms.ToolStrip();
      this.layerColorsButton = new System.Windows.Forms.ToolStripButton();
      this.tableLayoutPanel1.SuspendLayout();
      ( (System.ComponentModel.ISupportInitialize)( this.brushSizeTrackBar ) ).BeginInit();
      this.tableLayoutPanel2.SuspendLayout();
      this.toolStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // tableLayoutPanel1
      // 
      this.tableLayoutPanel1.ColumnCount = 1;
      this.tableLayoutPanel1.ColumnStyles.Add( new System.Windows.Forms.ColumnStyle( System.Windows.Forms.SizeType.Percent, 100F ) );
      this.tableLayoutPanel1.Controls.Add( this.brushSizeTrackBar, 0, 1 );
      this.tableLayoutPanel1.Controls.Add( this.brushSizeLabel, 0, 0 );
      this.tableLayoutPanel1.Controls.Add( this.tableLayoutPanel2, 0, 2 );
      this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tableLayoutPanel1.Location = new System.Drawing.Point( 0, 0 );
      this.tableLayoutPanel1.Name = "tableLayoutPanel1";
      this.tableLayoutPanel1.RowCount = 4;
      this.tableLayoutPanel1.RowStyles.Add( new System.Windows.Forms.RowStyle( System.Windows.Forms.SizeType.Absolute, 20F ) );
      this.tableLayoutPanel1.RowStyles.Add( new System.Windows.Forms.RowStyle( System.Windows.Forms.SizeType.Absolute, 37F ) );
      this.tableLayoutPanel1.RowStyles.Add( new System.Windows.Forms.RowStyle( System.Windows.Forms.SizeType.Absolute, 30F ) );
      this.tableLayoutPanel1.RowStyles.Add( new System.Windows.Forms.RowStyle() );
      this.tableLayoutPanel1.Size = new System.Drawing.Size( 369, 395 );
      this.tableLayoutPanel1.TabIndex = 0;
      // 
      // brushSizeTrackBar
      // 
      this.brushSizeTrackBar.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.brushSizeTrackBar.LargeChange = 1;
      this.brushSizeTrackBar.Location = new System.Drawing.Point( 3, 23 );
      this.brushSizeTrackBar.Maximum = 9;
      this.brushSizeTrackBar.Name = "brushSizeTrackBar";
      this.brushSizeTrackBar.Size = new System.Drawing.Size( 363, 31 );
      this.brushSizeTrackBar.TabIndex = 1;
      // 
      // brushSizeLabel
      // 
      this.brushSizeLabel.AutoSize = true;
      this.brushSizeLabel.Location = new System.Drawing.Point( 3, 0 );
      this.brushSizeLabel.Name = "brushSizeLabel";
      this.brushSizeLabel.Size = new System.Drawing.Size( 58, 13 );
      this.brushSizeLabel.TabIndex = 0;
      this.brushSizeLabel.Text = "Brush size:";
      // 
      // tableLayoutPanel2
      // 
      this.tableLayoutPanel2.ColumnCount = 1;
      this.tableLayoutPanel2.ColumnStyles.Add( new System.Windows.Forms.ColumnStyle( System.Windows.Forms.SizeType.Percent, 100F ) );
      this.tableLayoutPanel2.ColumnStyles.Add( new System.Windows.Forms.ColumnStyle( System.Windows.Forms.SizeType.Absolute, 25F ) );
      this.tableLayoutPanel2.Controls.Add( this.toolStrip1, 0, 0 );
      this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tableLayoutPanel2.Location = new System.Drawing.Point( 3, 60 );
      this.tableLayoutPanel2.Name = "tableLayoutPanel2";
      this.tableLayoutPanel2.RowCount = 1;
      this.tableLayoutPanel2.RowStyles.Add( new System.Windows.Forms.RowStyle( System.Windows.Forms.SizeType.Percent, 100F ) );
      this.tableLayoutPanel2.Size = new System.Drawing.Size( 363, 24 );
      this.tableLayoutPanel2.TabIndex = 2;
      // 
      // toolStrip1
      // 
      this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.toolStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.layerColorsButton} );
      this.toolStrip1.Location = new System.Drawing.Point( 0, 0 );
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new System.Drawing.Size( 363, 24 );
      this.toolStrip1.TabIndex = 0;
      this.toolStrip1.Text = "toolStrip1";
      // 
      // layerColorsButton
      // 
      this.layerColorsButton.CheckOnClick = true;
      this.layerColorsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.ImageAndText;
      this.layerColorsButton.Image = ( (System.Drawing.Image)( resources.GetObject( "layerColorsButton.Image" ) ) );
      this.layerColorsButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.layerColorsButton.Name = "layerColorsButton";
      this.layerColorsButton.Size = new System.Drawing.Size( 23, 21 );
      this.layerColorsButton.Text = "Normal Mode";
      this.layerColorsButton.CheckedChanged += new System.EventHandler( this.layerColorsButton_CheckedChanged );
      // 
      // BrushSettingsControl
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add( this.tableLayoutPanel1 );
      this.Name = "BrushSettingsControl";
      this.Size = new System.Drawing.Size( 369, 395 );
      this.tableLayoutPanel1.ResumeLayout( false );
      this.tableLayoutPanel1.PerformLayout();
      ( (System.ComponentModel.ISupportInitialize)( this.brushSizeTrackBar ) ).EndInit();
      this.tableLayoutPanel2.ResumeLayout( false );
      this.tableLayoutPanel2.PerformLayout();
      this.toolStrip1.ResumeLayout( false );
      this.toolStrip1.PerformLayout();
      this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Label brushSizeLabel;
		private System.Windows.Forms.TrackBar brushSizeTrackBar;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton layerColorsButton;
	}
}
