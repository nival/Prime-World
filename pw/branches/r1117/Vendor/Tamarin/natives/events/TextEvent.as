package flash.events
{

    public class TextEvent extends Event
    {
        private var m_text:String;
        public static const TEXT_INPUT:String = "textInput";
        public static const LINK:String = "link";

        public function TextEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, text:String = "")
        {
            super(type, bubbles, cancelable);
            this.m_text = text;
            return;
        }// end function

        public function get text() : String
        {
            return this.m_text;
        }// end function

        public function set text(value:String) : void
        {
            this.m_text = value;
            return;
        }// end function

        override public function toString() : String
        {
            return formatToString("TextEvent", "type", "bubbles", "cancelable", "eventPhase", "text");
        }// end function

        override public function clone() : Event
        {
            return new TextEvent(type, bubbles, cancelable, this.m_text);
        }// end function

    }
}
