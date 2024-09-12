using System;
using System.Collections.Generic;
using EditorNative;
using EditorNative.Manipulators;
using EditorPlugins.Scene.Editors.Terrain;
using libdb.DB;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		public sealed class NatureMapToolState : EditorControlState
		{
			public static float radius = 5;
			public static TerrainBrushType brushType = TerrainBrushType.Quadatic;

      public static Nullable<DBTypes.EFaction> affectedFaction = null;
      public static DBTypes.EFaction newFaction = DBTypes.EFaction.Neutral;


      internal NatureMapToolState(EditorControl editorControl) : base(editorControl) { }

			public override void OnUpdate()
			{
				PickResult pickResult = EditorControl.SceneControl.Scene.Pick(EditorControl.SceneControl.CursorPosition);

				if(pickResult.HasTerrainIntersection)
				{
					Utility.DrawCircleOnTerrain( pickResult.TerrainIntersection, 0.15F, 8, System.Drawing.Color.Red,
																			EditorControl.Scene.SceneTerrain , false);
					Utility.DrawCircleOnTerrain(pickResult.TerrainIntersection, radius, 64, System.Drawing.Color.Red,
					                            EditorControl.Scene.SceneTerrain, false);
				}

				if ( EditorControl.pickLeft.IsActivated || EditorControl.pickRight.IsActivated )
					OnPickActivated();
				if ( EditorControl.pickLeft.IsDeactivated || EditorControl.pickRight.IsDeactivated )
					OnPickDeactivated();

				if ( EditorControl.pickLeft.IsActive )
				{
          OnPickActive(pickResult, newFaction);
				}
				else if ( EditorControl.pickRight.IsActive )
				{
          OnPickActive(pickResult, DBTypes.EFaction.Neutral);
				}
				
				base.OnUpdate();
			}

			private void OnPickActivated()
			{
				StartDBOperation("Change Nature map with brush");
			}

			private void OnPickDeactivated()
			{
				LeaveDBOperation();
        //EditorControl.SceneControl.Scene.UpdateAllMSO();
			}

      private void OnPickActive(PickResult pickResult, DBTypes.EFaction faction)
			{
				pickResult = EditorControl.SceneControl.Scene.Pick(EditorControl.SceneControl.CursorPosition);

        var point = pickResult.TerrainIntersection;
        var elementIds = EditorControl.SceneControl.Scene.SceneTerrain.GetNatureMapElementIdsInCircle(point.X, point.Y, radius);

        int fromFact = affectedFaction.HasValue ? (int)affectedFaction : -1;
        DataBase.AddOperation(new NatureMapChangeOperation(EditorControl.terrainController, EditorControl.Scene, elementIds, fromFact, (int)faction));
			}


			private void DrawBrushBox(Vector3 point,float radius)
			{
				Vector3 point0 = point + new Vector3(-1,-1,0)*radius;
				Vector3 point1 = point + new Vector3(1,-1,0)*radius;
				Vector3 point2 = point + new Vector3( 1, 1, 0 ) * radius;
				Vector3 point3 = point + new Vector3( -1, 1, 0 ) * radius;
				EditorRender.DrawLine3D(point0, point1, System.Drawing.Color.Red, false);
				EditorRender.DrawLine3D( point1, point2, System.Drawing.Color.Red, false );
				EditorRender.DrawLine3D( point2, point3, System.Drawing.Color.Red, false );
				EditorRender.DrawLine3D( point3, point0, System.Drawing.Color.Red, false );
			}
		}
	}

}
