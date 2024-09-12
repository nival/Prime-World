using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using DBTypes;
using EditorLib.ToolBox;

namespace EditorPlugins.LayoutEditor.States
{
	internal class NewWindowState : BoundsControlState
	{
    internal const uint MIN_SIZE = 8;

		private Type windowType = null;
    private UILayout prototype = null;

		public NewWindowState( LayoutEditorControl control, Type _windowType )
			: base( control, true )
		{ 
			windowType = _windowType;
		}

    public NewWindowState( LayoutEditorControl control, UILayout _prototype )
      : base( control, true )
    {
      prototype = _prototype;
    }

    public override void OnEnterState( LayoutEditorState previousState )
		{
			base.OnEnterState( previousState );
			Control.SetCursor( Cursors.Cross );
		}

		public override void OnLeaveState( LayoutEditorState newState )
		{
			base.OnLeaveState( newState );
			Control.SetCursor( Cursors.Default );
		}

		public override void OnMouseUp( MouseEventArgs e )
		{
			if ( e.Button == MouseButtons.Left )
			{
				if ( SelectorView.Height > MIN_SIZE && SelectorView.Width > MIN_SIZE )
				{
					List<UILayout> windows = Control.GetWindowsUnderPoint( WhereLeftMouseDown );
          if ( 0 != windows.Count )
          {
            ToolBoxPanel toolBoxPanel = Control.EditorApplication.Panels.GetSingletonPanel<ToolBoxPanel>();
            //toolBoxPanel.SelectNull();
            if ( windowType != null )
              Control.CreateWindow( windowType, windows[windows.Count - 1], SelectorView );
            else
              Control.CreateWindowFromPrototype( prototype, windows[windows.Count - 1], SelectorView );
          }
				}
			}
			base.OnMouseUp( e );
		}
	}
}
