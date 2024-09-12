namespace EditorLib.FolderSelector
{
  partial class FolderSelectorForm
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
      this.btnOpen = new System.Windows.Forms.Button();
      this.btnCancel = new System.Windows.Forms.Button();
      this.panel1 = new System.Windows.Forms.Panel();
      this.treeFolders = new System.Windows.Forms.TreeView();
      this.panel1.SuspendLayout();
      this.SuspendLayout();
      // 
      // btnOpen
      // 
      this.btnOpen.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.btnOpen.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.btnOpen.Location = new System.Drawing.Point( 41, 12 );
      this.btnOpen.Name = "btnOpen";
      this.btnOpen.Size = new System.Drawing.Size( 75, 23 );
      this.btnOpen.TabIndex = 0;
      this.btnOpen.Text = "Open";
      this.btnOpen.UseVisualStyleBackColor = true;
      this.btnOpen.Click += new System.EventHandler( this.btnOpen_Click );
      // 
      // btnCancel
      // 
      this.btnCancel.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.btnCancel.Location = new System.Drawing.Point( 122, 12 );
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
      this.btnCancel.TabIndex = 1;
      this.btnCancel.Text = "Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      // 
      // panel1
      // 
      this.panel1.Controls.Add( this.btnCancel );
      this.panel1.Controls.Add( this.btnOpen );
      this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.panel1.Location = new System.Drawing.Point( 0, 318 );
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size( 239, 46 );
      this.panel1.TabIndex = 4;
      // 
      // treeFolders
      // 
      this.treeFolders.Dock = System.Windows.Forms.DockStyle.Fill;
      this.treeFolders.Location = new System.Drawing.Point( 0, 0 );
      this.treeFolders.Name = "treeFolders";
      this.treeFolders.Size = new System.Drawing.Size( 239, 318 );
      this.treeFolders.TabIndex = 5;
      // 
      // FolderSelectorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 239, 364 );
      this.Controls.Add( this.treeFolders );
      this.Controls.Add( this.panel1 );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.Name = "FolderSelectorForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "Select Folder";
      this.Load += new System.EventHandler( this.FolderSelector_FormLoad );
      this.panel1.ResumeLayout( false );
      this.ResumeLayout( false );

    }

    #endregion

    private System.Windows.Forms.Button btnOpen;
    private System.Windows.Forms.Button btnCancel;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.TreeView treeFolders;
  }
}