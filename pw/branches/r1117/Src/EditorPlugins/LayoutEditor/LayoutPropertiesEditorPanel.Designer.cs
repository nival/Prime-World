using System.Windows.Forms;
namespace EditorPlugins.LayoutEditor
{
	partial class LayoutPropertiesEditorPanel
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
			this.propertyGrid = new System.Windows.Forms.PropertyGrid();
			this.SuspendLayout();
			// 
			// propertyGrid
			// 
			this.propertyGrid.BackColor = System.Drawing.SystemColors.Control;
			this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
			this.propertyGrid.LineColor = System.Drawing.SystemColors.ControlLight;
			this.propertyGrid.Location = new System.Drawing.Point( 0, 0 );
			this.propertyGrid.Name = "propertyGrid";
			this.propertyGrid.Size = new System.Drawing.Size( 176, 428 );
			this.propertyGrid.TabIndex = 0;
			this.propertyGrid.ToolbarVisible = false;
			this.propertyGrid.PropertySort = PropertySort.NoSort;
			// 
			// LayoutPropertiesEditorPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 176, 428 );
			this.Controls.Add( this.propertyGrid );
			this.HideOnClose = true;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "LayoutPropertiesEditorPanel";
			this.TabText = "Layout Properties Editor";
			this.Text = "Layout Properties Editor";
			this.ResumeLayout( false );

		}

		#endregion

		public PropertyGrid propertyGrid;
	}
}