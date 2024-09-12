namespace EditorPlugins.LayoutEditor
{
	partial class LayoutEditor
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
      this.editArea = new UnscrollingPanelControl();
      this.editorControl = new EditorPlugins.LayoutEditor.LayoutEditorControl();
      this.toolStripLayout = new System.Windows.Forms.ToolStrip();
      this.toolStripLabelGridSize = new System.Windows.Forms.ToolStripLabel();
      this.toolStripTextBoxGridSize = new System.Windows.Forms.ToolStripTextBox();
      this.toolStripButtonShowGrid = new System.Windows.Forms.ToolStripButton();
      this.toolStripButtonGridSnap = new System.Windows.Forms.ToolStripButton();
      this.toolStripButtonParentSnap = new System.Windows.Forms.ToolStripButton();
      this.toolStripButtonWindowSnap = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.SelectState = new System.Windows.Forms.ToolStripComboBox();
      this.listBox1 = new System.Windows.Forms.ListBox();
      this.toolStripLayout.SuspendLayout();
      this.editArea.SuspendLayout();
      this.SuspendLayout();
      // 
      // toolStripLayout
      // 
      this.toolStripLayout.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.toolStripLayout.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabelGridSize,
            this.toolStripTextBoxGridSize,
            this.toolStripButtonShowGrid,
            this.toolStripButtonGridSnap,
            this.toolStripButtonParentSnap,
            this.toolStripButtonWindowSnap,
            this.toolStripSeparator1,
            this.SelectState} );
      this.toolStripLayout.Location = new System.Drawing.Point( 0, 0 );
      this.toolStripLayout.Name = "toolStripLayout";
      this.toolStripLayout.Size = new System.Drawing.Size( 711, 25 );
      this.toolStripLayout.TabIndex = 0;
      this.toolStripLayout.Text = "toolStrip1";
      // 
      // toolStripLabelGridSize
      // 
      this.toolStripLabelGridSize.Name = "toolStripLabelGridSize";
      this.toolStripLabelGridSize.Size = new System.Drawing.Size( 30, 22 );
      this.toolStripLabelGridSize.Text = "Grid:";
      // 
      // toolStripTextBoxGridSize
      // 
      this.toolStripTextBoxGridSize.Name = "toolStripTextBoxGridSize";
      this.toolStripTextBoxGridSize.Size = new System.Drawing.Size( 30, 25 );
      this.toolStripTextBoxGridSize.Text = "10";
      this.toolStripTextBoxGridSize.TextBoxTextAlign = System.Windows.Forms.HorizontalAlignment.Right;
      this.toolStripTextBoxGridSize.Leave += new System.EventHandler( this.toolStripTextBoxGridSize_Leave );
      // 
      // toolStripButtonShowGrid
      // 
      this.toolStripButtonShowGrid.CheckOnClick = true;
      this.toolStripButtonShowGrid.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripButtonShowGrid.Image = global::EditorPlugins.LayoutEditor.Resource.ShowGrid;
      this.toolStripButtonShowGrid.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButtonShowGrid.Name = "toolStripButtonShowGrid";
      this.toolStripButtonShowGrid.Size = new System.Drawing.Size( 23, 22 );
      this.toolStripButtonShowGrid.Text = "Show Grid";
      this.toolStripButtonShowGrid.CheckedChanged += new System.EventHandler( this.toolStripButtonShowGrid_CheckedChanged );
      // 
      // toolStripButtonGridSnap
      // 
      this.toolStripButtonGridSnap.CheckOnClick = true;
      this.toolStripButtonGridSnap.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripButtonGridSnap.Image = global::EditorPlugins.LayoutEditor.Resource.SnapGrid;
      this.toolStripButtonGridSnap.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButtonGridSnap.Name = "toolStripButtonGridSnap";
      this.toolStripButtonGridSnap.Size = new System.Drawing.Size( 23, 22 );
      this.toolStripButtonGridSnap.Text = "Grid Snap";
      this.toolStripButtonGridSnap.CheckedChanged += new System.EventHandler( this.toolStripButtonGridSnap_CheckedChanged );
      // 
      // toolStripButtonParentSnap
      // 
      this.toolStripButtonParentSnap.CheckOnClick = true;
      this.toolStripButtonParentSnap.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripButtonParentSnap.Image = global::EditorPlugins.LayoutEditor.Resource.SnapParent;
      this.toolStripButtonParentSnap.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButtonParentSnap.Name = "toolStripButtonParentSnap";
      this.toolStripButtonParentSnap.Size = new System.Drawing.Size( 23, 22 );
      this.toolStripButtonParentSnap.Text = "Parent Snap";
      this.toolStripButtonParentSnap.Enabled = false;
      this.toolStripButtonParentSnap.CheckedChanged += new System.EventHandler( this.toolStripButtonParentSnap_CheckedChanged );
      // 
      // toolStripButtonWindowSnap
      // 
      this.toolStripButtonWindowSnap.CheckOnClick = true;
      this.toolStripButtonWindowSnap.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripButtonWindowSnap.Image = global::EditorPlugins.LayoutEditor.Resource.SnapWindows;
      this.toolStripButtonWindowSnap.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButtonWindowSnap.Name = "toolStripButtonWindowSnap";
      this.toolStripButtonWindowSnap.Size = new System.Drawing.Size( 23, 22 );
      this.toolStripButtonWindowSnap.Text = "Neighbour Snap";
      this.toolStripButtonWindowSnap.Enabled = false;
      this.toolStripButtonWindowSnap.CheckedChanged += new System.EventHandler( this.toolStripButtonWindowSnap_CheckedChanged );
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
      // 
      // SelectState
      // 
      this.SelectState.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.SelectState.FlatStyle = System.Windows.Forms.FlatStyle.Standard;
      this.SelectState.Name = "SelectState";
      this.SelectState.Size = new System.Drawing.Size( 121, 25 );
      this.SelectState.SelectedIndexChanged += new System.EventHandler( this.SelectState_SelectedIndexChanged );
      // 
			// editorControl
			// 
			this.editorControl.BackColor = System.Drawing.SystemColors.Window;
			this.editorControl.BackColor1 = System.Drawing.Color.LightGray;
			this.editorControl.BackColor2 = System.Drawing.Color.White;
			this.editorControl.BackGridSize = 8;
			this.editorControl.CanvasSize = new System.Drawing.Size( 128, 128 );
			this.editorControl.Location = new System.Drawing.Point( 0, 0 );
			this.editorControl.Name = "editorControl";
			this.editorControl.ParentColor = System.Drawing.Color.Red;
			this.editorControl.RootLayout = null;
			this.editorControl.SelectionColor1 = System.Drawing.SystemColors.Highlight;
			this.editorControl.SelectionColor2 = System.Drawing.Color.White;
			this.editorControl.TabIndex = 0;
      // 
      // rulerControl
      // 
      this.editArea.AutoScroll = true;
      this.editArea.Controls.Add( this.editorControl );
      this.editArea.Dock = System.Windows.Forms.DockStyle.Fill;
      this.editArea.Location = new System.Drawing.Point( 0, 0 );
      this.editArea.Name = "editArea";
      this.editArea.Size = new System.Drawing.Size( 292, 266 );
      this.editArea.TabIndex = 1;
      // 
			// LayoutEditor
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoScroll = true;
			this.BackColor = System.Drawing.SystemColors.Window;
			this.KeyPreview = true;
      this.Controls.Add( this.editArea );
      this.Controls.Add( this.toolStripLayout );
      this.Name = "LayoutEditor";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Document;
			this.TabText = "Layout Editor";
			this.Text = "Layout Editor";
			this.VisibleChanged += new System.EventHandler( this.LayoutEditor_VisibleChanged );
			this.KeyDown += new System.Windows.Forms.KeyEventHandler( this.LayoutEditor_KeyDown );
      this.toolStripLayout.ResumeLayout( false );
      this.toolStripLayout.PerformLayout();
      this.editArea.ResumeLayout( false );
      this.ResumeLayout( false );

		}

		#endregion

		private LayoutEditorControl editorControl;
    private UnscrollingPanelControl editArea;
    private System.Windows.Forms.ToolStrip toolStripLayout;
    private System.Windows.Forms.ToolStripLabel toolStripLabelGridSize;
    private System.Windows.Forms.ListBox listBox1;
    private System.Windows.Forms.ToolStripTextBox toolStripTextBoxGridSize;
    private System.Windows.Forms.ToolStripButton toolStripButtonShowGrid;
    private System.Windows.Forms.ToolStripButton toolStripButtonGridSnap;
    private System.Windows.Forms.ToolStripButton toolStripButtonParentSnap;
    private System.Windows.Forms.ToolStripButton toolStripButtonWindowSnap;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripComboBox SelectState;
  }
}
