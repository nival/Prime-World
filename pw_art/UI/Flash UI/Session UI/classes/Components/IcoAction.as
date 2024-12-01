package Components
{
	import flash.display.DisplayObject;
	import flash.display.Loader;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.net.URLRequest;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	
	import src.Desaturate;

	public class IcoAction extends MovieClip
	{
		public var path:String='';
		public const type:String = 'action'

		private var ico_ld:Loader;
		
		private var TweenXOut:Tween;
		private var TweenYOut:Tween;
		private var TweenXIn:Tween;
		private var TweenYIn:Tween;

		private const Width:Number = 50;
		private const Height:Number = 50;
		private var myURLRequest:URLRequest;
		public function IcoAction()
		{
			ico_ld = new Loader  ;
			ico_ld.x =  -  Width / 2;//ширина кнопки в Шоп баре
			ico_ld.y =  -  Height / 2;
			ico_ld.contentLoaderInfo.addEventListener(Event.INIT,icoInit);
			addChild(ico_ld);
			

			TweenXIn = new Tween(this,"scaleX",Strong.easeOut,0.9,1,7,false);
			TweenYIn = new Tween(this,"scaleY",Strong.easeOut,0.9,1,7,false);
			TweenXOut = new Tween(this,"scaleX",Strong.easeOut,1,0.9,7,false);
			TweenYOut = new Tween(this,"scaleY",Strong.easeOut,1,0.9,7,false);
			TweenXOut.stop();
			TweenYOut.stop();
			TweenXIn.stop();
			TweenYIn.stop();
			
			//ico = 'art/ico/Talents/01.png';//для теста первая иконка
		}
		
		public function onDown()
		{
			TweenXIn.stop();
			TweenYIn.stop();
			TweenXOut.start();
			TweenYOut.start();
		}
		
		public function onUp()
		{
			TweenXOut.stop();
			TweenYOut.stop();
			TweenXIn.start();
			TweenYIn.start();
		}
		
		public function set ico(_path:String):void
		{
			path = _path;
			
			ico_ld.unload();
			
			if (path.length == 0)
			{
				ico_ld.visible = false;
				return;
			}
			else
			{
				myURLRequest = new URLRequest(_path);
				ico_ld.load(myURLRequest);
			}
		}
		
		private	function icoInit(e:Event):void
		{
			var bitmap = e.target.content;
			bitmap.smoothing = true;
			bitmap.width = Width;
			bitmap.height = Height;
			ico_ld.visible = true;
		}
		
		public function get ico():String
		{
			return path;
		}
		public function disable()
		{
			Desaturate.desaturate(this);
		}
		public function enable()
		{
			Desaturate.saturate(this);
		}
	}
}