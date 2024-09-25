package flash.media
{
    import flash.events.*;

    [native(cls="SoundChannelClass", instance="SoundChannelObject", methods="auto")]
    final public class SoundChannel extends EventDispatcher
    {

        public function SoundChannel()
        {
            return;
        }// end function

        public native function stop() : void;

        public native function get leftPeak() : Number;

        public native function get position() : Number;

        public native function set soundTransform(sndTransform:SoundTransform) : void;

        public native function get rightPeak() : Number;

        public native function get soundTransform() : SoundTransform;

    }
}
