package flash.errors
{

    dynamic public class MemoryError extends Error
    {

        public function MemoryError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
