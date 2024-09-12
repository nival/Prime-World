using System;
using System.Collections.Generic;
using System.Text;

namespace EditorPlugins.Commands
{
	public class ReloadGeometryCommand : EditorLib.Menu.IEditorCommand
	{
		public override void Execute(EditorLib.IEditorWinApplication application)
		{
			EditorNative.EditorRender.ReloadGeometry();
		}

		public override string Name
		{
			get { return "Reload Geometry"; }
		}
	}
}
