package flash.text.engine
{
    import flash.events.*;
    import flash.geom.*;

    [native(cls="TextLineMirrorRegionClass", instance="TextLineMirrorRegionObject", methods="auto")]
    final public class TextLineMirrorRegion extends Object
    {

        public function TextLineMirrorRegion()
        {
            return;
        }// end function

        public native function get textLine() : TextLine;

        public native function get bounds() : Rectangle;

        public native function get nextRegion() : TextLineMirrorRegion;

        public native function get previousRegion() : TextLineMirrorRegion;

        public native function get element() : ContentElement;

        public native function get mirror() : EventDispatcher;

    }
}
