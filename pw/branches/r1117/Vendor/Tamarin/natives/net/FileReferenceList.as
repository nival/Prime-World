package flash.net
{
    import flash.events.*;

    [native(cls="FileReferenceListClass", instance="FileReferenceListObject", methods="auto")]
    public class FileReferenceList extends EventDispatcher
    {

        public function FileReferenceList()
        {
            return;
        }// end function

        public native function browse(typeFilter:Array = null) : Boolean;

        public native function get fileList() : Array;

    }
}
