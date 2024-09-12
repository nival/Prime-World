using System;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using EditorNative.Terrain;

namespace EditorPlugins.Scene.Editors
{
  partial class EditorControl
  {
    private sealed class SelectByFrameState : EditorControlState
    {
      private readonly Vector2 initialCursorPosition;

      internal SelectByFrameState( EditorControl editorControl )
        : base( editorControl )
      {
        this.initialCursorPosition = SceneControl.CursorPosition;
      }

      #region Overrides.

      protected override void OnActivated()
      {
        base.OnActivated();
        Scene.SelectionFrame.Show();
      }

      public override void OnUpdate()
      {
				if ( EditorControl.pickLeft.IsDeactivated || !EditorControl.pickLeft.IsActive )
				{
					if ( WidgetState.CallBackWidjet != null )
					{
						SetState( WidgetState.CallBackWidjet );
					}
					else
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
        if ( Math.Abs( Scene.SelectionFrame.Width ) < TerrainUtils.CursorGranularity && Math.Abs( Scene.SelectionFrame.Height ) < TerrainUtils.CursorGranularity )
        {
          EditorControl.SelectObjectAtCursor();
        }
        else
        {
          float left = Scene.SelectionFrame.Left;
          float top = Scene.SelectionFrame.Top;
          float right = left + Scene.SelectionFrame.Width;
          float bottom = top + Scene.SelectionFrame.Height;

          Correct( ref left, ref right );
          Correct( ref top, ref bottom );
          EditorControl.SelectObjectByRect( left, top, right, bottom );
        }

        Scene.SelectionFrame.Hide();

				if ( EditorControl.SplineSelectionMode )
					RomeveNotSplines();

        base.OnDeactivated();
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
			private void RomeveNotSplines()
			{
				for(int i = Scene.SelectedObjects.Count-1;i>-1;--i)
				{
					GameSceneObject gso = Scene.SelectedObjects[i] as GameSceneObject;
					if(gso!=null)
					{
						if ( !EditorControl.IsSpline( gso ) )
							Scene.Deselect( Scene.SelectedObjects[i]);
					}
				}
			}

			#endregion
		}
  }
}
