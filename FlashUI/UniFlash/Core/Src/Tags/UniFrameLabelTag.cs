
using SwfDotNet.IO.Tags;
using System.Runtime.Serialization;

namespace Flash
{
    [System.Serializable]
	public class UniFrameLabelTag : UniBaseTag, IDisplayTag, ISerializable
	{
	    private string _label;
	    public string Label
	    {
            get { return _label; }
	    }
        
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            base.GetObjectData(info, context);
            
            Flash.SerializeHelpers.Pack(info, "_label", _label);
        }
        
        public UniFrameLabelTag(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
            Flash.SerializeHelpers.Unpack(info, "_label", out _label);
        }
        
        public UniFrameLabelTag(BaseTag baseTag,UniSwf owner) : base(owner)
        {
            _label = ((FrameLabelTag)baseTag).Name;
        }
		public void Execute( Frame frame, Sprite sprite ) { }
	}
}
