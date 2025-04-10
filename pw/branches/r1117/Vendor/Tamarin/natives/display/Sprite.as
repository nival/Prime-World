package flash.display
{
    import flash.geom.*;
    import flash.media.*;

    [native(cls="SpriteClass", instance="SpriteObject", methods="auto")]
    public class Sprite extends DisplayObjectContainer
    {

        public function Sprite()
        {
            this.constructChildren();
            return;
        }// end function

        public native function get dropTarget() : DisplayObject;

        public native function get soundTransform() : SoundTransform;

        private native function constructChildren() : void;

        public native function get hitArea() : Sprite;

        public native function set buttonMode(value:Boolean) : void;

        public native function get graphics() : Graphics;

        public native function get useHandCursor() : Boolean;

        public native function set hitArea(value:Sprite) : void;

        public native function get buttonMode() : Boolean;

        public native function stopDrag() : void;

        public native function set useHandCursor(value:Boolean) : void;

        public native function set soundTransform(sndTransform:SoundTransform) : void;

        public native function startDrag(lockCenter:Boolean = false, bounds:Rectangle = null) : void;

    }
}
