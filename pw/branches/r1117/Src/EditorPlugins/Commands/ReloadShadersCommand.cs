using System;
using System.Collections.Generic;
using System.Text;

namespace EditorPlugins.Commands
{
	public class ReloadShadersCommand : EditorLib.Menu.IEditorCommand
	{
		public override void Execute(EditorLib.IEditorWinApplication application)
		{
			EditorNative.EditorRender.ReloadShaders();
		}

		public override string Name
		{
			get { return "Reload All Shaders"; }
		}
	}
}
	