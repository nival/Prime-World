namespace EditorPlugins.Committer
{
  partial class DualCommitRevertForm
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
      this.buttonCancel = new System.Windows.Forms.Button();
      this.buttonOk = new System.Windows.Forms.Button();
      this.splitContainer1 = new System.Windows.Forms.SplitContainer();
      this.label1 = new System.Windows.Forms.Label();
      this.listBoxDataFiles = new System.Windows.Forms.ListBox();
      this.label2 = new System.Windows.Forms.Label();
      this.listBoxSourceFiles = new System.Windows.Forms.ListBox();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.SuspendLayout();
      // 
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 404, 219 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 0;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      // 
      // buttonOk
      // 
      this.buttonOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.buttonOk.Location = new System.Drawing.Point( 3, 219 );
      this.buttonOk.Name = "buttonOk";
      this.buttonOk.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOk.TabIndex = 1;
      this.buttonOk.Text = "Revert";
      this.buttonOk.UseVisualStyleBackColor = true;
      this.buttonOk.Click += new System.EventHandler( this.buttonOk_Click );
      // 
      // splitContainer1
      // 
      this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.splitContainer1.Location = new System.Drawing.Point( 0, 0 );
      this.splitContainer1.Name = "splitContainer1";
      this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
      // 
      // splitContainer1.Panel1
      // 
      this.splitContainer1.Panel1.Controls.Add( this.label1 );
      this.splitContainer1.Panel1.Controls.Add( this.listBoxDataFiles );
      // 
      // splitContainer1.Panel2
      // 
      this.splitContainer1.Panel2.Controls.Add( this.label2 );
      this.splitContainer1.Panel2.Controls.Add( this.listBoxSourceFiles );
      this.splitContainer1.Panel2.Controls.Add( this.buttonOk );
      this.splitContainer1.Panel2.Controls.Add( this.buttonCancel );
      this.splitContainer1.Size = new System.Drawing.Size( 482, 497 );
      this.splitContainer1.SplitterDistance = 248;
      this.splitContainer1.TabIndex = 2;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 3, 9 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 123, 13 );
      this.label1.TabIndex = 1;
      this.label1.Text = "Data files to be reverted:";
      // 
      // listBoxDataFiles
      // 
      this.listBoxDataFiles.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxDataFiles.FormattingEnabled = true;
      this.listBoxDataFiles.IntegralHeight = false;
      this.listBoxDataFiles.Location = new System.Drawing.Point( 0, 25 );
      this.listBoxDataFiles.Name = "listBoxDataFiles";
      this.listBoxDataFiles.Size = new System.Drawing.Size( 482, 220 );
      this.listBoxDataFiles.TabIndex = 0;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 3, 0 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 148, 13 );
      this.label2.TabIndex = 3;
      this.label2.Text = "Art source files to be reverted:";
      // 
      // listBoxSourceFiles
      // 
      this.listBoxSourceFiles.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxSourceFiles.FormattingEnabled = true;
      this.listBoxSourceFiles.IntegralHeight = false;
      this.listBoxSourceFiles.Location = new System.Drawing.Point( 0, 17 );
      this.listBoxSourceFiles.Name = "listBoxSourceFiles";
      this.listBoxSourceFiles.Size = new System.Drawing.Size( 482, 196 );
      this.listBoxSourceFiles.TabIndex = 2;
      // 
      // DualCommitRevertForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 482, 497 );
      this.Controls.Add( this.splitContainer1 );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.MinimumSize = new System.Drawing.Size( 400, 400 );
      this.Name = "DualCommitRevertForm";
      this.Text = "Revert";
      this.splitContainer1.Panel1.ResumeLayout( false );
      this.splitContainer1.Panel1.PerformLayout();
      this.splitContainer1.Panel2.ResumeLayout( false );
      this.splitContainer1.Panel2.PerformLayout();
      this.splitContainer1.ResumeLayout( false );
      this.ResumeLayout( false );

    }

    #endregion

    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.Button buttonOk;
    private System.Windows.Forms.SplitContainer splitContainer1;
    private System.Windows.Forms.ListBox listBoxDataFiles;
    private System.Windows.Forms.ListBox listBoxSourceFiles;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
  }
}