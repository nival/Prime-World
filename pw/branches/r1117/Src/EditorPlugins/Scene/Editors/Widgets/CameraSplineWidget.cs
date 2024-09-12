using System.Collections.Generic;
using DBTypes;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors.Splines;

namespace EditorPlugins.Scene.Editors.Widgets
{
  [EditorControlWidget( typeof( AdvMapCameraSpline ) )]
    public class CameraSplineWidget : CameraSplineWidgetBase<Spline3DControlPointDesc>
  {
      public CameraSplineWidget(EditorControl _control) : base(_control, false, false, false) { }

    public override bool HasThisWidget( GameSceneObject target ) { return true; }

    protected override IList<Spline3DControlPointDesc> GetSplineDesc(GameSceneObject target)
    {
        AdvMapCameraSpline obj = target.GetGameObject() as AdvMapCameraSpline;

        IList<Spline3DControlPointDesc> splineDesc = obj.points;

      if (splineDesc.Count < 3)
      {
        splineDesc.Clear();
        Vec2 location = new Vec2();
        Vec2 offset = new Vec2();
        offset.x = isAbsolutePosition ? target.Location.X : 0;
        offset.y = isAbsolutePosition ? target.Location.Y : 0;
        Spline3DControlPointDesc cpDesc = new Spline3DControlPointDesc();
        cpDesc.position.x = -20 + offset.x;
        cpDesc.position.y = 0 + offset.y;
        cpDesc.position.z = obj.hight;
        splineDesc.Add(cpDesc);
        cpDesc = new Spline3DControlPointDesc();
        cpDesc.position.x = 10 + offset.x;
        cpDesc.position.y = 10 + offset.y;
        cpDesc.position.z = obj.hight;
        splineDesc.Add(cpDesc);
        cpDesc = new Spline3DControlPointDesc();
        cpDesc.position.x = 10 + offset.x;
        cpDesc.position.y = -10 + offset.y;
        cpDesc.position.z = obj.hight;
        splineDesc.Add(cpDesc);
      }

      return splineDesc;
    }
  }
}
