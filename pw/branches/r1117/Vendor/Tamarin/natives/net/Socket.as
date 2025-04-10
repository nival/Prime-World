package flash.net
{
    import flash.events.*;
    import flash.utils.*;

    [native(cls="SocketClass", instance="SocketObject", methods="auto")]
    public class Socket extends EventDispatcher implements IDataInput, IDataOutput
    {
        private var _timeoutEvent:SecurityErrorEvent;
        private var _timeout:uint;
        private var _timeoutTimer:Timer;
        private static const MIN_TIMEOUT:Object = 250;

        public function Socket(host:String = null, port:int = 0)
        {
            this._init();
            if (host != null)
            {
                this.connect(host, port);
            }
            return;
        }// end function

        private function onTimeout(event:TimerEvent) : void
        {
            this._timeoutTimer.stop();
            if (this.didFailureOccur())
            {
                dispatchEvent(this._timeoutEvent);
            }
            else if (!this.connected)
            {
                dispatchEvent(this._timeoutEvent);
            }
            return;
        }// end function

        public native function writeUTFBytes(value:String) : void;

        public native function flush() : void;

        public native function writeObject(object) : void;

        public native function writeByte(value:int) : void;

        public native function get connected() : Boolean;

        public native function readShort() : int;

        public native function readUnsignedShort() : uint;

        public native function readDouble() : Number;

        public native function writeInt(value:int) : void;

        public native function get endian() : String;

        public native function set objectEncoding(version:uint) : void;

        public native function get bytesAvailable() : uint;

        private native function didFailureOccur() : Boolean;

        public native function writeDouble(value:Number) : void;

        public native function readObject();

        public native function readUTF() : String;

        public native function set endian(type:String) : void;

        private native function internalGetSecurityErrorMessage(host:String, port:int) : String;

        public native function readBoolean() : Boolean;

        public native function readUTFBytes(length:uint) : String;

        private native function internalClose() : void;

        public native function writeFloat(value:Number) : void;

        public function set timeout(value:uint) : void
        {
            if (value < MIN_TIMEOUT)
            {
                this._timeout = MIN_TIMEOUT;
            }
            else
            {
                this._timeout = value;
            }
            return;
        }// end function

        public native function readByte() : int;

        public native function writeUTF(value:String) : void;

        public native function writeBoolean(value:Boolean) : void;

        public native function get objectEncoding() : uint;

        public native function readUnsignedInt() : uint;

        public native function writeBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        public native function writeMultiByte(value:String, charSet:String) : void;

        public native function readUnsignedByte() : uint;

        public function get timeout() : uint
        {
            return this._timeout;
        }// end function

        public native function writeUnsignedInt(value:uint) : void;

        public native function writeShort(value:int) : void;

        public native function readFloat() : Number;

        public function connect(host:String, port:int) : void
        {
            this._init();
            this._timeoutEvent = new SecurityErrorEvent(SecurityErrorEvent.SECURITY_ERROR, false, false, this.internalGetSecurityErrorMessage(host, port));
            this._timeoutTimer.reset();
            this._timeoutTimer.delay = this._timeout;
            this._timeoutTimer.start();
            this.internalConnect(host, port);
            return;
        }// end function

        public native function readMultiByte(length:uint, charSet:String) : String;

        private native function internalConnect(host:String, port:int) : void;

        private function _init() : void
        {
            if (this._timeoutTimer)
            {
                return;
            }
            this._timeout = 20000;
            this._timeoutTimer = new Timer(this._timeout);
            this._timeoutTimer.addEventListener(TimerEvent.TIMER, this.onTimeout);
            return;
        }// end function

        public native function readBytes(bytes:ByteArray, offset:uint = 0, length:uint = 0) : void;

        public function close() : void
        {
            this._init();
            this._timeoutTimer.stop();
            this._timeoutTimer.reset();
            this.internalClose();
            return;
        }// end function

        public native function readInt() : int;

    }
}
