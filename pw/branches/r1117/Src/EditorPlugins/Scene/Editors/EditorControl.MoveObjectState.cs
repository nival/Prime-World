
using System.Collections.Generic;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class MoveObjectState : EditorControlState
		{
			private readonly CompositeMovingController controller;
			private readonly CursorPositionWatcher watcher;

			internal MoveObjectState( EditorControl _editorControl, CompositeMovingController _controller )
				: base( _editorControl )
			{
				controller = _controller;
				watcher = new CursorPositionWatcher( SceneControl );
			}

			protected override void OnActivated()
			{
				base.OnActivated();
        StartDBOperation( "Object Moving" );

				EditorControl.TileMap.RemoveObjects(Scene.SelectedObjects);
			}

      public override void OnUpdate()
			{
				if ( EditorControl.pickLeft.IsDeactivated )
				{
					SetMainState();
				}
				else if ( watcher.TileChanged )
				{
					controller.Move( EditorControl.nonTileMoving.IsActive );
          Scene.CurrentManipulator = Scene.CurrentManipulator;
				}

				if ( EditorControl.IsShowTileSet )
          EditorControl.TileMap.Draw();
			}

			protected override void OnDeactivated()
			{
				base.OnDeactivated();

				EditorControl.TileMap.PlaceObjects(Scene.SelectedObjects);

        if ( IsContainsHeightObject( Scene.SelectedObjects ) )
          Scene.CalcObjectHeightMap();

        Scene.ReplaceAllObjectsOnTerrain();

			  LeaveDBOperation();
      }

      private bool IsContainsHeightObject(IEnumerable<SceneElement> selection)
      {
			  foreach (SceneElement element in selection)
			  {
          var gso = element as GameSceneObject;

          if( gso == null )
            continue;

          if ( gso.GetGameObject().heightObject )
            return true;  
			  }

        return false;
      }
    }
	}
}
