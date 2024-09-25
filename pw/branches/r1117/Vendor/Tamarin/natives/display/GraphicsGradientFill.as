package flash.display
{
    import flash.geom.*;

    final public class GraphicsGradientFill extends Object implements IGraphicsFill, IGraphicsData
    {
        public var matrix:Matrix;
        public var focalPointRatio:Number;
        public var ratios:Array;
        private var _spreadMethod:String;
        private var _interpolationMethod:String;
        public var colors:Array;
        public var alphas:Array;
        private var _type:String;

        public function GraphicsGradientFill(type:String = "linear", colors:Array = null, alphas:Array = null, ratios:Array = null, matrix = null, spreadMethod = "pad", interpolationMethod:String = "rgb", focalPointRatio:Number = 0)
        {
            this._type = type;
            this.colors = colors;
            this.alphas = alphas;
            this.ratios = ratios;
            this.matrix = matrix;
            this._spreadMethod = spreadMethod;
            this._interpolationMethod = interpolationMethod;
            this.focalPointRatio = focalPointRatio;
            if (this._type != GradientType.LINEAR)
            {
            }
            if (this._type != GradientType.RADIAL)
            {
                Error.throwError(ArgumentError, 2008, "type");
            }
            if (this._spreadMethod != "none")
            {
            }
            if (this._spreadMethod != SpreadMethod.PAD)
            {
            }
            if (this._spreadMethod != SpreadMethod.REFLECT)
            {
            }
            if (this._spreadMethod != SpreadMethod.REPEAT)
            {
                Error.throwError(ArgumentError, 2008, "spreadMethod");
            }
            if (this._interpolationMethod != InterpolationMethod.LINEAR_RGB)
            {
            }
            if (this._interpolationMethod != InterpolationMethod.RGB)
            {
                Error.throwError(ArgumentError, 2008, "interpolationMethod");
            }
            return;
        }// end function

        public function get interpolationMethod() : String
        {
            return this._interpolationMethod;
        }// end function

        public function set spreadMethod(value:String)
        {
            if (value != "none")
            {
            }
            if (value != SpreadMethod.PAD)
            {
            }
            if (value != SpreadMethod.REFLECT)
            {
            }
            if (value != SpreadMethod.REPEAT)
            {
                Error.throwError(ArgumentError, 2008, "spreadMethod");
            }
            this._spreadMethod = value;
            return;
        }// end function

        public function set interpolationMethod(value:String)
        {
            if (value != InterpolationMethod.LINEAR_RGB)
            {
            }
            if (value != InterpolationMethod.RGB)
            {
                Error.throwError(ArgumentError, 2008, "interpolationMethod");
            }
            this._interpolationMethod = value;
            return;
        }// end function

        public function set type(value:String)
        {
            if (value != GradientType.LINEAR)
            {
            }
            if (value != GradientType.RADIAL)
            {
                Error.throwError(ArgumentError, 2008, "type");
            }
            this._type = value;
            return;
        }// end function

        public function get type() : String
        {
            return this._type;
        }// end function

        public function get spreadMethod() : String
        {
            return this._spreadMethod;
        }// end function

    }
}
