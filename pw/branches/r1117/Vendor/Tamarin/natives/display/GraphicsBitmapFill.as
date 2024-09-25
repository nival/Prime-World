package flash.display
{
    import flash.geom.*;

    final public class GraphicsBitmapFill extends Object implements IGraphicsFill, IGraphicsData
    {
        public var matrix:Matrix;
        public var bitmapData:BitmapData;
        public var repeat:Boolean;
        public var smooth:Boolean;

        public function GraphicsBitmapFill(bitmapData:BitmapData = null, matrix:Matrix = null, repeat:Boolean = true, smooth:Boolean = false)
        {
            this.bitmapData = bitmapData;
            this.matrix = matrix;
            this.repeat = repeat;
            this.smooth = smooth;
            return;
        }// end function

    }
}
