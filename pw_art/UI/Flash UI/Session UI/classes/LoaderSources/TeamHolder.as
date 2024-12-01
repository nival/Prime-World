package LoaderSources
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import BaseClasses.BaseResizableObject;
	import flash.events.MouseEvent;
	import flash.utils.Dictionary;

	public class TeamHolder extends BaseResizableObject
	{
		public var heroTeamMate1_mc:LoaderTeamMate;
		public var heroTeamMate2_mc:LoaderTeamMate;
		public var heroTeamMate3_mc:LoaderTeamMate;
		public var heroTeamMate4_mc:LoaderTeamMate;
		public var heroTeamMate5_mc:LoaderTeamMate;

		public var chainlock1:MovieClip;
		public var chainlock2:MovieClip;
		public var chainlock3:MovieClip;
		public var chainlock4:MovieClip;

		protected var _TeammatesMovieclips:Array;
		protected var _chainLockMovieClips:Array;
		private var _arrayOfTeamMatesInUse:Array = [];
		private var _isOurIsElfTeam:Boolean;
		public var OurHeroID:int = -1;

		private var _startTeamMateXPositions:Array = [];
		private var _sortedItemsByPartyID:Array = [];

		private var _partyIDsDict:Dictionary = new Dictionary();

		public function TeamHolder()
		{
			_TeammatesMovieclips = [heroTeamMate1_mc, heroTeamMate2_mc, heroTeamMate3_mc, heroTeamMate4_mc, heroTeamMate5_mc];
			_chainLockMovieClips = [chainlock1, chainlock2, chainlock3, chainlock4];
		}
		override public function AddedToStage(e:Event):void
		{
			super.AddedToStage(e);

			for each (var item:LoaderTeamMate in _TeammatesMovieclips)
			{
				_startTeamMateXPositions.push(item.x);
			}

			for each (var chain:MovieClip in _chainLockMovieClips)
			{
				chain.visible = false;
			}
		}

		public function SetElfTeamIsOur():void
		{
			_isOurIsElfTeam = true;
			trace (_isOurIsElfTeam);
		}

		public function GetHeroByID(ID:int):LoaderTeamMate
		{
			for (var index:int = 0; index < _arrayOfTeamMatesInUse.length; index++)
			{
				var id:int = _arrayOfTeamMatesInUse[index].id;
				if (id == ID)
					return _arrayOfTeamMatesInUse[index];
			}
			trace("member wasn't generated earlier, generate it before")
			return null
		}

		public function GenerateMateInfo(ID:int, partyID:int = 0):LoaderTeamMate
		{
			for (var index = 0; index < _arrayOfTeamMatesInUse.length; index++)
			{
				var id:int = _arrayOfTeamMatesInUse[index].id;

				if (id == ID)
					return _arrayOfTeamMatesInUse[index];
			}

			var newMateForUse:LoaderTeamMate = GetNewMateInfoInUseFromStartMates();

			if (newMateForUse == null)
			{
				trace("PANIC - there is now place for new teamMate - check number of mates")
				return null;
			}

			_arrayOfTeamMatesInUse.push(newMateForUse);
			newMateForUse.id = ID;
			_partyIDsDict[newMateForUse] = partyID;

			ArrangeItems();
			return newMateForUse;
		}

		public function DoesHeroExist(_id:int):Boolean
		{
			for (var index:int =0; index<_arrayOfTeamMatesInUse.length; index++)
				if (_id == _arrayOfTeamMatesInUse[index].id)
					return true;

			return false;
		}

		private function GetNewMateInfoInUseFromStartMates():LoaderTeamMate
		{
			for (var i:int = 0; i < _TeammatesMovieclips.length;i++)
			{
				if (_TeammatesMovieclips[i]!=null&&!_TeammatesMovieclips[i].isBusy)
				{
					_TeammatesMovieclips[i].isBusy = true;
					_TeammatesMovieclips[i].visible = true;

					BaseBarObjectResize();

					return _TeammatesMovieclips[i];
				}
			}
			return null;
		}

		private function SortFunction(a:LoaderTeamMate, b:LoaderTeamMate):Number
		{
			var ourParty:int = 0;

			if (OurHeroID != -1)
			{
				if (a.id == OurHeroID )
					return -1;

				if (b.id == OurHeroID)
					return 1;

				for each (var item:LoaderTeamMate in _TeammatesMovieclips)
				{
					if (item.id != OurHeroID)
						continue;

					ourParty = _partyIDsDict[item];
				}
			}


			if (ourParty != 0)
			{
				if (_partyIDsDict[a] == ourParty && _partyIDsDict[b]!=ourParty)
					return -1;

				if (_partyIDsDict[b] == ourParty && _partyIDsDict[a] != ourParty)
					return 1;

				if (_partyIDsDict[b] == _partyIDsDict[a] == ourParty)
					return 0;
			}

			if (_partyIDsDict[a] > _partyIDsDict[b])
				return -1;

			if (_partyIDsDict[a] < _partyIDsDict[b])
				return 1;

			if (_partyIDsDict[a] == _partyIDsDict[b])
				return 0;


			return 0;
		}

		private function ArrangeItems():void
		{
			_arrayOfTeamMatesInUse.sort(SortFunction);
			if (_isOurIsElfTeam) _arrayOfTeamMatesInUse.reverse();

			var n = _arrayOfTeamMatesInUse.length;
			for (var i:int = 0; i < _arrayOfTeamMatesInUse.length; i++)
			{
				_arrayOfTeamMatesInUse[i].x = _startTeamMateXPositions[i];
			}

			SetChains();
		}

		private function SetChains():void

		{
			for (var j:int = 0; j < _chainLockMovieClips.length; j++)
			{
				_chainLockMovieClips[j].visible = false;
				_chainLockMovieClips[j].stop();
			}

			for (var i:int = 0; i < _arrayOfTeamMatesInUse.length - 1; i++)
			{
				if (_partyIDsDict[_arrayOfTeamMatesInUse[i]] == 0 && _partyIDsDict[_arrayOfTeamMatesInUse[i + 1]] == 0 || _partyIDsDict[_arrayOfTeamMatesInUse[i]] != _partyIDsDict[_arrayOfTeamMatesInUse[i + 1]])
					continue;

				_chainLockMovieClips[i].visible = true;

				_chainLockMovieClips[i].gotoAndStop(1);
			/*	if (_isOurIsElfTeam)
				_chainLockMovieClips[i].gotoAndStop(2);*/
			}
		}

		public function get PersentOfLoading():Number
		{
			var persent:Number=0;
			for (var i:int = 0; i < _arrayOfTeamMatesInUse.length; i++)
			{
				persent += _arrayOfTeamMatesInUse[i].LoadingProgressBar;
			}
			if (_arrayOfTeamMatesInUse.length == 0)
				return 500;

			return (persent/_arrayOfTeamMatesInUse.length)*5;
		}

		public function set BotName(value:String):void
		{
			for each(var teamMate:LoaderTeamMate in _TeammatesMovieclips)
			{
				teamMate.heroName = value;
			}
		}

		public function RemoveAllRaitings():void
		{
			for each (var item:LoaderTeamMate in _TeammatesMovieclips)
			{
				item.raitingBar.visible = false;
			}
		}

		public function GetVisibleWidth():Number
		{
			var num:int = 0;

			for ( var i:int = 0; i < _TeammatesMovieclips.length; i++)
			{
				if (_TeammatesMovieclips[i].visible)
				{
					num++;
				}
			}
			return num * heroTeamMate1_mc.GetMateWidth()*scale;
		}
	}
}