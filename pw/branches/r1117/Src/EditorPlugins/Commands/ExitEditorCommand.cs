using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace EditorPlugins.Commands
{
	public sealed class ExitEditorCommand : EditorLib.Menu.IEditorCommand
	{
		private Form mainform = null;

		public ExitEditorCommand( Form _mainform ) { this.mainform = _mainform; }
		public override void Execute( EditorLib.IEditorWinApplication application )	{	mainform.Close();	}
		public override string Name	{	get { return "E&xit"; } }
	}
}
