package flash.net
{
    import flash.events.*;

    [native(cls="LocalConnectionClass", instance="LocalConnectionObject", methods="auto")]
    public class LocalConnection extends EventDispatcher
    {

        public function LocalConnection()
        {
            return;
        }// end function

        public native function get domain() : String;

        public native function set client(client:Object) : void;

        public native function close() : void;

        public native function allowInsecureDomain(... args) : void;

        public native function connect(connectionName:String) : void;

        public native function get client() : Object;

        public native function allowDomain(... args) : void;

        public native function send(connectionName:String, methodName:String, ... args) : void;

    }
}
