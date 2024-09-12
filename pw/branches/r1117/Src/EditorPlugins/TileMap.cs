using System;
using System.Collections.Generic;
using System.Drawing;
using DBTypes;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorNative.Terrain;
using Color = System.Drawing.Color;

namespace EditorPlugins
{
	public sealed class TileMap
	{
		private const float SIZE_OF_PATH = 10.0f;
		private const float BLOCK_HEIGHT_SCALE = 1.0f; //in tile size units

		private readonly float mapTileSize; //tile size for current map
		private readonly int mapWidth;
		private readonly int mapHeight;
		private readonly short[,] tileSet; //x,y
		private readonly float[,] heights; //z

		private readonly EditorScene scene;
    private readonly DBTypes.AdventureCameraSettings cameraSettings;

		public TileMap( EditorScene _scene, DBTypes.AdventureCameraSettings _cameraSettings )
		{
			scene = _scene;
      cameraSettings = _cameraSettings;

			//init tileSet
			mapTileSize = SIZE_OF_PATH / scene.SceneTerrain.TilesPerElement;

			mapWidth = scene.SceneTerrain.SizeX * scene.SceneTerrain.TilesPerElement;
			mapHeight = scene.SceneTerrain.SizeY * scene.SceneTerrain.TilesPerElement;
      tileSet = new short[mapWidth, mapHeight];
			heights = new float[mapWidth, mapHeight];

			//DateTime dt = DateTime.Now;//DEBUG

			RecalcHeightsInternal( 0, 0, mapWidth, mapHeight );	
			PlaceObjects( scene.GetSceneElements() );
      if ( cameraSettings != null)
        LockByCameraSettings();

			//System.Diagnostics.Debug.Print( "RenderTileSet: {0} ms", ( DateTime.Now - dt ).TotalMilliseconds );//DEBUG		
		}

		public void Draw()
		{
			DateTime dt = DateTime.Now;

			int excluded = 0;
			int included = 0;

			ForAllPoints( mapWidth, mapHeight, pt =>
			{
				if(tileSet[pt.X, pt.Y] <= 0) 
					return;

				PointF mapPoint = ToMapPoint( pt.X, pt.Y );
			
				float height = heights[pt.X, pt.Y];

				if ( !scene.IsInCameraFrustum( mapPoint.X, mapPoint.Y, height ) )
				{
					excluded++;
					return;
				}

				included++;

				EditorRender.DrawPoint3D( mapPoint.X, mapPoint.Y, height, mapTileSize * 0.25f, Color.Red );

			} );
			
			System.Diagnostics.Debug.Print( "Draw: {0} ms", ( DateTime.Now - dt ).TotalMilliseconds );
			System.Diagnostics.Debug.Print( "Included: {0} Excluded: {1}", included, excluded);
		}

		public void PlaceObjects(IEnumerable<SceneElement> _elements)
		{
			foreach ( SceneElement element in _elements )
			{
				if ( element is GameSceneObject )
					PlaceObject((GameSceneObject)element);
			}
		}

		public void RemoveObjects( IEnumerable<SceneElement> _elements )
		{
			foreach ( SceneElement element in _elements )
			{
				if(element is GameSceneObject)
					RemoveObject((GameSceneObject)element);
			}
		}

    private bool CheckObstacleLock(GameSceneObject gameSceneObject)
    {
      libdb.DB.DBPtr<GameObject> gameObject = libdb.DB.DataBase.Get<GameObject>(gameSceneObject.GetGameObject().DBId);

      var resource = gameObject.Get();

      if ( resource is AdvMapObstacle )
        return ((resource as AdvMapObstacle).LockMode == DBTypes.BooleanLockMode.Lock);

      return true;
    }

		public void PlaceObject( GameSceneObject _gameSceneObject )
		{
      UpdateObjectTiles(_gameSceneObject, CheckObstacleLock(_gameSceneObject) );
			//System.Diagnostics.Debug.Print( "PlaceObject '{0}'", _gameSceneObject.DbId );
		}

		public void RemoveObject( GameSceneObject _gameSceneObject )
		{
      UpdateObjectTiles(_gameSceneObject, !CheckObstacleLock(_gameSceneObject));
			//System.Diagnostics.Debug.Print( "RemoveObject '{0}'", _gameSceneObject.DbId );
		}

		public void RecalcHeights( float _minX, float _minY, float _maxX, float _maxY )
		{
			//пересчитываем проходимость высот
			Point minPoint = ToTilesPoint( _minX, _minY );
			Point maxPoint = ToTilesPoint( _maxX, _maxY );

			DateTime dt1 = DateTime.Now;
			RecalcHeightsInternal( minPoint.X, minPoint.Y, maxPoint.X - minPoint.X, maxPoint.Y - minPoint.Y );
			System.Diagnostics.Debug.Print( "RecalcHeightsInternal {0} ms", ( DateTime.Now - dt1 ).TotalMilliseconds );

		}

