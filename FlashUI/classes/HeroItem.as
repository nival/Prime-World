package 
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import MyButton;
	
	public class HeroItem extends MovieClip
	{
		public var heroPanelContainerOver: MovieClip;
		public var name_txt: TextField;
		public var roundBarControl: BarControl;
		public var heroPanelFrame: MovieClip;
		public var level_plate: MovieClip;
		public var workHeroPanel_mc: MovieClip;
		public var low_Level: MovieClip;
		public var heroPanelQuest_btn: MyButton;
		public var heroPanelBuy_btn:MyButton;
		public var heroPanelInfo_btn: MyButton;
		public var tutorialItemHighlight: MovieClip;
		public var heroPanelHeroIcon_icn: ImgLoader;
		public var heroPanelSilverCost_mc: priceClass;
		public var heroPanelZZGoldCost_mc: priceClass;
		public var heroPanelConditionQuest_img:MovieClip;
		public var state:Number;
		
		public function HeroItem()
		{
			addEventListener(Event.ADDED_TO_STAGE, OnAdded2Stage);
			stop();
		}
		
		private function OnAdded2Stage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAdded2Stage);
			tutorialItemHighlight.stop();
			roundBarControl.SetBarPosition(1);
			roundBarControl.SetMarkerPosition(1);
			level_plate.gotoAndStop(1);
			workHeroPanel_mc.gotoAndStop(1);
		}
		
		private function onInfo(e:MouseEvent):void 
		{
			trace ("Info button click");
		}
		
		private function onQuest(e:MouseEvent):void 
		{
			trace ("Quest button click");
		}
		
		private function onBuy(e:MouseEvent):void 
		{
			trace ("Buy button click");
		}
		
		public function SetHero(hero:HeroData):void 
		{
			tutorialItemHighlight.stop();
			name_txt.text = hero.Name;
			heroPanelHeroIcon_icn.SetImage(hero.Icon);

			if (hero.IsBought)
			{
				SetBoughtState(hero);
				level_plate.gotoAndStop(1);
				heroPanelQuest_btn.addEventListener(MouseEvent.CLICK, onQuest);
				workHeroPanel_mc.gotoAndStop(hero.Workstate);
				return;
			}
			
			if (hero.FameNeeded > 12)
			{
				SetDisabled(hero);
				return;
			}			
			SetCanBuyState(hero);
		}
		
		private function SetBoughtState(hero:HeroData):void 
		{
			this.gotoAndStop(1);
			roundBarControl.SetBarPosition(hero.Energy);
			roundBarControl.SetMarkerPosition(20);
			heroPanelInfo_btn.addEventListener(MouseEvent.CLICK, onInfo);
		}
		
		private function SetCanBuyState(hero:HeroData):void 
		{
			this.gotoAndStop(2);
			heroPanelSilverCost_mc.SetCost(hero.priceSilver);
			heroPanelZZGoldCost_mc.SetCost(hero.priceGold);
			heroPanelBuy_btn.addEventListener(MouseEvent.CLICK, onBuy);
			heroPanelInfo_btn.addEventListener(MouseEvent.CLICK, onInfo);
		}
		
		private function SetDisabled(hero:HeroData):void 
		{
			this.gotoAndStop(3);
			heroPanelSilverCost_mc.SetCost(hero.priceSilver);
			heroPanelZZGoldCost_mc.SetCost(hero.priceGold);
			low_Level.stop();
			heroPanelBuy_btn.addEventListener(MouseEvent.CLICK, onBuy);
			heroPanelInfo_btn.addEventListener(MouseEvent.CLICK, onInfo);
		}
	}
}