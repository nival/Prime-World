package StatisticBars {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.geom.ColorTransform;
	import flash.display.Shape;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import fl.transitions.TweenEvent;
	import flash.events.Event;
	import src.ButtonTooltipEvent;
	
	public class StatLine extends MovieClip 
	{
		private var widthTweenFinish:Event
		//reference
		public var line_txt:TextField;
		public var ToolTipText:String = "";
		
		private var line_sh:Shape;
		
		private var widthTween:Tween;
		private var xposTween:Tween;
		private var alphaTween:Tween;
		
		private var textAlphaTween:Tween;
		
		private var xposTextTween:Tween;
		
		private var time:Number = 40;
		private var isCanBeShowed:Boolean;
		private var textAlphaTweenDuration:int = 20;
		
		
		private var durationKoeff:int = 15;
		public function StatLine() 
		{
			widthTweenFinish = new Event('wTweenFinish', true);
			
			line_txt.autoSize = TextFieldAutoSize.CENTER;
			line_txt.visible = false;
			
			line_sh = new Shape();
			line_sh.graphics.beginFill(0xffffff);
			line_sh.graphics.drawRect(0,0,715,23);
			line_sh.graphics.endFill();
			addChild(line_sh);
			setChildIndex(line_sh, 0);
			
			widthTween = new Tween(line_sh, 'width', Strong.easeOut, 0, 0, time);
			widthTween.stop();
			xposTween = new Tween(this, 'x', Strong.easeOut, 0, 0, time);
			widthTween.addEventListener(TweenEvent.MOTION_FINISH, wFinish);
			xposTween.stop();
			alphaTween = new Tween(this,'alpha', Strong.easeOut, 1, 1, time);
			alphaTween.stop();
			
			textAlphaTween = new Tween(line_txt, "alpha", Strong.easeOut, 0, 1, textAlphaTweenDuration);
			
			xposTextTween = new Tween(line_txt, 'x', Strong.easeOut, 1, 1, time);
			
			this.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			this.addEventListener(MouseEvent.MOUSE_MOVE, OnMouseMove);
		}
		
		private function OnMouseMove(e:MouseEvent):void 
		{
			if (!isCanBeShowed||ToolTipText.length == 0) return;
			
			var point:Point = new Point(this.mouseX, this.mouseY);
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, this.localToGlobal(point).x, this.localToGlobal(point).y, ToolTipText+" "+line_txt.text));
		}
		
		private function OnMouseOver(e:MouseEvent):void 
		{
			if (!isCanBeShowed||ToolTipText.length == 0) return;
			
			var globalPoint:Point = this.localToGlobal(new Point(this.mouseX, this.mouseY));
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, globalPoint.x, globalPoint.y, ToolTipText+" "+line_txt.text));
		}
		
		private function OnMouseOut(e:MouseEvent):void 
		{
			if (!isCanBeShowed||ToolTipText.length == 0) return;
			
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		

		public function set Color(color:Number):void
		{
			var colorTrans:ColorTransform = line_sh.transform.colorTransform;

			colorTrans.redMultiplier = (color >> 16 & 255) / 255;
			colorTrans.greenMultiplier = (color >> 8 & 255) / 255;
			colorTrans.blueMultiplier = (color & 255) / 255;

			line_sh.transform.colorTransform = colorTrans;
		}
		public function set Alpha(Alpha:Number):void
		{
			line_sh.alpha = Alpha;
		}
		public function Width(_width:Number, animate:Boolean = true):void
		{
			if(animate)
			{
				widthTween.stop();
				widthTween.begin = line_sh.width;
				widthTween.finish = _width;
				widthTween.duration = Math.abs(line_sh.width - _width) / durationKoeff;
				
				widthTween.start();
				
				xposTextTween.stop();
				xposTextTween.begin = line_txt.x;
				xposTextTween.finish = (_width - line_txt.width) / 2;
				xposTextTween.duration = Math.abs(line_txt.x - (_width - line_txt.width) / 2) / durationKoeff;
				xposTextTween.start();
			}
			else
			{
				widthTween.stop();
				xposTextTween.stop();
				line_sh.width = _width;
				line_txt.x = (_width - line_txt.width)/2;
			}
		}
		
		public function get BarWidth():Number
		{
			return line_sh.width;
		}
		
		public function FadeIn():void
		{
			alphaTween.stop();
			alphaTween.begin = 0;
			alphaTween.finish =1;
			alphaTween.start();
		}
		private function wFinish(e:TweenEvent):void
		{
			dispatchEvent(widthTweenFinish);
		}
		public function X(_x:Number, animate:Boolean = true):void
		{
			if(animate)
			{
				xposTween.stop();
				xposTween.begin = this.x;
				xposTween.finish = _x;
				xposTween.start();
				return;
			}
			else
			{
				xposTween.stop();
				this.x = _x;
			}
		}
		public function set Text(text:String):void
		{
			line_txt.text = text;
		}
		
		public function ShowText():void
		{
			isCanBeShowed = true;
			
			this.visible = this.BarWidth > 0;
			
			if (line_txt.width >= line_sh.width) return;
			
			line_txt.alpha = 0;
			
			line_txt.visible = true;
			textAlphaTween.start();
		}
	}
}
