package
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.events.EventDispatcher;
	import flash.events.Event;

	public class PWButton extends MovieClip
	{
		public var hit_test:MovieClip;
		public var txt:TextField;

		
		private var tog:Boolean = false;
		private var sel:Boolean = false;
		
		private var hit_mc:MovieClip;

		public function PWButton()
		{
			this.stop();
			
			if(this.totalFrames>4)
			{
				tog = true;
			}

			if (txt != null)
			{
				txt.mouseEnabled = false;
			}

			if (hit_test == null)
			{
				setButton(this);
			}
			else
			{
				setButton(hit_test);
			}
		}
		
		private function setButton(hitTest_mc:MovieClip)
		{
			hitTest_mc.mouseChildren = false;
			hitTest_mc.buttonMode = true;
			hitTest_mc.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_UP, onUp);
			hit_mc = hitTest_mc;
		}
		
		public function onOver(e:MouseEvent):void
		{
			if(tog&&sel)
			{
				this.gotoAndStop(6);
				return;
			}
			this.gotoAndStop(2);
		}
		public function onOut(e:MouseEvent):void
		{
			if(tog&&sel)
			{
				this.gotoAndStop(5);
				return;
			}
			this.gotoAndStop(1);
		}
		public function onDown(e:MouseEvent):void
		{
			if(tog&&sel)
			{
				this.gotoAndStop(7);
				return;
			}
			this.gotoAndStop(3);
		}
		public function onUp(e:MouseEvent):void
		{
			if(tog&&!sel)
			{
				this.gotoAndStop(6);
				sel = !sel;
				dispatchEvent(new Event('onUp', true));
				return;
			}
			if(e!=null)
			{
				this.gotoAndStop(2);
			}
			else
			{
				this.gotoAndStop(1);
			}
			sel = !sel;
			dispatchEvent(new Event('onUp', true));
		}
		public function disable():void
		{
			hit_mc.removeEventListener(MouseEvent.MOUSE_OVER, onOver);
			hit_mc.removeEventListener(MouseEvent.MOUSE_OUT, onOut);
			hit_mc.removeEventListener(MouseEvent.MOUSE_DOWN, onDown);
			hit_mc.removeEventListener(MouseEvent.MOUSE_UP, onUp);
			this.gotoAndStop(4);
		}
		public function enable():void
		{
			hit_mc.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			hit_mc.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			hit_mc.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			hit_mc.addEventListener(MouseEvent.MOUSE_UP, onUp);
			this.gotoAndStop(1);
		}
		public function set Text(t:String):void
		{
			txt.text = t;
			return;
		}
	}
}