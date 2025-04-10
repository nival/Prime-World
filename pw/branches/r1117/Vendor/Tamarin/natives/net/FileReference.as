package flash.net
{
    import flash.events.*;
    import flash.utils.*;

    [native(cls="FileReferenceClass", instance="FileReferenceObject", methods="auto")]
    public class FileReference extends EventDispatcher
    {

        public function FileReference()
        {
            return;
        }// end function

        public native function upload(request:URLRequest, uploadDataFieldName:String = "Filedata", testUpload:Boolean = false) : void;

        private native function _load(dest:ByteArray) : void;

        public function load() : void
        {
            this._load(new ByteArray());
            return;
        }// end function

        public native function get size() : uint;

        public native function get type() : String;

        public native function browse(typeFilter:Array = null) : Boolean;

        public native function get name() : String;

        public native function get creator() : String;

        public native function get creationDate() : Date;

        public native function download(request:URLRequest, defaultFileName:String = null) : void;

        public native function get modificationDate() : Date;

        public native function get data() : ByteArray;

        public native function cancel() : void;

        private native function _save(data:ByteArray, defaultFileName:String) : void;

        public function save(data, defaultFileName:String = null) : void
        {
            var data:* = data;
            var defaultFileName:* = defaultFileName;
            var d:* = new ByteArray();
            if (data == null)
            {
                throw new ArgumentError("data");
            }
            if (data is String)
            {
                d.writeUTFBytes(data as String);
            }
            else if (data is XML)
            {
                d.writeUTFBytes((data as XML).toXMLString());
            }
            else if (data is ByteArray)
            {
                d.writeBytes(data as ByteArray);
            }
            else
            {
                try
                {
                    d.writeUTFBytes(data);
                }
                catch (e:Error)
                {
                    throw new ArgumentError("data");
                }
            }
            d.position = 0;
            if (defaultFileName == null)
            {
                defaultFileName;
            }
            this._save(d, defaultFileName);
            return;
        }// end function

    }
}
