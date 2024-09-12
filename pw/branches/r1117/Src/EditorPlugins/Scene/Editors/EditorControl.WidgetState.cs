using System;
using System.Collections.Generic;
using EditorLib;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors.Splines;
using EditorPlugins.Scene.Editors.Widgets;
using EditorPlugins.Scene.Editors.Polygons;

namespace EditorPlugins.Scene.Editors
{

  partial class EditorControl
  {
    private sealed class WidgetState : EditorControlState
    {
    	public static WidgetState CallBackWidjet{ get; private set; }

      private readonly GameSceneObject gameSceneObject;
      private readonly List<EditorControlWidget> widgets = null;
      private CompositeMovingController controller;
      private float lastValidX = 0.0f;
      private float lastValidY = 0.0f;
    	private bool isCurrentCallback;
			private bool isDoubleActivated;
			private DateTime lastActivatedTime;

      internal WidgetState( EditorControl editorControl, GameSceneObject obj, List<EditorControlWidget> _widgets )
        : base( editorControl )
      {
        gameSceneObject = obj;
        widgets = _widgets;
      }

    	private bool isTilesUpdateMode = false;

      public override void OnUpdate()
      {
				if ( !gameSceneObject.IsSelected && IsNeedLeave() && !isCurrentCallback )
        {
          SetMainState();
          EditorControl.SelectObjectAtCursor();
        }
        else
        {

					if ( EditorControl.pickLeft.IsActivated )
					{
						OnPickActivated();
					}
					else if(EditorControl.pickLeft.IsDeactivated)
					{
						if ( isTilesUpdateMode && gameSceneObject.IsSelected )
						{
							EditorControl.TileMap.PlaceObjects(Scene.SelectedObjects);
							isTilesUpdateMode = false;
						}

						OnPickDeactivated();
					}

          if ( EditorControl.pickLeft.IsActivated )
          {
            Scene.StartDragManipulator( EditorControl.IsCommonCenter );
          }

          if( EditorControl.pickLeft.IsActive )
          {
						if ( !isTilesUpdateMode && gameSceneObject.IsSelected )
						{
							EditorControl.TileMap.RemoveObjects(Scene.SelectedObjects);

							isTilesUpdateMode = true;
						}

            OnPickActive();
            Scene.DragManipulator( SceneControl.CursorDelta, SceneControl.CursorPosition );
          }
          else if( EditorControl.pickLeft.IsDeactivated )
          {
            Scene.EndDragManipulator();
            LeaveDBOperation();
          }
          
          foreach( EditorControlWidget widget in widgets )
          {
            widget.Update(); 
          }
        }

        base.OnUpdate();
      }

      private void OnPickActivated()
      {
				UpdateDoubleClick();

        StartDBOperation( "Widget Manipulation" );
        if( !SceneControl.TryCaptureManipulator() )
        {
          PickResult pickResult = SceneControl.Pick();

					if ( pickResult.PickedElements.Length > 0 && ContainsSplineElement( pickResult.PickedElements ) )
          {
            var firstPicked = pickResult.PickedElements[0];

            //нужно чтобы SplineControlElement и SplineWidthElement пикались вначале
            foreach( SceneElement element in pickResult.PickedElements )
            {
              if( IsSplineControlElement(element) )
              {
                firstPicked = element;
                break;
              }
            }

            if( EditorControl.SplineSelectionMode )
            {
              if( !( firstPicked is SplineControlElement )
                && !(firstPicked is CameraSplineControlElement)
                && !( firstPicked is SplineWidthElement )
                && !( EditorControl.IsSpline( firstPicked as GameSceneObject ) )
                )
              {
                firstPicked = gameSceneObject;
              }
            }

						// Cleanup Control
						if ( firstPicked is SplineWidthElement )
						{
							for ( int i = Scene.SelectedObjects.Count - 1; i > -1; --i )
							{
								if ( Scene.SelectedObjects[i] is SplineControlElement )
									Scene.Deselect( Scene.SelectedObjects[i] );
							}
							if ( isDoubleActivated )
							{
								IList<SceneElement> elements = Scene.GetSceneElementsByType( typeof( SplineWidthElement ) );
								foreach ( SceneElement element in elements )
								{
									Scene.Select( element );
								}
							}
						}
						// Cleanup Width
						if(firstPicked is SplineControlElement)
						{
							for(int i =Scene.SelectedObjects.Count-1;i>-1;--i)
							{
								if ( Scene.SelectedObjects[i] is SplineWidthElement )
									Scene.Deselect(Scene.SelectedObjects[i]);
							}
							if ( isDoubleActivated )
							{
								IList<SceneElement> elements =  Scene.GetSceneElementsByType( typeof(SplineControlElement) );
								foreach ( SceneElement element in elements )
								{
									Scene.Select(element);
								}
							}
						}

						if ( EditorControl.add.IsActive)
						{
              if ( firstPicked.IsSelected )
                Scene.Deselect( firstPicked );
              else
							  Scene.Select( firstPicked );
							Scene.CurrentManipulator = ManipulatorTypes.None;
						}
            else if( !firstPicked.IsSelected )
            {
              Scene.DeselectAll();
              Scene.Select( firstPicked );
              Scene.CurrentManipulator = ManipulatorTypes.None;
            }

          }
          else
          {
						if ( EditorControl.SplineSelectionMode )
						{
							isCurrentCallback = true;
							CallBackWidjet = this;
							SetState(new SelectByFrameState(EditorControl));
						}
                        else
                            Scene.DeselectAll();
          }
        }
        controller = null;
      }

