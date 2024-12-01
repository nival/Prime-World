package  StatisticBars{
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.utils.getDefinitionByName;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	
	import flash.display.Loader;
	import flash.net.URLRequest;
	import flash.events.Event;
	
	public class Titles extends MovieClip 
	{
		private var image:Loader;
		protected var _tooltipID:int=-1;
		public var badge_mc:MovieClip;
		private var animate:Boolean = true;
		
		public function Titles() 
		{
			this.visible = false;
			this.stop();
			this.mouseEnabled  = false;
			badge_mc.addEventListener(MouseEvent.MOUSE_OVER, OnOver);
			badge_mc.addEventListener(MouseEvent.MOUSE_OUT, OnOut);
			
			image = new Loader();
			image.contentLoaderInfo.addEventListener(Event.INIT, imageInit);
			badge_mc.addChild(image);
		}
		
		public function SetImage(_img:String,animated:Boolean=true):void
		{
			if(_img == null||_img.length == 0)return;
			animate = animated;
			
			image.load(new URLRequest(_img));	
		}
		
		private function imageInit(e:Event):void
		{
			this.visible = true;
			
			if (animate)
				this.play();
			else
				this.gotoAndStop(this.totalFrames);
		}
		
		protected function OnOver(e:MouseEvent):void
		{
			if (_tooltipID == -1) return;
			
			FSCommands.Send(FSCommands.TITLE_TOOLTIP, FSCommands.TOOLTIP_SHOW+ _tooltipID);
		}
		
		protected function OnOut(e:MouseEvent):void
		{
			if (_tooltipID == -1) return;
			
			FSCommands.Send(FSCommands.TITLE_TOOLTIP, FSCommands.TOOLTIP_HIDE+ _tooltipID);
		}
		
		
		public function set Tooltip(tooltipID:int):void
		{
			_tooltipID = tooltipID;
		}
		
		public function get Tooltip():int
		{
			return _tooltipID;
		}
		
				
		public function StopAnimation():void 
		{
			this.visible = false;
			this.gotoAndStop(1);
		}
	}
}
