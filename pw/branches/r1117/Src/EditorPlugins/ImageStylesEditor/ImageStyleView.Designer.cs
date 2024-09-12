namespace EditorPlugins.ImageStylesEditor
{
	
	partial class ImageStyleView
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
      this.SuspendLayout();
      // 
      // ImageStyleView
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.AutoScroll = true;
      this.Name = "ImageStyleView";
      this.Size = new System.Drawing.Size(929, 683);
      this.MouseLeave += new System.EventHandler(this.ImageStyleView_MouseLeave);
      this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ImageStyleView_MouseMove);
      this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ImageStyleView_MouseDown);
      this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ImageStyleView_MouseUp);
      this.ResumeLayout(false);

		}

		#endregion
	}
	 
}
