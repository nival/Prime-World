using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace EditorLib.Menu
{
	class MenuCommand: MenuItem
	{
		private IEditorCommand command = null;

		private Keys wantedHotkey = Keys.None;
		
    public MenuCommand( int _sortIndex, IEditorCommand _command, Keys _wantedHotkey )
			: base( _sortIndex, _command.Name )
		{
			command = _command;
			wantedHotkey = _wantedHotkey;
		}
		
    public override bool Visible
		{
			get
			{
				return command.Visible;
			}
		}
		
    public override bool Enabled
		{
			get
			{
				return command.Enabled;
			}
		}
		
    public override string Name
		{
			get { return command.Name; }
		}
		
    public Keys WantedHotkey
		{
			get { return wantedHotkey; }
		}
		
    public void Execute( EditorLib.IEditorWinApplication _application)
		{
			command.Execute( _application );
		}
		
    public System.Drawing.Bitmap Image
		{
			get { return command.Image; }
		}

	  public bool IsChecked
	  {
      get { return command.IsChecked; }
	  }
	}
}
