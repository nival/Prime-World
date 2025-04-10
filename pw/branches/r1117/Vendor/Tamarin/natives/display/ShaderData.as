package flash.display
{
    import flash.utils.*;

    [native(cls="ShaderDataClass", instance="ShaderDataObject", methods="auto")]
    final dynamic public class ShaderData extends Object
    {

        public function ShaderData(byteCode:ByteArray)
        {
            this._setByteCode(byteCode);
            return;
        }// end function

        private native function _setByteCode(code:ByteArray) : void;

    }
}
