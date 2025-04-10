package flash.events
{

    [native(cls="WeakMethodClosureClass", instance="WeakMethodClosureObject", methods="auto")]
    class WeakMethodClosure extends Object
    {

        function WeakMethodClosure()
        {
            return;
        }// end function

        private native function get savedThis() : Object;

    }
}
