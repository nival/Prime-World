package flash.system
{
    [native(cls="FSCommandClass", instance="FSCommandObject", methods="auto")]
    final class FSCommand extends Object
    {

        function FSCommand()
        {
            return;
        }// end function

        public static native function _fscommand(command:String, args:String) : void;

    }

    public function fscommand(command:String, args:String = "")
    {
      FSCommand._fscommand( command, args );
    }
}
