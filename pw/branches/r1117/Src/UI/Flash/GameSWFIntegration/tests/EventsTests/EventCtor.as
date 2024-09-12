import flash.events.*;
import testing.*;

var firstChildCtorWasCalled: Boolean = false;

class EventChild extends Event
{
    public function EventChild(type:String, bubbles:Boolean = false)
    {
	FlashAssert(true, "EventChild ctor");
	firstChildCtorWasCalled = true;
        super(type);
    }

}

class EventGrandChild extends EventChild
{
    public function EventGrandChild()
    {
	FlashAssert(true, "EventGrandChild ctor");
        super("EventGrandChild", false);
    }

}

var event: EventGrandChild = new EventGrandChild();

FlashAssert (event.type == "EventGrandChild", "parent super native ctor wasnt called, name now "+event.type);
FlashAssert(firstChildCtorWasCalled, "parent ctor wasnt called!");


