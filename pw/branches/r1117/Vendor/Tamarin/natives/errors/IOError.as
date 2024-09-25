package flash.errors
{

    dynamic public class IOError extends Error
    {

        public function IOError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
