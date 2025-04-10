package flash.utils
{

    [native(cls="ObjectOutputClass", instance="ObjectOutputObject", methods="auto")]
    class ObjectOutput extends Object implements IDataOutput
    {

        function ObjectOutput()
        {
            return;
        }// end function

        public native function writeMultiByte(value:String, charSet:String) : void;

        public native function writeUTFBytes(value:String) : void;

        public native function writeObject(object) : void;

        public native function writeBoolean(value:Boolean) : void;

        public native function writeBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        public native function writeByte(value:int) : void;

        public native function writeUTF(value:String) : void;

        public native function writeDouble(value:Number) : void;

        public native function writeUnsignedInt(value:uint) : void;

        public native function writeShort(value:int) : void;

        public native function writeInt(value:int) : void;

        public native function get endian() : String;

        public native function set objectEncoding(version:uint) : void;

        public native function get objectEncoding() : uint;

        public native function set endian(type:String) : void;

        public native function writeFloat(value:Number) : void;

    }
}
