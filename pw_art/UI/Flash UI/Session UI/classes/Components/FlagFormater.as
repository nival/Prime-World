package Components 
{
	import BaseClasses.TooltipSender;
	import BaseClasses.BaseIconLoader;

	public class FlagFormater extends TooltipSender
	{
		public var icon:BaseIconLoader;
		
		public function set Icon(path:String) 
		{
			icon.SetIcon(path);
		}
	}

}