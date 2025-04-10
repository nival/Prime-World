package flash.text.engine
{

    [native(cls="SpaceJustifierClass", instance="SpaceJustifierObject", methods="auto")]
    final public class SpaceJustifier extends TextJustifier
    {

        public function SpaceJustifier(locale:String = "en", lineJustification:String = "unjustified", letterSpacing:Boolean = false)
        {
            super(locale, lineJustification);
            this.letterSpacing = letterSpacing;
            return;
        }// end function

        public native function set letterSpacing(value:Boolean) : void;

        override public function clone() : TextJustifier
        {
            return new SpaceJustifier(this.locale, this.lineJustification, this.letterSpacing);
        }// end function

        public native function get letterSpacing() : Boolean;

    }
}
