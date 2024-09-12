using System.Collections.Generic;
using EditorNative.SceneElements.SceneObjects;
using DBTypes;

namespace EditorPlugins.Scene.Editors.Widgets
{
  [EditorControlWidget(typeof(Road))]
  public class RoadWidget : SplineWidgetBase<RoadControlPoint>
  {
    public RoadWidget(EditorControl _control) : base (_control, true, false, true){}
    
    public override bool HasThisWidget(GameSceneObject target) { return true; }

    protected override IList<RoadControlPoint> GetSplineDesc(GameSceneObject target)
    {
      var road = target.GetGameObject() as Road;

      return road.points;
    }
    
  }
}