package flash.display
{

    [native(cls="ShaderParameterClass", instance="ShaderParameterObject", methods="auto")]
    final dynamic public class ShaderParameter extends Object
    {

        public function ShaderParameter()
        {
            return;
        }// end function

        public native function get value() : Array;

        public native function set value(v:Array) : void;

        public native function get type() : String;

        public native function get index() : int;

    }
}
