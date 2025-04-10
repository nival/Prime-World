package flash.net
{

    [native(cls="ObjectEncodingClass", instance="ObjectEncodingObject", methods="auto")]
    final public class ObjectEncoding extends Object
    {
        public static const DEFAULT:uint = 3;
        public static const AMF0:uint = 0;
        public static const AMF3:uint = 3;

        public function ObjectEncoding()
        {
            return;
        }// end function

        public static native function get dynamicPropertyWriter() : IDynamicPropertyWriter;

        public static native function set dynamicPropertyWriter(object:IDynamicPropertyWriter) : void;

    }
}
