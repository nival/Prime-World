package Components
{
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	//import flash.display.BlendMode;//TODO не нужно
	import flash.filters.ColorMatrixFilter;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;

	public class ToggleButton extends Sprite
	{
		private var OnOf:Boolean = false;
		private var Down:Boolean = false;

		//private const myTime:Number = 7;//TODO не нужно

		private var down_arr:Array = [0.63,0.52,0,0,0,0.62,0.39,0,0,0,0.5,0.5,0,0,0,0,0,0,0.78,0];
		private var downCMF:ColorMatrixFilter = new ColorMatrixFilter(down_arr);

		//private var Width:Number;//TODO не нужно
		//private var Height:Number;//TODO не нужно

		private var toggled:Boolean = true;
		
		//reference
		public var ico_mc:MovieClip;
		public var up_mc:MovieClip;
		public var over_mc:MovieClip;
		public var down_mc:MovieClip;
		public var overDown_mc:MovieClip;
		public var hightLight_mc:MovieClip;

		public function ToggleButton()
		{
			Width = this.width;
			Height = this.height;

			ico_mc.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			ico_mc.addEventListener(MouseEvent.MOUSE_OUT,onOut);
			ico_mc.addEventListener(MouseEvent.MOUSE_DOWN,onDown);
			ico_mc.addEventListener(MouseEvent.MOUSE_UP,onUp);
			ico_mc.addEventListener(MouseEvent.DOUBLE_CLICK,onUp);
			
			this.buttonMode = true;
			this.doubleClickEnabled = true;
			//this.mouseEnabled = false;

			up_mc.mouseEnabled = false;
			over_mc.mouseEnabled = false;
			down_mc.mouseEnabled = false;
			overDown_mc.mouseEnabled = false;
			overDown_mc.mouseEnabled = false;
			hightLight_mc.mouseEnabled = false;

			addTween(over_mc);
			addTween(overDown_mc);
			
			enable();

		}
		public function addTween(target:MovieClip):void
		{
			target.tweenIn = new Tween(target,"alpha",Strong.easeOut,0,1,7,false);
			target.tweenOut = new Tween(target,"alpha",Strong.easeOut,1,0,21,false);

			target.tweenIn.stop();
			target.tweenOut.stop();
		}

		private function onOver(e:Event):void
		{
			if (! OnOf)
			{
				over();
			}
			if (OnOf)
			{
				overDown();
			}
			if (Down)
			{
			}
		}
		private function onOut(e:Event):void
		{
			if (! OnOf)
			{
				up();
			}
			if (OnOf)
			{
				down();
			}
		}
		private function onDown(e:Event):void
		{
			Down = true;
		}
		public function onUp(e:Event):void
		{
			Down = false;

			if (! OnOf&&toggled)
			{
				overDown();
				ico_mc.filters = [downCMF];
			}
			if (OnOf)
			{
				over();
				ico_mc.filters = [];
			}
			if (toggled == true)
			{
				OnOf = ! OnOf;
			}
		}

		private function up()
		{
			up_mc.visible = true;
			down_mc.visible = false;
			overDown_mc.visible = false;
			hightLight_mc.visible = true;
			over_mc.visible = true;
			
			over_mc.tweenIn.stop();
			over_mc.tweenOut.start();
			overDown_mc.tweenIn.stop();
			
		}
		private function down()
		{
			up_mc.visible = false;
			over_mc.visible = false;
			down_mc.visible = true;
			hightLight_mc.visible = false;
			overDown_mc.visible = true;
			
			over_mc.tweenIn.stop();
			overDown_mc.tweenIn.stop();
			overDown_mc.tweenOut.start();
			
		}

		private function over()
		{
			up_mc.visible = true;
			down_mc.visible = false;
			overDown_mc.visible = false;
			hightLight_mc.visible = true;
			
			over_mc.visible = true;
			over_mc.tweenOut.stop();
			over_mc.tweenIn.start();
			
		}
		private function overDown()
		{
			up_mc.visible = false;
			over_mc.visible = false;
			down_mc.visible = false;
			overDown_mc.visible = true;
			hightLight_mc.visible = false;
			
			overDown_mc.tweenOut.stop();
			overDown_mc.tweenIn.start();
			
		}
		public function enable():void
		{
			up_mc.visible = true;
			over_mc.visible = false;
			down_mc.visible = false;
			overDown_mc.visible = false;
			hightLight_mc.visible = true;
		}

		public function disable():void
		{
			over_mc.tweenIn.stop();
			over_mc.tweenOut.stop();
			overDown_mc.tweenIn.stop();
			overDown_mc.tweenOut.stop();

			up_mc.visible = false;
			over_mc.visible = false;
			down_mc.visible = false;
			overDown_mc.visible = false;
			hightLight_mc.visible = false;
			
			ico_mc.disable=true;
		}
	}
}