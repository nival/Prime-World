package flash.system
{

    [native(cls="SecurityClass", instance="SecurityObject", methods="auto")]
    final public class Security extends Object
    {
        public static const LOCAL_TRUSTED:String = "localTrusted";
        public static const REMOTE:String = "remote";
        public static const LOCAL_WITH_FILE:String = "localWithFile";
        public static const LOCAL_WITH_NETWORK:String = "localWithNetwork";

        public function Security()
        {
            return;
        }// end function

        public static native function showSettings(panel:String = "default") : void;

        public static native function get sandboxType() : String;

        public static native function get exactSettings() : Boolean;

        public static native function set exactSettings(value:Boolean) : void;

        public static native function allowDomain(... args) : void;

        public static native function allowInsecureDomain(... args) : void;

        public static native function loadPolicyFile(url:String) : void;

        public static native function set disableAVM1Loading(value:Boolean) : void;

        public static native function get disableAVM1Loading() : Boolean;

    }
}
