package flash.errors
{

    dynamic public class EOFError extends IOError
    {

        public function EOFError(message:String = "", id:int = 0)
        {
            super(message, id);
            return;
        }// end function

    }
}
