package flash.geom
{

    [native(cls="PerspectiveProjectionClass", instance="PerspectiveProjectionObject", methods="auto")]
    public class PerspectiveProjection extends Object
    {

        public function PerspectiveProjection();

        public native function get projectionCenter() : Point;

        public native function toMatrix3D() : Matrix3D;

        public native function get fieldOfView() : Number;

        public native function set projectionCenter(p:Point);

        public native function get focalLength() : Number;

        public native function set fieldOfView(fieldOfViewAngleInDegrees:Number) : void;

        public native function set focalLength(value:Number) : void;

    }
}
