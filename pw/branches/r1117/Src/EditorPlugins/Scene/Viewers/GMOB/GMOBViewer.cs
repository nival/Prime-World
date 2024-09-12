using System.Collections.ObjectModel;
using System.Drawing;
using EditorLib.Extensions;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using DBTypes;
using System.Collections.Generic;
using System;
using EditorNative;
using libdb.Diagnostics;
using System.Windows.Forms;

namespace EditorPlugins.Scene.Viewers.Effect
{
  internal sealed class PassMaskItem
  {
    private readonly float x;
    private readonly float y;
    private readonly float size;
    private readonly WithoutSHSceneObject so = null;

    public void AddToScene( SimpleEditorScene _scene )
    {
			_scene.Add( so );
			Placement pl = so.GetCurrentPlacement();
			pl.location.x = x;
			pl.location.y = y;
			pl.scale.x = size;
			pl.scale.y = size;
			so.SetCurrentPlacement( pl );
    }

    public void RemoveFromScene( SimpleEditorScene _scene )
    {
      _scene.Remove( so );
    }

    public PassMaskItem( float _x, float _y, float _size )
    {
      x = _x;
      y = _y;
      size = _size;
      so = new WithoutSHSceneObject( DBID.FromString( "Tech/Default/Plane.SOBJ" ) );
    }
  };

	internal sealed class PassMaskMap
	{
		private float shiftX;
		private float shiftY;
		private float distance;
		private readonly SimpleEditorScene scene;
		private readonly Dictionary<Point, PassMaskItem> maskMap = new Dictionary<Point, PassMaskItem>();

		public ReadOnlyCollection<PassMaskItem> Items 
		{ 
			get { return new List<PassMaskItem>(maskMap.Values).AsReadOnly(); }
		}

		public PassMaskMap( SimpleEditorScene _scene )
		{
			scene = _scene;
		}

		public void SetShift(float _shiftX, float _shiftY)
		{
			shiftX = _shiftX;
			shiftY = _shiftY;
		}

		public void SetDistance(float _distance)
		{
			distance = _distance;
		}

		public void AddRange(IEnumerable<IntPoint> _items)
		{
			foreach(IntPoint item in _items)
			{
				AddItem(item);	
			}		
		}

		public PassMaskItem AddItem( IntPoint _point )
		{
			PassMaskItem result = null;

			Point key = new Point( _point.x, _point.y );

			if ( !maskMap.ContainsKey( key ) )
			{
				result = new PassMaskItem( _point.x * distance + shiftX, _point.y * distance + shiftY, distance );
				result.AddToScene( scene );
				maskMap.Add(key, result);
			}

			return result;
		}

		public void RemoveItem( IntPoint _point )
		{
			Point key = new Point( _point.x, _point.y );
			PassMaskItem item = maskMap[key];
	
			if(item != null)
			{
				item.RemoveFromScene(scene);
				maskMap.Remove(key);
			}
		}

		public void ClearItems()
		{
			foreach(PassMaskItem item in maskMap.Values)
			{
				item.RemoveFromScene(scene);
			}

			maskMap.Clear();
		}
	}

