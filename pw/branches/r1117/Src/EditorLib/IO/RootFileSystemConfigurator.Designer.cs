namespace EditorLib.IO
{
	partial class RootFileSystemConfigurator
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

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.fileSystemListView = new System.Windows.Forms.ListView();
			this.Type = new System.Windows.Forms.ColumnHeader();
			this.Description = new System.Windows.Forms.ColumnHeader();
			this.addFileSystemButton = new System.Windows.Forms.Button();
			this.deleteFileSystemButton = new System.Windows.Forms.Button();
			this.setWritable = new System.Windows.Forms.Button();
			this.addContextMenu = new System.Windows.Forms.ContextMenuStrip( this.components );
			this.closeButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// fileSystemListView
			// 
			this.fileSystemListView.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.Type,
            this.Description} );
			this.fileSystemListView.Location = new System.Drawing.Point( 12, 12 );
			this.fileSystemListView.MultiSelect = false;
			this.fileSystemListView.Name = "fileSystemListView";
			this.fileSystemListView.Size = new System.Drawing.Size( 640, 233 );
			this.fileSystemListView.TabIndex = 2;
			this.fileSystemListView.UseCompatibleStateImageBehavior = false;
			this.fileSystemListView.View = System.Windows.Forms.View.Details;
			this.fileSystemListView.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler( this.fileSystemListView_MouseDoubleClick );
			// 
			// Type
			// 
			this.Type.Text = "Type";
			this.Type.Width = 240;
			// 
			// Description
			// 
			this.Description.Text = "Description";
			this.Description.Width = 320;
			// 
			// addFileSystemButton
			// 
			this.addFileSystemButton.Location = new System.Drawing.Point( 12, 251 );
			this.addFileSystemButton.Name = "addFileSystemButton";
			this.addFileSystemButton.Size = new System.Drawing.Size( 75, 23 );
			this.addFileSystemButton.TabIndex = 3;
			this.addFileSystemButton.Text = "Add";
			this.addFileSystemButton.UseVisualStyleBackColor = true;
			this.addFileSystemButton.Click += new System.EventHandler( this.OnAddFileSystemButtonClick );
			// 
			// deleteFileSystemButton
			// 
			this.deleteFileSystemButton.Location = new System.Drawing.Point( 93, 251 );
			this.deleteFileSystemButton.Name = "deleteFileSystemButton";
			this.deleteFileSystemButton.Size = new System.Drawing.Size( 75, 23 );
			this.deleteFileSystemButton.TabIndex = 4;
			this.deleteFileSystemButton.Text = "Delete";
			this.deleteFileSystemButton.UseVisualStyleBackColor = true;
			this.deleteFileSystemButton.Click += new System.EventHandler( this.OnDeleteFileSystemButtonClick );
			// 
			// setWritable
			// 
			this.setWritable.Location = new System.Drawing.Point( 174, 251 );
			this.setWritable.Name = "setWritable";
			this.setWritable.Size = new System.Drawing.Size( 75, 23 );
			this.setWritable.TabIndex = 5;
			this.setWritable.Text = "Set Writable";
			this.setWritable.UseVisualStyleBackColor = true;
			this.setWritable.Click += new System.EventHandler( this.OnSetWritableClick );
			// 
			// addContextMenu
			// 
			this.addContextMenu.Name = "addContextMenu";
			this.addContextMenu.Size = new System.Drawing.Size( 61, 4 );
			this.addContextMenu.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler( this.OnAddContextMenuItemClicked );
			// 
			// closeButton
			// 
			this.closeButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.closeButton.Location = new System.Drawing.Point( 577, 251 );
			this.closeButton.Name = "closeButton";
			this.closeButton.Size = new System.Drawing.Size( 75, 23 );
			this.closeButton.TabIndex = 6;
			this.closeButton.Text = "Close";
			this.closeButton.UseVisualStyleBackColor = true;
			this.closeButton.Click += new System.EventHandler( this.OnCloseClick );
			// 
			// RootFileSystemConfigurator
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.closeButton;
			this.ClientSize = new System.Drawing.Size( 664, 281 );
			this.Controls.Add( this.closeButton );
			this.Controls.Add( this.setWritable );
			this.Controls.Add( this.deleteFileSystemButton );
			this.Controls.Add( this.addFileSystemButton );
			this.Controls.Add( this.fileSystemListView );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RootFileSystemConfigurator";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.Text = "RootFileSystemConfigurator";
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.ListView fileSystemListView;
		private System.Windows.Forms.ColumnHeader Type;
		private System.Windows.Forms.ColumnHeader Description;
		private System.Windows.Forms.Button addFileSystemButton;
		private System.Windows.Forms.Button deleteFileSystemButton;
		private System.Windows.Forms.Button setWritable;
		private System.Windows.Forms.ContextMenuStrip addContextMenu;
		private System.Windows.Forms.Button closeButton;



	}
}