package Components
{

	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import src.ButtonTooltipEvent;
	import flash.geom.Point;
	import flash.display.Bitmap;
	import flash.utils.getDefinitionByName;

	import Events.WindowVisibleControllerEvent;
	import ActionBar.ToggleButtonSmall;
	
	public class RulerButton extends MovieClip
	{

		private var _iconPath:String;
		private var globalPoint:Point;
		private var isOn:Boolean = false;
		private var isButtonDown:Boolean = false;
		private var isButtonOn:Boolean = true;
		
		public var toggleButtonSmall_mc:ToggleButtonSmall;
		
		public var __exportedProperties : Array = ['Tooltip','TogledTooltip'];
		private var tooltip:String = '';
		private var togleledTooltip:String = "";
		private var _index:int;
		private var currentTooltip:String = "";
				
		private var naftaShining:RulerButtonLevelUp;
		private var isShiningShowing:Boolean;	
		
		
		public function RulerButton()
		{
			this.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			this.addEventListener(MouseEvent.MOUSE_UP, onUp);
			this.addEventListener(MouseEvent.DOUBLE_CLICK,onUp);
			
			this.doubleClickEnabled = true;
			this.buttonMode = true;
				
			currentTooltip = Tooltip;
			
			this.mouseChildren = false;
			//DisableButton();
			//EnableButton();
		}
				
		private function onUp(e:MouseEvent):void
		{
			if (!isButtonDown) return;
			isButtonDown = false;
			
			toggleButtonSmall_mc.onOut(isButtonOn);
			toggleButtonSmall_mc.onUp();
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,_index));
			
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
			
			globalPoint = this.localToGlobal(new Point());
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, globalPoint.x, globalPoint.y, currentTooltip));
		}
		
		private function onDown(e:MouseEvent):void
		{ 
			isButtonDown = true;
			toggleButtonSmall_mc.onDown();
		}
		
		private function onOver(e:MouseEvent):void
		{	
			globalPoint = this.localToGlobal(new Point());
			
			toggleButtonSmall_mc.onOver(isButtonOn);
			
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, globalPoint.x, globalPoint.y, currentTooltip));
		}
		private function onOut(e:MouseEvent):void
		{
			toggleButtonSmall_mc.onOut(isButtonOn);
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		
		public function set ButtonIndex(value:int):void
		{
			_index = value;
		}
		public function get ButtonIndex():int
		{
			return _index;
		}
		
		public function get iconPath():String
		{
			return _iconPath;
		}

		public function set iconPath( _path : String ):void
		{
			_iconPath = _path;

			if (_iconPath.length == 0)
			{
				return;
			}
			var image:Class = getDefinitionByName(_iconPath) as Class;
			
			var img:Bitmap = new Bitmap(new image);
			var imgD:Bitmap = new Bitmap(new image);
			
			
			
			img.smoothing = true;
			imgD.smoothing = true;
			
			img.width = imgD.width = this.width-1;
			img.height = imgD.height = this.height;
			
			/*img.width = 32;
			img.height = 65;
			imgD.width = 32;
			imgD.height = 65;*/

			img.x = (27 - img.width)/2;
			img.y = (54 - img.height)/2;
			imgD.x = (27 - imgD.width)/2;
			imgD.y = (54 - imgD.height) / 2;
			
			toggleButtonSmall_mc.ico.addChild(img);
			toggleButtonSmall_mc.icoDown.addChild(imgD);
		}
		
		public function set Tooltip(_tooltip:String)
		{
			tooltip = _tooltip;
		
			if (!isButtonOn)
				currentTooltip = _tooltip;
		}
		
		public function get Tooltip():String
		{
			return tooltip;
		}
		
		public function set TogledTooltip(_tooltip:String)
		{
			togleledTooltip = _tooltip;
			
			if (isButtonOn)
				currentTooltip = _tooltip;
		}
		public function get TogledTooltip():String
		{
			return togleledTooltip;
		}
		
		public function setOffState():void
		{
			toggleButtonSmall_mc.SetOffState();
			isButtonOn = false;
			currentTooltip = tooltip;
		}
		
		public function setOnState():void
		{
			toggleButtonSmall_mc.SetOnState();
			isButtonOn = true;
			currentTooltip = togleledTooltip;
		}
		
		public function DisableButton():void
		{
			this.mouseEnabled = false;
			this.buttonMode = false;
			toggleButtonSmall_mc.disable();
			this.removeEventListener(MouseEvent.ROLL_OVER, onOver);
			this.removeEventListener(MouseEvent.ROLL_OUT, onOut);
			this.removeEventListener(MouseEvent.MOUSE_DOWN, onDown);
			this.removeEventListener(MouseEvent.MOUSE_UP, onUp);
			this.removeEventListener(MouseEvent.DOUBLE_CLICK,onUp);
		}
		
		public function EnableButton():void
		{
			this.mouseEnabled = true;
			this.buttonMode = true;
			toggleButtonSmall_mc.enable();
			this.addEventListener(MouseEvent.ROLL_OVER, onOver);
			this.addEventListener(MouseEvent.ROLL_OUT, onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			this.addEventListener(MouseEvent.MOUSE_UP, onUp);
			this.addEventListener(MouseEvent.DOUBLE_CLICK,onUp);
		}
		public function AddNaftaShiningAnimation():void
		{
			naftaShining = new RulerButtonLevelUp();
			addChild(naftaShining);
			naftaShining.x = 3;
			naftaShining.y = 2;
			naftaShining.blendMode = 'add';
			naftaShining.stop();	
		}
		
		public function ShowNaftaShiningAnimation(show:Boolean):void
		{
			if (naftaShining == null) return;
			
			if (show&&!isShiningShowing) 
			{
				naftaShining.gotoAndPlay(1)
				isShiningShowing = true;
			}
				
			if (!show&&isShiningShowing)
			{
				isShiningShowing = false;
				naftaShining.gotoAndStop(1);
			}
		}
	}
}