using System;
using System.Collections.Generic;
using System.Windows.Forms;
using DBTypes;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors.Splines;

namespace EditorPlugins.Scene.Editors.Widgets
{
  public abstract class SplineWidgetBase<TItem> : EditorControlWidget
    where TItem : FlatSplineControlPointDesc, new() 
  {
    private SplineMainElement<TItem> splineElement = null;
    private GameSceneObject gameSceneObject = null;

    private ToolStripButton tsbSplineAddControlPoint = null;
    private ToolStripButton tsbSplineDeleteControlPoint = null;
    private ToolStripSeparator tssSpline = null;

    private readonly bool hasWidth;
    private readonly bool isCircle;
    protected readonly bool isAbsolutePosition;

    protected SplineWidgetBase(EditorControl _control, bool _hasWidth, bool _isCircle, bool _isAbsolutePosition)
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

    protected abstract IList<TItem> GetSplineDesc(GameSceneObject _target);

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

      tssSpline = new ToolStripSeparator();
      EditorControl.ToolStrip.Items.Add( tssSpline );
      EditorControl.ToolStrip.Items.Add( tsbSplineAddControlPoint );
      EditorControl.ToolStrip.Items.Add( tsbSplineDeleteControlPoint );
      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      splineElement = new SplineMainElement<TItem>(EditorControl.SceneControl, GetSplineDesc(gameSceneObject),
                                            gameSceneObject.Location, gameSceneObject.Rotation, gameSceneObject.Scale,
                                            hasWidth, isCircle, isAbsolutePosition );

      splineElement.AddToScene(EditorControl.SceneControl.Scene);
      splineElement.UpdateToolbarItemsEvent += UpdateSplineButtonsHandler;
    }
  
    public override void Destroy()
    {
      EditorControl.ToolStrip.SuspendLayout();
      EditorControl.ToolStrip.Items.Remove( tssSpline );
      EditorControl.ToolStrip.Items.Remove( tsbSplineAddControlPoint );
      EditorControl.ToolStrip.Items.Remove( tsbSplineDeleteControlPoint );
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
        SplineControlElement element = null;
        
        if(item is SplineControlElement)
        {
          element = (SplineControlElement)item;
        }
        else if (item is SplineWidthElement)
        {
          element = ((SplineWidthElement)item).ControlElement;
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
        SplineControlElement element = null;

        if( item is SplineControlElement )
        {
          element = (SplineControlElement)item;
        }
        else if( item is SplineWidthElement )
        {
          element = ( (SplineWidthElement)item ).ControlElement;
        }

        if (element != null)
          splineElement.DeleteControlPoint(element);
      }

      gameSceneObject.IsSelected = true;
    }

    private void UpdateSplineButtonsHandler( bool addEnabled, bool deleteEnabled )
    {
      tsbSplineAddControlPoint.Enabled = addEnabled;
      tsbSplineDeleteControlPoint.Enabled = deleteEnabled;
    }
    
    #endregion
  }

  //[EditorControlWidget( typeof( DBTypes.AdvMapCreep ) )]
  public class SplineWidgetTest : SplineWidgetBase<FlatSplineControlPointDesc>
  {
    public SplineWidgetTest( EditorControl _control ) : base(_control, true, true, false) { }

    public override bool HasThisWidget( GameSceneObject target ) { return true; }

    protected override IList<FlatSplineControlPointDesc> GetSplineDesc(GameSceneObject target)
    {
      IList<FlatSplineControlPointDesc> splineDesc = new List<FlatSplineControlPointDesc>();

      Vec2 location = new Vec2();
      FlatSplineControlPointDesc cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = -10;
      cpDesc.location.y = 0;
      cpDesc.width = 1;
      splineDesc.Add(cpDesc);
      cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = 0;
      cpDesc.location.y = 20;
      cpDesc.width = 4;
      splineDesc.Add(cpDesc);
      cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = 20;
      cpDesc.location.y = 0;
      cpDesc.width = 2;
      splineDesc.Add(cpDesc);

      return splineDesc;
    }

  }

  [EditorControlWidget( typeof( DBTypes.AdvMapCreep ) )]
  public class SplineWidgetTest2 : SplineWidgetBase<FlatSplineControlPointDesc>
  {
    public SplineWidgetTest2( EditorControl _control ) : base(_control, true, false, true) { }

    public override bool HasThisWidget( GameSceneObject target ) { return true; }

    protected override IList<FlatSplineControlPointDesc> GetSplineDesc(GameSceneObject target)
    {
      List<FlatSplineControlPointDesc> splineDesc = new List<FlatSplineControlPointDesc>();

      Vec2 location = new Vec2();
      FlatSplineControlPointDesc cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = target.Location.X - 5;
      cpDesc.location.y = target.Location.Y;
      cpDesc.width = 4;
      splineDesc.Add(cpDesc);
      cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = target.Location.X;
      cpDesc.location.y = target.Location.Y + 5;
      cpDesc.width = 2;
      splineDesc.Add(cpDesc);
      cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = target.Location.X + 10;
      cpDesc.location.y = target.Location.Y;
      cpDesc.width = 6;
      splineDesc.Add(cpDesc);
      cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = target.Location.X;
      cpDesc.location.y = target.Location.Y - 10;
      cpDesc.width = 6;
      splineDesc.Add(cpDesc);
      cpDesc = new FlatSplineControlPointDesc();
      cpDesc.location.x = target.Location.X - 10;
      cpDesc.location.y = target.Location.Y;
      cpDesc.width = 4;
      splineDesc.Add(cpDesc);

      return splineDesc;
    }

  }

}
