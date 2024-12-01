package LoaderSources
{
	import flash.events.Event;

	public class LeftTeamHolder extends TeamHolder
	{
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.y = 4;
			this.x = 0;
		}
		
		
		
	}
}