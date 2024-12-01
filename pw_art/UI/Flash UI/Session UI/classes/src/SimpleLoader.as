package src
{

	import flash.display.Sprite;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;

	public class SimpleLoader extends Sprite
	{
		public var tweenIn:Tween;
		public var tweenOut:Tween;

		public function SimpleLoader(Path:String)
		{

			var myLoader:Loader = new Loader();
			var myURLRequest:URLRequest = new URLRequest(Path);
			myLoader.contentLoaderInfo.addEventListener(Event.INIT,onInit);
			myLoader.load(myURLRequest);


			function onInit(e:Event):void
			{
				addChild(myLoader.content);
				dispatchEvent(new Event("INIT",true));
			}
		}
		public function addTween():void
		{
			tweenIn = new Tween(this,"alpha",Strong.easeOut,0,1,7,false);
			tweenOut = new Tween(this,"alpha",Strong.easeOut,1,0,21,false);

			tweenIn.stop();
			tweenOut.stop();
		}
	}
}