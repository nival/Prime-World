package flash.errors
{

    dynamic public class StackOverflowError extends Error
    {

        public function StackOverflowError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
