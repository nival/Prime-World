using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Menu
{
	public interface IMenuUpdater
	{
		void UpdateMenu( IEditorWinApplication application );
	}
}
