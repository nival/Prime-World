package flash.events
{

    [native(cls="KeyboardEventClass", instance="KeyboardEventObject", methods="auto")]
    public class KeyboardEvent extends Event
    {
        private var m_altKey:Boolean;
        private var m_shiftKey:Boolean;
        private var m_keyCode:uint;
        private var m_keyLocation:uint;
        private var m_ctrlKey:Boolean;
        private var m_charCode:uint;
        public static const KEY_DOWN:String = "keyDown";
        public static const KEY_UP:String = "keyUp";

        public function KeyboardEvent(type:String, bubbles:Boolean = true, cancelable:Boolean = false, charCode:uint = 0, keyCode:uint = 0, keyLocation:uint = 0, ctrlKey:Boolean = false, altKey:Boolean = false, shiftKey:Boolean = false)
        {
            super(type, bubbles, cancelable);
            this.m_charCode = charCode;
            this.m_keyCode = keyCode;
            this.m_keyLocation = keyLocation;
            this.m_ctrlKey = ctrlKey;
            this.m_altKey = altKey;
            this.m_shiftKey = shiftKey;
            return;
        }// end function

        public function set shiftKey(value:Boolean) : void
        {
            this.m_shiftKey = value;
            return;
        }// end function

        public function get keyLocation() : uint
        {
            return this.m_keyLocation;
        }// end function

        public function set charCode(value:uint) : void
        {
            this.m_charCode = value;
            return;
        }// end function

        public native function updateAfterEvent() : void;

        public function get keyCode() : uint
        {
            return this.m_keyCode;
        }// end function

        public function set keyCode(value:uint) : void
        {
            this.m_keyCode = value;
            return;
        }// end function

        override public function clone() : Event
        {
            return new KeyboardEvent(type, bubbles, cancelable, this.m_charCode, this.m_keyCode, this.m_keyLocation, this.m_ctrlKey, this.m_altKey, this.m_shiftKey);
        }// end function

        public function get charCode() : uint
        {
            return this.m_charCode;
        }// end function

        public function set ctrlKey(value:Boolean) : void
        {
            this.m_ctrlKey = value;
            return;
        }// end function

        override public function toString() : String
        {
            return formatToString("KeyboardEvent", "type", "bubbles", "cancelable", "eventPhase", "charCode", "keyCode", "keyLocation", "ctrlKey", "altKey", "shiftKey");
        }// end function

        public function set keyLocation(value:uint) : void
        {
            this.m_keyLocation = value;
            return;
        }// end function

        public function set altKey(value:Boolean) : void
        {
            this.m_altKey = value;
            return;
        }// end function

        public function get ctrlKey() : Boolean
        {
            return this.m_ctrlKey;
        }// end function

        public function get altKey() : Boolean
        {
            return this.m_altKey;
        }// end function

        public function get shiftKey() : Boolean
        {
            return this.m_shiftKey;
        }// end function

    }
}
