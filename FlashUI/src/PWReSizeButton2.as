package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.EventDispatcher;
	import flash.text.TextField;
	import flash.events.Event;
	
	import flash.geom.Rectangle;
	import flash.display.Bitmap;
	import flash.display.BitmapData;

	
	public class PWReSizeButton extends MovieClip
	{
		public var hit_test:MovieClip;
		public var txt:TextField;
		
		private var tog:Boolean = false;
		private var sel:Boolean = false;
		private var hit_mc:MovieClip;
		
		private var Width:int;
		private var Height:int;
		
		private var rectangle:Rectangle;
		private var image:Bitmap;
		
		private var up_bm:Bitmap;
		private var over_bm:Bitmap;
		private var down_bm:Bitmap;
		private var disable_bm:Bitmap;
		
		private var selectUp_bm:Bitmap;
		private var selectOver_bm:Bitmap;
		private var selectDown_bm:Bitmap;
		private var selectDisable_bm:Bitmap;
		
		private var scaleImagesArray:Array = [];


		public function PWReSizeButton() 
		{
			addEventListener(Event.ADDED_TO_STAGE, onInit);
		}
		private function onInit(e:Event):void
		{
			removeEventListener(Event.ADDED_TO_STAGE, onInit);
			
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
			if(this.scale9Grid)
			{
				setRectangle();
				configure();
			}
		}
		private function configure():void
		{
			Width = this.width;
			Height = this.height;
			
			gotoAndStop(1);
			up_bm = getChildAt(0) as Bitmap;			
			setScaleBitmap(up_bm);
			trace(up_bm)
			
			gotoAndStop(2);
			over_bm = getChildAt(0) as Bitmap;			
			setScaleBitmap(over_bm);
			
			gotoAndStop(3);
			down_bm = getChildAt(0) as Bitmap;			
			setScaleBitmap(down_bm);
			
			gotoAndStop(4);
			disable_bm = getChildAt(0) as Bitmap;			
			setScaleBitmap(disable_bm);			
			
			gotoAndStop(1);
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
//			if(tog&&sel)
//			{
//				//this.gotoAndStop(6);
//				//return;
//			}
			//this.gotoAndStop(2);
			up_bm.visible = false;
			over_bm.visible = true;
		}
		public function onOut(e:MouseEvent):void
		{
//			if(tog&&sel)
//			{
//				this.gotoAndStop(5);
//				return;
//			}
//			this.gotoAndStop(1);
		}
		public function onDown(e:MouseEvent):void
		{
//			if(tog&&sel)
//			{
//				this.gotoAndStop(7);
//				return;
//			}
//			this.gotoAndStop(3);
		}
		public function onUp(e:MouseEvent):void
		{
			if(tog&&!sel)
			{
				this.gotoAndStop(6);
				sel = !sel;
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

		public function setSize(_w:Number, _h:Number)
		{	
		trace('setSize')
			txt.width = _w;
			txt.y = (_h - txt.height)/2;
			
			for(var i:int=0; i<scaleImagesArray.length; i++)
			{
				scaleImagesArray[i].width = _w;
				scaleImagesArray[i].height = _h;
			}
			
			this.scaleX = 1;
			this.scaleY = 1;
		}
		private function setScaleBitmap(_image:Bitmap)
		{	
			var depth:int = getChildIndex(_image);
			var image_bd:BitmapData = _image.bitmapData;
			var scaleBitmap:ScaleBitmap = new ScaleBitmap(image_bd);
			scaleBitmap.scale9Grid = rectangle;
			trace(currentFrame,scaleBitmap.width)
			image = _image;
			_image.visible = false;
			removeChild(_image);
			_image = null;
			image = scaleBitmap;

			addChildAt(scaleBitmap, depth+1);
			scaleBitmap.width = Width;
			scaleBitmap.height = Height;
			scaleImagesArray.push(scaleBitmap);
			
			this.scaleX = 1;
			this.scaleY = 1;
		}
		private function setRectangle():void
		{
			rectangle = new Rectangle();
			rectangle.x = this.scale9Grid.x;
			rectangle.y = this.scale9Grid.y;
			rectangle.width = this.scale9Grid.width;
			rectangle.height = this.scale9Grid.height;
		}

		public function set Text(t:String):void
		{
			txt.text = t;
			return;
		}
	}
}
