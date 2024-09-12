namespace EditorPlugins.Editors.AnimGraph
{
  partial class AnimGraphPanel
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
			this.toolStrip = new System.Windows.Forms.ToolStrip();
			this.toolStripCheckSustain = new System.Windows.Forms.ToolStripButton();
			this.toolStripEditSustain = new System.Windows.Forms.ToolStripTextBox();
			this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
			this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
			this.btnRescaleToFit = new System.Windows.Forms.ToolStripButton();
			this.btnSmartSelection = new System.Windows.Forms.ToolStripButton();
			this.splitContainerGraphs = new System.Windows.Forms.SplitContainer();
			this.tabControlMain = new System.Windows.Forms.TabControl();
			this.tabPageAnimGraphEditor = new System.Windows.Forms.TabPage();
			this.tabPageAnimations = new System.Windows.Forms.TabPage();
			this.updateTimer = new System.Windows.Forms.Timer( this.components );
			this.goView1 = new EditorPlugins.Editors.AnimGraph.AnimGraphControl();
			this.goView2 = new EditorPlugins.Editors.AnimGraph.AnimGraphControl();
			this.toolStrip.SuspendLayout();
			this.splitContainerGraphs.Panel1.SuspendLayout();
			this.splitContainerGraphs.Panel2.SuspendLayout();
			this.splitContainerGraphs.SuspendLayout();
			this.tabControlMain.SuspendLayout();
			this.tabPageAnimGraphEditor.SuspendLayout();
			this.SuspendLayout();
			// 
			// toolStrip
			// 
			this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.toolStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.toolStripCheckSustain,
            this.toolStripEditSustain,
            this.toolStripLabel1,
            this.toolStripSeparator5,
            this.btnRescaleToFit,
            this.btnSmartSelection} );
			this.toolStrip.Location = new System.Drawing.Point( 0, 0 );
			this.toolStrip.Name = "toolStrip";
			this.toolStrip.Size = new System.Drawing.Size( 478, 25 );
			this.toolStrip.TabIndex = 1;
			this.toolStrip.Text = "toolStrip1";
			// 
			// toolStripCheckSustain
			// 
			this.toolStripCheckSustain.CheckOnClick = true;
			this.toolStripCheckSustain.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.toolStripCheckSustain.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripCheckSustain.Name = "toolStripCheckSustain";
			this.toolStripCheckSustain.Size = new System.Drawing.Size( 38, 22 );
			this.toolStripCheckSustain.Text = "Loop";
			this.toolStripCheckSustain.ToolTipText = "Play looped nodes for at least this time";
			this.toolStripCheckSustain.CheckStateChanged += new System.EventHandler( this.toolStripCheckSustain_CheckStateChanged );
			// 
			// toolStripEditSustain
			// 
			this.toolStripEditSustain.Name = "toolStripEditSustain";
			this.toolStripEditSustain.Size = new System.Drawing.Size( 30, 25 );
			this.toolStripEditSustain.Text = "0";
			this.toolStripEditSustain.Leave += new System.EventHandler( this.toolStripEditSustain_Leave );
			this.toolStripEditSustain.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.toolStripEditSustain_KeyPress );
			// 
			// toolStripLabel1
			// 
			this.toolStripLabel1.Name = "toolStripLabel1";
			this.toolStripLabel1.Size = new System.Drawing.Size( 24, 22 );
			this.toolStripLabel1.Text = "sec";
			// 
			// toolStripSeparator5
			// 
			this.toolStripSeparator5.Name = "toolStripSeparator5";
			this.toolStripSeparator5.Size = new System.Drawing.Size( 6, 25 );
			// 
			// btnRescaleToFit
			// 
			this.btnRescaleToFit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.btnRescaleToFit.Image = global::EditorPlugins.EditorPluginResources.RescaleToFit;
			this.btnRescaleToFit.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.btnRescaleToFit.Name = "btnRescaleToFit";
			this.btnRescaleToFit.Size = new System.Drawing.Size( 23, 22 );
			this.btnRescaleToFit.Text = "Rescale to fit";
			this.btnRescaleToFit.Click += new System.EventHandler( this.btnRescaleToFit_Click );
			// 
			// btnSmartSelection
			// 
			this.btnSmartSelection.CheckOnClick = true;
			this.btnSmartSelection.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.btnSmartSelection.Image = global::EditorPlugins.EditorPluginResources.SmartSelection;
			this.btnSmartSelection.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.btnSmartSelection.Name = "btnSmartSelection";
			this.btnSmartSelection.Size = new System.Drawing.Size( 23, 22 );
			this.btnSmartSelection.Text = "Smart Selection";
			this.btnSmartSelection.CheckedChanged += new System.EventHandler( this.btnSmartSelection_CheckedChanged );
			// 
			// splitContainerGraphs
			// 
			this.splitContainerGraphs.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainerGraphs.Location = new System.Drawing.Point( 3, 3 );
			this.splitContainerGraphs.Name = "splitContainerGraphs";
			this.splitContainerGraphs.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainerGraphs.Panel1
			// 
			this.splitContainerGraphs.Panel1.Controls.Add( this.goView1 );
			// 
			// splitContainerGraphs.Panel2
			// 
			this.splitContainerGraphs.Panel2.Controls.Add( this.goView2 );
			this.splitContainerGraphs.Size = new System.Drawing.Size( 464, 442 );
			this.splitContainerGraphs.SplitterDistance = 223;
			this.splitContainerGraphs.TabIndex = 0;
			// 
			// tabControlMain
			// 
			this.tabControlMain.Controls.Add( this.tabPageAnimGraphEditor );
			this.tabControlMain.Controls.Add( this.tabPageAnimations );
			this.tabControlMain.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControlMain.HotTrack = true;
			this.tabControlMain.Location = new System.Drawing.Point( 0, 25 );
			this.tabControlMain.Name = "tabControlMain";
			this.tabControlMain.SelectedIndex = 0;
			this.tabControlMain.Size = new System.Drawing.Size( 478, 474 );
			this.tabControlMain.TabIndex = 2;
			// 
			// tabPageAnimGraphEditor
			// 
			this.tabPageAnimGraphEditor.Controls.Add( this.splitContainerGraphs );
			this.tabPageAnimGraphEditor.Location = new System.Drawing.Point( 4, 22 );
			this.tabPageAnimGraphEditor.Name = "tabPageAnimGraphEditor";
			this.tabPageAnimGraphEditor.Padding = new System.Windows.Forms.Padding( 3 );
			this.tabPageAnimGraphEditor.Size = new System.Drawing.Size( 470, 448 );
			this.tabPageAnimGraphEditor.TabIndex = 0;
			this.tabPageAnimGraphEditor.Text = "AnimGraph Editor";
			this.tabPageAnimGraphEditor.UseVisualStyleBackColor = true;
			// 
			// tabPageAnimations
			// 
			this.tabPageAnimations.Location = new System.Drawing.Point( 4, 22 );
			this.tabPageAnimations.Name = "tabPageAnimations";
			this.tabPageAnimations.Padding = new System.Windows.Forms.Padding( 3 );
			this.tabPageAnimations.Size = new System.Drawing.Size( 470, 419 );
			this.tabPageAnimations.TabIndex = 1;
			this.tabPageAnimations.Text = "Animations";
			this.tabPageAnimations.UseVisualStyleBackColor = true;
			// 
			// updateTimer
			// 
			this.updateTimer.Enabled = true;
			this.updateTimer.Tick += new System.EventHandler( this.updateTimer_Tick );
			// 
			// goView1
			// 
			this.goView1.AllowCopy = false;
			this.goView1.AllowDragOut = false;
			this.goView1.AllowDrop = false;
			this.goView1.ArrowMoveLarge = 10F;
			this.goView1.ArrowMoveSmall = 1F;
			this.goView1.BackColor = System.Drawing.SystemColors.Window;
			this.goView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.goView1.DragsRealtime = true;
			this.goView1.Enabled = false;
			this.goView1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.goView1.Location = new System.Drawing.Point( 0, 0 );
			this.goView1.Name = "goView1";
			this.goView1.PortGravity = 5F;
			this.goView1.PrimarySelectionColor = System.Drawing.Color.Transparent;
			this.goView1.SecondarySelectionColor = System.Drawing.Color.Transparent;
			this.goView1.ShowHorizontalScrollBar = Northwoods.Go.GoViewScrollBarVisibility.Show;
			this.goView1.ShowVerticalScrollBar = Northwoods.Go.GoViewScrollBarVisibility.Show;
			this.goView1.Size = new System.Drawing.Size( 464, 223 );
			this.goView1.SmartSelectionEnabled = false;
			this.goView1.SustainLength = 0F;
			this.goView1.SustainLooped = false;
			this.goView1.TabIndex = 1;
			this.goView1.Text = "goView1";
			this.goView1.SelectedObjectChanged += new System.EventHandler( this.goView2_SelectedObjectChanged );
			// 
			// goView2
			// 
			this.goView2.AllowDragOut = false;
			this.goView2.AllowDrop = false;
			this.goView2.ArrowMoveLarge = 10F;
			this.goView2.ArrowMoveSmall = 1F;
			this.goView2.BackColor = System.Drawing.SystemColors.Window;
			this.goView2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.goView2.DragsRealtime = true;
			this.goView2.Enabled = false;
			this.goView2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.goView2.Location = new System.Drawing.Point( 0, 0 );
			this.goView2.Name = "goView2";
			this.goView2.PortGravity = 5F;
			this.goView2.PrimarySelectionColor = System.Drawing.Color.Transparent;
			this.goView2.SecondarySelectionColor = System.Drawing.Color.Transparent;
			this.goView2.ShowHorizontalScrollBar = Northwoods.Go.GoViewScrollBarVisibility.Show;
			this.goView2.ShowVerticalScrollBar = Northwoods.Go.GoViewScrollBarVisibility.Show;
			this.goView2.Size = new System.Drawing.Size( 464, 215 );
			this.goView2.SmartSelectionEnabled = false;
			this.goView2.SustainLength = 0F;
			this.goView2.SustainLooped = false;
			this.goView2.TabIndex = 2;
			this.goView2.Text = "goView2";
			this.goView2.SelectedObjectChanged += new System.EventHandler( this.goView2_SelectedObjectChanged );
			// 
			// AnimGraphPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 478, 499 );
			this.Controls.Add( this.tabControlMain );
			this.Controls.Add( this.toolStrip );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AnimGraphPanel";
			this.TabText = "Animations";
			this.Text = "Animations";
			this.toolStrip.ResumeLayout( false );
			this.toolStrip.PerformLayout();
			this.splitContainerGraphs.Panel1.ResumeLayout( false );
			this.splitContainerGraphs.Panel2.ResumeLayout( false );
			this.splitContainerGraphs.ResumeLayout( false );
			this.tabControlMain.ResumeLayout( false );
			this.tabPageAnimGraphEditor.ResumeLayout( false );
			this.ResumeLayout( false );
			this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ToolStrip toolStrip;
    private AnimGraphControl goView1;
    private AnimGraphControl goView2;
		private System.Windows.Forms.SplitContainer splitContainerGraphs;
		private System.Windows.Forms.TabControl tabControlMain;
		private System.Windows.Forms.TabPage tabPageAnimGraphEditor;
		private System.Windows.Forms.TabPage tabPageAnimations;
    private System.Windows.Forms.ToolStripButton toolStripCheckSustain;
    private System.Windows.Forms.ToolStripTextBox toolStripEditSustain;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
    private System.Windows.Forms.ToolStripLabel toolStripLabel1;
    private System.Windows.Forms.Timer updateTimer;
		private System.Windows.Forms.ToolStripButton btnRescaleToFit;
		private System.Windows.Forms.ToolStripButton btnSmartSelection;
  }
}