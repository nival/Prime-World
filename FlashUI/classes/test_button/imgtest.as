package  {
	
	import flash.display.Loader;
	import flash.display.MovieClip;
	import flash.net.URLRequest;
	import flash.events.Event;	
	
	public class imgtest extends MovieClip{
		
		private var clipHeight:Number;
		private var clipWidth: Number;
		public var Stretch2Fit:String = "растягиваем";
		public var OriginalSize:String = "сохраняем размер";
		public var Stretch: String;
		public var imgldr:Loader = new Loader();		
		
		public function imgtest() 
		{
			clipHeigh = this.height;
			clipWidth = this.width;
			
			addChild(imgldr);
			imgldr.contentLoaderInfo.addEventListener(Event.COMPLETE, OnImageLoaded);
		}
		
		private function OnImageLoaded(evt:Event): void 
		{
			if (Stretch == Stretch2Fit) 
			{
				imgldr.height = clipHeight;
				imgldr.width = clipWidth;
			}
		}
		
		public function SetImage(ldrname:String): void 
		{
			var url:URLRequest = new URLRequest (ldrname);
			imgldr.load(url);
		}
	}
	
}
