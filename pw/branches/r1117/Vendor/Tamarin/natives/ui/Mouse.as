package flash.ui
{

    [native(cls="MouseClass", instance="MouseObject", methods="auto")]
    final public class Mouse extends Object
    {

        public function Mouse()
        {
            return;
        }// end function

        public static native function hide() : void;

        public static native function set cursor(value:String) : void;

        public static native function show() : void;

        public static native function get cursor() : String;

    }
}
