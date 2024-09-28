using EditorNative;
using EditorPlugins.Scene.Editors.Drawing.TerrainLayers;
using libdb.DB;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class DrawModeState : EditorControlState
		{
			private readonly IEditorControlDrawingExtension drawingExtension;
      private bool isLastActivePick;
      private bool isLastActiveAlternativePick;

			internal DrawModeState( EditorControl editorControl, IEditorControlDrawingExtension drawingExtension )
				: base( editorControl )
			{
				this.drawingExtension = drawingExtension;
        isLastActivePick = false;
        isLastActiveAlternativePick = false;
      }

 			protected override void OnActivated()
      {
        base.OnActivated();
        drawingExtension.OnActivated();
      }

      public override void OnUpdate()
			{
				PickResult pickRes = EditorControl.SceneControl.Scene.Pick( EditorControl.SceneControl.CursorPosition );
				if ( pickRes.HasTerrainIntersection )
				{
					Utility.DrawCircleOnTerrain( pickRes.TerrainIntersection, 0.15F, 8, System.Drawing.Color.Red,
																			EditorControl.Scene.SceneTerrain, false );
					Utility.DrawCircleOnTerrain( pickRes.TerrainIntersection, BrushSettingsControl.brushSize/2, 64, System.Drawing.Color.Red,
																			EditorControl.Scene.SceneTerrain, false );
				}

				if ( EditorControl.pickLeft.IsActive )
				{
          if ( isLastActiveAlternativePick )
          {
            DataBase.UndoRedoManager.Commit();
            DataBase.UndoRedoManager.Start( "1.Drawing" );
          }
          else if ( !isLastActivePick )
          {
            DataBase.UndoRedoManager.Start( "2.Drawing" );
          }
          
          isLastActiveAlternativePick = false;
          isLastActivePick = true;

					if ( drawingExtension.CanBeginDrawing )
					{
            var pickResult = SceneControl.Pick();
            if ( pickResult.HasTerrainIntersection )
            {
              drawingExtension.BeginDrawing().Draw( pickResult );
            }
          }
				}
        else if ( EditorControl.pickRight.IsActive )
        {
          if ( isLastActivePick )
          {
            DataBase.UndoRedoManager.Commit();
            DataBase.UndoRedoManager.Start( "3.Drawing" );
          }
          else if ( !isLastActiveAlternativePick )
          {
            DataBase.UndoRedoManager.Start( "4.Drawing" );
          }
          
          isLastActivePick = false;
          isLastActiveAlternativePick = true;

          if ( drawingExtension.CanBeginDrawing )
          {
            var pickResult = SceneControl.Pick();
            if ( pickResult.HasTerrainIntersection )
            {
              drawingExtension.BeginDrawing().Erase( pickResult );
            }
          }
        }
        else
        {
          if ( isLastActivePick || isLastActiveAlternativePick )
          {
            DataBase.UndoRedoManager.Commit();
          }
          isLastActiveAlternativePick = false;
          isLastActivePick = false;
        }
			}

      protected override void OnDeactivated()
      {
        base.OnDeactivated();
        drawingExtension.OnDeactivated();
      }

		}
	}
}
