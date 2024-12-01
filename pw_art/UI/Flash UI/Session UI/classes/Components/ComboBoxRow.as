package Components 
{
	import Controllers.SoundController;
	import Controllers.TextFieldFormater;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	public class ComboBoxRow  extends MovieClip
	{
		private var overRect:Bitmap;
		private var selectRect:Bitmap;
		private var textColor:uint;

		public var txt:TextField;
		public var ID:Number = -1;
		public var ComponentName:String;
		private var formatedText:TextFieldFormater;
		
		public function ComboBoxRow()
		{
			addEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			formatedText = new TextFieldFormater(txt);
		}
		
		private function OnAddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			
		//	txt.mouseEnabled = false;
		
			overRect = new Bitmap(new rowOver_png());
			selectRect = new Bitmap(new rowSelected_png());
			
			this.addChildAt(overRect, 0);
			this.addChildAt(selectRect, 0);
			//this.addChild(txt);
			
			this.addEventListener(MouseEvent.MOUSE_OVER, rowOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, rowOut);
			this.addEventListener(MouseEvent.CLICK, rowUp);
	
			overRect.x = 2;
			overRect.y = txt.y;
			overRect.alpha = 0;
			selectRect.visible = false;
			selectRect.x = 2;
			selectRect.y = txt.y;
			textColor = txt.textColor;
		}
		
		private function rowOver(e:MouseEvent):void
		{
			overRect.alpha = 1;
		}
		
		private function rowOut(e:MouseEvent):void 
		{
			overRect.alpha = 0;
		}
		
		public function set Text(text:String):void 
		{
			formatedText.Text = text;
		}
		
		public function get Text():String
		{
			return formatedText.Text;
		}
			
		private function rowUp(e:MouseEvent):void
		{
			dispatchEvent(new PWComponentValueEvent(PWComponentValueEvent.CHANGE, ID, ComponentName));
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_BIG);
		}
		
		public function ShowSelectRectangle(show:Boolean):void
		{
			selectRect.visible = show;
		}
		
		public function SetWidth(newwidth:Number):void 
		{
			txt.width = newwidth - txt.x - 2;
			overRect.width = newwidth - 4;
			selectRect.width = newwidth - 4;//поправка на толщину рамки
			formatedText.RecalcTextWidth(newwidth - txt.x - 2);
		}
		
		public function SetHeigt(_height:Number):void
		{
		//	txt.y = (_height - txt.height)/2;
			overRect.y = txt.y;
			selectRect.y = txt.y;
			overRect.height = _height;
			selectRect.height = _height;
		}
		
		public function set TextColor(value:uint):void
		{
			textColor = value;
			txt.textColor = value;
		}
		public function get TextColor():uint
		{
			return txt.textColor;
		}
	}
}