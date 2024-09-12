namespace DockSample
{
    partial class AboutDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
      this.buttonOK = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // buttonOK
      // 
      this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonOK.Location = new System.Drawing.Point( 240, 184 );
      this.buttonOK.Name = "buttonOK";
      this.buttonOK.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOK.TabIndex = 0;
      this.buttonOK.Text = "OK";
      // 
      // AboutDialog
      // 
      this.AcceptButton = this.buttonOK;
      this.CancelButton = this.buttonOK;
      this.ClientSize = new System.Drawing.Size( 322, 215 );
      this.Controls.Add( this.buttonOK );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "AboutDialog";
      this.ShowInTaskbar = false;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "About";
      this.Load += new System.EventHandler( this.AboutDialog_Load );
      this.ResumeLayout( false );

		}
		#endregion

    private System.Windows.Forms.Button buttonOK;
    }
}