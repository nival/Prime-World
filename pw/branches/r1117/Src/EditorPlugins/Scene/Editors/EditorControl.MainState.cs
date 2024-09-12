using System;
using System.Collections.Generic;
using EditorLib;
using EditorPlugins.Minimap;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.SceneElements;
using EditorPlugins.Scene.Editors.Terrain;
using libdb.UndoRedo;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class MainState : EditorControlState
		{
      private Vector2 prevValid = new Vector2( 0, 0 );

			internal MainState( EditorControl editorControl )
				: base( editorControl )
			{
			}

			public override void OnUpdate()
			{
				Perform( EditorControl.rotate, OnRotate90 );
	      Perform( EditorControl.levelTcvs, OnLevelTcvs );
        Perform( EditorControl.hideSelection, () => Scene.ShowSelection = !Scene.ShowSelection );
        Perform( EditorControl.switchTerrainElementsCanBeSelected, OnTerrainElementsCanBeSelectedChanged );
        if( Scene != null )Perform( EditorControl.cancel, () => Scene.DeselectAll() );
        Perform( EditorControl.storeDefaultCamera, OnStoreDefaultCamera );
        Perform( EditorControl.setDefaultCamera, OnSetDefaultCamera );
        Perform( EditorControl.pickLeft, OnPickActivated );
        Perform( EditorControl.pickRight, OnPickAlternative );
        Perform( EditorControl.mirrorSelectedTCVs, OnMirrorSelectedTCVs );

				//To Redraw Frustum
				EditorControl.application.Panels.GetSingletonPanel<MinimapPanel>().Refresh();			

			  base.OnUpdate();	
			}

      private void OnPickActivated()
      {
        // select manipulator
        if ( SceneControl.TryCaptureManipulator() )
          SetState( new ManipulationState( EditorControl ) );
        else
        {
          PickResult pickResult = SceneControl.Pick();
          if ( pickResult.PickedElements.Length == 0 || EditorControl.LockObjectMode || EditorControl.terrainController.TerrainElementsSelectable )
          {
						SetState( new SelectByFrameState( EditorControl ) );
          }
          else
          {
            EditorControl.SelectObjectAtCursor();
            OnBeginMoving();				
					}
        }
      }

			private void OnPickAlternative()
			{
				SetState( new PickAlternativeState( EditorControl ) );
			}

			private void OnBeginMoving()
			{
        //TODO
        if ( EditorControl.LockObjectMode || SceneControl.Substate is WidgetState )
          return;

				var controllers = CollectionUtils.FindAll( Scene.SelectedObjects, obj => obj is IMovingController ).ConvertAll( obj => (IMovingController)obj );

				if ( controllers.Count > 0 )
				{
          PickResult pickResult = SceneControl.Pick();
          if ( pickResult.HasTerrainIntersection )
            prevValid = new Vector2( pickResult.TerrainIntersection );
					
          SetState( new MoveObjectState( EditorControl, new CompositeMovingController( prevValid, controllers ) ) );
				}
			}

      private IObjectTransformController GetTransformController( IList<SceneElement> elements )
      {
        var controllers = new List<IObjectTransformController>();
        foreach ( var element in elements )
        {
          IObjectTransformController transformController = element as IObjectTransformController;
          if ( !ReferenceEquals( transformController, null ) && transformController.RotationYaw.MaxValue > Math.PI && transformController.RotationYaw.MinValue < -Math.PI )
          {
            controllers.Add( transformController );
          }
        }

        if ( controllers.Count > 0 )
        {
          return new CompositeTransformController( controllers.ToArray() );
        }
        else
        {
          return null;
        }
      }

			private void OnRotate90()
			{
				var transformController = GetTransformController( Scene.SelectedObjects );
				if ( !ReferenceEquals( transformController, null ) )
				{
          using( UndoRedoTransaction trans = new UndoRedoTransaction( "Rotation 90 degree" ) )
          {
            transformController.Rotation = Quaternion.FromAngleAxis( -Math.PI / 2, Vector3.AxisZ ) * transformController.Rotation;
            trans.Commit();
          }
				}
			}

			private void OnLevelTcvs()
			{
				var selectedTcvControllers =
					CollectionUtils.FindAll( Scene.SelectedObjects, element => element is ControlableTcvMarker ).
					ConvertAll<IObjectTransformController>( element => (ControlableTcvMarker)element );

				if ( selectedTcvControllers.Count > 0 )
				{
					double sumHeight = 0;
					selectedTcvControllers.ForEach( controller => sumHeight += controller.Location.Z );

          using( UndoRedoTransaction trans = new UndoRedoTransaction( "Level tcvs"  ) )
          {
            float height = (float)( sumHeight / selectedTcvControllers.Count );
            selectedTcvControllers.ForEach( c => c.Location = new Vector3( c.Location.X, c.Location.Y, height ) );
            trans.Commit();
          }
				}
			}

			private void OnTerrainElementsCanBeSelectedChanged()
			{
				var terrainController =  EditorControl.terrainController;
				if ( !ReferenceEquals( terrainController, null ) )
				{
					terrainController.TerrainElementsCanBeSelected = !terrainController.TerrainElementsCanBeSelected;
				}
			}

      public void OnSetDefaultCamera()
      {
        EditorConfigObject config = EditorControl.application.Application.Settings.Get<EditorConfigObject>();
        if ( config == null )
          return;

        Scene.SceneCamera.Pitch = config.DefaultPitch;
        Scene.SceneCamera.Rod = config.DefaultRod;
        Scene.SceneCamera.Roll = config.DefaultRoll;
        Scene.SceneCamera.Yaw = config.DefaultYaw;
				Scene.UpdateCamera( 0.0f, 0.0f, 0.0f, new Vector2( 0.0f, 0.0f ), new Vector2( 0.0f, 0.0f ) );
      }

      private void OnStoreDefaultCamera()
      {
        EditorConfigObject config = EditorControl.application.Application.Settings.Get<EditorConfigObject>();
        if ( config == null )
          return;

        config.DefaultPitch = Scene.SceneCamera.Pitch;
        config.DefaultRod = Scene.SceneCamera.Rod;
        config.DefaultRoll = Scene.SceneCamera.Roll;
        config.DefaultYaw = Scene.SceneCamera.Yaw;
      }

      private void OnMirrorSelectedTCVs()
      {
        if ( Scene.SelectedObjects.Count == 0 )
          return;

        MirrorSelectedTCVs mirrorTask = new MirrorSelectedTCVs( Scene );

        if ( mirrorTask.CheckSelectionAndCollect( Scene.SelectedObjects ) == false )
          return;

        using( UndoRedoTransaction trans = new UndoRedoTransaction( "Mirror selected TCVs"  ) )
        {
          mirrorTask.Execute();
          trans.Commit();
        }
      }
		}
	}
}
