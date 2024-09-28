using EditorPlugins.Scene;
using EditorNative;
using System.Drawing;
using System.Collections.Generic;
using EditorNative.SceneElements;
using DBTypes;
using libdb;

namespace EditorPlugins.Scene.Editors.Splines
{
  internal interface ISplineMainElement
  {
    void CorrectPosition(Vector3 _point);
    SceneControl SceneControl { get; }
    bool HasWidth { get; }
    bool IsAbsolutePosition { get; }
    Vector3 BaseLocation{ get; set; }
    Quaternion BaseRotation { get; set; }
    Vector3 BaseScale { get; set; }
    void Invalidate();
    void UpdateToolbarItems();
  }

    internal abstract class SplineMainElementBase<TItemPoint, TItemControl> : SceneElement, ISplineMainElement
      where TItemControl : SceneElement
        where TItemPoint : libdb.ICompositeDBValue, libdb.IChangeable
    {
      protected readonly IList<TItemPoint> splinePoints;
      protected readonly List<TItemControl> controlPoints = new List<TItemControl>();
      protected bool needResample = true;
      protected bool isControlPointSelected = false;

      public delegate void UpdateToolbarItemsHandler(bool addEnabled, bool deleteEnabled);
      public event UpdateToolbarItemsHandler UpdateToolbarItemsEvent = null;

      public SceneControl SceneControl { get; protected set; }
      public Vector3 BaseLocation { get; set; }
      public virtual Quaternion BaseRotation { get; set; }
      public virtual Vector3 BaseScale { get; set; }

      public bool HasWidth { get; protected set; }
      public bool IsCircle { get; protected set; }
      public bool IsAbsolutePosition { get; protected set; }

      public SplineMainElementBase( SceneControl _control, IList<TItemPoint> _splinePoints, Vector3 _baseLocation, Quaternion _baseRotation, Vector3 _baseScale, bool _hasWidth, bool _isCircle, bool _isAbsolutePosition )
      {
          SceneControl = _control;
          splinePoints = _splinePoints;
          BaseLocation = _baseLocation;
          BaseRotation = _baseRotation;
          BaseScale = _baseScale;

          HasWidth = _hasWidth;
          IsCircle = _isCircle;
          IsAbsolutePosition = _isAbsolutePosition;
      }

      public void AddToScene( EditorScene scene )
      {
          AddToSceneInternal(scene);
          scene.Add(this);
      }

      public void RemoveFromScene()
      {
          RemoveFromSceneInternal();
          Scene.Remove(this);
          controlPoints.Clear();
      }

      public void UpdateToolbarItems()
      {
          int cpSelected = 0;
          foreach ( TItemControl cp in controlPoints )
          {
              if ( cp.IsSelected )
                  ++cpSelected;
              if ( cp.GetType() == typeof(SplineControlElement) )
              {
                  var obj = cp as SplineControlElement;
                  if ( obj.WidthControl != null && obj.WidthControl.IsSelected )
                      ++cpSelected;
              }
          }

          bool addEnabled = (cpSelected == 1);
          bool deleteEnabled = (cpSelected > 0 && cpSelected < controlPoints.Count - (IsCircle ? 2 : 1));

          isControlPointSelected = (cpSelected > 0);

          if ( null != UpdateToolbarItemsEvent )
              UpdateToolbarItemsEvent( addEnabled, deleteEnabled );
      }

      public void InsertControlPoint(TItemControl cp)
      {
          InsertControlPoint(controlPoints.IndexOf(cp));
      }

      public void DeleteControlPoint(TItemControl cp)
      {
          DeleteControlPoint(controlPoints.IndexOf(cp));
      }

      public void Invalidate() { needResample = true; }

      internal new bool IsSelected { get { return isControlPointSelected; } }

      internal abstract void InsertControlPoint(int position);
      internal abstract void DeleteControlPoint(int position);
      public abstract void CorrectPosition(Vector3 point);
      internal abstract void AddToSceneInternal(EditorScene scene);
      internal abstract void RemoveFromSceneInternal();
    }
}
