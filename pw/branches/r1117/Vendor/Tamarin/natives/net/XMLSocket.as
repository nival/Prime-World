package flash.net
{
    import flash.events.*;
    import flash.utils.*;

    public class XMLSocket extends EventDispatcher
    {
        private var _rcvBuffer:ByteArray;
        private var _internalSocket:Socket;
        private var _bytesInPacket:uint;

        public function XMLSocket(host:String = null, port:int = 0) : void
        {
            this._rcvBuffer = new ByteArray();
            this._bytesInPacket = 0;
            this._internalSocket = new Socket(host, port);
            this._internalSocket.addEventListener(Event.CLOSE, this.reflectEvent);
            this._internalSocket.addEventListener(Event.CONNECT, this.reflectEvent);
            this._internalSocket.addEventListener(IOErrorEvent.IO_ERROR, this.reflectEvent);
            this._internalSocket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, this.reflectEvent);
            this._internalSocket.addEventListener(ProgressEvent.SOCKET_DATA, this.scanAndSendEvent);
            return;
        }// end function

        public function get timeout() : int
        {
            return this._internalSocket.timeout;
        }// end function

        public function set timeout(value:int) : void
        {
            this._internalSocket.timeout = value;
            return;
        }// end function

        public function send(object) : void
        {
            if (object is XML)
            {
                this._internalSocket.writeUTFBytes(object.toXMLString());
            }
            else
            {
                this._internalSocket.writeUTFBytes(object.toString());
            }
            this._internalSocket.writeByte(0);
            this._internalSocket.flush();
            return;
        }// end function

        public function get connected() : Boolean
        {
            return this._internalSocket.connected;
        }// end function

        public function connect(host:String, port:int) : void
        {
            this._internalSocket.connect(host, port);
            return;
        }// end function

        private function scanAndSendEvent(event:ProgressEvent) : void
        {
            var _loc_2:uint = 0;
            var _loc_3:* = this._rcvBuffer.position;
            var _loc_4:uint = 0;
            var _loc_5:uint = 0;
            var _loc_6:uint = 0;
            if (this._internalSocket.bytesAvailable)
            {
                this._internalSocket.readBytes(this._rcvBuffer, this._rcvBuffer.position);
            }
            this._rcvBuffer.position = _loc_3;
            _loc_5 = this._rcvBuffer.bytesAvailable + this._bytesInPacket;
            _loc_4 = this._bytesInPacket;
            while (_loc_4 < _loc_5)
            {
                
                var _loc_7:String = this;
                var _loc_8:* = this._bytesInPacket + 1;
                _loc_7._bytesInPacket = _loc_8;
                if (this._rcvBuffer[_loc_4] == 0)
                {
                    this._rcvBuffer.position = _loc_6;
                    dispatchEvent(new DataEvent(DataEvent.DATA, false, false, this._rcvBuffer.readUTFBytes(this._bytesInPacket)));
                    _loc_6 = _loc_6 + this._bytesInPacket;
                    this._bytesInPacket = 0;
                }
                _loc_4 = _loc_4 + 1;
            }
            if (this._bytesInPacket != 0)
            {
                _loc_4 = 0;
                while (_loc_4 < this._bytesInPacket)
                {
                    
                    this._rcvBuffer[_loc_4] = this._rcvBuffer[_loc_6++];
                    _loc_4 = _loc_4 + 1;
                }
                this._rcvBuffer.length = this._bytesInPacket;
                this._rcvBuffer.position = this._bytesInPacket;
            }
            else
            {
                this._rcvBuffer.length = 0;
                this._rcvBuffer.position = 0;
            }
            return;
        }// end function

        private function reflectEvent(event:Event) : void
        {
            dispatchEvent(event);
            return;
        }// end function

        public function close() : void
        {
            this._internalSocket.close();
            return;
        }// end function

    }
}
