using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using libdb.Diagnostics;

namespace EditorLib.Panels
{
	public partial class HotkeyPanel : Form
	{
		private System.Windows.Forms.TextBox txtHelp;

		public HotkeyPanel()
		{
			InitializeComponent();
			this.Name = "Hotkeys";
			this.Width = 300;
			this.Height = 600;
		}

		private void InitializeComponent()
		{
			this.txtHelp = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// txtHelp
			// 
			this.txtHelp.BackColor = System.Drawing.SystemColors.Window;
			this.txtHelp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.txtHelp.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtHelp.Location = new System.Drawing.Point( 0, 0 );
			this.txtHelp.Multiline = true;
			this.txtHelp.Name = "txtHelp";
			this.txtHelp.ReadOnly = true;
			this.txtHelp.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtHelp.Size = new System.Drawing.Size( 318, 466 );
			this.txtHelp.TabIndex = 0;
			this.txtHelp.TabStop = false;
			this.txtHelp.TextChanged += new System.EventHandler( this.txtHelp_TextChanged );
			// 
			// HotkeyPanel
			// 
			this.ClientSize = new System.Drawing.Size( 318, 466 );
			this.Controls.Add( this.txtHelp );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "HotkeyPanel";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Load += new System.EventHandler( this.HotkeyPanel_Load );
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		private void treeView1_AfterSelect( object sender, System.Windows.Forms.TreeViewEventArgs e )
		{

		}

		private void propertyGrid1_Click( object sender, EventArgs e )
		{

		}

		private void HotkeyPanel_Load( object sender, EventArgs e )
		{
			string filename = @"..\Profiles\Hotkeys.txt";

			if(File.Exists(filename) )
			{
				txtHelp.Text = File.ReadAllText(filename);
			}
			else
			{
				Log.TraceWarning("Can't find file \"{0}\"", filename);
			}
		}

		private void txtHelp_TextChanged( object sender, EventArgs e )
		{

		}

	}
}
