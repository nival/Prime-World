package flash.display
{

    [native(cls="BitmapClass", instance="BitmapObject", methods="auto")]
    public class Bitmap extends DisplayObject
    {

        public function Bitmap(bitmapData:BitmapData = null, pixelSnapping:String = "auto", smoothing:Boolean = false)
        {
          _Init( bitmapData, pixelSnapping, smoothing);
        }

	      private native function _Init(bitmapData:BitmapData = null, pixelSnapping:String = "auto", smoothing:Boolean = false): void;
	
        public native function set bitmapData(value:BitmapData) : void;

        public native function get pixelSnapping() : String;

        public native function set pixelSnapping(value:String) : void;

        public native function set smoothing(value:Boolean) : void;

        public native function get bitmapData() : BitmapData;

        public native function get smoothing() : Boolean;

    }
}
