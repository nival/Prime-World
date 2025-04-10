package flash.text
{

    public class TextLineMetrics extends Object
    {
        public var ascent:Number;
        public var width:Number;
        public var height:Number;
        public var leading:Number;
        public var x:Number;
        public var descent:Number;

        public function TextLineMetrics(x:Number, width:Number, height:Number, ascent:Number, descent:Number, leading:Number)
        {
            this.x = x;
            this.width = width;
            this.height = height;
            this.ascent = ascent;
            this.descent = descent;
            this.leading = leading;
            return;
        }// end function

    }
}
