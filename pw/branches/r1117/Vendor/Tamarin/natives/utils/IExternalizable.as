package flash.utils
{

    public interface IExternalizable
    {

        public function IExternalizable();

        function readExternal(input:IDataInput) : void;

        function writeExternal(output:IDataOutput) : void;

    }
}
