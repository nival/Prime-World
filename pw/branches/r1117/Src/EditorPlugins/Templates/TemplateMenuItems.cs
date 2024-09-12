using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Menu;
using libdb.DB;

namespace EditorPlugins.Templates
{
	public class NewTemplateMenuItem : IEditorCommand
	{
		public readonly static Guid NewObjectFromTemplateMenuGroupGuid = new Guid( "b5806dff-57a6-4bfa-94f6-24aff00cf89d" );

		public override void Execute( EditorLib.IEditorWinApplication application )
		{
			DefineTemplateForm form = new DefineTemplateForm( application );
			form.ShowDialog();
		}

		public override string Name { get { return "New Template..."; } }
	}

	public class NewObjectFromTemplateMenuItem : IEditorCommand
	{
		private readonly string name = string.Empty;
		private readonly DBID template = DBID.Empty;

		public NewObjectFromTemplateMenuItem( string name, DBID template )
		{
			this.name = name;
			this.template = template;
		}

		public override void Execute( EditorLib.IEditorWinApplication application )
		{
			NewObjectTemplateForm form = new NewObjectTemplateForm( application, template );
			form.ShowDialog();
		}

		public override string Name { get { return name; } }
	}
}
