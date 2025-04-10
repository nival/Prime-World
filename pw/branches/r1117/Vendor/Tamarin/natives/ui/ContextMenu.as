package flash.ui
{
    import flash.events.*;
    import flash.net.*;

    [native(cls="ContextMenuClass", instance="ContextMenuObject", methods="auto")]
    final public class ContextMenu extends EventDispatcher
    {

        public function ContextMenu()
        {
            this.builtInItems = new ContextMenuBuiltInItems();
            this.customItems = new Array();
            this.initLinkAndClipboardProperties();
            return;
        }// end function

        public native function set builtInItems(value:ContextMenuBuiltInItems) : void;

        public native function get builtInItems() : ContextMenuBuiltInItems;

        private native function cloneLinkAndClipboardProperties(c:ContextMenu) : void;

        public native function get clipboardItems() : ContextMenuClipboardItems;

        public native function get customItems() : Array;

        public native function set clipboardMenu(value:Boolean) : void;

        public native function set link(value:URLRequest) : void;

        public native function get clipboardMenu() : Boolean;

        public native function get link() : URLRequest;

        public native function set clipboardItems(value:ContextMenuClipboardItems) : void;

        private native function initLinkAndClipboardProperties() : void;

        public function clone() : ContextMenu
        {
            var _loc_1:* = new ContextMenu();
            _loc_1.builtInItems = this.builtInItems.clone();
            this.cloneLinkAndClipboardProperties(_loc_1);
            var _loc_2:int = 0;
            while (_loc_2 < this.customItems.length)
            {
                
                _loc_1.customItems.push(this.customItems[_loc_2].clone());
                _loc_2 = _loc_2 + 1;
            }
            return _loc_1;
        }// end function

        public native function set customItems(value:Array) : void;

        public function hideBuiltInItems() : void
        {
            this.builtInItems.save = false;
            this.builtInItems.zoom = false;
            this.builtInItems.quality = false;
            this.builtInItems.play = false;
            this.builtInItems.loop = false;
            this.builtInItems.rewind = false;
            this.builtInItems.forwardAndBack = false;
            this.builtInItems.print = false;
            return;
        }// end function

    }
}
