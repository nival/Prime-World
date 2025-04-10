package flash.text
{

    [native(cls="FontClass", instance="FontObject", methods="auto")]
    public class Font extends Object
    {

        public function Font()
        {
            return;
        }// end function

        public native function get fontType() : String;

        public native function get fontStyle() : String;

        public native function get fontName() : String;

        public native function hasGlyphs(str:String) : Boolean;

        public static native function enumerateFonts(enumerateDeviceFonts:Boolean = false) : Array;

        public static native function registerFont(font:Class) : void;

    }
}