  [EditorAttribute( "GMOB", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
	[ApplicableForDeriver( Exclude = new[] { typeof( Road ), typeof( HeroPlaceHolder ), typeof( AdvMapWaterZone ), typeof( Hero ) } )]
  public sealed class GMOBViewer : SimpleViewer<GameObject>
  {
  	private const float NORMAL_OPACITY = 1.0f;
		private const float TILE_MODE_OPACITY = 0.5f;
    private bool isTileEditorOn = false;
    private bool isTileAdd = false;
	
  	private PassMaskMap passMap;
	
    protected override void OnActivateEditor()
    {
			base.OnActivateEditor();

			if(passMap == null)
				passMap = new PassMaskMap( SceneControl.Scene );
      
			//DataBase.ChangeDBResourceEvent += x => RecalcGridSize();
    }

		private void RecalcGridSize()
		{
			GameObject obj = resource.Get();

			float xSize = ( obj.collision.x2 - obj.collision.x1 );
			float ySize = ( obj.collision.y2 - obj.collision.y1 );
			float length = xSize > ySize ? xSize : ySize;

			if ( length > 0.0f && SceneControl != null )
			{
				SceneControl.areaSize = Math.Max( length, SceneControl.areaSize );
				SceneControl.lineDistance = SceneControl.areaSize / 10;
				SceneControl.subDivision = (int)( SceneControl.lineDistance / obj.lockMask.tileSize );
				SceneControl.ShowGrid = SceneControl.ShowGrid;

				passMap.SetShift( obj.collision.x1, obj.collision.y1 );
				passMap.SetDistance( obj.lockMask.tileSize );
				passMap.ClearItems();
				passMap.AddRange( obj.lockMask.mask );
			}
		}

		private void ProcessClick( SimplePickResult _pickInfo, bool _isMove )
		{
			if(!_pickInfo.hasZIntersection)
				return;

			GameObject obj = resource.Get();

			if (!_isMove && (obj.collision.x1 >= obj.collision.x2 || obj.collision.y1 >= obj.collision.y2))
			{
				Log.TraceError( "Wrong object's collision coordinates: [{0}:{1}]-[{2}:{3}]! Must be x1 < x2 and y1 < y2", 
													obj.collision.x1, obj.collision.y1, obj.collision.x2, obj.collision.y2);

				MessageBox.Show( (IWin32Window)this, "Wrong object's collision coordinates! Must be x1 < x2 and y1 < y2", "Error",
												MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1 );
				return;
			}
			 
			IntPoint tileItem = GetItemCoordinates(_pickInfo, obj);

			if(tileItem == null)
				return;

			IntPoint pt = FindPoint(obj.lockMask.mask, tileItem.x, tileItem.y);

			bool? add = null;

			if(_isMove)
			{
				//мы находимся в режиме удаления точек и нашли точку, которую надо удалить
				if(!isTileAdd && pt != null)
					add = false;

				//мы находимся в режиме добавления точек и нашли точку, которую надо добавить
				if(isTileAdd && pt == null)
					add = true;
			}
			else
			{
				add = pt == null;
				isTileAdd = add.Value;
			}

			if(add.HasValue)
			{
				if(add.Value)
				{
					obj.lockMask.mask.Add(tileItem);
					passMap.AddItem(tileItem);
				}
				else
				{
					obj.lockMask.mask.Remove(pt);
					passMap.RemoveItem(pt);
				}
			}
		}

  	private void SceneControl_OnTileClick( SimplePickResult _pickInfo )
    {
			ProcessClick( _pickInfo, false );
    }

		private void SceneControl_OnTileMove( SimplePickResult _pickInfo )
		{
			ProcessClick( _pickInfo, true );
		}

		#region Staff

		protected override string ConfigSection { get { return "GMOB"; } }

		protected override string GetTabText( DBPtr<GameObject> _resource )
		{
			return "GMOB";
		}

		protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.GameObject> _resource )
		{
			GameObject stateObject = _resource.Get();

			if ( stateObject is SingleStateObject )
				return new EditorSceneObject( ( (SingleStateObject)stateObject ).sceneObject.DBId );

			if ( stateObject is MultiStateObject )
				return new EditorSceneObject( ( (MultiStateObject)stateObject ).sceneObjects[0].DBId );

      if ( stateObject is AdvMapObstacle )
        return new EditorSceneObject( _resource .DBId );

			return null;
		}

		protected override void ToggleEditTileSet()
		{
			if ( isTileEditorOn )
			{
				TunrOffEditTileSet();
			}
			else
			{
				TunrOnEditTileSet();
			}
		}

		private void TunrOnEditTileSet()
		{
			SceneControl.OnTileClick += SceneControl_OnTileClick;
			SceneControl.OnTileMove += SceneControl_OnTileMove;
			mainSceneObject.SetOpacity( TILE_MODE_OPACITY );

			RecalcGridSize();
			PropertiesEditor.Enabled = false;
			isTileEditorOn = true;
		}

		private void TunrOffEditTileSet()
		{
			SceneControl.OnTileClick -= SceneControl_OnTileClick;
			SceneControl.OnTileMove -= SceneControl_OnTileMove;
			mainSceneObject.SetOpacity( NORMAL_OPACITY );

			passMap.ClearItems();

			isTileEditorOn = false;
			PropertiesEditor.Enabled = true;
			DataBase.ChangeCallback( DBID.Empty );
		}

		protected override void OnChangeDBResource( DBID dbid )
		{
			//обновляем ресурсы только при выключенном TileSet Mode
			if ( !isTileEditorOn )
			{
				base.OnChangeDBResource( dbid );
			}
		}

		protected override void OnClosing( System.ComponentModel.CancelEventArgs e )
		{
			TunrOffEditTileSet();
			base.OnClosing( e );
		}

		protected override void OnRefreshScene()
		{
			if(isTileEditorOn)
				mainSceneObject.SetOpacity( TILE_MODE_OPACITY );
			else
				mainSceneObject.SetOpacity( NORMAL_OPACITY );
		}

		#endregion

		#region Helpers

		private IntPoint GetItemCoordinates( SimplePickResult _pickInfo, GameObject obj )
		{
			float xNorm = ( _pickInfo.zIntersection.X - obj.collision.x1 ) / ( obj.collision.x2 - obj.collision.x1 );

			if ( xNorm < 0.0f || xNorm > 1.0f )
				return null;


			float yNorm = ( _pickInfo.zIntersection.Y - obj.collision.y1 ) / ( obj.collision.y2 - obj.collision.y1 );

			if ( yNorm < 0.0f || yNorm > 1.0f )
				return null;


			int x = (int)( xNorm * ( ( obj.collision.x2 - obj.collision.x1 ) / obj.lockMask.tileSize ) );
			int y = (int)( yNorm * ( ( obj.collision.y2 - obj.collision.y1 ) / obj.lockMask.tileSize ) );

			return new IntPoint { x = x, y = y };
		}

		private IntPoint FindPoint( IEnumerable<IntPoint> _points, int _x, int _y )
		{
			foreach ( IntPoint item in _points )
			{
				if ( item.x == _x && item.y == _y )
					return item;
			}

			return null;
		}

		#endregion

	}
}