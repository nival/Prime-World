using System;
using Flash.Utils;
using SwfDotNet.IO.Tags;
using UnityEngine;

namespace Flash
{
  public class ScaleGridData : ICloneable
  {
    private Bounds _localSplitterBounds;
    public Bounds LocalSplitterBounds
    {
      get { return _localSplitterBounds; }
    }
    private Bounds _worldStartBounds;
    private Bounds _worldSpriteBounds;
    private Bounds _worldTargetBounds;
    private Vector3 _worldScaleCenter;
    public Vector3 WorldScaleCenter
    {
      get { return _worldScaleCenter; }
    }
    private Vector3 _worldScale;
    public Vector3 WorldScale
    {
      get { return _worldScale; }
    }
    private Vector4 _localSceleGrid;
    public Vector4 LocalScaleGrid
    {
      get { return _localSceleGrid; }
    }
    private Vector4 _targetScaleGrid;
    public Vector4 TargetScaleGrid
    {
      get { return _targetScaleGrid; }
    }
    private Sprite _sprite;
    public Sprite Sprite
    {
      get { return _sprite; }
      set { _sprite = value; }
    }

    private Matrix4x4 _scaleGridSummary;
    public Matrix4x4 ScaleGridSummary
    {
      get { return _scaleGridSummary; }
    }

    private int _version = 0;
    public int Version
    {
      get { return _version; }
      set { _version = value; }
    }

