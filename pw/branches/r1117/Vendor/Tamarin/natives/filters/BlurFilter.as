package flash.filters
{

    [native(cls="BlurFilterClass", instance="BlurFilterObject", methods="auto")]
    final public class BlurFilter extends BitmapFilter
    {

        public function BlurFilter(blurX:Number = 4, blurY:Number = 4, quality:int = 1)
        {
            this.blurX = blurX;
            this.blurY = blurY;
            this.quality = quality;
            return;
        }// end function

        public native function get blurX() : Number;

        public native function set blurX(value:Number) : void;

        public native function set blurY(value:Number) : void;

        public native function get blurY() : Number;

        override public function clone() : BitmapFilter
        {
            return new BlurFilter(this.blurX, this.blurY, this.quality);
        }// end function

        public native function set quality(value:int) : void;

        public native function get quality() : int;

    }
}
