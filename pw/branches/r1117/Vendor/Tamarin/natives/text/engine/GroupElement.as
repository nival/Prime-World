package flash.text.engine
{
    import __AS3__.vec.*;
    import flash.events.*;

    [native(cls="GroupElementClass", instance="GroupElementObject", methods="auto")]
    final public class GroupElement extends ContentElement
    {

        public function GroupElement(elements:Vector.<ContentElement> = null, elementFormat:ElementFormat = null, eventMirror:EventDispatcher = null, textRotation:String = "rotate0")
        {
            super(elementFormat, eventMirror, textRotation);
            this.setElements(elements);
            return;
        }// end function

        public native function getElementAt(index:int) : ContentElement;

        public native function getElementAtCharIndex(charIndex:int) : ContentElement;

        public native function get elementCount() : int;

        public function getElementIndex(element:ContentElement) : int
        {
            var _loc_2:int = 0;
            while (_loc_2 < this.elementCount)
            {
                
                if (element == this.getElementAt(_loc_2))
                {
                    return _loc_2;
                }
                _loc_2 = _loc_2 + 1;
            }
            return -1;
        }// end function

        public native function splitTextElement(elementIndex:int, splitIndex:int) : TextElement;

        public native function groupElements(beginIndex:int, endIndex:int) : GroupElement;

        public native function setElements(value:Vector.<ContentElement>) : void;

        public native function replaceElements(beginIndex:int, endIndex:int, newElements:Vector.<ContentElement>) : Vector.<ContentElement>;

        public native function mergeTextElements(beginIndex:int, endIndex:int) : TextElement;

        public native function ungroupElements(groupIndex:int) : void;

    }
}
