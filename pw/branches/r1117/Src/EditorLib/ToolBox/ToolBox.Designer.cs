namespace EditorLib.ToolBox
{
	partial class ToolBox
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
			if ( disposing && (components != null) )
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
      this.treeView = new System.Windows.Forms.TreeView();
      this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip( this.components );
      this.addCategoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.addItemFromEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
      this.renameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
      this.removeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.contextMenuStrip.SuspendLayout();
      this.SuspendLayout();
      // 
      // treeView
      // 
      this.treeView.AllowDrop = true;
      this.treeView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.treeView.ContextMenuStrip = this.contextMenuStrip;
      this.treeView.Dock = System.Windows.Forms.DockStyle.Fill;
      this.treeView.FullRowSelect = true;
      this.treeView.HideSelection = false;
      this.treeView.LabelEdit = true;
      this.treeView.Location = new System.Drawing.Point( 0, 0 );
      this.treeView.Name = "treeView";
      this.treeView.ShowLines = false;
      this.treeView.Size = new System.Drawing.Size( 240, 554 );
      this.treeView.TabIndex = 0;
      this.treeView.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler( this.OnTreeViewAfterLabelEdit );
      this.treeView.DragDrop += new System.Windows.Forms.DragEventHandler( this.OnTreeViewDragDrop );
      this.treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler( this.OnTreeViewAfterSelect );
      this.treeView.DragEnter += new System.Windows.Forms.DragEventHandler( this.OnTreeViewDragEnter );
      this.treeView.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler( this.OnTreeViewNodeMouseClick );
      this.treeView.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler( this.OnTreeViewBeforeLabelEdit );
      this.treeView.ItemDrag += new System.Windows.Forms.ItemDragEventHandler( this.OnTreeViewItemDrag );
      this.treeView.DragOver += new System.Windows.Forms.DragEventHandler( this.OnTreeViewDragOver );
      // 
      // contextMenuStrip
      // 
      this.contextMenuStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.addCategoryToolStripMenuItem,
            this.addItemFromEditorToolStripMenuItem,
            this.toolStripMenuItem1,
            this.renameToolStripMenuItem,
            this.toolStripMenuItem2,
            this.removeToolStripMenuItem} );
      this.contextMenuStrip.Name = "contextMenuStrip";
      this.contextMenuStrip.Size = new System.Drawing.Size( 188, 126 );
      this.contextMenuStrip.Opening += new System.ComponentModel.CancelEventHandler( this.contextMenuStrip_Opening );
      // 
      // addCategoryToolStripMenuItem
      // 
      this.addCategoryToolStripMenuItem.Name = "addCategoryToolStripMenuItem";
      this.addCategoryToolStripMenuItem.Size = new System.Drawing.Size( 187, 22 );
      this.addCategoryToolStripMenuItem.Text = "Add Category";
      this.addCategoryToolStripMenuItem.Click += new System.EventHandler( this.OnAddCategoryClicked );
      // 
      // addItemFromEditorToolStripMenuItem
      // 
      this.addItemFromEditorToolStripMenuItem.Name = "addItemFromEditorToolStripMenuItem";
      this.addItemFromEditorToolStripMenuItem.Size = new System.Drawing.Size( 187, 22 );
      this.addItemFromEditorToolStripMenuItem.Text = "Add Item From Editor";
      this.addItemFromEditorToolStripMenuItem.Click += new System.EventHandler( this.OnAddItemClicked );
      // 
      // toolStripMenuItem1
      // 
      this.toolStripMenuItem1.Name = "toolStripMenuItem1";
      this.toolStripMenuItem1.Size = new System.Drawing.Size( 184, 6 );
      // 
      // renameToolStripMenuItem
      // 
      this.renameToolStripMenuItem.Name = "renameToolStripMenuItem";
      this.renameToolStripMenuItem.Size = new System.Drawing.Size( 187, 22 );
      this.renameToolStripMenuItem.Text = "Rename";
      this.renameToolStripMenuItem.Click += new System.EventHandler( this.OnRenameItemClicked );
      // 
      // toolStripMenuItem2
      // 
      this.toolStripMenuItem2.Name = "toolStripMenuItem2";
      this.toolStripMenuItem2.Size = new System.Drawing.Size( 184, 6 );
      // 
      // removeToolStripMenuItem
      // 
      this.removeToolStripMenuItem.Name = "removeToolStripMenuItem";
      this.removeToolStripMenuItem.Size = new System.Drawing.Size( 187, 22 );
      this.removeToolStripMenuItem.Text = "Remove";
      this.removeToolStripMenuItem.Click += new System.EventHandler( this.OnRemoveItemClicked );
      // 
      // ToolBox
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add( this.treeView );
      this.Name = "ToolBox";
      this.Size = new System.Drawing.Size( 240, 554 );
      this.contextMenuStrip.ResumeLayout( false );
      this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.TreeView treeView;
    private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
    private System.Windows.Forms.ToolStripMenuItem addCategoryToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem addItemFromEditorToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
    private System.Windows.Forms.ToolStripMenuItem renameToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
    private System.Windows.Forms.ToolStripMenuItem removeToolStripMenuItem;
	}
}
