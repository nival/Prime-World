package flash.events
{

    public interface IEventDispatcher
    {

        public function IEventDispatcher();

        function dispatchEvent(event:Event) : Boolean;

        function hasEventListener(type:String) : Boolean;

        function willTrigger(type:String) : Boolean;

        function removeEventListener(type:String, listener:Function, useCapture:Boolean = false) : void;

        function addEventListener(type:String, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false) : void;

    }
}
