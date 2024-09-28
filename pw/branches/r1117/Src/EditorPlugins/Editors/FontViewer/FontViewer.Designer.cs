namespace EditorPlugins.Editors.FontViewer
{
  partial class FontViewer
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
      this.fontViewerControl1 = new EditorPlugins.Editors.FontViewer.FontViewerControl();
      this.SuspendLayout();
      // 
      // fontViewerControl1
      // 
      this.fontViewerControl1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.fontViewerControl1.Location = new System.Drawing.Point( 0, 0 );
      this.fontViewerControl1.Name = "fontViewerControl1";
      this.fontViewerControl1.Size = new System.Drawing.Size( 292, 266 );
      this.fontViewerControl1.TabIndex = 0;
      // 
      // FontViewer
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 292, 266 );
      this.Controls.Add( this.fontViewerControl1 );
      this.Name = "FontViewer";
      this.Text = "FontViewer";
      this.ResumeLayout( false );

    }

    #endregion

    private FontViewerControl fontViewerControl1;
  }
}