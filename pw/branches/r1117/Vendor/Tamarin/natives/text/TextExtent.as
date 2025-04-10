package flash.text
{

    public class TextExtent extends Object
    {
        public var ascent:Number;
        public var width:Number;
        public var height:Number;
        public var textFieldWidth:Number;
        public var descent:Number;
        public var textFieldHeight:Number;

        public function TextExtent(width:Number, height:Number, textFieldWidth:Number, textFieldHeight:Number, ascent:Number, descent:Number)
        {
            this.width = width;
            this.height = height;
            this.textFieldWidth = textFieldWidth;
            this.textFieldHeight = textFieldHeight;
            this.ascent = ascent;
            this.descent = descent;
            return;
        }// end function

    }
}
