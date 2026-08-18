using System.Collections.Generic;
using SwfDotNet.IO.Tags;
using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
  [System.Serializable]
  public class UniDefineSpriteTag : UniBaseTag, ISerializable
  {
    private List<IDisplayTag> _tags = new List<IDisplayTag>();
    public List<IDisplayTag> Tags
    {
      get { return _tags; }
      set { _tags = value; }
    }
    private DefineScalingGrid scale9Grid;
    public DefineScalingGrid Scale9Grid
    {
      get { return scale9Grid; }
      set { scale9Grid = value; }
    }
    private int _framesCount;
    public int FramesCount
    {
      get { return _framesCount; }
    }

    public override void GetObjectData(SerializationInfo info, StreamingContext context)
    {
        base.GetObjectData(info, context);
            
        Flash.SerializeHelpers.Pack(info, "_tags", _tags);
        Flash.SerializeHelpers.Pack(info, "scale9Grid", scale9Grid);
        Flash.SerializeHelpers.Pack(info, "_framesCount", _framesCount);
    }
        
    public UniDefineSpriteTag(SerializationInfo info, StreamingContext context) 
        : base (info, context)
    {
        Flash.SerializeHelpers.Unpack(info, "_tags", out _tags);
        Flash.SerializeHelpers.Unpack(info, "scale9Grid", out scale9Grid);            
        Flash.SerializeHelpers.Unpack(info, "_framesCount", out _framesCount);
    }

    public UniDefineSpriteTag(UniSwf owner) : base(owner) { }
    public UniDefineSpriteTag(BaseTag baseTag, UniSwf owner)
      : base(owner)
    {
      DefineSpriteTag spriteTag = (DefineSpriteTag)baseTag;
      _framesCount = spriteTag.FrameCount;

      //Debug.Log("*************** Sprite Tags*******************");
      //UniSwf.ShowTags(spriteTag.Tags);

      UniSwf.ParseTags(spriteTag.Tags, _tags, owner);
    }
  }
}