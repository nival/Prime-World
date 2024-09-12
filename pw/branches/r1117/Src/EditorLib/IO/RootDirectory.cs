using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace EditorLib.IO
{
	public partial class RootDirectory : Form
	{
		public RootDirectory()
		{
			InitializeComponent();
			Location = new Point( Screen.PrimaryScreen.WorkingArea.Left + (Screen.PrimaryScreen.WorkingArea.Width - Size.Width) / 2, Screen.PrimaryScreen.WorkingArea.Top + (Screen.PrimaryScreen.WorkingArea.Height - Size.Height) / 2 );
			folderBrowserDialog.SelectedPath = Path.GetFullPath( "..\\Data\\" );
		}

		private void ok_Click( object sender, EventArgs e )
		{
			DialogResult = DialogResult.OK;
			Close();
		}

		private void cancel_Click( object sender, EventArgs e )
		{
			DialogResult = DialogResult.Cancel;
			Close();
		}

		private void openFileButton_Click( object sender, EventArgs e )
		{
			string temp = Environment.CurrentDirectory;
			DialogResult rez = folderBrowserDialog.ShowDialog( this );
			Environment.CurrentDirectory = temp;
			if ( rez == DialogResult.OK )
				fileSystemRoot.Text = folderBrowserDialog.SelectedPath;
		}
	}
}
