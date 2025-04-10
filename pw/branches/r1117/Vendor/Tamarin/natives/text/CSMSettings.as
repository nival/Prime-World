package flash.text
{

    final public class CSMSettings extends Object
    {
        public var fontSize:Number;
        public var outsideCutoff:Number;
        public var insideCutoff:Number;

        public function CSMSettings(fontSize:Number, insideCutoff:Number, outsideCutoff:Number)
        {
            this.fontSize = fontSize;
            this.insideCutoff = insideCutoff;
            this.outsideCutoff = outsideCutoff;
            return;
        }// end function

    }
}
