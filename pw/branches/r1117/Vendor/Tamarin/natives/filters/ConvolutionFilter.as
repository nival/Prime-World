package flash.filters
{

    [native(cls="ConvolutionFilterClass", instance="ConvolutionFilterObject", methods="auto")]
    public class ConvolutionFilter extends BitmapFilter
    {

        public function ConvolutionFilter(matrixX:Number = 0, matrixY:Number = 0, matrix:Array = null, divisor:Number = 1, bias:Number = 0, preserveAlpha:Boolean = true, clamp:Boolean = true, color:uint = 0, alpha:Number = 0)
        {
            this.matrixX = matrixX;
            this.matrixY = matrixY;
            if (matrix != null)
            {
                this.matrix = matrix;
            }
            this.divisor = divisor;
            this.bias = bias;
            this.preserveAlpha = preserveAlpha;
            this.clamp = clamp;
            this.color = color;
            this.alpha = alpha;
            return;
        }// end function

        public native function get matrix() : Array;

        public native function set matrix(value:Array) : void;

        public native function get color() : uint;

        public native function set preserveAlpha(value:Boolean) : void;

        public native function get alpha() : Number;

        public native function set color(value:uint) : void;

        public native function set bias(value:Number) : void;

        public native function set alpha(value:Number) : void;

        public native function set matrixX(value:Number) : void;

        public native function set matrixY(value:Number) : void;

        public native function get preserveAlpha() : Boolean;

        public native function set clamp(value:Boolean) : void;

        public native function get matrixX() : Number;

        public native function get matrixY() : Number;

        public native function get bias() : Number;

        public native function get clamp() : Boolean;

        public native function set divisor(value:Number) : void;

        override public function clone() : BitmapFilter
        {
            return new ConvolutionFilter(this.matrixX, this.matrixY, this.matrix, this.divisor, this.bias, this.preserveAlpha, this.clamp, this.color, this.alpha);
        }// end function

        public native function get divisor() : Number;

    }
}
