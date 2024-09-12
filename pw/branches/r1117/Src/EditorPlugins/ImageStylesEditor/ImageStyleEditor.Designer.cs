namespace EditorPlugins.ImageStylesEditor
{
	
	partial class ImageStyleEditor
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
			this.imageSylesEditor = new EditorPlugins.ImageStylesEditor.ImageStylesEditorControl();
			this.SuspendLayout();
			// 
			// imageSylesEditor1
			// 
			this.imageSylesEditor.Dock = System.Windows.Forms.DockStyle.Fill;
			this.imageSylesEditor.Location = new System.Drawing.Point( 0, 0 );
			this.imageSylesEditor.Name = "imageSylesEditor1";
			this.imageSylesEditor.Size = new System.Drawing.Size( 519, 342 );
			this.imageSylesEditor.TabIndex = 0;
			// 
			// ImageStyleEditor
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoScroll = true;
			this.AutoScrollMinSize = new System.Drawing.Size( 519, 342 );
			this.ClientSize = new System.Drawing.Size( 519, 342 );
			this.Controls.Add( this.imageSylesEditor );
			this.Name = "ImageStyleEditor";
			this.Text = "ImageStyleEditor";
			this.ResumeLayout( false );

		}

		#endregion

		private EditorPlugins.ImageStylesEditor.ImageStylesEditorControl imageSylesEditor;
	}
	
}