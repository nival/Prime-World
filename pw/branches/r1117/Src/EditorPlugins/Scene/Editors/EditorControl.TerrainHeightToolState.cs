using System;
using System.Collections.Generic;
using EditorNative;
using EditorNative.Manipulators;
using EditorPlugins.Scene.Editors.Terrain;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		public sealed class TerrainHeightToolState : EditorControlState
		{
			public static float radius = 10;
			public static float pressure = 0.8F;// Max 1 Min 0
			public static TerrainBrushType brushType = TerrainBrushType.Quadatic;
			public static TerrainAffectType affectType = TerrainAffectType.Up;


			private List<KeyValuePair<ControlableTcvMarker, float>> markersUnderBrush = new List<KeyValuePair<ControlableTcvMarker, float>>();
			private Dictionary<ControlableTcvMarker, Vector3> locationCache = new Dictionary<ControlableTcvMarker, Vector3>();

			internal TerrainHeightToolState( EditorControl editorControl ) : base( editorControl ) { }

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

				if ( EditorControl.pickLeft.IsActivated || EditorControl.pickMiddle.IsActivated ||  EditorControl.pickRight.IsActivated )
					OnPickActivated();
				if ( EditorControl.pickLeft.IsDeactivated || EditorControl.pickRight.IsDeactivated || EditorControl.pickMiddle.IsDeactivated )
					OnPickDeactivated();

				if ( EditorControl.pickLeft.IsActive )
				{
					OnPickActive( pickResult, affectType );
				}
				else if ( EditorControl.pickRight.IsActive )
				{
					OnPickActive( pickResult, TerrainAffectType.Down );
				}
				else if ( EditorControl.pickMiddle.IsActive)
				{
					OnPickActive( pickResult, TerrainAffectType.Smooth );
				}
				
				base.OnUpdate();
			}

			private void OnPickActivated()
			{
				StartDBOperation("Change terrain with brush");
			}

			private void OnPickDeactivated()
			{
				EditorControl.SceneControl.Scene.SceneTerrain.Owner.ReplaceAllObjectsOnTerrain();
				LeaveDBOperation();
			}
			
			private void OnPickActive( PickResult pickResult, TerrainAffectType affectType )
			{
				pickResult = EditorControl.SceneControl.Scene.Pick(EditorControl.SceneControl.CursorPosition);

				GetMarkersUnderBrush(pickResult.TerrainIntersection);

				switch(affectType)
				{
				case TerrainAffectType.Up:
						UpTcv();
						break;
				case TerrainAffectType.Down:
						DownTcv();
						break;
				case TerrainAffectType.Smooth:
						SmoothTcv();
						break;
				case TerrainAffectType.Flat:
						FlattenTcv();
						break;
				}


				List<ControlableTcvMarker> markers = new List<ControlableTcvMarker>();

				foreach (KeyValuePair<ControlableTcvMarker, float> pair in markersUnderBrush)
				{
					markers.Add(pair.Key);
				}

				RecalcTileHeights(markers);
				
			}

			#region Affect Methods

			private void SmoothTcv()
			{
				if ( markersUnderBrush.Count == 0 )
					return;

				int dim = (int)Math.Sqrt( markersUnderBrush.Count );
				for ( int i = 0; i < dim; ++i )
				{
					for ( int j = 0; j < dim; ++j )
					{
						DoBoxBlurForZ( i, j, dim );
					}
				}
			}		

			private void FlattenTcv()
			{
				float averagedZ = 0;
				foreach ( KeyValuePair<ControlableTcvMarker, float> pair in markersUnderBrush )
				{
					averagedZ += pair.Key.Location.Z;
				}
				averagedZ /= markersUnderBrush.Count;
				foreach ( KeyValuePair<ControlableTcvMarker, float> pair in markersUnderBrush )
				{
					float f = GetPressure( pair.Value );
					float smothZ = ( 1 - f ) * pair.Key.Location.Z + f * averagedZ;
					( pair.Key as IObjectTransformController ).Location = new Vector3( pair.Key.Location.X, pair.Key.Location.Y, smothZ );
				}
			}

			private void UpTcv()
			{
				foreach ( KeyValuePair<ControlableTcvMarker, float> pair in markersUnderBrush )
				{
					(pair.Key as IObjectTransformController).Location += new Vector3( 0, 0, GetPressure( pair.Value ) );
				}
			}

			private void DownTcv()
			{
				foreach ( KeyValuePair<ControlableTcvMarker, float> pair in markersUnderBrush )
				{
					(pair.Key as IObjectTransformController ).Location += new Vector3( 0, 0, -GetPressure( pair.Value ) );
				}
			}

			#endregion

			private void GetMarkersUnderBrush(Vector3 point)
			{
				markersUnderBrush.Clear();
				foreach ( ControlableTcvMarker marker in EditorControl.SceneControl.Scene.SceneTerrain.TcvMarkers )
				{
					float lendth = (new Vector3(marker.Location.X-point.X,marker.Location.Y-point.Y,0)).Length;
					float normalizedLendth = lendth/radius;
					if ( normalizedLendth > 1 )
						normalizedLendth = 1;
					if ( IsTcvInsideBox( point, radius, marker ) )
						markersUnderBrush.Add( new KeyValuePair<ControlableTcvMarker, float>( marker as ControlableTcvMarker, normalizedLendth ) );
				}
			}

			private float GetPressure(float normalizedLendth)
			{
				float result = 0;
				switch ( brushType )
				{
					case TerrainBrushType.Flat:
						result = pressure;
						break;
				case TerrainBrushType.Quadatic:
						result = (1 - normalizedLendth*normalizedLendth)*pressure;
						break;
				}

				return result;
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

			private bool IsTcvInsideBox( Vector3 point, float radius, ControlableTcvMarker tcv )
			{
				Vector3 lb = point + new Vector3( -1, -1, 0 ) * radius;
				Vector3 rt = point + new Vector3( 1, 1, 0 ) * radius;

				if ( tcv.Location.X > lb.X && tcv.Location.Y > lb.Y && tcv.Location.X < rt.X && tcv.Location.Y < rt.Y )
					return true;

				return false;
			}

			private void DoBoxBlurForZ(int i,int j, int dim)
			{
				float smoothZ = 0;
				for(int k = -1;k<2;++k)
				{
					for(int l = -1;l<2;++l)
					{
						int new_i = i + k;
						int new_j = j + l;
						// if out of sample bounds
						if(new_i<0||new_i>=dim||new_j<0||new_j>=dim)
						{
							new_i = i;
							new_j = j;
						}

						smoothZ += GetMarkerAt2DPoint(new_i, new_j, dim).Location.Z;
					}
				}
				smoothZ /= 9;

				float f = 0;
				ControlableTcvMarker tcv = GetMarkerAt2DPoint( i, j, dim, ref f );
				// Lerp with pressure
				smoothZ = ( 1 - GetPressure( f ) ) * tcv.Location.Z + GetPressure(f) * smoothZ;
				// Set
				(tcv as IObjectTransformController ).Location = new Vector3( tcv.Location.X, tcv.Location.Y, smoothZ );
			}

			private ControlableTcvMarker GetMarkerAt2DPoint( int i, int j, int dim )
			{
				return markersUnderBrush[dim * j + i].Key;
			}

			private ControlableTcvMarker GetMarkerAt2DPoint( int i, int j, int dim, ref float lendth )
			{
				lendth = markersUnderBrush[dim*j + i].Value;
				return markersUnderBrush[dim * j + i].Key;
			}
		}
	}

	public enum TerrainBrushType
	{
		Flat,
		Quadatic
	}

	public enum TerrainAffectType
	{
		Up,
		Down,
		Smooth,
		Flat
	}
}
