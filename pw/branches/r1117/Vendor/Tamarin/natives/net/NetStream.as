package flash.net
{
    import flash.events.*;
    import flash.media.*;

    [native(cls="NetStreamClass", instance="NetStreamObject", methods="auto")]
    public class NetStream extends EventDispatcher
    {
        private static const kSetBufferTime:uint = 4;
        private static const kGetAudioCodecID:uint = 313;
        private static const kGetMaxPauseBufferTime:Object = 400;
        private static const kSetAudioCodecID:uint = 314;
        private static const kSend:uint = 3;
        private static const kSetMaxPauseBufferTime:Object = 401;
        private static const kGetTotalFrames:uint = 307;
        private static const kGetFarNonce:uint = 342;
        private static const kAttachAudio:uint = 1;
        private static const kSetTotalFrames:uint = 308;
        private static const kGetInfo:uint = 343;
        public static const CONNECT_TO_FMS:String = "connectToFMS";
        private static const kGetVideoCodecID:uint = 311;
        private static const kGetFarID:uint = 340;
        private static const kAttachVideo:uint = 2;
        private static const kClose:uint = 0;
        private static const kGetBufferLength:uint = 303;
        private static const kGetLiveDelay:uint = 304;
        private static const kSetVideoCodecID:uint = 312;
        private static const kGetTime:uint = 300;
        public static const DIRECT_CONNECTIONS:String = "directConnections";
        private static const kGetBytesTotal:uint = 306;
        private static const kGetBytesLoaded:uint = 305;
        private static const kCall:uint = 202;
        private static const kGetBufferTime:uint = 302;
        private static const kGetCurrentFps:uint = 301;
        private static const kGetNearNonce:uint = 341;

        public function NetStream(connection:NetConnection, peerID:String = "connectToFMS")
        {
            this.construct(connection, peerID);
            if (peerID == CONNECT_TO_FMS)
            {
                connection.call("createStream", new Responder(this.onResult, this.onStatus));
            }
            return;
        }// end function

        private function onStatus(info) : void
        {
            dispatchEvent(new NetStatusEvent("status", false, false, info));
            return;
        }// end function

        public native function set soundTransform(sndTransform:SoundTransform) : void;

        public function togglePause() : void
        {
            this.call(this, "pause", null, undefined, this.time * 1000);
            return;
        }// end function

        public function set maxPauseBufferTime(pauseBufferTime:Number) : void
        {
            this.invoke(kSetMaxPauseBufferTime, pauseBufferTime);
            return;
        }// end function

        public function get maxPauseBufferTime() : Number
        {
            return this.invoke(kGetMaxPauseBufferTime);
        }// end function

        public function seek(offset:Number) : void
        {
            this.call(this, "seek", null, offset * 1000);
            return;
        }// end function

        public function send(handlerName:String, ... args) : void
        {
            args.unshift(handlerName);
            this.invokeWithArgsArray(kSend, args);
            return;
        }// end function

        public native function get peerStreams() : Array;

        public function attachCamera(theCamera:Camera, snapshotMilliseconds:int = -1) : void
        {
            this.invoke(kAttachVideo, theCamera, snapshotMilliseconds);
            return;
        }// end function

        public native function get client() : Object;

        private native function invokeWithArgsArray(index:uint, p_arguments:Array);

        public function publish(name:String = null, type:String = null) : void
        {
            if (type)
            {
                this.call(this, "publish", null, name, type);
            }
            else
            {
                this.call(this, "publish", null, name);
            }
            return;
        }// end function

        public function get bytesLoaded() : uint
        {
            return this.invoke(kGetBytesLoaded);
        }// end function

        public function attachAudio(microphone:Microphone) : void
        {
            this.invoke(kAttachAudio, microphone);
            return;
        }// end function

        public function get time() : Number
        {
            return this.invoke(kGetTime);
        }// end function

        public function get bufferLength() : Number
        {
            return this.invoke(kGetBufferLength);
        }// end function

        public native function set client(object:Object) : void;

        private native function construct(connection:NetConnection, peerID:String) : void;

        public function receiveVideo(flag:Boolean) : void
        {
            this.call(this, "receiveVideo", null, flag);
            return;
        }// end function

        public function get bytesTotal() : uint
        {
            return this.invoke(kGetBytesTotal);
        }// end function

        public function set bufferTime(bufferTime:Number) : void
        {
            this.invoke(kSetBufferTime, bufferTime);
            return;
        }// end function

        public function get videoCodec() : uint
        {
            return this.invoke(kGetVideoCodecID);
        }// end function

        private native function onResult(streamId:int) : void;

        public native function get soundTransform() : SoundTransform;

        private function call(stream:NetStream, command:String, responder:Responder, ... args) : void
        {
            args.unshift(stream, command, responder);
            this.invokeWithArgsArray(kCall, args);
            return;
        }// end function

        public native function get farNonce() : String;

        public function get audioCodec() : uint
        {
            return this.invoke(kGetAudioCodecID);
        }// end function

        public function onPeerConnect(subscriber:NetStream) : Boolean
        {
            return true;
        }// end function

        public native function get nearNonce() : String;

        public native function set checkPolicyFile(state:Boolean) : void;

        public function get bufferTime() : Number
        {
            return this.invoke(kGetBufferTime);
        }// end function

        public native function get info() : NetStreamInfo;

        public function get currentFPS() : Number
        {
            return this.invoke(kGetCurrentFps);
        }// end function

        public function receiveVideoFPS(FPS:Number) : void
        {
            this.call(this, "receiveVideo", null, FPS);
            return;
        }// end function

        public native function get objectEncoding() : uint;

        public function receiveAudio(flag:Boolean) : void
        {
            this.call(this, "receiveAudio", null, flag);
            return;
        }// end function

        public function resume() : void
        {
            this.call(this, "pause", null, false, this.time * 1000);
            return;
        }// end function

        public function pause() : void
        {
            this.call(this, "pause", null, true, this.time * 1000);
            return;
        }// end function

        public function get liveDelay() : Number
        {
            return this.invoke(kGetLiveDelay);
        }// end function

        private native function invoke(index:uint, ... args);

        public native function get farID() : String;

        public native function play(... args) : void;

        public function get decodedFrames() : uint
        {
            return this.invoke(kGetTotalFrames);
        }// end function

        public native function get checkPolicyFile() : Boolean;

        public native function play2(param:NetStreamPlayOptions) : void;

        public function close() : void
        {
            this.invoke(kClose);
            return;
        }// end function

    }
}
