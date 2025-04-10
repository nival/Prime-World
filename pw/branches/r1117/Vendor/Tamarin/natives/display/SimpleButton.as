package flash.display
{
    import flash.media.*;

    [native(cls="SimpleButtonClass", instance="SimpleButtonObject", methods="auto")]
    public class SimpleButton extends InteractiveObject
    {

        public function SimpleButton(upState:DisplayObject = null, overState:DisplayObject = null, downState:DisplayObject = null, hitTestState:DisplayObject = null)
        {
            if (upState)
            {
                this.upState = upState;
            }
            if (overState)
            {
                this.overState = overState;
            }
            if (downState)
            {
                this.downState = downState;
            }
            if (hitTestState)
            {
                this.hitTestState = hitTestState;
            }
            this._updateButton();
            return;
        }// end function

        public native function get enabled() : Boolean;

        public native function set enabled(value:Boolean) : void;

        public native function get hitTestState() : DisplayObject;

        public native function set hitTestState(value:DisplayObject) : void;

        private native function _updateButton() : void;

        public native function set upState(value:DisplayObject) : void;

        public native function get downState() : DisplayObject;

        public native function set soundTransform(sndTransform:SoundTransform) : void;

        public native function get soundTransform() : SoundTransform;

        public native function get upState() : DisplayObject;

        public native function set useHandCursor(value:Boolean) : void;

        public native function set overState(value:DisplayObject) : void;

        public native function get useHandCursor() : Boolean;

        public native function get trackAsMenu() : Boolean;

        public native function get overState() : DisplayObject;

        public native function set downState(value:DisplayObject) : void;

        public native function set trackAsMenu(value:Boolean) : void;

    }
}
