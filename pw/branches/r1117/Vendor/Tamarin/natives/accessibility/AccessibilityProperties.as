package flash.accessibility
{

    public class AccessibilityProperties extends Object
    {
        public var shortcut:String;
        public var name:String;
        public var silent:Boolean;
        public var description:String;
        public var forceSimple:Boolean;
        public var noAutoLabeling:Boolean;

        public function AccessibilityProperties()
        {
            this.name = "";
            this.description = "";
            this.shortcut = "";
            this.silent = false;
            this.forceSimple = false;
            this.noAutoLabeling = false;
            return;
        }// end function

    }
}
