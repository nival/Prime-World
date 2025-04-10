package flash.geom
{
    import flash.display.*;

    [native(cls="TransformClass", instance="TransformObject", methods="auto")]
    public class Transform extends Object
    {

	//was DisplayObject [139] SimonK recheck it
        public function Transform(displayObject:Object);

        public native function get matrix() : Matrix;

        public native function set matrix(value:Matrix) : void;

        public native function set matrix3D(m:Matrix3D);

        public native function get colorTransform() : ColorTransform;

        public native function get perspectiveProjection() : PerspectiveProjection;

        public native function get concatenatedMatrix() : Matrix;

        public native function get matrix3D() : Matrix3D;

	//was DisplayObject [139] SimonK recheck it
	public native function getRelativeMatrix3D(relativeTo:Object) : Matrix3D;

        public native function set perspectiveProjection(pm:PerspectiveProjection) : void;

        public native function get concatenatedColorTransform() : ColorTransform;

        public native function set colorTransform(value:ColorTransform) : void;

        public native function get pixelBounds() : Rectangle;

    }
}
