using System;
using UnityEngine;
using Flash.Render;
using System.Runtime.Serialization;

namespace Flash
{
  [System.Serializable]
  public abstract class RenderableElement : ICloneable, IDisposable, ISerializable
  {
    private bool _transparent = false;
    public bool Transparent
    {
      get { return _transparent; }
      set { _transparent = value; }
    }
    private Mesh _fillMesh;
    public Mesh FillMesh
    {
      get { return _fillMesh; }
      set { _fillMesh = value; }
    }
    private FlashMaterial _fillMaterial;
    public FlashMaterial FillMaterial
    {
      get { return _fillMaterial; }
      set { _fillMaterial = value; }
    }


    private bool _transparentLine = false;
    public bool TransparentLine
    {
      get { return _transparentLine; }
      set { _transparentLine = value; }
    }
    private Mesh _lineMesh;
    public Mesh LineMesh
    {
      get { return _lineMesh; }
      set { _lineMesh = value; }
    }
    private FlashMaterial _lineMaterial;
    public FlashMaterial LineMaterial
    {
      get { return _lineMaterial; }
      set { _lineMaterial = value; }
    }


    private int _lineTriangleOffset = -1;
    public int LineTriangleOffset
    {
      get { return _lineTriangleOffset; }
      set
      {
          _lineTriangleOffset = value;
      }
    }
    private int _lineVertexOffset = -1;
    public int LineVertexOffset
    {
      get { return _lineVertexOffset; }
      set
      {
          _lineVertexOffset = value;
      }
    }
        
    public RenderableElement(SerializationInfo info, StreamingContext context) 
    {
    }
        
    public RenderableElement() {
    }
        
    public virtual void GetObjectData(SerializationInfo info, StreamingContext context) {
    }


    public object Clone()
    {
      RenderableElement clone = (RenderableElement)MemberwiseClone();
      return clone;
    }

    public virtual void Dispose()
    {
      if (_fillMesh != null)
        Mesh.Destroy(_fillMesh);
      if (_lineMesh != null)
        Mesh.Destroy(_lineMesh);
      if (_fillMaterial != null)
        _fillMaterial.Release();
      if (_lineMaterial != null)
        _lineMaterial.Release();
    }

    public virtual void Release(){}
  }
}
