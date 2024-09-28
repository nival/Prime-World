package flash.display
{
    import flash.utils.*;

    [native(cls="AVM1MovieClass", instance="AVM1MovieObject", methods="auto")]
    public class AVM1Movie extends DisplayObject
    {
        private var callbackTable:Object;

        public function AVM1Movie()
        {
            this.callbackTable = {};
            this._setCallAS3(this._callAS3);
            return;
        }// end function

        private native function _setCallAS3(closure:Function) : void;

        private function _callAS3(functionName:String, data:ByteArray) : void
        {
            var _loc_3:* = this.callbackTable[functionName];
            if (_loc_3 == null)
            {
                Error.throwError(Error, 2133, functionName);
            }
            var _loc_4:* = data.readObject();
            var _loc_5:* = _loc_3.apply(null, _loc_4);
            data.position = 0;
            data.length = 0;
            data.writeObject(_loc_5);
            return;
        }// end function

        public function addCallback(functionName:String, closure:Function) : void
        {
            if (!this._interopAvailable)
            {
                Error.throwError(IllegalOperationError, 2014);
            }
            this.callbackTable[functionName] = closure;
            return;
        }// end function

        private native function _callAS2(functionName:String, arguments:ByteArray) : ByteArray;

        private native function get _interopAvailable() : Boolean;

        public function call(functionName:String, ... args)
        {
            if (!this._interopAvailable)
            {
                Error.throwError(IllegalOperationError, 2014);
            }
            args = new ByteArray();
            args.objectEncoding = ObjectEncoding.AMF0;
            args.writeObject(args);
            this._callAS2(functionName, args);
            return args.length ? (args.readObject()) : (null);
        }// end function

    }
}
