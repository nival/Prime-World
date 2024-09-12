
namespace EditorPlugins.Scene.Viewers
{
	partial class SceneHierarchyPanel
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.noResourceLabel = new System.Windows.Forms.Label();
			this.treeHierarchy = new EditorLib.ImprovedTreeView();
			this.SuspendLayout();
			// 
			// noResourceLabel
			// 
			this.noResourceLabel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.noResourceLabel.Location = new System.Drawing.Point( 0, 0 );
			this.noResourceLabel.Name = "noResourceLabel";
			this.noResourceLabel.Size = new System.Drawing.Size( 292, 276 );
			this.noResourceLabel.TabIndex = 1;
			this.noResourceLabel.Text = "No resource loaded";
			this.noResourceLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// treeHierarchy
			// 
			this.treeHierarchy.AdditionalTextColor = System.Drawing.SystemColors.GrayText;
			this.treeHierarchy.AdditionalTextFont = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic );
			this.treeHierarchy.CheckBoxes = true;
			this.treeHierarchy.Dock = System.Windows.Forms.DockStyle.Fill;
			this.treeHierarchy.DrawMode = System.Windows.Forms.TreeViewDrawMode.OwnerDrawText;
			this.treeHierarchy.HideSelection = false;
			this.treeHierarchy.Indent = 10;
			this.treeHierarchy.Location = new System.Drawing.Point( 0, 0 );
			this.treeHierarchy.Name = "treeHierarchy";
			this.treeHierarchy.Size = new System.Drawing.Size( 292, 276 );
			this.treeHierarchy.TabIndex = 3;
			this.treeHierarchy.AfterCheck += new System.Windows.Forms.TreeViewEventHandler( this.OnAfterCheckNode );
			this.treeHierarchy.AfterSelect += new System.Windows.Forms.TreeViewEventHandler( this.OnAfterSelectNode );
			this.treeHierarchy.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler( this.OnNodeMouseClick );
			// 
			// SceneHierarchyPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 292, 276 );
			this.Controls.Add( this.treeHierarchy );
			this.Controls.Add( this.noResourceLabel );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.Name = "SceneHierarchyPanel";
			this.TabText = "Scene Hierarchy";
			this.Text = "Scene Hierarchy";
			this.ResumeLayout( false );

		}

		#endregion

    private System.Windows.Forms.Label noResourceLabel;
    private EditorLib.ImprovedTreeView treeHierarchy;
	}
}