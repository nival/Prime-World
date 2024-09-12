using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace River.Bot
{
	public partial class OptionsForm : Form
	{
		public OptionsForm( string masterUrl )
		{
			InitializeComponent();
			masterTextBox.Text = masterUrl;
		}

		private void OnVerify( object sender, LinkLabelLinkClickedEventArgs e )
		{
		}

		public string MasterUrl { get { return masterTextBox.Text; } }
	}
}
