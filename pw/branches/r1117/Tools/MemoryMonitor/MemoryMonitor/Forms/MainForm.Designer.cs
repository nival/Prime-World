namespace MemoryMonitor.Forms
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
      this.menuStrip1 = new System.Windows.Forms.MenuStrip();
      this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.openBinaryDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.tsmiOpenModules = new System.Windows.Forms.ToolStripMenuItem();
      this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.tsmZoomOut = new System.Windows.Forms.ToolStripMenuItem();
      this.splitContainer1 = new System.Windows.Forms.SplitContainer();
      this.MemoryMapControl = new MemoryMonitor.Forms.MemoryMapControl();
      this.label2 = new System.Windows.Forms.Label();
      this.lbCallStack = new System.Windows.Forms.ListBox();
      this.bNextNEvents = new System.Windows.Forms.Button();
      this.bPrevNEvents = new System.Windows.Forms.Button();
      this.bNextEvent = new System.Windows.Forms.Button();
      this.bPrevEvent = new System.Windows.Forms.Button();
      this.bNextTime = new System.Windows.Forms.Button();
      this.bPrevTime = new System.Windows.Forms.Button();
      this.tbTime = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.lbSelectedAllocs = new System.Windows.Forms.ListBox();
      this.menuStrip1.SuspendLayout();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.SuspendLayout();
      // 
      // menuStrip1
      // 
      this.menuStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.tsmZoomOut} );
      this.menuStrip1.Location = new System.Drawing.Point( 0, 0 );
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new System.Drawing.Size( 876, 24 );
      this.menuStrip1.TabIndex = 2;
      this.menuStrip1.Text = "Main menu";
      // 
      // fileToolStripMenuItem
      // 
      this.fileToolStripMenuItem.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.openBinaryDataToolStripMenuItem,
            this.tsmiOpenModules,
            this.exitToolStripMenuItem} );
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new System.Drawing.Size( 35, 20 );
      this.fileToolStripMenuItem.Text = "File";
      // 
      // openBinaryDataToolStripMenuItem
      // 
      this.openBinaryDataToolStripMenuItem.Name = "openBinaryDataToolStripMenuItem";
      this.openBinaryDataToolStripMenuItem.Size = new System.Drawing.Size( 178, 22 );
      this.openBinaryDataToolStripMenuItem.Text = "Open binary data";
      this.openBinaryDataToolStripMenuItem.Click += new System.EventHandler( this.openBinaryDataToolStripMenuItem_Click );
      // 
      // tsmiOpenModules
      // 
      this.tsmiOpenModules.Name = "tsmiOpenModules";
      this.tsmiOpenModules.Size = new System.Drawing.Size( 178, 22 );
      this.tsmiOpenModules.Text = "Load module layout";
      this.tsmiOpenModules.Click += new System.EventHandler( this.tsmiOpenModules_Click );
      // 
      // exitToolStripMenuItem
      // 
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new System.Drawing.Size( 178, 22 );
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new System.EventHandler( this.exitToolStripMenuItem_Click );
      // 
      // tsmZoomOut
      // 
      this.tsmZoomOut.Name = "tsmZoomOut";
      this.tsmZoomOut.Size = new System.Drawing.Size( 66, 20 );
      this.tsmZoomOut.Text = "Zoom Out";
      this.tsmZoomOut.Click += new System.EventHandler( this.tsmZoomOut_Click );
      // 
      // splitContainer1
      // 
      this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
      this.splitContainer1.Location = new System.Drawing.Point( 0, 24 );
      this.splitContainer1.Name = "splitContainer1";
      this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
      // 
      // splitContainer1.Panel1
      // 
      this.splitContainer1.Panel1.Controls.Add( this.MemoryMapControl );
      // 
      // splitContainer1.Panel2
      // 
      this.splitContainer1.Panel2.Controls.Add( this.label2 );
      this.splitContainer1.Panel2.Controls.Add( this.lbCallStack );
      this.splitContainer1.Panel2.Controls.Add( this.bNextNEvents );
      this.splitContainer1.Panel2.Controls.Add( this.bPrevNEvents );
      this.splitContainer1.Panel2.Controls.Add( this.bNextEvent );
      this.splitContainer1.Panel2.Controls.Add( this.bPrevEvent );
      this.splitContainer1.Panel2.Controls.Add( this.bNextTime );
      this.splitContainer1.Panel2.Controls.Add( this.bPrevTime );
      this.splitContainer1.Panel2.Controls.Add( this.tbTime );
      this.splitContainer1.Panel2.Controls.Add( this.label1 );
      this.splitContainer1.Panel2.Controls.Add( this.lbSelectedAllocs );
      this.splitContainer1.Panel2.Margin = new System.Windows.Forms.Padding( 100 );
      this.splitContainer1.Size = new System.Drawing.Size( 876, 650 );
      this.splitContainer1.SplitterDistance = 518;
      this.splitContainer1.SplitterWidth = 1;
      this.splitContainer1.TabIndex = 1;
      // 
      // MemoryMapControl
      // 
      this.MemoryMapControl.AutoScroll = true;
      this.MemoryMapControl.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.MemoryMapControl.CellAreaMargin = 5;
      this.MemoryMapControl.CellGap = 2;
      this.MemoryMapControl.CellSize = 8;
      this.MemoryMapControl.Dock = System.Windows.Forms.DockStyle.Fill;
      this.MemoryMapControl.EmptyCellColor = System.Drawing.Color.LightGray;
      this.MemoryMapControl.FullCellColor = System.Drawing.Color.Blue;
      this.MemoryMapControl.Location = new System.Drawing.Point( 0, 0 );
      this.MemoryMapControl.Name = "MemoryMapControl";
      this.MemoryMapControl.NumberOfCells = ( (uint)( 4096u ) );
      this.MemoryMapControl.PartialCellColor = System.Drawing.Color.LightCoral;
      this.MemoryMapControl.Size = new System.Drawing.Size( 876, 518 );
      this.MemoryMapControl.TabIndex = 0;
      this.MemoryMapControl.TraceChanges = false;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 300, 2 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 58, 13 );
      this.label2.TabIndex = 11;
      this.label2.Text = "Call Stack:";
      // 
      // lbCallStack
      // 
      this.lbCallStack.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.lbCallStack.FormattingEnabled = true;
      this.lbCallStack.IntegralHeight = false;
      this.lbCallStack.Location = new System.Drawing.Point( 303, 18 );
      this.lbCallStack.Name = "lbCallStack";
      this.lbCallStack.Size = new System.Drawing.Size( 408, 110 );
      this.lbCallStack.TabIndex = 10;
      // 
      // bNextNEvents
      // 
      this.bNextNEvents.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.bNextNEvents.Location = new System.Drawing.Point( 798, 92 );
      this.bNextNEvents.Name = "bNextNEvents";
      this.bNextNEvents.Size = new System.Drawing.Size( 75, 23 );
      this.bNextNEvents.TabIndex = 9;
      this.bNextNEvents.Text = ">> 10 ev";
      this.bNextNEvents.UseVisualStyleBackColor = true;
      this.bNextNEvents.Click += new System.EventHandler( this.bNextNEvents_Click );
      // 
      // bPrevNEvents
      // 
      this.bPrevNEvents.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.bPrevNEvents.Location = new System.Drawing.Point( 717, 92 );
      this.bPrevNEvents.Name = "bPrevNEvents";
      this.bPrevNEvents.Size = new System.Drawing.Size( 75, 23 );
      this.bPrevNEvents.TabIndex = 8;
      this.bPrevNEvents.Text = "<< 10 ev";
      this.bPrevNEvents.UseVisualStyleBackColor = true;
      this.bPrevNEvents.Click += new System.EventHandler( this.bPrevNEvents_Click );
      // 
      // bNextEvent
      // 
      this.bNextEvent.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.bNextEvent.Location = new System.Drawing.Point( 798, 63 );
      this.bNextEvent.Name = "bNextEvent";
      this.bNextEvent.Size = new System.Drawing.Size( 75, 23 );
      this.bNextEvent.TabIndex = 7;
      this.bNextEvent.Text = ">> 1 ev";
      this.bNextEvent.UseVisualStyleBackColor = true;
      this.bNextEvent.Click += new System.EventHandler( this.bNextEvent_Click );
      // 
      // bPrevEvent
      // 
      this.bPrevEvent.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.bPrevEvent.Location = new System.Drawing.Point( 717, 63 );
      this.bPrevEvent.Name = "bPrevEvent";
      this.bPrevEvent.Size = new System.Drawing.Size( 75, 23 );
      this.bPrevEvent.TabIndex = 6;
      this.bPrevEvent.Text = "<< 1 ev";
      this.bPrevEvent.UseVisualStyleBackColor = true;
      this.bPrevEvent.Click += new System.EventHandler( this.bPrevEvent_Click );
      // 
      // bNextTime
      // 
      this.bNextTime.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.bNextTime.Location = new System.Drawing.Point( 798, 34 );
      this.bNextTime.Name = "bNextTime";
      this.bNextTime.Size = new System.Drawing.Size( 75, 23 );
      this.bNextTime.TabIndex = 5;
      this.bNextTime.Text = ">> 1 sec";
      this.bNextTime.UseVisualStyleBackColor = true;
      this.bNextTime.Click += new System.EventHandler( this.bNextTime_Click );
      // 
      // bPrevTime
      // 
      this.bPrevTime.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.bPrevTime.Location = new System.Drawing.Point( 717, 34 );
      this.bPrevTime.Name = "bPrevTime";
      this.bPrevTime.Size = new System.Drawing.Size( 75, 23 );
      this.bPrevTime.TabIndex = 4;
      this.bPrevTime.Text = "<< 1 sec";
      this.bPrevTime.UseVisualStyleBackColor = true;
      this.bPrevTime.Click += new System.EventHandler( this.bPrevTime_Click );
      // 
      // tbTime
      // 
      this.tbTime.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.tbTime.Location = new System.Drawing.Point( 739, 7 );
      this.tbTime.Name = "tbTime";
      this.tbTime.Size = new System.Drawing.Size( 100, 20 );
      this.tbTime.TabIndex = 3;
      this.tbTime.KeyDown += new System.Windows.Forms.KeyEventHandler( this.tbTime_KeyDown );
      this.tbTime.Leave += new System.EventHandler( this.tbTime_Leave );
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 3, 2 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 89, 13 );
      this.label1.TabIndex = 2;
      this.label1.Text = "Allocated Blocks:";
      // 
      // lbSelectedAllocs
      // 
      this.lbSelectedAllocs.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.lbSelectedAllocs.FormattingEnabled = true;
      this.lbSelectedAllocs.IntegralHeight = false;
      this.lbSelectedAllocs.Location = new System.Drawing.Point( 3, 18 );
      this.lbSelectedAllocs.Name = "lbSelectedAllocs";
      this.lbSelectedAllocs.Size = new System.Drawing.Size( 294, 110 );
      this.lbSelectedAllocs.TabIndex = 0;
      this.lbSelectedAllocs.SelectedIndexChanged += new System.EventHandler( this.lbSelectedAllocs_SelectedIndexChanged );
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 876, 674 );
      this.Controls.Add( this.splitContainer1 );
      this.Controls.Add( this.menuStrip1 );
      this.DoubleBuffered = true;
      this.MainMenuStrip = this.menuStrip1;
      this.Name = "MainForm";
      this.Text = "Memory Monitor";
      this.menuStrip1.ResumeLayout( false );
      this.menuStrip1.PerformLayout();
      this.splitContainer1.Panel1.ResumeLayout( false );
      this.splitContainer1.Panel2.ResumeLayout( false );
      this.splitContainer1.Panel2.PerformLayout();
      this.splitContainer1.ResumeLayout( false );
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.SplitContainer splitContainer1;
    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    private MemoryMapControl MemoryMapControl;
    private System.Windows.Forms.ToolStripMenuItem openBinaryDataToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem tsmZoomOut;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.ListBox lbSelectedAllocs;
    private System.Windows.Forms.Button bPrevEvent;
    private System.Windows.Forms.Button bNextTime;
    private System.Windows.Forms.Button bPrevTime;
    private System.Windows.Forms.TextBox tbTime;
    private System.Windows.Forms.Button bNextNEvents;
    private System.Windows.Forms.Button bPrevNEvents;
    private System.Windows.Forms.Button bNextEvent;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.ListBox lbCallStack;
    private System.Windows.Forms.ToolStripMenuItem tsmiOpenModules;
  }
}

