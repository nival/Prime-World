package flash.utils
{
    import flash.events.*;

    [native(cls="TimerClass", instance="TimerObject", methods="auto")]
    public class Timer extends EventDispatcher
    {
        private var m_repeatCount:int;
        private var m_iteration:int;
        private var m_delay:Number;

        public function Timer(delay:Number, repeatCount:int = 0)
        {
            if (delay >= 0)
            {
            }
            if (!isFinite(delay))
            {
                Error.throwError(RangeError, 2066);
            }
            this.m_delay = delay;
            this.m_repeatCount = repeatCount;
            return;
        }// end function

        private native function _timerDispatch() : void;

        public function get delay() : Number
        {
            return this.m_delay;
        }// end function

        public function set delay(value:Number) : void
        {
            if (value >= 0)
            {
            }
            if (!isFinite(value))
            {
                Error.throwError(RangeError, 2066);
            }
            this.m_delay = value;
            if (this.running)
            {
                this.stop();
                this.start();
            }
            return;
        }// end function

        public function set repeatCount(value:int) : void
        {
            this.m_repeatCount = value;
            if (this.running)
            {
            }
            if (this.m_repeatCount != 0)
            {
            }
            if (this.m_iteration >= this.m_repeatCount)
            {
                this.stop();
            }
            return;
        }// end function

        private native function _start(delay:Number, closure:Function) : void;

        private function tick() : void
        {
	    m_iteration++;
            this._timerDispatch();

            if (this.m_iteration >= this.m_repeatCount)
            {
                this.stop();
                dispatchEvent(new TimerEvent(TimerEvent.TIMER_COMPLETE, false, false));
            }
            return;
        }// end function

        public function reset() : void
        {
            if (this.running)
            {
                this.stop();
            }
            this.m_iteration = 0;
            return;
        }// end function

        public function get repeatCount() : int
        {
            return this.m_repeatCount;
        }// end function

        public function start() : void
        {
            if (!this.running)
            {
                this._start(this.m_delay, this.tick);
            }
            return;
        }// end function

        public native function stop() : void;

        public function get currentCount() : int
        {
            return this.m_iteration;
        }// end function

        public native function get running() : Boolean;

    }
}