			private void OnPickDeactivated()
			{
			}

      private void OnPickActive()
      {
        if( controller != null )
        {
          controller.Move( false );
          Scene.CurrentManipulator = Scene.CurrentManipulator;
        }
        else if( Scene.CurrentManipulator == ManipulatorTypes.None )
        {
          var controllers = CollectionUtils.FindAll( Scene.SelectedObjects, obj => obj is IMovingController ).ConvertAll( obj => (IMovingController)obj );

          if( controllers.Count > 0 )
          {
						PickResult pickResult = SceneControl.Pick();

						if ( controllers[0] is SplineWidthElement && controllers.Count == 1 )
						{
							SplineWidthElement.mainElement = controllers[0] as SplineWidthElement;
						}
						else if (pickResult.PickedElements.Length >0 && pickResult.PickedElements[0] != null && pickResult.PickedElements[0] is SplineWidthElement )
						{
							SplineWidthElement.mainElement = pickResult.PickedElements[0] as SplineWidthElement;
						}

            if( pickResult.HasTerrainIntersection )
            {
              lastValidX = pickResult.TerrainIntersection.X;
              lastValidY = pickResult.TerrainIntersection.Y;
							controller = new CompositeMovingController( new Vector2( pickResult.TerrainIntersection.X, pickResult.TerrainIntersection.Y ),controllers);
            }
            else
            {
							controller = new CompositeMovingController( new Vector2( lastValidX, lastValidY ), controllers);
            }
          }
        }
      }

      protected override void OnDelete()
      {
        if(gameSceneObject.IsSelected)
        {
          LeaveDBOperation();
          base.OnDelete();
        }
      }

      protected override void OnActivated()
      {
      	base.OnActivated();

      	if (!isCurrentCallback)
      	{
      		foreach (EditorControlWidget widget in widgets)
      		{
      			widget.Create(gameSceneObject);
      		}
      	}

				if ( EditorControl.SplineSelectionMode )
				{
					for ( int i = Scene.SelectedObjects.Count - 1; i > -1; --i )
					{
                        if (Scene.SelectedObjects[i].GetType() != typeof(SplineControlElement) && Scene.SelectedObjects[i].GetType() != typeof(CameraSplineControlElement) && Scene.SelectedObjects[i] != gameSceneObject)
							Scene.Deselect( Scene.SelectedObjects[i] );
					}
				}

    	  isCurrentCallback = false;
      	CallBackWidjet = null;
      }

      protected override void OnDeactivated()
      {
        base.OnDeactivated();

        LeaveDBOperation();
				if ( !isCurrentCallback )
				{
					foreach (EditorControlWidget widget in widgets)
					{
						widget.Destroy();
					}
				}

      }

      private bool IsNeedLeave()
      {
				foreach ( EditorControlWidget widget in widgets )
				{
					if ( widget.IsSelected )
						return false;
				}
				return true;
      }

			private void UpdateDoubleClick()
			{
				isDoubleActivated = false;
				if ( ( DateTime.Now - lastActivatedTime ).TotalMilliseconds < 400 )
					isDoubleActivated = true;
				lastActivatedTime = DateTime.Now;
			}

			private bool IsSplineControlElement(SceneElement element)
			{
        return (element is SplineWidthElement || element is SplineControlElement || element is TargetPathPoint || element is CameraSplineControlElement || element is PointElement);
			}
			
			private bool ContainsSplineElement(SceneElement[] elements)
			{
				foreach(SceneElement e in elements)
				{
					if ( IsSplineControlElement( e ) )
						return true;
				}
				return false;
			}
    }
  }
}
