package flash.display
{

    [native(cls="ShaderInputClass", instance="ShaderInputObject", methods="auto")]
    final dynamic public class ShaderInput extends Object
    {

        public function ShaderInput()
        {
            return;
        }// end function

        public native function get channels() : int;

        public native function get index() : int;

        public native function set input(input:Object) : void;

        public native function get width() : int;

        public native function get height() : int;

        public native function get input() : Object;

        public native function set width(value:int) : void;

        public native function set height(value:int) : void;

    }
}
