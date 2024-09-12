namespace EditorPlugins.Forms
{
	partial class SplashScreen
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
			this.pictureBox = new System.Windows.Forms.PictureBox();
			this.panelStatus = new System.Windows.Forms.Panel();
			this.labelStatus = new System.Windows.Forms.Label();
			this.progressBarStatus = new System.Windows.Forms.ProgressBar();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
			this.panelStatus.SuspendLayout();
			this.SuspendLayout();
			// 
			// pictureBox
			// 
			this.pictureBox.BackColor = System.Drawing.Color.Firebrick;
			this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pictureBox.ErrorImage = null;
			this.pictureBox.InitialImage = null;
			this.pictureBox.Location = new System.Drawing.Point( 0, 0 );
			this.pictureBox.Name = "pictureBox";
			this.pictureBox.Padding = new System.Windows.Forms.Padding( 5 );
			this.pictureBox.Size = new System.Drawing.Size( 512, 320 );
			this.pictureBox.TabIndex = 0;
			this.pictureBox.TabStop = false;
			this.pictureBox.UseWaitCursor = true;
			// 
			// panelStatus
			// 
			this.panelStatus.BackColor = System.Drawing.SystemColors.Control;
			this.panelStatus.Controls.Add( this.labelStatus );
			this.panelStatus.Controls.Add( this.progressBarStatus );
			this.panelStatus.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panelStatus.Location = new System.Drawing.Point( 0, 298 );
			this.panelStatus.Name = "panelStatus";
			this.panelStatus.Size = new System.Drawing.Size( 512, 22 );
			this.panelStatus.TabIndex = 1;
			this.panelStatus.UseWaitCursor = true;
			// 
			// labelStatus
			// 
			this.labelStatus.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
									| System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.labelStatus.BackColor = System.Drawing.SystemColors.Control;
			this.labelStatus.ForeColor = System.Drawing.SystemColors.ControlText;
			this.labelStatus.Location = new System.Drawing.Point( 0, 0 );
			this.labelStatus.Name = "labelStatus";
			this.labelStatus.Size = new System.Drawing.Size( 403, 22 );
			this.labelStatus.TabIndex = 2;
			this.labelStatus.Text = "Ready";
			this.labelStatus.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.labelStatus.UseWaitCursor = true;
			// 
			// progressBarStatus
			// 
			this.progressBarStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.progressBarStatus.Location = new System.Drawing.Point( 409, 3 );
			this.progressBarStatus.Name = "progressBarStatus";
			this.progressBarStatus.Size = new System.Drawing.Size( 100, 16 );
			this.progressBarStatus.TabIndex = 3;
			this.progressBarStatus.UseWaitCursor = true;
			// 
			// SplashScreen
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 512, 320 );
			this.ControlBox = false;
			this.Controls.Add( this.panelStatus );
			this.Controls.Add( this.pictureBox );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "SplashScreen";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "SplashScreen";
			this.UseWaitCursor = true;
			this.Load += new System.EventHandler( this.OnLoad );
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler( this.OnClose );
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
			this.panelStatus.ResumeLayout( false );
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.PictureBox pictureBox;
		private System.Windows.Forms.Panel panelStatus;
		private System.Windows.Forms.Label labelStatus;
		private System.Windows.Forms.ProgressBar progressBarStatus;
	}
}