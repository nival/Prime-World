package TalentBar
{
	import ActionBar.ActionBar;
	import flash.display.MovieClip;
	import flash.events.Event;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.easing.None;
	import fl.transitions.TweenEvent;
	import flash.text.TextField;
	import BaseClasses.BaseDragObject;
	import Enums.TalentUIState;
	import Interfaces.IShowImpulseTalent;
	public class TalentsBar extends BaseDragObject
	{
		private var naftaLevelHeightTween:Tween;//Nafta height
		private var floatFlashInTween:Tween;//Float alpha In;
		private var floatFlashOutTween:Tween;//Out
		private var floatVerticalPositionTween:Tween;//Float y;
		private var waveHeightTween:Tween;//Wave height;
		private var waveVerticalPositionTween:Tween;//Wave y;
		private var waveMaskVerticalPositionTween:Tween;//WaveMask y;
		private var waveEffectVerticalPositionTween:Tween;

		private var thisWidth:Number = 552;
		private var thisHeight:Number = 561;

		private var myLevel:int=0;

		private var flaskHeight:int = 493;//534
		private var maxLevel:int = 20;
		private var segment:int = 82;//534/6
		private var levelPix:Number = 493 / (6*4);//17,8  //размер одного ячейки уровня.
		private const otstup:int = 23//отступ снизу из-за неровности графики;
		private const waveMaskOffset:int = 3;//отступ анимированной маски вниз от ватерлинии для того чтобы ее края не стробили в игре;

		private var talentBar_arr:Array;
		private const RAW:int = 6;
		private var currentWaterLevel:int = -1;

		private var isTopLevelFilled:Boolean;
		
		public var float_mc:MovieClip;
		public var nafta_mc:MovieClip;
		public var waveEffect2_mc:MovieClip;
		public var wave_mc:MovieClip;
		public var waveMask_mc:MovieClip;
		public var talentMask_mc:MovieClip;
		public var header_txt:TextField;
		public var secondLevel:MovieClip;
		
		public var secondRawHighlighter:MovieClip;
		
		private var isWaveEffectPlaying:Boolean;
		public var talent1_1:Talent;
		public var talent1_2:Talent;
		public var talent1_3:Talent;
		public var talent1_4:Talent;
		public var talent1_5:Talent;
		public var talent1_6:Talent;
		public var talent2_1:Talent;
		public var talent2_2:Talent;
		public var talent2_3:Talent;
		public var talent2_4:Talent;
		public var talent2_5:Talent;
		public var talent2_6:Talent;
		public var talent3_1:Talent;
		public var talent3_2:Talent;
		public var talent3_3:Talent;
		public var talent3_4:Talent;
		public var talent3_5:Talent;
		public var talent3_6:Talent;
		public var talent4_1:Talent;
		public var talent4_2:Talent;
		public var talent4_3:Talent;
		public var talent4_4:Talent;
		public var talent4_5:Talent;
		public var talent4_6:Talent;
		public var talent5_1:Talent;
		public var talent5_2:Talent;
		public var talent5_3:Talent;
		public var talent5_4:Talent;
		public var talent5_5:Talent;
		public var talent5_6:Talent;
		public var talent6_1:Talent;
		public var talent6_2:Talent;
		public var talent6_3:Talent;
		public var talent6_4:Talent;
		public var talent6_5:Talent;
		public var talent6_6:Talent;
		public var ImpulseShower:IShowImpulseTalent;
		
		public function TalentsBar()
		{	
			
			talentBar_arr = [talent1_1,talent1_2,talent1_3,talent1_4,talent1_5,talent1_6,talent2_1,talent2_2,talent2_3,talent2_4,talent2_5,talent2_6,talent3_1,talent3_2,talent3_3,talent3_4,talent3_5,talent3_6,talent4_1,talent4_2,talent4_3,talent4_4,talent4_5,talent4_6,talent5_1,talent5_2,talent5_3,talent5_4,talent5_5,talent5_6,talent6_1,talent6_2,talent6_3,talent6_4,talent6_5,talent6_6];
			
			for (var i:int = 0; i < talentBar_arr.length; i++ ) 
			{
				talentBar_arr[i].TalantIndex = i;
			}
			//Анимация поднятия уровня нафты
			naftaLevelHeightTween = new Tween(nafta_mc,"height",Strong.easeOut,nafta_mc.height,segment + otstup,25,false);
			naftaLevelHeightTween.stop();
			//Анимация поднятия уровня поплавка
			floatVerticalPositionTween = new Tween(float_mc,"y",Strong.easeOut,float_mc.y,segment + otstup,45,false);
			floatVerticalPositionTween.stop();
			//анимация поднятия уровня анимации вспышки на воде
			waveEffectVerticalPositionTween = new Tween(waveEffect2_mc,"y",Strong.easeOut,waveEffect2_mc.y,segment + otstup,45,false);
			waveEffectVerticalPositionTween.stop();
			//анимация увеличения высоты воды
			waveHeightTween = new Tween(wave_mc,"height",Strong.easeOut,segment,segment + otstup,45,false);
			waveHeightTween.stop();
			//анимация поднятия уровня воды
			waveVerticalPositionTween = new Tween(wave_mc,"y",Strong.easeOut,thisHeight - wave_mc.height,segment + otstup,45,false);
			waveVerticalPositionTween.stop();
//			//анимация поднятия уровня маски воды
			waveMaskVerticalPositionTween = new Tween(waveMask_mc, "y", Strong.easeOut, thisHeight - wave_mc.height + waveMaskOffset,segment + otstup,45,false);
			waveMaskVerticalPositionTween.stop();
			//анимация затухания вспышки на поплавке
			floatFlashOutTween = new Tween(float_mc.blueGlow_mc,"alpha",Strong.easeInOut,1,0,30,false);
			floatFlashOutTween.addEventListener(TweenEvent.MOTION_FINISH, FOutFinish);
			floatFlashOutTween.stop();
			//анимация вспышки на поплавке
			floatFlashInTween = new Tween(float_mc.blueGlow_mc, "alpha", Strong.easeInOut, 0, 1, 10, false);
			floatFlashInTween.stop();
			
			floatFlashInTween.addEventListener(TweenEvent.MOTION_FINISH, FAIFinish);
			float_mc.blueGlow_mc.visible = false;
			
			this.mask = talentMask_mc;
			waveEffect2_mc.addEventListener(Event.ENTER_FRAME, waveEnterFrame);
			waveEffect2_mc.stop();
			waveEffect2_mc.mouseEnabled = false;
			
			this.mouseEnabled = false;
		//	StartLevelVisualisation();
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
		}
		
		private function FillLocalization(e:Event):void
		{
			header_txt.text = Localization.TalantsBar_HeaderText;
		}		
		
			
		public function get iconArray():Array
		{
			return talentBar_arr;
		}

		public function GetTalent(col:int, row:int):Talent
		{
			if (col < 0) return null;
			if (row < 0) return null;

			var count:int = talentBar_arr.length / RAW;

			if (col >= count) return null;
			if (row >= count) return null;

			return talentBar_arr[row * RAW + col];
		}

		public function SetIcon(column:int, raw:int, path:String, altPath:String, isActive:Boolean, desiredIndex:int, upgradeLevel:int, isClassTalent:Boolean, price:int)
		{
			var talent:Talent = GetTalent(column,raw);

			if (talent == null) return;
			
			talent.column = column;
			talent.raw = raw;
			talent.icon = path;
			talent.altIcon = altPath;
			talent.IsActive = isActive;
			talent.DesiredIndex = desiredIndex;
			talent.IsClassTalent = isClassTalent;
			talent.setOnTur();
			talent.price = price;
			talent.SetUpgradeLevel(upgradeLevel);
		}

		public function setState(column:int,raw:int,state:int)
		{
			var talent:Talent = GetTalent(column,raw);

			if (talent == null)	return;
		
			switch (state)
			{
				case TalentUIState.BOUGHT :
					{
						talent.icoState = TalentUIState.BOUGHT;
						talent.setEnable();
						talent.RemoveCanBuyEffect();
						break;

					};
				case TalentUIState.CANBUY :
					{
						talent.icoState = TalentUIState.CANBUY;
						talent.setCanBuy();
						talent.ApplyCanBuyEffect();
						break;

					};
				case TalentUIState.NOTENOUGH_DEV_POINTS :
					{
						talent.icoState = TalentUIState.NOTENOUGH_DEV_POINTS;
						talent.setOnTur();
						talent.RemoveCanBuyEffect();
						break;

					};
				case TalentUIState.NOTENOUGH_PRIME :
					{
						talent.icoState = TalentUIState.NOTENOUGH_PRIME;
						talent.setNoNafta();
						talent.RemoveCanBuyEffect();
						break;

					};
				default :
					{
						/*trace поставь фигню передали*/
					}
			}
		};

		public function onStateChanged():void
		{
			var topLevel:int = GetWaterLevel();
			var minLevel:int = topLevel;

			if (IsTalentLevelBought(topLevel))
			{
				minLevel = 0;
			}

			var talent:Talent;

			for (var level:int = 0; level < RAW; ++level)
			{
				for (var slot:int = 0; slot < RAW; ++slot)
				{
					talent = GetTalent(slot, level);

					if (!IsValidTalent(talent))
						continue;

					if (talent.icoState == TalentUIState.CANBUY)
					{
						ImpulseShower.AddImpulseTalent(talent, topLevel, minLevel);
					}
					else
					{
						ImpulseShower.RemoveImpulseTalent(talent);
					}
				}
			}

			ImpulseShower.ShowImpulseTalent();
		}

		/////////////////////////////////////////////////Level
		private function IsValidTalent(talent:Talent):Boolean
		{
			if (talent == null)
				return false;
			if (talent.icon == null)
				return false;
			if (talent.icon.length == 0)
				return false;

			return true;
		}

		private function IsTalentLevelBought(level:int):Boolean
		{
			for (var i:int = 0; i < RAW; ++i)
			{
				var talent:Talent = GetTalent(i, level);

				if (!IsValidTalent(talent))
					continue;

				if (talent.icoState != TalentUIState.BOUGHT)
					return false;
			}

			return true;
		}

		public function set Level(level:int):void
		{
			if (myLevel == level) return;
				
			myLevel = level;
			
			float_mc.level_txt.text = myLevel.toString();
			StartLevelVisualisation();
		}
		public function get Level():int
		{
			return myLevel;
		}
		
		private function StartLevelVisualisation():void
		{
			ProcessNaftaLevelAnimation();

			var waterLevel:int = GetWaterLevel();

			if (currentWaterLevel == waterLevel) 
			{
				floatFlashInTween.start();
				return;
			}
			
			currentWaterLevel = waterLevel;
			
			var level:int = myLevel > maxLevel? maxLevel : myLevel;
			
			var levelSegment:uint = level - level % 4;
			
			var currentWaterHeight:Number = thisHeight - levelSegment * levelPix - segment - otstup;
			
			floatVerticalPositionTween.stop();
			floatVerticalPositionTween.continueTo(currentWaterHeight,45);
			floatVerticalPositionTween.start();
			
			waveVerticalPositionTween.stop();
			waveVerticalPositionTween.continueTo(currentWaterHeight,45);
			waveVerticalPositionTween.start();
			
			waveMaskVerticalPositionTween.stop();
			waveMaskVerticalPositionTween.continueTo(currentWaterHeight + waveMaskOffset,45);
			waveMaskVerticalPositionTween.start();
			
			waveEffectVerticalPositionTween.stop();
			waveEffectVerticalPositionTween.continueTo(currentWaterHeight,45);
			waveEffectVerticalPositionTween.start();
			
			PlayWaveAnimation();
			
			waveHeightTween.stop();
			waveHeightTween.continueTo(570 - currentWaterHeight,45);
			waveHeightTween.start();
			isWaveEffectPlaying = false;
		}
		
		private function PlayWaveAnimation():void
		{
			if (isWaveEffectPlaying) return;
			
			waveEffect2_mc.gotoAndStop(1);
			waveEffect2_mc.gotoAndPlay(1);
			waveEffect2_mc.visible = true;
			isWaveEffectPlaying = true;
		}

		public function ProcessNaftaLevelAnimation():void
		{
			if (currentWaterLevel == 5) return;
			
			var level:int = myLevel > maxLevel? maxLevel : myLevel;
			var pix:Number = levelPix * level; 
			
			naftaLevelHeightTween.stop();
			naftaLevelHeightTween.continueTo(segment + otstup + pix,25);
			naftaLevelHeightTween.start();
		}
		
		public function GetWaterLevel():int
		{
			var talent:Talent;

			for (var row:int = RAW; row > 0; )
			{
				--row;

				for (var col:int = 0; col < RAW; ++col)
				{
					talent = GetTalent(col, row);

					if (!IsValidTalent(talent))
						continue;

					if (talent.icoState != TalentUIState.NOTENOUGH_DEV_POINTS)
						return row;
				}
			}

			return 0;
		}
		
		public function HeroIsDead(isHeroDead:Boolean):void 
		{
			for each(var talent:Talent in talentBar_arr) 
			{
				talent.HeroIsDead(isHeroDead);
			}
		}
		
		public function ResetTalentBar():void 
		{			
			for each(var talent:Talent in talentBar_arr) 
			{
				talent.icoState = TalentUIState.CANBUY;
			}
		}
		
		private function waveEnterFrame(e:Event):void
		{
			if (e.target.currentFrame == 17)
			{
				float_mc.blueGlow_mc.visible = true;
				floatFlashInTween.start();
			}
		}
		private function FAIFinish(e:TweenEvent):void
		{
			floatFlashOutTween.start();
		}
		private function FOutFinish(e:TweenEvent):void
		{
			float_mc.blueGlow_mc.visible = false;
		}
	}
}