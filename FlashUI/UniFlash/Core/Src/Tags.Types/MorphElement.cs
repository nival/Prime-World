using System;
using UnityEngine;
using System.Runtime.Serialization;
using System.Collections.Generic;

namespace Flash
{
  [System.Serializable]
  public class MorphElement : RenderableElement, ISerializable
  {
    private List<Vector3> _startContours;
    private List<Vector3> _endContours;
    private Color _startFillColor;
    private Color _endFillColor;
    private Color _startLineColor;
    private Color _endLineColor;
    private float _startFillFocalPoint;
    private float _endFillFocalPoint;
    private Matrix4x4 _startFillBitmapTransform;
    private Matrix4x4 _endFillBitmapTransform;
    private TextureTransform _startFillTextureTransform;
    private TextureTransform _endFillTextureTransform;
    private float _startLineWidth;
    private float _endLineWidth;
    private UnityEngine.Rect _startBounds;
    private UnityEngine.Rect _endBounds;
    private bool _closedShape;
    
    public UnityEngine.Rect StartBounds
    {
      get { return _startBounds; }
      set { _startBounds = value; }
    }
    
    public UnityEngine.Rect EndBounds
    {
      get { return _endBounds; }
      set { _endBounds = value; }
    }
    
    public bool IsClosed
    {
      get { return _closedShape; }
      set { _closedShape = value; }
    }

    public List<Vector3> StartContours
    {
      get { return _startContours; }
      set { _startContours = value; }
    }

    public List<Vector3> EndContours
    {
      get { return _endContours; }
      set { _endContours = value; }
    }

    public Color StartFillColor
    {
      get { return _startFillColor; }
      set { _startFillColor = value; }
    }

    public Color EndFillColor
    {
      get { return _endFillColor; }
      set { _endFillColor = value; }
    }

    public Color StartLineColor
    {
      get { return _startLineColor; }
      set { _startLineColor = value; }
    }

    public Color EndLineColor
    {
      get { return _endLineColor; }
      set { _endLineColor = value; }
    }

    public float StartFillFocalPoint
    {
      get { return _startFillFocalPoint; }
      set { _startFillFocalPoint = value; }
    }

    public float EndFillFocalPoint
    {
      get { return _endFillFocalPoint; }
      set { _endFillFocalPoint = value; }
    }

    public Matrix4x4 StartFillBitmapTransform
    {
      get { return _startFillBitmapTransform; }
      set { _startFillBitmapTransform = value; }
    }

    public Matrix4x4 EndFillBitmapTransform
    {
      get { return _endFillBitmapTransform; }
      set { _endFillBitmapTransform = value; }
    }

    public TextureTransform StartFillTextureTransform
    {
      get { return _startFillTextureTransform; }
      set { _startFillTextureTransform = value; }
    }

    public TextureTransform EndFillTextureTransform
    {
      get { return _endFillTextureTransform; }
      set { _endFillTextureTransform = value; }
    }

    public float StartLineWidth
    {
      get { return _startLineWidth; }
      set { _startLineWidth = value; }
    }

    public float EndLineWidth
    {
      get { return _endLineWidth; }
      set { _endLineWidth = value; }
    }

    public override void GetObjectData(SerializationInfo info, StreamingContext context)
    {
        base.GetObjectData(info, context);
            
        Flash.SerializeHelpers.Pack(info, "StartFillColor", StartFillColor);
        Flash.SerializeHelpers.Pack(info, "EndFillColor", EndFillColor);
        Flash.SerializeHelpers.Pack(info, "StartLineColor", StartLineColor);
        Flash.SerializeHelpers.Pack(info, "EndLineColor", EndLineColor);
            
        Flash.SerializeHelpers.Pack(info, "StartFillFocalPoint", StartFillFocalPoint);
        Flash.SerializeHelpers.Pack(info, "EndFillFocalPoint", EndFillFocalPoint);
            
        Flash.SerializeHelpers.Pack(info, "StartFillBitmapTransform", StartFillBitmapTransform);
        Flash.SerializeHelpers.Pack(info, "EndFillBitmapTransform", EndFillBitmapTransform);            
            
        Flash.SerializeHelpers.Pack(info, "StartFillTextureTransform", StartFillTextureTransform);
        Flash.SerializeHelpers.Pack(info, "EndFillTextureTransform", EndFillTextureTransform);
    }
        
    public MorphElement(SerializationInfo info, StreamingContext context) 
        : base (info, context)
    {
        Flash.SerializeHelpers.Unpack(info, "StartFillColor", out _startFillColor);
        Flash.SerializeHelpers.Unpack(info, "EndFillColor", out _endFillColor);
        Flash.SerializeHelpers.Unpack(info, "StartLineColor", out _startLineColor);
        Flash.SerializeHelpers.Unpack(info, "EndLineColor", out _endLineColor);
            
        Flash.SerializeHelpers.Unpack(info, "StartFillFocalPoint", out _startFillFocalPoint);
        Flash.SerializeHelpers.Unpack(info, "EndFillFocalPoint", out _endFillFocalPoint);
            
        Flash.SerializeHelpers.Unpack(info, "StartFillBitmapTransform", out _startFillBitmapTransform);
        Flash.SerializeHelpers.Unpack(info, "EndFillBitmapTransform", out _endFillBitmapTransform);            
            
        Flash.SerializeHelpers.Unpack(info, "StartFillTextureTransform", out _startFillTextureTransform);
        Flash.SerializeHelpers.Unpack(info, "EndFillTextureTransform", out _endFillTextureTransform);
    }
        
    public MorphElement() {
    }
  }
}