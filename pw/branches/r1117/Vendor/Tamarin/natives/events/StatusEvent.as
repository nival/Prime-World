package flash.events
{

    public class StatusEvent extends Event
    {
        private var m_level:String;
        private var m_code:String;
        public static const STATUS:String = "status";

        public function StatusEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, code:String = "", level:String = "")
        {
            super(type, bubbles, cancelable);
            this.m_code = code;
            this.m_level = level;
            return;
        }// end function

        public function get code() : String
        {
            return this.m_code;
        }// end function

        public function set level(value:String) : void
        {
            this.m_level = value;
            return;
        }// end function

        public function set code(value:String) : void
        {
            this.m_code = value;
            return;
        }// end function

        public function get level() : String
        {
            return this.m_level;
        }// end function

        override public function toString() : String
        {
            return formatToString("StatusEvent", "type", "bubbles", "cancelable", "eventPhase", "code", "level");
        }// end function

        override public function clone() : Event
        {
            return new StatusEvent(type, bubbles, cancelable, this.m_code, this.m_level);
        }// end function

    }
}
