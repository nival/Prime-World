package  {
	
	import flash.display.DisplayObject;
	import flash.display.Loader;
	import flash.display.MovieClip;
	import flash.net.URLRequest;
	import flash.events.Event;
	
	public class ImgLoader extends MovieClip {

		public const StretchToFit:String = "Растягиваем под размер мувиклипа";
		public const SetOriginalSize:String = "Оставляем оригинальный размер";
		public var imgldr:Loader = new Loader();		
		private var clipWidth:Number;
		private var clipHeight:Number;		
		public var Stretch:String;
		
		public function ImgLoader() 
		{
			clipWidth = this.width;
			clipHeight = this.height;
			
			var child:DisplayObject = this.getChildAt(0);
			
			if (child!=null)
				this.removeChild(child);
			
			addChild(imgldr);
			imgldr.contentLoaderInfo.addEventListener(Event.COMPLETE, OnImgLoaded);		
		}
		
		private function OnImgLoaded(evt:Event):void
		{
			if(Stretch==StretchToFit)
			{
				imgldr.width = clipWidth;
				imgldr.height = clipHeight;
			}
		}
		
		public function SetImage(path:String):void
		{
			var url:URLRequest = new URLRequest(path);
			imgldr.load(url);
		}
	}	
}
