package Tutorial 
{
	import BaseClasses.BaseIconLoader;
	import Controllers.TextFieldFormater;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	
	public class DownNpcDialogLine extends BaseNpcCinematicDialog
	{
		public var ico_mc:CinematicDialogPortrait;
		public var name_txt:TextField;
		public var txt:TextField;
		public var close_btn:MovieClip;
		public var next_btn:CooldownButtonRound;
		public var nameBack:MovieClip;
		public var portraitBack:MovieClip;
		
		private var formatedText:TextFieldFormater;
		private var buttonOffset:Number;
		private var textLeftOffset:Number;
		private var nextBtnOffset:Number;
		
		override public function AddedToStage(e:Event):void 
		{
			startDialogYPosition = stage.stageHeight;
			endDialogYPosition = stage.stageHeight - this.height;
			this.y = startDialogYPosition;
			buttonOffset = NPCLine_mc.width - close_btn.x;
			textLeftOffset = NPCLine_mc.width - (txt.x + txt.width);
			nextBtnOffset = NPCLine_mc.width - next_btn.x;
			
			formatedText = new TextFieldFormater(name_txt);
			close_btn.visible = false;
			next_btn.visible = false;
			super.AddedToStage(e);
			next_btn.addEventListener("Up", NextButtonClick);
			
			
		}
		
		private function NextButtonClick(e:Event):void 
		{
			next_btn.disable();
			FSCommands.Send(FSCommands.CinematicNextButtonClick);
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			startDialogYPosition = stage.stageHeight;
			endDialogYPosition = stage.stageHeight - this.height;
			super.BaseBarObjectResize(e);
			
			close_btn.x = NPCLine_mc.width - buttonOffset;
			txt.width = NPCLine_mc.width -textLeftOffset - txt.x; 
			next_btn.x = NPCLine_mc.width - nextBtnOffset;
		}
	
		public function ShowCinematicNPC( icon: String, name: String ):void
		{
			ico_mc.Icon = icon;
			ico_mc.visible = icon.length != 0;
			formatedText.Text = name;
			nameBack.visible = name.length != 0;
		}
		
		public function ShowCinematicMessage(message:String, color:uint):void
		{
			txt.text = message;
			txt.textColor = color;
		}
	}

}