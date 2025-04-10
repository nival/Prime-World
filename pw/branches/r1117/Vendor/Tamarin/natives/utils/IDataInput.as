package flash.utils
{

    public interface IDataInput
    {

        public function IDataInput();

        function get objectEncoding() : uint;

        function readUnsignedInt() : uint;

        function get bytesAvailable() : uint;

        function readShort() : int;

        function readDouble() : Number;

        function readMultiByte(length:uint, charSet:String) : String;

        function readFloat() : Number;

        function readUnsignedShort() : uint;

        function readBoolean() : Boolean;

        function readUnsignedByte() : uint;

        function readBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        function set endian(type:String) : void;

        function readUTF() : String;

        function readInt() : int;

        function readUTFBytes(length:uint) : String;

        function get endian() : String;

        function readObject();

        function set objectEncoding(version:uint) : void;

        function readByte() : int;

    }
}
