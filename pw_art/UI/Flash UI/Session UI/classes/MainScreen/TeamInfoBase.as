package MainScreen 
{
	import BaseClasses.MateInfoBase;
	import flash.display.MovieClip;
	import flash.events.Event;
	import Interfaces.IMateInfoContainer;
	import BaseClasses.BaseResizableObject;
	public class TeamInfoBase extends BaseResizableObject implements IMateInfoContainer
	{
		public var teamMate1_mc:MateInfoBase;
		public var teamMate2_mc:MateInfoBase;
		public var teamMate3_mc:MateInfoBase;
		public var teamMate4_mc:MateInfoBase;
		public var teamMate5_mc:MateInfoBase;
		public var chain1:MovieClip;
		public var chain2:MovieClip;
		public var chain3:MovieClip;
		public var chain4:MovieClip;
		
		
		protected var teamMates:Array;
		private var teamMatesStartPositions:Array = new Array();
		protected var chains:Array = new Array();
		
		
		override public function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);
			
			this.mouseEnabled = false;
			
			for (var i:int = 0;i< teamMates.length;i++)
			{
				teamMates[i].mouseEnabled = false;
				teamMatesStartPositions.push(teamMates[i].x);
			}
		}
		
		public function HideChains():void 
		{
			for each (var item:MovieClip in chains) 
			{
				item.visible = false;
				item.gotoAndStop(1);
			}
		}
		
		public function ShowChain(i:int, show:Boolean):void 
		{
			
			if (i<0 || i>=chains.length )
				return;
			
			chains[i].visible = show;
		}
		
		public function getNewMateInfo():MateInfoBase
		{
			for (var i:int = 0; i < teamMates.length;i++)
			{
				if (teamMates[i]!=null&&!teamMates[i].isBusy)
				{
					teamMates[i].isBusy = true;
					teamMates[i].visible = true;
					return teamMates[i];
				}
			}
			
			return null;
		}
		
		public function teamHide()
		{
			this.visible = false;
		}
		public function teamShow()
		{
			this.visible = true;
		}
		
		public function ResetMateState():void
		{
			for (var i:int = 0; i < teamMates.length; i++)
			{
				if (teamMates[i] != null)
				{
					teamMates[i].isBusy = false;
					teamMates[i].visible = false;
				}
			}
		}
		
		public function ResetMateSelection():void
		{
			for (var i:int = 0; i < teamMates.length; i++)
			{
				if (teamMates[i] != null)
				{
					teamMates[i].SetSelected(false);
				}
			}
		}
		
		
		public function GetStartPositions():Array
		{
			return teamMatesStartPositions;
		}
		
	}

}