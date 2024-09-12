namespace libdb.DB
{
	partial class UninlineFileAsker
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

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.ok = new System.Windows.Forms.Button();
			this.cancel = new System.Windows.Forms.Button();
			this.filename = new System.Windows.Forms.TextBox();
			this.dir = new System.Windows.Forms.Label();
			this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
			this.labelExt = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// ok
			// 
			this.ok.Enabled = false;
			this.ok.Location = new System.Drawing.Point( 217, 72 );
			this.ok.Name = "ok";
			this.ok.Size = new System.Drawing.Size( 75, 23 );
			this.ok.TabIndex = 0;
			this.ok.Text = "OK";
			this.ok.UseVisualStyleBackColor = true;
			this.ok.Click += new System.EventHandler( this.ok_Click );
			// 
			// cancel
			// 
			this.cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.cancel.Location = new System.Drawing.Point( 298, 72 );
			this.cancel.Name = "cancel";
			this.cancel.Size = new System.Drawing.Size( 75, 23 );
			this.cancel.TabIndex = 1;
			this.cancel.Text = "Cancel";
			this.cancel.UseVisualStyleBackColor = true;
			this.cancel.Click += new System.EventHandler( this.cancel_Click );
			// 
			// filename
			// 
			this.filename.Location = new System.Drawing.Point( 12, 35 );
			this.filename.Name = "filename";
			this.filename.Size = new System.Drawing.Size( 297, 20 );
			this.filename.TabIndex = 2;
			this.filename.Text = "Write correct file name here";
			this.filename.Enter += new System.EventHandler( this.filename_Enter );
			// 
			// dir
			// 
			this.dir.Location = new System.Drawing.Point( 12, 9 );
			this.dir.Name = "dir";
			this.dir.Size = new System.Drawing.Size( 567, 23 );
			this.dir.TabIndex = 3;
			this.dir.Text = ".\\";
			this.dir.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// labelExt
			// 
			this.labelExt.AutoSize = true;
			this.labelExt.Location = new System.Drawing.Point( 315, 38 );
			this.labelExt.Name = "labelExt";
			this.labelExt.Size = new System.Drawing.Size( 58, 13 );
			this.labelExt.TabIndex = 4;
			this.labelExt.Text = "(extension)";
			// 
			// UninlineFileAsker
			// 
			this.AcceptButton = this.ok;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.cancel;
			this.ClientSize = new System.Drawing.Size( 390, 107 );
			this.Controls.Add( this.labelExt );
			this.Controls.Add( this.dir );
			this.Controls.Add( this.filename );
			this.Controls.Add( this.cancel );
			this.Controls.Add( this.ok );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "UninlineFileAsker";
			this.ShowIcon = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Specify name for uninlined object";
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button ok;
		private System.Windows.Forms.Button cancel;
		private System.Windows.Forms.TextBox filename;
		private System.Windows.Forms.Label dir;
    private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
    private System.Windows.Forms.Label labelExt;
	}
}