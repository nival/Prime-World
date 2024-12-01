package ActionBar
{
	import flash.display.Bitmap;
	import flash.display.DisplayObject;
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.BlendMode;
	import flash.filters.ColorMatrixFilter;
	import fl.transitions.TweenEvent;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import Components.IcoAction;
	
	public class ActionBarToggle extends Sprite
	{
		private var Down:Boolean = false;

		private const myTime:Number = 7;

		private var down_arr:Array = [0.48,0.43,0.08,0,0,0.25,0.53,0.18,0,0,0.18,0.46,0.44,0,0,1,1,1,1,0];
		private var downCMF:ColorMatrixFilter = new ColorMatrixFilter(down_arr);

		private var Width:Number;
		private var Height:Number;
		public var enabled:Boolean;
		
		//reference in stage
		public var ico_mc:IcoAction;
		
		public var over_mc:MovieClip;
		public var overDown_mc:MovieClip;
		public var down_mc:MovieClip;
		public var hightLight_mc:MovieClip;
		public var up_mc:MovieClip;

		private var	tweenOut:Tween;
		private var	tweenIn:Tween;
		
		private var over_bm:DisplayObject;
		private var overDown_bm:DisplayObject;
		private var down_bm:DisplayObject;
		private var hightLight_bm:DisplayObject;
		private var up_bm:DisplayObject;
		
		public function ActionBarToggle()
		{	
			Width = this.width;
			Height = this.height;
			
			tweenIn = new Tween(this, "alpha", Strong.easeOut, 0, 1, 7, false);
			tweenOut = new Tween(this,"alpha",Strong.easeOut,1,0,21,false);
			tweenIn.stop();
			tweenOut.stop();
			
			up_bm = ConvertFromMovieToBitmap(up_mc);
			over_bm = ConvertFromMovieToBitmap(over_mc);
			down_bm = ConvertFromMovieToBitmap(down_mc);
			overDown_bm = ConvertFromMovieToBitmap(overDown_mc);
			hightLight_bm = ConvertFromMovieToBitmap(hightLight_mc);	
			
			over_bm.blendMode = BlendMode.OVERLAY;
			overDown_bm.blendMode = BlendMode.OVERLAY;
			down_bm.blendMode = BlendMode.OVERLAY;
			up_bm.blendMode = BlendMode.OVERLAY;
			
			up_mc = null;
			over_mc = null;
			down_mc = null;
			overDown_mc = null;
			hightLight_mc = null;
			
			over_bm.visible = false;
			overDown_bm.visible = false;
			
			enable()
		}

		private function ConvertFromMovieToBitmap(dispObject:MovieClip):DisplayObject
		{
			var bitm:DisplayObject = dispObject.getChildAt(0) as DisplayObject;
			this.addChildAt(bitm, this.getChildIndex(dispObject));
			this.removeChild(dispObject);
			return bitm;
		}
		
		
		public function onOver():void
		{
			if (!enabled) return;
			
			if (Down)
			{
				down();
			}
			else
			{
				over();
			}
		
		}
		public function onOut():void
		{
			if (!enabled) return;
			
			if(Down)
				ico_mc.onUp();
			
			//TODO нужно чтобы тут параметр Down сбрасывался при отпускании из вне, а от сюда убрать
			Down = false;
			
			up();
		}
		public function onDown():void
		{
			if (!enabled) return;
			
			Down = true;
			down();
		
		}
		public function onUp():void
		{
			if (!enabled) return;
			
			if(Down)
			{
				ico_mc.onUp();
				over();
			}
			Down = false;
		
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
		
		public function up()
		{
			up_bm.visible = true;
			over_bm.visible = true;
			down_bm.visible = false;
			hightLight_bm.visible = true;
			
			StartOutAnimation(over_bm);
		}
		
		private function over()
		{
			over_bm.visible = true;
			
			StartInAnimation(over_bm);
			
			down_bm.visible = false;
			hightLight_bm.visible = true;
		}
		
		public function down()
		{
			up_bm.visible = false;
			down_bm.visible = true;
			over_bm.visible = false;
			hightLight_bm.visible = false;
			
			tweenIn.obj = over_bm;
			tweenIn.stop();
			
			ico_mc.onDown();
		}
		
		public function enable():void
		{
			enabled = true;
			up_bm.visible = true;
			over_bm.visible = false;
			down_bm.visible = false;
			hightLight_bm.visible = true;
		}

		public function disable(applyFilter:Boolean = true):void
		{
			enabled = false;
			
			tweenIn.obj = over_bm;
			tweenIn.stop();
			tweenOut.obj = over_bm;
			tweenOut.stop();
			
			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = false;
			hightLight_bm.visible = false;

			if (applyFilter)
				ico_mc.disable();
		}
	}
}