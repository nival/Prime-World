package flash.xml
{

    [native(cls="XMLParserClass", instance="XMLParserObject", methods="auto")]
    final class XMLParser extends Object
    {

        function XMLParser()
        {
            return;
        }// end function

        public native function getNext(tag:XMLTag) : int;

        public native function startParse(source:String, ignoreWhite:Boolean) : void;

    }
}
