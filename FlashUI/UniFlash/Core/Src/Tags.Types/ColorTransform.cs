using SwfDotNet.IO.Tags.Types;
using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
    [System.Serializable]
  public class ColorTransform : ISerializable
  {
    private Color _addColor = Color.clear;
    public Color AddColor
    {
      get { return _addColor; }
      set
      {
        _addColor = value;
      }
    }
    private Color _multColor = Color.white;
    public Color MultColor
    {
      get { return _multColor; }
      set
      {
        _multColor = value;
      }
    }
        
    public void GetObjectData(SerializationInfo info, StreamingContext context) {
        Flash.SerializeHelpers.Pack(info, "_addColor", _addColor);
        Flash.SerializeHelpers.Pack(info, "_multColor", _multColor);
    }
        
    public ColorTransform(SerializationInfo info, StreamingContext context) {
        Flash.SerializeHelpers.Unpack(info, "_addColor", out _addColor);
        Flash.SerializeHelpers.Unpack(info, "_multColor", out _multColor);
    }

    public ColorTransform(CXFormWithAlphaData data)
    {
      if (data != null)
      {
        if (data.HasAddTerms)
        {
          AddColor = new Color(data.RedAddTerms / 256.0F, data.GreenAddTerms / 256.0F, data.BlueAddTerms / 256.0F,
                      data.AlphaAddTerms / 256.0F);
        }
        if (data.HasMultTerms)
        {
          MultColor = new Color(data.RedMultTerms / 256.0F, data.GreenMultTerms / 256.0F, data.BlueMultTerms / 256.0F,
                       data.AlphaMultTerms / 256.0F);
        }
      }
    }
    public override string ToString()
    {
      return "AddColor: " + _addColor + " MultColor: " + _multColor;
    }
  }
}
