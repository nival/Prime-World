package flash.ui
{

    final public class ContextMenuClipboardItems extends Object
    {
        public var cut:Boolean = false;
        public var paste:Boolean = false;
        public var copy:Boolean = false;
        public var selectAll:Boolean = true;
        public var clear:Boolean = false;

        public function ContextMenuClipboardItems()
        {
            return;
        }// end function

        public function clone() : ContextMenuClipboardItems
        {
            var _loc_1:* = new ContextMenuClipboardItems();
            _loc_1.cut = this.cut;
            _loc_1.copy = this.copy;
            _loc_1.paste = this.paste;
            _loc_1.clear = this.clear;
            _loc_1.selectAll = this.selectAll;
            return _loc_1;
        }// end function

    }
}
