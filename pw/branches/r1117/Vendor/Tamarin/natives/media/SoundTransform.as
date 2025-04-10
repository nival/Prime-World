package flash.media
{

    [native(cls="SoundTransformClass", instance="SoundTransformObject", methods="auto")]
    final public class SoundTransform extends Object
    {

        public function SoundTransform(vol:Number = 1, panning:Number = 0)
        {
            this.volume = vol;
            this.pan = panning;
            return;
        }// end function

        public function set pan(panning:Number) : void
        {
            this.leftToLeft = Math.sqrt(1 - panning);
            this.leftToRight = 0;
            this.rightToRight = Math.sqrt(1 + panning);
            this.rightToLeft = 0;
            return;
        }// end function

        public native function get rightToRight() : Number;

        public native function get volume() : Number;

        public native function get leftToLeft() : Number;

        public native function set rightToRight(rightToRight:Number) : void;

        public native function set leftToLeft(leftToLeft:Number) : void;

        public native function set leftToRight(leftToRight:Number) : void;

        public native function get leftToRight() : Number;

        public native function set volume(volume:Number) : void;

        public native function set rightToLeft(rightToLeft:Number) : void;

        public function get pan() : Number
        {
            if (this.leftToRight == 0)
            {
            }
            if (this.rightToLeft == 0)
            {
                return 1 - this.leftToLeft * this.leftToLeft;
            }
            return 0;
        }// end function

        public native function get rightToLeft() : Number;

    }
}
