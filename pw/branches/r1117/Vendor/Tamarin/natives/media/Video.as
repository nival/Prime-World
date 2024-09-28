package flash.media
{
    import flash.display.*;
    import flash.net.*;

    public class Video extends DisplayObject
    {

        public function Video(width:int = 320, height:int = 240);

        public function get videoHeight() : int;

        public function get smoothing() : Boolean;

        public function get deblocking() : int;

        public function set smoothing(value:Boolean) : void;

        public function attachCamera(camera:Camera) : void;

        public function get videoWidth() : int;

        public function set deblocking(value:int) : void;

        public function clear() : void;

        public function attachNetStream(netStream:NetStream) : void;

    }
}
