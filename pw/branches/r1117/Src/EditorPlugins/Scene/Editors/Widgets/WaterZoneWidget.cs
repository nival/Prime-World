using System.Collections.Generic;
using DBTypes;
using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Scene.Editors.Widgets
{
  [EditorControlWidget( typeof( AdvMapWaterZone ) )]
  public class WaterZoneWidget : SplineWidgetBase<FlatSplineControlPointDesc>
  {
    public WaterZoneWidget( EditorControl _control ) : base(_control, false, true, false) { }

    public override bool HasThisWidget( GameSceneObject target ) { return true; }

    protected override IList<FlatSplineControlPointDesc> GetSplineDesc(GameSceneObject target)
    {
      AdvMapWaterZone obj = target.GetGameObject() as AdvMapWaterZone;


      IList<FlatSplineControlPointDesc> splineDesc = obj.area.points;

      if (splineDesc.Count < 3)
      {
        splineDesc.Clear();
        Vec2 location = new Vec2();
        Vec2 offset = new Vec2();
        offset.x = isAbsolutePosition ? target.Location.X : 0;
        offset.y = isAbsolutePosition ? target.Location.Y : 0;
        FlatSplineControlPointDesc cpDesc = new FlatSplineControlPointDesc();
        cpDesc.location.x = -20 + offset.x;
        cpDesc.location.y = 0 + offset.y;
        splineDesc.Add(cpDesc);
        cpDesc = new FlatSplineControlPointDesc();
        cpDesc.location.x = 10 + offset.x;
        cpDesc.location.y = 10 + offset.y;
        splineDesc.Add(cpDesc);
        cpDesc = new FlatSplineControlPointDesc();
        cpDesc.location.x = 10 + offset.x;
        cpDesc.location.y = -10 + offset.y;
        splineDesc.Add(cpDesc);
      }

      return splineDesc;
    }
  }
}
