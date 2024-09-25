package flash.text.engine
{

    [native(cls="ElementFormatClass", instance="ElementFormatObject", methods="auto")]
    final public class ElementFormat extends Object
    {

        public function ElementFormat(fontDescription:FontDescription = null, fontSize:Number = 12, color:uint = 0, alpha:Number = 1, textRotation:String = "auto", dominantBaseline:String = "roman", alignmentBaseline:String = "useDominantBaseline", baselineShift:Number = 0, kerning:String = "on", trackingRight:Number = 0, trackingLeft:Number = 0, locale:String = "en", breakOpportunity:String = "auto", digitCase:String = "default", digitWidth:String = "default", ligatureLevel:String = "common", typographicCase:String = "default")
        {
            this.fontDescription = fontDescription ? (fontDescription) : (new FontDescription());
            this.fontSize = fontSize;
            this.color = color;
            this.alpha = alpha;
            this.textRotation = textRotation;
            this.dominantBaseline = dominantBaseline;
            this.alignmentBaseline = alignmentBaseline;
            this.baselineShift = baselineShift;
            this.kerning = kerning;
            this.trackingRight = trackingRight;
            this.trackingLeft = trackingLeft;
            this.locale = locale;
            this.breakOpportunity = breakOpportunity;
            this.digitCase = digitCase;
            this.digitWidth = digitWidth;
            this.ligatureLevel = ligatureLevel;
            this.typographicCase = typographicCase;
            return;
        }// end function

        public native function set baselineShift(value:Number) : void;

        public native function set trackingLeft(value:Number) : void;

        public native function get baselineShift() : Number;

        public native function get dominantBaseline() : String;

        public native function set color(value:uint) : void;

        public native function get alignmentBaseline() : String;

        public native function set dominantBaseline(dominantBaseline:String) : void;

        public native function get textRotation() : String;

        public native function get kerning() : String;

        public native function set alignmentBaseline(alignmentBaseline:String) : void;

        public native function set trackingRight(value:Number) : void;

        public native function get breakOpportunity() : String;

        public native function set textRotation(value:String) : void;

        public native function set kerning(value:String) : void;

        public native function get digitWidth() : String;

        public native function set fontDescription(value:FontDescription) : void;

        public native function set locked(value:Boolean) : void;

        public function clone() : ElementFormat
        {
            return new ElementFormat(this.fontDescription ? (this.fontDescription.clone()) : (null), this.fontSize, this.color, this.alpha, this.textRotation, this.dominantBaseline, this.alignmentBaseline, this.baselineShift, this.kerning, this.trackingRight, this.trackingLeft, this.locale, this.breakOpportunity, this.digitCase, this.digitWidth, this.ligatureLevel, this.typographicCase);
        }// end function

        public native function get alpha() : Number;

        public native function set ligatureLevel(ligatureLevelType:String) : void;

        public native function set fontSize(value:Number) : void;

        public native function get locale() : String;

        public native function get locked() : Boolean;

        public native function get color() : uint;

        public native function get trackingRight() : Number;

        public native function set breakOpportunity(opportunityType:String) : void;

        public native function get fontDescription() : FontDescription;

        public native function set typographicCase(typographicCaseType:String) : void;

        public native function get fontSize() : Number;

        public native function set digitWidth(digitWidthType:String) : void;

        public native function set locale(value:String) : void;

        public native function get trackingLeft() : Number;

        public native function get ligatureLevel() : String;

        public native function set digitCase(digitCaseType:String) : void;

        public native function get typographicCase() : String;

        public native function set alpha(value:Number) : void;

        public native function get digitCase() : String;

        public native function getFontMetrics() : FontMetrics;

    }
}
