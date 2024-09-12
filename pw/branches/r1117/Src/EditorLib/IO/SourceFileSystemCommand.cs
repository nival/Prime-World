using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Menu;
using libdb.IO;
using System.Windows.Forms;
using System.IO;

namespace EditorLib.IO
{
	internal sealed class SourceFileSystemCommand : IEditorCommand
	{
		private readonly SourceFileSystem sourceFileSystem;

		internal SourceFileSystemCommand( SourceFileSystem _sourceFileSystem )
		{
			sourceFileSystem = _sourceFileSystem;
		}

		public override void Execute( IEditorWinApplication application )
		{
			var dialog = new FolderBrowserDialog() { SelectedPath = sourceFileSystem.RootPath.Replace('/','\\') };
			
			if ( dialog.ShowDialog() == DialogResult.OK )
			{
				sourceFileSystem.RootPath = dialog.SelectedPath;
			}
		}

		public override string Name
		{
			get { return "Select Source Folder ..."; }
		}
	}
}
