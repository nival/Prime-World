package flash.text
{

    [native(cls="TextRendererClass", instance="TextRendererObject", methods="auto")]
    final public class TextRenderer extends Object
    {

        public function TextRenderer()
        {
            return;
        }// end function

        public static native function set maxLevel(value:int) : void;

        public static native function get displayMode() : String;

        public static native function setAdvancedAntiAliasingTable(fontName:String, fontStyle:String, colorType:String, advancedAntiAliasingTable:Array) : void;

        public static native function get maxLevel() : int;

        public static native function get antiAliasType() : String;

        public static native function set displayMode(value:String) : void;

        public static native function set antiAliasType(value:String) : void;

    }
}
