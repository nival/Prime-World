package Components
{

	import flash.display.BlendMode;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	import fl.transitions.Tween;
	import fl.transitions.easing.*;
	import fl.transitions.TweenEvent;
	import flash.geom.Rectangle;

	import src.ScaleBitmap;
	import flash.display.Bitmap;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.display.Shape;

	public class Bar extends MovieClip
	{
		// TODO: скорее всего, этим константам здесь не место
		public static const HEALTHBAR_COLOR_ALLY:uint = 0xFF5BFF24;
		public static const HEALTHBAR_COLOR_ENEMY:uint = 0xFFFF1318;
		public static const MANABAR_COLOR_DEFAULT:uint = 0xFF30B7FF;
		
		private var maxBarWidth:Number=1;
		private var currentWidth:Number=1;
		private var currentValue:int = -1;
		private var maxBarValue:int = 1;
			
		public var myScaleBitmap:ScaleBitmap;

		private var tweenLineBack:Tween;
		private var tweenLineBackAlpha:Tween;
		private var tweenGlowAlpha:Tween;
		private var originalBarHeight:Number = 16;
		private var isNeedToShowText:Boolean = true;
		private var showRegenerationText:Boolean = true;
		
		
		public var showInActionBar:Boolean = true;
		public var hideOnZeroMax:Boolean = true;
		
		//reference in stage
		public var percent_txt:TextField;
		public var regeneration_txt:TextField;
		public var glass_png:Bitmap;
		public var lineMain_mc:MovieClip;
		public var lineMain_sh:Shape;
		public var glowMain_mc:MovieClip;
		public var lineBack_sh:Shape;
		public var back_sh:Shape;
		
		public function Bar()
		{
			this.mouseEnabled = false;
			this.mouseChildren = false;

			glass_png = getChildAt(3) as Bitmap;//стекло
			lineBack_sh = getChildAt(2) as Shape;
			lineBack_sh.x = lineMain_mc.x;
			back_sh = getChildAt(0) as Shape;//подложка
			
			myScaleBitmap = new ScaleBitmap(glass_png.bitmapData);
			myScaleBitmap.scale9Grid = new Rectangle(8,3,526,7);
			
			removeChild(glass_png);
			glass_png = null;
			addChildAt(myScaleBitmap, 3);
			
			lineMain_sh = lineMain_mc.getChildAt(0) as Shape;
			glowMain_mc = lineMain_mc.getChildAt(1) as MovieClip;
			glowMain_mc.blendMode = BlendMode.ADD;
			
//			swapChildren(myScaleBitmap, percent_txt);
//			swapChildren(myScaleBitmap, regeneration_txt);
			swapChildren(lineMain_mc, lineBack_sh);

			tweenLineBackAlpha = new Tween(lineBack_sh,"alpha",None.easeNone,1,0.5,10,true);
			tweenLineBackAlpha.stop();
			
			tweenLineBack = new Tween(lineBack_sh,"width",Strong.easeInOut,lineBack_sh.width,1,10,true);
			tweenLineBack.stop();
			
			//эффект свечения при прибавлении значения бара
			glowMain_mc.visible = false;
			tweenGlowAlpha = new Tween(glowMain_mc, 'alpha', Strong.easeOut, 1, 0, 10, true);
			tweenGlowAlpha.addEventListener(TweenEvent.MOTION_FINISH, glowAlphaFinish);
			tweenGlowAlpha.stop();
			
			regeneration_txt.x = 0;
			percent_txt.autoSize = TextFieldAutoSize.CENTER;
			regeneration_txt.autoSize = TextFieldAutoSize.RIGHT;
			
			
			var w:Number = super.width;
			var h:Number = myScaleBitmap.height*this.height/originalBarHeight;
			super.scaleX = super.scaleY = 1;
			setSize(w, h);
			
			UpdateTextVisible()
		}
		
		public function get BarHeight():Number
		{
			return myScaleBitmap.height;
		}
		
		public function setSize(_width:Number,_height:Number):void
		{
			regeneration_txt.x = 0;
			
			myScaleBitmap.setSize(_width,_height);

			lineMain_mc.width = _width - 12;
			lineMain_mc.height = _height - 1;
						
			lineBack_sh.x = lineMain_mc.x;
			lineBack_sh.y = lineMain_mc.y = (myScaleBitmap.height - lineMain_mc.height) / 2;

			lineBack_sh.width = lineMain_mc.width;
			lineBack_sh.height = lineMain_mc.height;
							
			back_sh.width = lineMain_mc.width+10;
			back_sh.height = lineMain_mc.height;

			regeneration_txt.x = _width - regeneration_txt.width-10;
			regeneration_txt.y = (_height - percent_txt.height + 1) / 2;

			percent_txt.x = (_width - percent_txt.width) / 2;
			percent_txt.y = (_height - percent_txt.height + 1) / 2;

			maxBarWidth = currentWidth = lineMain_mc.width;
		}

		public function setValue(valueBar:int,regeneration:Number=0, animate:Boolean = true):void
		{
			var regen:Number = Math.round(regeneration * 10) / 10;
			
			regeneration_txt.text = (regen>0?"+":"") + regen.toString();
			regeneration_txt.width = regeneration_txt.textWidth;
			if (currentValue == valueBar)
				return;

			
			currentValue = valueBar;
			SetWidthBars(animate);
		}

		public function setMaxBar(max:int, animate:Boolean = true):void
		{
			if (maxBarValue==max)
				return;
			
			maxBarValue = max;
			
			if (currentValue >= maxBarValue)
				currentValue = maxBarValue;
				
			if (showInActionBar && hideOnZeroMax) 
				visible = max!=0;
				
			SetWidthBars(animate);
		}

		private function SetWidthBars(animate:Boolean):void
		{
			currentWidth = maxBarValue != 0 ? currentValue *  maxBarWidth / maxBarValue : 0;
			
			percent_txt.text = currentValue.toString() + " / " + maxBarValue.toString();

			if(animate)
			{
				tweenLineBackAlpha.stop();
				tweenLineBackAlpha.duration = duration/2;
				tweenLineBackAlpha.start();
				
				tweenLineBack.stop();
				tweenLineBack.begin = lineMain_mc.width;
				tweenLineBack.finish = currentWidth;
				tweenLineBack.duration = duration;
				tweenLineBack.start();
			}
			else
			{
				tweenLineBack.stop();
				tweenLineBackAlpha.stop();
				lineBack_sh.width = currentWidth;
				
			}
			
			if(currentWidth > lineMain_mc.width && animate)
			{
				glowMain_mc.scaleX = duration;
				glowMain_mc.visible = true;
				tweenGlowAlpha.stop();
				tweenGlowAlpha.begin = 1;
				tweenGlowAlpha.finish = 0;
				tweenGlowAlpha.duration = 2;
				tweenGlowAlpha.start();	
			}
			else
			{
				tweenGlowAlpha.stop();
				glowMain_mc.alpha = 0;
				glowMain_mc.visible = false;
			}
		
			lineMain_mc.width = currentWidth;
		}
		
		private function get duration():Number
		{
			return 1.8 * Math.abs(lineMain_mc.width - currentWidth) / maxBarWidth;
		}

		private function glowAlphaFinish(e:TweenEvent):void
		{
			glowMain_mc.visible = false;
		}
		
		private function UpdateTextVisible():void
		{
			percent_txt.visible = isNeedToShowText;
			regeneration_txt.visible = isNeedToShowText && showRegenerationText;
		}
		
		//{ для компонент
		public function get barColor():uint
		{
			var r:Number = lineMain_sh.transform.colorTransform.redMultiplier * 255;
			var g:Number = lineMain_sh.transform.colorTransform.greenMultiplier * 255;
			var b:Number = lineMain_sh.transform.colorTransform.blueMultiplier * 255;

			return r << 16 | g << 8 | b;
		}

		public function set barColor(_color:uint):void
		{
			var colorTrans:ColorTransform = lineMain_sh.transform.colorTransform;

			colorTrans.redMultiplier = (_color >> 16 & 255) / 255;
			colorTrans.greenMultiplier = (_color >> 8 & 255) / 255;
			colorTrans.blueMultiplier = (_color & 255) / 255;

			lineMain_sh.transform.colorTransform = colorTrans;
			lineBack_sh.transform.colorTransform = colorTrans;
		}
		
		
		
		//используется только для компонент.
		public function set TextShow(show:Boolean)
		{
			isNeedToShowText = show;
			UpdateTextVisible()
		}
		public function get TextShow():Boolean
		{
			return isNeedToShowText; 
		}
		
		public function set ShowRegenerationText(show:Boolean)
		{
			showRegenerationText = show;
			UpdateTextVisible();
		}
		
		public function get ShowRegenerationText():Boolean
		{
			return showRegenerationText;
		}
		//}
	}
}