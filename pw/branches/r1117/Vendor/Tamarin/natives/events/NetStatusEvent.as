package flash.events
{

    public class NetStatusEvent extends Event
    {
        private var m_info:Object;
        public static const NET_STATUS:String = "netStatus";

        public function NetStatusEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false, info:Object = null)
        {
            super(type, bubbles, cancelable);
            this.m_info = info;
            return;
        }// end function

        public function set info(value:Object) : void
        {
            this.m_info = value;
            return;
        }// end function

        override public function toString() : String
        {
            return formatToString("NetStatusEvent", "type", "bubbles", "cancelable", "eventPhase", "info");
        }// end function

        override public function clone() : Event
        {
            return new NetStatusEvent(type, bubbles, cancelable, this.m_info);
        }// end function

        public function get info() : Object
        {
            return this.m_info;
        }// end function

    }
}
