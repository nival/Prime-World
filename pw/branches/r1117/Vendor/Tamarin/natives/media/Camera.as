package flash.media
{
    import flash.events.*;

    [native(cls="CameraClass", instance="CameraObject", methods="auto")]
    final public class Camera extends EventDispatcher
    {

        public function Camera()
        {
            return;
        }// end function

        public native function get loopback() : Boolean;

        public native function setMode(width:int, height:int, fps:Number, favorArea:Boolean = true) : void;

        public native function get width() : int;

        public native function get height() : int;

        public native function get fps() : Number;

        public native function get name() : String;

        public native function setMotionLevel(motionLevel:int, timeout:int = 2000) : void;

        public native function get muted() : Boolean;

        public native function get motionLevel() : int;

        public native function get currentFPS() : Number;

        public native function get bandwidth() : int;

        public native function get index() : int;

        public native function get keyFrameInterval() : int;

        public native function setLoopback(compress:Boolean = false) : void;

        public native function get activityLevel() : Number;

        public native function setCursor(value:Boolean) : void;

        public native function get motionTimeout() : int;

        public native function setKeyFrameInterval(keyFrameInterval:int) : void;

        public native function setQuality(bandwidth:int, quality:int) : void;

        public native function get quality() : int;

        public static native function get names() : Array;

        public static native function getCamera(name:String = null) : Camera;

    }
}
