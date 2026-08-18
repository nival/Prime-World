using System;
using System.Runtime.Serialization;

namespace Flash
{
  [Serializable]
  public class UniBaseTag : ISerializable
  {
    protected UniSwf _swf;
    public UniSwf Swf
    {
      get { return _swf; }
    }
    protected Bounds _localBounds;
    public Bounds LocalBounds
    {
      get { return _localBounds; }
      set { _localBounds = value; }
    }
    private ushort _id = 0;
    public ushort Id
    {
      get { return _id; }
      set { _id = value; }
    }

    public UniBaseTag( UniSwf swf )
    {
      _swf = swf;
    }
    public virtual void Release() { }

    virtual public void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Pack( info, "_swf", _swf );
      Flash.SerializeHelpers.Pack( info, "_localBounds", _localBounds );
      Flash.SerializeHelpers.Pack( info, "_id", _id );
    }

    protected UniBaseTag( SerializationInfo info, StreamingContext context )
    {
      try
      {
        Flash.SerializeHelpers.Unpack( info, "_swf", out _swf );
      }
      catch ( Exception )
      {
        Flash.SerializeHelpers.Unpack( info, "_swf", out _swf );
      }
      Flash.SerializeHelpers.Unpack( info, "_localBounds", out _localBounds );
      Flash.SerializeHelpers.Unpack( info, "_id", out _id );
    }

  }
}
