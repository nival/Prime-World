package flash.net
{
    import flash.events.*;

    [native(cls="SharedObjectClass", instance="SharedObjectObject", methods="auto")]
    public class SharedObject extends EventDispatcher
    {
        private static const kClear:uint = 6;
        private static const kSetFps:uint = 5;
        private static const kGetSize:uint = 4;
        private static const kClose:uint = 3;
        private static const kFlush:uint = 2;
        private static const kSend:uint = 1;
        private static const kConnect:uint = 0;

        public function SharedObject()
        {
            return;
        }// end function

        public function get size() : uint
        {
            return uint(this.invoke(kGetSize));
        }// end function

        public function flush(minDiskSpace:int = 0) : String
        {
            var _loc_2:* = this.invoke(kFlush, minDiskSpace);
            if (_loc_2 == true)
            {
                return SharedObjectFlushStatus.FLUSHED;
            }
            if (_loc_2 == "pending")
            {
                return SharedObjectFlushStatus.PENDING;
            }
            Error.throwError(Error, 2130);
            return null;
        }// end function

        public function send(... args) : void
        {
            this.invokeWithArgsArray(kSend, args);
            return;
        }// end function

        public native function get data() : Object;

        public native function get client() : Object;

        public function clear() : void
        {
            this.invoke(kClear);
            return;
        }// end function

        public native function setDirty(propertyName:String) : void;

        public function connect(myConnection:NetConnection, params:String = null) : void
        {
            if (!Boolean(this.invoke(kConnect, myConnection, params)))
            {
                Error.throwError(Error, 2139);
            }
            return;
        }// end function

        public function set fps(updatesPerSecond:Number) : void
        {
            this.invoke(kSetFps, updatesPerSecond);
            return;
        }// end function

        public native function set objectEncoding(version:uint) : void;

        public native function set client(object:Object) : void;

        public function setProperty(propertyName:String, value:Object = null) : void
        {
            if (this.data[propertyName] != value)
            {
                this.data[propertyName] = value;
                this.setDirty(propertyName);
            }
            return;
        }// end function

        public function close() : void
        {
            this.invoke(kClose);
            return;
        }// end function

        public native function get objectEncoding() : uint;

        private native function invokeWithArgsArray(index:uint, args:Array);

        private native function invoke(index:uint, ... args);

        public static native function set defaultObjectEncoding(version:uint) : void;

        public static native function getDiskUsage(url:String) : int;

        public static native function get defaultObjectEncoding() : uint;

        public static native function getLocal(name:String, localPath:String = null, secure:Boolean = false) : SharedObject;

        public static native function deleteAll(url:String) : int;

        public static native function getRemote(name:String, remotePath:String = null, persistence:Object = false, secure:Boolean = false) : SharedObject;

    }
}
