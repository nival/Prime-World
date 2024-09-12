using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace EditorLib.IO
{
	public partial class SVNFileSysConfigure : Form
	{
		public SVNFileSysConfigure()
		{
			InitializeComponent();
			Location = new Point( Screen.PrimaryScreen.WorkingArea.Left + ( Screen.PrimaryScreen.WorkingArea.Width - Size.Width ) / 2, Screen.PrimaryScreen.WorkingArea.Top + ( Screen.PrimaryScreen.WorkingArea.Height - Size.Height ) / 2 );

		}

		private void button3_Click( object sender, EventArgs e )
		{
			var folderBrowserDialog = new FolderBrowserDialog();

			string temp = Environment.CurrentDirectory;
			DialogResult rez = folderBrowserDialog.ShowDialog( this );
			Environment.CurrentDirectory = temp;
			if ( rez == DialogResult.OK )
				tbFSRoot.Text = folderBrowserDialog.SelectedPath;
		}


	}
}
