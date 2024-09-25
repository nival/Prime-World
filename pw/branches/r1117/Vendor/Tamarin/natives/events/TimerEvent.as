package flash.events
{

    [native(cls="TimerEventClass", instance="TimerEventObject", methods="auto")]
    public class TimerEvent extends Event
    {
        public static const TIMER_COMPLETE:String = "timerComplete";
        public static const TIMER:String = "timer";

        public function TimerEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
        {
            super(type, bubbles, cancelable);
            return;
        }// end function

        override public function toString() : String
        {
            return formatToString("TimerEvent", "type", "bubbles", "cancelable", "eventPhase");
        }// end function

        override public function clone() : Event
        {
            return new TimerEvent(type, bubbles, cancelable);
        }// end function

        public native function updateAfterEvent() : void;

    }
}
