package flash.display
{
    import __AS3__.vec.*;
    import flash.geom.*;

    [native(cls="GraphicsClass", instance="GraphicsObject", methods="auto")]
    final public class Graphics extends Object
    {

        public function Graphics()
        {
            return;
        }// end function

        public native function drawTriangles(vertices:Vector.<Number>, indices:Vector.<int> = null, uvtData:Vector.<Number> = null, culling:String = "none") : void;

        public native function drawRect(x:Number, y:Number, width:Number, height:Number) : void;

        public native function drawPath(commands:Vector.<int>, data:Vector.<Number>, winding:String = "evenOdd") : void;

        public native function curveTo(controlX:Number, controlY:Number, anchorX:Number, anchorY:Number) : void;

        public native function beginFill(color:uint, alpha:Number = 1) : void;

        public native function clear() : void;

        public native function lineTo(x:Number, y:Number) : void;

        public native function beginShaderFill(shader:Shader, matrix:Matrix = null) : void;

        public native function lineGradientStyle(type:String, colors:Array, alphas:Array, ratios:Array, matrix:Matrix = null, spreadMethod:String = "pad", interpolationMethod:String = "rgb", focalPointRatio:Number = 0) : void;

        public native function beginBitmapFill(bitmap:BitmapData, matrix:Matrix = null, repeat:Boolean = true, smooth:Boolean = false) : void;

        public native function beginGradientFill(type:String, colors:Array, alphas:Array, ratios:Array, matrix:Matrix = null, spreadMethod:String = "pad", interpolationMethod:String = "rgb", focalPointRatio:Number = 0) : void;

        public native function lineStyle(thickness:Number , color:uint = 0, alpha:Number = 1, pixelHinting:Boolean = false, scaleMode:String = "normal", caps:String = null, joints:String = null, miterLimit:Number = 3) : void;

        private function beginStrokeObject(istroke:IGraphicsStroke) : void
        {
            var _loc_4:GraphicsSolidFill = null;
            var _loc_5:GraphicsGradientFill = null;
            var _loc_6:GraphicsBitmapFill = null;
            var _loc_7:GraphicsShaderFill = null;
            var _loc_2:GraphicsStroke = null;
            var _loc_3:IGraphicsFill = null;
            if (istroke != null)
            {
            }
            if (istroke is GraphicsStroke)
            {
                _loc_2 = istroke as GraphicsStroke;
            }
            if (_loc_2)
            {
            }
            if (_loc_2.fill)
            {
            }
            if (_loc_2.fill is IGraphicsFill)
            {
                _loc_3 = _loc_2.fill;
            }
            if (_loc_2 != null)
            {
            }
            if (_loc_3 == null)
            {
                this.lineStyle();
            }
            else if (_loc_3 is GraphicsSolidFill)
            {
                _loc_4 = _loc_3 as GraphicsSolidFill;
                this.lineStyle(_loc_2.thickness, _loc_4.color, _loc_4.alpha, _loc_2.pixelHinting, _loc_2.scaleMode, _loc_2.caps, _loc_2.joints, _loc_2.miterLimit);
            }
            else if (_loc_3 is GraphicsGradientFill)
            {
                _loc_5 = _loc_3 as GraphicsGradientFill;
                this.lineStyle(_loc_2.thickness, 0, 1, _loc_2.pixelHinting, _loc_2.scaleMode, _loc_2.caps, _loc_2.joints, _loc_2.miterLimit);
                this.lineGradientStyle(_loc_5.type, _loc_5.colors, _loc_5.alphas, _loc_5.ratios, _loc_5.matrix, _loc_5.spreadMethod, _loc_5.interpolationMethod, _loc_5.focalPointRatio);
            }
            else if (_loc_3 is GraphicsBitmapFill)
            {
                _loc_6 = _loc_3 as GraphicsBitmapFill;
                this.lineStyle(_loc_2.thickness, 0, 1, _loc_2.pixelHinting, _loc_2.scaleMode, _loc_2.caps, _loc_2.joints, _loc_2.miterLimit);
                this.lineBitmapStyle(_loc_6.bitmapData, _loc_6.matrix, _loc_6.repeat, _loc_6.smooth);
            }
            else if (_loc_3 is GraphicsShaderFill)
            {
                _loc_7 = _loc_3 as GraphicsShaderFill;
                this.lineStyle(_loc_2.thickness, 0, 1, _loc_2.pixelHinting, _loc_2.scaleMode, _loc_2.caps, _loc_2.joints, _loc_2.miterLimit);
                this.lineShaderStyle(_loc_7.shader, _loc_7.matrix);
            }
            return;
        }// end function

        public native function drawRoundRectComplex(x:Number, y:Number, width:Number, height:Number, topLeftRadius:Number, topRightRadius:Number, bottomLeftRadius:Number, bottomRightRadius:Number) : void;

        private function drawPathObject(path:IGraphicsPath) : void
        {
            var _loc_2:GraphicsPath = null;
            var _loc_3:GraphicsTrianglePath = null;
            if (path is GraphicsPath)
            {
                _loc_2 = path as GraphicsPath;
                this.drawPath(_loc_2.commands, _loc_2.data, _loc_2.winding);
            }
            else if (path is GraphicsTrianglePath)
            {
                _loc_3 = path as GraphicsTrianglePath;
                this.drawTriangles(_loc_3.vertices, _loc_3.indices, _loc_3.uvtData, _loc_3.culling);
            }
            return;
        }// end function

        private function beginFillObject(fill:IGraphicsFill) : void
        {
            var _loc_2:GraphicsSolidFill = null;
            var _loc_3:GraphicsGradientFill = null;
            var _loc_4:GraphicsBitmapFill = null;
            var _loc_5:GraphicsShaderFill = null;
            if (fill == null)
            {
                this.endFill();
            }
            else if (fill is GraphicsEndFill)
            {
                this.endFill();
            }
            else if (fill is GraphicsSolidFill)
            {
                _loc_2 = fill as GraphicsSolidFill;
                this.beginFill(_loc_2.color, _loc_2.alpha);
            }
            else if (fill is GraphicsGradientFill)
            {
                _loc_3 = fill as GraphicsGradientFill;
                this.beginGradientFill(_loc_3.type, _loc_3.colors, _loc_3.alphas, _loc_3.ratios, _loc_3.matrix, _loc_3.spreadMethod, _loc_3.interpolationMethod, _loc_3.focalPointRatio);
            }
            else if (fill is GraphicsBitmapFill)
            {
                _loc_4 = fill as GraphicsBitmapFill;
                this.beginBitmapFill(_loc_4.bitmapData, _loc_4.matrix, _loc_4.repeat, _loc_4.smooth);
            }
            else if (fill is GraphicsShaderFill)
            {
                _loc_5 = fill as GraphicsShaderFill;
                this.beginShaderFill(_loc_5.shader, _loc_5.matrix);
            }
            return;
        }// end function

        public native function moveTo(x:Number, y:Number) : void;

        public native function drawRoundRect(x:Number, y:Number, width:Number, height:Number, ellipseWidth:Number, ellipseHeight:Number ) : void;

        public function drawCircle(x:Number, y:Number, radius:Number) : void
        {
            this.drawRoundRect(x - radius, y - radius, radius * 2, radius * 2, radius * 2, radius * 2);
            return;
        }// end function

        public native function lineBitmapStyle(bitmap:BitmapData, matrix:Matrix = null, repeat:Boolean = true, smooth:Boolean = false) : void;

        public native function lineShaderStyle(shader:Shader, matrix:Matrix = null) : void;

        public function drawGraphicsData(graphicsData:Vector.<IGraphicsData>) : void
        {
            var _loc_3:IGraphicsData = null;
            var _loc_4:IGraphicsPath = null;
            var _loc_5:IGraphicsFill = null;
            var _loc_6:IGraphicsStroke = null;
            if (graphicsData == null)
            {
                return;
            }
            var _loc_2:int = 0;
            while (_loc_2 < graphicsData.length)
            {
                
                _loc_3 = graphicsData[_loc_2];
                if (_loc_3 is IGraphicsPath)
                {
                    _loc_4 = _loc_3 as IGraphicsPath;
                    this.drawPathObject(_loc_4);
                }
                else if (_loc_3 is IGraphicsFill)
                {
                    _loc_5 = _loc_3 as IGraphicsFill;
                    this.beginFillObject(_loc_5);
                }
                else if (_loc_3 is IGraphicsStroke)
                {
                    _loc_6 = _loc_3 as IGraphicsStroke;
                    this.beginStrokeObject(_loc_6);
                }
                _loc_2 = _loc_2 + 1;
            }
            return;
        }// end function

        public function drawEllipse(x:Number, y:Number, width:Number, height:Number) : void
        {
            this.drawRoundRect(x, y, width, height, width, height);
            return;
        }// end function

        public native function endFill() : void;

        public native function copyFrom(sourceGraphics:Graphics) : void;

    }
}
