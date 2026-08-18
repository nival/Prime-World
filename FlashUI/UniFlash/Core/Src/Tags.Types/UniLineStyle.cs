using System.Collections.Generic;
using Flash.Utils;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
  [System.Serializable]
  public class UniLineStyle : ISerializable
  {

    private Color _lineColor = Color.white;
    public Color LineColor
    {
      get { return _lineColor; }
    }
    private float _width;
    public float Width
    {
      get { return _width; }
    }
    private bool _endStyle;
    public bool EndStyle
    {
      get { return _endStyle; }
    }
    private UniFillStyle _uniFillStyle;
    public UniFillStyle UniFillStyle
    {
      get { return _uniFillStyle; }
    }
  
    public void GetObjectData(SerializationInfo info, StreamingContext context) {    
        Flash.SerializeHelpers.Pack(info, "_lineColor", _lineColor);
        Flash.SerializeHelpers.Pack(info, "_width", _width);
        Flash.SerializeHelpers.Pack(info, "_endStyle", _endStyle);
        Flash.SerializeHelpers.Pack(info, "_uniFillStyle", _uniFillStyle);
    }
        
    public UniLineStyle(SerializationInfo info, StreamingContext context) {
        Flash.SerializeHelpers.Unpack(info, "_lineColor", out _lineColor);
        Flash.SerializeHelpers.Unpack(info, "_width", out _width);
        Flash.SerializeHelpers.Unpack(info, "_endStyle", out _endStyle);
        Flash.SerializeHelpers.Unpack(info, "_uniFillStyle", out _uniFillStyle);
    }
     
    public UniLineStyle() { }
    public UniLineStyle(LineStyle lineStyle, UniSwf _swf)
    {
      _width = FlashToUnityConverter.TwipsToPixels(lineStyle.Width);
      if (_width < 1)
        _width = 1;
      _width /= 2;

      if (lineStyle is LineStyle2)
      {
        LineStyle2 lineStyle2 = lineStyle as LineStyle2;
        if (lineStyle2.FillStyle != null)
          _uniFillStyle = new UniFillStyle(lineStyle2.FillStyle, _swf);
      }

      if (_uniFillStyle == null)
        _lineColor = FlashToUnityConverter.ConvertColor(lineStyle.Rgb);
    }
    public UniLineStyle(MorphLineStyle lineStyle, UniSwf _swf, bool endStyle)
    {
      _endStyle = endStyle;

      _width = FlashToUnityConverter.TwipsToPixels(lineStyle.StartWidth);
      if (endStyle)
        _width = FlashToUnityConverter.TwipsToPixels(lineStyle.EndWidth);
      
      _width = _width < 1.0f ? 0.5f : _width * 0.5f;

      if (lineStyle is MorphLineStyle2)
      {
        MorphLineStyle2 morphLineStyle2 = lineStyle as MorphLineStyle2;
        if (morphLineStyle2.FillType != null)
          _uniFillStyle = new UniFillStyle(morphLineStyle2.FillType, _swf, endStyle);
      }

      if (_uniFillStyle == null)
      {
        _lineColor = FlashToUnityConverter.ConvertColor(lineStyle.StartColor);
        if (endStyle)
          _lineColor = FlashToUnityConverter.ConvertColor(lineStyle.EndColor);
      }
    }
  }
}
