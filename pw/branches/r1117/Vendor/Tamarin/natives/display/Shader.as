package flash.display
{
    import flash.utils.*;

    [native(cls="ShaderClass", instance="ShaderObject", methods="auto")]
    public class Shader extends Object
    {

        public function Shader(code:ByteArray = null)
        {
            if (code)
            {
                this.byteCode = code;
            }
            return;
        }// end function

        public function set byteCode(code:ByteArray) : void
        {
            this.data = new ShaderData(code);
            return;
        }// end function

        public native function set data(p:ShaderData) : void;

        public native function get precisionHint() : String;

        public native function get data() : ShaderData;

        public native function set precisionHint(p:String) : void;

    }
}
