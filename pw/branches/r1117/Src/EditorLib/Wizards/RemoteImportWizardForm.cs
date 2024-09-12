using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Settings;

namespace EditorLib.Wizards
{
	public partial class RemoteImportWizardForm : Form
	{
		public RemoteImportWizardForm()
		{
			InitializeComponent();
		}

		private void RemoteImportWizardForm_Load( object sender, EventArgs e )
		{
		 tbURL.Text = EditorCommonApplication.ApplicationSingleton.Settings.Get<RemoteImportWizardConfig>().URL;
		}


		private void btnCancel_Click( object sender, EventArgs e )
		{
			this.DialogResult = DialogResult.Cancel;
			this.Close();
		}

		private void btnRun_Click( object sender, EventArgs e )
		{
			EditorCommonApplication.ApplicationSingleton.Settings.Get<RemoteImportWizardConfig>().URL = tbURL.Text;
			this.DialogResult = DialogResult.Yes;
			this.Close();
		}

		private void btnSaveurl_Click( object sender, EventArgs e )
		{
			EditorCommonApplication.ApplicationSingleton.Settings.Get<RemoteImportWizardConfig>().URL = tbURL.Text;
			this.DialogResult = DialogResult.Cancel;
			this.Close();
		}



	}

	[ConfigObject( true )]
	public class RemoteImportWizardConfig : SimpleConfigObject
	{
		public string URL = "";
	}
}
