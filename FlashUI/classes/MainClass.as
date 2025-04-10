package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import MyButton;
	import ToggleButton;
	import TextToggleButton;
	import ImageToggleButton;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
		
	public class MainClass extends MovieClip {
		
		public	var filter_tb:ToggleButton;
		public	var filter_btn:MyButton;
		public 	var ldr:ImgLoader;
		public 	var start_btn:ImageToggleButton;
		public 	var text_tb:TextToggleButton;
		public 	var bt:Boolean = true;
		private var myText:TextField = new TextField();
		private	var togText:String = "КУКУ!";
		public 	var ico:ImgLoader;
		public 	var heroItem_mc:HeroItem;
		public var	but_1:MyButton;
		public var	but_2:MyButton;
		public var	but_3:MyButton;
		
		private var heroIcons:Array = ["13.png","14.png","15.png"]
		
		private var heroes:Array = new Array();
		
		
		public function MainClass()
		{
			addEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
		// constructor code
		}
		
		private function OnAddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			ldr.Stretch=ldr.StretchToFit;
			filter_tb.addEventListener(MouseEvent.CLICK,OnTbClick);
			filter_btn.addEventListener(MouseEvent.CLICK, OnBtnClick);
			start_btn.SetImg("13.png");
			start_btn.addEventListener(MouseEvent.CLICK, OnStartClick);
			but_1.addEventListener(MouseEvent.CLICK, OnButton1Click);
			but_2.addEventListener(MouseEvent.CLICK, OnButton2Click);
			but_3.addEventListener(MouseEvent.CLICK, OnButton3Click);
			text_tb.SetText(togText);
			
			GenerateHeroes(3);
			heroItem_mc.SetHero(heroes[0]);
		}
		
		private function GenerateHeroes(count:int):void 
		{
			for (var i:int = 0; i < count; i++) 
			{
				var newHero:HeroData = new HeroData();
				newHero.Name = "Hero " + i;
				newHero.Level = 10 + i;
				newHero.Icon = heroIcons[i];
				newHero.Energy = 30 + i * 10;
				newHero.Workstate = i + 2;
				newHero.FameNeeded = 11 + i;
				newHero.IsBought = i == 0? true:false;
				
				var leftPrice:ResourceData = new ResourceData();
				leftPrice.Cost = 10 + i * 100;
				leftPrice.ResourceType = ResourceData.Silver;
				
				var rightPrice:ResourceData = new ResourceData();
				rightPrice.Cost = 20 + i * 200;
				rightPrice.ResourceType = ResourceData.Gold;
				
				newHero.priceGold = rightPrice;
				newHero.priceSilver = leftPrice;
				
				heroes.push(newHero);
			}
		}
		
		private function OnButton3Click(e:MouseEvent):void 
		{
			heroItem_mc.SetHero(heroes[2]);
		}
		
		private function OnButton2Click(e:MouseEvent):void 
		{
			heroItem_mc.SetHero(heroes[1]);
		}
		
		private function OnButton1Click(e:MouseEvent):void 
		{
			heroItem_mc.SetHero(heroes[0]);
		}
		
		private function OnStartClick(e:MouseEvent):void 
		{
			ldr.SetImage("start.png")
		}
		
		private function OnTbClick(e:MouseEvent):void
		{
			ldr.SetImage("test.png")
		}
		
		private function OnBtnClick(e:MouseEvent):void
		{
			myText.selectable = false;
			myText.x = 100;
			myText.y = 0;
			if (bt) {myText.text = "Вы нажали кнопко!"}
			else {myText.text = "Вы опять нажали кнопко!"}
			this.addChild(myText);
			bt=!bt;
		}
	}
}