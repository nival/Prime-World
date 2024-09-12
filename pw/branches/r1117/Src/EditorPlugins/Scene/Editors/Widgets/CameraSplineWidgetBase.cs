using System;
using System.Collections.Generic;
using System.Windows.Forms;
using DBTypes;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors.Splines;

namespace EditorPlugins.Scene.Editors.Widgets
{
  public abstract class CameraSplineWidgetBase<TItem> : EditorControlWidget
      where TItem : Spline3DControlPointDesc, new() 
  {
    private CameraSplineMainElement splineElement = null;
    private GameSceneObject gameSceneObject = null;

    private ToolStripButton tsbSplineAddControlPoint = null;
    private ToolStripButton tsbSplineDeleteControlPoint = null;
    private ToolStripSeparator tssSpline = null;

    private ToolStripButton tsbCameraToPoint = null;
    private ToolStripButton tsbPointToCamera = null;
    private ToolStripButton tsbPointAddFromCamera = null;

    private readonly bool hasWidth;
    private readonly bool isCircle;
    protected readonly bool isAbsolutePosition;

    protected CameraSplineWidgetBase(EditorControl _control, bool _hasWidth, bool _isCircle, bool _isAbsolutePosition)
      : base(_control)
    {
      hasWidth = _hasWidth;
      isCircle = _isCircle;
      isAbsolutePosition = _isAbsolutePosition;
    }

    public override bool IsSelected
    {
      get { return splineElement.IsSelected; }
    }

    protected abstract IList<Spline3DControlPointDesc> GetSplineDesc(GameSceneObject _target);

    public override void Create(GameSceneObject _target)
    {
      gameSceneObject = _target;

      EditorControl.ToolStrip.SuspendLayout();
      tsbSplineAddControlPoint = new ToolStripButton( EditorPluginResources.SplineCPInsert );
      tsbSplineDeleteControlPoint = new ToolStripButton( EditorPluginResources.SplineCPDelete );
      tsbSplineAddControlPoint.Name = "SplineAddControlPoint";
      tsbSplineDeleteControlPoint.Name = "SplineDeleteControlPoint";
      tsbSplineAddControlPoint.Enabled = false;
      tsbSplineDeleteControlPoint.Enabled = false;
      tsbSplineAddControlPoint.Click += OnAddControlPoint;
      tsbSplineDeleteControlPoint.Click += OnDeleteControlPoint;

      tsbCameraToPoint = new ToolStripButton( EditorPluginResources.SplineCPToCamera );
      tsbPointToCamera = new ToolStripButton( EditorPluginResources.SplineCPFromCamera );
      tsbPointAddFromCamera = new ToolStripButton( EditorPluginResources.SplineNewCPFromCamera );
      tsbCameraToPoint.Name = "SplineCameraToPoint";
      tsbPointToCamera.Name = "SplinePointToCamera";
      tsbPointAddFromCamera.Name = "SplinePointAddFromCamera";
      tsbCameraToPoint.ToolTipText = "Look from selected point";
      tsbPointToCamera.ToolTipText = "Move selected point to camera position";
      tsbPointAddFromCamera.ToolTipText = "Add new point at camera position";

      tsbCameraToPoint.Enabled = false;
      tsbPointToCamera.Enabled = false;
      tsbPointAddFromCamera.Enabled = true;
      tsbCameraToPoint.Click += OnCameraToPoint;
      tsbPointToCamera.Click += OnPointToCamera;
      tsbPointAddFromCamera.Click += OnPointAddFromCamera;

      tssSpline = new ToolStripSeparator();
      EditorControl.ToolStrip.Items.Add( tssSpline );
      EditorControl.ToolStrip.Items.Add( tsbSplineAddControlPoint );
      EditorControl.ToolStrip.Items.Add( tsbSplineDeleteControlPoint );
      EditorControl.ToolStrip.Items.Add( tsbCameraToPoint );
      EditorControl.ToolStrip.Items.Add( tsbPointToCamera );
      EditorControl.ToolStrip.Items.Add( tsbPointAddFromCamera );
      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      AdvMapCameraSpline cameraSpline = gameSceneObject.GetGameObject() as AdvMapCameraSpline;

      splineElement = new CameraSplineMainElement(EditorControl.SceneControl, GetSplineDesc(gameSceneObject),
                                                  gameSceneObject.Location, gameSceneObject.Rotation, gameSceneObject.Scale, hasWidth, isCircle, isAbsolutePosition, cameraSpline.hight );

      splineElement.AddToScene(EditorControl.SceneControl.Scene);
      splineElement.UpdateToolbarItemsEvent += UpdateSplineButtonsHandler;
    }
  
    public override void Destroy()
    {
      EditorControl.ToolStrip.SuspendLayout();
      EditorControl.ToolStrip.Items.Remove( tssSpline );
      EditorControl.ToolStrip.Items.Remove( tsbSplineAddControlPoint );
      EditorControl.ToolStrip.Items.Remove( tsbSplineDeleteControlPoint );
      EditorControl.ToolStrip.Items.Remove( tsbCameraToPoint );
      EditorControl.ToolStrip.Items.Remove( tsbPointToCamera );
      EditorControl.ToolStrip.Items.Remove( tsbPointAddFromCamera );

      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      splineElement.RemoveFromScene();
    }

    public override void Update()
    {
      splineElement.BaseLocation = gameSceneObject.Location;
      splineElement.BaseRotation = gameSceneObject.Rotation;
      splineElement.BaseScale = gameSceneObject.Scale;
      splineElement.Invalidate();
    }

    #region Event Handlers

    private void OnAddControlPoint( object sender, EventArgs e )
    {
      IList<SceneElement> selected = EditorControl.Scene.SelectedObjects;
      foreach ( SceneElement item in selected )
      {
        CameraSplineControlElement element = null;

        if (item is CameraSplineControlElement)
        {
            element = (CameraSplineControlElement)item;
        }

        if(element != null)
        {
          splineElement.InsertControlPoint(element);
          break;
        }
      }
    }

    private void OnDeleteControlPoint( object sender, EventArgs e )
    {
      IList<SceneElement> selected = EditorControl.Scene.SelectedObjects;

      for (int i = selected.Count-1; i >= 0; --i)
      {
        SceneElement item = selected[i];
        CameraSplineControlElement element = null;

        if (item is CameraSplineControlElement)
        {
            element = (CameraSplineControlElement)item;
        }

        if (element != null)
          splineElement.DeleteControlPoint(element);
      }

      gameSceneObject.IsSelected = true;
    }

    private void OnCameraToPoint( object sender, EventArgs e )
    {
      SceneElement selected = EditorControl.Scene.SelectedObjects[0];
      if ( !( selected is CameraSplineControlElement ) )
        return;
      Spline3DControlPointDesc cp = ((CameraSplineControlElement)selected).ControlPoint;

      Vector3 point = new Vector3( cp.position.x, cp.position.y, cp.position.z );
      splineElement.CorrectPosition(point);

      float rod = EditorControl.Scene.SceneCamera.Rod;

      EditorConfigObject config = EditorControl.Settings.Get<EditorConfigObject>();
      if ( config != null )
        rod = config.DefaultRod;

      EditorControl.Scene.SetCameraPosition( point, cp.rotation.z, cp.rotation.x, cp.rotation.y, rod );

    }

    private void OnPointToCamera( object sender, EventArgs e )
    {
      SceneElement selected = EditorControl.Scene.SelectedObjects[0];
      if ( !( selected is CameraSplineControlElement ) )
        return;
      CameraSplineControlElement elem = (CameraSplineControlElement)selected;

      Vector3 point = new Vector3(0,0,0);
      Vec3 rot = new Vec3();
      float x = 0, y = 0, z = 0;

      EditorControl.Scene.GetCameraPosition( point,ref z, ref x, ref y );

      rot.x = x; rot.y = y; rot.z = z;
      elem.SetPosition( point, rot );
    }

    private void OnPointAddFromCamera( object sender, EventArgs e )
    {
      Spline3DControlPointDesc cp = new Spline3DControlPointDesc();

      Vector3 point = new Vector3( 0, 0, 0 );
      float x = 0, y = 0, z = 0;

      EditorControl.Scene.GetCameraPosition( point, ref z, ref x, ref y );

      Vector3 corr = new Vector3( 0, 0, 0 );
      splineElement.CorrectPosition( corr );
      point = point - corr;

      cp.position.x = point.X;
      cp.position.y = point.Y;
      cp.position.z = point.Z;

      cp.rotation.x = x;
      cp.rotation.y = y;
      cp.rotation.z = z;

      splineElement.AddControlPoint( cp );

    }

    private void UpdateSplineButtonsHandler( bool addEnabled, bool deleteEnabled )
    {
      tsbSplineAddControlPoint.Enabled = addEnabled;
      tsbSplineDeleteControlPoint.Enabled = deleteEnabled;

      tsbCameraToPoint.Enabled = addEnabled;
      tsbPointToCamera.Enabled = addEnabled;
    }
    
    #endregion
  }

}
