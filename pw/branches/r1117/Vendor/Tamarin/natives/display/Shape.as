package flash.display
{

    [native(cls="ShapeClass", instance="ShapeObject", methods="auto")]
    public class Shape extends DisplayObject
    {

        public function Shape();

        public native function get graphics() : Graphics;

    }
}
