using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using EditorPlugins.UIScene;

namespace EditorPlugins.LayoutEditor.States
{
	/// <summary>
	/// Control bounds using mouse down/move/up events. Draw this frame.
	/// </summary>
	internal abstract class BoundsControlState : LayoutEditorState
	{
		private Point whereLeftMouseDown = LayoutEditorState.InvalidPoint;
		protected Point WhereLeftMouseDown { get { return whereLeftMouseDown; } }
    private bool doSnap = false;

		public BoundsControlState( LayoutEditorControl control )
			: base( control )
		{
      SetSelectorView( LayoutEditorState.InvalidPoint, LayoutEditorState.InvalidPoint );
		}

    public BoundsControlState( LayoutEditorControl control, bool snap )
      : base( control )
    {
      doSnap = snap;
      SetSelectorView( LayoutEditorState.InvalidPoint, LayoutEditorState.InvalidPoint );
    }

    public override void OnPaint( Editor2DSceneControl uiRender )
		{
			base.OnPaint( uiRender );
			if ( SelectorView.Bottom > 0 && selectorView.Location != LayoutEditorState.InvalidPoint )
			{
				uiRender.DrawRectangle( SelectorView, Control.SelectionPen1.Color );
			}

		}
		private Rectangle selectorView = new Rectangle( 0, 0, 0, 0 );
		protected Rectangle SelectorView { get { return LayoutEditorControl.NormalizeRectangle( selectorView ); } }
		private void SetSelectorView( Point downPoint, Point currentPoint )
		{
      if ( doSnap && Control.Snapper != null )
      {
        selectorView.X = Control.Snapper.SnapX( downPoint.X );
        selectorView.Y = Control.Snapper.SnapY( downPoint.Y );
        selectorView.Height = Control.Snapper.SnapY( currentPoint.Y ) - selectorView.Y;
        selectorView.Width = Control.Snapper.SnapX( currentPoint.X ) - selectorView.X;
      }
      else
      {
        selectorView.Height = currentPoint.Y - downPoint.Y;
        selectorView.Width = currentPoint.X - downPoint.X;
        selectorView.X = downPoint.X;
        selectorView.Y = downPoint.Y;
      }

			Control.Invalidate();
		}

		public override void OnMouseMove( MouseEventArgs e )
		{
			base.OnMouseMove( e );
			if ( e.Button == MouseButtons.Left )
			{
				SetSelectorView( whereLeftMouseDown, e.Location );
			}
		}

    public override void OnMouseDown( MouseEventArgs e )
		{
      base.OnMouseDown( e );
      if ( e.Button == MouseButtons.Left )
        whereLeftMouseDown = e.Location;
		}

    public override void OnMouseUp( MouseEventArgs e )
    {
      base.OnMouseUp( e );
      if ( e.Button == MouseButtons.Left )
      {
        whereLeftMouseDown = LayoutEditorState.InvalidPoint;
        SetSelectorView( LayoutEditorState.InvalidPoint, LayoutEditorState.InvalidPoint );
      }
		}

	}
}
