package flash.net
{

    final public class URLRequestHeader extends Object
    {
        public var value:String;
        public var name:String;

        public function URLRequestHeader(name:String = "", value:String = "")
        {
            this.name = name;
            this.value = value;
            return;
        }// end function

    }
}
