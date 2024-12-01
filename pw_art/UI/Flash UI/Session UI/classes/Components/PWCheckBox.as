package Components
{
	
	import Controllers.SoundController;
	import Interfaces.IPWComponents;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class PWCheckBox extends MovieClip implements IPWComponents 
	{
		private var isDisabled:Boolean = false;
		private var isToggled:Boolean = false;
		private var isDowned:Boolean = false;
		private var isRevert:Boolean;
				
		//references
		public var up_mc:MovieClip;
		public var over_mc:MovieClip;
		public var down_mc:MovieClip;
		public var disabled_mc:MovieClip
		
		public var togUp_mc:MovieClip;
		public var togOver_mc:MovieClip;
		public var togDown_mc:MovieClip;
		public var togDisabled_mc:MovieClip;
		
		private var isOver:Boolean;
		
		public function PWCheckBox() 
		{
			if(up_mc == null || over_mc == null || down_mc == null || togUp_mc == null || togOver_mc == null || togDown_mc == null)
			{
				visible = false;
				return;
			}
			
			this.doubleClickEnabled = true;
			
			this.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			this.addEventListener(MouseEvent.CLICK, onUp);
			this.addEventListener(MouseEvent.DOUBLE_CLICK, onDoubleClick);
			this.addEventListener(Event.ADDED_TO_STAGE, onAdded);
			
			this.mouseChildren = false;
			
			StartState();
			up_mc.visible = true;
			
			
			over_mc.visible = false;
			down_mc.visible = false;
			disabled_mc.visible = false;
			
			togUp_mc.visible = false;
			togOver_mc.visible = false;
			togDown_mc.visible = false;
			togDisabled_mc.visible = false;
		}
		

		private function onAdded(e:Event):void
		{
			removeEventListener(Event.ADDED_TO_STAGE, onAdded);
			stage.addEventListener(MouseEvent.MOUSE_UP, stageUp);
		}
		
		private function StartState():void
		{
			up_mc.visible = false;
			over_mc.visible = false;
			down_mc.visible = false;
			disabled_mc.visible = false;
			
			togUp_mc.visible = false;
			togOver_mc.visible = false;
			togDown_mc.visible = false;
			togDisabled_mc.visible = false;
		}

		private function onOver(e:MouseEvent):void
		{
			if (isDisabled)
				return;
				
			StartState();	
				
			over_mc.visible = !isToggled;
			togOver_mc.visible = isToggled;
			
			isOver = true;
		}
		private function onOut(e:MouseEvent):void
		{
			if (isDisabled)
				return;
				
			StartState();
			up_mc.visible = !isToggled;	
			togUp_mc.visible = isToggled;	
			isOver = false;
		}
		private function onDown(e:MouseEvent):void
		{
			if (isDisabled) 
			return;
				
			StartState();
			down_mc.visible = !isToggled;
			togDown_mc.visible = isToggled;	
			isDowned = true;
		}
		private function onUp(e:MouseEvent):void
		{
			if (isDisabled )//|| !isDowned)
				return;
		
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
			ChangeState();
		}
		
		private function onDoubleClick(e:MouseEvent):void 
		{
			if (isDisabled)	return;
			
			ChangeState();
		}
		
		private function ChangeState():void
		{
			isToggled =!isToggled;
			isDowned = false;
			
			StartState();
			
			up_mc.visible = !isToggled;	
			togUp_mc.visible = isToggled;		
			
			dispatchEvent(new PWComponentValueEvent(PWComponentValueEvent.CHANGE, int(isToggled),this.name));
		}
		
		private function stageUp(e:MouseEvent):void
		{
			if (isDisabled)
				return;
			
			StartState();
			up_mc.visible = !isToggled;	
			togUp_mc.visible = isToggled;	
			isDowned = false;
		}
		
		/* INTERFACE classes.Interfaces.IPWComponents */
		
		public function set Value(value:int):void 
		{
			Select = value != 0;
		}

		public function get Value():int 
		{
			return int(isToggled);
		}
		
		public function set Disable(value:Boolean):void
		{
			isDisabled = value;
			
			if (!isDisabled) return;
				
			StartState();
			
			disabled_mc.visible = !isToggled;	
			togDisabled_mc.visible = isToggled;
		}
		public function set Select(sel:Boolean):void
		{
			StartState();
			isToggled = sel;
			up_mc.visible = !isToggled;	
			togUp_mc.visible = isToggled;	
		}
		
		
	}
}
