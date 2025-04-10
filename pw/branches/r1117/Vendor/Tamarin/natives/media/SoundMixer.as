package flash.media
{
    import flash.utils.*;

    [native(cls="SoundMixerClass", instance="SoundMixerObject", methods="auto")]
    final public class SoundMixer extends Object
    {

        public function SoundMixer()
        {
            return;
        }// end function

        public static native function set soundTransform(sndTransform:SoundTransform) : void;

        public static native function areSoundsInaccessible() : Boolean;

        public static native function get bufferTime() : int;

        public static native function computeSpectrum(outputArray:ByteArray, FFTMode:Boolean = false, stretchFactor:int = 0) : void;

        public static native function set bufferTime(bufferTime:int) : void;

        public static native function get soundTransform() : SoundTransform;

        public static native function stopAll() : void;

    }
}
