package flash.errors
{

    dynamic public class IllegalOperationError extends Error
    {

        public function IllegalOperationError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
