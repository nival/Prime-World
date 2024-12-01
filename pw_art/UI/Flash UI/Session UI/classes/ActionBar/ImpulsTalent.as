package ActionBar 
{
	import Enums.TalentUIState;
	import flash.display.MovieClip;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import TalentBar.Talent;
	public class ImpulsTalent extends MovieClip
	{	
		public var impulsTalentIcoCont_mc:ImpulsTalentIco;
		public var impulsTalentEffect_mc:MovieClip;

		private var talentQueue:Array = new Array();
		private var isShowing:Boolean = false;

		private var _topLevel:int = 0;
		private var _minLevel:int = 0;

		public function ImpulsTalent()
		{
			impulsTalentEffect_mc.mouseEnabled = false;
			impulsTalentEffect_mc.mouseChildren = false;
			impulsTalentEffect_mc.gotoAndStop(1);
		}
		
		public function AddImpulseTalent(talent:Talent, topLevel:int, minLevel:int):void 
		{	
			if (talent == null) return;

			_topLevel = topLevel;
			_minLevel = minLevel;

			if (_topLevel < _minLevel)
			{
				_topLevel = _minLevel;
			}

			var i:int = talentQueue.indexOf(talent);

			if (i < 0)
			{
				DoInsertTalent(talent);
			}
		}
		
		public function RemoveImpulseTalent(talent:Talent):void 
		{
			if (talent == null) return;

			var i:int = talentQueue.indexOf(talent);

			if (i >= 0)
			{
				talentQueue.splice(i, 1);
			}
		}

		public function ShowImpulseTalent():void
		{
			if (talentQueue.length == 0)
			{
				DoHideImpulseTalent();
				return;
			}

			var talent:Talent = talentQueue[0];

			if ((talent.raw < _topLevel) &&
				(talent.raw < _minLevel))
			{
				if (talent.IsClassTalent)
				{
					// TODO: ?
				}
				else
				{
					DoHideImpulseTalent();
					return;
				}
			}

			DoShowImpulseTalent(talent);
		}

		private function DoInsertTalent(talent:Talent):void
		{
			var lhs:Talent = talent;
			var rhs:Talent;
			
			for (var i:int = 0; i < talentQueue.length; ++i) 
			{
				rhs = talentQueue[i];

				if (lhs.IsClassTalent == rhs.IsClassTalent)
				{
					if (lhs.raw < rhs.raw)
					{
						continue;
					}
					else if (lhs.raw > rhs.raw)
					{

					}
					else if (lhs.column > rhs.column)
					{
						continue;
					}
				}
				else
				{
					if (rhs.IsClassTalent)
					{
						continue;
					}
				}
				
				talentQueue.splice(i, 0, talent);
				return;
			}

			talentQueue.push(talent);
		}

		private function DoShowImpulseTalent(talent:Talent):void
		{
			if (impulsTalentIcoCont_mc.isShowing == false)
			{
				impulsTalentIcoCont_mc.isShowing = true;
				this.gotoAndPlay("start");
				impulsTalentEffect_mc.gotoAndPlay('start');
			}

			impulsTalentIcoCont_mc.StartShowingImpulseTimer(talent);
		}

		private function DoHideImpulseTalent():void
		{
			if (impulsTalentIcoCont_mc.isShowing == true)
			{
				impulsTalentIcoCont_mc.isShowing = false;
				this.gotoAndPlay("end");
				impulsTalentEffect_mc.gotoAndPlay('end');
			}

			impulsTalentIcoCont_mc.StartShowingImpulseTimer(null);
		}
		
		public function ShowNaftaShining():Boolean
		{
			return impulsTalentIcoCont_mc.isShowing;
		}
	}
}