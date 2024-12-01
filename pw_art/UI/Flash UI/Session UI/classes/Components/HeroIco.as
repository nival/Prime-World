package Components
{
	import flash.events.Event;
	import BaseClasses.BaseIconLoader;
	public class HeroIco extends BaseIconLoader
	{
		
		private var parentWidth: Number;
		private var parentHeight: Number;

		override public function SetIcon(_path:String):void 
		{
			if ( parent != null )
			{
				parentWidth = parent.getChildByName("roundFrame").width;
				parentHeight = parent.getChildByName("roundFrame").height;
			}
			
			super.SetIcon(_path);
		}
		
		override protected function OnLoaded(e:Event):void 
		{
			ico_ld.width = parentWidth;
			ico_ld.height = parentHeight;
		}
	}
}