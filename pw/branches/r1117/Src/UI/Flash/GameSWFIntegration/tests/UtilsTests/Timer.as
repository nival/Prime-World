import testing.*;
import flash.utils.*;
import flash.events.*;

class TestTimer extends Timer
{
	public function TestTimer(delay:Number, repeatCount:int  = 0)
	{
		super(delay, repeatCount);
	}
}


var smallTimer: TestTimer = new TestTimer(5, 10);
var largeTimer: TestTimer = new TestTimer(60);

FlashAssert (smallTimer.delay == 5 && largeTimer.delay == 60, "something wrong with ctor delays are not setted!");
FlashAssert (smallTimer.repeatCount == 10, "something wrong with ctor reapeatCount is wrong!");

var iterationCount: int = 0;
var timerCompleteCatched: Boolean = false;


function timerHandler(e:TimerEvent):void
{
	iterationCount++;	
}

function completeHandler(e:TimerEvent):void 
{
	timerCompleteCatched = true;
}
 
smallTimer.addEventListener(TimerEvent.TIMER, timerHandler);
largeTimer.addEventListener(TimerEvent.TIMER_COMPLETE, completeHandler);
 
//fire both timers
smallTimer.start();
largeTimer.start();

//check wether they are started now. just to be sure
FlashAssert(smallTimer.running && largeTimer.running, "allright both timers are running");

//run test for 70 mlseconds
for (var i:int = 0; i <70; i++)
	CoreWrapper.Advance(1);

FlashAssert(timerCompleteCatched, "largeTimer is not completed");
FlashAssert(iterationCount==10, "small timer didnt run 10 times but only "+iterationCount);

FlashAssert(!smallTimer.running, "small timer is running but has to be finished");
FlashAssert(!largeTimer.running, "large timer is running but has to be finished");

