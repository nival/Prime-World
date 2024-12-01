package src{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.getTimer;
	import flash.text.TextFormat;

	public class FPSCounter extends Sprite {
		private var last:uint=getTimer();
		private var ticks:uint=0;
		private var tf:TextField;

		public function FPSCounter(xPos:int=5, yPos:int=20, color:uint=0xffffff, fillBackground:Boolean=true, backgroundColor:uint=0x000000) {
			x=xPos;
			y=yPos;
			
			var my_fmt:TextFormat = new TextFormat();
			my_fmt.size = 14;
	 
			tf = new TextField();
			tf.textColor=color;
			tf.text="----- fps";
			tf.selectable=false;
//			tf.background=fillBackground;
//			tf.backgroundColor=backgroundColor;
			tf.autoSize=TextFieldAutoSize.LEFT;
			tf.textColor = 0x000000
			tf.defaultTextFormat = my_fmt;
			addChild(tf);
//			width=tf.textWidth;
//			height=tf.textHeight;
			addEventListener(Event.ENTER_FRAME, tick);
		}

		public function tick(evt:Event):void {
			ticks++;
			var now:uint=getTimer();
			var delta:uint=now-last;
			if (delta>=1000) {
				
				var fps:Number=ticks/delta*1000;
				tf.text=fps.toFixed(1)+" fps";
				ticks=0;
				last=now;
			}
		}
	}
}