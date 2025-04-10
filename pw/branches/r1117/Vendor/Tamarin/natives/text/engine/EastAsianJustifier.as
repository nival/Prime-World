package flash.text.engine
{

    [native(cls="EastAsianJustifierClass", instance="EastAsianJustifierObject", methods="auto")]
    final public class EastAsianJustifier extends TextJustifier
    {

        public function EastAsianJustifier(locale:String = "ja", lineJustification:String = "allButLast", justificationStyle:String = "pushInKinsoku")
        {
            super(locale, lineJustification);
            this.justificationStyle = justificationStyle;
            return;
        }// end function

        override public function clone() : TextJustifier
        {
            return new EastAsianJustifier(this.locale, this.lineJustification, this.justificationStyle);
        }// end function

        public native function set justificationStyle(value:String) : void;

        public native function get justificationStyle() : String;

    }
}
