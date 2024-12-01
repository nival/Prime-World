package MainScreen 
{
	import Components.FormatedTimer;
	import Components.Frame;
	import flash.display.MovieClip;
	import BaseClasses.BaseResizableObject;
	import Components.ButtonStandart;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	public class VoteMenu extends BaseResizableObject
	{
		public var timer_mc:FormatedTimer;
		
		public var votex5_mc:MovieClip;
		public var votex4_mc:MovieClip;
		public var votex3_mc:MovieClip;
		public var votex2_mc:MovieClip;
		
		public var yes:TextField;
		public var no:TextField;
		public var votingYes_btn:ButtonStandart;
		public var votingNo_btn:ButtonStandart;
		public var surrender:TextField;
		public var frame:Frame;
		
		private var votes:Array = new Array();
		
		private var votesForTwo:Array = new Array();
		private var votesForThree:Array = new Array();
		private var votesForFour:Array = new Array();
		private var votesForFive:Array = new Array();
		
		private var numYes:int = 0;
		private var numNo:int = 0;
		
		private var currentGameTimer:int = 0;
		
		private var timerTime:int = 0;
		
		private var startHeight:Number;
		
		public function VoteMenu() 
		{
			this.visible = false;
			
			votesForTwo = [votex2_mc.vote_btn, votex2_mc.vote2_btn];
			votesForThree = [votex3_mc.vote_btn,votex3_mc.vote2_btn,votex3_mc.vote3_btn];
			votesForFour = [votex4_mc.vote_btn,votex4_mc.vote2_btn,votex4_mc.vote3_btn,votex4_mc.vote4_btn];
			votesForFive = [votex5_mc.vote_btn,votex5_mc.vote2_btn,votex5_mc.vote3_btn,votex5_mc.vote4_btn,votex5_mc.vote5_btn];
			
			for (var i:int = 0; i < votes.length; i++) 
				votes[i].gotoAndStop(3);
				
			votingYes_btn.visible = false;
			votingNo_btn.visible = false;
			yes.visible = false;
			no.visible = false;
			
			votingYes_btn.addEventListener(MouseEvent.CLICK, OnVotingYes);
			votingNo_btn.addEventListener(MouseEvent.CLICK, OnVotingNo);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
				
			startHeight = this.height;
		}
		
		private function FillLocalization(e:Event):void 
		{
			votingYes_btn.LocalizeText = Localization.VoteMenu_YesButton;
			votingNo_btn.LocalizeText = Localization.VoteMenu_NoButton;
			yes.text = Localization.VoteMenu_YesLabel;
			no.text = Localization.VoteMenu_NoLabel;
			surrender.text = Localization.VoteMenu_SurrenderText;
		}
		
		private function OnVotingNo(e:MouseEvent):void 
		{
			votingYes_btn.visible = false;
			votingNo_btn.visible = false;
			no.visible = true;
			
			FSCommands.Send(FSCommands.VOTEMENU_SURRENDER_VOTE, FSCommands.DISABLE);
		}
		
		private function OnVotingYes(e:MouseEvent):void 
		{
			votingYes_btn.visible = false;
			votingNo_btn.visible = false;
			yes.visible = true;

			FSCommands.Send(FSCommands.VOTEMENU_SURRENDER_VOTE, FSCommands.ENABLE);
		}
		
		public function ShowVoteWindow(timeout:int, isAlreadyConceded:Boolean):void 
		{
			this.visible = true;
			
			votingYes_btn.visible = !isAlreadyConceded;
			votingNo_btn.visible = !isAlreadyConceded;
			
			no.visible = false;
			
			yes.visible = isAlreadyConceded;
			
			timerTime = timeout;
			
			timer_mc.Time = timerTime;
		}
		
		public function HideVoteWindow():void 
		{
			this.visible = false;
		}
		
		public function SetSurrenderVoteStatus(concededCount:int, declinedCount:int, totalCount:int):void 
		{
			votex2_mc.visible = totalCount == 2;
			votex3_mc.visible = totalCount == 3;
			votex4_mc.visible = totalCount == 4;
			votex5_mc.visible = totalCount == 5;
			
			FillVoteButtons(totalCount);
			
			if (concededCount + declinedCount > votes.length) 
			{
				trace("Not Corrected number of voted players");
			}
			
			var i:int = 0;
			
			for ( i = 0; i < votes.length; i++) 
				votes[i].gotoAndStop(3);
			
			if (concededCount > 0)
			{
				for ( i = 0; i <concededCount ; i++) 
				{
					votes[i].gotoAndStop(1);
				}
			}
				
			if (declinedCount > 0)
			{
				for (i=0; i <declinedCount ; i++) 
				{
					votes[votes.length-1-i].gotoAndStop(2);
				}
			}
		}
		
		private function FillVoteButtons(totalCount:int):void 
		{
			votes = GetVoteBtns(totalCount);
			
			for (var i:int = 0; i < votes.length; i++) 
				votes[i].gotoAndStop(3);
		}
		
		private function GetVoteBtns(totalCount:int):Array 
		{
			if (totalCount == 2)
				return votesForTwo;
			if (totalCount == 3)
				return votesForThree;
			if (totalCount == 4)
				return votesForFour;
				
			return votesForFive;
		}
		
		
		public function SetTime(gameTime:int):void 
		{
			if (currentGameTimer == gameTime) return;
			currentGameTimer = gameTime;
			
			if (timerTime <= 0) return;
			
			timerTime--;
			timer_mc.Time = timerTime;
		}
		
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			
			this.x = stage.stageWidth -(initialStage.x - startXPosition)*scale;
			this.y = stage.stageHeight - (initialStage.y - startPozition.y)*scale;
		}
	}

}