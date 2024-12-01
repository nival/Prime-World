package Components
{

	import flash.display.Sprite;
	import flash.display.MovieClip;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;

	import flash.events.MouseEvent;

	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import fl.transitions.TweenEvent;

	public class IcoSample extends MovieClip
	{

		private var TweenXOut:Tween;
		private var TweenYOut:Tween;
		private var TweenXIn:Tween;
		private var TweenYIn:Tween;

		private var path:String;

		private var ico_ld:Loader;
		public var icoCont_sp:Sprite;

		private var configPath:String = 'art/general/';

		public static var _onDown:Boolean;
		
		//reference
		public var back_mc:MovieClip;

		public function IcoSample()
		{
			back_mc.visible = false;
			icoCont_sp = new Sprite  ;
			icoCont_sp.x = back_mc.width / 2;
			icoCont_sp.y = back_mc.height / 2;
			addChild(icoCont_sp);
			
			ico_ld = new Loader  ;

			ico_ld.contentLoaderInfo.addEventListener(Event.INIT, icoInit);
			icoCont_sp.addChild(ico_ld);
			
			this.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT,onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN,onDown);
			this.addEventListener(MouseEvent.MOUSE_UP,onUp);
			this.addEventListener(MouseEvent.DOUBLE_CLICK,onUp);
			this.buttonMode = true;
			this.doubleClickEnabled = true;

			TweenXIn = new Tween(icoCont_sp,"scaleX",Strong.easeOut,0.9,1,7,false);
			TweenYIn = new Tween(icoCont_sp,"scaleY",Strong.easeOut,0.9,1,7,false);
			TweenXOut = new Tween(icoCont_sp,"scaleX",Strong.easeOut,1,0.9,7,false);
			TweenYOut = new Tween(icoCont_sp,"scaleY",Strong.easeOut,1,0.9,7,false);

			TweenXOut.stop();
			TweenYOut.stop();
			TweenXIn.stop();
			TweenYIn.stop();
		}
		private function onOver(e:MouseEvent):void
		{
			dispatchEvent(new Event('Over',true));
		}
		private function onOut(e:MouseEvent):void
		{
			dispatchEvent(new Event('Out', true));
		}
		private function onDown(e:MouseEvent):void
		{
			_onDown = true;
			TweenXIn.stop();
			TweenYIn.stop();

			TweenXOut.start();
			TweenYOut.start();
		}
		private function onUp(e:MouseEvent):void
		{
			if (_onDown)
			{
				TweenXOut.stop();
				TweenYOut.stop();

				TweenXIn.start();
				TweenYIn.start();
				dispatchEvent(new Event('Up',true));
			}
		}
		public function setIcon(_path:String):void
		{
			icons = _path;
		}
		public function set icons(_path:String):void
		{
			path = _path;

			if (path.length == 0)
			{
				ico_ld.unload();
				return;
			}

			var myURLRequest:URLRequest = new URLRequest(_path);

			ico_ld.unload();
			ico_ld.load(myURLRequest);
		}

		public function get icons():String
		{
			return path;
		}

		private function icoInit(e:Event):void
		{
			e.target.content.smoothing = true;

			ico_ld.x =  -  ico_ld.width / 2;
			ico_ld.y =  -  ico_ld.height / 2;

		}
	}
}