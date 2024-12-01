package Components
{
	import Controllers.SoundController;
	import Events.ToggleButtonClickedEvent;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.events.Event;
	import flash.utils.getDefinitionByName;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	
	import src.ButtonTooltipEvent;
	import src.Desaturate;
	import src.WButton;

	public class ButtonRound extends MovieClip
	{

		public var IsChecked:Boolean = false;
		private var toggled:Boolean = false;
		private var iconName:String;
		private var sendingTooltip:String = "";
		
		//reference
		public var button_mc:TooltipButton;
		public var buttont_mc:TooltipButton;
		
		private var notToggledImage:Bitmap
		private var toggledImage:Bitmap
		public var AutoCheck:Boolean = true;
		
		public function ButtonRound()
		{
			buttont_mc.visible = false;

			button_mc.addEventListener("Up",SetToggle);
			buttont_mc.addEventListener("Up", SetUntogle);
				
//			var image:Class = getDefinitionByName(iconName) as Class;
//			var toggledImage:Class = getDefinitionByName("t" + iconName) as Class;
//			
//			notToggledImage = new Bitmap(new image)
//			toggledImage = new Bitmap(new toggledImage)
//			
//			button_mc.ico_mc.addChild(notToggledImage);
//			buttont_mc.icot_mc.addChild(toggledImage);			
		}
		
		private function SetUntogle(e:Event):void 
		{
			e.stopPropagation();
			OnMouseUp(false);
		}
		
		private function SetToggle(e:Event):void 
		{
			e.stopPropagation();
			OnMouseUp(true);
		}
		
		private function OnMouseUp(checked:Boolean):void
		{
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
			
			dispatchEvent(new ToggleButtonClickedEvent(checked));
			
/*			if (toggled && AutoCheck)
			{
				button_mc.visible = !checked;
				buttont_mc.visible = checked;
				IsChecked = checked;
			}
*/		}
		
		
		public function set Tooltip(value:String):void
		{
			button_mc.Tooltip = value;
		}
		
		public function get Tooltip():String
		{
			return button_mc.Tooltip;
		}
		
		public function set TogledTooltip(value:String):void
		{
			buttont_mc.Tooltip = value;
		}
		
		public function get TogledTooltip():String
		{
			return buttont_mc.Tooltip;
		}
		
		public function SwitchOn():void
		{
			button_mc.visible = false;
			buttont_mc.visible = true;
			IsChecked = true;
		}
		
		public function SwitchOff():void
		{
			button_mc.visible = true;
			buttont_mc.visible = false;
			IsChecked = false;
		}
		
		public function set Toggle(tog):void
		{
			toggled = tog;
		}
		public function get Toggle():Boolean
		{
			return (toggled);
		}
		
		public function set Ico(_value:String):void
		{
			iconName = _value;
			
			if(iconName == '_')
			{
				button_mc.removeChild(notToggledImage);
				notToggledImage = null;
				buttont_mc.removeChild(toggledImage);
				toggledImage = null;
				return;
			}
				
			var image:Class = getDefinitionByName(iconName) as Class;
			var imaget:Class = getDefinitionByName("t" + iconName) as Class;
			
			if(notToggledImage != null)
			{
				button_mc.removeChild(notToggledImage);
				notToggledImage = null;
			}
			
			notToggledImage = new Bitmap(new image)
			notToggledImage.x = button_mc.ico_mc.x;
			notToggledImage.y = button_mc.ico_mc.y;
			button_mc.addChild(notToggledImage);
						
			if(toggledImage != null)
			{
				buttont_mc.removeChild(toggledImage);
				toggledImage = null;
			}
			toggledImage = new Bitmap(new imaget)
			toggledImage.x = buttont_mc.icot_mc.x;
			toggledImage.y = buttont_mc.icot_mc.y;
			buttont_mc.addChild(toggledImage);
			
		}
		public function get Ico():String
		{
			return iconName;
		}
		public function disable():void
		{
			Desaturate.desaturate(button_mc);
			Desaturate.desaturate(buttont_mc);
			this.mouseEnabled = false;
			this.mouseChildren = false;
		}
		public function enable():void
		{
			Desaturate.saturate(button_mc);
			Desaturate.saturate(buttont_mc);
			this.mouseEnabled = true;
			this.mouseChildren = true;
		}
	}
}