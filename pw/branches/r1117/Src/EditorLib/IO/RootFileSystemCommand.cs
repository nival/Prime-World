using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Menu;
using libdb.IO;

namespace EditorLib.IO
{
	internal sealed class RootFileSystemCommand: IEditorCommand
	{
		public override void Execute( IEditorWinApplication application )
		{
			RootFileSystemConfigurator config = new RootFileSystemConfigurator( application.Application );
			config.ShowDialog();
		}

		public override string Name
		{
			get { return "File System Configuration"; }
		}
	}
}
