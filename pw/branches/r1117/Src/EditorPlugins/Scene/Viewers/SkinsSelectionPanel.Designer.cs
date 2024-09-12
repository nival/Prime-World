namespace EditorPlugins.Scene.Viewers
{
	partial class SkinsSelectionPanel
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
			this.skinsListBox = new System.Windows.Forms.CheckedListBox();
			this.noResourceLabel = new System.Windows.Forms.Label();
			this.grayPanel = new System.Windows.Forms.Panel();
			this.grayPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// skinsListBox
			// 
			this.skinsListBox.CheckOnClick = true;
			this.skinsListBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.skinsListBox.FormattingEnabled = true;
			this.skinsListBox.IntegralHeight = false;
			this.skinsListBox.Location = new System.Drawing.Point( 1, 1 );
			this.skinsListBox.Name = "skinsListBox";
			this.skinsListBox.Size = new System.Drawing.Size( 282, 264 );
			this.skinsListBox.Sorted = true;
			this.skinsListBox.TabIndex = 0;
			this.skinsListBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler( this.OnItemCheck );
			// 
			// noResourceLabel
			// 
			this.noResourceLabel.BackColor = System.Drawing.SystemColors.Control;
			this.noResourceLabel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.noResourceLabel.ForeColor = System.Drawing.Color.Blue;
			this.noResourceLabel.Location = new System.Drawing.Point( 1, 1 );
			this.noResourceLabel.Name = "noResourceLabel";
			this.noResourceLabel.Size = new System.Drawing.Size( 282, 264 );
			this.noResourceLabel.TabIndex = 3;
			this.noResourceLabel.Text = "No resource loaded or no skins in loaded resource";
			this.noResourceLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// grayPanel
			// 
			this.grayPanel.BackColor = System.Drawing.SystemColors.ControlDarkDark;
			this.grayPanel.Controls.Add( this.noResourceLabel );
			this.grayPanel.Controls.Add( this.skinsListBox );
			this.grayPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.grayPanel.Location = new System.Drawing.Point( 0, 0 );
			this.grayPanel.Name = "grayPanel";
			this.grayPanel.Padding = new System.Windows.Forms.Padding( 1 );
			this.grayPanel.Size = new System.Drawing.Size( 284, 266 );
			this.grayPanel.TabIndex = 4;
			// 
			// SkinPartsSelectorPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 284, 266 );
			this.Controls.Add( this.grayPanel );
			this.Name = "SkinPartsSelectorPanel";
			this.TabText = "Skins";
			this.Text = "Skins";
			this.grayPanel.ResumeLayout( false );
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.CheckedListBox skinsListBox;
		private System.Windows.Forms.Label noResourceLabel;
		private System.Windows.Forms.Panel grayPanel;
	}
}
