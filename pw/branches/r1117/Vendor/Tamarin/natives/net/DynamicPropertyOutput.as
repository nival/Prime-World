package flash.net
{

    [native(cls="DynamicPropertyOutputClass", instance="DynamicPropertyOutputObject", methods="auto")]
    class DynamicPropertyOutput extends Object implements IDynamicPropertyOutput
    {

        function DynamicPropertyOutput()
        {
            return;
        }// end function

        public native function writeDynamicProperty(name:String, value) : void;

    }
}
