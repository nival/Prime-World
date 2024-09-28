package flash.errors
{

    dynamic public class InvalidSWFError extends Error
    {

        public function InvalidSWFError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
