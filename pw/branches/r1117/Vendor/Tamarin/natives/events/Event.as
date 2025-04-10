package flash.events
{

    [native(cls="EventClass", instance="EventObject", methods="auto")]
    public class Event extends Object
    {
        public static const CANCEL:String = "cancel";
        public static const ENTER_FRAME:String = "enterFrame";
        public static const SOUND_COMPLETE:String = "soundComplete";
        public static const UNLOAD:String = "unload";
        public static const INIT:String = "init";
        public static const RENDER:String = "render";
        public static const TAB_ENABLED_CHANGE:String = "tabEnabledChange";
        public static const ADDED_TO_STAGE:String = "addedToStage";
        public static const FRAME_CONSTRUCTED:String = "frameConstructed";
        public static const TAB_CHILDREN_CHANGE:String = "tabChildrenChange";
        public static const CUT:String = "cut";
        public static const CLEAR:String = "clear";
        public static const CHANGE:String = "change";
        public static const RESIZE:String = "resize";
        public static const COMPLETE:String = "complete";
        public static const FULLSCREEN:String = "fullScreen";
        public static const SELECT_ALL:String = "selectAll";
        public static const REMOVED:String = "removed";
        public static const CONNECT:String = "connect";
        public static const SCROLL:String = "scroll";
        public static const OPEN:String = "open";
        public static const CLOSE:String = "close";
        public static const MOUSE_LEAVE:String = "mouseLeave";
        public static const ADDED:String = "added";
        public static const REMOVED_FROM_STAGE:String = "removedFromStage";
        public static const EXIT_FRAME:String = "exitFrame";
        public static const TAB_INDEX_CHANGE:String = "tabIndexChange";
        public static const PASTE:String = "paste";
        public static const DEACTIVATE:String = "deactivate";
        public static const COPY:String = "copy";
        public static const ID3:String = "id3";
        public static const ACTIVATE:String = "activate";
        public static const SELECT:String = "select";


        public function Event(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
	{
		Init(type, bubbles, cancelable);
	}

	private native function Init(type:String, bubbles:Boolean, cancelable:Boolean): void;

        public native function isDefaultPrevented() : Boolean;

        public native function get eventPhase() : uint;

        public function formatToString(className:String, ... args) : String
        {
            var _loc_5:String = null;
            var _loc_6:* = undefined;
            var result: String = "";
            result = result + ("[" + className);
            var _loc_4:uint = 0;
            while (_loc_4 < args.length)
            {
                
                _loc_5 = args[_loc_4];
                _loc_6 = this[_loc_5];
                if (_loc_6 is String)
                {
                    result = result + (" " + _loc_5 + "=\"" + _loc_6 + "\"");
                }
                else
                {
                    result = result + (" " + _loc_5 + "=" + _loc_6);
                }
                _loc_4 = _loc_4 + 1;
            }
            result = result + "]";
            return result;
        }// end function

        public function clone() : Event
        {
            return new Event(this.type, this.bubbles, this.cancelable);
        }// end function

        public native function get bubbles() : Boolean;

        public native function preventDefault() : void;

        public native function stopPropagation() : void;

        public function toString() : String
        {
            return this.formatToString("Event", "type", "bubbles", "cancelable", "eventPhase");
        }// end function

        public native function get target() : Object;

        public native function get cancelable() : Boolean;

        public native function get currentTarget() : Object;

        public native function get type() : String;

        public native function stopImmediatePropagation() : void;

    }
}
