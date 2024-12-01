package ActionBar
{
	import BaseClasses.BaseShortCut;
	import Controllers.SoundController;
	import Enums.ActionBarSlotState;
	import Interfaces.IActionButton;
	
	
	public class ActionBarShortcut extends BaseShortCut
	{
		protected var lastStatus:int = ActionBarSlotState.DISABLED;
		protected var curStatus:int = ActionBarSlotState.ACTIVE;
		
		protected var deathMaskEnabled: Boolean = false;
		
		protected var cooldown:Number = 0;
		protected var _actionButton:IActionButton;
		protected var actionBar:ActionBar;
		protected var maxCooldown:Number;
		
		public function ActionBarShortcut(_actionBar:ActionBar)
		{	
			actionBar = _actionBar;
		}
		
		override public function set State(_state:int):void
		{	
			if (deathMaskEnabled)
			{ 
				lastStatus = _state;
				return;
			}
			
			curStatus = _state;
			
			if (_actionButton == null)
				return;
				
			_actionButton.State = _state;
		};
		
		override public function Cooldown(_cooldown:Number,_maxCooldown:Number):void
		{
			if (_actionButton != null)
			{
				_actionButton.Cooldown(_cooldown, _maxCooldown);
				
			}
			cooldown = _cooldown;
			maxCooldown = _maxCooldown;
		}
		
		override public function GlobalCoolDown (_cooldown:Number,maxCooldown:Number):void
		{
			if (_actionButton!=null)
				_actionButton.GlobalCoolDown(_cooldown,maxCooldown);
		}
		
		
		override public function EnableDeathMask(enableMask:Boolean):void
		{
			if  (deathMaskEnabled == enableMask)
				return;
				
			if (enableMask)
			{
				lastStatus = curStatus;
				State = ActionBarSlotState.DISABLED;
				deathMaskEnabled = true;
			}
			else
			{
				deathMaskEnabled = false;
				State = lastStatus;
			}
		}
		
		override public function set actionButton(button:IActionButton)
		{
			button.DontShowCoolDownEndAnimation();
			_actionButton = button;
			_actionButton.State = curStatus;
			Cooldown(cooldown,maxCooldown);
		}
		
		override public function Press():void
		{			
			
		}
	}
}