package flash.net
{

    [native(cls="URLRequestClass", instance="URLRequestObject", methods="auto")]
    final public class URLRequest extends Object
    {

        public function URLRequest(url:String = null)
        {
            if (url != null)
            {
                this.url = url;
            }
            this.requestHeaders = [];
            return;
        }// end function

        private function shouldFilterHTTPHeader(header:String) : Boolean
        {
            return false;
        }// end function

        public native function get method() : String;

        public native function set method(value:String) : void;

        public native function get digest() : String;

        public native function set contentType(value:String) : void;

        public native function set digest(value:String) : void;

        public native function get data() : Object;

        public native function set requestHeaders(value:Array) : void;

        public native function get url() : String;

        public native function set data(value:Object) : void;

        public native function get requestHeaders() : Array;

        public native function get contentType() : String;

        public native function set url(value:String) : void;

    }
}
