package flash.filters
{

    [native(cls="DropShadowFilterClass", instance="DropShadowFilterObject", methods="auto")]
    final public class DropShadowFilter extends BitmapFilter
    {

        public function DropShadowFilter(distance:Number = 4, angle:Number = 45, color:uint = 0, alpha:Number = 1, blurX:Number = 4, blurY:Number = 4, strength:Number = 1, quality:int = 1, inner:Boolean = false, knockout:Boolean = false, hideObject:Boolean = false)
        {
            this.distance = distance;
            this.angle = angle;
            this.color = color;
            this.alpha = alpha;
            this.blurX = blurX;
            this.blurY = blurY;
            this.quality = quality;
            this.strength = strength;
            this.inner = inner;
            this.knockout = knockout;
            this.hideObject = hideObject;
            return;
        }// end function

        public native function get hideObject() : Boolean;

        public native function set blurX(value:Number) : void;

        public native function get color() : uint;

        public native function set blurY(value:Number) : void;

        public native function set quality(value:int) : void;

        public native function set angle(value:Number) : void;

        public native function get strength() : Number;

        public native function set hideObject(value:Boolean) : void;

        public native function set distance(value:Number) : void;

        public native function set inner(value:Boolean) : void;

        public native function set color(value:uint) : void;

        public native function set strength(value:Number) : void;

        public native function get blurX() : Number;

        public native function get blurY() : Number;

        public native function get angle() : Number;

        public native function set knockout(value:Boolean) : void;

        public native function get distance() : Number;

        public native function get inner() : Boolean;

        public native function get knockout() : Boolean;

        public native function set alpha(value:Number) : void;

        override public function clone() : BitmapFilter
        {
            return new DropShadowFilter(this.distance, this.angle, this.color, this.alpha, this.blurX, this.blurY, this.strength, this.quality, this.inner, this.knockout, this.hideObject);
        }// end function

        public native function get alpha() : Number;

        public native function get quality() : int;

    }
}
