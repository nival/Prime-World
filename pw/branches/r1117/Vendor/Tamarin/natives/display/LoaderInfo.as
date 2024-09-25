package flash.display
{
    import flash.events.*;
    import flash.system.*;
    import flash.utils.*;
    import flash.errors.*;

    [native(cls="LoaderInfoClass", instance="LoaderInfoObject", methods="auto")]
    public class LoaderInfo extends EventDispatcher
    {

        public function LoaderInfo()
        {
            return;
        }// end function

        override public function dispatchEvent(event:Event) : Boolean
        {
            Error.throwError(IllegalOperationError, 2118);
            return false;
        }// end function

        private native function _getArgs() : Object;

        public native function get width() : int;

        public native function get height() : int;

        public native function get parentAllowsChild() : Boolean;

        public function get parameters() : Object
        {
            var _loc_3:String = null;
            var _loc_1:* = this._getArgs();
            var _loc_2:Object = {};
            for (_loc_3 in _loc_1)
            {
                
                _loc_2[_loc_3] = _loc_1[_loc_3];
            }
            return _loc_2;
        }// end function

        public native function get bytes() : ByteArray;

        public native function get frameRate() : Number;

        public native function get url() : String;

        public native function get bytesLoaded() : uint;

        public native function get sameDomain() : Boolean;

        public native function get contentType() : String;

        public native function get applicationDomain() : ApplicationDomain;

        public native function get swfVersion() : uint;

        public native function get actionScriptVersion() : uint;

        public native function get bytesTotal() : uint;

        public native function get loader() : Loader;

        public native function get content() : DisplayObject;

        public native function get loaderURL() : String;

        public native function get sharedEvents() : EventDispatcher;

        public native function get childAllowsParent() : Boolean;

        public static native function getLoaderInfoByDefinition(object:Object) : LoaderInfo;

    }
}
