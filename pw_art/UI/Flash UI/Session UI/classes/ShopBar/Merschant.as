package ShopBar
{

	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.utils.setInterval;
	import flash.utils.clearInterval;

	public class Merschant extends MovieClip
	{

		private var myInt:Number;
		private var chance:Number;

		//reference
		public var head_mc:MovieClip;
		public var light:MovieClip;
		public var bottle_mc:MovieClip;

		public function Merschant()
		{
			myInt = setInterval(tick,3000);
		}
		private function tick():void
		{
			chance = Math.random() * 10;

			if (chance >= 6)
			{
				this.play();
			}
			if (chance > 4)
			{
				head_mc.eyeLids_mc.play();
			}
		}
	}
}