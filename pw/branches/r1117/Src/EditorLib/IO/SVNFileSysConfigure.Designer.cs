namespace EditorLib.IO
{
	partial class SVNFileSysConfigure
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
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.tbRepo = new System.Windows.Forms.TextBox();
			this.tbFSRoot = new System.Windows.Forms.TextBox();
			this.btnSave = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 12, 13 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 107, 13 );
			this.label1.TabIndex = 0;
			this.label1.Text = "SVN Repository URL";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 12, 54 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 62, 13 );
			this.label2.TabIndex = 1;
			this.label2.Text = "Root Folder";
			// 
			// tbRepo
			// 
			this.tbRepo.Location = new System.Drawing.Point( 12, 29 );
			this.tbRepo.Name = "tbRepo";
			this.tbRepo.Size = new System.Drawing.Size( 363, 20 );
			this.tbRepo.TabIndex = 2;
			// 
			// tbFSRoot
			// 
			this.tbFSRoot.Location = new System.Drawing.Point( 12, 70 );
			this.tbFSRoot.Name = "tbFSRoot";
			this.tbFSRoot.Size = new System.Drawing.Size( 328, 20 );
			this.tbFSRoot.TabIndex = 3;
			// 
			// btnSave
			// 
			this.btnSave.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnSave.Location = new System.Drawing.Point( 219, 99 );
			this.btnSave.Name = "btnSave";
			this.btnSave.Size = new System.Drawing.Size( 75, 23 );
			this.btnSave.TabIndex = 4;
			this.btnSave.Text = "Save";
			this.btnSave.UseVisualStyleBackColor = true;
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point( 300, 99 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 5;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point( 346, 70 );
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size( 29, 23 );
			this.button3.TabIndex = 6;
			this.button3.Text = "...";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler( this.button3_Click );
			// 
			// SVNFileSysConfigure
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 387, 127 );
			this.Controls.Add( this.button3 );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.btnSave );
			this.Controls.Add( this.tbFSRoot );
			this.Controls.Add( this.tbRepo );
			this.Controls.Add( this.label2 );
			this.Controls.Add( this.label1 );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "SVNFileSysConfigure";
			this.Text = "SVNFileSysConfigure";
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button btnSave;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button button3;
		public System.Windows.Forms.TextBox tbFSRoot;
		public System.Windows.Forms.TextBox tbRepo;
	}
}