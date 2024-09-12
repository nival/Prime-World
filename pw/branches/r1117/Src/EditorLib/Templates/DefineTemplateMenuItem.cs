using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Menu;

namespace EditorLib.Templates
{
	public class DefineTemplateMenuItem : IEditorCommand
	{
		public override void Execute( EditorLib.IEditorWinApplication application )
		{
			DefineTemplateForm form = new DefineTemplateForm();
			form.ShowDialog();
		}

		public override string Name { get { return "Define Template..."; } }
	}
}
