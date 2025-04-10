package flash.xml
{

    [native(cls="XMLTagClass", instance="XMLTagObject", methods="auto")]
    final class XMLTag extends Object
    {

        function XMLTag()
        {
            return;
        }// end function

        public native function get value() : String;

        public native function set value(v:String) : void;

        public native function set type(value:uint) : void;

        public native function get type() : uint;

        public native function set empty(value:Boolean) : void;

        public native function set attrs(value:Object) : void;

        public native function get empty() : Boolean;

        public native function get attrs() : Object;

    }
}
