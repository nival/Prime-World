namespace DockSample
{
    partial class DummyDoc
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
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( DummyDoc ) );
      this.mainMenu = new System.Windows.Forms.MenuStrip();
      this.menuItem1 = new System.Windows.Forms.ToolStripMenuItem();
      this.menuItem2 = new System.Windows.Forms.ToolStripMenuItem();
      this.menuItemCheckTest = new System.Windows.Forms.ToolStripMenuItem();
      this.contextMenuTabPage = new System.Windows.Forms.ContextMenuStrip( this.components );
      this.menuItemClose = new System.Windows.Forms.ToolStripMenuItem();
      this.toolTip = new System.Windows.Forms.ToolTip( this.components );
      this.dgvResult = new System.Windows.Forms.DataGridView();
      this.txtCurrentQuery = new System.Windows.Forms.RichTextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.lblCurrentFile = new System.Windows.Forms.Label();
      this.btnApplyFilter = new System.Windows.Forms.Button();
      this.label2 = new System.Windows.Forms.Label();
      this.btnClearFilter = new System.Windows.Forms.Button();
      this.txtMessage = new System.Windows.Forms.TextBox();
      this.cmbLogLevel = new System.Windows.Forms.ComboBox();
      this.dateTo = new System.Windows.Forms.DateTimePicker();
      this.label3 = new System.Windows.Forms.Label();
      this.dateFrom = new System.Windows.Forms.DateTimePicker();
      this.txtChannel = new System.Windows.Forms.TextBox();
      this.lblMessage = new System.Windows.Forms.Label();
      this.lblLogLevel = new System.Windows.Forms.Label();
      this.lblChannel = new System.Windows.Forms.Label();
      this.lblTime = new System.Windows.Forms.Label();
      this.lblThread = new System.Windows.Forms.Label();
      this.txtThreadId = new System.Windows.Forms.TextBox();
      this.chkEnableTime = new System.Windows.Forms.CheckBox();
      this.btnExecuteQuery = new System.Windows.Forms.Button();
      this.btnLoadQuery = new System.Windows.Forms.Button();
      this.btnSaveQuery = new System.Windows.Forms.Button();
      this.cmbThreadOperator = new System.Windows.Forms.ComboBox();
      this.cmbChannelOperator = new System.Windows.Forms.ComboBox();
      this.cmbMessageOperator = new System.Windows.Forms.ComboBox();
      this.cmbLevelOperator = new System.Windows.Forms.ComboBox();
      this.lblStatus = new System.Windows.Forms.Label();
      this.lblExecTime = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.txtTopRecords = new System.Windows.Forms.TextBox();
      this.label5 = new System.Windows.Forms.Label();
      this.progressBar = new System.Windows.Forms.ProgressBar();
      this.mainMenu.SuspendLayout();
      this.contextMenuTabPage.SuspendLayout();
      ( (System.ComponentModel.ISupportInitialize)( this.dgvResult ) ).BeginInit();
      this.SuspendLayout();
      // 
      // mainMenu
      // 
      this.mainMenu.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.menuItem1} );
      this.mainMenu.Location = new System.Drawing.Point( 0, 4 );
      this.mainMenu.Name = "mainMenu";
      this.mainMenu.Size = new System.Drawing.Size( 832, 24 );
      this.mainMenu.TabIndex = 1;
      this.mainMenu.Visible = false;
      // 
      // menuItem1
      // 
      this.menuItem1.Name = "menuItem1";
      this.menuItem1.Size = new System.Drawing.Size( 12, 20 );
      // 
      // menuItem2
      // 
      this.menuItem2.Name = "menuItem2";
      this.menuItem2.Size = new System.Drawing.Size( 32, 19 );
      // 
      // menuItemCheckTest
      // 
      this.menuItemCheckTest.Name = "menuItemCheckTest";
      this.menuItemCheckTest.Size = new System.Drawing.Size( 132, 22 );
      this.menuItemCheckTest.Text = "Check Test";
      this.menuItemCheckTest.Click += new System.EventHandler( this.menuItemCheckTest_Click );
      // 
      // contextMenuTabPage
      // 
      this.contextMenuTabPage.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.menuItemClose} );
      this.contextMenuTabPage.Name = "contextMenuTabPage";
      this.contextMenuTabPage.Size = new System.Drawing.Size( 104, 26 );
      // 
      // menuItemClose
      // 
      this.menuItemClose.Name = "menuItemClose";
      this.menuItemClose.Size = new System.Drawing.Size( 103, 22 );
      this.menuItemClose.Text = "Close";
      this.menuItemClose.Click += new System.EventHandler( this.menuItemClose_Click );
      // 
      // dgvResult
      // 
      this.dgvResult.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.dgvResult.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgvResult.Location = new System.Drawing.Point( 3, 188 );
      this.dgvResult.Name = "dgvResult";
      this.dgvResult.Size = new System.Drawing.Size( 891, 519 );
      this.dgvResult.TabIndex = 2;
      // 
      // txtCurrentQuery
      // 
      this.txtCurrentQuery.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.txtCurrentQuery.Font = new System.Drawing.Font( "Lucida Console", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 134 ) ) );
      this.txtCurrentQuery.Location = new System.Drawing.Point( 538, 28 );
      this.txtCurrentQuery.Name = "txtCurrentQuery";
      this.txtCurrentQuery.Size = new System.Drawing.Size( 356, 72 );
      this.txtCurrentQuery.TabIndex = 3;
      this.txtCurrentQuery.Text = "";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 3, 4 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 32, 15 );
      this.label1.TabIndex = 5;
      this.label1.Text = "file : ";
      // 
      // lblCurrentFile
      // 
      this.lblCurrentFile.AutoSize = true;
      this.lblCurrentFile.Location = new System.Drawing.Point( 31, 4 );
      this.lblCurrentFile.Name = "lblCurrentFile";
      this.lblCurrentFile.Size = new System.Drawing.Size( 99, 15 );
      this.lblCurrentFile.TabIndex = 6;
      this.lblCurrentFile.Text = "currentFileName";
      // 
      // btnApplyFilter
      // 
      this.btnApplyFilter.Location = new System.Drawing.Point( 345, 28 );
      this.btnApplyFilter.Name = "btnApplyFilter";
      this.btnApplyFilter.Size = new System.Drawing.Size( 129, 32 );
      this.btnApplyFilter.TabIndex = 4;
      this.btnApplyFilter.Text = "Apply filter";
      this.btnApplyFilter.UseVisualStyleBackColor = true;
      this.btnApplyFilter.Click += new System.EventHandler( this.btnApplyFilter_Click );
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 114, 57 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 32, 15 );
      this.label2.TabIndex = 31;
      this.label2.Text = "from";
      // 
      // btnClearFilter
      // 
      this.btnClearFilter.Location = new System.Drawing.Point( 345, 71 );
      this.btnClearFilter.Name = "btnClearFilter";
      this.btnClearFilter.Size = new System.Drawing.Size( 129, 32 );
      this.btnClearFilter.TabIndex = 29;
      this.btnClearFilter.Text = "Clear filter";
      this.btnClearFilter.UseVisualStyleBackColor = true;
      this.btnClearFilter.Click += new System.EventHandler( this.btnClearFilter_Click );
      // 
      // txtMessage
      // 
      this.txtMessage.Location = new System.Drawing.Point( 178, 138 );
      this.txtMessage.Name = "txtMessage";
      this.txtMessage.Size = new System.Drawing.Size( 296, 21 );
      this.txtMessage.TabIndex = 28;
      // 
      // cmbLogLevel
      // 
      this.cmbLogLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cmbLogLevel.FormattingEnabled = true;
      this.cmbLogLevel.Location = new System.Drawing.Point( 178, 109 );
      this.cmbLogLevel.Name = "cmbLogLevel";
      this.cmbLogLevel.Size = new System.Drawing.Size( 155, 23 );
      this.cmbLogLevel.TabIndex = 27;
      // 
      // dateTo
      // 
      this.dateTo.Format = System.Windows.Forms.DateTimePickerFormat.Time;
      this.dateTo.Location = new System.Drawing.Point( 262, 55 );
      this.dateTo.Name = "dateTo";
      this.dateTo.ShowUpDown = true;
      this.dateTo.Size = new System.Drawing.Size( 71, 21 );
      this.dateTo.TabIndex = 26;
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point( 239, 57 );
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size( 17, 15 );
      this.label3.TabIndex = 25;
      this.label3.Text = "to";
      // 
      // dateFrom
      // 
      this.dateFrom.Format = System.Windows.Forms.DateTimePickerFormat.Time;
      this.dateFrom.Location = new System.Drawing.Point( 152, 55 );
      this.dateFrom.Name = "dateFrom";
      this.dateFrom.ShowUpDown = true;
      this.dateFrom.Size = new System.Drawing.Size( 71, 21 );
      this.dateFrom.TabIndex = 24;
      // 
      // txtChannel
      // 
      this.txtChannel.Location = new System.Drawing.Point( 178, 82 );
      this.txtChannel.Name = "txtChannel";
      this.txtChannel.Size = new System.Drawing.Size( 155, 21 );
      this.txtChannel.TabIndex = 23;
      // 
      // lblMessage
      // 
      this.lblMessage.AutoSize = true;
      this.lblMessage.Location = new System.Drawing.Point( 6, 141 );
      this.lblMessage.Name = "lblMessage";
      this.lblMessage.Size = new System.Drawing.Size( 58, 15 );
      this.lblMessage.TabIndex = 22;
      this.lblMessage.Text = "Message";
      // 
      // lblLogLevel
      // 
      this.lblLogLevel.AutoSize = true;
      this.lblLogLevel.Location = new System.Drawing.Point( 6, 112 );
      this.lblLogLevel.Name = "lblLogLevel";
      this.lblLogLevel.Size = new System.Drawing.Size( 57, 15 );
      this.lblLogLevel.TabIndex = 21;
      this.lblLogLevel.Text = "LogLevel";
      // 
      // lblChannel
      // 
      this.lblChannel.AutoSize = true;
      this.lblChannel.Location = new System.Drawing.Point( 6, 85 );
      this.lblChannel.Name = "lblChannel";
      this.lblChannel.Size = new System.Drawing.Size( 53, 15 );
      this.lblChannel.TabIndex = 20;
      this.lblChannel.Text = "Channel";
      // 
      // lblTime
      // 
      this.lblTime.AutoSize = true;
      this.lblTime.Location = new System.Drawing.Point( 6, 60 );
      this.lblTime.Name = "lblTime";
      this.lblTime.Size = new System.Drawing.Size( 69, 15 );
      this.lblTime.TabIndex = 19;
      this.lblTime.Text = "HH:MM:SS";
      // 
      // lblThread
      // 
      this.lblThread.AutoSize = true;
      this.lblThread.Location = new System.Drawing.Point( 6, 31 );
      this.lblThread.Name = "lblThread";
      this.lblThread.Size = new System.Drawing.Size( 56, 15 );
      this.lblThread.TabIndex = 17;
      this.lblThread.Text = "ThreadId";
      // 
      // txtThreadId
      // 
      this.txtThreadId.Location = new System.Drawing.Point( 178, 28 );
      this.txtThreadId.Name = "txtThreadId";
      this.txtThreadId.Size = new System.Drawing.Size( 155, 21 );
      this.txtThreadId.TabIndex = 18;
      // 
      // chkEnableTime
      // 
      this.chkEnableTime.AutoSize = true;
      this.chkEnableTime.Checked = true;
      this.chkEnableTime.CheckState = System.Windows.Forms.CheckState.Checked;
      this.chkEnableTime.Location = new System.Drawing.Point( 93, 58 );
      this.chkEnableTime.Name = "chkEnableTime";
      this.chkEnableTime.Size = new System.Drawing.Size( 15, 14 );
      this.chkEnableTime.TabIndex = 32;
      this.chkEnableTime.UseVisualStyleBackColor = true;
      this.chkEnableTime.CheckedChanged += new System.EventHandler( this.chkEnableTime_CheckedChanged );
      // 
      // btnExecuteQuery
      // 
      this.btnExecuteQuery.Location = new System.Drawing.Point( 538, 112 );
      this.btnExecuteQuery.Name = "btnExecuteQuery";
      this.btnExecuteQuery.Size = new System.Drawing.Size( 129, 32 );
      this.btnExecuteQuery.TabIndex = 34;
      this.btnExecuteQuery.Text = "Execute Query";
      this.btnExecuteQuery.UseVisualStyleBackColor = true;
      this.btnExecuteQuery.Click += new System.EventHandler( this.btnExecuteQuery_Click );
      // 
      // btnLoadQuery
      // 
      this.btnLoadQuery.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.btnLoadQuery.Location = new System.Drawing.Point( 819, 106 );
      this.btnLoadQuery.Name = "btnLoadQuery";
      this.btnLoadQuery.Size = new System.Drawing.Size( 75, 23 );
      this.btnLoadQuery.TabIndex = 35;
      this.btnLoadQuery.Text = "LoadQuery";
      this.btnLoadQuery.UseVisualStyleBackColor = true;
      this.btnLoadQuery.Visible = false;
      this.btnLoadQuery.Click += new System.EventHandler( this.btnLoadQuery_Click );
      // 
      // btnSaveQuery
      // 
      this.btnSaveQuery.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.btnSaveQuery.Location = new System.Drawing.Point( 738, 106 );
      this.btnSaveQuery.Name = "btnSaveQuery";
      this.btnSaveQuery.Size = new System.Drawing.Size( 75, 23 );
      this.btnSaveQuery.TabIndex = 36;
      this.btnSaveQuery.Text = "SaveQuery";
      this.btnSaveQuery.UseVisualStyleBackColor = true;
      this.btnSaveQuery.Visible = false;
      this.btnSaveQuery.Click += new System.EventHandler( this.btnSaveQuery_Click );
      // 
      // cmbThreadOperator
      // 
      this.cmbThreadOperator.FormattingEnabled = true;
      this.cmbThreadOperator.Location = new System.Drawing.Point( 93, 28 );
      this.cmbThreadOperator.Name = "cmbThreadOperator";
      this.cmbThreadOperator.Size = new System.Drawing.Size( 83, 23 );
      this.cmbThreadOperator.TabIndex = 37;
      // 
      // cmbChannelOperator
      // 
      this.cmbChannelOperator.FormattingEnabled = true;
      this.cmbChannelOperator.Location = new System.Drawing.Point( 93, 82 );
      this.cmbChannelOperator.Name = "cmbChannelOperator";
      this.cmbChannelOperator.Size = new System.Drawing.Size( 83, 23 );
      this.cmbChannelOperator.TabIndex = 38;
      // 
      // cmbMessageOperator
      // 
      this.cmbMessageOperator.FormattingEnabled = true;
      this.cmbMessageOperator.Location = new System.Drawing.Point( 93, 138 );
      this.cmbMessageOperator.Name = "cmbMessageOperator";
      this.cmbMessageOperator.Size = new System.Drawing.Size( 83, 23 );
      this.cmbMessageOperator.TabIndex = 39;
      // 
      // cmbLevelOperator
      // 
      this.cmbLevelOperator.FormattingEnabled = true;
      this.cmbLevelOperator.Location = new System.Drawing.Point( 93, 109 );
      this.cmbLevelOperator.Name = "cmbLevelOperator";
      this.cmbLevelOperator.Size = new System.Drawing.Size( 37, 23 );
      this.cmbLevelOperator.TabIndex = 40;
      this.cmbLevelOperator.Visible = false;
      // 
      // lblStatus
      // 
      this.lblStatus.AutoSize = true;
      this.lblStatus.Font = new System.Drawing.Font( "Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 134 ) ) );
      this.lblStatus.Location = new System.Drawing.Point( 6, 170 );
      this.lblStatus.Name = "lblStatus";
      this.lblStatus.Size = new System.Drawing.Size( 0, 15 );
      this.lblStatus.TabIndex = 42;
      this.lblStatus.UseMnemonic = false;
      // 
      // lblExecTime
      // 
      this.lblExecTime.AutoSize = true;
      this.lblExecTime.Location = new System.Drawing.Point( 342, 4 );
      this.lblExecTime.Name = "lblExecTime";
      this.lblExecTime.Size = new System.Drawing.Size( 0, 15 );
      this.lblExecTime.TabIndex = 43;
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point( 352, 112 );
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size( 28, 15 );
      this.label4.TabIndex = 44;
      this.label4.Text = "Top";
      // 
      // txtTopRecords
      // 
      this.txtTopRecords.Location = new System.Drawing.Point( 386, 109 );
      this.txtTopRecords.Name = "txtTopRecords";
      this.txtTopRecords.Size = new System.Drawing.Size( 88, 21 );
      this.txtTopRecords.TabIndex = 45;
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point( 151, 112 );
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size( 21, 15 );
      this.label5.TabIndex = 46;
      this.label5.Text = ">=";
      // 
      // progressBar
      // 
      this.progressBar.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.progressBar.Location = new System.Drawing.Point( 3, 162 );
      this.progressBar.Name = "progressBar";
      this.progressBar.Size = new System.Drawing.Size( 891, 23 );
      this.progressBar.TabIndex = 47;
      this.progressBar.Visible = false;
      // 
      // DummyDoc
      // 
      this.ClientSize = new System.Drawing.Size( 897, 707 );
      this.Controls.Add( this.txtTopRecords );
      this.Controls.Add( this.label5 );
      this.Controls.Add( this.progressBar );
      this.Controls.Add( this.label4 );
      this.Controls.Add( this.lblExecTime );
      this.Controls.Add( this.lblStatus );
      this.Controls.Add( this.cmbLevelOperator );
      this.Controls.Add( this.cmbMessageOperator );
      this.Controls.Add( this.cmbChannelOperator );
      this.Controls.Add( this.cmbThreadOperator );
      this.Controls.Add( this.btnSaveQuery );
      this.Controls.Add( this.btnLoadQuery );
      this.Controls.Add( this.btnExecuteQuery );
      this.Controls.Add( this.chkEnableTime );
      this.Controls.Add( this.txtMessage );
      this.Controls.Add( this.label2 );
      this.Controls.Add( this.btnClearFilter );
      this.Controls.Add( this.cmbLogLevel );
      this.Controls.Add( this.txtChannel );
      this.Controls.Add( this.dateTo );
      this.Controls.Add( this.label3 );
      this.Controls.Add( this.dateFrom );
      this.Controls.Add( this.lblMessage );
      this.Controls.Add( this.lblLogLevel );
      this.Controls.Add( this.lblChannel );
      this.Controls.Add( this.lblTime );
      this.Controls.Add( this.lblThread );
      this.Controls.Add( this.txtThreadId );
      this.Controls.Add( this.lblCurrentFile );
      this.Controls.Add( this.label1 );
      this.Controls.Add( this.mainMenu );
      this.Controls.Add( this.dgvResult );
      this.Controls.Add( this.btnApplyFilter );
      this.Controls.Add( this.txtCurrentQuery );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 134 ) ) );
      this.Icon = ( (System.Drawing.Icon)( resources.GetObject( "$this.Icon" ) ) );
      this.MainMenuStrip = this.mainMenu;
      this.Name = "DummyDoc";
      this.Padding = new System.Windows.Forms.Padding( 0, 4, 0, 0 );
      this.TabPageContextMenuStrip = this.contextMenuTabPage;
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.DummyDoc_FormClosing );
      this.mainMenu.ResumeLayout( false );
      this.mainMenu.PerformLayout();
      this.contextMenuTabPage.ResumeLayout( false );
      ( (System.ComponentModel.ISupportInitialize)( this.dgvResult ) ).EndInit();
      this.ResumeLayout( false );
      this.PerformLayout();

		}
		#endregion

        private System.Windows.Forms.MenuStrip mainMenu;
		private System.Windows.Forms.ToolStripMenuItem menuItem1;
		private System.Windows.Forms.ToolStripMenuItem menuItem2;
		private System.Windows.Forms.ContextMenuStrip contextMenuTabPage;
    private System.Windows.Forms.ToolStripMenuItem menuItemClose;
		private System.Windows.Forms.ToolStripMenuItem menuItemCheckTest;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.DataGridView dgvResult;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblCurrentFile;
        private System.Windows.Forms.Button btnApplyFilter;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnClearFilter;
        private System.Windows.Forms.TextBox txtMessage;
        private System.Windows.Forms.ComboBox cmbLogLevel;
        private System.Windows.Forms.DateTimePicker dateTo;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker dateFrom;
        private System.Windows.Forms.TextBox txtChannel;
        private System.Windows.Forms.Label lblMessage;
        private System.Windows.Forms.Label lblLogLevel;
        private System.Windows.Forms.Label lblChannel;
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Label lblThread;
        private System.Windows.Forms.TextBox txtThreadId;
        private System.Windows.Forms.CheckBox chkEnableTime;
        private System.Windows.Forms.Button btnExecuteQuery;
        private System.Windows.Forms.Button btnLoadQuery;
        private System.Windows.Forms.Button btnSaveQuery;
        private System.Windows.Forms.ComboBox cmbThreadOperator;
        private System.Windows.Forms.ComboBox cmbChannelOperator;
        private System.Windows.Forms.ComboBox cmbMessageOperator;
        private System.Windows.Forms.ComboBox cmbLevelOperator;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Label lblExecTime;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtTopRecords;
        private System.Windows.Forms.Label label5;
        public System.Windows.Forms.RichTextBox txtCurrentQuery;
        private System.Windows.Forms.ProgressBar progressBar;
    }
}