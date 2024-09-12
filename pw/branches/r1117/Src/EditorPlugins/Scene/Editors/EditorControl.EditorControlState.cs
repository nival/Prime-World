using System;
using System.Collections.Generic;
using EditorLib;
using EditorLib.Binds;
using EditorLib.States;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors.Terrain;
using libdb.UndoRedo;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		public abstract class EditorControlState : State
		{
			private readonly EditorControl editorControl;
			private readonly float cameraSpeed = 30F;

      protected EditorControl EditorControl { get { return editorControl; } }
      protected SceneControl SceneControl { get { return editorControl.sceneControl; } }
      protected EditorScene Scene { get { return SceneControl.Scene; } }

			internal EditorControlState( EditorControl editorControl )
			{
				this.editorControl = editorControl;
			}

			protected void SetState( State newState )
			{
				SceneControl.Substate = newState;
			}

			protected void SetMainState()
			{
				SetState( EditorControl.mainState );
			}

      //TODO в будущем переделать стейты, надо не опрашивать состояние биндов, а подписываться на Bind.Activated, Bind.Deactivated
      /// Логика этого метода продиктована следующими соображениями
      /// Проблема: т.к. мы используем OnUpdate для опроса состояния Bind 
      /// у нас часто возникает ситуация, что при одном нажатии на клавишу пользователем
      /// происходит около сотни OnUpdate. Это приводит к тому, что одна и та же операция 
      /// повторяется оргомное количество раз.
      /// Решение: Чтобы избежать такого, мы запоминаем последний использованный Bind и отслеживаем его деактивацию. 
      /// Если операция, связанная с биндом была выполнена и при этом бинд не был деактивирован, то операция не повторяется.
      /// По сути ниженаписанный код является подпоркой. Но чтобы избежать этой подпорки надо уходить от 
      /// текущей реаллизации и переделывать все стейты, на это в данный момент нет ресурсов.
      private IBind lastBind = null;//last processed bind
      protected bool Perform( IBind bind, Operation operation )
      {
        if ( bind == lastBind && bind.IsDeactivated )
          lastBind = null;

        if ( bind == lastBind )
          return false;

        lastBind = null;

        if ( bind.IsActivated )
        {
          operation();
          lastBind = bind;
          return true;
        }
        return false;
      }

			protected bool PerformHold( IBind bind, Operation operation )
			{
				if ( bind.IsActive )
				{
					operation();
					return true;
				}

				return false;
			}

      public override void OnUpdate()
      {
				Perform( EditorControl.pickRightShift, OnPickRightShift );
        Perform( EditorControl.copy, OnCopy );
        Perform( EditorControl.cut, OnCut );
        Perform( EditorControl.paste, OnPaste );
        Perform( EditorControl.delete, OnDelete );
        Perform( EditorControl.showMoving, () => Scene.CurrentManipulator = ManipulatorTypes.Mover );
        Perform( EditorControl.showScaling, () => Scene.CurrentManipulator = ManipulatorTypes.Scaler );
        Perform( EditorControl.showRotation, () => Scene.CurrentManipulator = ManipulatorTypes.Rotator );
        Perform( EditorControl.cameraFocus, OnFocusCamera );
				Perform( EditorControl.resetAngles, OnResetRotation );
				Perform( EditorControl.resetAnglesByTerrain, OnResetRotationByTerrain );
      	Perform( EditorControl.cameraLookDown, OnCameraLookDown);
      	Perform( EditorControl.randomRotate, OnRandomRotation);
      	Perform( EditorControl.randomScale, OnRandomScale);
      	Perform( EditorControl.selectObjectsByType, OnSelectObjectsByType);
				Perform( EditorControl.selectObjectsByAsset, OnSelectObjectsByAsset );
				PerformHold( EditorControl.cameraMoveForward, OnCameraMoveForward );
				PerformHold( EditorControl.cameraMoveBackward, OnCameraMoveBackward );
				PerformHold( EditorControl.cameraMoveRight, OnCameraMoveRight );
				PerformHold( EditorControl.cameraMoveLeft, OnCameraMoveLeft );
        Perform( EditorControl.showHideTiles, () => EditorControl.IsShowTileSet = !EditorControl.IsShowTileSet );
        Perform( EditorControl.showSymmetricLine, () => EditorControl.NextSymmetricLineMode() );
        Perform( EditorControl.setScriptGroupName, () => EditorControl.SetScriptGroupName() );

        Perform( EditorControl.resetManipulatorSize, OnResetManipulatorSize );
        Perform( EditorControl.increaseManipulator, OnIncreaseManipulatorSize );
        Perform( EditorControl.decreaseManipulator, OnDecreaseManipulatorSize );
        Perform( EditorControl.increaseManipulatorNumpad, OnIncreaseManipulatorSize );
        Perform( EditorControl.decreaseManipulatorNumpad, OnDecreaseManipulatorSize );
        Perform( EditorControl.globalLocalManipulatorsMode, () => EditorControl.IsGlobal = !EditorControl.IsGlobal );


				if ( editorControl.IsShowTileSet )
					editorControl.TileMap.Draw();

        editorControl.DrawSymmetricLine( editorControl.ShowSymmetricLineMode );

      }

		  protected virtual void OnCopy()
      {
        EditorControl.extension.TryCopy();
      }

      protected virtual void OnCut()
      {
        using( UndoRedoTransaction trans = new UndoRedoTransaction( "Cut" ) )
        {
          OnCopy();
          OnDelete();
          trans.Commit();
        }
      }

      protected virtual void OnPaste()
      {
        EditorControl.extension.TryPaste();
      }

      protected virtual void OnDelete()
      {
        using( UndoRedoTransaction trans = new UndoRedoTransaction( "Deleting" ) )
        {
					EditorControl.TileMap.RemoveObjects( Scene.SelectedObjects );

          foreach( var selectedObject in new List<SceneElement>( Scene.SelectedObjects ) )
          {
            if( selectedObject is ControlableTerrainElement )
            {
              EditorControl.terrainController.Remove( ( (ControlableTerrainElement)selectedObject ).Resource );
            }
            else
            {
              EditorControl.extension.TryRemove( selectedObject );
            }
          }
          trans.Commit();
        }
      }

      private void OnFocusCamera()
      {
        Bound bound = Scene.GetSelectedObjectsGroupBoundingBox();

        if( bound != null )
        {      
          Scene.SceneCamera.Anchor = new Vector3(
                                      bound.Center.X / 2.0f,
                                      bound.Center.Y / 2.0f,
                                      bound.Center.Z / 2.0f );

          Scene.SceneCamera.Rod = bound.HalfSize.Abs * 10.0f;
        }
        else
        {
          var pickResult = SceneControl.Pick();
          Scene.SceneCamera.Anchor = pickResult.HasTerrainIntersection ? pickResult.TerrainIntersection : Vector3.Zero;
        }
      }

			private void OnResetRotation()
			{
				editorControl.ResetRotation( this, null );
			}

			private void OnResetRotationByTerrain()
			{
				editorControl.ResetRotationByTerrain( this, null );
			}

			private void OnRandomRotation()
			{
				editorControl.RandomRotation(this, null);
			}

			private void OnRandomScale()
			{
				editorControl.RandomScale(this, null);
			}

			private void OnSelectObjectsByType()
			{
				if ( !Scene.HasSelectedObject )
					return;

				var selectedObject = Scene.SelectedObjects[0] as GameSceneObject;
				var gobj = ( selectedObject == null ) ? null : selectedObject.GetGameObject();
				if ( gobj == null )
					return;
				
				Type typeOfSelected = gobj.GetType();

				IList<SceneElement> sceneElements = Scene.GetSceneElements();
				
				foreach(SceneElement element in sceneElements)
				{
					var el = element as GameSceneObject;
					var elGObj = (el == null) ? null : el.GetGameObject();
					if ( elGObj == null )
						continue;

					if ( typeOfSelected == elGObj.GetType() )
					{
						Scene.Select(element);
					}
				}
			}

			private void OnSelectObjectsByAsset()
			{
				if ( !Scene.HasSelectedObject )
					return;

				var selectedObject = Scene.SelectedObjects[0] as GameSceneObject;
				var gobj = ( selectedObject == null ) ? null : selectedObject.GetGameObject();
				if ( gobj == null )
					return;

				string asset = gobj.DBId.FileName;

				IList<SceneElement> sceneElements = Scene.GetSceneElements();

				foreach ( SceneElement element in sceneElements )
				{
					var el = element as GameSceneObject;
					var elGObj = ( el == null ) ? null : el.GetGameObject();
					if ( elGObj == null )
						continue;

					if ( asset == elGObj.DBId.FileName )
					{
						Scene.Select( element );
					}
				}
			}

			private void OnCameraLookDown()
			{
				if ( Scene.SceneCamera == null )
					return;
				Scene.SceneCamera.Pitch = -(float)Math.PI/2;
			}

			private void OnCameraMoveForward()
			{
				Scene.SceneCamera.Anchor += new Vector3( Scene.SceneCamera.Direction.X, Scene.SceneCamera.Direction.Y, 0 ) * GetCameraSpeed();
			}
			
			private void OnCameraMoveBackward()
			{
				Scene.SceneCamera.Anchor -= new Vector3( Scene.SceneCamera.Direction.X, Scene.SceneCamera.Direction.Y, 0 ) * GetCameraSpeed();
			}
			
			private void OnCameraMoveRight()
			{
				Scene.SceneCamera.Anchor += new Vector3( Scene.SceneCamera.RightDirection.X, Scene.SceneCamera.RightDirection.Y, 0 ) * GetCameraSpeed();
			}
			
			private void OnCameraMoveLeft()
			{
				Scene.SceneCamera.Anchor -= new Vector3( Scene.SceneCamera.RightDirection.X, Scene.SceneCamera.RightDirection.Y, 0 ) * GetCameraSpeed();
			}
			
			private float GetCameraSpeed()
			{
				return cameraSpeed*SceneControl.timer.Interval/1000;
			}
			
			private void OnPickRightShift()
			{
					SetState(new PickAlternativeState(editorControl));
			}

      private void OnResetManipulatorSize()
      {
        if ( EditorControl.Scene.CurrentManipulator != ManipulatorTypes.None )
          EditorControl.Scene.ResetManipulatorSize();
      }

      private void OnIncreaseManipulatorSize()
      {
        if ( EditorControl.Scene.CurrentManipulator != ManipulatorTypes.None )
          EditorControl.Scene.IncreaseManipulatorSize();
      }

      private void OnDecreaseManipulatorSize()
      {
        if ( EditorControl.Scene.CurrentManipulator != ManipulatorTypes.None )
          EditorControl.Scene.DecreaseManipulatorSize();
      }

			internal void RecalcTileHeights( IEnumerable<ControlableTcvMarker> _markers )
			{
				float minX = float.MaxValue;
				float maxX = float.MinValue;
				float minY = float.MaxValue;
				float maxY = float.MinValue;

				foreach ( ControlableTcvMarker marker in _markers )
				{
					minX = Math.Min( minX, marker.Location.X );
					maxX = Math.Max( maxX, marker.Location.X );

					minY = Math.Min( minY, marker.Location.Y );
					maxY = Math.Max( maxY, marker.Location.Y );
				}

				float distance = 5.0f;

				EditorControl.TileMap.RecalcHeights( minX - distance, minY - distance, maxX + distance, maxY + distance );
			}
    }
	}
}
