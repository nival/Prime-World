package flash.text.engine
{

    [native(cls="TabStopClass", instance="TabStopObject", methods="auto")]
    final public class TabStop extends Object
    {

        public function TabStop(alignment:String = "start", position:Number = 0, decimalAlignmentToken:String = "")
        {
            this.alignment = alignment;
            this.position = position;
            this.decimalAlignmentToken = decimalAlignmentToken;
            return;
        }// end function

        public native function set position(value:Number) : void;

        public native function get alignment() : String;

        public native function set alignment(value:String) : void;

        public native function get decimalAlignmentToken() : String;

        public native function get position() : Number;

        public native function set decimalAlignmentToken(value:String) : void;

    }
}
