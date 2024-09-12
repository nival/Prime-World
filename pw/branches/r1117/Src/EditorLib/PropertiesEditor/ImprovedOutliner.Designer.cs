namespace EditorLib.PropertiesEditor
{
	public partial class ImprovedOutliner
	{
		// Initialize the control elements.
		public void InitializeComponent()
		{
			this.treeView = new EditorLib.ImprovedTreeView();
			this.SuspendLayout();
			// 
			// treeView
			// 
			this.treeView.AdditionalTextColor = System.Drawing.SystemColors.GrayText;
			this.treeView.AdditionalTextFont = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic );
			this.treeView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.treeView.DrawMode = System.Windows.Forms.TreeViewDrawMode.OwnerDrawText;
			this.treeView.FullRowSelect = true;
			this.treeView.HotTracking = true;
			this.treeView.Indent = 10;
			this.treeView.LevelColors = new System.Drawing.Color[0];
			this.treeView.Location = new System.Drawing.Point( 0, 0 );
			this.treeView.Name = "treeView";
			this.treeView.ShowLines = false;
			this.treeView.Size = new System.Drawing.Size( 150, 150 );
			this.treeView.TabIndex = 0;
			this.treeView.AfterCollapse += new System.Windows.Forms.TreeViewEventHandler( this.OnAfterNodeCollapse );
			this.treeView.MouseClick += new System.Windows.Forms.MouseEventHandler( this.OnNodeMouseClick );
			this.treeView.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler( this.OnBeforeNodeExpand );
			this.treeView.AfterExpand += new System.Windows.Forms.TreeViewEventHandler( this.OnAfterNodeExpand );
			// 
			// ImprovedOutliner
			// 
			this.Controls.Add( this.treeView );
			this.Name = "ImprovedOutliner";
			this.ResumeLayout( false );

		}
	}
}