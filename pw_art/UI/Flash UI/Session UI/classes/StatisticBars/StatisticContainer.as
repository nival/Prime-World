package StatisticBars 
{
	import Datas.PlayerStatisticData;
	import flash.display.MovieClip;
	import flash.events.Event;
	import Interfaces.IScrollableObject;
	
	public class StatisticContainer extends MovieClip
	{
		public var teamMate1_mc:StatisticsBarPlayers;
		public var teamMate2_mc:StatisticsBarPlayers;
		public var teamMate3_mc:StatisticsBarPlayers;
		public var teamMate4_mc:StatisticsBarPlayers;
		public var teamMate5_mc:StatisticsBarPlayers;
		public var chainlock1:MovieClip;
		public var chainlock2:MovieClip;
		public var chainlock3:MovieClip;
		public var chainlock4:MovieClip;
		
		private var teamMates:Vector.<StatisticsBarPlayers> = new Vector.<StatisticsBarPlayers>();
		private var _scytheTooltip:String;
		private var _mightTooltip:String;
		private var _fistTooltip:String;
		private var _textColor:uint;		
		private var posX:Number=0;
		private var posY:Number=0;
		private var _cupTooltip:String;
		private var oneElementHeight:Number = 0;
		private var _primeTooltip:String;
		
		public var chains:Vector.<MovieClip> = new Vector.<MovieClip>();
		
		public function StatisticContainer() 
		{
			teamMates.push(teamMate1_mc, teamMate2_mc, teamMate3_mc, teamMate4_mc, teamMate5_mc);
			chains.push(chainlock1, chainlock2, chainlock3, chainlock4);
			
			oneElementHeight = teamMate2_mc.y - teamMate1_mc.y;
			
			addEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
		}
		
		private function OnAddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			HideChains();
		}
		
		public function set TextColors(color:uint):void
		{
			_textColor = color;
			for each (var teamMate:StatisticsBarPlayers in teamMates) 
			{
					teamMate.TextColors = color;
			}
		}
		
		public function getNewMateInfo():StatisticsBarPlayers
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
		
		public function ResetMateState():void
		{
			for (var i:int = 0; i < teamMates.length;i++)
			{
				if (teamMates[i] != null)				
				{
					teamMates[i].isBusy = false;
					teamMates[i].visible = false;
					teamMates[i].SetSelected(false);
				}
			}
		}
		
		public function set MightTooltip(value:String):void
		{
			_mightTooltip = value;
			for (var i:int = 0; i < teamMates.length;i++)
				teamMates[i].MightTooltip = value;
		}
		
		public function get MightTooltip():String
		{
			return teamMate1_mc.MightTooltip;
		}
		
		public function set ScytheTooltip(value:String):void
		{
			_scytheTooltip = value;
			for (var i:int = 0; i < teamMates.length;i++)
				teamMates[i].ScytheTooltip = value
		}
		
		public function get ScytheTooltip():String
		{
			return teamMate1_mc.ScytheTooltip;
		}
		
		
		public function set FistTooltip(value:String):void
		{
			_fistTooltip = value;
			for (var i:int = 0; i < teamMates.length;i++)
				teamMates[i].FistTooltip = value;
		}
		
		public function get FistTooltip():String
		{
			return teamMate1_mc.FistTooltip;
		}
		
		public function set CupTooltip(value:String):void
		{	
			_cupTooltip = value;
			for (var i:int = 0; i < teamMates.length;i++)
				teamMates[i].CupTooltip = value;
		}
		
		public function get CupTooltip():String
		{
			return teamMate1_mc.CupTooltip
		}
		
		public function set PrimeTooltip(value:String):void
		{	
			_primeTooltip = value;
			for (var i:int = 0; i < teamMates.length;i++)
				teamMates[i].PrimeTooltip = value;
		}
		
		public function get PrimeTooltip():String
		{
			return teamMate1_mc.PrimeTooltip
		}
		
		public function set PartyMarkerTooltip(value:String):void
		{
			for (var i:int = 0; i < teamMates.length; ++i)
				teamMates[i].PartyMarkerTooltip = value;
		}
		
		public function set MuteTooltip(value:String):void
		{
			for (var i:int = 0; i < teamMates.length; ++i)
				teamMates[i].MuteTooltip = value;
		}
		
		public function GetTeamKillsCount():int
		{
			var count:int = 0;
		
			for (var i:int = 0; i < teamMates.length; i++)
			{
				count += teamMates[i]._kills;
			}
			
			return 	count;
		}
		
		
		public function GetTeamPrimeCount():int
		{	
			var count:int = 0;
		
			for (var i:int = 0; i < teamMates.length; i++)
			{
				count += teamMates[i]._prime;
			}
			return 	count;
		}
		
		public function SwitchToSpectetorMode():void 
		{
			for each (var item:StatisticsBarPlayers in teamMates) 
			{
				item.teamMateStat_mc.SpectatorMode = true;
			}
		}
		
		public function SwitchPlayersToFinalStatistic():void 
		{
			for each (var item:StatisticsBarPlayers in teamMates) 
			{
				item.SwitchToFinalStatistic();
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
		
		public function ShowChain(j:int, show:Boolean):void 
		{
			if (j<0 || j>=chains.length)
				return;
				
			chains[j].visible = show;
		}
		
		public function get OneElementHeight():Number
		{
			return oneElementHeight;
		}
	}

}