package StatisticBars
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import MainScreen.TeamInfoBase;
	
	import MainScreen.TeamInfoFriendly;
	
	public class StatisticTeamInfoFriendly extends TeamInfoBase 
	{
		override public function AddedToStage(e:Event):void 
		{
			teamMates = [teamMate1_mc, teamMate2_mc, teamMate3_mc, teamMate4_mc, teamMate5_mc];
			chains =  [chain1, chain2, chain3, chain4];
			super.AddedToStage(e);
		}
		
				
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			
		}
	}
}