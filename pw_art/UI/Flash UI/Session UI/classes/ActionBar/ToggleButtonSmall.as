package ActionBar
{
	import flash.display.Sprite;
	import flash.display.Shape;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.BlendMode;
	import flash.display.DisplayObject;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	
	import flash.events.EventDispatcher;
	import src.SeladonColor;
	import src.Desaturate;
    
	import flash.geom.Point;


	public class ToggleButtonSmall extends MovieClip
	{
		public var ico:Sprite;
		public var icoDown:Sprite;

		private const myTime:Number = 5;

		private var tweenXIn:Tween;
		private var tweenYIn:Tween;
		private var tweenXOut:Tween;
		private var tweenYOut:Tween;

		private var	tweenOut:Tween;
		private var	tweenIn:Tween;
		
		private var Width:Number;
		private var Height:Number;
		
		private var disabled:Boolean;
		
		//reference in stage
		public var ico_mc:MovieClip;
		public var up_mc:MovieClip;
		public var over_mc:MovieClip;
		public var down_mc:MovieClip;
		public var overDown_mc:MovieClip;
		public var hightLight_mc:MovieClip;
		public var toggleButtonSmall_mc:MovieClip;
		
		public var up_bm:DisplayObject;
		public var over_bm:DisplayObject;
		public var down_bm:DisplayObject;
		public var overDown_bm:DisplayObject;
		public var hightLight_bm:DisplayObject;

		public function ToggleButtonSmall()
		{
			Width = this.width;
			Height = this.height;

			ico = new Sprite  ;
			ico_mc.addChild(ico);
			icoDown = new Sprite  ;
			ico_mc.addChild(icoDown);

			ico.x =  -  this.width / 2;
			ico.y =  -  this.height / 2;
			icoDown.x =  -  this.width / 2;
			icoDown.y =  -  this.height / 2;

			SeladonColor.seladon(icoDown);
			icoDown.visible = false;
		
			var myMask:Shape = new Shape  ;
			myMask.graphics.beginFill(0x000000,1);
			myMask.graphics.drawRoundRect(3,2,Width - 6,Height-4,5,5);
			myMask.graphics.endFill();
			addChild(myMask);
			ico_mc.mask = myMask;
			ico_mc.mouseEnabled = false;

			tweenIn = new Tween(this, "alpha", Strong.easeOut, 0, 1, 7, false);
			tweenOut = new Tween(this,"alpha",Strong.easeOut,1,0,21,false);
			tweenIn.stop();
			tweenOut.stop();
			
			
			up_bm = ConvertFromMovieToBitmap(up_mc);
			over_bm = ConvertFromMovieToBitmap(over_mc);
			down_bm = ConvertFromMovieToBitmap(down_mc);
			overDown_bm = ConvertFromMovieToBitmap(overDown_mc);
			hightLight_bm = ConvertFromMovieToBitmap(hightLight_mc);	
			
			up_bm.blendMode = BlendMode.OVERLAY;
			over_bm.blendMode = BlendMode.OVERLAY;
			down_bm.blendMode = BlendMode.OVERLAY;
			overDown_bm.blendMode = BlendMode.OVERLAY;
			
			up_mc = null;
			over_mc = null;
			down_mc = null;
			overDown_mc = null;
			hightLight_mc = null;
			
			over_bm.visible = false;
			overDown_bm.visible = false;
		
			ico_mc.tweenXIn = new Tween(ico_mc,"scaleX",Strong.easeOut,0.90, 0.95,myTime,false);
			ico_mc.tweenYIn = new Tween(ico_mc,"scaleY",Strong.easeOut,0.90, 0.95,myTime,false);

			ico_mc.tweenXOut = new Tween(ico_mc,"scaleX",Strong.easeOut,0.95,0.90, myTime,false);
			ico_mc.tweenYOut = new Tween(ico_mc,"scaleY",Strong.easeOut,0.95,0.90, myTime,false);
			
			ico_mc.scaleX = ico_mc.scaleY = 1;

			ico_mc.tweenXOut.stop();
			ico_mc.tweenYOut.stop();
			ico_mc.tweenXIn.stop();
			ico_mc.tweenYIn.stop();
			//disable();
		//enable();
		}
		
		private function ConvertFromMovieToBitmap(dispObject:MovieClip):DisplayObject
		{
			var bitm:DisplayObject = dispObject.getChildAt(0) as DisplayObject;
			this.addChildAt(bitm, this.getChildIndex(dispObject));
			//TODO разобраться почему именно так
			bitm.x = dispObject.x-1;
			bitm.y = dispObject.y;
			this.removeChild(dispObject);
				
			return bitm;
		}
		
		private function StartInAnimation(obj:Object):void
		{
			if (obj == null) return;
			
			tweenOut.obj = obj;
			tweenOut.stop();
			tweenIn.obj = obj;
			tweenIn.start();
		}
		
		private function StartOutAnimation(obj:Object):void
		{
			if (obj == null) return;
			
			tweenIn.obj = obj;
			tweenIn.stop();
			tweenOut.obj = obj;
			tweenOut.start();
		}

		public function onOver(isButtonOn:Boolean):void
		{
			if (isButtonOn)
			{
				overDown();
			}
			else
			{
				over();
			}
			
			ico_mc.tweenXIn.stop();
			ico_mc.tweenYIn.stop();
			ico_mc.tweenXOut.stop();
			ico_mc.tweenYOut.stop();
			ico_mc.scaleX = ico_mc.scaleY = 0.95;
		}
		public function onOut(isButtonOn:Boolean):void
		{
			if (isButtonOn)
			{
				down();
			}
			else
			{
				up();
			}
			ico_mc.tweenXIn.stop();
			ico_mc.tweenYIn.stop();
			ico_mc.tweenXOut.stop();
			ico_mc.tweenYOut.stop();
			ico_mc.scaleX = ico_mc.scaleY = 1;
			
		}
		public function onDown():void
		{
			ico_mc.tweenXIn.stop();
			ico_mc.tweenYIn.stop();
			ico_mc.tweenXOut.start();
			ico_mc.tweenYOut.start();
		}
		public function onUp():void
		{
			ico_mc.tweenXOut.stop();
			ico_mc.tweenYOut.stop();
			ico_mc.tweenXIn.start();
			ico_mc.tweenYIn.start();
		}
		
		private function up() //в невжатое обычное состояние
		{
			if(!disabled)
			{
				up_bm.visible = true;
				down_bm.visible = false;
				overDown_bm.visible = false;
				hightLight_bm.visible = true;
				over_bm.visible = true;

				tweenIn.obj = overDown_bm;
				tweenIn.stop();
				
				StartOutAnimation(over_bm);
			}
		}
		private function down() // вжатие кнопки
		{
			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = true;
			hightLight_bm.visible = false;
			overDown_bm.visible = true;
			
			tweenIn.obj = over_bm;
			tweenIn.stop();
			
			StartOutAnimation(overDown_bm);			
		}

		private function over() //над невжатой кнопкой
		{
			up_bm.visible = true;
			down_bm.visible =false;
			overDown_bm.visible =false;
			hightLight_bm.visible = true;
			over_bm.visible = true;
			
			StartInAnimation(over_bm);			
		}
		private function overDown()  //над вжатой
		{
			up_bm.visible =false;
			over_bm.visible =false;
			down_bm.visible = false;
			hightLight_bm.visible = false;
			overDown_bm.visible = true;
			
			StartInAnimation(overDown_bm);
			
		}
		public function enable():void  
		{
			disabled = false;
			up_bm.visible = true;
			over_bm.visible = false;
			down_bm.visible = false;
			overDown_bm.visible = false;
			hightLight_bm.visible = true;
			Desaturate.saturate(ico_mc);
			ico_mc.alpha = 1;
			//trace('enable')
		}

		public function disable():void
		{
			disabled = true;
			ico_mc.tweenXOut.stop();
			ico_mc.tweenYOut.stop();
			ico_mc.tweenXIn.stop();
			ico_mc.tweenYIn.stop();

			tweenIn.stop();
			tweenOut.stop();
			
			Desaturate.desaturate(ico_mc);
			ico_mc.alpha = 0.4;

			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = false;
			overDown_bm.visible = false;
			hightLight_bm.visible = false;
			//trace('disable')
		}
		
		public function SetOffState():void
		{
			ico.visible = true;
			icoDown.visible = false;
			up();
		}
		
		public function SetOnState():void
		{
			ico.visible = false;
			icoDown.visible = true;
			down();
		}
	}
}