package flash.display
{

    [native(cls="MovieClipClass", instance="MovieClipObject", methods="auto")]
    dynamic public class MovieClip extends Sprite
    {

        public function MovieClip()
        {
          _Init();
          super();
        }

        private native function _Init() : void;

        public native function get currentFrameLabel() : String;

        public native function prevFrame() : void;

        public native function stop() : void;

        public native function get scenes() : Array;

        public native function gotoAndPlay(frame:Object, scene:String = null) : void;

        public native function set enabled(value:Boolean) : void;

        public native function get totalFrames() : int;

        public native function get framesLoaded() : int;

        public native function get enabled() : Boolean;

        public native function nextScene() : void;

        public native function get currentFrame() : int;

        public native function get currentScene() : Scene;

        public native function gotoAndStop(frame:Object, scene:String = null) : void;

        public native function addFrameScript(... args) : void;

        public native function set trackAsMenu(value:Boolean) : void;

        public native function prevScene() : void;

        public native function nextFrame() : void;

        public native function play() : void;

        public native function get trackAsMenu() : Boolean;

        public native function get currentLabel() : String;

        public function get currentLabels() : Array
        {
            return this.currentScene.labels;
        }// end function

    }
}
