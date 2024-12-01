package MainScreen
{
	import Events.ContextMenuEvent;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextField;
	import BaseClasses.MateInfoBase;
	import Components.RoundFrame;
	import Events.WindowVisibleControllerEvent;
	import Enums.EWindows;
	import Strokes.SelectionLevelStroke;
	import Strokes.Stroke;
	import Utils.AnimatedPortraitsUtils;
	
	public class SelectionMateInfo extends MateInfoBase
	{
		
		//reference
		public var round_mc:RoundFrame;
		private var anotherHero:Boolean = false;
		public var animatedIcoContainer:MovieClip;

		public function SelectionMateInfo()
		{
			mouseCatcher.buttonMode = true;
			mouseCatcher.doubleClickEnabled = true;
			
			roundFrame.mouseEnabled = false;
			roundFrame.mouseChildren = false;
		}
		
		override protected function Init():void 
		{
			super.Init();
		}
		
		override protected function onDown(e:MouseEvent):void
		{
			FSCommands.Send(FSCommands.SELECTION_CLICK);
			e.stopPropagation();
		}
		
		override protected function onUp(e:MouseEvent = null):void
		{
			FSCommands.Send(FSCommands.HERO_LOSTFOCUS);
			
			if (e)
			{
				e.stopPropagation()
				super.onUp(e);
			}
		}

		override protected function onDoubleClick(e:MouseEvent):void
		{
			FSCommands.Send(FSCommands.SELECTION_DOUBLECLICK);
			e.stopPropagation();
		}
		
		override public function set level(value:int):void 
		{
			if(_level == value)
			{
				return;
			}
			_level = value;
			level_txt.text = _level.toString();
			
			if (anotherHero)
			{
				anotherHero = false;
			}
			else StartGlow(); 
		}
		
		override public function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void 
		{
			anotherHero = true;
			
			var classObject:Object = AnimatedPortraitsUtils.FindClassObject(path, isAnimatedAvatar);
			
			// нашли подходящий анимированный портрет - грузим анимацию
			if (classObject != null)
			{
				AnimatedPortraitsUtils.ClearContainer(animatedIcoContainer);
								
				heroIco_mc.visible = false;
				animatedIcoContainer.visible = true;
				
				var iconClass:Class = classObject as Class;
				var animatedIcon:MovieClip = new iconClass();
				animatedIcoContainer.addChild(animatedIcon);
				
				// размер иконки 166, размер места под иконку 105
				// 105 / 166 == 0.63
				animatedIcon.scaleX = 0.63;
				animatedIcon.scaleY = 0.63;
			}
			else
			{
				heroIco_mc.visible = true;
				animatedIcoContainer.visible = false;
				super.setHeroInfoIcon(path, false);
			}
		}
		
		override public function ShowTutorialLevelHighlight(show:Boolean):void 
		{
			if (show)
			{
				if (tutorialLevelHighlight != null) return;
			
				tutorialLevelHighlight = new SelectionLevelStroke();
				tutorialLevelHighlight.x = round_mc.x + round_mc.width / 2 - tutorialLevelHighlight.width / 2;
				tutorialLevelHighlight.y = round_mc.y + round_mc.height / 2 - tutorialLevelHighlight.height / 2;
				this.addChild(tutorialLevelHighlight);
			}
			else
			{
				if (tutorialLevelHighlight!=null)
					this.removeChild(tutorialLevelHighlight);
			}
		}
		
	}
}