namespace PWLocalizator
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
			this.label1 = new System.Windows.Forms.Label();
			this.txtDataFolder = new System.Windows.Forms.TextBox();
			this.btnBrowse = new System.Windows.Forms.Button();
			this.btnToExcel = new System.Windows.Forms.Button();
			this.btnToData = new System.Windows.Forms.Button();
			this.bwUpdateData = new System.ComponentModel.BackgroundWorker();
			this.bwCollectData = new System.ComponentModel.BackgroundWorker();
			this.progress = new System.Windows.Forms.ProgressBar();
			this.pnlProgress = new System.Windows.Forms.Panel();
			this.pnlCommands = new System.Windows.Forms.Panel();
			this.lblStatus = new System.Windows.Forms.Label();
			this.pnlProgress.SuspendLayout();
			this.pnlCommands.SuspendLayout();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 12, 15 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 59, 13 );
			this.label1.TabIndex = 0;
			this.label1.Text = "Data folder";
			// 
			// txtDataFolder
			// 
			this.txtDataFolder.Location = new System.Drawing.Point( 77, 12 );
			this.txtDataFolder.Name = "txtDataFolder";
			this.txtDataFolder.Size = new System.Drawing.Size( 209, 20 );
			this.txtDataFolder.TabIndex = 1;
			this.txtDataFolder.Text = "";
			// 
			// btnBrowse
			// 
			this.btnBrowse.Location = new System.Drawing.Point( 292, 10 );
			this.btnBrowse.Name = "btnBrowse";
			this.btnBrowse.Size = new System.Drawing.Size( 24, 23 );
			this.btnBrowse.TabIndex = 2;
			this.btnBrowse.Text = "...";
			this.btnBrowse.UseVisualStyleBackColor = true;
			this.btnBrowse.Click += new System.EventHandler( this.btnBrowse_Click );
			// 
			// btnToExcel
			// 
			this.btnToExcel.Image = global::PWLocalizator.Properties.Resources.excel;
			this.btnToExcel.Location = new System.Drawing.Point( 3, 16 );
			this.btnToExcel.Name = "btnToExcel";
			this.btnToExcel.Size = new System.Drawing.Size( 129, 69 );
			this.btnToExcel.TabIndex = 5;
			this.btnToExcel.Text = "Save To Excel";
			this.btnToExcel.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
			this.btnToExcel.UseVisualStyleBackColor = true;
			this.btnToExcel.Click += new System.EventHandler( this.btnToExcel_Click );
			// 
			// btnToData
			// 
			this.btnToData.Image = global::PWLocalizator.Properties.Resources.App;
			this.btnToData.Location = new System.Drawing.Point( 138, 16 );
			this.btnToData.Name = "btnToData";
			this.btnToData.Size = new System.Drawing.Size( 129, 69 );
			this.btnToData.TabIndex = 6;
			this.btnToData.Text = "Update Data";
			this.btnToData.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
			this.btnToData.UseVisualStyleBackColor = true;
			this.btnToData.Click += new System.EventHandler( this.btnToData_Click );
			// 
			// bwUpdateData
			// 
			this.bwUpdateData.WorkerReportsProgress = true;
			// 
			// bwCollectData
			// 
			this.bwCollectData.WorkerReportsProgress = true;
			// 
			// progress
			// 
			this.progress.Location = new System.Drawing.Point( 6, 31 );
			this.progress.Name = "progress";
			this.progress.Size = new System.Drawing.Size( 258, 23 );
			this.progress.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
			this.progress.TabIndex = 7;
			// 
			// pnlProgress
			// 
			this.pnlProgress.Controls.Add( this.lblStatus );
			this.pnlProgress.Controls.Add( this.progress );
			this.pnlProgress.Location = new System.Drawing.Point( 22, 52 );
			this.pnlProgress.Name = "pnlProgress";
			this.pnlProgress.Size = new System.Drawing.Size( 271, 100 );
			this.pnlProgress.TabIndex = 8;
			this.pnlProgress.Visible = false;
			// 
			// pnlCommands
			// 
			this.pnlCommands.Controls.Add( this.btnToData );
			this.pnlCommands.Controls.Add( this.btnToExcel );
			this.pnlCommands.Location = new System.Drawing.Point( 22, 52 );
			this.pnlCommands.Name = "pnlCommands";
			this.pnlCommands.Size = new System.Drawing.Size( 271, 100 );
			this.pnlCommands.TabIndex = 9;
			// 
			// lblStatus
			// 
			this.lblStatus.AutoSize = true;
			this.lblStatus.Location = new System.Drawing.Point( 10, 57 );
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.Size = new System.Drawing.Size( 35, 13 );
			this.lblStatus.TabIndex = 8;
			this.lblStatus.Text = "status";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 322, 172 );
			this.Controls.Add( this.pnlCommands );
			this.Controls.Add( this.pnlProgress );
			this.Controls.Add( this.btnBrowse );
			this.Controls.Add( this.txtDataFolder );
			this.Controls.Add( this.label1 );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "PW Localization Tool";
			this.Load += new System.EventHandler( this.MainForm_Load );
			this.pnlProgress.ResumeLayout( false );
			this.pnlProgress.PerformLayout();
			this.pnlCommands.ResumeLayout( false );
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox txtDataFolder;
		private System.Windows.Forms.Button btnBrowse;
		private System.Windows.Forms.Button btnToExcel;
		private System.Windows.Forms.Button btnToData;
		private System.ComponentModel.BackgroundWorker bwUpdateData;
		private System.ComponentModel.BackgroundWorker bwCollectData;
		private System.Windows.Forms.ProgressBar progress;
		private System.Windows.Forms.Panel pnlProgress;
		private System.Windows.Forms.Label lblStatus;
		private System.Windows.Forms.Panel pnlCommands;
	}
}

