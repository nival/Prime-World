package flash.text
{
    import flash.events.*;

    [native(cls="StyleSheetClass", instance="StyleSheetObject", methods="auto")]
    dynamic public class StyleSheet extends EventDispatcher
    {
        private var _css:Object;

        public function StyleSheet()
        {
            this._css = {};
            this._styles = {};
            return;
        }// end function

        private native function _update() : void;

        private native function get _styles() : Object;

        private native function set _styles(styles:Object) : void;

        private native function _parseCSSFontFamily(fontFamily:String) : String;

        public function transform(formatObject:Object) : TextFormat
        {
            if (formatObject == null)
            {
                return null;
            }
            var _loc_2:* = new TextFormat();
            var _loc_3:* = formatObject.textAlign;
            if (_loc_3)
            {
                _loc_2.align = _loc_3;
            }
            _loc_3 = formatObject.fontSize;
            if (_loc_3)
            {
                _loc_3 = parseInt(_loc_3);
                if (_loc_3 > 0)
                {
                    _loc_2.size = _loc_3;
                }
            }
            _loc_3 = formatObject.textDecoration;
            if (_loc_3 == "none")
            {
                _loc_2.underline = false;
            }
            else if (_loc_3 == "underline")
            {
                _loc_2.underline = true;
            }
            _loc_3 = formatObject.marginLeft;
            if (_loc_3)
            {
                _loc_2.leftMargin = parseInt(_loc_3);
            }
            _loc_3 = formatObject.marginRight;
            if (_loc_3)
            {
                _loc_2.rightMargin = parseInt(_loc_3);
            }
            _loc_3 = formatObject.leading;
            if (_loc_3)
            {
                _loc_2.leading = parseInt(_loc_3);
            }
            _loc_3 = formatObject.kerning;
            if (_loc_3 == "true")
            {
                _loc_2.kerning = 1;
            }
            else if (_loc_3 == "false")
            {
                _loc_2.kerning = 0;
            }
            else
            {
                _loc_2.kerning = parseInt(_loc_3);
            }
            _loc_3 = formatObject.letterSpacing;
            if (_loc_3)
            {
                _loc_2.letterSpacing = parseFloat(_loc_3);
            }
            _loc_3 = formatObject.fontFamily;
            if (_loc_3)
            {
                _loc_2.font = this._parseCSSFontFamily(_loc_3);
            }
            _loc_3 = formatObject.display;
            if (_loc_3)
            {
                _loc_2.display = _loc_3;
            }
            _loc_3 = formatObject.fontWeight;
            if (_loc_3 == "bold")
            {
                _loc_2.bold = true;
            }
            else if (_loc_3 == "normal")
            {
                _loc_2.bold = false;
            }
            _loc_3 = formatObject.fontStyle;
            if (_loc_3 == "italic")
            {
                _loc_2.italic = true;
            }
            else if (_loc_3 == "normal")
            {
                _loc_2.italic = false;
            }
            _loc_3 = formatObject.textIndent;
            if (_loc_3)
            {
                _loc_2.indent = parseInt(_loc_3);
            }
            _loc_3 = formatObject.color;
            if (_loc_3)
            {
                _loc_3 = this._parseColor(_loc_3);
                if (_loc_3 != null)
                {
                    _loc_2.color = _loc_3;
                }
            }
            return _loc_2;
        }// end function

        public function clear() : void
        {
            this._css = {};
            this._styles = {};
            this._update();
            return;
        }// end function

        private native function _parseCSSInternal(cssText:String) : Object;

        public function setStyle(styleName:String, styleObject:Object) : void
        {
            var _loc_3:* = styleName.toLowerCase();
            this._css[_loc_3] = this._copy(styleObject);
            this.doTransform(_loc_3);
            this._update();
            return;
        }// end function

        public function parseCSS(CSSText:String) : void
        {
            var _loc_3:String = null;
            var _loc_2:* = this._parseCSSInternal(CSSText);
            if (typeof(_loc_2) == "null")
            {
                return;
            }
            for (_loc_3 in _loc_2)
            {
                
                this._css[_loc_3] = this._copy(_loc_2[_loc_3]);
                this.doTransform(_loc_3);
            }
            this._update();
            return;
        }// end function

        private function _copy(o:Object) : Object
        {
            var _loc_3:Object = null;
            if (typeof(o) != "object")
            {
                return null;
            }
            var _loc_2:Object = {};
            for (_loc_3 in o)
            {
                
                _loc_2[_loc_3] = o[_loc_3];
            }
            return _loc_2;
        }// end function

        private native function _parseColor(color:String) : uint;

        public function get styleNames() : Array
        {
            var _loc_2:Object = null;
            var _loc_1:Array = [];
            for (_loc_2 in this._css)
            {
                
                _loc_1.push(_loc_2);
            }
            return _loc_1;
        }// end function

        private function doTransform(n:String) : void
        {
            var _loc_2:* = this.transform(this._css[n]);
            this._styles[n] = _loc_2;
            return;
        }// end function

        public function getStyle(styleName:String) : Object
        {
            return this._copy(this._css[styleName.toLowerCase()]);
        }// end function

    }
}
