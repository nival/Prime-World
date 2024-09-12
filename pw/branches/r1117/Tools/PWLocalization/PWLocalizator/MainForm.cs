using System;
using System.Collections.Specialized;
using System.IO;
using System.Windows.Forms;

namespace PWLocalizator
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();

			bwUpdateData.DoWork += OnUpdatingData;
			bwUpdateData.ProgressChanged += OnProgressChanged;
			bwUpdateData.RunWorkerCompleted += OnDataUpdateCompleted;

			bwCollectData.DoWork += OnCollectingData;
			bwCollectData.ProgressChanged += OnProgressChanged;
			bwCollectData.RunWorkerCompleted += OnCollectCompleted;
		}

		#region Event Handlers

		private void MainForm_Load( object sender, EventArgs e )
		{
			txtDataFolder.Text = UserSettings.DataFolder;
		}

		private void btnBrowse_Click( object sender, EventArgs e )
		{
			var dialog = new FolderBrowserDialog();
			dialog.ShowNewFolderButton = false;
			dialog.Description = "Please select Prime World Data folder";

			if ( dialog.ShowDialog() == DialogResult.OK )
			{
				string dataFolder = dialog.SelectedPath;
				txtDataFolder.Text = dataFolder;
				UserSettings.DataFolder = dataFolder;
			}
		}

		private bool ValidateFolder()
		{
			if ( !Directory.Exists( txtDataFolder.Text ) )
			{
				MessageBox.Show( "Directory doesn't exist. Please select correct Data folder.",
					Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Error );

				txtDataFolder.Focus();

				return false;
			}

			return true;
		}

		private void btnToExcel_Click( object sender, EventArgs e )
		{
			if(!ValidateFolder())
				return;

			var dialog = new SaveFileDialog();
			dialog.Filter = "Excel xml files (*.xml)|*.xml";
			dialog.SupportMultiDottedExtensions = true;
			dialog.OverwritePrompt = true;
			dialog.CheckPathExists = true;

			if ( dialog.ShowDialog() != DialogResult.OK )
				return;

			pnlProgress.Visible = true;
			pnlCommands.Visible = false;

			bwCollectData.RunWorkerAsync( new string[] { txtDataFolder.Text, dialog.FileName } );
		}

		private void OnCollectingData( object sender, System.ComponentModel.DoWorkEventArgs e )
		{
			string[] args = (string[])e.Argument;

			string folder = args[0];
			string excelFile = args[1];

			bwCollectData.ReportProgress( 0, "Collecting data" );
			NameValueCollection result = TextRefProcessor.CollectTextRefs( folder );

			bwCollectData.ReportProgress( 0, "Creating Excel file" );
			TextRefProcessor.CreateExcelFile( excelFile, result );

			e.Result = excelFile;
		}
		
		private void OnCollectCompleted( object sender, System.ComponentModel.RunWorkerCompletedEventArgs e )
		{
			pnlProgress.Visible = false;
			pnlCommands.Visible = true;

			if ( e.Error != null )
			{
				string msg = String.Format( "An error occurred: {0}", e.Error.Message );
				MessageBox.Show( msg, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Error );
			}
			else
			{
				string msg = string.Format("File '{0}' created successfuly", e.Result);
				MessageBox.Show( msg, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Information );
			}
		}

		private void btnToData_Click( object sender, EventArgs e )
		{
			if ( !ValidateFolder() )
				return;

			var dialog = new OpenFileDialog();
			dialog.Filter = "Excel xml files (*.xml)|*.xml";
			dialog.SupportMultiDottedExtensions = true;
			dialog.CheckPathExists = true;

			if ( dialog.ShowDialog() != DialogResult.OK )
				return;

			pnlProgress.Visible = true;
			pnlCommands.Visible = false;

			bwUpdateData.RunWorkerAsync( new string[]{txtDataFolder.Text, dialog.FileName} );
		}

		private void OnUpdatingData( object sender, System.ComponentModel.DoWorkEventArgs e )
		{
			string[] args = (string[])e.Argument;

			string folder = args[0];
			string excelFile = args[1];

			bwUpdateData.ReportProgress(0, "Reading Excel file");
			NameValueCollection result = TextRefProcessor.ReadExcelFile( excelFile );

			foreach (string key in result.Keys)
			{
				if(string.IsNullOrEmpty(result[key]))
				{
					string msg = "Not all data are translated.\nEmpty entries are ignored.\nPlease pay attention to it.";
					MessageBox.Show(msg, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
					break;
				}
			}

			bwUpdateData.ReportProgress( 0, "Updating Data folder" );
			TextRefProcessor.UpdateTextRefs( folder, result, false );
		}

		private void OnProgressChanged( object sender, System.ComponentModel.ProgressChangedEventArgs e )
		{
			string text = (string)e.UserState;
			lblStatus.Text = text;
		}

		private void OnDataUpdateCompleted( object sender, System.ComponentModel.RunWorkerCompletedEventArgs e )
		{
			pnlProgress.Visible = false;
			pnlCommands.Visible = true;

			if ( e.Error != null )
			{
				string msg = String.Format( "An error occurred: {0}", e.Error.Message );
				MessageBox.Show( msg, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Error );
			}
			else
			{
				MessageBox.Show( "Data update successfuly", Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Information );
			}
		}

		#endregion

	}
}
