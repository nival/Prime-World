namespace EditorPlugins.Committer
{
  partial class DualCommitForm
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
      this.components = new System.ComponentModel.Container();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.buttonCommit = new System.Windows.Forms.Button();
      this.treeViewAssets = new System.Windows.Forms.TreeView();
      this.imageListTypeIcons = new System.Windows.Forms.ImageList( this.components );
      this.listBoxResourceItems = new System.Windows.Forms.ListBox();
      this.textBoxCommitMessage = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.splitContainer1 = new System.Windows.Forms.SplitContainer();
      this.labelStatus = new System.Windows.Forms.Label();
      this.checkBoxCustomText = new System.Windows.Forms.CheckBox();
      this.linkLabelRevert = new System.Windows.Forms.LinkLabel();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.SuspendLayout();
      // 
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 505, 566 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 0;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      this.buttonCancel.Click += new System.EventHandler( this.buttonCancel_Click );
      // 
      // buttonCommit
      // 
      this.buttonCommit.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCommit.Enabled = false;
      this.buttonCommit.Location = new System.Drawing.Point( 365, 566 );
      this.buttonCommit.Name = "buttonCommit";
      this.buttonCommit.Size = new System.Drawing.Size( 134, 23 );
      this.buttonCommit.TabIndex = 1;
      this.buttonCommit.Text = "Check and Commit";
      this.buttonCommit.UseVisualStyleBackColor = true;
      this.buttonCommit.Click += new System.EventHandler( this.buttonCommit_Click );
      // 
      // treeViewAssets
      // 
      this.treeViewAssets.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.treeViewAssets.CheckBoxes = true;
      this.treeViewAssets.ImageIndex = 0;
      this.treeViewAssets.ImageList = this.imageListTypeIcons;
      this.treeViewAssets.Location = new System.Drawing.Point( 3, 22 );
      this.treeViewAssets.Name = "treeViewAssets";
      this.treeViewAssets.SelectedImageIndex = 0;
      this.treeViewAssets.Size = new System.Drawing.Size( 586, 211 );
      this.treeViewAssets.TabIndex = 4;
      this.treeViewAssets.AfterCheck += new System.Windows.Forms.TreeViewEventHandler( this.treeViewAssets_AfterCheck );
      this.treeViewAssets.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler( this.treeViewAssets_MouseDoubleClick );
      this.treeViewAssets.MouseClick += new System.Windows.Forms.MouseEventHandler( this.treeViewAssets_MouseClick );
      this.treeViewAssets.AfterSelect += new System.Windows.Forms.TreeViewEventHandler( this.treeViewAssets_AfterSelect );
      // 
      // imageListTypeIcons
      // 
      this.imageListTypeIcons.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
      this.imageListTypeIcons.ImageSize = new System.Drawing.Size( 16, 16 );
      this.imageListTypeIcons.TransparentColor = System.Drawing.Color.Transparent;
      // 
      // listBoxResourceItems
      // 
      this.listBoxResourceItems.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxResourceItems.FormattingEnabled = true;
      this.listBoxResourceItems.Location = new System.Drawing.Point( 3, 16 );
      this.listBoxResourceItems.Name = "listBoxResourceItems";
      this.listBoxResourceItems.SelectionMode = System.Windows.Forms.SelectionMode.None;
      this.listBoxResourceItems.Size = new System.Drawing.Size( 586, 108 );
      this.listBoxResourceItems.TabIndex = 5;
      // 
      // textBoxCommitMessage
      // 
      this.textBoxCommitMessage.AcceptsReturn = true;
      this.textBoxCommitMessage.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.textBoxCommitMessage.Location = new System.Drawing.Point( 3, 143 );
      this.textBoxCommitMessage.Multiline = true;
      this.textBoxCommitMessage.Name = "textBoxCommitMessage";
      this.textBoxCommitMessage.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxCommitMessage.Size = new System.Drawing.Size( 586, 173 );
      this.textBoxCommitMessage.TabIndex = 6;
      this.textBoxCommitMessage.TextChanged += new System.EventHandler( this.textBoxCommitMessage_TextChanged );
      this.textBoxCommitMessage.KeyDown += new System.Windows.Forms.KeyEventHandler( this.textBoxCommitMessage_KeyDown );
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 3, 127 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 89, 13 );
      this.label1.TabIndex = 7;
      this.label1.Text = "Commit message:";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 3, 0 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 74, 13 );
      this.label2.TabIndex = 8;
      this.label2.Text = "Files included:";
      // 
      // splitContainer1
      // 
      this.splitContainer1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.splitContainer1.Location = new System.Drawing.Point( 0, 0 );
      this.splitContainer1.Name = "splitContainer1";
      this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
      // 
      // splitContainer1.Panel1
      // 
      this.splitContainer1.Panel1.Controls.Add( this.labelStatus );
      this.splitContainer1.Panel1.Controls.Add( this.treeViewAssets );
      this.splitContainer1.Panel1MinSize = 150;
      // 
      // splitContainer1.Panel2
      // 
      this.splitContainer1.Panel2.Controls.Add( this.checkBoxCustomText );
      this.splitContainer1.Panel2.Controls.Add( this.label1 );
      this.splitContainer1.Panel2.Controls.Add( this.label2 );
      this.splitContainer1.Panel2.Controls.Add( this.textBoxCommitMessage );
      this.splitContainer1.Panel2.Controls.Add( this.listBoxResourceItems );
      this.splitContainer1.Size = new System.Drawing.Size( 592, 560 );
      this.splitContainer1.SplitterDistance = 236;
      this.splitContainer1.SplitterWidth = 5;
      this.splitContainer1.TabIndex = 9;
      // 
      // labelStatus
      // 
      this.labelStatus.AutoSize = true;
      this.labelStatus.Location = new System.Drawing.Point( 3, 6 );
      this.labelStatus.Name = "labelStatus";
      this.labelStatus.Size = new System.Drawing.Size( 130, 13 );
      this.labelStatus.TabIndex = 5;
      this.labelStatus.Text = "Getting SVN Information...";
      // 
      // checkBoxCustomText
      // 
      this.checkBoxCustomText.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.checkBoxCustomText.AutoSize = true;
      this.checkBoxCustomText.Enabled = false;
      this.checkBoxCustomText.Location = new System.Drawing.Point( 445, 126 );
      this.checkBoxCustomText.Name = "checkBoxCustomText";
      this.checkBoxCustomText.Size = new System.Drawing.Size( 142, 17 );
      this.checkBoxCustomText.TabIndex = 9;
      this.checkBoxCustomText.Text = "Custom commit message";
      this.checkBoxCustomText.UseVisualStyleBackColor = true;
      this.checkBoxCustomText.CheckedChanged += new System.EventHandler( this.checkBoxCustomText_CheckedChanged );
      // 
      // linkLabelRevert
      // 
      this.linkLabelRevert.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.linkLabelRevert.AutoSize = true;
      this.linkLabelRevert.Location = new System.Drawing.Point( 3, 571 );
      this.linkLabelRevert.Name = "linkLabelRevert";
      this.linkLabelRevert.Size = new System.Drawing.Size( 117, 13 );
      this.linkLabelRevert.TabIndex = 10;
      this.linkLabelRevert.TabStop = true;
      this.linkLabelRevert.Text = "Revert checked assets";
      this.linkLabelRevert.Visible = false;
      this.linkLabelRevert.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler( this.linkLabelRevert_LinkClicked );
      // 
      // DualCommitForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 592, 601 );
      this.Controls.Add( this.linkLabelRevert );
      this.Controls.Add( this.splitContainer1 );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.buttonCommit );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.MinimizeBox = false;
      this.MinimumSize = new System.Drawing.Size( 500, 550 );
      this.Name = "DualCommitForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.Text = "Combined Commit";
      this.splitContainer1.Panel1.ResumeLayout( false );
      this.splitContainer1.Panel1.PerformLayout();
      this.splitContainer1.Panel2.ResumeLayout( false );
      this.splitContainer1.Panel2.PerformLayout();
      this.splitContainer1.ResumeLayout( false );
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.Button buttonCommit;
    private System.Windows.Forms.TreeView treeViewAssets;
    private System.Windows.Forms.ImageList imageListTypeIcons;
    private System.Windows.Forms.ListBox listBoxResourceItems;
    private System.Windows.Forms.TextBox textBoxCommitMessage;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.SplitContainer splitContainer1;
    private System.Windows.Forms.Label labelStatus;
    private System.Windows.Forms.CheckBox checkBoxCustomText;
    private System.Windows.Forms.LinkLabel linkLabelRevert;
  }
}