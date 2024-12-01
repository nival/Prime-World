package ActionBar 
{
	import BaseClasses.BaseBarButton;
	import Controllers.SoundController;
	import Enums.ActionBarSlotState;
	import Enums.EErrorMessageType;
	import Enums.TalentUIState;
	import Events.ErrorEvent;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;

	public class ActionButtonPortal extends BaseBarButton
	{
		private var deathMaskEnabled;
		private var lastStatus;
		private var curStatus;
		public var textNum:TextField;
		
		private var disableForTutorial:Boolean = false;
		public function ActionButtonPortal() 
		{
			textNum.mouseEnabled = false;
			textNum.text = "-"; //Захардкожено по просьбе камза=)
			State = ActionBarSlotState.ACTIVE;
		}
		
		public function SetPortalStatus(status:int, cooldown:Number, maxCooldownValue:Number):void 
		{
			State = status;
			Cooldown(cooldown,maxCooldownValue);	
		}
		
		public function EnableDeathMask(enableMask:Boolean):void  //выглядит как копипаст, хз пока что как это разрулить.
		{
			if  (deathMaskEnabled == enableMask)  return;
				
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
		
		public function EnableForTutorial(show:Boolean):void //выглядит как копипаст, хз пока что как это разрулить.
		{
			if (disableForTutorial == !show) return;
			
			if (deathMaskEnabled)
			{
				disableForTutorial = !show;
				return;
			}
			
			if (!show)
			{
				lastStatus = curStatus;
				State = ActionBarSlotState.DISABLED;
				disableForTutorial = true;
			}
			else
			{
				disableForTutorial = false;
				State = lastStatus;
			}
		}

		override public function get State():int 
		{
			return super.State;
		}
		
		override public function set State(value:int):void 
		{
			if (deathMaskEnabled||disableForTutorial)
			{ 
				lastStatus = value;
				return;
			}
			
			curStatus = value;
			
			super.State = value;
		}
		
		
		override protected function onUp(e:MouseEvent):void 
		{	
			super.onUp(e);
		
			Press();
		} 
		
		override protected function onOver(e:MouseEvent):void 
		{
			if (State != ActionBarSlotState.CHOSEN)
				toggleButton_mc.onOver();
				
			FSCommands.Send(FSCommands.PortalTooltip, FSCommands.TOOLTIP_SHOW);
		}
		
		override protected function onOut(e:MouseEvent):void 
		{	
			if (State != ActionBarSlotState.CHOSEN)
				toggleButton_mc.onOut();
			
			FSCommands.Send(FSCommands.PortalTooltip, FSCommands.TOOLTIP_HIDE);
		}
		
		override protected function onRightClick(e:Event):void
		{
			e.stopPropagation();
			Press();
		}
		
		private function Press():void 
		{
			if (cooldown > 0)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_ABILITYONCOOLDOWN));
				return;
			}
			
			if (State == ActionBarSlotState.NOT_ENOUGHT_MANA)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY));
				return;
			}
			
			if (State == ActionBarSlotState.DISABLED||deathMaskEnabled) return;
			
			FSCommands.Send(FSCommands.PortalClick);
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
		}
		
	}

}