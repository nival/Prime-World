package flash.geom
{
    import __AS3__.vec.*;

    [native(cls="Matrix3DClass", instance="Matrix3DObject", methods="auto")]
    public class Matrix3D extends Object
    {

        public function Matrix3D(v:Vector.<Number> = null);

        public native function transpose() : void;

        public native function prependTranslation(x:Number, y:Number, z:Number) : void;

        public native function set rawData(v:Vector.<Number>) : void;

        public native function deltaTransformVector(v:Vector3D) : Vector3D;

        public native function get position() : Vector3D;

        public native function pointAt(pos:Vector3D, at:Vector3D = null, up:Vector3D = null) : void;

        public native function transformVectors(vin:Vector.<Number>, vout:Vector.<Number>) : void;

        public native function prependRotation(degrees:Number, axis:Vector3D, pivotPoint:Vector3D = null) : void;

        public native function prepend(rhs:Matrix3D) : void;

        public native function transformVector(v:Vector3D) : Vector3D;

        public native function appendScale(xScale:Number, yScale:Number, zScale:Number) : void;

        public native function decompose(orientationStyle:String = "eulerAngles") : Vector.<Vector3D>;

        public native function get rawData() : Vector.<Number>;

        public native function interpolateTo(toMat:Matrix3D, percent:Number) : void;

        public native function get determinant() : Number;

        public native function invert() : Boolean;

        public native function appendTranslation(x:Number, y:Number, z:Number) : void;

        public native function appendRotation(degrees:Number, axis:Vector3D, pivotPoint:Vector3D = null) : void;

        public native function set position(pos:Vector3D) : void;

        public native function append(lhs:Matrix3D) : void;

        public native function prependScale(xScale:Number, yScale:Number, zScale:Number) : void;

        public function clone() : Matrix3D
        {
            return new Matrix3D(this.rawData);
        }// end function

        public native function identity() : void;

        public native function recompose(components:Vector.<Vector3D>, orientationStyle:String = "eulerAngles") : Boolean;

        public static native function interpolate(thisMat:Matrix3D, toMat:Matrix3D, percent:Number) : Matrix3D;

    }
}
