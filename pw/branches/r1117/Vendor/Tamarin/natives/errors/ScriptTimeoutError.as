package flash.errors
{

    dynamic public class ScriptTimeoutError extends Error
    {

        public function ScriptTimeoutError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
