package flash.net
{

    public interface IDynamicPropertyWriter
    {

        public function IDynamicPropertyWriter();

        function writeDynamicProperties(obj:Object, output:IDynamicPropertyOutput) : void;

    }
}
