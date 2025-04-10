package flash.events
{

    [native(cls="EventDispatcherClass", instance="EventDispatcherObject", methods="auto")]
    public class EventDispatcher extends Object implements IEventDispatcher
    {

        public function EventDispatcher(target:IEventDispatcher = null);

        public function dispatchEvent(event:Event) : Boolean
        {
            if (event.target)
            {
                return this.dispatchEventFunction(event.clone());
            }
            return this.dispatchEventFunction(event);
        }// end function

        public native function willTrigger(type:String) : Boolean;

        public native function removeEventListener(type:String, listener:Function, useCapture:Boolean = false) : void;

        public function toString() : String
        {
            return Object.prototype.toString.call(this);
        }// end function

        private native function dispatchEventFunction(event:Event) : Boolean;

        public native function hasEventListener(type:String) : Boolean;

        public native function addEventListener(type:String, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false) : void;

        private native function get listeners() : Array;

    }
}
