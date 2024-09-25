package flash.text.engine
{
    import flash.display.*;
    import flash.events.*;

    [native(cls="GraphicElementClass", instance="GraphicElementObject", methods="auto")]
    final public class GraphicElement extends ContentElement
    {

        public function GraphicElement(graphic:DisplayObject = null, elementWidth:Number = 15, elementHeight:Number = 15, elementFormat:ElementFormat = null, eventMirror:EventDispatcher = null, textRotation:String = "rotate0")
        {
            super(elementFormat, eventMirror, textRotation);
            this.elementWidth = elementWidth;
            this.elementHeight = elementHeight;
            this.graphic = graphic;
            return;
        }// end function

        public native function set graphic(value:DisplayObject) : void;

        public native function get elementHeight() : Number;

        public native function set elementWidth(value:Number) : void;

        public native function set elementHeight(value:Number) : void;

        public native function get graphic() : DisplayObject;

        public native function get elementWidth() : Number;

    }
}
