package StatisticBars
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import MainScreen.TeamInfoBase;
	import MainScreen.TeamInfoEnemy;
	
	public class StatisticTeamInfoEnemy extends TeamInfoBase  
	{
		override public function AddedToStage(e:Event):void 
		{
			teamMates = [teamMate5_mc, teamMate4_mc, teamMate3_mc, teamMate2_mc, teamMate1_mc];
			chains = [chain4, chain3, chain2, chain1];
			super.AddedToStage(e);
		}
		
		
		public function SetThisAsOurFraction():void
		{
			//teamMates = [teamMate1_mc, teamMate2_mc, teamMate3_mc, teamMate4_mc, teamMate5_mc];
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			
		}
	}
}