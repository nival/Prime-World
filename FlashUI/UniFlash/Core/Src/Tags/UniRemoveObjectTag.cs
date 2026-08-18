using SwfDotNet.IO.Tags;
using System.Runtime.Serialization;

namespace Flash
{
    [System.Serializable]
	public class UniRemoveObjectTag : UniBaseTag, IDisplayTag, ISerializable
	{
		private ushort _depth;
        
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            base.GetObjectData(info, context);
            
            Flash.SerializeHelpers.Pack(info, "_depth", _depth);
        }
        
        public UniRemoveObjectTag(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
            Flash.SerializeHelpers.Unpack(info, "_depth", out _depth);
        }

		public UniRemoveObjectTag( BaseTag baseTag , UniSwf owner): base (owner)
		{
			RemoveObject2Tag removeTag = baseTag as RemoveObject2Tag;
			_depth = removeTag.Depth;
		}
		public void Execute( Frame frame, Sprite sprite )
		{
			if ( _depth > 0 )
			{
				frame.RemoveInternal( _depth );
			}
		}
	}
}
