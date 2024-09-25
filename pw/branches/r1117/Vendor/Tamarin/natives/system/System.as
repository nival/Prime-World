package flash.system
{

    [native(cls="SystemClass", instance="SystemObject", methods="auto")]
    final public class System extends Object
    {
        private static var theIME:IME = null;

        public function System()
        {
            return;
        }// end function

        public static function get ime() : IME
        {
            if (!theIME)
            {
                IME.constructOK = true;
                theIME = new IME();
                IME.constructOK = false;
            }
            return theIME;
        }// end function

        public static native function get useCodePage() : Boolean;

        public static native function get totalMemory() : uint;

        public static native function set useCodePage(value:Boolean) : void;

        public static native function get vmVersion() : String;

        public static native function resume() : void;

        public static native function setClipboard(string:String) : void;

        public static native function pause() : void;

        public static native function gc() : void;

        public static native function exit(code:uint) : void;

    }
}
