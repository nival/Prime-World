using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using libdb.DB;
using DBTypes;

namespace EditorPlugins.LayoutEditor.States
{
	/// <summary>
	/// Controls windows selection process
	/// </summary>
	internal abstract class PreselectionState : BoundsControlState
	{
		internal const int MOUSE_CLICK_DIST = 3;

		private List<UILayout> preSelectedWindows = null;
    protected List<UILayout> PreSelectedWindows { get { return preSelectedWindows; } }

		private static Pen parentPen = new Pen( parentColor, 1.0f );
		private static System.Drawing.Color parentColor = System.Drawing.Color.Blue;
		
		internal static System.Drawing.Color ParentColor
		{
			get
			{
				return parentColor;
			}
			set
			{
				parentColor = value;
				parentPen = new Pen( value, 1.0f );
				parentPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
			}
		}

		public PreselectionState( LayoutEditorControl control )
			: base( control )
		{ }

    private void OnContextMenu()
    {
      Point location = Control.PointToClient( Cursor.Position );
      menu.MenuItems.Clear();
      ConstructMenu( location, false, true );
      menu.Show( Control, location );
    }
		
		public override void OnMouseMove( System.Windows.Forms.MouseEventArgs e )
		{
			base.OnMouseMove( e );
			if ( e.Button == MouseButtons.Left )
			{
				if ( SelectorView.Height > MOUSE_CLICK_DIST && SelectorView.Width > MOUSE_CLICK_DIST )
				{
					preSelectedWindows = Control.GetWindowsInRect( SelectorView );
				}
				else
				{
					preSelectedWindows = null;
				}
			}
		}

		protected abstract void SelectWindow( UILayout _window );
		private void Select( object sender, EventArgs e )
		{
      menu.MenuItems.Clear();
			MenuItem item = sender as MenuItem;
			if ( item == null )
				return;

      UILayout window = item.Tag as UILayout;
			if ( window != null )
			{
				SelectWindow( window );
			}
		}

		protected System.Windows.Forms.ContextMenu menu = new ContextMenu();
    protected virtual void ConstructMenu( Point location, bool showStates, bool checkCursorPos )
		{
      List<UILayout> windows = Control.GetWindowsUnderPoint( location );
      if ( windows.Count > 0 )
      {
        foreach ( UILayout window in windows )
        {
          string itemName = "Select " + window.name + " ";
          itemName += string.Format( "({0})", window.GetType().Name );
          MenuItem itemMenu = new MenuItem( itemName, Select );
          itemMenu.Tag = window;
          menu.MenuItems.Add( itemMenu );
        }
      }
    }

		public override void OnMouseUp( MouseEventArgs e )
		{
			base.OnMouseUp( e );
			if ( e.Button == MouseButtons.Left )
			{
				preSelectedWindows = null;
			}
      else if ( e.Button == MouseButtons.Right )
      {
        OnContextMenu();
      }
		}
	}
}
