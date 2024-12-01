package Components
{
	import Controllers.SoundController;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.events.Event;
	import flash.utils.getDefinitionByName;
		
	import src.Desaturate;
	import src.WButton;

	public class ButtonToggle extends MovieClip
	{

		private var downed:Boolean = false;//нажата/не нажата кнопка
		private var toggled:Boolean = false;//если кнопка тоггл
		private var iconName:String;//имя иконки
				
		//references
		public var button_mc:TooltipButton;//наследуется от WButton
		public var buttont_mc:TooltipButton;//наследуется от WButton
		
		private var notToggledImage:Bitmap;//обычная иконка
		private var toggledImage:Bitmap;//вжатая иконка
		
		private var isNeedToPlaySound:Boolean=true;
		
		public function ButtonToggle()
		{
			button_mc.addEventListener("Up",OnMouseUp);
			
			//если кнопка тоггл
			if(toggled && buttont_mc != null)
			{
				buttont_mc.visible = false;
				buttont_mc.addEventListener("Up", OnMouseUp);
			}
		}
		
		//реакция на состоявшееся нажатие кнопки
		private function OnMouseUp(e:Event):void
		{
			if (!isNeedToPlaySound) return;
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
			
			if (toggled && buttont_mc != null)
			{
				//переключаемся между двумя кнопками
				button_mc.visible = downed;
				buttont_mc.visible = ! downed;
				downed = ! downed;
			}
		}
		
		//удаленное вжатие кнопки
		public function SwitchOn():void
		{
			if (toggled && buttont_mc != null)
			{
				button_mc.visible = false;
				buttont_mc.visible = true;
				downed = true;
			}
		}
		
		//удаленное отжатие кнопки
		public function SwitchOff():void
		{
			if (toggled && buttont_mc != null)
			{
				button_mc.visible = true;
				buttont_mc.visible = false;
				downed = false;
			}
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
			if (toggled && buttont_mc != null)
			{
				buttont_mc.Tooltip = value;
			}
		}
		
		public function get TogledTooltip():String
		{
			if (toggled && buttont_mc != null)
			{
				return buttont_mc.Tooltip;
			}
			else
			{
				return null;
			}
		}				
		public function set Toggle(tog):void
		{
			toggled = tog;
		}
		public function get Toggle():Boolean
		{
			return (toggled);
		}
		
		public function get PushedIN():Boolean
		{
			return downed;
		}
		public function set Ico(_value:String):void
		{
			iconName = _value;
			
			if(iconName == '_')
			{
				button_mc.removeChild(notToggledImage);
				notToggledImage = null;
				
				if (toggled && buttont_mc != null)
				{
					buttont_mc.removeChild(toggledImage);
					toggledImage = null;
				}
				return;
			}
				
			var image:Class = getDefinitionByName(iconName) as Class;
			
			if(notToggledImage != null)
			{
				button_mc.removeChild(notToggledImage);
				notToggledImage = null;
			}
			
			notToggledImage = new Bitmap(new image)
			notToggledImage.x = button_mc.ico_mc.x;
			notToggledImage.y = button_mc.ico_mc.y;
			
			button_mc.addChild(notToggledImage);
			
			if (toggled && buttont_mc != null)
			{
				var imaget:Class = getDefinitionByName("t" + iconName) as Class;
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
		}
		public function get Ico():String
		{
			return iconName;
		}
		public function disable():void
		{
			Desaturate.desaturate(button_mc);
			this.mouseEnabled = false;
			this.mouseChildren = false;
			
			if (toggled && buttont_mc != null)
			{
				Desaturate.desaturate(buttont_mc);
			}
		}
		public function enable():void
		{
			Desaturate.saturate(button_mc);
			this.mouseEnabled = true;
			this.mouseChildren = true;
			
			if (toggled && buttont_mc != null)
			{
				Desaturate.saturate(buttont_mc);
			}
		}
		public function RemoveIntegratedSound():void 
		{
			isNeedToPlaySound = false;
		}
	}
}