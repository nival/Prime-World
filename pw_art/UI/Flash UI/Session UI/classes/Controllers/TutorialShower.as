package Controllers 
{
	import ActionBar.ActionButtonPortal;
	import CharStat.CharStats;
	import Chat.ChatBar;
	import Components.ButtonStandart;
	import Components.RulerButton;
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	public class TutorialShower 
	{
		private var tutorialElements:Array = new Array();
		private var time:Number = 20;//время анимации
		
		public function TutorialShower( elements:Array) 
		{
			tutorialElements = elements;
		}
		
		public function ShowElements(show:Boolean):void
		{
			for each (var item:MovieClip in tutorialElements) 
			{			
				if (item == null)
					continue;
					
				if (item is RulerButton) 
				{
					var rulerBtn: RulerButton = item as RulerButton;
					if (show)
						rulerBtn.EnableButton();
					else
						rulerBtn.DisableButton();
					continue;
				}
				
				if (item is ActionButtonPortal)
				{
					var portal:ActionButtonPortal = item as ActionButtonPortal;
					
					portal.EnableForTutorial(show);
					continue;
				}
				
				if (item is ButtonStandart) 
				{
					var btn:ButtonStandart = item as ButtonStandart;
					
					btn.EnableButton = show;
					continue;
				}
				
				item.visible = show;
				
				if (item is ChatBar) 
				{
					var chatBar:ChatBar = item as ChatBar;
					chatBar.DisableInput(!show);
				}
				
				if (show)
				{
					var tweenAlphaIn:Tween = new Tween(item, 'alpha', Strong.easeOut, 0, 1, time);
					tweenAlphaIn.start();
				}
			}
		}
	}
	

}