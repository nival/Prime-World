package Components
{
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	
	import flash.utils.setInterval;
	
	import src.ScaleBitmap;

	public class WFrame extends MovieClip
	{
		//private var myScaleBitmapBack:ScaleBitmap;
		private var myScaleBitmapEmpty:ScaleBitmap;
		
		private var Width:Number;
		
		private var TweenMouseLight:Tween;
		private var lightItn:Number;
		
		//ref
		public var light_mc:MovieClip;
		public var lightFrame_mc:MovieClip;

		public function WFrame()
		{
			super();
			Width = this.width;
//			this.removeChildAt(0);
//			
//			var _wFrameBack:BitmapData = new wFrameBack_png  ;
//			myScaleBitmapBack = new ScaleBitmap(_wFrameBack);
//			myScaleBitmapBack.scale9Grid = new Rectangle(140,28,60,46);
//			addChild(myScaleBitmapBack);
						
			this.removeChildAt(0);
			
			var _wFrameEmpty:BitmapData = new wFrameEmpty_png  ;
			myScaleBitmapEmpty = new ScaleBitmap(_wFrameEmpty);
			myScaleBitmapEmpty.scale9Grid = new Rectangle(140,29,60,46);
			addChildAt(myScaleBitmapEmpty, 0);
						
//			setChildIndex(light_mc,1);
//			setChildIndex(lightFrame_mc,2);
			//TODO в клипе  lightFrame_mc visible выключается в первом кадре после проигрывании анимации она переходит в первый кадр, там стопиться и скрывается
			light_mc.visible = false;
			
			lightItn = setInterval(Flash, 15000);
			
			TweenMouseLight = new Tween(light_mc,"alpha",Strong.easeOut,0,1,20,false);
			TweenMouseLight.addEventListener(TweenEvent.MOTION_FINISH, TweenMouseLightFinish);
			TweenMouseLight.stop();
			
			configUI();
		}
		private function Flash():void
		{
			var chance:Number = Math.random()*10;
			
			if(chance>5)
			{
				lightFrame_mc.visible = true;
				lightFrame_mc.play();
			}
		}

		protected function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			var w:Number = super.width;
			var h:Number = super.height;
			super.scaleX = super.scaleY = 1;
			
			Width = w;
			
			setSize(w,h);
			rotation = r;
		}
		public function onMove():void
		{
			if(light_mc.x - (light_mc.width / 2) >= 0 && light_mc.x + (light_mc.width / 2) <= Width )
			{
				light_mc.x = mouseX;
			}
			
			if(light_mc.x - (light_mc.width / 2) < 0 )
			{
				light_mc.x = light_mc.width / 2;
				return;
			}
			if(light_mc.x + (light_mc.width / 2) > Width)
			{
				light_mc.x = Width - light_mc.width / 2;
				return;
			}
		}
		public function onOver():void
		{
			light_mc.visible = true;
			TweenMouseLight.continueTo(0.4,20);
		}
		public function onOut():void
		{
			TweenMouseLight.continueTo(0,20);
		}
		public function onDown():void
		{
			TweenMouseLight.continueTo(1,15);
		}
		public function onUp():void
		{
			TweenMouseLight.continueTo(0.4,15);
		}
		private function TweenMouseLightFinish(e:TweenEvent):void
		{
			if(e.target.finish == 0)
			{
				light_mc.visible = false;
			}
		}

		public function setSize(_width:Number, _height:Number):void
		{
			myScaleBitmapEmpty.setSize(_width, _height);
			//myScaleBitmapBack.setSize(_width, _height);
			
			lightFrame_mc.width = _width;
			lightFrame_mc.height = _height;
		}
	}
};