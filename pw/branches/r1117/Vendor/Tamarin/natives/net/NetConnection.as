package flash.net
{
    import flash.events.*;

    [native(cls="NetConnectionClass", instance="NetConnectionObject", methods="auto")]
    public class NetConnection extends EventDispatcher
    {
        private static const kAddHeader:uint = 3;
        private static const kGetProtocol:uint = 6;
        private static const kGetFarID:uint = 8;
        private static const kCall:uint = 2;
        private static const kGetConnectedProxyType:uint = 4;
        private static const kGetNearNonce:uint = 9;
        private static const kGetNearID:uint = 7;
        private static const kGetFarNonce:uint = 10;
        private static const kGetUsingTLS:uint = 5;
        private static const kClose:uint = 1;
        private static const kConnect:uint = 0;

        public function NetConnection()
        {
            return;
        }// end function

        public native function get unconnectedPeerStreams() : Array;

        public native function get nearID() : String;

        public native function set objectEncoding(version:uint) : void;

        public native function set maxPeerConnections(maxPeers:uint) : void;

        public native function get protocol() : String;

        public native function get proxyType() : String;

        public native function get connected() : Boolean;

        public native function connect(command:String, ... args) : void;

        public native function get client() : Object;

        public native function get uri() : String;

        private native function invokeWithArgsArray(index:uint, args:Array);

        public function addHeader(operation:String, mustUnderstand:Boolean = false, param:Object = null) : void
        {
            var _loc_4:* = new Array(operation, mustUnderstand, param);
            this.invokeWithArgsArray(kAddHeader, _loc_4);
            return;
        }// end function

        public native function get maxPeerConnections() : uint;

        public native function set proxyType(ptype:String) : void;

        private native function invoke(index:uint, ... args);

        public native function get objectEncoding() : uint;

        public native function get nearNonce() : String;

        public native function set client(object:Object) : void;

        public native function get usingTLS() : Boolean;

        public function close() : void
        {
            this.invoke(kClose);
            return;
        }// end function

        public native function get farID() : String;

        public native function get farNonce() : String;

        public function call(command:String, responder:Responder, ... args) : void
        {
            args.unshift(command, responder);
            this.invokeWithArgsArray(kCall, args);
            return;
        }// end function

        public native function get connectedProxyType() : String;

        public static native function set defaultObjectEncoding(version:uint) : void;

        public static native function get defaultObjectEncoding() : uint;

    }
}
