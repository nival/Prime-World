package flash.media
{
    import flash.events.*;
    import flash.net.*;
    import flash.utils.*;

    [native(cls="SoundClass", instance="SoundObject", methods="auto")]
    public class Sound extends EventDispatcher
    {

        public function Sound(stream:URLRequest = null, context:SoundLoaderContext = null)
        {
            this.load(stream, context);
            return;
        }// end function

        public native function extract(target:ByteArray, length:Number, startPosition:Number = -1) : Number;

        private native function _load(stream:URLRequest, checkPolicyFile:Boolean, bufferTime:Number) : void;

        public function load(stream:URLRequest, context:SoundLoaderContext = null) : void
        {
            var _loc_3:* = this._buildLoaderContext(context);
            this._load(stream, _loc_3.checkPolicyFile, _loc_3.bufferTime);
            return;
        }// end function

        public native function close() : void;

        private function _buildLoaderContext(context:SoundLoaderContext) : SoundLoaderContext
        {
            if (context == null)
            {
                context = new SoundLoaderContext();
            }
            return context;
        }// end function

        public native function get url() : String;

        public native function get bytesLoaded() : uint;

        public native function play(startTime:Number = 0, loops:int = 0, sndTransform:SoundTransform = null) : SoundChannel;

        public native function get length() : Number;

        public native function get id3() : ID3Info;

        public native function get bytesTotal() : int;

        public native function get isBuffering() : Boolean;

    }
}
