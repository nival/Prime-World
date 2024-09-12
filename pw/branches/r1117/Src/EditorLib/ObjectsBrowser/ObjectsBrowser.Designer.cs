namespace EditorLib.ObjectsBrowser
{
  partial class ObjectsBrowser
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
      if( disposing && ( components != null ) )
      {
        components.Dispose();
      }
      base.Dispose( disposing );
    }

    #region Component Designer generated code

    /// <summary> 
    /// Required method for Designer support - do not modify 
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( ObjectsBrowser ) );
      this.objectsBrowserToolStrip = new System.Windows.Forms.ToolStrip();
      this.newFolderButton = new System.Windows.Forms.ToolStripButton();
      this.tsNewItemButton = new System.Windows.Forms.ToolStripDropDownButton();
      this.typeDesiredItemNameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.tsNewItemSearchTb = new System.Windows.Forms.ToolStripTextBox();
      this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
      this.recentItemsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      this.tsbFilter = new System.Windows.Forms.ToolStripSplitButton();
      this.mnuEditFilter = new System.Windows.Forms.ToolStripMenuItem();
      this.mnuClearFilter = new System.Windows.Forms.ToolStripMenuItem();
      this.tsbSort = new System.Windows.Forms.ToolStripDropDownButton();
      this.mnuSortByName = new System.Windows.Forms.ToolStripMenuItem();
      this.mnuSortByType = new System.Windows.Forms.ToolStripMenuItem();
      this.tsbRefresh = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
      this.tsbBookmarks = new System.Windows.Forms.ToolStripDropDownButton();
      this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
      this.btnBack = new System.Windows.Forms.ToolStripSplitButton();
      this.btnForward = new System.Windows.Forms.ToolStripSplitButton();
      this.objectsBrowserControl = new EditorLib.ObjectsBrowser.ObjectsBrowserControl();
      this.myBreadcrumbControl1 = new EditorLib.ObjectsBrowser.BreadcrumbControl();
      this.objectsBrowserToolStrip.SuspendLayout();
      this.SuspendLayout();
      // 
      // objectsBrowserToolStrip
      // 
      this.objectsBrowserToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.objectsBrowserToolStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.newFolderButton,
            this.tsNewItemButton,
            this.toolStripSeparator2,
            this.tsbFilter,
            this.tsbSort,
            this.tsbRefresh,
            this.toolStripSeparator5,
            this.tsbBookmarks,
            this.toolStripSeparator3,
            this.btnBack,
            this.btnForward} );
      this.objectsBrowserToolStrip.Location = new System.Drawing.Point( 0, 25 );
      this.objectsBrowserToolStrip.Name = "objectsBrowserToolStrip";
      this.objectsBrowserToolStrip.Size = new System.Drawing.Size( 236, 25 );
      this.objectsBrowserToolStrip.TabIndex = 4;
      this.objectsBrowserToolStrip.TabStop = true;
      // 
      // newFolderButton
      // 
      this.newFolderButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.newFolderButton.Image = global::EditorLib.EditorLibResources.NewFolder;
      this.newFolderButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.newFolderButton.Name = "newFolderButton";
      this.newFolderButton.Size = new System.Drawing.Size( 23, 22 );
      this.newFolderButton.Text = "toolStripButton1";
      this.newFolderButton.ToolTipText = "Create folder";
      this.newFolderButton.Click += new System.EventHandler( this.OnNewFolderButtonClick );
      // 
      // tsNewItemButton
      // 
      this.tsNewItemButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.tsNewItemButton.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.typeDesiredItemNameToolStripMenuItem,
            this.tsNewItemSearchTb,
            this.toolStripSeparator4,
            this.recentItemsToolStripMenuItem} );
      this.tsNewItemButton.Image = global::EditorLib.EditorLibResources.NewItem;
      this.tsNewItemButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.tsNewItemButton.Name = "tsNewItemButton";
      this.tsNewItemButton.Size = new System.Drawing.Size( 29, 22 );
      this.tsNewItemButton.Text = "Create New Item";
      this.tsNewItemButton.DropDownOpened += new System.EventHandler( this.tsNewItemButton_DropDownOpened );
      // 
      // typeDesiredItemNameToolStripMenuItem
      // 
      this.typeDesiredItemNameToolStripMenuItem.Font = new System.Drawing.Font( "Tahoma", 8.25F, System.Drawing.FontStyle.Bold );
      this.typeDesiredItemNameToolStripMenuItem.Name = "typeDesiredItemNameToolStripMenuItem";
      this.typeDesiredItemNameToolStripMenuItem.Size = new System.Drawing.Size( 280, 22 );
      this.typeDesiredItemNameToolStripMenuItem.Text = "Type desired item name to search:";
      // 
      // tsNewItemSearchTb
      // 
      this.tsNewItemSearchTb.Name = "tsNewItemSearchTb";
      this.tsNewItemSearchTb.Size = new System.Drawing.Size( 220, 23 );
      this.tsNewItemSearchTb.KeyDown += new System.Windows.Forms.KeyEventHandler( this.tsNewItemSearchTb_KeyUp );
      this.tsNewItemSearchTb.TextChanged += new System.EventHandler( this.toolStripComboBox1_TextUpdate );
      // 
      // toolStripSeparator4
      // 
      this.toolStripSeparator4.Name = "toolStripSeparator4";
      this.toolStripSeparator4.Size = new System.Drawing.Size( 277, 6 );
      // 
      // recentItemsToolStripMenuItem
      // 
      this.recentItemsToolStripMenuItem.Font = new System.Drawing.Font( "Tahoma", 8.25F, System.Drawing.FontStyle.Bold );
      this.recentItemsToolStripMenuItem.Name = "recentItemsToolStripMenuItem";
      this.recentItemsToolStripMenuItem.Size = new System.Drawing.Size( 280, 22 );
      this.recentItemsToolStripMenuItem.Text = "Recent items:";
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size( 6, 25 );
      // 
      // tsbFilter
      // 
      this.tsbFilter.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.tsbFilter.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuEditFilter,
            this.mnuClearFilter} );
      this.tsbFilter.Image = global::EditorLib.EditorLibResources.filterOff;
      this.tsbFilter.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.tsbFilter.Name = "tsbFilter";
      this.tsbFilter.Size = new System.Drawing.Size( 32, 22 );
      this.tsbFilter.Text = "Extensions Filter";
      this.tsbFilter.ButtonClick += new System.EventHandler( this.tsbFilter_ButtonClick );
      // 
      // mnuEditFilter
      // 
      this.mnuEditFilter.Name = "mnuEditFilter";
      this.mnuEditFilter.Size = new System.Drawing.Size( 131, 22 );
      this.mnuEditFilter.Text = "Set Filter ...";
      this.mnuEditFilter.Click += new System.EventHandler( this.mnuEditFilter_Click );
      // 
      // mnuClearFilter
      // 
      this.mnuClearFilter.Name = "mnuClearFilter";
      this.mnuClearFilter.Size = new System.Drawing.Size( 131, 22 );
      this.mnuClearFilter.Text = "Clear";
      this.mnuClearFilter.Click += new System.EventHandler( this.mnuClearFilter_Click );
      // 
      // tsbSort
      // 
      this.tsbSort.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.tsbSort.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuSortByName,
            this.mnuSortByType} );
      this.tsbSort.Image = global::EditorLib.EditorLibResources.sortByName;
      this.tsbSort.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.tsbSort.Name = "tsbSort";
      this.tsbSort.Size = new System.Drawing.Size( 29, 22 );
      this.tsbSort.Text = "Sort by name/type";
      // 
      // mnuSortByName
      // 
      this.mnuSortByName.Image = global::EditorLib.EditorLibResources.sortByName;
      this.mnuSortByName.Name = "mnuSortByName";
      this.mnuSortByName.Size = new System.Drawing.Size( 144, 22 );
      this.mnuSortByName.Text = "Sort by name";
      this.mnuSortByName.Click += new System.EventHandler( this.mnuSortByName_Click );
      // 
      // mnuSortByType
      // 
      this.mnuSortByType.Image = global::EditorLib.EditorLibResources.sortByType;
      this.mnuSortByType.Name = "mnuSortByType";
      this.mnuSortByType.Size = new System.Drawing.Size( 144, 22 );
      this.mnuSortByType.Text = "Sort by type";
      this.mnuSortByType.Click += new System.EventHandler( this.mnuSortByType_Click );
      // 
      // tsbRefresh
      // 
      this.tsbRefresh.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.tsbRefresh.Image = global::EditorLib.EditorLibResources.Refresh;
      this.tsbRefresh.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.tsbRefresh.Name = "tsbRefresh";
      this.tsbRefresh.Size = new System.Drawing.Size( 23, 22 );
      this.tsbRefresh.Text = "Reload folder contents from disk";
      this.tsbRefresh.Click += new System.EventHandler( this.tsbRefresh_Click );
      // 
      // toolStripSeparator5
      // 
      this.toolStripSeparator5.Name = "toolStripSeparator5";
      this.toolStripSeparator5.Size = new System.Drawing.Size( 6, 25 );
      // 
      // tsbBookmarks
      // 
      this.tsbBookmarks.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.tsbBookmarks.Image = global::EditorLib.EditorLibResources.BookmarkFolder;
      this.tsbBookmarks.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.tsbBookmarks.Name = "tsbBookmarks";
      this.tsbBookmarks.Size = new System.Drawing.Size( 29, 22 );
      this.tsbBookmarks.Text = "Bookmarks and Recent Folders";
      // 
      // toolStripSeparator3
      // 
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new System.Drawing.Size( 6, 25 );
      // 
      // btnBack
      // 
      this.btnBack.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnBack.Enabled = false;
      this.btnBack.Image = global::EditorLib.EditorLibResources.history_back;
      this.btnBack.ImageTransparentColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 178 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 255 ) ) ) ) );
      this.btnBack.Name = "btnBack";
      this.btnBack.Size = new System.Drawing.Size( 32, 22 );
      this.btnBack.Text = "toolStripSplitButton1";
      this.btnBack.ToolTipText = "Back";
      this.btnBack.ButtonClick += new System.EventHandler( this.btnBack_ButtonClick );
      this.btnBack.DropDownOpening += new System.EventHandler( this.btnBack_DropDownOpening );
      this.btnBack.DropDownItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler( this.OnDropDownItemClicked );
      // 
      // btnForward
      // 
      this.btnForward.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnForward.Enabled = false;
      this.btnForward.Image = global::EditorLib.EditorLibResources.history_fwd;
      this.btnForward.ImageTransparentColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 178 ) ) ) ), ( (int)( ( (byte)( 0 ) ) ) ), ( (int)( ( (byte)( 255 ) ) ) ) );
      this.btnForward.Name = "btnForward";
      this.btnForward.Size = new System.Drawing.Size( 32, 20 );
      this.btnForward.Text = "Forward";
      this.btnForward.ButtonClick += new System.EventHandler( this.btnForward_ButtonClick );
      this.btnForward.DropDownOpening += new System.EventHandler( this.btnForward_DropDownOpening );
      this.btnForward.DropDownItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler( this.OnDropDownItemClicked );
      // 
      // objectsBrowserControl
      // 
      this.objectsBrowserControl.CurrentFolder = null;
      this.objectsBrowserControl.Dock = System.Windows.Forms.DockStyle.Fill;
      this.objectsBrowserControl.ExtensionsFilter = ( (System.Collections.Generic.List<string>)( resources.GetObject( "objectsBrowserControl.ExtensionsFilter" ) ) );
      this.objectsBrowserControl.FilterType = null;
      this.objectsBrowserControl.FullRowSelect = true;
      this.objectsBrowserControl.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
      this.objectsBrowserControl.HideSelection = false;
      this.objectsBrowserControl.Location = new System.Drawing.Point( 0, 50 );
      this.objectsBrowserControl.Margin = new System.Windows.Forms.Padding( 0 );
      this.objectsBrowserControl.Name = "objectsBrowserControl";
      this.objectsBrowserControl.SelectedFolder = null;
      this.objectsBrowserControl.SelectedObject = null;
      this.objectsBrowserControl.Size = new System.Drawing.Size( 236, 213 );
      this.objectsBrowserControl.TabIndex = 5;
      this.objectsBrowserControl.UseCompatibleStateImageBehavior = false;
      this.objectsBrowserControl.View = System.Windows.Forms.View.Details;
      this.objectsBrowserControl.ViewState = EditorLib.ObjectsBrowser.ObjectsBrowserViewState.FoldersAndFiles;
      this.objectsBrowserControl.ChangeSelectedItemEvent += new System.EventHandler( this.OnChangeSelectedItem );
      this.objectsBrowserControl.OpenItemEvent += new System.EventHandler<EditorLib.ObjectsBrowser.DBIDEventArgs>( this.OnOpenItem );
      this.objectsBrowserControl.ChangeSelectedFolderEvent += new System.EventHandler( this.OnChangeSelectedFolder );
      // 
      // myBreadcrumbControl1
      // 
      this.myBreadcrumbControl1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.myBreadcrumbControl1.LinkedObjectsBrowser = this.objectsBrowserControl;
      this.myBreadcrumbControl1.Location = new System.Drawing.Point( 0, 0 );
      this.myBreadcrumbControl1.Name = "myBreadcrumbControl1";
      this.myBreadcrumbControl1.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
      this.myBreadcrumbControl1.Size = new System.Drawing.Size( 236, 25 );
      this.myBreadcrumbControl1.TabIndex = 3;
      this.myBreadcrumbControl1.Text = "myBreadcrumbControl1";
      // 
      // ObjectsBrowser
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add( this.objectsBrowserControl );
      this.Controls.Add( this.objectsBrowserToolStrip );
      this.Controls.Add( this.myBreadcrumbControl1 );
      this.Name = "ObjectsBrowser";
      this.Size = new System.Drawing.Size( 236, 263 );
      this.Load += new System.EventHandler( this.OnLoad );
      this.KeyDown += new System.Windows.Forms.KeyEventHandler( this.KeyPressProcess );
      this.objectsBrowserToolStrip.ResumeLayout( false );
      this.objectsBrowserToolStrip.PerformLayout();
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private ObjectsBrowserControl objectsBrowserControl;
    private System.Windows.Forms.ToolStrip objectsBrowserToolStrip;
    private System.Windows.Forms.ToolStripButton newFolderButton;
    private System.Windows.Forms.ToolStripDropDownButton tsNewItemButton;
    private System.Windows.Forms.ToolStripMenuItem typeDesiredItemNameToolStripMenuItem;
    private System.Windows.Forms.ToolStripTextBox tsNewItemSearchTb;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
    private System.Windows.Forms.ToolStripMenuItem recentItemsToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
    private System.Windows.Forms.ToolStripDropDownButton tsbBookmarks;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
    private System.Windows.Forms.ToolStripSplitButton btnBack;
    private System.Windows.Forms.ToolStripSplitButton btnForward;
		private BreadcrumbControl myBreadcrumbControl1;
		private System.Windows.Forms.ToolStripSplitButton tsbFilter;
		private System.Windows.Forms.ToolStripMenuItem mnuClearFilter;
		private System.Windows.Forms.ToolStripMenuItem mnuEditFilter;
		private System.Windows.Forms.ToolStripDropDownButton tsbSort;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
		private System.Windows.Forms.ToolStripMenuItem mnuSortByName;
		private System.Windows.Forms.ToolStripMenuItem mnuSortByType;
    private System.Windows.Forms.ToolStripButton tsbRefresh;
  }
}
