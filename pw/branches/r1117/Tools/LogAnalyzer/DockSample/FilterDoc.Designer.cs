namespace DockSample
{
  partial class FilterDoc
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
      this.progressBar = new System.Windows.Forms.ProgressBar();
      this.txtTopRecords = new System.Windows.Forms.TextBox();
      this.label5 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.lblExecTime = new System.Windows.Forms.Label();
      this.lblStatus = new System.Windows.Forms.Label();
      this.cmbLevelOperator = new System.Windows.Forms.ComboBox();
      this.cmbChannelOperator = new System.Windows.Forms.ComboBox();
      this.cmbThreadOperator = new System.Windows.Forms.ComboBox();
      this.chkEnableTime = new System.Windows.Forms.CheckBox();
      this.txtMessage = new System.Windows.Forms.TextBox();
      this.label2 = new System.Windows.Forms.Label();
      this.btnClearFilter = new System.Windows.Forms.Button();
      this.cmbLogLevel = new System.Windows.Forms.ComboBox();
      this.txtChannel = new System.Windows.Forms.TextBox();
      this.dateTo = new System.Windows.Forms.DateTimePicker();
      this.label3 = new System.Windows.Forms.Label();
      this.dateFrom = new System.Windows.Forms.DateTimePicker();
      this.lblMessage = new System.Windows.Forms.Label();
      this.lblLogLevel = new System.Windows.Forms.Label();
      this.lblChannel = new System.Windows.Forms.Label();
      this.lblTime = new System.Windows.Forms.Label();
      this.lblThread = new System.Windows.Forms.Label();
      this.txtThreadId = new System.Windows.Forms.TextBox();
      this.lblCurrentFile = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.btnApplyFilter = new System.Windows.Forms.Button();
      this.dgvResult = new System.Windows.Forms.DataGridView();
      this.cmbMessageOperator = new System.Windows.Forms.ComboBox();
      ( (System.ComponentModel.ISupportInitialize)( this.dgvResult ) ).BeginInit();
      this.SuspendLayout();
      // 
      // progressBar
      // 
      this.progressBar.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.progressBar.Location = new System.Drawing.Point( 1, 167 );
      this.progressBar.Name = "progressBar";
      this.progressBar.Size = new System.Drawing.Size( 891, 23 );
      this.progressBar.TabIndex = 75;
      this.progressBar.Visible = false;
      // 
      // txtTopRecords
      // 
      this.txtTopRecords.Location = new System.Drawing.Point( 353, 114 );
      this.txtTopRecords.Name = "txtTopRecords";
      this.txtTopRecords.Size = new System.Drawing.Size( 88, 20 );
      this.txtTopRecords.TabIndex = 73;
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point( 118, 117 );
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size( 19, 13 );
      this.label5.TabIndex = 74;
      this.label5.Text = ">=";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point( 319, 117 );
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size( 26, 13 );
      this.label4.TabIndex = 72;
      this.label4.Text = "Top";
      // 
      // lblExecTime
      // 
      this.lblExecTime.AutoSize = true;
      this.lblExecTime.Location = new System.Drawing.Point( 340, 9 );
      this.lblExecTime.Name = "lblExecTime";
      this.lblExecTime.Size = new System.Drawing.Size( 0, 13 );
      this.lblExecTime.TabIndex = 71;
      // 
      // lblStatus
      // 
      this.lblStatus.AutoSize = true;
      this.lblStatus.Font = new System.Drawing.Font( "Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 134 ) ) );
      this.lblStatus.Location = new System.Drawing.Point( 4, 175 );
      this.lblStatus.Name = "lblStatus";
      this.lblStatus.Size = new System.Drawing.Size( 0, 15 );
      this.lblStatus.TabIndex = 70;
      this.lblStatus.UseMnemonic = false;
      // 
      // cmbLevelOperator
      // 
      this.cmbLevelOperator.FormattingEnabled = true;
      this.cmbLevelOperator.Location = new System.Drawing.Point( 60, 114 );
      this.cmbLevelOperator.Name = "cmbLevelOperator";
      this.cmbLevelOperator.Size = new System.Drawing.Size( 37, 21 );
      this.cmbLevelOperator.TabIndex = 69;
      this.cmbLevelOperator.Visible = false;
      // 
      // cmbChannelOperator
      // 
      this.cmbChannelOperator.FormattingEnabled = true;
      this.cmbChannelOperator.Location = new System.Drawing.Point( 60, 87 );
      this.cmbChannelOperator.Name = "cmbChannelOperator";
      this.cmbChannelOperator.Size = new System.Drawing.Size( 83, 21 );
      this.cmbChannelOperator.TabIndex = 67;
      // 
      // cmbThreadOperator
      // 
      this.cmbThreadOperator.FormattingEnabled = true;
      this.cmbThreadOperator.Location = new System.Drawing.Point( 60, 33 );
      this.cmbThreadOperator.Name = "cmbThreadOperator";
      this.cmbThreadOperator.Size = new System.Drawing.Size( 83, 21 );
      this.cmbThreadOperator.TabIndex = 66;
      // 
      // chkEnableTime
      // 
      this.chkEnableTime.AutoSize = true;
      this.chkEnableTime.Checked = true;
      this.chkEnableTime.CheckState = System.Windows.Forms.CheckState.Checked;
      this.chkEnableTime.Location = new System.Drawing.Point( 65, 62 );
      this.chkEnableTime.Name = "chkEnableTime";
      this.chkEnableTime.Size = new System.Drawing.Size( 15, 14 );
      this.chkEnableTime.TabIndex = 65;
      this.chkEnableTime.UseVisualStyleBackColor = true;
      // 
      // txtMessage
      // 
      this.txtMessage.Location = new System.Drawing.Point( 139, 143 );
      this.txtMessage.Name = "txtMessage";
      this.txtMessage.Size = new System.Drawing.Size( 302, 20 );
      this.txtMessage.TabIndex = 62;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 86, 62 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 27, 13 );
      this.label2.TabIndex = 64;
      this.label2.Text = "from";
      // 
      // btnClearFilter
      // 
      this.btnClearFilter.Location = new System.Drawing.Point( 312, 76 );
      this.btnClearFilter.Name = "btnClearFilter";
      this.btnClearFilter.Size = new System.Drawing.Size( 129, 32 );
      this.btnClearFilter.TabIndex = 63;
      this.btnClearFilter.Text = "Clear filter";
      this.btnClearFilter.UseVisualStyleBackColor = true;
      this.btnClearFilter.Click += new System.EventHandler( this.btnClearFilter_Click );
      // 
      // cmbLogLevel
      // 
      this.cmbLogLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cmbLogLevel.FormattingEnabled = true;
      this.cmbLogLevel.Location = new System.Drawing.Point( 145, 114 );
      this.cmbLogLevel.Name = "cmbLogLevel";
      this.cmbLogLevel.Size = new System.Drawing.Size( 155, 21 );
      this.cmbLogLevel.TabIndex = 61;
      // 
      // txtChannel
      // 
      this.txtChannel.Location = new System.Drawing.Point( 145, 87 );
      this.txtChannel.Name = "txtChannel";
      this.txtChannel.Size = new System.Drawing.Size( 155, 20 );
      this.txtChannel.TabIndex = 57;
      // 
      // dateTo
      // 
      this.dateTo.Format = System.Windows.Forms.DateTimePickerFormat.Time;
      this.dateTo.Location = new System.Drawing.Point( 229, 60 );
      this.dateTo.Name = "dateTo";
      this.dateTo.ShowUpDown = true;
      this.dateTo.Size = new System.Drawing.Size( 71, 20 );
      this.dateTo.TabIndex = 60;
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point( 206, 62 );
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size( 16, 13 );
      this.label3.TabIndex = 59;
      this.label3.Text = "to";
      // 
      // dateFrom
      // 
      this.dateFrom.Format = System.Windows.Forms.DateTimePickerFormat.Time;
      this.dateFrom.Location = new System.Drawing.Point( 119, 60 );
      this.dateFrom.Name = "dateFrom";
      this.dateFrom.ShowUpDown = true;
      this.dateFrom.Size = new System.Drawing.Size( 71, 20 );
      this.dateFrom.TabIndex = 58;
      // 
      // lblMessage
      // 
      this.lblMessage.AutoSize = true;
      this.lblMessage.Location = new System.Drawing.Point( 4, 146 );
      this.lblMessage.Name = "lblMessage";
      this.lblMessage.Size = new System.Drawing.Size( 50, 13 );
      this.lblMessage.TabIndex = 56;
      this.lblMessage.Text = "Message";
      // 
      // lblLogLevel
      // 
      this.lblLogLevel.AutoSize = true;
      this.lblLogLevel.Location = new System.Drawing.Point( 4, 117 );
      this.lblLogLevel.Name = "lblLogLevel";
      this.lblLogLevel.Size = new System.Drawing.Size( 51, 13 );
      this.lblLogLevel.TabIndex = 55;
      this.lblLogLevel.Text = "LogLevel";
      // 
      // lblChannel
      // 
      this.lblChannel.AutoSize = true;
      this.lblChannel.Location = new System.Drawing.Point( 4, 90 );
      this.lblChannel.Name = "lblChannel";
      this.lblChannel.Size = new System.Drawing.Size( 46, 13 );
      this.lblChannel.TabIndex = 54;
      this.lblChannel.Text = "Channel";
      // 
      // lblTime
      // 
      this.lblTime.AutoSize = true;
      this.lblTime.Location = new System.Drawing.Point( 4, 62 );
      this.lblTime.Name = "lblTime";
      this.lblTime.Size = new System.Drawing.Size( 61, 13 );
      this.lblTime.TabIndex = 53;
      this.lblTime.Text = "HH:MM:SS";
      // 
      // lblThread
      // 
      this.lblThread.AutoSize = true;
      this.lblThread.Location = new System.Drawing.Point( 4, 36 );
      this.lblThread.Name = "lblThread";
      this.lblThread.Size = new System.Drawing.Size( 50, 13 );
      this.lblThread.TabIndex = 51;
      this.lblThread.Text = "ThreadId";
      // 
      // txtThreadId
      // 
      this.txtThreadId.Location = new System.Drawing.Point( 145, 33 );
      this.txtThreadId.Name = "txtThreadId";
      this.txtThreadId.Size = new System.Drawing.Size( 155, 20 );
      this.txtThreadId.TabIndex = 52;
      // 
      // lblCurrentFile
      // 
      this.lblCurrentFile.AutoSize = true;
      this.lblCurrentFile.Location = new System.Drawing.Point( 29, 9 );
      this.lblCurrentFile.Name = "lblCurrentFile";
      this.lblCurrentFile.Size = new System.Drawing.Size( 84, 13 );
      this.lblCurrentFile.TabIndex = 50;
      this.lblCurrentFile.Text = "currentFileName";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 1, 9 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 29, 13 );
      this.label1.TabIndex = 49;
      this.label1.Text = "file : ";
      // 
      // btnApplyFilter
      // 
      this.btnApplyFilter.Location = new System.Drawing.Point( 312, 33 );
      this.btnApplyFilter.Name = "btnApplyFilter";
      this.btnApplyFilter.Size = new System.Drawing.Size( 129, 32 );
      this.btnApplyFilter.TabIndex = 48;
      this.btnApplyFilter.Text = "Apply filter";
      this.btnApplyFilter.UseVisualStyleBackColor = true;
      this.btnApplyFilter.Click += new System.EventHandler( this.btnApplyFilter_Click );
      // 
      // dgvResult
      // 
      this.dgvResult.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.dgvResult.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgvResult.Location = new System.Drawing.Point( 1, 193 );
      this.dgvResult.Name = "dgvResult";
      this.dgvResult.Size = new System.Drawing.Size( 891, 445 );
      this.dgvResult.TabIndex = 76;
      // 
      // cmbMessageOperator
      // 
      this.cmbMessageOperator.FormattingEnabled = true;
      this.cmbMessageOperator.Location = new System.Drawing.Point( 60, 143 );
      this.cmbMessageOperator.Name = "cmbMessageOperator";
      this.cmbMessageOperator.Size = new System.Drawing.Size( 77, 21 );
      this.cmbMessageOperator.TabIndex = 77;
      // 
      // FilterDoc
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 893, 640 );
      this.Controls.Add( this.cmbMessageOperator );
      this.Controls.Add( this.dgvResult );
      this.Controls.Add( this.progressBar );
      this.Controls.Add( this.txtTopRecords );
      this.Controls.Add( this.label5 );
      this.Controls.Add( this.label4 );
      this.Controls.Add( this.lblExecTime );
      this.Controls.Add( this.lblStatus );
      this.Controls.Add( this.cmbLevelOperator );
      this.Controls.Add( this.cmbChannelOperator );
      this.Controls.Add( this.cmbThreadOperator );
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
      this.Controls.Add( this.btnApplyFilter );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.Name = "FilterDoc";
      this.Text = "FilterDoc";
      ( (System.ComponentModel.ISupportInitialize)( this.dgvResult ) ).EndInit();
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ProgressBar progressBar;
    private System.Windows.Forms.TextBox txtTopRecords;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label lblExecTime;
    private System.Windows.Forms.Label lblStatus;
    private System.Windows.Forms.ComboBox cmbLevelOperator;
    private System.Windows.Forms.ComboBox cmbChannelOperator;
    private System.Windows.Forms.ComboBox cmbThreadOperator;
    private System.Windows.Forms.CheckBox chkEnableTime;
    private System.Windows.Forms.TextBox txtMessage;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Button btnClearFilter;
    private System.Windows.Forms.ComboBox cmbLogLevel;
    private System.Windows.Forms.TextBox txtChannel;
    private System.Windows.Forms.DateTimePicker dateTo;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.DateTimePicker dateFrom;
    private System.Windows.Forms.Label lblMessage;
    private System.Windows.Forms.Label lblLogLevel;
    private System.Windows.Forms.Label lblChannel;
    private System.Windows.Forms.Label lblTime;
    private System.Windows.Forms.Label lblThread;
    private System.Windows.Forms.TextBox txtThreadId;
    private System.Windows.Forms.Label lblCurrentFile;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button btnApplyFilter;
    private System.Windows.Forms.DataGridView dgvResult;
    private System.Windows.Forms.ComboBox cmbMessageOperator;
  }
}