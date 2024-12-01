package 
{

	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.utils.Timer;
	import flash.events.TimerEvent;


	public class testFrameCounter extends MovieClip
	{

		private var fpsCounter:FPSCounter;
		private var timer:Timer;
		private var frame:int = 0;
		var played:Boolean = true;

		public function testFrameCounter()
		{
			addChild(fpsCounter = new FPSCounter(10));

			addEventListener(Event.ENTER_FRAME,EnterFrame);

			timer = new Timer(41.66666666666667, 240);
			timer.addEventListener(TimerEvent.TIMER,tick);

			myButton_mc.stop();
			myButton_mc.txt.text = 'play';
			myButton_mc.txt.mouseEnabled = false;

			myButton_mc.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			myButton_mc.addEventListener(MouseEvent.MOUSE_OUT,onOut);
			myButton_mc.addEventListener(MouseEvent.MOUSE_DOWN,onDown);
			myButton_mc.addEventListener(MouseEvent.MOUSE_UP,onUp);

			myButton_mc.buttonMode = true;
			
			function playFrame1():void	{ trace('frame1');}// myButton_mc.txt.text = 'frame1';	}
			function playFrame2():void	{ trace('frame2');}// myButton_mc.txt.text = 'frame2';	}
			function playFrame3():void	{ trace('frame3');}// myButton_mc.txt.text = 'frame3';	}
						
			myButton_mc.addFrameScript(0, playFrame1);
			myButton_mc.addFrameScript(1, playFrame2);
			myButton_mc.addFrameScript(2, playFrame3);
		
			
			stop();

		}
		private function EnterFrame(e:Event):void
		{
			txt.text = currentFrame.toString();
			txt3.text = currentFrame.toString();
		}
		private function tick(e:TimerEvent):void
		{
			frame++;
			txt2.text = frame.toString();
			line_mc.width = frame;
		}

		function onOver(e:MouseEvent):void
		{
			myButton_mc.gotoAndStop(2);
		}

		function onOut(e:MouseEvent):void
		{
			myButton_mc.gotoAndStop(1);
		}

		function onDown(e:MouseEvent):void
		{
			myButton_mc.gotoAndStop(3);
						
			if (played)
			{
				myButton_mc.txt.text = 'stop';
				trace('root.play()');
				play();
				timer.start();
			}
			else
			{
				myButton_mc.txt.text = 'play';
				trace('root.gotoAndStop(1)');
				gotoAndStop(1);
				timer.stop();
				timer.reset();
				txt.text = '1';
				txt2.text = '1'
				line_mc.width = 1
				frame = 1;
			}
			played = ! played;
		}

		function onUp(e:MouseEvent):void
		{
			myButton_mc.gotoAndStop(1);
		}
	}	
}
