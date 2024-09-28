package flash.system
{
    import flash.events.*;

    [native(cls="IMEClass", instance="IMEObject", methods="auto")]
    final public class IME extends EventDispatcher
    {

        public function IME()
        {
            return;
        }// end function

        public static native function setCompositionString(composition:String) : void;

        public static native function get enabled() : Boolean;

        public static native function set conversionMode(mode:String) : void;

        public static native function set constructOK(construct:Boolean) : void;

        public static native function doConversion() : void;

        public static native function get conversionMode() : String;

        public static native function set enabled(enabled:Boolean) : void;

    }
}
