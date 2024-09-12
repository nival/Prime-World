namespace EditorLib.Wizards.TableDataEditing
{
  partial class TableDataPresetsForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( TableDataPresetsForm ) );
			this.btnSavePreset = new System.Windows.Forms.Button();
			this.label7 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.btnRootFolder = new System.Windows.Forms.Button();
			this.cboType = new System.Windows.Forms.ComboBox();
			this.txtRootFolder = new System.Windows.Forms.TextBox();
			this.btnCancel = new System.Windows.Forms.Button();
			this.lblProperties = new System.Windows.Forms.Label();
			this.panel1 = new System.Windows.Forms.Panel();
			this.lstPresets = new System.Windows.Forms.ListBox();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
			this.tsbAddPreset = new System.Windows.Forms.ToolStripButton();
			this.tsbDeletePreset = new System.Windows.Forms.ToolStripButton();
			this.grPreset = new System.Windows.Forms.GroupBox();
			this.txtPresetName = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.treeProperties = new EditorLib.ImprovedTreeView();
			this.panel1.SuspendLayout();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.grPreset.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnSavePreset
			// 
			this.btnSavePreset.Anchor = System.Windows.Forms.AnchorStyles.Top;
			this.btnSavePreset.Location = new System.Drawing.Point( 123, 11 );
			this.btnSavePreset.Name = "btnSavePreset";
			this.btnSavePreset.Size = new System.Drawing.Size( 75, 23 );
			this.btnSavePreset.TabIndex = 0;
			this.btnSavePreset.Text = "Save";
			this.btnSavePreset.UseVisualStyleBackColor = true;
			this.btnSavePreset.Click += new System.EventHandler( this.OnSaveClick );
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point( 10, 69 );
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size( 62, 13 );
			this.label7.TabIndex = 1;
			this.label7.Text = "Root Folder";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 10, 42 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 31, 13 );
			this.label1.TabIndex = 0;
			this.label1.Text = "Type";
			// 
			// btnRootFolder
			// 
			this.btnRootFolder.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.btnRootFolder.Location = new System.Drawing.Point( 355, 64 );
			this.btnRootFolder.Name = "btnRootFolder";
			this.btnRootFolder.Size = new System.Drawing.Size( 29, 23 );
			this.btnRootFolder.TabIndex = 3;
			this.btnRootFolder.Text = "...";
			this.btnRootFolder.UseVisualStyleBackColor = true;
			this.btnRootFolder.Click += new System.EventHandler( this.OnRootFolderClick );
			// 
			// cboType
			// 
			this.cboType.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.cboType.FormattingEnabled = true;
			this.cboType.Location = new System.Drawing.Point( 84, 39 );
			this.cboType.MaxDropDownItems = 20;
			this.cboType.Name = "cboType";
			this.cboType.Size = new System.Drawing.Size( 300, 21 );
			this.cboType.TabIndex = 1;
			this.cboType.SelectedIndexChanged += new System.EventHandler( this.OnTypeChanged );
			// 
			// txtRootFolder
			// 
			this.txtRootFolder.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.txtRootFolder.Location = new System.Drawing.Point( 84, 66 );
			this.txtRootFolder.Name = "txtRootFolder";
			this.txtRootFolder.Size = new System.Drawing.Size( 265, 20 );
			this.txtRootFolder.TabIndex = 2;
			this.txtRootFolder.Leave += new System.EventHandler( this.txtRootFolder_Leave );
			// 
			// btnCancel
			// 
			this.btnCancel.Anchor = System.Windows.Forms.AnchorStyles.Top;
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point( 204, 11 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 1;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			// 
			// lblProperties
			// 
			this.lblProperties.AutoSize = true;
			this.lblProperties.Location = new System.Drawing.Point( 10, 104 );
			this.lblProperties.Name = "lblProperties";
			this.lblProperties.Size = new System.Drawing.Size( 54, 13 );
			this.lblProperties.TabIndex = 20;
			this.lblProperties.Text = "Properties";
			// 
			// panel1
			// 
			this.panel1.Controls.Add( this.btnSavePreset );
			this.panel1.Controls.Add( this.btnCancel );
			this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel1.Location = new System.Drawing.Point( 0, 477 );
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size( 402, 44 );
			this.panel1.TabIndex = 3;
			// 
			// lstPresets
			// 
			this.lstPresets.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.lstPresets.FormattingEnabled = true;
			this.lstPresets.IntegralHeight = false;
			this.lstPresets.Location = new System.Drawing.Point( 3, 28 );
			this.lstPresets.Name = "lstPresets";
			this.lstPresets.Size = new System.Drawing.Size( 174, 490 );
			this.lstPresets.TabIndex = 0;
			this.lstPresets.SelectedIndexChanged += new System.EventHandler( this.OnPresetSelected );
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point( 0, 0 );
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add( this.toolStrip1 );
			this.splitContainer1.Panel1.Controls.Add( this.lstPresets );
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add( this.grPreset );
			this.splitContainer1.Panel2.Controls.Add( this.panel1 );
			this.splitContainer1.Panel2.Controls.Add( this.label3 );
			this.splitContainer1.Size = new System.Drawing.Size( 586, 521 );
			this.splitContainer1.SplitterDistance = 180;
			this.splitContainer1.TabIndex = 22;
			// 
			// toolStrip1
			// 
			this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.toolStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.tsbAddPreset,
            this.tsbDeletePreset} );
			this.toolStrip1.Location = new System.Drawing.Point( 0, 0 );
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size( 180, 25 );
			this.toolStrip1.TabIndex = 22;
			this.toolStrip1.Text = "tsPresets";
			// 
			// toolStripLabel1
			// 
			this.toolStripLabel1.Name = "toolStripLabel1";
			this.toolStripLabel1.Size = new System.Drawing.Size( 56, 22 );
			this.toolStripLabel1.Text = "Presets    ";
			// 
			// tsbAddPreset
			// 
			this.tsbAddPreset.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbAddPreset.Image = global::EditorLib.EditorLibResources.Add;
			this.tsbAddPreset.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbAddPreset.Name = "tsbAddPreset";
			this.tsbAddPreset.Size = new System.Drawing.Size( 23, 22 );
			this.tsbAddPreset.Text = "Add New Preset";
			this.tsbAddPreset.Click += new System.EventHandler( this.OnAddPresetClick );
			// 
			// tsbDeletePreset
			// 
			this.tsbDeletePreset.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbDeletePreset.Image = ( (System.Drawing.Image)( resources.GetObject( "tsbDeletePreset.Image" ) ) );
			this.tsbDeletePreset.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbDeletePreset.Name = "tsbDeletePreset";
			this.tsbDeletePreset.Size = new System.Drawing.Size( 23, 22 );
			this.tsbDeletePreset.Text = "Delete Selected Preset";
			this.tsbDeletePreset.Click += new System.EventHandler( this.OnDeletePresetClick );
			// 
			// grPreset
			// 
			this.grPreset.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.grPreset.Controls.Add( this.txtPresetName );
			this.grPreset.Controls.Add( this.label2 );
			this.grPreset.Controls.Add( this.label7 );
			this.grPreset.Controls.Add( this.treeProperties );
			this.grPreset.Controls.Add( this.label1 );
			this.grPreset.Controls.Add( this.btnRootFolder );
			this.grPreset.Controls.Add( this.lblProperties );
			this.grPreset.Controls.Add( this.cboType );
			this.grPreset.Controls.Add( this.txtRootFolder );
			this.grPreset.Location = new System.Drawing.Point( 0, 3 );
			this.grPreset.Name = "grPreset";
			this.grPreset.Size = new System.Drawing.Size( 396, 468 );
			this.grPreset.TabIndex = 22;
			this.grPreset.TabStop = false;
			this.grPreset.Leave += new System.EventHandler( this.OnLeavePreset );
			// 
			// txtPresetName
			// 
			this.txtPresetName.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.txtPresetName.Location = new System.Drawing.Point( 84, 13 );
			this.txtPresetName.Name = "txtPresetName";
			this.txtPresetName.Size = new System.Drawing.Size( 300, 20 );
			this.txtPresetName.TabIndex = 0;
			this.txtPresetName.Leave += new System.EventHandler( this.txtPresetName_Leave );
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 10, 16 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 68, 13 );
			this.label2.TabIndex = 4;
			this.label2.Text = "Preset Name";
			// 
			// label3
			// 
			this.label3.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.label3.Location = new System.Drawing.Point( 44, 176 );
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size( 315, 168 );
			this.label3.TabIndex = 21;
			this.label3.Text = "Preset not selected";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.label3.Visible = false;
			// 
			// treeProperties
			// 
			this.treeProperties.AdditionalTextColor = System.Drawing.SystemColors.GrayText;
			this.treeProperties.AdditionalTextFont = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic );
			this.treeProperties.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.treeProperties.CheckBoxes = true;
			this.treeProperties.DrawMode = System.Windows.Forms.TreeViewDrawMode.OwnerDrawText;
			this.treeProperties.Location = new System.Drawing.Point( 13, 120 );
			this.treeProperties.Name = "treeProperties";
			this.treeProperties.Size = new System.Drawing.Size( 371, 330 );
			this.treeProperties.TabIndex = 4;
			this.treeProperties.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler( this.OnBeforeNodeExpand );
			this.treeProperties.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler( this.OnNodeMouseClick );
			// 
			// TableDataPresetsForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 586, 521 );
			this.Controls.Add( this.splitContainer1 );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
			this.Name = "TableDataPresetsForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Table Presets Manager";
			this.panel1.ResumeLayout( false );
			this.splitContainer1.Panel1.ResumeLayout( false );
			this.splitContainer1.Panel1.PerformLayout();
			this.splitContainer1.Panel2.ResumeLayout( false );
			this.splitContainer1.ResumeLayout( false );
			this.toolStrip1.ResumeLayout( false );
			this.toolStrip1.PerformLayout();
			this.grPreset.ResumeLayout( false );
			this.grPreset.PerformLayout();
			this.ResumeLayout( false );

    }

    #endregion

		private System.Windows.Forms.Button btnSavePreset;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button btnRootFolder;
    private System.Windows.Forms.ComboBox cboType;
    private System.Windows.Forms.TextBox txtRootFolder;
		private System.Windows.Forms.Button btnCancel;
    private System.Windows.Forms.Label lblProperties;
    private System.Windows.Forms.Panel panel1;
		private ImprovedTreeView treeProperties;
		private System.Windows.Forms.ListBox lstPresets;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton tsbAddPreset;
		private System.Windows.Forms.ToolStripButton tsbDeletePreset;
		private System.Windows.Forms.ToolStripLabel toolStripLabel1;
		private System.Windows.Forms.TextBox txtPresetName;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.GroupBox grPreset;
		private System.Windows.Forms.Label label3;
  }
}