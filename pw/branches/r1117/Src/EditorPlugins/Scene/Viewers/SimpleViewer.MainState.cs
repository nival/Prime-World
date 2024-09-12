using EditorLib.States;
using EditorNative;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers
{
  partial class SimpleViewer<TResource>
    where TResource : DBResource, new()
  {
    private sealed class MainState : State
    {
      private ManipulatorTypes manipulatorMode = ManipulatorTypes.None;

      private readonly SimpleViewer<TResource> viewer;

      internal MainState(SimpleViewer<TResource> viewer)
      {
        this.viewer = viewer;
        this.manipulatorMode = ManipulatorTypes.None;
      }

      public override void OnUpdate()
      {
        if ( viewer.showGrid.IsActivated )
        {
          viewer.sceneControl.ShowGrid = !viewer.sceneControl.ShowGrid;
        }

        if ( viewer.restart.IsActivated )
        {
            viewer.RefreshScene();
        }

        if ( viewer.toggleTranslate.IsActivated )
        {
          ToggleManupulator( ManipulatorTypes.Mover ); 
        }

        if ( viewer.toggleRotate.IsActivated )
        {
          ToggleManupulator( ManipulatorTypes.Rotator );
        }

        if ( viewer.toggleScale.IsActivated )
        {
          ToggleManupulator( ManipulatorTypes.Scaler );
        }
      }

      private void ToggleManupulator(ManipulatorTypes _manipulatorType)
      {
        if( manipulatorMode != _manipulatorType )
          SetManipulator( _manipulatorType );
        else
          ResetManipulator();
      }

      private void SetManipulator(ManipulatorTypes _manipulatorType)
      {
        if ( !viewer.manipulator.IsActive() )
        {
          viewer.manipulator.TurnOn();
        }

        viewer.manipulator.SetMode( _manipulatorType );
        manipulatorMode = _manipulatorType;
      }

      private void ResetManipulator()
      {
				viewer.timeControl.Paused = false;
        manipulatorMode = ManipulatorTypes.None;
        viewer.manipulator.TurnOff();
        viewer.RefreshScene();
      }
    }
  }
}
