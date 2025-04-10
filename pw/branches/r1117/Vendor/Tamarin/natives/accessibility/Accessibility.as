package flash.accessibility
{
    import flash.display.*;

    [native(cls="AccessibilityClass", instance="AccessibilityObject", methods="auto")]
    final public class Accessibility extends Object
    {

        public function Accessibility()
        {
            return;
        }// end function

        public static native function sendEvent(source:DisplayObject, childID:uint, eventType:uint, nonHTML:Boolean = false) : void;

        public static native function updateProperties() : void;

        public static native function get active() : Boolean;

    }
}
