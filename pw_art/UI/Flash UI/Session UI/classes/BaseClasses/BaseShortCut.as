package BaseClasses 
{
	import InventoryBar.InventoryButton;
	import Enums.ActionBarSlotState;
	import Interfaces.IActionButton;
	import Enums.EActionBarDesiredPositions;
	
	public class BaseShortCut 
	{
		public function BaseShortCut() 	{}

		public function set State(_state:int):void	{ }
		
		public function Cooldown(_cooldown:Number,_maxCooldown:Number):void	{ }
		
	/*	public function get Cooldown():Number	
		{
			return 0;
		}
		*/
		
		public function Press():void {}
		
		public function showTooltip():void	{}
		
		public function hideTooltip():void	{}
		
		public function set actionButton(button:IActionButton)
		{
			if (button == null) return;
			button.iconPath = '';
			button.State = ActionBarSlotState.DISABLED;
			button.DontShowCoolDownEndAnimation();
			button.Cooldown(0,0);
			button.GlobalCoolDown(0,0);
			button.count = 0;
		}
		
		public function EnableDeathMask(enableMask:Boolean):void{}
		
		public function GlobalCoolDown (_cooldown:Number,_maxCooldown:Number):void{}
		
		public function get icon ():String
		{
			return "";
		}
		
		public function RemoveFromActionbar():void { }
		
		public function set count(value:int):void { }
		
		public function set InventoryButtonItem(_item:InventoryButton):void { }
		
		public function get DesirableIndex():int {return EActionBarDesiredPositions.INTO_ANY_POSITION}
		
	}
}
