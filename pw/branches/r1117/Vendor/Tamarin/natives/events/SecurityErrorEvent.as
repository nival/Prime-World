package flash.events
{

    public class SecurityErrorEvent extends ErrorEvent
    {
        public static const SECURITY_ERROR:String = "securityError";

        public function SecurityErrorEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, text:String = "")
        {
            super(type, bubbles, cancelable, text);
            return;
        }// end function

        override public function toString() : String
        {
            return formatToString("SecurityErrorEvent", "type", "bubbles", "cancelable", "eventPhase", "text");
        }// end function

        override public function clone() : Event
        {
            return new SecurityErrorEvent(type, bubbles, cancelable, text);
        }// end function

    }
}
