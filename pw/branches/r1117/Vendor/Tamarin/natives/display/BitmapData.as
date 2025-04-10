package flash.display
{
    import __AS3__.vec.*;
    import flash.filters.*;
    import flash.geom.*;
    import flash.utils.*;

    [native(cls="BitmapDataClass", instance="BitmapDataObject", methods="auto")]
    public class BitmapData extends Object implements IBitmapDrawable
    {
        public function BitmapData(width:int, height:int, transparent:Boolean = true, fillColor:uint = 1 /*4294970000*/)
        {
          _Init( width, height, transparent, fillColor );
        }

        private native function _Init(width:int, height:int, transparent:Boolean, fillColor:uint) : void;

        public native function copyPixels(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, alphaBitmapData:BitmapData = null, alphaPoint:Point = null, mergeAlpha:Boolean = false) : void;

        public native function setPixel(x:int, y:int, color:uint) : void;

        public native function hitTest(firstPoint:Point, firstAlphaThreshold:uint, secondObject:Object, secondBitmapDataPoint:Point = null, secondAlphaThreshold:uint = 1) : Boolean;

        public native function applyFilter(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, filter:BitmapFilter) : void;

        public native function fillRect(rect:Rectangle, color:uint) : void;

        public native function colorTransform(rect:Rectangle, colorTransform:ColorTransform) : void;

        public native function draw(source:IBitmapDrawable, matrix:Matrix = null, colorTransform:ColorTransform = null, blendMode:String = null, clipRect:Rectangle = null, smoothing:Boolean = false) : void;

        public function setVector(rect:Rectangle, inputVector:Vector.<uint>) : void
        {
            var _loc_3:* = this.rect;
            if (rect == null)
            {
                Error.throwError(TypeError, 2007, "rect");
            }
            if (inputVector == null)
            {
                Error.throwError(TypeError, 2007, "inputVector");
            }
            var _loc_4:* = _loc_3.intersection(rect);
            var _loc_5:* = _loc_4.width;
            var _loc_6:* = _loc_4.height;
            if (_loc_5 * _loc_6 > inputVector.length)
            {
                Error.throwError(RangeError, 1125, _loc_5 * _loc_6 - 1, inputVector.length);
            }
            this._setVector(inputVector, _loc_4.x, _loc_4.y, _loc_4.width, _loc_4.height);
            return;
        }// end function

        public native function get width() : int;

        public native function copyChannel(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, sourceChannel:uint, destChannel:uint) : void;

        public native function getPixel(x:int, y:int) : uint;

        public native function generateFilterRect(sourceRect:Rectangle, filter:BitmapFilter) : Rectangle;

        public native function get transparent() : Boolean;

        public native function unlock(changeRect:Rectangle = null) : void;

        public native function scroll(x:int, y:int) : void;

        public native function getColorBoundsRect(mask:uint, color:uint, findColor:Boolean = true) : Rectangle;

        public native function pixelDissolve(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, randomSeed:int = 0, numPixels:int = 0, fillColor:uint = 0) : int;

        public native function noise(randomSeed:int, low:uint = 0, high:uint = 255, channelOptions:uint = 7, grayScale:Boolean = false) : void;

        public native function clone() : BitmapData;

        private native function _setVector(inputVector:Vector.<uint>, x:int, y:int, width:int, height:int) : void;

        public native function dispose() : void;

        public native function floodFill(x:int, y:int, color:uint) : void;

        public native function setPixel32(x:int, y:int, color:uint) : void;

        public function get rect() : Rectangle
        {
            return new Rectangle(0, 0, this.width, this.height);
        }// end function

        public native function compare(otherBitmapData:BitmapData) : Object;

        public native function perlinNoise(baseX:Number, baseY:Number, numOctaves:uint, randomSeed:int, stitch:Boolean, fractalNoise:Boolean, channelOptions:uint = 7, grayScale:Boolean = false, offsets:Array = null) : void;

        public native function get height() : int;

        public native function paletteMap(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, redArray:Array = null, greenArray:Array = null, blueArray:Array = null, alphaArray:Array = null) : void;

        public native function getPixels(rect:Rectangle) : ByteArray;

        public native function threshold(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, operation:String, threshold:uint, color:uint = 0, mask:uint = 1/*4294970000*/, copySource:Boolean = false) : uint;

        public native function getPixel32(x:int, y:int) : uint;

        public native function lock() : void;

        public native function setPixels(rect:Rectangle, inputByteArray:ByteArray) : void;

        public native function merge(sourceBitmapData:BitmapData, sourceRect:Rectangle, destPoint:Point, redMultiplier:uint, greenMultiplier:uint, blueMultiplier:uint, alphaMultiplier:uint) : void;

        public function getVector(rect:Rectangle) : Vector.<uint>
        {
            var _loc_2:* = this.rect;
            if (rect == null)
            {
                Error.throwError(TypeError, 2007, "rect");
            }
            var _loc_3:* = _loc_2.intersection(rect);
            var _loc_4:* = _loc_3.width;
            var _loc_5:* = _loc_3.height;
            var _loc_6:* = new Vector.<uint>(_loc_4 * _loc_5);
            this._getVector(_loc_6, _loc_3.x, _loc_3.y, _loc_3.width, _loc_3.height);
            return _loc_6;
        }// end function

        private native function _getVector(v:Vector.<uint>, x:int, y:int, width:int, height:int);

        public native function histogram(hRect:Rectangle = null) : Vector.<Vector.<Number>>;

    }
}
