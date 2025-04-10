package flash.ui
{
    import flash.events.*;

    [native(cls="ContextMenuItemClass", instance="ContextMenuItemObject", methods="auto")]
    final public class ContextMenuItem extends EventDispatcher
    {

        public function ContextMenuItem(caption:String, separatorBefore:Boolean = false, enabled:Boolean = true, visible:Boolean = true)
        {
            this.caption = caption;
            this.separatorBefore = separatorBefore;
            this.enabled = enabled;
            this.visible = visible;
            return;
        }// end function

        public native function get enabled() : Boolean;

        public native function set enabled(value:Boolean) : void;

        public native function get separatorBefore() : Boolean;

        public native function get caption() : String;

        public native function set separatorBefore(value:Boolean) : void;

        public native function get visible() : Boolean;

        public native function set visible(value:Boolean) : void;

        public native function set caption(value:String) : void;

        public function clone() : ContextMenuItem
        {
            var _loc_1:* = new ContextMenuItem(this.caption, this.separatorBefore, this.enabled, this.visible);
            return _loc_1;
        }// end function

    }
}
