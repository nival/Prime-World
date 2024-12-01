package src
{
	import flash.display.Bitmap;
	import flash.display.DisplayObject;
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.geom.Rectangle;
	
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
	import flash.geom.Point;
	
	import flash.events.EventDispatcher;
    import src.ButtonTooltipEvent;

	public class WButton extends Sprite
	{
		private var Time:Number = 10;
		public var onDown:Boolean =false;
		
		//reference object in Stage
		public var up_mc:MovieClip;
		public var over_mc:MovieClip;
		public var down_mc:MovieClip;
		public var disable_mc:MovieClip;
		
		public var ico_mc:MovieClip;
		public var icot_mc:MovieClip;

		private var down:DisplayObject;
		private var up:DisplayObject;
		private var over:DisplayObject;
		private var disable:DisplayObject;
		
		private var	tweenOut:Tween;
		private var	tweenIn:Tween;
		
		private var isOver:Boolean =  false;
		private var enabled:Boolean = true;
		
		public function WButton()
		{
			if (up_mc != null) 
			{				
				up = up_mc.getChildAt(0) as DisplayObject;	
				up.x = up_mc.x;
				up.y = up_mc.y;
				this.addChildAt(up, getChildIndex(up_mc));
				this.removeChild(up_mc);
				up_mc = null;
			}
			if(over_mc != null)
			{
				over = over_mc.getChildAt(0) as DisplayObject;
				over.x = over_mc.x;
				over.y = over_mc.y;

				this.addChildAt(over, getChildIndex(over_mc));
				this.removeChild(over_mc);
				over_mc = null;
				
				over.visible = false;
			}
			if(down_mc != null)
			{
				down = down_mc.getChildAt(0) as DisplayObject;
				down.x = down_mc.x;
				down.y = down_mc.y;
				
				this.addChildAt(down, getChildIndex(down_mc));
				this.removeChild(down_mc);
				down_mc = null;
				
				down.visible = false;	
			}
			
			if (disable_mc != null)
			{
				disable = disable_mc.getChildAt(0) as DisplayObject;			
				disable.x = disable_mc.x;
				disable.y = disable_mc.y;
				
				this.addChildAt(disable, getChildIndex(disable_mc));
				this.removeChild(disable_mc);
				disable_mc = null;
				
				disable.visible = false;
				
			}							
			tweenIn = new Tween(this,"alpha",Strong.easeOut,0,1,Time,false);
			tweenIn.addEventListener(TweenEvent.MOTION_FINISH, tweenInFinish);
			tweenOut = new Tween(this,"alpha",Strong.easeOut,1,0,Time * 2,false);
			tweenOut.addEventListener(TweenEvent.MOTION_FINISH, tweenOutFinish);
			
			tweenIn.stop();
			tweenOut.stop();
			
			this.mouseChildren = false;
			this.buttonMode = true;
			this.doubleClickEnabled = true;
			
			this.addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
		}
		
		private function AddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			
			this.addEventListener(MouseEvent.MOUSE_OVER,OnOver);
			this.addEventListener(MouseEvent.MOUSE_OUT,OnOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN,OnDown);
			this.addEventListener(MouseEvent.MOUSE_UP,OnUp);
			this.addEventListener(MouseEvent.DOUBLE_CLICK,OnUp);
			
			stage.addEventListener(MouseEvent.MOUSE_UP, stageUp);	
		}
		
		private function stageUp(e:MouseEvent):void 
		{
			if (!enabled) return;
			if (!isOver&&onDown)
				onDown = false;
		}
		
		public function ConvertBitmapToScaleBitmap(rec:Rectangle):void
		{
			if (disable != null)
			{
				disable = ReplaseByScaleBitmap(rec, disable);
				disable.visible = false;
			}
			if (up!=null)
				up = ReplaseByScaleBitmap(rec, up);
				
			down = ReplaseByScaleBitmap(rec, down);
			over = ReplaseByScaleBitmap(rec, over);
			//Важен порядок добавления объектов, чтобы корректно отображались эффекты.
	
			down.visible = false;
			over.visible = false;
		}
		
		private function ReplaseByScaleBitmap(rec:Rectangle,dispObject:DisplayObject):DisplayObject
		{
			var bitm:Bitmap = dispObject as Bitmap;
			
			if (bitm == null)
				return dispObject;
		
			var scaleBitm:ScaleBitmap = new ScaleBitmap(bitm.bitmapData);
			scaleBitm.scale9Grid = rec;
			this.addChildAt(scaleBitm, getChildIndex(dispObject));
			this.removeChild(dispObject);
			dispObject = scaleBitm;
			
			return dispObject;
		}
		
		public function SetScaleBitmapSizes(_width:Number, _height:Number):void
		{
			SetScaleBitmapSize(up, _width, _height);
			SetScaleBitmapSize(over, _width, _height);
			SetScaleBitmapSize(down, _width, _height);
			SetScaleBitmapSize(disable, _width, _height);
		}
		
		private function SetScaleBitmapSize(dispObject:DisplayObject,_width:Number, _height:Number):void
		{
			
			if (dispObject == null) return;
			
			var scaleBitm:ScaleBitmap = dispObject as ScaleBitmap;
			if (scaleBitm == null) return;
			scaleBitm.setSize(_width, _height);
		}
		
		public function SetSize(_width, _height):void
		{
			disable.width=down.width=over.width = up.width = _width;
		//	disable.height=down.height=over.height = up.height = _height;
		}
		
		
		public function get UpVisObj():DisplayObject
		{
			return up;
		}
		
		public function get DownVisObj():DisplayObject
		{
			return down;
		}
		
		public function get OverVisObj():DisplayObject
		{
			return over;
		}
		
		public function get DisableVisObj():DisplayObject
		{
			return disable;
		}
		
		protected function OnOver(e:MouseEvent):void
		{
			if (!enabled) return;
			isOver = true;
			
			if (!onDown)
			{
				over.visible = true;
				
				StartInAnimation(over);
			}
			if(onDown)
			{
				OnDown(null);
			}
		}
		protected function OnOut(e:MouseEvent):void
		{
			if (!enabled) return;
			
			isOver = false;
			
			if (!onDown)
			{
				over.visible = true;
				StartOutAnimation(over)
			}
			else
			{
				over.visible = false;
				StartInAnimation(over)
				StartOutAnimation(down);
			}
		}
		private function OnDown(e:MouseEvent):void
		{
			if (!enabled) return;
			onDown = true;
			over.visible = false;
			down.visible = true;
			StartInAnimation(down)
		}
		private function OnUp(e:MouseEvent):void
		{
			if (!onDown) return;
			
			onDown = false;
			
			over.visible = true;
			down.visible = false;
			StartOutAnimation(down);
			StartInAnimation(over)
			
			dispatchEvent(new Event("Up",true));
		}

				
		private function tweenOutFinish(e:TweenEvent):void
		{
			e.target.obj.visible = false;
		}
		private function tweenInFinish(e:TweenEvent):void
		{
			if(e.target.obj == down)
			{
				over.visible = false;
			}
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
		
		public function set Enable(value:Boolean):void
		{
			enabled = value;
			this.mouseEnabled = value;
			
		/*	if (value)
			{
				this.addEventListener(MouseEvent.MOUSE_OVER,OnOver);
				this.addEventListener(MouseEvent.MOUSE_OUT,OnOut);
				this.addEventListener(MouseEvent.MOUSE_DOWN,OnDown);
				this.addEventListener(MouseEvent.MOUSE_UP,OnUp);
				this.addEventListener(MouseEvent.DOUBLE_CLICK,OnUp);
				
				stage.addEventListener(MouseEvent.MOUSE_UP, stageUp);	
			}
			else
			{
				this.removeEventListener(MouseEvent.MOUSE_OVER,OnOver);
				this.removeEventListener(MouseEvent.MOUSE_OUT,OnOut);
				this.removeEventListener(MouseEvent.MOUSE_DOWN,OnDown);
				this.removeEventListener(MouseEvent.MOUSE_UP,OnUp);
				this.removeEventListener(MouseEvent.DOUBLE_CLICK,OnUp);
				
				stage.removeEventListener(MouseEvent.MOUSE_UP, stageUp);	
			}*/
		}
		
	}
}