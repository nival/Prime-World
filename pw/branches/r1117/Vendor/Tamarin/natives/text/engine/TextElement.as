package flash.text.engine
{
    import flash.events.*;

    [native(cls="TextElementClass", instance="TextElementObject", methods="auto")]
    final public class TextElement extends ContentElement
    {

        public function TextElement(text:String = null, elementFormat:ElementFormat = null, eventMirror:EventDispatcher = null, textRotation:String = "rotate0")
        {
            super(elementFormat, eventMirror, textRotation);
            this.text = text;
            return;
        }// end function

        public native function replaceText(beginIndex:int, endIndex:int, newText:String) : void;

        public native function set text(value:String) : void;

    }
}
