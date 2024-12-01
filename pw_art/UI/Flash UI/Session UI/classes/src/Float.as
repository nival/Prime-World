package src
{
	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.events.Event;

	public class Float extends Sprite
	{
		public var myTitle:TextField;
		public var myLoaderBG:SimpleLoader;

		public function Float(Title:String)
		{
			var myLoader:SimpleLoader = new SimpleLoader("../../pict/talentsBar/float.png");
			myLoader.addEventListener("INIT",onInit);

			myLoaderBG = new SimpleLoader("../../pict/talentsBar/blueGlow.png");
			myLoaderBG.addEventListener("INIT",onInitBG);
			myLoaderBG.blendMode = "add"

			myTitle=new TextField();
			myTitle.autoSize = TextFieldAutoSize.CENTER;
			TextFieldFormat.Format(myTitle);
			myTitle.selectable = false;
			myTitle.text = Title;

			function onInit(e:Event):void
			{
				var contSp:Sprite = new Sprite();
				myLoader.removeEventListener("INIT",onInit);

				contSp.addChild(myLoader.getChildAt(0));

				contSp.y =  -  contSp.height / 2;

				myTitle.x = (contSp.width-myTitle.width-3)/2;
				myTitle.y = 10;
				myLoaderBG.alpha = 0;

				contSp.addChild(myTitle);
				contSp.addChild(myLoaderBG);
				addChild(contSp);
			}
			function onInitBG(e:Event):void
			{
				myLoaderBG.getChildAt(0).x = -10;
				myLoaderBG.getChildAt(0).y = -12;
			}
		}
	}
}