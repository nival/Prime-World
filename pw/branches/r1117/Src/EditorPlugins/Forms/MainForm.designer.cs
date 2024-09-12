namespace EditorPlugins.Forms
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
      this.components = new System.ComponentModel.Container();
      WeifenLuo.WinFormsUI.Docking.DockPanelSkin dockPanelSkin2 = new WeifenLuo.WinFormsUI.Docking.DockPanelSkin();
      WeifenLuo.WinFormsUI.Docking.AutoHideStripSkin autoHideStripSkin2 = new WeifenLuo.WinFormsUI.Docking.AutoHideStripSkin();
      WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient4 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient8 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      WeifenLuo.WinFormsUI.Docking.DockPaneStripSkin dockPaneStripSkin2 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripSkin();
      WeifenLuo.WinFormsUI.Docking.DockPaneStripGradient dockPaneStripGradient2 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient9 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient5 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient10 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      WeifenLuo.WinFormsUI.Docking.DockPaneStripToolWindowGradient dockPaneStripToolWindowGradient2 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripToolWindowGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient11 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient12 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient6 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient13 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient14 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( MainForm ) );
      this.statusBar = new System.Windows.Forms.Panel();
      this.statusBarProgressBar = new System.Windows.Forms.ProgressBar();
      this.statusBarLabel = new System.Windows.Forms.Label();
      this.statusBarPanel = new System.Windows.Forms.Panel();
      this.dockPanel = new WeifenLuo.WinFormsUI.Docking.DockPanel();
      this.mainMenuStrip = new System.Windows.Forms.MenuStrip();
      this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
      this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.redoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolbars = new System.Windows.Forms.Panel();
      this.scriptTimer = new System.Windows.Forms.Timer( this.components );
      this.statusBar.SuspendLayout();
      this.mainMenuStrip.SuspendLayout();
      this.SuspendLayout();
      // 
      // statusBar
      // 
      this.statusBar.BackColor = System.Drawing.SystemColors.Control;
      this.statusBar.Controls.Add( this.statusBarProgressBar );
      this.statusBar.Controls.Add( this.statusBarLabel );
      this.statusBar.Controls.Add( this.statusBarPanel );
      this.statusBar.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.statusBar.Location = new System.Drawing.Point( 0, 442 );
      this.statusBar.Name = "statusBar";
      this.statusBar.Size = new System.Drawing.Size( 784, 22 );
      this.statusBar.TabIndex = 0;
      // 
      // statusBarProgressBar
      // 
      this.statusBarProgressBar.Dock = System.Windows.Forms.DockStyle.Right;
      this.statusBarProgressBar.Location = new System.Drawing.Point( 684, 0 );
      this.statusBarProgressBar.Name = "statusBarProgressBar";
      this.statusBarProgressBar.Size = new System.Drawing.Size( 100, 22 );
      this.statusBarProgressBar.TabIndex = 3;
      this.statusBarProgressBar.Visible = false;
      // 
      // statusBarLabel
      // 
      this.statusBarLabel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.statusBarLabel.Location = new System.Drawing.Point( 0, 0 );
      this.statusBarLabel.Name = "statusBarLabel";
      this.statusBarLabel.Size = new System.Drawing.Size( 784, 22 );
      this.statusBarLabel.TabIndex = 2;
      this.statusBarLabel.Text = "Ready";
      this.statusBarLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // statusBarPanel
      // 
      this.statusBarPanel.Dock = System.Windows.Forms.DockStyle.Right;
      this.statusBarPanel.Location = new System.Drawing.Point( 784, 0 );
      this.statusBarPanel.Name = "statusBarPanel";
      this.statusBarPanel.Size = new System.Drawing.Size( 0, 22 );
      this.statusBarPanel.TabIndex = 4;
      this.statusBarPanel.Visible = false;
      // 
      // dockPanel
      // 
      this.dockPanel.ActiveAutoHideContent = null;
      this.dockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.dockPanel.DockBackColor = System.Drawing.SystemColors.AppWorkspace;
      this.dockPanel.Font = new System.Drawing.Font( "Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World );
      this.dockPanel.Location = new System.Drawing.Point( 0, 50 );
      this.dockPanel.Name = "dockPanel";
      this.dockPanel.Size = new System.Drawing.Size( 784, 392 );
      dockPanelGradient4.EndColor = System.Drawing.SystemColors.ControlLight;
      dockPanelGradient4.StartColor = System.Drawing.SystemColors.ControlLight;
      autoHideStripSkin2.DockStripGradient = dockPanelGradient4;
      tabGradient8.EndColor = System.Drawing.SystemColors.Control;
      tabGradient8.StartColor = System.Drawing.SystemColors.Control;
      tabGradient8.TextColor = System.Drawing.SystemColors.ControlDarkDark;
      autoHideStripSkin2.TabGradient = tabGradient8;
      dockPanelSkin2.AutoHideStripSkin = autoHideStripSkin2;
      tabGradient9.EndColor = System.Drawing.SystemColors.ControlLightLight;
      tabGradient9.StartColor = System.Drawing.SystemColors.ControlLightLight;
      tabGradient9.TextColor = System.Drawing.SystemColors.ControlText;
      dockPaneStripGradient2.ActiveTabGradient = tabGradient9;
      dockPanelGradient5.EndColor = System.Drawing.SystemColors.Control;
      dockPanelGradient5.StartColor = System.Drawing.SystemColors.Control;
      dockPaneStripGradient2.DockStripGradient = dockPanelGradient5;
      tabGradient10.EndColor = System.Drawing.SystemColors.ControlLight;
      tabGradient10.StartColor = System.Drawing.SystemColors.ControlLight;
      tabGradient10.TextColor = System.Drawing.SystemColors.ControlText;
      dockPaneStripGradient2.InactiveTabGradient = tabGradient10;
      dockPaneStripSkin2.DocumentGradient = dockPaneStripGradient2;
      tabGradient11.EndColor = System.Drawing.SystemColors.ActiveCaption;
      tabGradient11.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
      tabGradient11.StartColor = System.Drawing.SystemColors.GradientActiveCaption;
      tabGradient11.TextColor = System.Drawing.SystemColors.ActiveCaptionText;
      dockPaneStripToolWindowGradient2.ActiveCaptionGradient = tabGradient11;
      tabGradient12.EndColor = System.Drawing.SystemColors.Control;
      tabGradient12.StartColor = System.Drawing.SystemColors.Control;
      tabGradient12.TextColor = System.Drawing.SystemColors.ControlText;
      dockPaneStripToolWindowGradient2.ActiveTabGradient = tabGradient12;
      dockPanelGradient6.EndColor = System.Drawing.SystemColors.ControlLight;
      dockPanelGradient6.StartColor = System.Drawing.SystemColors.ControlLight;
      dockPaneStripToolWindowGradient2.DockStripGradient = dockPanelGradient6;
      tabGradient13.EndColor = System.Drawing.SystemColors.GradientInactiveCaption;
      tabGradient13.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
      tabGradient13.StartColor = System.Drawing.SystemColors.GradientInactiveCaption;
      tabGradient13.TextColor = System.Drawing.SystemColors.ControlText;
      dockPaneStripToolWindowGradient2.InactiveCaptionGradient = tabGradient13;
      tabGradient14.EndColor = System.Drawing.Color.Transparent;
      tabGradient14.StartColor = System.Drawing.Color.Transparent;
      tabGradient14.TextColor = System.Drawing.SystemColors.ControlDarkDark;
      dockPaneStripToolWindowGradient2.InactiveTabGradient = tabGradient14;
      dockPaneStripSkin2.ToolWindowGradient = dockPaneStripToolWindowGradient2;
      dockPanelSkin2.DockPaneStripSkin = dockPaneStripSkin2;
      this.dockPanel.Skin = dockPanelSkin2;
      this.dockPanel.TabIndex = 1;
      // 
      // mainMenuStrip
      // 
      this.mainMenuStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.viewToolStripMenuItem} );
      this.mainMenuStrip.Location = new System.Drawing.Point( 0, 0 );
      this.mainMenuStrip.Name = "mainMenuStrip";
      this.mainMenuStrip.Size = new System.Drawing.Size( 784, 24 );
      this.mainMenuStrip.TabIndex = 8;
      this.mainMenuStrip.Text = "menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this.fileToolStripMenuItem.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem} );
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new System.Drawing.Size( 37, 20 );
      this.fileToolStripMenuItem.Text = "&File";
      // 
      // saveToolStripMenuItem
      // 
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S ) ) );
      this.saveToolStripMenuItem.Size = new System.Drawing.Size( 138, 22 );
      this.saveToolStripMenuItem.Text = "Save";
      // 
      // toolStripMenuItem1
      // 
      this.toolStripMenuItem1.Name = "toolStripMenuItem1";
      this.toolStripMenuItem1.Size = new System.Drawing.Size( 135, 6 );
      // 
      // exitToolStripMenuItem
      // 
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4 ) ) );
      this.exitToolStripMenuItem.Size = new System.Drawing.Size( 138, 22 );
      this.exitToolStripMenuItem.Text = "E&xit";
      this.exitToolStripMenuItem.Click += new System.EventHandler( this.OnExitClick );
      // 
      // editToolStripMenuItem
      // 
      this.editToolStripMenuItem.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.undoToolStripMenuItem,
            this.redoToolStripMenuItem} );
      this.editToolStripMenuItem.Name = "editToolStripMenuItem";
      this.editToolStripMenuItem.Size = new System.Drawing.Size( 39, 20 );
      this.editToolStripMenuItem.Text = "&Edit";

      // 
      // undoToolStripMenuItem
      // 
      this.undoToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Fuchsia;
      this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
      this.undoToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z ) ) );
      this.undoToolStripMenuItem.Size = new System.Drawing.Size( 144, 22 );
      this.undoToolStripMenuItem.Text = "&Undo";
      this.undoToolStripMenuItem.Click += new System.EventHandler( this.OnUndoClick );
      // 
      // redoToolStripMenuItem
      // 
      this.redoToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Fuchsia;
      this.redoToolStripMenuItem.Name = "redoToolStripMenuItem";
      this.redoToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y ) ) );
      this.redoToolStripMenuItem.Size = new System.Drawing.Size( 144, 22 );
      this.redoToolStripMenuItem.Text = "&Redo";
      this.redoToolStripMenuItem.Click += new System.EventHandler( this.onRedoClick );
      // 
      // viewToolStripMenuItem
      // 
      this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
      this.viewToolStripMenuItem.Size = new System.Drawing.Size( 44, 20 );
      this.viewToolStripMenuItem.Text = "&View";
      // 
      // toolbars
      // 
      this.toolbars.BackColor = System.Drawing.SystemColors.Control;
      this.toolbars.Dock = System.Windows.Forms.DockStyle.Top;
      this.toolbars.Location = new System.Drawing.Point( 0, 24 );
      this.toolbars.Name = "toolbars";
      this.toolbars.Size = new System.Drawing.Size( 784, 26 );
      this.toolbars.TabIndex = 16;
      // 
      // scriptTimer
      // 
      this.scriptTimer.Enabled = true;
      this.scriptTimer.Interval = 25;
      this.scriptTimer.Tick += new System.EventHandler( this.OnScriptTimerTick );
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.SystemColors.AppWorkspace;
      this.ClientSize = new System.Drawing.Size( 784, 464 );
      this.Controls.Add( this.dockPanel );
      this.Controls.Add( this.toolbars );
      this.Controls.Add( this.statusBar );
      this.Controls.Add( this.mainMenuStrip );
      this.Icon = ( (System.Drawing.Icon)( resources.GetObject( "$this.Icon" ) ) );
      this.IsMdiContainer = true;
      this.Name = "MainForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Load += new System.EventHandler( this.OnLoad );
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.OnFormClosing );
      this.statusBar.ResumeLayout( false );
      this.mainMenuStrip.ResumeLayout( false );
      this.mainMenuStrip.PerformLayout();
      this.ResumeLayout( false );
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel statusBar;
		private System.Windows.Forms.Label statusBarLabel;
		private WeifenLuo.WinFormsUI.Docking.DockPanel dockPanel;
		private System.Windows.Forms.MenuStrip mainMenuStrip;
		private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem undoToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem redoToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ProgressBar statusBarProgressBar;
		private System.Windows.Forms.Panel statusBarPanel;
		private System.Windows.Forms.Panel toolbars;
    private System.Windows.Forms.Timer scriptTimer;
	}
}