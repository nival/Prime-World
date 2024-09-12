using System;
using System.Collections.Generic;
using System.Text;

namespace EditorPlugins.Commands
{
	public class ReloadPFXCommand : EditorLib.Menu.IEditorCommand
	{
		public override void Execute(EditorLib.IEditorWinApplication application)
		{
			EditorNative.EditorRender.ReloadPFX();
		}

		public override string Name
		{
			get { return "Reload All PFX"; }
		}
	}
}
