using System;
using System.Drawing;
using System.Windows.Forms;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.Terrain;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class PickAlternativeState : EditorControlState
		{
			#region Private members.

      private readonly Vector2 initialCursorPosition;

      #endregion

			#region Initialization.

			internal PickAlternativeState( EditorControl editorControl )
				: base( editorControl )
			{
        this.initialCursorPosition = SceneControl.CursorPosition;
			}

			#endregion

			#region Overrides.

      protected override void OnActivated()
      {
        base.OnActivated();
        Scene.SelectionFrame.Show();
      }

      public override void OnUpdate()
			{
				if ( EditorControl.pickRight.IsDeactivated || !EditorControl.pickRight.IsActive )
				{
					SetMainState();
				}
        else
        {
          var delta = Scene.ConvertCursorPosition2( SceneControl.CursorPosition ) - Scene.ConvertCursorPosition2( initialCursorPosition );

          Scene.SelectionFrame.Location = Scene.ConvertCursorPosition2( initialCursorPosition );
          Scene.SelectionFrame.Size = delta;
        }
      }

      protected override void OnDeactivated()
      {
        var menu = new ContextMenuStrip();
        PickResult pickResult = null;

      	menu.KeyUp += delegate(object sender, KeyEventArgs e)
      	              	{
      	              		EditorControl.BindsManager.OnKeyUp(e);
      	              	};

        if ( Math.Abs( Scene.SelectionFrame.Width ) < TerrainUtils.CursorGranularity && Math.Abs( Scene.SelectionFrame.Height ) < TerrainUtils.CursorGranularity )
        {
          pickResult = SceneControl.Pick();
        }
        else
        {
          float left = Scene.SelectionFrame.Left;
          float top = Scene.SelectionFrame.Top;
          float right = left + Scene.SelectionFrame.Width;
          float bottom = top + Scene.SelectionFrame.Height;

          Correct( ref left, ref right );
          Correct( ref top, ref bottom );

          pickResult = Scene.PickByFrame( left, top, right, bottom );
        }
        if ( pickResult != null && pickResult.PickedElements.Length > 0 )
        {

          foreach ( var element in pickResult.PickedElements )
          {
            var menuItemName = EditorControl.extension.GetMenuItemNameBy( element );
            if ( !string.IsNullOrEmpty( menuItemName ) )
            {
              var menuItem = new ToolStripMenuItem( menuItemName );
              menuItem.Tag = element;
              menu.Items.Add( menuItem );
              menuItem.Click += ( _1, _2 ) => EditorControl.SelectObject( (SceneElement)menuItem.Tag );
              menuItem.MouseEnter += ( _1, _2 ) => EditorControl.PreselectObject( (SceneElement)menuItem.Tag );
              menuItem.MouseLeave += ( _1, _2 ) => EditorControl.RestoreLockedSelection();
            }
          }
        }
        if ( menu.Items.Count > 0 )
        {
          menu.Closed += menu_Closed;

          EditorControl.LockSelection();
          if ( !EditorControl.add.IsActive )
            Scene.DeselectAll();

          var cursorPisition = SceneControl.CursorPosition;
          menu.Show( SceneControl, new Point( (int)cursorPisition.X, (int)cursorPisition.Y ) );
        }
        else
          Scene.SelectionFrame.Hide();

        base.OnDeactivated();
      }

      private void menu_Closed( object sender, ToolStripDropDownClosedEventArgs e )
      {
        Scene.SelectionFrame.Hide();
        if ( e.CloseReason != ToolStripDropDownCloseReason.ItemClicked )
        {
          EditorControl.RestoreLockedSelection();
          EditorControl.ReleaseSelection();
        }
				else
					EditorControl.OnAfterSelectionChanged();
      }

			#endregion

			#region Private helper methods.

      private void Correct( ref float less, ref float greater )
      {
        if ( less > greater )
        {
          float temp = less;
          less = greater;
          greater = temp;
        }
      }

			#endregion
		}
	}
}