    public ScaleGridData(Sprite sprite, DefineScalingGrid scalingGrid)
    {
      _sprite = sprite;
      _localSplitterBounds = new Bounds()
      {
        LeftTop = FlashToUnityConverter.ConvertPosition(scalingGrid.Splitter.XMin, scalingGrid.Splitter.YMin),
        RightBottom = FlashToUnityConverter.ConvertPosition(scalingGrid.Splitter.XMax, scalingGrid.Splitter.YMax),
      };
      _localSceleGrid.x = _localSplitterBounds.LeftTop.x;
      _localSceleGrid.y = _localSplitterBounds.LeftTop.y;
      _localSceleGrid.z = _localSplitterBounds.RightBottom.x;
      _localSceleGrid.w = _localSplitterBounds.RightBottom.y;
    }
    public void UpdateScaleGrid()
    {
      //Profiler.BeginSample("UPDATE_SCALEGRID");

      Vector4 offset = new Vector4(); // left , right, top , bottom
      offset.x = _sprite.LocalBounds.LeftTop.x - _localSplitterBounds.LeftTop.x;
      offset.y = _sprite.LocalBounds.RightBottom.x - _localSplitterBounds.RightBottom.x;
      offset.z = _sprite.LocalBounds.LeftTop.y - _localSplitterBounds.LeftTop.y;
      offset.w = _sprite.LocalBounds.RightBottom.y - _localSplitterBounds.RightBottom.y;

      _worldStartBounds = _sprite.Transform.WorldMatrix * _localSplitterBounds;
      _worldSpriteBounds = _sprite.Transform.WorldMatrix * _sprite.LocalBounds;

      Vector3 lt = _worldSpriteBounds.LeftTop;
      Vector3 rb = _worldSpriteBounds.RightBottom;
      lt.x -= offset.x;
      lt.y -= offset.z;
      rb.x -= offset.y;
      rb.y -= offset.w;
      _worldTargetBounds = new Bounds()
      {
        LeftTop = lt,
        RightBottom = rb,
      };
      _targetScaleGrid.x = _worldTargetBounds.LeftTop.x;
      _targetScaleGrid.y = _worldTargetBounds.LeftTop.y;
      _targetScaleGrid.z = _worldTargetBounds.RightBottom.x;
      _targetScaleGrid.w = _worldTargetBounds.RightBottom.y;

      #region Center point of splitter scale
      float xl0 = _worldStartBounds.LeftTop.x;
      float xr0 = _worldStartBounds.RightBottom.x;
      float xl1 = _worldTargetBounds.LeftTop.x;
      float xr1 = _worldTargetBounds.RightBottom.x;

      float yl0 = _worldStartBounds.LeftTop.y;
      float yr0 = _worldStartBounds.RightBottom.y;
      float yl1 = _worldTargetBounds.LeftTop.y;
      float yr1 = _worldTargetBounds.RightBottom.y;

      if (xl0 == xl1 && xr0 == xr1)
        _worldScaleCenter.x = (xl0 + xr0) / 2;
      else
        _worldScaleCenter.x = (xl0 * xr1 - xl1 * xr0) / (-xr0 - xl1 + xr1 + xl0);

      if (yl0 == yl1 && yr0 == yr1)
        _worldScaleCenter.y = (yl0 + yr0) / 2;
      else
        _worldScaleCenter.y = (yl0 * yr1 - yl1 * yr0) / (-yr0 - yl1 + yr1 + yl0);
      #endregion

      _worldScale = new Vector3();
      _worldScale.x = _worldTargetBounds.Width / _worldStartBounds.Width;
      _worldScale.y = _worldTargetBounds.Height / _worldStartBounds.Height;


      _scaleGridSummary.SetRow(0, LocalScaleGrid);
      _scaleGridSummary.SetRow(1, TargetScaleGrid);
      _scaleGridSummary[2,0] = _worldScaleCenter.x;
      _scaleGridSummary[2,1] = _worldScaleCenter.y;
      _scaleGridSummary[2,2] = _worldScale.x;
      _scaleGridSummary[2,3] = _worldScale.y;
      _scaleGridSummary.SetRow(3, _sprite.TexelHint);

      _version++;

      //Profiler.EndSample();
    }
    public void DrawScaleGrid()
    {
      GL.LoadProjectionMatrix(GL.GetGPUProjectionMatrix(UniFlashPlayer.Camera.projectionMatrix, false));
      UniFlashPlayer.FlashDebug.DrawMaterial.SetPass(0);
      GL.Begin(GL.LINES);

      // sprite world bounding
      GL.Color(new Color(0, 1, 0, 1F));
      GL.Vertex3(_worldSpriteBounds.LeftTop.x, _worldSpriteBounds.LeftTop.y, 0);
      GL.Vertex3(_worldSpriteBounds.LeftTop.x, _worldSpriteBounds.RightBottom.y, 0);
      GL.Vertex3(_worldSpriteBounds.LeftTop.x, _worldSpriteBounds.RightBottom.y, 0);
      GL.Vertex3(_worldSpriteBounds.RightBottom.x, _worldSpriteBounds.RightBottom.y, 0);
      GL.Vertex3(_worldSpriteBounds.RightBottom.x, _worldSpriteBounds.RightBottom.y, 0);
      GL.Vertex3(_worldSpriteBounds.RightBottom.x, _worldSpriteBounds.LeftTop.y, 0);
      GL.Vertex3(_worldSpriteBounds.RightBottom.x, _worldSpriteBounds.LeftTop.y, 0);
      GL.Vertex3(_worldSpriteBounds.LeftTop.x, _worldSpriteBounds.LeftTop.y, 0);

      // target bounds
      GL.Color(new Color(0, 0, 1, 1));
      GL.Vertex3(_worldTargetBounds.LeftTop.x, _worldTargetBounds.LeftTop.y, 0);
      GL.Vertex3(_worldTargetBounds.LeftTop.x, _worldTargetBounds.RightBottom.y, 0);
      GL.Vertex3(_worldTargetBounds.LeftTop.x, _worldTargetBounds.RightBottom.y, 0);
      GL.Vertex3(_worldTargetBounds.RightBottom.x, _worldTargetBounds.RightBottom.y, 0);
      GL.Vertex3(_worldTargetBounds.RightBottom.x, _worldTargetBounds.RightBottom.y, 0);
      GL.Vertex3(_worldTargetBounds.RightBottom.x, _worldTargetBounds.LeftTop.y, 0);
      GL.Vertex3(_worldTargetBounds.RightBottom.x, _worldTargetBounds.LeftTop.y, 0);
      GL.Vertex3(_worldTargetBounds.LeftTop.x, _worldTargetBounds.LeftTop.y, 0);

      // local splitter bounds
      GL.Color(new Color(1, 0, 0, 1F));
      GL.Vertex3(_worldStartBounds.LeftTop.x, _worldStartBounds.LeftTop.y, 0);
      GL.Vertex3(_worldStartBounds.LeftTop.x, _worldStartBounds.RightBottom.y, 0);
      GL.Vertex3(_worldStartBounds.LeftTop.x, _worldStartBounds.RightBottom.y, 0);
      GL.Vertex3(_worldStartBounds.RightBottom.x, _worldStartBounds.RightBottom.y, 0);
      GL.Vertex3(_worldStartBounds.RightBottom.x, _worldStartBounds.RightBottom.y, 0);
      GL.Vertex3(_worldStartBounds.RightBottom.x, _worldStartBounds.LeftTop.y, 0);
      GL.Vertex3(_worldStartBounds.RightBottom.x, _worldStartBounds.LeftTop.y, 0);
      GL.Vertex3(_worldStartBounds.LeftTop.x, _worldStartBounds.LeftTop.y, 0);

      // scale center
      GL.Color(new Color(0, 1, 0, 1F));
      int s = 2;
      GL.Vertex3(_worldScaleCenter.x - s, _worldScaleCenter.y + s, 0);
      GL.Vertex3(_worldScaleCenter.x + s, _worldScaleCenter.y + s, 0);

      GL.Vertex3(_worldScaleCenter.x + s, _worldScaleCenter.y + s, 0);
      GL.Vertex3(_worldScaleCenter.x + s, _worldScaleCenter.y - s, 0);

      GL.Vertex3(_worldScaleCenter.x + s, _worldScaleCenter.y - s, 0);
      GL.Vertex3(_worldScaleCenter.x - s, _worldScaleCenter.y - s, 0);

      GL.Vertex3(_worldScaleCenter.x - s, _worldScaleCenter.y - s, 0);
      GL.Vertex3(_worldScaleCenter.x - s, _worldScaleCenter.y + s, 0);

      GL.End();
    }
    public object Clone()
    {
      ScaleGridData clone = (ScaleGridData)MemberwiseClone();
      return clone;
    }
  }
}