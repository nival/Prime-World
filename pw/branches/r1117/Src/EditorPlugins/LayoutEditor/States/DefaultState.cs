using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using libdb.Diagnostics;
using libdb.DB;
using EditorPlugins.UIScene;
using DBTypes;

namespace EditorPlugins.LayoutEditor.States
{
	internal class DefaultState : PreselectionState
	{
		public DefaultState( LayoutEditorControl control )
			: base( control )
		{
    }

		public override void OnEnterState( LayoutEditorState previousState ) 
		{
      base.OnEnterState( previousState );
			Control.EditorApplication.Panels.GetSingletonPanel<EditorLib.PropertiesEditor.PropertiesEditorPanel>().SelectedObject = null;
			Control.EditorApplication.Panels.GetSingletonPanel<LayoutTreeView>().SetSelectedLayout( null );
		}

    public override void OnPaint( Editor2DSceneControl uiRender )
		{
			base.OnPaint( uiRender );
			if ( PreSelectedWindows == null )
				return;
			for ( int i = 0; i < PreSelectedWindows.Count; ++i )
			{
				uiRender.DrawSelection( Control.GetWindowRectangle( PreSelectedWindows[i] ), SelectedState.SelectedPen.Color, true, true );
			}
		}

		protected override void SelectWindow( UILayout _window )
		{
      List<UILayout> windows = null;
			if ( _window != null )
			{
        windows = new List<UILayout>();
        windows.Add( _window );
			}
			Control.SetSelection( windows );
		}

    public override void OnMouseUp( MouseEventArgs e )
    {
      if ( e.Button != MouseButtons.Left )
        return;

      if ( SelectorView.Height > MOUSE_CLICK_DIST && SelectorView.Width > MOUSE_CLICK_DIST )
			{
        List<UILayout> windows = Control.GetWindowsInRect( SelectorView );
				Control.SetSelection( windows );
			}
			else
			{
				List<UILayout> windows = Control.GetWindowsUnderPoint( e.Location );
        UILayout selectedWindow = windows.Count > 0 ? windows[0] : null;
				SelectWindow( selectedWindow );
			}
      base.OnMouseUp( e );
    }
	}
}
