package flash.filters
{

    [native(cls="GradientBevelFilterClass", instance="GradientBevelFilterObject", methods="auto")]
    final public class GradientBevelFilter extends BitmapFilter
    {

        public function GradientBevelFilter(distance:Number = 4, angle:Number = 45, colors:Array = null, alphas:Array = null, ratios:Array = null, blurX:Number = 4, blurY:Number = 4, strength:Number = 1, quality:int = 1, type:String = "inner", knockout:Boolean = false)
        {
            this.distance = distance;
            this.angle = angle;
            if (colors != null)
            {
                this.colors = colors;
            }
            if (alphas != null)
            {
                this.alphas = alphas;
            }
            if (ratios != null)
            {
                this.ratios = ratios;
            }
            this.blurX = blurX;
            this.blurY = blurY;
            this.quality = quality;
            this.strength = strength;
            this.type = type;
            this.knockout = knockout;
            return;
        }// end function

        public native function set colors(value:Array) : void;

        public native function get strength() : Number;

        public native function set blurX(value:Number) : void;

        public native function set blurY(value:Number) : void;

        public native function set angle(value:Number) : void;

        public native function get type() : String;

        public native function get ratios() : Array;

        public native function set strength(value:Number) : void;

        public native function set alphas(value:Array) : void;

        public native function get colors() : Array;

        public native function get blurX() : Number;

        public native function get blurY() : Number;

        public native function get angle() : Number;

        public native function set knockout(value:Boolean) : void;

        public native function get distance() : Number;

        public native function set ratios(value:Array) : void;

        public native function set distance(value:Number) : void;

        public native function get knockout() : Boolean;

        public native function set type(value:String) : void;

        public native function get alphas() : Array;

        override public function clone() : BitmapFilter
        {
            return new GradientBevelFilter(this.distance, this.angle, this.colors, this.alphas, this.ratios, this.blurX, this.blurY, this.strength, this.quality, this.type, this.knockout);
        }// end function

        public native function set quality(value:int) : void;

        public native function get quality() : int;

    }
}
