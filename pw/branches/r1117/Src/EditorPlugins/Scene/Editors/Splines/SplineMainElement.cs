using EditorPlugins.Scene;
using EditorNative;
using EditorPlugins.Mathematics;
using DBTypes;
using System.Collections.Generic;
using System.Drawing;

namespace EditorPlugins.Scene.Editors.Splines
{
    internal class WideSplineSampledPoint
    {
      public PointF location;
      public PointF normal;
      public float width = 2;
      public FlatSplineControlPointDesc cpoint = null;
    }

    class SplineMainElement<TItem> : SplineMainElementBase<TItem, SplineControlElement>
    where TItem : FlatSplineControlPointDesc, new()
    {
        private readonly List<WideSplineSampledPoint> sampledPoints = new List<WideSplineSampledPoint>();

        public SplineMainElement(SceneControl control, IList<TItem> splinePoints, Vector3 baseLocation, Quaternion baseRotation, Vector3 baseScale, bool hasWidth, bool isCircle, bool isAbsolutePosition)
          : base( control, splinePoints, baseLocation, baseRotation, baseScale, hasWidth, isCircle, isAbsolutePosition )
        {
        }

        public override void CorrectPosition(Vector3 point)
        {
            if (!IsAbsolutePosition)
            {
                point.X += BaseLocation.X;
                point.Y += BaseLocation.Y;
            }
        }

        internal override void AddToSceneInternal(EditorScene scene) 
        {
            for (int i = 0; i < splinePoints.Count; ++i)
            {
                SplineControlElement newCP = new SplineControlElement(this, splinePoints[i]);
                controlPoints.Add(newCP);
                newCP.AddToScene(scene);
            }
        }

        internal override void RemoveFromSceneInternal()
        {
            for (int i = 0; i < controlPoints.Count; ++i)
                controlPoints[i].RemoveFromScene();
        }

        public override void Draw()
        {
            if (null == splinePoints || splinePoints.Count < 2)
               return;

            float z = 0;

            Vector3 prevPoint = new Vector3(splinePoints[0].location.x, splinePoints[0].location.y, 0);
            CorrectPosition(prevPoint);
            Scene.SceneTerrain.TryGetHeight(prevPoint.X, prevPoint.Y, ref z);
            prevPoint.Z = z;
            Vector3 startPoint = prevPoint;

            for (int i = 1; i < splinePoints.Count; ++i)
            {
                Vector3 curPoint = new Vector3(splinePoints[i].location.x, splinePoints[i].location.y, 0);
                CorrectPosition(curPoint);
                Scene.SceneTerrain.TryGetHeight(curPoint.X, curPoint.Y, ref z);
                curPoint.Z = z;

                EditorRender.DrawLine3D(prevPoint, curPoint, System.Drawing.Color.Red, false);
                prevPoint = curPoint;
            }

            if (IsCircle)
                EditorRender.DrawLine3D(prevPoint, startPoint, System.Drawing.Color.Red, false);


            if (needResample)
                ResampleSpline();

            if (sampledPoints.Count == 0)
                return;

            prevPoint = new Vector3(sampledPoints[0].location.X, sampledPoints[0].location.Y, 0);
            CorrectPosition(prevPoint);
            Scene.SceneTerrain.TryGetHeight(prevPoint.X, prevPoint.Y, ref z);
            prevPoint.Z = z;
            PointF offset = sampledPoints[0].normal;
            offset.X *= sampledPoints[0].width;
            offset.Y *= sampledPoints[0].width;
            Vector3 prevEdge1 = new Vector3(sampledPoints[0].location.X + offset.X, sampledPoints[0].location.Y + offset.Y, 0);
            Vector3 prevEdge2 = new Vector3(sampledPoints[0].location.X - offset.X, sampledPoints[0].location.Y - offset.Y, 0);
            CorrectPosition(prevEdge1);
            CorrectPosition(prevEdge2);
            Vector3 startEdge1 = prevEdge1;
            Vector3 startEdge2 = prevEdge2;
            startPoint = prevPoint;
            if (HasWidth)
            {
                Scene.SceneTerrain.TryGetHeight(prevEdge1.X, prevEdge1.Y, ref z);
                prevEdge1.Z = z;
                Scene.SceneTerrain.TryGetHeight(prevEdge2.X, prevEdge2.Y, ref z);
                prevEdge2.Z = z;
                EditorRender.DrawLine3D(prevPoint, prevEdge1, System.Drawing.Color.Yellow, false);
                 EditorRender.DrawLine3D(prevPoint, prevEdge2, System.Drawing.Color.Yellow, false);
            }

            for (int i = 1; i < sampledPoints.Count; ++i)
            {
                Vector3 curPoint = new Vector3(sampledPoints[i].location.X, sampledPoints[i].location.Y, 0);
                CorrectPosition(curPoint);
                Scene.SceneTerrain.TryGetHeight(curPoint.X, curPoint.Y, ref z);
                curPoint.Z = z;
                 
                EditorRender.DrawLine3D(prevPoint, curPoint, System.Drawing.Color.Yellow, false);

                if (HasWidth)
                {
                    offset = sampledPoints[i].normal;
                    offset.X *= sampledPoints[i].width;
                    offset.Y *= sampledPoints[i].width;
                    Vector3 curEdge1 = new Vector3(sampledPoints[i].location.X + offset.X, sampledPoints[i].location.Y + offset.Y, 0);
                    CorrectPosition(curEdge1);
                    Scene.SceneTerrain.TryGetHeight(curEdge1.X, curEdge1.Y, ref z);
                    curEdge1.Z = z;
                    Vector3 curEdge2 = new Vector3(sampledPoints[i].location.X - offset.X, sampledPoints[i].location.Y - offset.Y, 0);
                    CorrectPosition(curEdge2);
                    Scene.SceneTerrain.TryGetHeight(curEdge2.X, curEdge2.Y, ref z);
                    curEdge2.Z = z;
                    EditorRender.DrawLine3D(curPoint, curEdge1, System.Drawing.Color.Aqua, false);
                    EditorRender.DrawLine3D(curPoint, curEdge2, System.Drawing.Color.Aqua, false);
                    EditorRender.DrawLine3D(prevEdge1, curEdge1, System.Drawing.Color.Green, false);
                    EditorRender.DrawLine3D(prevEdge2, curEdge2, System.Drawing.Color.Green, false);
                     
                    prevEdge1 = curEdge1;
                    prevEdge2 = curEdge2;
                }

                prevPoint = curPoint;
            }

            if (IsCircle)
            {
                EditorRender.DrawLine3D(prevPoint, startPoint, System.Drawing.Color.Yellow, false);
                if (HasWidth)
                {
                    EditorRender.DrawLine3D(prevEdge1, startEdge1, System.Drawing.Color.Green, false);
                    EditorRender.DrawLine3D(prevEdge2, startEdge2, System.Drawing.Color.Green, false);
                }
            }
        }

        internal override void InsertControlPoint(int position)
        {
            if (position < 0 || position >= controlPoints.Count)
                return;

            int i = (position == 0) ? 1 : position;

            TItem point = new TItem();
            point.location.x = (splinePoints[i].location.x + splinePoints[i - 1].location.x) * 0.5f;
            point.location.y = (splinePoints[i].location.y + splinePoints[i - 1].location.y) * 0.5f;
            point.width = (splinePoints[i].width + splinePoints[i - 1].width) * 0.5f;
            splinePoints.Insert(i, point);

            SplineControlElement newCP = new SplineControlElement(this, splinePoints[i]);
            controlPoints.Insert(i, newCP);
            newCP.AddToScene(Scene);

            UpdateToolbarItems();
            Invalidate();
        }

        internal override void DeleteControlPoint(int position)
        {
            if (position < 0 || position >= controlPoints.Count || controlPoints.Count <= 2)
               return;

            SplineControlElement cp = controlPoints[position];
            controlPoints.RemoveAt(position);
            splinePoints.RemoveAt(position);
            cp.RemoveFromScene();

            UpdateToolbarItems();
            Invalidate();
       }

        private void ResampleSpline()
        {
            if (splinePoints.Count < 2)
                return;
             
            sampledPoints.Clear();

            List<PointF> cpsSource = new List<PointF>(splinePoints.Count);
            for (int i = 0; i < splinePoints.Count; ++i)
                cpsSource.Add(new PointF(splinePoints[i].location.x, splinePoints[i].location.y));

            CompositeBSpline.SampleSpline(cpsSource, IsCircle, SplineSampleFunctor);

            if (HasWidth)
                SampleWidth();

            needResample = false;
        }

        private void SplineSampleFunctor(PointF position, PointF normal, int cpIndex)
        {
            WideSplineSampledPoint point = new WideSplineSampledPoint();
            point.location = position;
            point.width = 1;
            if (HasWidth && cpIndex >= 0)
            {
                point.cpoint = splinePoints[cpIndex];
                point.width = point.cpoint.width;
                controlPoints[cpIndex].WidthControl.SetSampledPoint(point);
            }
            point.normal = normal;
            sampledPoints.Add(point);
        }

        private void SampleWidth()
        {
            List<int> keyPoints = new List<int>(splinePoints.Count + 4);
            if (IsCircle)
                keyPoints.Add(-1);
            else
                keyPoints.Add(sampledPoints.Count - 1);

            for (int i = 0; i < sampledPoints.Count; ++i)
            {
                if (sampledPoints[i].cpoint != null)
                    keyPoints.Add(i);
            }

            if (IsCircle)
            {
                keyPoints[0] = keyPoints[keyPoints.Count - 1];
                keyPoints.Add(keyPoints[1]);
                keyPoints.Add(keyPoints[2]);
            }
            else
            {
                keyPoints.Add(sampledPoints.Count - 1);
            }

            InterpolatingSpline spline1D = new InterpolatingSpline();
            for (int i = 0; i < keyPoints.Count - 3; ++i)
            {
                int idx0 = keyPoints[i];
                int idx1 = keyPoints[i + 1];
                int idx2 = keyPoints[i + 2];
                int idx3 = keyPoints[i + 3];
                 
                spline1D.Setup(sampledPoints[idx0].width, sampledPoints[idx1].width, sampledPoints[idx2].width, sampledPoints[idx3].width);

                if (idx2 <= idx1 && IsCircle)
                {
                    for (int j = idx1; j < sampledPoints.Count; ++j)
                    {
                        float ratio = ((float)(j - idx1)) / (sampledPoints.Count - idx1);
                        sampledPoints[j].width = spline1D.Get(ratio);
                    }
                     
                    continue;
                }

                for (int j = idx1; j < idx2; ++j)
                {
                    float ratio = ((float)(j - idx1)) / (idx2 - idx1);
                    sampledPoints[j].width = spline1D.Get(ratio);
                }
            }
        }
    }
}

