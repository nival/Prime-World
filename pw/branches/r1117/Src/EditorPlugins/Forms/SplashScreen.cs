using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using EditorLib;

namespace EditorPlugins.Forms
{
	public sealed partial class SplashScreen : Form
	{
		#region Private members.

		private readonly EditorWinApplication application;

		#endregion

		#region Initialization.

		public SplashScreen( EditorWinApplication application )
		{
			this.application = application;
			InitializeComponent();
			if ( TryLoadSplashImage( "splash" ) )
				FixFormSize();
		}

		#endregion

		#region Event handlers.

		private void OnOperationProgress( string message, int progress )
		{
			labelStatus.Text = message;
			progressBarStatus.Value = progress;
		}

		private void OnLoad( object sender, EventArgs e )
		{
			application.OperationExecutor.ProgressOperationEvent += new EditorLib.Operations.Executor.ProgressOperationEventHandler( OperationExecutor_ProgressOperationEvent );
			application.OperationExecutor.Start( application.Initialize, CloseSplashScreen );
		}

		private void OperationExecutor_ProgressOperationEvent( string messagge, int progress )
		{
			Invoke( new EditorLib.Operations.Executor.ProgressOperationEventHandler( OnOperationProgress ), messagge, progress );
		}

		private void OnClose( object sender, FormClosedEventArgs e )
		{
			application.OperationExecutor.ProgressOperationEvent -= new EditorLib.Operations.Executor.ProgressOperationEventHandler( OperationExecutor_ProgressOperationEvent );
		}

		#endregion

		#region Private helper methods.

		private bool TryLoadSplashImage( string fileName )
		{
			string fullFileName = Path.Combine( Application.StartupPath, fileName );
			foreach ( string extension in new string[] { ".bmp", ".png", ".jpg" } )
			{
				string thisFileName = Path.ChangeExtension( fullFileName, extension );
				try
				{
					if ( File.Exists( thisFileName ) )
					{
						pictureBox.Load( thisFileName );
						return true;
					}
				}
				catch { }
			}

			return false;
		}

		private void FixFormSize()
		{
			int dx = ClientSize.Width - pictureBox.ClientSize.Width;
			int dy = ClientSize.Height - pictureBox.ClientSize.Height;
			ClientSize = new Size( pictureBox.Image.Size.Width + dx, pictureBox.Image.Size.Height + dy );
			Location = new Point( Screen.PrimaryScreen.WorkingArea.Left + (Screen.PrimaryScreen.WorkingArea.Width - Size.Width) / 2, Screen.PrimaryScreen.WorkingArea.Top + (Screen.PrimaryScreen.WorkingArea.Height - Size.Height) / 2 );
		}

		private bool CloseSplashScreen( EditorLib.Operations.IOperationContext context )
		{
			Invoke( new Operation( Close ) );
			return true;
		}

		#endregion
	}
}
