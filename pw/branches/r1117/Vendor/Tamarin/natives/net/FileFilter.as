package flash.net
{

    [native(cls="FileFilterClass", instance="FileFilterObject", methods="auto")]
    final public class FileFilter extends Object
    {

        public function FileFilter(description:String, extension:String, macType:String = null)
        {
            this.description = description;
            this.extension = extension;
            this.macType = macType;
            return;
        }// end function

        public native function set macType(value:String) : void;

        public native function set description(value:String) : void;

        public native function get macType() : String;

        public native function get description() : String;

        public native function set extension(value:String) : void;

        public native function get extension() : String;

    }
}
