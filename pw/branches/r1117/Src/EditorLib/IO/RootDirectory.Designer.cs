namespace EditorLib.IO
{
	partial class RootDirectory
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
			this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
			this.openFileButton = new System.Windows.Forms.Button();
			this.cancel = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.fileSystemRoot = new System.Windows.Forms.TextBox();
			this.ok = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// folderBrowserDialog
			// 
			this.folderBrowserDialog.RootFolder = System.Environment.SpecialFolder.MyComputer;
			this.folderBrowserDialog.SelectedPath = "C:\\";
			// 
			// openFileButton
			// 
			this.openFileButton.Location = new System.Drawing.Point( 255, 12 );
			this.openFileButton.Name = "openFileButton";
			this.openFileButton.Size = new System.Drawing.Size( 25, 23 );
			this.openFileButton.TabIndex = 15;
			this.openFileButton.Text = "...";
			this.openFileButton.UseVisualStyleBackColor = true;
			this.openFileButton.Click += new System.EventHandler( this.openFileButton_Click );
			// 
			// cancel
			// 
			this.cancel.Location = new System.Drawing.Point( 205, 49 );
			this.cancel.Name = "cancel";
			this.cancel.Size = new System.Drawing.Size( 75, 23 );
			this.cancel.TabIndex = 14;
			this.cancel.Text = "Cancel";
			this.cancel.UseVisualStyleBackColor = true;
			this.cancel.Click += new System.EventHandler( this.cancel_Click );
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point( 29, 18 );
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size( 63, 13 );
			this.label3.TabIndex = 13;
			this.label3.Text = "system root:";
			// 
			// fileSystemRoot
			// 
			this.fileSystemRoot.Location = new System.Drawing.Point( 105, 12 );
			this.fileSystemRoot.Name = "fileSystemRoot";
			this.fileSystemRoot.Size = new System.Drawing.Size( 144, 20 );
			this.fileSystemRoot.TabIndex = 11;
			// 
			// ok
			// 
			this.ok.Location = new System.Drawing.Point( 17, 49 );
			this.ok.Name = "ok";
			this.ok.Size = new System.Drawing.Size( 75, 23 );
			this.ok.TabIndex = 12;
			this.ok.Text = "OK";
			this.ok.UseVisualStyleBackColor = true;
			this.ok.Click += new System.EventHandler( this.ok_Click );
			// 
			// RootDirectory
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 292, 89 );
			this.Controls.Add( this.openFileButton );
			this.Controls.Add( this.cancel );
			this.Controls.Add( this.label3 );
			this.Controls.Add( this.fileSystemRoot );
			this.Controls.Add( this.ok );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RootDirectory";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.Text = "RootDirectory";
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button openFileButton;
		private System.Windows.Forms.Button cancel;
		private System.Windows.Forms.Label label3;
		public System.Windows.Forms.TextBox fileSystemRoot;
		private System.Windows.Forms.Button ok;
		private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
	}
}