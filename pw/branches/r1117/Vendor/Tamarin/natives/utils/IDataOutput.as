package flash.utils
{

    public interface IDataOutput
    {

        public function IDataOutput();

        function writeMultiByte(value:String, charSet:String) : void;

        function writeUTFBytes(value:String) : void;

        function writeShort(value:int) : void;

        function writeByte(value:int) : void;

        function writeUTF(value:String) : void;

        function writeBoolean(value:Boolean) : void;

        function get endian() : String;

        function set objectEncoding(version:uint) : void;

        function writeBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        function writeInt(value:int) : void;

        function get objectEncoding() : uint;

        function set endian(type:String) : void;

        function writeDouble(value:Number) : void;

        function writeUnsignedInt(value:uint) : void;

        function writeFloat(value:Number) : void;

        function writeObject(object) : void;

    }
}
