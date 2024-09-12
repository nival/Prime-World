using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using EditorLib;
using EditorLib.Menu;
using EditorLib.Panels;

namespace EditorPlugins.Commands.Help
{
	public sealed class HotkeysMenuCommand : IEditorCommand
	{
		private HotkeyPanel hotkeyPanel;

		public override string Name
		{
			get { return "Hotkeys"; }
		}
		public override void Execute( IEditorWinApplication application )
		{
			if ( hotkeyPanel != null )
			{
				hotkeyPanel.Close();
				hotkeyPanel.Dispose();
			}
			hotkeyPanel = new HotkeyPanel();
			hotkeyPanel.ShowDialog();
		}
	}
}
