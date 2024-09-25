package flash.text.engine
{
    import __AS3__.vec.*;
    import flash.display.*;
    import flash.events.*;
    import flash.geom.*;
    import flash.ui.*;

    [native(cls="TextLineClass", instance="TextLineObject", methods="auto")]
    final public class TextLine extends DisplayObjectContainer
    {
        public var userData:Object;
        public static const MAX_LINE_WIDTH:int = 1000000;

        public function TextLine()
        {
            return;
        }// end function

        public native function get mirrorRegions() : Vector.<TextLineMirrorRegion>;

        public native function get descent() : Number;

        public native function getAtomGraphic(atomIndex:int) : DisplayObject;

        public native function getBaselinePosition(baseline:String) : Number;

        public native function get nextLine() : TextLine;

        public function getMirrorRegion(mirror:EventDispatcher) : TextLineMirrorRegion
        {
            var _loc_4:TextLineMirrorRegion = null;
            var _loc_2:* = this.mirrorRegions;
            var _loc_3:int = 0;
            while (_loc_3 < _loc_2.length)
            {
                
                _loc_4 = _loc_2[_loc_3];
                if (_loc_4.mirror == mirror)
                {
                    return _loc_4;
                }
                _loc_3 = _loc_3 + 1;
            }
            return null;
        }// end function

        public native function get previousLine() : TextLine;

        public native function dump() : String;

        private native function doGetAtomIndexAtPoint(x:Number, y:Number) : int;

        public native function getAtomBidiLevel(atomIndex:int) : int;

        public function getAtomIndexAtPoint(stageX:Number, stageY:Number) : int
        {
            var _loc_3:* = new Point(stageX, stageY);
            var _loc_4:* = this.globalToLocal(_loc_3);
            return this.doGetAtomIndexAtPoint(_loc_4.x, _loc_4.y);
        }// end function

        public native function get unjustifiedTextWidth() : Number;

        override public function set tabEnabled(enabled:Boolean) : void
        {
            Error.throwError(IllegalOperationError, 2181);
            return;
        }// end function

        public native function get textWidth() : Number;

        public native function get ascent() : Number;

        override public function set contextMenu(cm:ContextMenu) : void
        {
            Error.throwError(IllegalOperationError, 2181);
            return;
        }// end function

        public function getAtomIndexAtCharIndex(charIndex:int) : int
        {
            var _loc_4:int = 0;
            var _loc_5:int = 0;
            var _loc_2:int = -1;
            var _loc_3:int = 0;
            while (_loc_3 < this.atomCount)
            {
                
                _loc_4 = this.getAtomTextBlockBeginIndex(_loc_3);
                _loc_5 = this.getAtomTextBlockEndIndex(_loc_3);
                if (_loc_4 <= charIndex)
                {
                }
                if (_loc_5 > charIndex)
                {
                    _loc_2 = _loc_3;
                    break;
                }
                _loc_3 = _loc_3 + 1;
            }
            return _loc_2;
        }// end function

        public native function get textBlock() : TextBlock;

        public native function getAtomWordBoundaryOnLeft(atomIndex:int) : Boolean;

        public native function getAtomTextBlockBeginIndex(atomIndex:int) : int;

        public native function getAtomBounds(atomIndex:int) : Rectangle;

        public native function set validity(value:String) : void;

        override public function set tabChildren(enable:Boolean) : void
        {
            Error.throwError(IllegalOperationError, 2181);
            return;
        }// end function

        public native function get textBlockBeginIndex() : int;

        public native function get hasGraphicElement() : Boolean;

        public native function getAtomTextBlockEndIndex(atomIndex:int) : int;

        public native function get validity() : String;

        public native function get textHeight() : Number;

        public native function get specifiedWidth() : Number;

        override public function set focusRect(focusRect:Object) : void
        {
            Error.throwError(IllegalOperationError, 2181);
            return;
        }// end function

        public native function getAtomTextRotation(atomIndex:int) : String;

        override public function set tabIndex(index:int) : void
        {
            Error.throwError(IllegalOperationError, 2181);
            return;
        }// end function

        public native function get rawTextLength() : int;

        public native function getAtomCenter(atomIndex:int) : Number;

        public native function get atomCount() : int;

        public native function flushAtomData() : void;

    }
}
