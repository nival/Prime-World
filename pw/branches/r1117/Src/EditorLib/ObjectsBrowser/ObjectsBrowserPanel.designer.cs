namespace EditorLib.ObjectsBrowser
{
	partial class ObjectsBrowserPanel
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
			if ( disposing && ( components != null ) )
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
      this.objectsBrowser = new EditorLib.ObjectsBrowser.ObjectsBrowser();
      this.SuspendLayout();
      // 
      // objectsBrowser
      // 
      this.objectsBrowser.CurrentFolder = "";
      this.objectsBrowser.Dock = System.Windows.Forms.DockStyle.Fill;
      this.objectsBrowser.Location = new System.Drawing.Point( 0, 0 );
      this.objectsBrowser.Name = "objectsBrowser";
      this.objectsBrowser.Size = new System.Drawing.Size( 235, 780 );
      this.objectsBrowser.TabIndex = 3;
      this.objectsBrowser.OpenItemEvent += new System.EventHandler<EditorLib.ObjectsBrowser.DBIDEventArgs>( this.OnOpenItem );
      // 
      // ObjectsBrowserPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 235, 780 );
      this.Controls.Add( this.objectsBrowser );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.HideOnClose = true;
      this.KeyPreview = true;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "ObjectsBrowserPanel";
      this.TabText = "Objects Browser";
      this.Text = "Objects Browser";
      this.ResumeLayout( false );

		}

		#endregion

    private ObjectsBrowser objectsBrowser;


  }
}
