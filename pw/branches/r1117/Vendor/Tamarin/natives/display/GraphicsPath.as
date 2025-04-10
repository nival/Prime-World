package flash.display
{
    import __AS3__.vec.*;

    final public class GraphicsPath extends Object implements IGraphicsPath, IGraphicsData
    {
        public var commands:Vector.<int>;
        public var data:Vector.<Number>;
        private var _winding:String;

        public function GraphicsPath(commands:Vector.<int> = null, data:Vector.<Number> = null, winding:String = "evenOdd")
        {
            this.commands = commands;
            this.data = data;
            if (winding != GraphicsPathWinding.EVEN_ODD)
            {
            }
            if (winding != GraphicsPathWinding.NON_ZERO)
            {
                Error.throwError(ArgumentError, 2008, "winding");
            }
            this._winding = winding;
            return;
        }// end function

        public function wideLineTo(x:Number, y:Number) : void
        {
            if (this.commands == null)
            {
                this.commands = new Vector.<int>;
            }
            if (this.data == null)
            {
                this.data = new Vector.<Number>;
            }
            this.commands.push(GraphicsPathCommand.WIDE_LINE_TO);
            this.data.push(0, 0, x, y);
            return;
        }// end function

        public function set winding(value:String)
        {
            if (value != GraphicsPathWinding.EVEN_ODD)
            {
            }
            if (value != GraphicsPathWinding.NON_ZERO)
            {
                Error.throwError(ArgumentError, 2008, "winding");
            }
            this._winding = value;
            return;
        }// end function

        public function moveTo(x:Number, y:Number) : void
        {
            if (this.commands == null)
            {
                this.commands = new Vector.<int>;
            }
            if (this.data == null)
            {
                this.data = new Vector.<Number>;
            }
            this.commands.push(GraphicsPathCommand.MOVE_TO);
            this.data.push(x, y);
            return;
        }// end function

        public function lineTo(x:Number, y:Number) : void
        {
            if (this.commands == null)
            {
                this.commands = new Vector.<int>;
            }
            if (this.data == null)
            {
                this.data = new Vector.<Number>;
            }
            this.commands.push(GraphicsPathCommand.LINE_TO);
            this.data.push(x, y);
            return;
        }// end function

        public function curveTo(controlX:Number, controlY:Number, anchorX:Number, anchorY:Number) : void
        {
            if (this.commands == null)
            {
                this.commands = new Vector.<int>;
            }
            if (this.data == null)
            {
                this.data = new Vector.<Number>;
            }
            this.commands.push(GraphicsPathCommand.CURVE_TO);
            this.data.push(controlX, controlY, anchorX, anchorY);
            return;
        }// end function

        public function get winding() : String
        {
            return this._winding;
        }// end function

        public function wideMoveTo(x:Number, y:Number) : void
        {
            if (this.commands == null)
            {
                this.commands = new Vector.<int>;
            }
            if (this.data == null)
            {
                this.data = new Vector.<Number>;
            }
            this.commands.push(GraphicsPathCommand.WIDE_MOVE_TO);
            this.data.push(0, 0, x, y);
            return;
        }// end function

    }
}
