package src
{
	import flash.display.Sprite;
	import flash.display.Shape;
	import flash.display.Loader;
	import flash.display.BlendMode;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.net.URLRequest;
	import flash.events.Event;

	public class HeroInfo extends Sprite
	{

		private var myBigRadius:Number;
		private var mySmallRadius:Number;
		
		public var CharacterName:TextField;
		public var CharacterLevel:TextField;
		public var ico:Loader;

		public function HeroInfo(bigRadius:Number,smallRadius:Number)
		{
			myBigRadius = bigRadius;//тут идет полный писец - разные условия
			mySmallRadius = smallRadius;

			var tickness:uint = 2;
			var posY:Number=0;
			
			if (myBigRadius < 150)
			{
				tickness = 1;
			}
			if(myBigRadius<=72){
				posY=5;
			}

			var bigRoundSp:Sprite = new Sprite();

			var selfShadowBig:selfShadow_mc=new selfShadow_mc();
			selfShadowBig.width = selfShadowBig.height = myBigRadius;
			bigRoundSp.addChild(selfShadowBig);

			var nameBackSp:nameBack = new nameBack();
			nameBackSp.width = nameBackSp.height = myBigRadius;
			bigRoundSp.addChild(nameBackSp);
			bigRoundSp.blendMode = BlendMode.LAYER;

			var bigRound:RoundFrame = new RoundFrame(5,tickness,myBigRadius / 2);//переключаем толщину линии на 1 если размер круга меньше 150 pix иначе все не красиво.
			bigRoundSp.addChild(bigRound);

			ico = new Loader();
			ico.addEventListener(Event.INIT,icoInit);
			bigRoundSp.addChild(ico);

			var halfShadow:halfShadow_mc = new halfShadow_mc();
			halfShadow.width = halfShadow.height = myBigRadius;
			bigRoundSp.addChild(halfShadow);

			var light:SimpleLoader = new SimpleLoader("../../pict/general/lensFlare.png");
			light.blendMode = BlendMode.ADD;
			light.alpha = 0.8;
			light.x = -12;
			light.y = -12;
			halfShadow.addChild(light);

			var smallRoundMask:Shape = new Shape();
			smallRoundMask.graphics.beginFill(0x000000);
			smallRoundMask.graphics.drawCircle(mySmallRadius/2,mySmallRadius/2,mySmallRadius/2);
			smallRoundMask.graphics.endFill();
			smallRoundMask.x = myBigRadius / 25 + tickness;
			//smallRoundMask.y = myBigRadius - smallRoundMask.width - myBigRadius / 25 + tickness;//как было изначально
			smallRoundMask.y = myBigRadius - smallRoundMask.width+posY + tickness;//это когда большой круг типа так ;( кружок стоит на полу
			smallRoundMask.blendMode = BlendMode.ERASE;
			bigRoundSp.addChild(smallRoundMask);

			addChild(bigRoundSp);

			var CharacterName = new TextField();
			CharacterName.autoSize = TextFieldAutoSize.LEFT;
			TextFieldFormat.Format(CharacterName,myBigRadius/6);
			CharacterName.text = "Hero";
			CharacterName.x=smallRoundMask.x+smallRoundMask.width+myBigRadius/25;
			CharacterName.y=myBigRadius/1.39

			addChild(CharacterName);

			var selfShadowSmall:selfShadow_mc=new selfShadow_mc();
			selfShadowSmall.width = selfShadowSmall.height = mySmallRadius;
			selfShadowSmall.x = smallRoundMask.x;
			selfShadowSmall.y = smallRoundMask.y;
			addChild(selfShadowSmall);

			var smallRound:RoundFrame = new RoundFrame(2,tickness,mySmallRadius/2);
			smallRound.x = smallRoundMask.x;
			smallRound.y = smallRoundMask.y;
			addChild(smallRound);

			var CharacterLevel = new TextField();
			CharacterLevel.autoSize = TextFieldAutoSize.CENTER;
			TextFieldFormat.Format(CharacterLevel,myBigRadius/6);
			CharacterLevel.text = "0";
			CharacterLevel.x=(smallRound.width-CharacterLevel.width)/2;
			CharacterLevel.y=(smallRound.height-CharacterLevel.height)/2;

			smallRound.addChild(CharacterLevel);
		}
		private function icoInit(e:Event):void
		{
			ico.width = myBigRadius;
			ico.height = myBigRadius;
		}
	}
}