using System.Runtime.Serialization;

namespace Flash
{
    [System.Serializable]
	public class UniShowFrameTag : UniBaseTag, IDisplayTag, ISerializable
	{
		public UniShowFrameTag(UniSwf owner) : base(owner){}
		public void Execute( Frame frame, Sprite sprite ) { }
        
        protected UniShowFrameTag(SerializationInfo info, StreamingContext context) 
            : base(info, context)
        {
        }
	}
}
