namespace TrackVis
{
  partial class TrackVisForm
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
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( TrackVisForm ) );
      this.menuStrip1 = new System.Windows.Forms.MenuStrip();
      this.toolStripMenu = new System.Windows.Forms.ToolStripMenuItem();
      this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
      this.tracksPanel = new TrackVis.ScrollablePanel();
      this.tabs = new System.Windows.Forms.TabControl();
      this.tabPageTracks = new System.Windows.Forms.TabPage();
      this.buttonResetVZoom = new System.Windows.Forms.Button();
      this.buttonVZoomOut = new System.Windows.Forms.Button();
      this.buttonVZoomIn = new System.Windows.Forms.Button();
      this.buttonZoomOut = new System.Windows.Forms.Button();
      this.buttonZoomIn = new System.Windows.Forms.Button();
      this.hScrollBrowse = new System.Windows.Forms.HScrollBar();
      this.comboTo = new System.Windows.Forms.ComboBox();
      this.comboFrom = new System.Windows.Forms.ComboBox();
      this.tabPageGraph = new System.Windows.Forms.TabPage();
      this.cbOppositeLines = new System.Windows.Forms.CheckBox();
      this.comboSelectLeftGraph = new System.Windows.Forms.ComboBox();
      this.hScrollBarPlay = new System.Windows.Forms.HScrollBar();
      this.textBoxTimes = new System.Windows.Forms.TextBox();
      this.buttonPlay = new System.Windows.Forms.Button();
      this.connGraphVis = new TrackVis.ConnGraphVisControl();
      this.tabPageLegend = new System.Windows.Forms.TabPage();
      this.splitContainerLegend1 = new System.Windows.Forms.SplitContainer();
      this.label1 = new System.Windows.Forms.Label();
      this.flowLegend = new System.Windows.Forms.FlowLayoutPanel();
      this.flowLegendEvents = new System.Windows.Forms.FlowLayoutPanel();
      this.label2 = new System.Windows.Forms.Label();
      this.timerRefreshProgress = new System.Windows.Forms.Timer( this.components );
      this.tabPageEventDesc = new System.Windows.Forms.TabPage();
      this.textBoxEventsDesc = new System.Windows.Forms.TextBox();
      this.menuStrip1.SuspendLayout();
      this.tabs.SuspendLayout();
      this.tabPageTracks.SuspendLayout();
      this.tabPageGraph.SuspendLayout();
      this.tabPageLegend.SuspendLayout();
      this.splitContainerLegend1.Panel1.SuspendLayout();
      this.splitContainerLegend1.Panel2.SuspendLayout();
      this.splitContainerLegend1.SuspendLayout();
      this.tabPageEventDesc.SuspendLayout();
      this.SuspendLayout();
      // 
      // menuStrip1
      // 
      this.menuStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenu} );
      this.menuStrip1.Location = new System.Drawing.Point( 0, 0 );
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new System.Drawing.Size( 866, 24 );
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      // 
      // toolStripMenu
      // 
      this.toolStripMenu.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem} );
      this.toolStripMenu.Name = "toolStripMenu";
      this.toolStripMenu.Size = new System.Drawing.Size( 54, 20 );
      this.toolStripMenu.Text = "Actions";
      // 
      // openToolStripMenuItem
      // 
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new System.Drawing.Size( 123, 22 );
      this.openToolStripMenuItem.Text = "Open...";
      this.openToolStripMenuItem.Click += new System.EventHandler( this.openToolStripMenuItem_Click );
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size( 120, 6 );
      // 
      // exitToolStripMenuItem
      // 
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new System.Drawing.Size( 123, 22 );
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new System.EventHandler( this.exitToolStripMenuItem_Click );
      // 
      // openFileDialog
      // 
      this.openFileDialog.Filter = "Track Data Files|*.tcsv";
      this.openFileDialog.Multiselect = true;
      this.openFileDialog.Title = "Open Track Datafile(s)";
      // 
      // tracksPanel
      // 
      this.tracksPanel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.tracksPanel.AutoScroll = true;
      this.tracksPanel.Location = new System.Drawing.Point( 0, 56 );
      this.tracksPanel.Name = "tracksPanel";
      this.tracksPanel.Size = new System.Drawing.Size( 858, 558 );
      this.tracksPanel.TabIndex = 1;
      // 
      // tabs
      // 
      this.tabs.Controls.Add( this.tabPageTracks );
      this.tabs.Controls.Add( this.tabPageEventDesc );
      this.tabs.Controls.Add( this.tabPageGraph );
      this.tabs.Controls.Add( this.tabPageLegend );
      this.tabs.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tabs.Location = new System.Drawing.Point( 0, 24 );
      this.tabs.Name = "tabs";
      this.tabs.SelectedIndex = 0;
      this.tabs.Size = new System.Drawing.Size( 866, 640 );
      this.tabs.TabIndex = 2;
      // 
      // tabPageTracks
      // 
      this.tabPageTracks.Controls.Add( this.buttonResetVZoom );
      this.tabPageTracks.Controls.Add( this.buttonVZoomOut );
      this.tabPageTracks.Controls.Add( this.buttonVZoomIn );
      this.tabPageTracks.Controls.Add( this.buttonZoomOut );
      this.tabPageTracks.Controls.Add( this.buttonZoomIn );
      this.tabPageTracks.Controls.Add( this.hScrollBrowse );
      this.tabPageTracks.Controls.Add( this.comboTo );
      this.tabPageTracks.Controls.Add( this.comboFrom );
      this.tabPageTracks.Controls.Add( this.tracksPanel );
      this.tabPageTracks.Location = new System.Drawing.Point( 4, 22 );
      this.tabPageTracks.Name = "tabPageTracks";
      this.tabPageTracks.Padding = new System.Windows.Forms.Padding( 3 );
      this.tabPageTracks.Size = new System.Drawing.Size( 858, 614 );
      this.tabPageTracks.TabIndex = 0;
      this.tabPageTracks.Text = "Tracks";
      this.tabPageTracks.UseVisualStyleBackColor = true;
      // 
      // buttonResetVZoom
      // 
      this.buttonResetVZoom.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonResetVZoom.Location = new System.Drawing.Point( 524, 6 );
      this.buttonResetVZoom.Name = "buttonResetVZoom";
      this.buttonResetVZoom.Size = new System.Drawing.Size( 75, 23 );
      this.buttonResetVZoom.TabIndex = 12;
      this.buttonResetVZoom.Text = "All to 1 sec";
      this.buttonResetVZoom.UseVisualStyleBackColor = true;
      this.buttonResetVZoom.Click += new System.EventHandler( this.buttonResetVZoom_Click );
      // 
      // buttonVZoomOut
      // 
      this.buttonVZoomOut.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonVZoomOut.Location = new System.Drawing.Point( 605, 6 );
      this.buttonVZoomOut.Name = "buttonVZoomOut";
      this.buttonVZoomOut.Size = new System.Drawing.Size( 75, 23 );
      this.buttonVZoomOut.TabIndex = 11;
      this.buttonVZoomOut.Text = "VZoom -";
      this.buttonVZoomOut.UseVisualStyleBackColor = true;
      this.buttonVZoomOut.Click += new System.EventHandler( this.buttonVZoomOut_Click );
      // 
      // buttonVZoomIn
      // 
      this.buttonVZoomIn.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonVZoomIn.Location = new System.Drawing.Point( 443, 6 );
      this.buttonVZoomIn.Name = "buttonVZoomIn";
      this.buttonVZoomIn.Size = new System.Drawing.Size( 75, 23 );
      this.buttonVZoomIn.TabIndex = 10;
      this.buttonVZoomIn.Text = "VZoom +";
      this.buttonVZoomIn.UseVisualStyleBackColor = true;
      this.buttonVZoomIn.Click += new System.EventHandler( this.buttonVZoomIn_Click );
      // 
      // buttonZoomOut
      // 
      this.buttonZoomOut.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonZoomOut.Location = new System.Drawing.Point( 775, 6 );
      this.buttonZoomOut.Name = "buttonZoomOut";
      this.buttonZoomOut.Size = new System.Drawing.Size( 75, 23 );
      this.buttonZoomOut.TabIndex = 8;
      this.buttonZoomOut.Text = "Zoom -";
      this.buttonZoomOut.UseVisualStyleBackColor = true;
      this.buttonZoomOut.Click += new System.EventHandler( this.buttonZoomOut_Click );
      // 
      // buttonZoomIn
      // 
      this.buttonZoomIn.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonZoomIn.Location = new System.Drawing.Point( 694, 6 );
      this.buttonZoomIn.Name = "buttonZoomIn";
      this.buttonZoomIn.Size = new System.Drawing.Size( 75, 23 );
      this.buttonZoomIn.TabIndex = 7;
      this.buttonZoomIn.Text = "Zoom +";
      this.buttonZoomIn.UseVisualStyleBackColor = true;
      this.buttonZoomIn.Click += new System.EventHandler( this.buttonZoomIn_Click );
      // 
      // hScrollBrowse
      // 
      this.hScrollBrowse.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.hScrollBrowse.Enabled = false;
      this.hScrollBrowse.Location = new System.Drawing.Point( 0, 32 );
      this.hScrollBrowse.Name = "hScrollBrowse";
      this.hScrollBrowse.Size = new System.Drawing.Size( 855, 21 );
      this.hScrollBrowse.TabIndex = 6;
      this.hScrollBrowse.Scroll += new System.Windows.Forms.ScrollEventHandler( this.hScrollBrowse_Scroll );
      // 
      // comboTo
      // 
      this.comboTo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.comboTo.FormattingEnabled = true;
      this.comboTo.Location = new System.Drawing.Point( 165, 6 );
      this.comboTo.Name = "comboTo";
      this.comboTo.Size = new System.Drawing.Size( 153, 21 );
      this.comboTo.TabIndex = 5;
      this.comboTo.SelectedIndexChanged += new System.EventHandler( this.comboTo_SelectedIndexChanged );
      // 
      // comboFrom
      // 
      this.comboFrom.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.comboFrom.FormattingEnabled = true;
      this.comboFrom.Location = new System.Drawing.Point( 6, 6 );
      this.comboFrom.Name = "comboFrom";
      this.comboFrom.Size = new System.Drawing.Size( 153, 21 );
      this.comboFrom.TabIndex = 2;
      this.comboFrom.SelectedIndexChanged += new System.EventHandler( this.comboFrom_SelectedIndexChanged );
      // 
      // tabPageGraph
      // 
      this.tabPageGraph.Controls.Add( this.cbOppositeLines );
      this.tabPageGraph.Controls.Add( this.comboSelectLeftGraph );
      this.tabPageGraph.Controls.Add( this.hScrollBarPlay );
      this.tabPageGraph.Controls.Add( this.textBoxTimes );
      this.tabPageGraph.Controls.Add( this.buttonPlay );
      this.tabPageGraph.Controls.Add( this.connGraphVis );
      this.tabPageGraph.Location = new System.Drawing.Point( 4, 22 );
      this.tabPageGraph.Name = "tabPageGraph";
      this.tabPageGraph.Padding = new System.Windows.Forms.Padding( 3 );
      this.tabPageGraph.Size = new System.Drawing.Size( 858, 614 );
      this.tabPageGraph.TabIndex = 1;
      this.tabPageGraph.Text = "Graph";
      this.tabPageGraph.UseVisualStyleBackColor = true;
      // 
      // cbOppositeLines
      // 
      this.cbOppositeLines.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.cbOppositeLines.AutoSize = true;
      this.cbOppositeLines.Location = new System.Drawing.Point( 744, 33 );
      this.cbOppositeLines.Name = "cbOppositeLines";
      this.cbOppositeLines.Size = new System.Drawing.Size( 106, 17 );
      this.cbOppositeLines.TabIndex = 6;
      this.cbOppositeLines.Text = "Swap line halves";
      this.cbOppositeLines.UseVisualStyleBackColor = true;
      this.cbOppositeLines.CheckedChanged += new System.EventHandler( this.cbOppositeLines_CheckedChanged );
      // 
      // comboSelectLeftGraph
      // 
      this.comboSelectLeftGraph.FormattingEnabled = true;
      this.comboSelectLeftGraph.Location = new System.Drawing.Point( 6, 31 );
      this.comboSelectLeftGraph.Name = "comboSelectLeftGraph";
      this.comboSelectLeftGraph.Size = new System.Drawing.Size( 185, 21 );
      this.comboSelectLeftGraph.TabIndex = 5;
      this.comboSelectLeftGraph.SelectedIndexChanged += new System.EventHandler( this.comboSelectLeftGraph_SelectedIndexChanged );
      // 
      // hScrollBarPlay
      // 
      this.hScrollBarPlay.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.hScrollBarPlay.Location = new System.Drawing.Point( 86, 6 );
      this.hScrollBarPlay.Maximum = 1000;
      this.hScrollBarPlay.Name = "hScrollBarPlay";
      this.hScrollBarPlay.Size = new System.Drawing.Size( 650, 22 );
      this.hScrollBarPlay.TabIndex = 4;
      this.hScrollBarPlay.Scroll += new System.Windows.Forms.ScrollEventHandler( this.hScrollBarPlay_Scroll );
      // 
      // textBoxTimes
      // 
      this.textBoxTimes.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.textBoxTimes.Location = new System.Drawing.Point( 739, 8 );
      this.textBoxTimes.Name = "textBoxTimes";
      this.textBoxTimes.Size = new System.Drawing.Size( 113, 20 );
      this.textBoxTimes.TabIndex = 3;
      this.textBoxTimes.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
      // 
      // buttonPlay
      // 
      this.buttonPlay.Location = new System.Drawing.Point( 6, 6 );
      this.buttonPlay.Name = "buttonPlay";
      this.buttonPlay.Size = new System.Drawing.Size( 75, 23 );
      this.buttonPlay.TabIndex = 1;
      this.buttonPlay.Text = "Play";
      this.buttonPlay.UseVisualStyleBackColor = true;
      this.buttonPlay.Click += new System.EventHandler( this.buttonPlay_Click );
      // 
      // connGraphVis
      // 
      this.connGraphVis.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.connGraphVis.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.connGraphVis.Dataset = null;
      this.connGraphVis.Location = new System.Drawing.Point( 0, 58 );
      this.connGraphVis.Name = "connGraphVis";
      this.connGraphVis.Playing = false;
      this.connGraphVis.Size = new System.Drawing.Size( 858, 556 );
      this.connGraphVis.TabIndex = 0;
      // 
      // tabPageLegend
      // 
      this.tabPageLegend.Controls.Add( this.splitContainerLegend1 );
      this.tabPageLegend.Location = new System.Drawing.Point( 4, 22 );
      this.tabPageLegend.Name = "tabPageLegend";
      this.tabPageLegend.Padding = new System.Windows.Forms.Padding( 3 );
      this.tabPageLegend.Size = new System.Drawing.Size( 858, 614 );
      this.tabPageLegend.TabIndex = 2;
      this.tabPageLegend.Text = "Legend";
      this.tabPageLegend.UseVisualStyleBackColor = true;
      // 
      // splitContainerLegend1
      // 
      this.splitContainerLegend1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.splitContainerLegend1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.splitContainerLegend1.Location = new System.Drawing.Point( 3, 3 );
      this.splitContainerLegend1.Name = "splitContainerLegend1";
      // 
      // splitContainerLegend1.Panel1
      // 
      this.splitContainerLegend1.Panel1.Controls.Add( this.label1 );
      this.splitContainerLegend1.Panel1.Controls.Add( this.flowLegend );
      // 
      // splitContainerLegend1.Panel2
      // 
      this.splitContainerLegend1.Panel2.Controls.Add( this.flowLegendEvents );
      this.splitContainerLegend1.Panel2.Controls.Add( this.label2 );
      this.splitContainerLegend1.Size = new System.Drawing.Size( 852, 608 );
      this.splitContainerLegend1.SplitterDistance = 412;
      this.splitContainerLegend1.TabIndex = 10;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 4, 0 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 40, 13 );
      this.label1.TabIndex = 10;
      this.label1.Text = "Tracks";
      // 
      // flowLegend
      // 
      this.flowLegend.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.flowLegend.Location = new System.Drawing.Point( 4, 16 );
      this.flowLegend.Name = "flowLegend";
      this.flowLegend.Size = new System.Drawing.Size( 403, 586 );
      this.flowLegend.TabIndex = 9;
      // 
      // flowLegendEvents
      // 
      this.flowLegendEvents.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.flowLegendEvents.Location = new System.Drawing.Point( 3, 16 );
      this.flowLegendEvents.Name = "flowLegendEvents";
      this.flowLegendEvents.Size = new System.Drawing.Size( 427, 586 );
      this.flowLegendEvents.TabIndex = 1;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 3, 0 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 40, 13 );
      this.label2.TabIndex = 0;
      this.label2.Text = "Events";
      // 
      // timerRefreshProgress
      // 
      this.timerRefreshProgress.Tick += new System.EventHandler( this.timerRefreshProgress_Tick );
      // 
      // tabPageEventDesc
      // 
      this.tabPageEventDesc.Controls.Add( this.textBoxEventsDesc );
      this.tabPageEventDesc.Location = new System.Drawing.Point( 4, 22 );
      this.tabPageEventDesc.Name = "tabPageEventDesc";
      this.tabPageEventDesc.Padding = new System.Windows.Forms.Padding( 3 );
      this.tabPageEventDesc.Size = new System.Drawing.Size( 858, 614 );
      this.tabPageEventDesc.TabIndex = 3;
      this.tabPageEventDesc.Text = "Events";
      this.tabPageEventDesc.UseVisualStyleBackColor = true;
      // 
      // textBoxEventsDesc
      // 
      this.textBoxEventsDesc.Dock = System.Windows.Forms.DockStyle.Fill;
      this.textBoxEventsDesc.Location = new System.Drawing.Point( 3, 3 );
      this.textBoxEventsDesc.Multiline = true;
      this.textBoxEventsDesc.Name = "textBoxEventsDesc";
      this.textBoxEventsDesc.ReadOnly = true;
      this.textBoxEventsDesc.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxEventsDesc.Size = new System.Drawing.Size( 852, 608 );
      this.textBoxEventsDesc.TabIndex = 0;
      // 
      // TrackVisForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.AutoScroll = true;
      this.ClientSize = new System.Drawing.Size( 866, 664 );
      this.Controls.Add( this.tabs );
      this.Controls.Add( this.menuStrip1 );
      this.Icon = ( (System.Drawing.Icon)( resources.GetObject( "$this.Icon" ) ) );
      this.MainMenuStrip = this.menuStrip1;
      this.MinimumSize = new System.Drawing.Size( 800, 500 );
      this.Name = "TrackVisForm";
      this.Text = "TrackVis";
      this.Resize += new System.EventHandler( this.TrackVisForm_Resize );
      this.menuStrip1.ResumeLayout( false );
      this.menuStrip1.PerformLayout();
      this.tabs.ResumeLayout( false );
      this.tabPageTracks.ResumeLayout( false );
      this.tabPageGraph.ResumeLayout( false );
      this.tabPageGraph.PerformLayout();
      this.tabPageLegend.ResumeLayout( false );
      this.splitContainerLegend1.Panel1.ResumeLayout( false );
      this.splitContainerLegend1.Panel1.PerformLayout();
      this.splitContainerLegend1.Panel2.ResumeLayout( false );
      this.splitContainerLegend1.Panel2.PerformLayout();
      this.splitContainerLegend1.ResumeLayout( false );
      this.tabPageEventDesc.ResumeLayout( false );
      this.tabPageEventDesc.PerformLayout();
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem toolStripMenu;
    private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    private System.Windows.Forms.OpenFileDialog openFileDialog;
    private ScrollablePanel tracksPanel;
    private System.Windows.Forms.TabControl tabs;
    private System.Windows.Forms.TabPage tabPageTracks;
    private System.Windows.Forms.TabPage tabPageGraph;
    private ConnGraphVisControl connGraphVis;
    private System.Windows.Forms.Button buttonPlay;
    private System.Windows.Forms.TextBox textBoxTimes;
    private System.Windows.Forms.Timer timerRefreshProgress;
    private System.Windows.Forms.HScrollBar hScrollBarPlay;
    private System.Windows.Forms.ComboBox comboTo;
    private System.Windows.Forms.ComboBox comboFrom;
    private System.Windows.Forms.HScrollBar hScrollBrowse;
    private System.Windows.Forms.Button buttonZoomOut;
    private System.Windows.Forms.Button buttonZoomIn;
    private System.Windows.Forms.ComboBox comboSelectLeftGraph;
    private System.Windows.Forms.CheckBox cbOppositeLines;
    private System.Windows.Forms.FlowLayoutPanel flowLegend;
    private System.Windows.Forms.Button buttonVZoomOut;
    private System.Windows.Forms.Button buttonVZoomIn;
    private System.Windows.Forms.Button buttonResetVZoom;
    private System.Windows.Forms.TabPage tabPageLegend;
    private System.Windows.Forms.SplitContainer splitContainerLegend1;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.FlowLayoutPanel flowLegendEvents;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.TabPage tabPageEventDesc;
    private System.Windows.Forms.TextBox textBoxEventsDesc;

  }
}

