using SwfDotNet.IO.Tags;
using System.Runtime.Serialization;

namespace Flash
{
    [System.Serializable]
	public class UniSetBackgroundColorTag : UniBaseTag, IDisplayTag, ISerializable
	{
		//private Color _backgroundColor;

		public UniSetBackgroundColorTag( BaseTag baseTag, UniSwf owner ) : base(owner)
		{
			//_backgroundColor = SwfToUnityConverter.ConvertColor( ( baseTag as SetBackgroundColorTag ).RGB );
		}
		public void Execute( Frame frame, Sprite sprite ) { }
        
        public override void GetObjectData (SerializationInfo info, StreamingContext context)
        {
            base.GetObjectData(info, context);
        }
        
        protected UniSetBackgroundColorTag(SerializationInfo info, StreamingContext context) 
            : base(info, context)
        {
        }
	}
}
