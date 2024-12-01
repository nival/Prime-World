package StatisticBars
{
	import Datas.AwardData;
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.geom.Point;
	
	import Interfaces.IScrollableObject;
	
	public class AwardIcons extends MovieClip implements IScrollableObject
	{
		private var startHeight:Number = 400;
		
		private var horisontalSpace:int = 97.6;
		private var verticalSpace:int = 92.8;
		private var iconHeight:int = 64;
		private var maxHorisintalPosition:int =  horisontalSpace *3;
		private var StartPosition:Point = new Point(40.5, 28.8);
		private var lastAwardStartPosition:Point = new Point(StartPosition.x, 0);
		private var scrollableHight:Number = 0;
		private var back:Shape;
		private var awardsIcons:Array = [];
		
		
		public function AwardIcons()
		{
			startHeight = this.height;
			back = this.getChildAt(0) as Shape;
		}
		
		public function RemoveIcons():void
		{
			for (var i:int = 0; i < this.awardsIcons.length; i++)
			{
				this.removeChild(this.awardsIcons[i]); 
			}
				
			this.awardsIcons.splice(0, this.awardsIcons.length);
			
			lastAwardStartPosition.x = StartPosition.x;
			lastAwardStartPosition.y = 0;
		}
		
		public function AddAward(award:AwardData):void
		{
			if (maxHorisintalPosition <= lastAwardStartPosition.x)
			{
				lastAwardStartPosition.x = StartPosition.x;
				lastAwardStartPosition.y += verticalSpace;
			}
			
			var AwardIco:PersonalStatisticAward = new PersonalStatisticAward();
			AwardIco.SetImage(award.Icon);
			AwardIco.Count = award.Count;
			AwardIco.IsPremium = award.IsFirstWin;
			AwardIco.x = lastAwardStartPosition.x;
			AwardIco.y = lastAwardStartPosition.y;
			AwardIco.ID = award.Id;
			
			awardsIcons.push(AwardIco);
			this.addChild(AwardIco);
			lastAwardStartPosition.x += horisontalSpace;
			
			scrollableHight = AwardIco.y + verticalSpace;
			
			if (back != null)
			{
				scrollableHight < startHeight ? back.height = startHeight : back.height = scrollableHight;
			}
		}
		
		public function SetTitle(title:String):void 
		{
			var newTitle:RewardTitle = new RewardTitle();
			
			this.awardsIcons.push(newTitle); //for RemoveIcons
			this.addChild(newTitle);
			newTitle.SetText(title);
			newTitle.x = (this.width - newTitle.width) / 2;
			
			newTitle.y = lastAwardStartPosition.y + (lastAwardStartPosition.x == StartPosition.x? 0: verticalSpace); 
			
			lastAwardStartPosition.x = StartPosition.x;
			lastAwardStartPosition.y = newTitle.y + newTitle.height;
		}
		
		/* INTERFACE Interfaces.IScrollableObject */
		
		public function get TopMargin():Number 
		{
			return 0;
		}
		
		public function get BottomMargin():Number 
		{
			return 0;
		}
		
		public function get ScrollableHeight():Number
		{
			return scrollableHight;
		}
		
		public function get StepSize():Number
		{
			return verticalSpace;
		}
		
		public function get ActualHeight():Number
		{
			return startHeight;
		}
	}
	
}