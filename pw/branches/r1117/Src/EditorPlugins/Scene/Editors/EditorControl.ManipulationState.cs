using System.Collections.Generic;
using EditorNative.SceneElements;
using EditorPlugins.Scene.Editors.Terrain;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class ManipulationState : EditorControlState
		{
			internal ManipulationState( EditorControl editorControl )
				: base( editorControl )
			{
			}

			protected override void OnActivated()
			{
				base.OnActivated();
        StartDBOperation( "Objects Manipulation" );
				
				EditorControl.TileMap.RemoveObjects( Scene.SelectedObjects );
        
        Scene.StartDragManipulator( EditorControl.IsCommonCenter );
			}

      public override void OnUpdate()
			{
        if ( EditorControl.pickLeft.IsDeactivated )
          SetMainState();
        else
          Scene.DragManipulator( SceneControl.CursorDelta, SceneControl.CursorPosition );
			}

			protected override void OnDeactivated()
			{
				base.OnDeactivated();

        Scene.EndDragManipulator();

				EditorControl.TileMap.PlaceObjects(Scene.SelectedObjects);

				List<ControlableTcvMarker> markers = new List<ControlableTcvMarker>();

				foreach(SceneElement sceneElement in Scene.SelectedObjects)
				{
					if(sceneElement is ControlableTcvMarker)
						markers.Add((ControlableTcvMarker) sceneElement);
				}

				RecalcTileHeights(markers);

				LeaveDBOperation();
				Scene.UncaptureManipulator();
			}
		}
	}
}
