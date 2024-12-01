package BaseClasses
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.display.Loader;
	import flash.events.MouseEvent;
	
	public class BaseIconLoader extends MovieClip
	{
		public var ico_ld:Loader;
		protected var path:String;
		private var iconIsLoaded:Boolean = false;
		private var iconWidth:Number = -1;
		private var iconHeight:Number=-1;
		protected var _tooltipID:int = -1;
		
		public function BaseIconLoader():void
		{
			if (this.width > 0 && this.height > 0)
			{
				iconWidth = this.width;
				iconHeight = this.height;
			}
			
			var childs:Array  = new Array();
			for (var i:int = 0; i <this.numChildren ; i++) 
			{
				childs.push(this.getChildAt(i) );
			}
			
			for each (var child:DisplayObject in childs) 
			{
				this.removeChild(child)
			}
			
			childs = new Array();
			ico_ld = new Loader();
			ico_ld.contentLoaderInfo.addEventListener( Event.INIT, OnLoaded );
			addChild(ico_ld);
		}
		
		public function SetIcon(_path:String):void
		{
			if (_path == null) return;
			path = _path;
			
		
			if (path.length == 0)
			{
				ico_ld.unload();
				return;
			}

			var myURLRequest:URLRequest = new URLRequest(_path);

			ico_ld.unload();
			ico_ld.load(myURLRequest);
			iconIsLoaded = true;
		}
		
		protected function OnLoaded(e:Event):void
		{
			dispatchEvent(new Event(Event.COMPLETE));
			if (iconWidth != -1 && iconHeight != -1)
			{
				ico_ld.width = iconWidth;
				ico_ld.height = iconHeight;
			}
		}
		
		public function SetIconSize(_width:Number, _height:Number):void
		{
			iconWidth = _width;
			iconHeight = _height;
		}
		
		public function get isFilled():Boolean
		{
			return iconIsLoaded;
		}
		
		public function set Tooltip(tooltipID:int):void
		{
			_tooltipID = tooltipID;
		}
		
		public function get Tooltip():int
		{
			return _tooltipID;
		}

		public function GetInitialWidth():Number
		{
			return iconWidth != -1? iconWidth:0;		
		}
		
		public function GetInitialHeight():Number
		{
			return iconHeight != -1? iconHeight:0;		
		}
		
	}
	
}