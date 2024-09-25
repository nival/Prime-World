package flash.text
{
    import flash.display.*;

    [native(cls="StaticTextClass", instance="StaticTextObject", methods="auto")]
    final public class StaticText extends DisplayObject
    {

        public function StaticText()
        {
            return;
        }// end function

        public native function get text() : String;

    }
}
