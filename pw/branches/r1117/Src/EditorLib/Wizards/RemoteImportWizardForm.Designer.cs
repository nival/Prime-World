namespace EditorLib.Wizards
{
	partial class RemoteImportWizardForm
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
			this.tbURL = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.btnRun = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.btnSaveurl = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// tbURL
			// 
			this.tbURL.Location = new System.Drawing.Point( 35, 13 );
			this.tbURL.Name = "tbURL";
			this.tbURL.Size = new System.Drawing.Size( 353, 20 );
			this.tbURL.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 3, 16 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 26, 13 );
			this.label1.TabIndex = 1;
			this.label1.Text = "URI";
			// 
			// btnRun
			// 
			this.btnRun.Location = new System.Drawing.Point( 35, 39 );
			this.btnRun.Name = "btnRun";
			this.btnRun.Size = new System.Drawing.Size( 75, 23 );
			this.btnRun.TabIndex = 2;
			this.btnRun.Text = "RUN!";
			this.btnRun.UseVisualStyleBackColor = true;
			this.btnRun.Click += new System.EventHandler( this.btnRun_Click );
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point( 313, 39 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 3;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
			// 
			// btnSaveurl
			// 
			this.btnSaveurl.Location = new System.Drawing.Point( 144, 39 );
			this.btnSaveurl.Name = "btnSaveurl";
			this.btnSaveurl.Size = new System.Drawing.Size( 132, 23 );
			this.btnSaveurl.TabIndex = 4;
			this.btnSaveurl.Text = "Save URL and Cancel";
			this.btnSaveurl.UseVisualStyleBackColor = true;
			this.btnSaveurl.Click += new System.EventHandler( this.btnSaveurl_Click );
			// 
			// RemoteImportWizardForm
			// 
			this.AcceptButton = this.btnRun;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.btnCancel;
			this.ClientSize = new System.Drawing.Size( 392, 69 );
			this.ControlBox = false;
			this.Controls.Add( this.btnSaveurl );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.btnRun );
			this.Controls.Add( this.label1 );
			this.Controls.Add( this.tbURL );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "RemoteImportWizardForm";
			this.Text = "Run maya import wizard on remote computer?";
			this.Load += new System.EventHandler( this.RemoteImportWizardForm_Load );
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox tbURL;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnRun;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnSaveurl;
	}
}