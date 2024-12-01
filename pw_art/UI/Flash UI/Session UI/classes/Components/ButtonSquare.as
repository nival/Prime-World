package Components
{
	import Controllers.SoundController;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.events.Event;
	import flash.utils.getDefinitionByName;

	import src.Desaturate;
	import src.WButton;

	public class ButtonSquare extends MovieClip
	{
		//теперь квадратная кнопка всегда обычная, не тоггл
		public var downed:Boolean = false;
		private var toggled:Boolean = false;
		private var iconName:String = "cross_png";
	
		//reference
		public var icons_mc:MovieClip;
		public var button_mc:TooltipButton;
		public var buttont_mc:TooltipButton;
	
		private var notToggledImage:Bitmap;
		private var isNeedToPlaySound:Boolean=true;
		//private var toggledImage:Bitmap;
		
		public function ButtonSquare()
		{
			
			//buttont_mc.visible = false;

			button_mc.addEventListener("Up",OnUp);
			//buttont_mc.addEventListener("Up", onDown);
				
			var image:Class = getDefinitionByName(iconName) as Class;
			//var timage:Class = getDefinitionByName("t" + iconName) as Class;
			
			notToggledImage = new Bitmap(new image)
			//toggledImage = new Bitmap(new timage)
			
			button_mc.addChild(notToggledImage);
			//buttont_mc.addChild(toggledImage);
		}
		
		private function OnUp(e:Event):void 
		{
			if (!isNeedToPlaySound) return;
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
		}
		private function onDown(e:Event):void
		{
//			if (toggled)
//			{
//				button_mc.visible = downed;
//				buttont_mc.visible = ! downed;
//				downed = ! downed;
//			}
		}
		
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
			//buttont_mc.Tooltip = value;
			button_mc.Tooltip = value;
		}
		
		public function get TogledTooltip():String
		{
			//return buttont_mc.Tooltip;
			return button_mc.Tooltip;
		}
		
		public function set Toggle(tog):void
		{
			toggled = tog;
		}
		public function get Toggle():Boolean
		{
			return (toggled);
		}
		public function set Ico(value:String):void
		{
			iconName = value;
			if(iconName == '_')
			{
				button_mc.removeChild(notToggledImage);
				notToggledImage = null;

				return;
			}
			
			var image:Class = getDefinitionByName(iconName) as Class;
			
			button_mc.removeChild(notToggledImage);
			
			notToggledImage = new Bitmap(new image);
			button_mc.addChild(notToggledImage);
			
//			if (!toggled) return;
//			
//			var timage:Class = getDefinitionByName("t" + iconName) as Class;
//			
//			buttont_mc.removeChild(toggledImage);
//			
//			toggledImage = new Bitmap(new timage)
//			buttont_mc.addChild(toggledImage);
		}
		public function get Ico():String
		{
			return iconName;
		}
		public function disable():void
		{
			Desaturate.desaturate(button_mc);
			//Desaturate.desaturate(buttont_mc);
			this.mouseEnabled = false;
			this.mouseChildren = false;
		}
		public function enable():void
		{
			Desaturate.saturate(button_mc);
			//Desaturate.saturate(buttont_mc);
			this.mouseEnabled = true;
			this.mouseChildren = true;
		}
		
		public function RemoveIntegratedSound():void 
		{
			isNeedToPlaySound = false;
		}
	}
}