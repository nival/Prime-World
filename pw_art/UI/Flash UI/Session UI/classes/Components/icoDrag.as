package Components
{

	import flash.display.MovieClip;

	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;


	public class icoDrag extends MovieClip
	{

		private var ico_ld:Loader;

		public function icoDrag()
		{
			this.mouseEnabled = false;
			this.mouseChildren = false;
			// constructor code
			ico_ld = new Loader  ;
			ico_ld.contentLoaderInfo.addEventListener(Event.INIT,icoInit);
			addChild(ico_ld)

		}
		public function setIco(path:String):void
		{
			if (path.length == 0)
			{
				ico_ld.unload();
				return;
			}
			else
			{
				var myURLRequest:URLRequest = new URLRequest(path);

				ico_ld.unload();
				ico_ld.load(myURLRequest);
			}
			this.parent.setChildIndex(this, this.parent.numChildren - 1);
		}
		private function icoInit(e:Event):void {
			
			e.target.content.smoothing = true;
			this.width = 54;
			this.height = 54;
			ico_ld.x = -27;
			ico_ld.y = -27;
		}
	}
}