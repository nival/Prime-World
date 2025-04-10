package flash.display
{
    import __AS3__.vec.*;

    final public class GraphicsTrianglePath extends Object implements IGraphicsPath, IGraphicsData
    {
        private var _culling:String;
        public var indices:Vector.<int>;
        public var vertices:Vector.<Number>;
        public var uvtData:Vector.<Number>;

        public function GraphicsTrianglePath(vertices:Vector.<Number> = null, indices:Vector.<int> = null, uvtData:Vector.<Number> = null, culling:String = "none")
        {
            this.vertices = vertices;
            this.indices = indices;
            this.uvtData = uvtData;
            this._culling = culling;
            if (culling != TriangleCulling.NONE)
            {
            }
            if (culling != TriangleCulling.POSITIVE)
            {
            }
            if (culling != TriangleCulling.NEGATIVE)
            {
                Error.throwError(ArgumentError, 2008, "culling");
            }
            return;
        }// end function

        public function get culling() : String
        {
            return this._culling;
        }// end function

        public function set culling(value:String) : void
        {
            if (value != TriangleCulling.NONE)
            {
            }
            if (value != TriangleCulling.POSITIVE)
            {
            }
            if (value != TriangleCulling.NEGATIVE)
            {
                Error.throwError(ArgumentError, 2008, "culling");
            }
            this._culling = value;
            return;
        }// end function

    }
}
