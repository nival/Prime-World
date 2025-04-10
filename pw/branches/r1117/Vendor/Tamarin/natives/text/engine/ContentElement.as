package flash.text.engine
{
    import flash.events.*;

    [native(cls="ContentElementClass", instance="ContentElementObject", methods="auto")]
    public class ContentElement extends Object
    {
        public var userData:Object;
        public static const GRAPHIC_ELEMENT:uint = 65007;

        public function ContentElement(elementFormat:ElementFormat = null, eventMirror:EventDispatcher = null, textRotation:String = "rotate0")
        {
            if (getQualifiedClassName(this) == "flash.text.engine::ContentElement")
            {
                Error.throwError(ArgumentError, 2012, "ContentElement");
            }
            this.elementFormat = elementFormat;
            this.eventMirror = eventMirror;
            this.textRotation = textRotation;
            return;
        }// end function

        public native function get textBlock() : TextBlock;

        public native function set elementFormat(value:ElementFormat) : void;

        public native function get textBlockBeginIndex() : int;

        public native function get textRotation() : String;

        public native function get text() : String;

        public native function set eventMirror(value:EventDispatcher) : void;

        public native function get elementFormat() : ElementFormat;

        public native function set textRotation(value:String) : void;

        public native function get eventMirror() : EventDispatcher;

        public native function get rawText() : String;

        public native function get groupElement() : GroupElement;

    }
}
