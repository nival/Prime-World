namespace EditorPlugins.Minimap
{
	partial class MinimapPanel
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
			if( disposing && ( components != null ) )
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
			this.picMinimap = new System.Windows.Forms.PictureBox();
			this.tsControls = new System.Windows.Forms.ToolStrip();
			this.btnZoomIn = new System.Windows.Forms.ToolStripButton();
			this.btnZoomOut = new System.Windows.Forms.ToolStripButton();
			( (System.ComponentModel.ISupportInitialize)( this.picMinimap ) ).BeginInit();
			this.tsControls.SuspendLayout();
			this.SuspendLayout();
			// 
			// picMinimap
			// 
			this.picMinimap.BackColor = System.Drawing.SystemColors.ControlDark;
			this.picMinimap.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.picMinimap.Location = new System.Drawing.Point( 4, 29 );
			this.picMinimap.Name = "picMinimap";
			this.picMinimap.Size = new System.Drawing.Size( 238, 221 );
			this.picMinimap.TabIndex = 0;
			this.picMinimap.TabStop = false;
			this.picMinimap.Visible = false;
			this.picMinimap.MouseClick += new System.Windows.Forms.MouseEventHandler( this.picMinimap_MouseClick );
			this.picMinimap.Paint += new System.Windows.Forms.PaintEventHandler( this.picMinimap_Paint );
			// 
			// tsControls
			// 
			this.tsControls.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.tsControls.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.btnZoomIn,
            this.btnZoomOut} );
			this.tsControls.Location = new System.Drawing.Point( 0, 0 );
			this.tsControls.Name = "tsControls";
			this.tsControls.Size = new System.Drawing.Size( 247, 25 );
			this.tsControls.TabIndex = 1;
			this.tsControls.Text = "toolStrip1";
			// 
			// btnZoomIn
			// 
			this.btnZoomIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnZoomIn.Image = global::EditorPlugins.EditorPluginResources.ZoomIn;
			this.btnZoomIn.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.btnZoomIn.Name = "btnZoomIn";
			this.btnZoomIn.Size = new System.Drawing.Size( 23, 22 );
			this.btnZoomIn.Text = "Zoom In";
			this.btnZoomIn.Click += new System.EventHandler( this.btnZoomIn_Click );
			// 
			// btnZoomOut
			// 
			this.btnZoomOut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnZoomOut.Image = global::EditorPlugins.EditorPluginResources.ZoomOut;
			this.btnZoomOut.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.btnZoomOut.Name = "btnZoomOut";
			this.btnZoomOut.Size = new System.Drawing.Size( 23, 22 );
			this.btnZoomOut.Text = "Zoom Out";
			this.btnZoomOut.Click += new System.EventHandler( this.btnZoomOut_Click );
			// 
			// MinimapPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.ClientSize = new System.Drawing.Size( 247, 254 );
			this.Controls.Add( this.tsControls );
			this.Controls.Add( this.picMinimap );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.Name = "MinimapPanel";
			this.Text = "MinimapPanel";
			this.Resize += new System.EventHandler( this.MinimapPanel_Resize );
			( (System.ComponentModel.ISupportInitialize)( this.picMinimap ) ).EndInit();
			this.tsControls.ResumeLayout( false );
			this.tsControls.PerformLayout();
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.PictureBox picMinimap;
		private System.Windows.Forms.ToolStrip tsControls;
		private System.Windows.Forms.ToolStripButton btnZoomIn;
		private System.Windows.Forms.ToolStripButton btnZoomOut;
	}
}