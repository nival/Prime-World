package LoaderSources
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import BaseClasses.BaseResizableObject;
	import StatisticBars.TerrainDominate;
	
	public class LoadingBar extends BaseResizableObject
	{
		public var terrainDominating:TerrainDominate;
		
		public var rightGerb_mc:MovieClip;
		public var leftGerb_mc:MovieClip;
		
		public function SetLoadingBarParametres(humanTerrain:Number, elfTerrain:Number):void
		{
			terrainDominating.DwarfenTerrain = humanTerrain;
			terrainDominating.ElfenTerrain = elfTerrain;
		}
		
		public function SetPlayersFaction(leftFaction:int, rightFaction:int):void 
		{
			leftGerb_mc.gotoAndStop(leftFaction);
			rightGerb_mc.gotoAndStop(rightFaction);
		}
		
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = stage.stageWidth/2;
			this.y = stage.stageHeight-10;
		}
	}
	
}