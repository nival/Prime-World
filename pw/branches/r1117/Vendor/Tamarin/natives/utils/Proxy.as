package flash.utils
{

    [native(cls="ProxyClass", instance="ProxyObject", methods="auto")]
    public class Proxy extends Object
    {

        public function Proxy()
        {
            return;
        }// end function

        function deleteProperty(name) : Boolean
        {
            Error.throwError(IllegalOperationError, 2092);
            return null;
        }// end function

        native function isAttribute(name) : Boolean;

        function callProperty(name, ... args)
        {
            Error.throwError(IllegalOperationError, 2090);
            return null;
        }// end function

        function nextNameIndex(index:int) : int
        {
            Error.throwError(IllegalOperationError, 2105);
            return null;
        }// end function

        function nextName(index:int) : String
        {
            Error.throwError(IllegalOperationError, 2106);
            return null;
        }// end function

        function getDescendants(name)
        {
            Error.throwError(IllegalOperationError, 2093);
            return null;
        }// end function

        function getProperty(name)
        {
            Error.throwError(IllegalOperationError, 2088);
            return;
        }// end function

        function nextValue(index:int)
        {
            Error.throwError(IllegalOperationError, 2107);
            return null;
        }// end function

        function setProperty(name, value) : void
        {
            Error.throwError(IllegalOperationError, 2089);
            return;
        }// end function

        function hasProperty(name) : Boolean
        {
            Error.throwError(IllegalOperationError, 2091);
            return null;
        }// end function

    }
}
