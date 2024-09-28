package flash.display
{

    final public class GraphicsSolidFill extends Object implements IGraphicsFill, IGraphicsData
    {
        public var color:uint = 0;
        public var alpha:Number = 1;

        public function GraphicsSolidFill(color:uint = 0, alpha:Number = 1)
        {
            this.color = color;
            this.alpha = alpha;
            return;
        }// end function

    }
}
