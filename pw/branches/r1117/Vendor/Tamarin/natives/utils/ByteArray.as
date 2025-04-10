package flash.utils
{
    [native(cls="ByteArrayClass", instance="ByteArrayObject", methods="auto")]
    public class ByteArray extends Object implements IDataInput, IDataOutput
    {

        public function ByteArray()
        {
            return;
        }// end function

        public native function writeUTFBytes(value:String) : void;

        public native function readShort() : int;

        public native function writeByte(value:int) : void;

        public native function writeDouble(value:Number) : void;

        public native function readUnsignedShort() : uint;

        public native function readDouble() : Number;

        public native function writeInt(value:int) : void;

        private native function _uncompress(algorithm:String) : void;

        public native function get endian() : String;

        public native function get bytesAvailable() : uint;

        public native function readObject();

        public function deflate() : void
        {
            this._compress("deflate");
            return;
        }// end function

        public native function get position() : uint;

        public native function readBoolean() : Boolean;

        public function inflate() : void
        {
            this._uncompress("deflate");
            return;
        }// end function

        public native function set endian(type:String) : void;

        public native function readUTF() : String;

        public native function readUTFBytes(length:uint) : String;

        public native function writeFloat(value:Number) : void;

        public native function writeMultiByte(value:String, charSet:String) : void;

        public native function readUnsignedInt() : uint;

        public native function readByte() : int;

        public native function get objectEncoding() : uint;

        public native function writeBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        public native function clear() : void;

        public native function writeUTF(value:String) : void;

        public native function writeBoolean(value:Boolean) : void;

        public native function set position(offset:uint) : void;

        private native function _compress(algorithm:String) : void;

        public native function readUnsignedByte() : uint;

        public native function writeUnsignedInt(value:uint) : void;

        public native function writeShort(value:int) : void;

        public native function get length() : uint;

        public function compress() : void
        {
            this._compress("zlib");
            return;
        }// end function

        public native function toString() : String;

        public native function set length(value:uint) : void;

        public native function set objectEncoding(version:uint) : void;

        public native function readFloat() : Number;

        public native function readInt() : int;

        public native function readMultiByte(length:uint, charSet:String) : String;

        public function uncompress() : void
        {
            this._uncompress("zlib");
            return;
        }// end function

        public native function readBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        public native function writeObject(object) : void;

        public static native function get defaultObjectEncoding() : uint;

        public static native function set defaultObjectEncoding(version:uint) : void;

    }
}
