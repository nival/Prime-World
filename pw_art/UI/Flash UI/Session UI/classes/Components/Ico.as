package Components
{

	import flash.display.Loader;
	import flash.display.MovieClip;
	import flash.display.Sprite;

	import flash.events.MouseEvent;

	import flash.net.URLRequest;

	public class Ico extends MovieClip
	{
		private var path:String;

		private var icoCont_sp:Sprite;
		private var ico_sp:Sprite;

		private var ico_ld:Loader;

		private var configPath:String = 'art/general/';

		private var back_mc:Object;

		public function Ico()
		{
			// constructor code
			back_mc = getChildAt(0) as MovieClip;
			//back_mc.visible = false;

			icoCont_sp = new Sprite  ;
			ico_sp = new Sprite  ;

			icoCont_sp.x = back_mc.width / 2;
			icoCont_sp.y = back_mc.height / 2;

			addChild(icoCont_sp);
			icoCont_sp.addChild(ico_sp);

			ico_ld = new Loader  ;
			ico_sp.addChild(ico_ld);

			this.buttonMode = true;

		}
	}
}