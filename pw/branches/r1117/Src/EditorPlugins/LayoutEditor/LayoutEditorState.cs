using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using libdb.Diagnostics;
using Win32;
using EditorPlugins.UIScene;

namespace EditorPlugins.LayoutEditor
{
	internal class LayoutEditorState
	{
		private static readonly Point invalidPoint = new Point( -1, -1 );
		protected static Point InvalidPoint { get { return invalidPoint; } }

		private readonly LayoutEditorControl control = null;
		public LayoutEditorControl Control { get { return control; } }

		protected LayoutEditorState( LayoutEditorControl control ) { this.control = control; }

		public virtual void OnPaint( Editor2DSceneControl uiRender ) { }

		public virtual void OnEnterState( LayoutEditorState previousState )
    {
    }

		public virtual void OnLeaveState( LayoutEditorState newState ) 
    {
    }

    public virtual void ShowContextMenu( Control ctrl, Point at ) { }

    public virtual void OnMouseMove( MouseEventArgs e ) { }

    public virtual void OnMouseDown( MouseEventArgs e ) { }

    public virtual void OnMouseUp( MouseEventArgs e ) { }

    public virtual void OnKeyDown( KeyEventArgs e ) { }

    public virtual void OnKeyUp( KeyEventArgs e ) { }

		#region KeyModifiers
		protected static bool IsShift
		{
			get
			{
				return User.GetKeyState( User.VK_SHIFT ) >> 15 > 0;
			}
		}
		protected static bool IsAlt
		{
			get
			{
				return User.GetKeyState( User.VK_MENU ) >> 15 > 0;
			}
		}
		protected static bool IsControl
		{
			get
			{
				return User.GetKeyState( User.VK_CONTROL ) >> 15 > 0;
			}
		}
		#endregion
	}
}
