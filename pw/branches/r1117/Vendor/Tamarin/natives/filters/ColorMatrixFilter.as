package flash.filters
{

    [native(cls="ColorMatrixFilterClass", instance="ColorMatrixFilterObject", methods="auto")]
    final public class ColorMatrixFilter extends BitmapFilter
    {

        public function ColorMatrixFilter(matrix:Array = null)
        {
            if (matrix != null)
            {
                this.matrix = matrix;
            }
            return;
        }// end function

        public native function get matrix() : Array;

        public native function set matrix(value:Array) : void;

        override public function clone() : BitmapFilter
        {
            return new ColorMatrixFilter(this.matrix);
        }// end function

    }
}
