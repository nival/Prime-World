package flash.filters
{

    [native(cls="GlowFilterClass", instance="GlowFilterObject", methods="auto")]
    final public class GlowFilter extends BitmapFilter
    {

        public function GlowFilter(color:uint = 16711680, alpha:Number = 1, blurX:Number = 6, blurY:Number = 6, strength:Number = 2, quality:int = 1, inner:Boolean = false, knockout:Boolean = false)
        {
            this.color = color;
            this.alpha = alpha;
            this.blurX = blurX;
            this.blurY = blurY;
            this.quality = quality;
            this.strength = strength;
            this.inner = inner;
            this.knockout = knockout;
            return;
        }// end function

        public native function get strength() : Number;

        public native function set blurX(value:Number) : void;

        public native function get color() : uint;

        public native function set blurY(value:Number) : void;

        public native function set quality(value:int) : void;

        public native function set color(value:uint) : void;

        public native function set strength(value:Number) : void;

        public native function set inner(value:Boolean) : void;

        public native function get blurX() : Number;

        public native function get blurY() : Number;

        public native function set knockout(value:Boolean) : void;

        public native function get inner() : Boolean;

        public native function get knockout() : Boolean;

        public native function set alpha(value:Number) : void;

        override public function clone() : BitmapFilter
        {
            return new GlowFilter(this.color, this.alpha, this.blurX, this.blurY, this.strength, this.quality, this.inner, this.knockout);
        }// end function

        public native function get alpha() : Number;

        public native function get quality() : int;

    }
}
