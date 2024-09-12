namespace EditorPlugins.Commands.UndoRedo
{
  partial class BrowseUndoRedoForm
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
      this.lstHistory = new System.Windows.Forms.ListBox();
      this.statusStrip1 = new System.Windows.Forms.StatusStrip();
      this.toolStripStatusLabelTotal = new System.Windows.Forms.ToolStripStatusLabel();
      this.lblStstistic = new System.Windows.Forms.ToolStripStatusLabel();
      this.tabsContainer = new System.Windows.Forms.TabControl();
      this.tabHistory = new System.Windows.Forms.TabPage();
      this.tabTrace = new System.Windows.Forms.TabPage();
      this.lstUndoRedoTrace = new System.Windows.Forms.ListBox();
      this.btnClearTrace = new System.Windows.Forms.Button();
      this.statusStrip1.SuspendLayout();
      this.tabsContainer.SuspendLayout();
      this.tabHistory.SuspendLayout();
      this.tabTrace.SuspendLayout();
      this.SuspendLayout();
      // 
      // lstHistory
      // 
      this.lstHistory.Dock = System.Windows.Forms.DockStyle.Fill;
      this.lstHistory.FormattingEnabled = true;
      this.lstHistory.IntegralHeight = false;
      this.lstHistory.Location = new System.Drawing.Point( 3, 3 );
      this.lstHistory.Name = "lstHistory";
      this.lstHistory.Size = new System.Drawing.Size( 324, 305 );
      this.lstHistory.TabIndex = 0;
      // 
      // statusStrip1
      // 
      this.statusStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabelTotal,
            this.lblStstistic} );
      this.statusStrip1.Location = new System.Drawing.Point( 0, 367 );
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new System.Drawing.Size( 292, 22 );
      this.statusStrip1.TabIndex = 2;
      this.statusStrip1.Text = "statusStrip1";
      // 
      // toolStripStatusLabelTotal
      // 
      this.toolStripStatusLabelTotal.Name = "toolStripStatusLabelTotal";
      this.toolStripStatusLabelTotal.Size = new System.Drawing.Size( 38, 17 );
      this.toolStripStatusLabelTotal.Text = "Total: ";
      // 
      // lblStstistic
      // 
      this.lblStstistic.Name = "lblStstistic";
      this.lblStstistic.Size = new System.Drawing.Size( 25, 17 );
      this.lblStstistic.Text = "xxx";
      // 
      // tabsContainer
      // 
      this.tabsContainer.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.tabsContainer.Controls.Add( this.tabHistory );
      this.tabsContainer.Controls.Add( this.tabTrace );
      this.tabsContainer.Location = new System.Drawing.Point( 3, 2 );
      this.tabsContainer.Name = "tabsContainer";
      this.tabsContainer.SelectedIndex = 0;
      this.tabsContainer.Size = new System.Drawing.Size( 286, 362 );
      this.tabsContainer.TabIndex = 3;
      this.tabsContainer.SelectedIndexChanged += new System.EventHandler( this.OnSelectedTabChanged );
      // 
      // tabHistory
      // 
      this.tabHistory.Controls.Add( this.lstHistory );
      this.tabHistory.Location = new System.Drawing.Point( 4, 22 );
      this.tabHistory.Name = "tabHistory";
      this.tabHistory.Padding = new System.Windows.Forms.Padding( 3 );
      this.tabHistory.Size = new System.Drawing.Size( 330, 311 );
      this.tabHistory.TabIndex = 0;
      this.tabHistory.Text = "History";
      this.tabHistory.UseVisualStyleBackColor = true;
      // 
      // tabTrace
      // 
      this.tabTrace.Controls.Add( this.btnClearTrace );
      this.tabTrace.Controls.Add( this.lstUndoRedoTrace );
      this.tabTrace.Location = new System.Drawing.Point( 4, 22 );
      this.tabTrace.Name = "tabTrace";
      this.tabTrace.Padding = new System.Windows.Forms.Padding( 3 );
      this.tabTrace.Size = new System.Drawing.Size( 278, 336 );
      this.tabTrace.TabIndex = 1;
      this.tabTrace.Text = "Trace";
      this.tabTrace.UseVisualStyleBackColor = true;
      // 
      // lstUndoRedoTrace
      // 
      this.lstUndoRedoTrace.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.lstUndoRedoTrace.FormattingEnabled = true;
      this.lstUndoRedoTrace.IntegralHeight = false;
      this.lstUndoRedoTrace.Location = new System.Drawing.Point( 3, 3 );
      this.lstUndoRedoTrace.Name = "lstUndoRedoTrace";
      this.lstUndoRedoTrace.Size = new System.Drawing.Size( 272, 298 );
      this.lstUndoRedoTrace.TabIndex = 0;
      // 
      // btnClearTrace
      // 
      this.btnClearTrace.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.btnClearTrace.Location = new System.Drawing.Point( 197, 307 );
      this.btnClearTrace.Name = "btnClearTrace";
      this.btnClearTrace.Size = new System.Drawing.Size( 75, 23 );
      this.btnClearTrace.TabIndex = 1;
      this.btnClearTrace.Text = "Clear";
      this.btnClearTrace.UseVisualStyleBackColor = true;
      this.btnClearTrace.Click += new System.EventHandler( this.btnClearTrace_Click );
      // 
      // BrowseUndoRedoForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 292, 389 );
      this.Controls.Add( this.tabsContainer );
      this.Controls.Add( this.statusStrip1 );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.MinimumSize = new System.Drawing.Size( 300, 300 );
      this.Name = "BrowseUndoRedoForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "UndoRedo Operations";
      this.Load += new System.EventHandler( this.BrowseUndoRedoForm_Load );
      this.statusStrip1.ResumeLayout( false );
      this.statusStrip1.PerformLayout();
      this.tabsContainer.ResumeLayout( false );
      this.tabHistory.ResumeLayout( false );
      this.tabTrace.ResumeLayout( false );
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ListBox lstHistory;
    private System.Windows.Forms.StatusStrip statusStrip1;
    private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelTotal;
    private System.Windows.Forms.TabControl tabsContainer;
    private System.Windows.Forms.TabPage tabHistory;
    private System.Windows.Forms.TabPage tabTrace;
    private System.Windows.Forms.ListBox lstUndoRedoTrace;
    private System.Windows.Forms.ToolStripStatusLabel lblStstistic;
    private System.Windows.Forms.Button btnClearTrace;
  }
}