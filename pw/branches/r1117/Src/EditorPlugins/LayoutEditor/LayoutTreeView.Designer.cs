namespace EditorPlugins.LayoutEditor
{
	partial class LayoutTreeView
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
      this.layoutTree = new EditorPlugins.LayoutEditor.AdvancedTreeView();
      this.SuspendLayout();
      // 
      // layoutTree
      // 
      this.layoutTree.AllowDrop = true;
      this.layoutTree.CheckBoxes = true;
      this.layoutTree.Dock = System.Windows.Forms.DockStyle.Fill;
      this.layoutTree.DrawMode = System.Windows.Forms.TreeViewDrawMode.OwnerDrawText;
      this.layoutTree.HideSelection = false;
      this.layoutTree.Location = new System.Drawing.Point( 0, 0 );
      this.layoutTree.Name = "layoutTree";
      this.layoutTree.Size = new System.Drawing.Size( 330, 589 );
      this.layoutTree.TabIndex = 0;
      this.layoutTree.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler( this.layoutTree_NodeMouseDoubleClick );
      this.layoutTree.AfterCheck += new System.Windows.Forms.TreeViewEventHandler( this.layoutTree_AfterCheck );
      this.layoutTree.AfterCollapse += new System.Windows.Forms.TreeViewEventHandler( this.layoutTree_AfterCollapse );
      this.layoutTree.DragLeave += new System.EventHandler( this.layoutTree_DragLeave );
      this.layoutTree.DrawNode += new System.Windows.Forms.DrawTreeNodeEventHandler( this.layoutTree_DrawNode );
      this.layoutTree.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler( this.layoutTree_AfterLabelEdit );
      this.layoutTree.MouseUp += new System.Windows.Forms.MouseEventHandler( this.layoutTree_MouseUp );
      this.layoutTree.DragDrop += new System.Windows.Forms.DragEventHandler( this.layoutTree_DragDrop );
      this.layoutTree.AfterSelect += new System.Windows.Forms.TreeViewEventHandler( this.layoutTree_AfterSelect );
      this.layoutTree.AfterExpand += new System.Windows.Forms.TreeViewEventHandler( this.layoutTree_AfterExpand );
      this.layoutTree.ItemDrag += new System.Windows.Forms.ItemDragEventHandler( this.layoutTree_ItemDrag );
      this.layoutTree.DragOver += new System.Windows.Forms.DragEventHandler( this.layoutTree_DragOver );
      // 
      // LayoutTreeView
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 330, 589 );
      this.Controls.Add( this.layoutTree );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.Name = "LayoutTreeView";
      this.TabText = "UI Layout TreeView";
      this.Text = "UI Layout TreeView";
      this.ResumeLayout( false );

		}

		#endregion

    private AdvancedTreeView layoutTree;
	}
}