		private void RecalcHeightsInternal( int _startX, int _startY, int _width, int _height )
		{
			if ( _startX < 0 || _startX >= mapWidth )
				_startX = 0;

			if ( _startY < 0 || _startY >= mapHeight )
				_startY = 0;

			if ( _startX + _width > mapWidth )
				_width = mapWidth - _startX;

			if ( _startY + _height > mapHeight )
				_height = mapHeight - _startY;

			for ( int x = _startX; x < _startX + _width; x++ )
			{
				for ( int y = _startY; y < _startY + _height; y++ )
				{
					// check adjacent cells
					float h0 = 0.0f;
					PointF mapPoint0 = ToMapPoint( x, y );
					scene.TryGetHeight( mapPoint0.X, mapPoint0.Y, ref h0 );///*/heights[y][x];

					float maxDelta = 0;
					for ( int dx = -1; dx <= 1; dx++ )
					{
						int x1 = x + dx;
						if ( x1 < 0 || x1 >= _startX + _width )
							continue;										// outside of the world
						for ( int dy = -1; dy <= 1; dy++ )
						{
							if ( dx == 0 && dy == 0 )
								continue;									// skip center point
							int y1 = y + dy;
							if ( y1 < 0 || y1 >= _startY + _height )
								continue;									// outside of the world

							float h1 = 0.0f;
							PointF mapPoint1 = ToMapPoint( x1, y1 );
							scene.TryGetHeight( mapPoint1.X, mapPoint1.Y, ref h1 );

							float dh = Math.Abs( h0 - h1 );
							if ( dh > maxDelta )
								maxDelta = dh;
						}
					}

					// analyze height difference
					if(maxDelta > mapTileSize*BLOCK_HEIGHT_SCALE)
					{
						tileSet[x, y] += 1;
					}
					else if ( tileSet[x, y] != 0)
					{
						tileSet[x, y] -= 1;
					}

					//update heights
					float z = 0;
					PointF point = ToMapPoint( x, y );
					scene.TryGetHeight( point.X, point.Y, ref z );
					heights[x, y] = z;
				}
			}
		}

    private void LockByCameraSettings()
    {
      Point sz = ToTilesPoint( cameraSettings.limitRadiusHor, cameraSettings.limitRadiusVert ); 

      // Apply lock multipliers, if they are not zero
      if (cameraSettings.lockMultRadiusHor > 0)
        sz.X = (int) (sz.X * cameraSettings.lockMultRadiusHor);
      if (cameraSettings.lockMultRadiusVert > 0)
        sz.Y = (int) (sz.Y * cameraSettings.lockMultRadiusVert);

      // Apply locking circle center offsets: first - camera offset, 
      // second - lock offset relative to the camera offset.
      Point center = new Point(mapWidth/2, mapHeight/2);
      center.X += (int)(cameraSettings.centerOffset.x + cameraSettings.lockCenterOffset.x);
      center.Y += (int)(cameraSettings.centerOffset.y + cameraSettings.lockCenterOffset.y);

      
      for (int i=0; i<mapWidth; i++)
      {
        for (int j=0; j<mapHeight;j++)
        {
          float x = i - center.X;
          float y = j - center.Y;
          bool outside = (x*x/(sz.X*sz.X) + y*y/(sz.Y*sz.Y))>1;  

          if ( outside )
            tileSet[i,j] += 1;
        }
      }
    }

   

		#region Helpers

		private void UpdateObjectTiles( GameSceneObject _gameSceneObject, bool _objectPlaced )
		{
			GameObject go = _gameSceneObject.GetGameObject();

			List<Point> list = TileMapHelper.FillOccupiedTiles( mapWidth, mapHeight, mapTileSize, 
																													  go.collision, go.lockMask.tileSize, go.lockMask.mask, 
																														_gameSceneObject.GetCurrentPlacement() );

			foreach ( Point pt in list )
			{
				if ( _objectPlaced )//place object
				{
					tileSet[pt.X, pt.Y] += 1;
				}
				else if (go is AdvMapObstacle || tileSet[pt.X, pt.Y] != 0)
				{
            tileSet[pt.X, pt.Y] -= 1;
				}
			}
		}

		private PointF ToMapPoint( int x, int y )
		{
			return new PointF( x * mapTileSize, y * mapTileSize );
		}

		private Point ToTilesPoint( float x, float y )
		{
			return new Point( (int)Math.Ceiling( x / mapTileSize ), (int)Math.Ceiling( y / mapTileSize ) );
		}

		private static void ForAllPoints( int _sizeX, int _sizeY, Action<Point> _action )
		{
			for ( int x = 0; x < _sizeX; ++x )
			{
				for ( int y = 0; y < _sizeY; ++y )
				{
					_action( new Point( x, y ) );
				}
			}
		}

		#endregion
	}
}