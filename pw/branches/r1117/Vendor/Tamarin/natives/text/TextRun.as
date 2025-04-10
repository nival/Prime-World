package flash.text
{

    public class TextRun extends Object
    {
        public var textFormat:TextFormat;
        public var endIndex:int;
        public var beginIndex:int;

        public function TextRun(beginIndex:int, endIndex:int, textFormat:TextFormat)
        {
            this.beginIndex = beginIndex;
            this.endIndex = endIndex;
            this.textFormat = textFormat;
            return;
        }// end function

    }
}
