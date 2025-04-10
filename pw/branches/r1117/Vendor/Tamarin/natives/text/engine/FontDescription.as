package flash.text.engine
{

    [native(cls="FontDescriptionClass", instance="FontDescriptionObject", methods="auto")]
    final public class FontDescription extends Object
    {

        public function FontDescription(fontName:String = "_serif", fontWeight:String = "normal", fontPosture:String = "normal", fontLookup:String = "device", renderingMode:String = "cff", cffHinting:String = "horizontalStem")
        {
            this.fontName = fontName;
            this.fontWeight = fontWeight;
            this.fontPosture = fontPosture;
            this.fontLookup = fontLookup;
            this.renderingMode = renderingMode;
            this.cffHinting = cffHinting;
            return;
        }// end function

        public native function set fontLookup(value:String) : void;

        public native function get fontWeight() : String;

        public native function get fontLookup() : String;

        public native function get locked() : Boolean;

        public native function set fontWeight(value:String) : void;

        public native function get renderingMode() : String;

        public native function set cffHinting(value:String) : void;

        public native function set fontPosture(value:String) : void;

        public native function set fontName(value:String) : void;

        public native function get cffHinting() : String;

        public native function get fontPosture() : String;

        public native function get fontName() : String;

        public native function set locked(value:Boolean) : void;

        public function clone() : FontDescription
        {
            return new FontDescription(this.fontName, this.fontWeight, this.fontPosture, this.fontLookup, this.renderingMode, this.cffHinting);
        }// end function

        public native function set renderingMode(value:String) : void;

        public static native function isFontCompatible(fontName:String, fontWeight:String, fontPosture:String) : Boolean;

    }
}
