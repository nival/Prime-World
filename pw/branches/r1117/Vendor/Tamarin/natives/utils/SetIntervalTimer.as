package flash.utils
{
    import flash.events.*;

    final class SetIntervalTimer extends Timer
    {
        private var closure:Function;
        private var rest:Array;
        var id:uint;
        private static var intervals:Array = [];

        function SetIntervalTimer(closure:Function, delay:Number, repeats:Boolean, rest:Array)
        {
            super(delay, repeats ? (0) : (1));
            this.closure = closure;
            this.rest = rest;
            addEventListener(TimerEvent.TIMER, this.onTimer);
            start();
            this.id = intervals.length + 1;
            intervals.push(this);
            return;
        }// end function

        private function onTimer(event:Event) : void
        {
            this.closure.apply(null, this.rest);
            if (repeatCount == 1)
            {
                this.clearArrayEntry();
            }
            return;
        }// end function

        function clearArrayEntry() : void
        {
            var _loc_1:int = 0;
            while (_loc_1 < intervals.length)
            {
                
                if (intervals[_loc_1] == this)
                {
                    intervals[_loc_1] = 0;
                    break;
                }
                _loc_1 = _loc_1 + 1;
            }
            return;
        }// end function

        static function clearInterval(id:uint) : void
        {
            id = id - 1;
	    // [139] SimonK. put (intervals[id] is SetIntervalTimer) by myself. recheck it 
            if (intervals[id] is SetIntervalTimer)
            {
                intervals[id].stop();
                delete intervals[id];
            }
            return;
        }// end function

    }
}
