package flash.text.engine
{
    import flash.geom.*;

    final public class FontMetrics extends Object
    {
        public var strikethroughThickness:Number;
        public var emBox:Rectangle;
        public var superscriptScale:Number;
        public var strikethroughOffset:Number;
        public var underlineThickness:Number;
        public var subscriptScale:Number;
        public var superscriptOffset:Number;
        public var subscriptOffset:Number;
        public var underlineOffset:Number;

        public function FontMetrics(emBox:Rectangle, strikethroughOffset:Number, strikethroughThickness:Number, underlineOffset:Number, underlineThickness:Number, subscriptOffset:Number, subscriptScale:Number, superscriptOffset:Number, superscriptScale:Number)
        {
            this.emBox = emBox;
            this.strikethroughOffset = strikethroughOffset;
            this.strikethroughThickness = strikethroughThickness;
            this.underlineOffset = underlineOffset;
            this.underlineThickness = underlineThickness;
            this.subscriptOffset = subscriptOffset;
            this.subscriptScale = subscriptScale;
            this.superscriptOffset = superscriptOffset;
            this.superscriptScale = superscriptScale;
            return;
        }// end function

    }
}
