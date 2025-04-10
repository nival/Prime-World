package flash.events
{
    import flash.display.*;

    public class FocusEvent extends Event
    {
        private var m_isRelatedObjectInaccessible:Boolean;
        private var m_shiftKey:Boolean;
        private var m_relatedObject:InteractiveObject;
        private var m_keyCode:uint;
        public static const MOUSE_FOCUS_CHANGE:String = "mouseFocusChange";
        public static const FOCUS_OUT:String = "focusOut";
        public static const KEY_FOCUS_CHANGE:String = "keyFocusChange";
        public static const FOCUS_IN:String = "focusIn";

        public function FocusEvent(type:String, bubbles:Boolean = true, cancelable:Boolean = false, relatedObject:InteractiveObject = null, shiftKey:Boolean = false, keyCode:uint = 0)
        {
            super(type, bubbles, cancelable);
            this.m_relatedObject = relatedObject;
            this.m_shiftKey = shiftKey;
            this.m_keyCode = keyCode;
            return;
        }// end function

        public function set shiftKey(value:Boolean) : void
        {
            this.m_shiftKey = value;
            return;
        }// end function

        public function get isRelatedObjectInaccessible() : Boolean
        {
            return this.m_isRelatedObjectInaccessible;
        }// end function

        public function get shiftKey() : Boolean
        {
            return this.m_shiftKey;
        }// end function

        public function get relatedObject() : InteractiveObject
        {
            return this.m_relatedObject;
        }// end function

        override public function toString() : String
        {
            return formatToString("FocusEvent", "type", "bubbles", "cancelable", "eventPhase", "relatedObject", "shiftKey", "keyCode");
        }// end function

        public function get keyCode() : uint
        {
            return this.m_keyCode;
        }// end function

        public function set isRelatedObjectInaccessible(value:Boolean) : void
        {
            this.m_isRelatedObjectInaccessible = value;
            return;
        }// end function

        public function set relatedObject(value:InteractiveObject) : void
        {
            this.m_relatedObject = value;
            return;
        }// end function

        override public function clone() : Event
        {
            return new FocusEvent(type, bubbles, cancelable, this.m_relatedObject, this.m_shiftKey, this.m_keyCode);
        }// end function

        public function set keyCode(value:uint) : void
        {
            this.m_keyCode = value;
            return;
        }// end function

    }
}
