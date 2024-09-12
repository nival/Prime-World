using libdb.DB;
namespace EditorLib.BacklinksInfo
{
	partial class BacklinksInfo
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
      this.backlinks = new System.Windows.Forms.ListView();
      this.Linked = new System.Windows.Forms.ColumnHeader();
      this.SuspendLayout();
      // 
      // backlinks
      // 
      this.backlinks.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.Linked} );
      this.backlinks.Dock = System.Windows.Forms.DockStyle.Fill;
      this.backlinks.GridLines = true;
      this.backlinks.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
      this.backlinks.Location = new System.Drawing.Point( 0, 0 );
      this.backlinks.Name = "backlinks";
      this.backlinks.Size = new System.Drawing.Size( 482, 163 );
      this.backlinks.TabIndex = 1;
      this.backlinks.UseCompatibleStateImageBehavior = false;
      this.backlinks.View = System.Windows.Forms.View.Details;
      this.backlinks.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler( this.OnBacklinksMouseDoubleClick );
      // 
      // Linked
      // 
      this.Linked.Text = "Linked";
      this.Linked.Width = 256;
      // 
      // BacklinksInfo
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 482, 163 );
      this.Controls.Add( this.backlinks );
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "BacklinksInfo";
      this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Float;
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.TabText = "";
      this.Text = "Backlinks";
      this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.ListView backlinks;
		private System.Windows.Forms.ColumnHeader Linked;
		//private DBID resultLink = null;
	}
}