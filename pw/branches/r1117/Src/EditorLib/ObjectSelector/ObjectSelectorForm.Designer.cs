namespace EditorLib.ObjectSelector
{
	partial class ObjectSelectorForm
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
      this.buttonsPanel = new System.Windows.Forms.Panel();
      this.openButton = new System.Windows.Forms.Button();
      this.cancelButton = new System.Windows.Forms.Button();
      this.splitContainer = new System.Windows.Forms.SplitContainer();
      this.objectsBrowser = new EditorLib.ObjectsBrowser.ObjectsBrowser();
      this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
      this.toolStripSplitButton1 = new System.Windows.Forms.ToolStripSplitButton();
      this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
      this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
      this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.buttonsPanel.SuspendLayout();
      this.splitContainer.Panel1.SuspendLayout();
      this.splitContainer.Panel2.SuspendLayout();
      this.splitContainer.SuspendLayout();
      this.SuspendLayout();
      // 
      // buttonsPanel
      // 
      this.buttonsPanel.Controls.Add( this.openButton );
      this.buttonsPanel.Controls.Add( this.cancelButton );
      this.buttonsPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.buttonsPanel.Location = new System.Drawing.Point( 0, 298 );
      this.buttonsPanel.Name = "buttonsPanel";
      this.buttonsPanel.Size = new System.Drawing.Size( 237, 29 );
      this.buttonsPanel.TabIndex = 0;
      // 
      // openButton
      // 
      this.openButton.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.openButton.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.openButton.Location = new System.Drawing.Point( 78, 4 );
      this.openButton.Name = "openButton";
      this.openButton.Size = new System.Drawing.Size( 75, 23 );
      this.openButton.TabIndex = 3;
      this.openButton.Text = "Open";
      this.openButton.UseVisualStyleBackColor = true;
      this.openButton.Click += new System.EventHandler( this.OnOpenButtonClick );
      // 
      // cancelButton
      // 
      this.cancelButton.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.cancelButton.Location = new System.Drawing.Point( 159, 4 );
      this.cancelButton.Name = "cancelButton";
      this.cancelButton.Size = new System.Drawing.Size( 75, 23 );
      this.cancelButton.TabIndex = 4;
      this.cancelButton.Text = "Cancel";
      this.cancelButton.UseVisualStyleBackColor = true;
      // 
      // splitContainer
      // 
      this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
      this.splitContainer.Location = new System.Drawing.Point( 0, 0 );
      this.splitContainer.Name = "splitContainer";
      // 
      // splitContainer.Panel1
      // 
      this.splitContainer.Panel1.Controls.Add( this.objectsBrowser );
      // 
      // splitContainer.Panel2
      // 
      this.splitContainer.Panel2.Controls.Add( this.propertyGrid1 );
      this.splitContainer.Panel2.Controls.Add( this.buttonsPanel );
      this.splitContainer.Size = new System.Drawing.Size( 463, 327 );
      this.splitContainer.SplitterDistance = 222;
      this.splitContainer.TabIndex = 0;
      // 
      // objectsBrowser
      // 
      this.objectsBrowser.Dock = System.Windows.Forms.DockStyle.Fill;
      this.objectsBrowser.Location = new System.Drawing.Point( 0, 0 );
      this.objectsBrowser.Name = "objectsBrowser";
      this.objectsBrowser.SelectedObject = null;
      this.objectsBrowser.Size = new System.Drawing.Size( 222, 327 );
      this.objectsBrowser.TabIndex = 2;
      this.objectsBrowser.OpenItemEvent += new System.EventHandler<EditorLib.ObjectsBrowser.DBIDEventArgs>( this.OnOpenItem );
      this.objectsBrowser.ChangeSelectedItemEvent += new EditorLib.ObjectsBrowser.ObjectsBrowser.ChangeSelectedItemEventHandler( this.OnChangeSelectedItem );
      // 
      // propertyGrid1
      // 
      this.propertyGrid1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.propertyGrid1.Location = new System.Drawing.Point( 0, 0 );
      this.propertyGrid1.Name = "propertyGrid1";
      this.propertyGrid1.PropertySort = System.Windows.Forms.PropertySort.Alphabetical;
      this.propertyGrid1.Size = new System.Drawing.Size( 237, 298 );
      this.propertyGrid1.TabIndex = 2;
      this.propertyGrid1.ToolbarVisible = false;
      this.propertyGrid1.SelectedObjectsChanged += new System.EventHandler( this.propertyGrid1_SelectedObjectsChanged );
      // 
      // toolStripSplitButton1
      // 
      this.toolStripSplitButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripSplitButton1.Image = global::EditorLib.EditorLibResources.NewItem;
      this.toolStripSplitButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripSplitButton1.Name = "toolStripSplitButton1";
      this.toolStripSplitButton1.Size = new System.Drawing.Size( 32, 22 );
      this.toolStripSplitButton1.Text = "toolStripSplitButton1";
      // 
      // toolStripButton2
      // 
      this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripButton2.Image = global::EditorLib.EditorLibResources.Rename;
      this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButton2.Name = "toolStripButton2";
      this.toolStripButton2.Size = new System.Drawing.Size( 23, 22 );
      this.toolStripButton2.Text = "toolStripButton2";
      // 
      // toolStripButton3
      // 
      this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.toolStripButton3.Image = global::EditorLib.EditorLibResources.Delete;
      this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButton3.Name = "toolStripButton3";
      this.toolStripButton3.Size = new System.Drawing.Size( 23, 22 );
      this.toolStripButton3.Text = "toolStripButton3";
      // 
      // toolStripButton1
      // 
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new System.Drawing.Size( 23, 23 );
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
      // 
      // ObjectSelectorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.cancelButton;
      this.ClientSize = new System.Drawing.Size( 463, 327 );
      this.Controls.Add( this.splitContainer );
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "ObjectSelectorForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.Text = "Object Selector";
      this.Load += new System.EventHandler( this.ObjectSelectorForm_Load );
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.ObjectSelectorForm_FormClosing );
      this.buttonsPanel.ResumeLayout( false );
      this.splitContainer.Panel1.ResumeLayout( false );
      this.splitContainer.Panel2.ResumeLayout( false );
      this.splitContainer.ResumeLayout( false );
      this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.Panel buttonsPanel;
		private System.Windows.Forms.Button openButton;
    private System.Windows.Forms.Button cancelButton;
		private System.Windows.Forms.SplitContainer splitContainer;
    private System.Windows.Forms.PropertyGrid propertyGrid1;
		private System.Windows.Forms.ToolStripButton toolStripButton1;
    private System.Windows.Forms.ToolStripSplitButton toolStripSplitButton1;
		private System.Windows.Forms.ToolStripButton toolStripButton2;
    private System.Windows.Forms.ToolStripButton toolStripButton3;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private EditorLib.ObjectsBrowser.ObjectsBrowser objectsBrowser;

	}
}