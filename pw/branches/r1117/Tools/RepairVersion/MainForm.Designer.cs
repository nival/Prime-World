namespace fixcontent
{
  partial class MainForm
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
      this.logTextBox = new System.Windows.Forms.TextBox();
      this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip( this.components );
      this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.contextMenuStrip.SuspendLayout();
      this.SuspendLayout();
      // 
      // logTextBox
      // 
      this.logTextBox.ContextMenuStrip = this.contextMenuStrip;
      this.logTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
      this.logTextBox.Location = new System.Drawing.Point( 0, 0 );
      this.logTextBox.Multiline = true;
      this.logTextBox.Name = "logTextBox";
      this.logTextBox.ReadOnly = true;
      this.logTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
      this.logTextBox.Size = new System.Drawing.Size( 745, 455 );
      this.logTextBox.TabIndex = 0;
      // 
      // contextMenuStrip
      // 
      this.contextMenuStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem} );
      this.contextMenuStrip.Name = "contextMenuStrip";
      this.contextMenuStrip.Size = new System.Drawing.Size( 182, 26 );
      // 
      // copyToolStripMenuItem
      // 
      this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
      this.copyToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C ) ) );
      this.copyToolStripMenuItem.Size = new System.Drawing.Size( 181, 22 );
      this.copyToolStripMenuItem.Text = "Копировать";
      this.copyToolStripMenuItem.Click += new System.EventHandler( this.OnCopyButtonClick );
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 745, 455 );
      this.Controls.Add( this.logTextBox );
      this.Name = "MainForm";
      this.ShowIcon = false;
      this.Text = "Исправление Версии";
      this.contextMenuStrip.ResumeLayout( false );
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.TextBox logTextBox;
    private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
    private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
  }
}

