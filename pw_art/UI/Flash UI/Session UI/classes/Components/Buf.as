package Components
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.URLRequest;
	import flash.text.TextField;
	public class Buf extends MovieClip
	{

		private var bufDebuf:String;
		private var time:String;
		private var iconpath:String;
		private var loader:Loader;
		
		//reference
		public var buf_mc:MovieClip;
		public var debuf_mc:MovieClip;
		public var mask_mc:MovieClip;
		public var ico_mc:MovieClip;
		public var count_text:TextField;
		public var back_mc:MovieClip;
		public var bufDebufFlash_mc:MovieClip;//остановил и захайдил. Его нужно отхайдить и запустить при появлении буфа. В последнем кадре я написал возврат назад и хайд.
		
		private var back:DisplayObject;
		private var isSelection:Boolean = false;
		private var index:int = -1;
		private var onFocus:Boolean = false;
		private var epselon:Number = 0.001;
		
		private var isNeedToShowup:Boolean = true;
		
		private var buf:DisplayObject;
		private var debuf:DisplayObject;
		private var isNewIcon:Boolean;
		public function Buf()
		{
			this.stop();
			mask_mc.stop();
			bufDebufFlash_mc.mouseEnabled = false;
			bufDebufFlash_mc.mouseChildren = false;
			
			mask_mc.mouseEnabled = false;
			count_text.mouseEnabled = false;
			loader = new Loader;
			loader.contentLoaderInfo.addEventListener(Event.INIT, ScaleIconToNeededSize);
			ico_mc.addChild(loader);
			ico_mc.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			ico_mc.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			count_text.visible = false;
			
			buf = ConvertFromMovieToBitmap(buf_mc);
			debuf = ConvertFromMovieToBitmap(debuf_mc);
			back = ConvertFromMovieToBitmap(back_mc);
			buf_mc = null;
			debuf_mc = null;
			back_mc = null;
		}
		
		private function ConvertFromMovieToBitmap(dispObject:MovieClip):DisplayObject
		{
			
			var bitm:DisplayObject = dispObject.getChildAt(0) as DisplayObject;
			this.addChildAt(bitm, this.getChildIndex(dispObject));
			bitm.x = dispObject.x;
			bitm.y = dispObject.y;
			this.removeChild(dispObject);
				
			return bitm;
		}
		
		public function get BuffHeight():Number
		{
			return back.height;
		}
		
		private function set BufDeBuf(b:Boolean)
		{			
			if (b)
			{
				buf.visible = true;
				debuf.visible = false;
			}
			else
			{
				buf.visible = false;
				debuf.visible = true;
			}
		}
	
		private function ScaleIconToNeededSize(e:Event):void
		{
			loader.content.width = debuf.width;
			loader.content.height = debuf.height;
		}
		private function onOver(e:MouseEvent=null):void
		{
			if(isSelection)
				FSCommands.Send(FSCommands.SELECTIONBUFF_TOOLTIP, FSCommands.TOOLTIP_SHOW+index);
			else 	
				FSCommands.Send(FSCommands.OURBUFF_TOOLTIP, FSCommands.TOOLTIP_SHOW + index);
			
			onFocus = true;
		}	
		
		private function onOut(e:MouseEvent=null):void
		{
			if(isSelection)
				FSCommands.Send(FSCommands.SELECTIONBUFF_TOOLTIP, FSCommands.TOOLTIP_HIDE+index);
			else 	
				FSCommands.Send(FSCommands.OURBUFF_TOOLTIP, FSCommands.TOOLTIP_HIDE + index);
			
			onFocus = false;
		}
		
		private function set BufTime(percent:Number):void
		{			
			if (percent < epselon) 
				percent = 0;
			
			if (percent > 1 - epselon) percent = 1;
			
			if (isNewIcon && percent == 0 )
			{
			//	bufDebufFlash_mc.visible = true;
			//	bufDebufFlash_mc.gotoAndPlay(2);
				isNewIcon = false;
			}
			
			var framesCount:Number = mask_mc.totalFrames;
			
			var curFrame:Number = Math.round(framesCount * percent + 0.5);		
			
			if (!isNeedToShowup)	return;

			mask_mc.gotoAndStop(curFrame);
		}

		private function get BuffTime():String
		{
			return (time);
		}

		private function get iconPath():String
		{
			return(iconPath);
		}

		private function set iconPath(path : String ):void
		{	
			iconpath = path;			
			if (iconpath == "")	
			{
				if (onFocus) onOut();
				this.visible = false;
				return;
			}
			
			if (onFocus) 
			{
				onOut();
				onOver();
			}
			
			var myURLRequest:URLRequest = new URLRequest(path);

			loader.unload();
			loader.load(myURLRequest);
			
			
			if (!isNeedToShowup)	return;
			
			isNewIcon = true;
			this.visible = true;
		}
		
		private function set BuffCount(count:int):void
		{
			if (count <= 1) 
			{
				count_text.visible = false; return;
			}
			
			count_text.text = count.toString();
			
			count_text.visible = true;
		}
		
		public function SetBuffIcon(_isSelection:Boolean,path:String,_index:int, isPositive:Boolean):void
		{	
			index = _index;
			isSelection = _isSelection;
			BufDeBuf = isPositive;
			iconPath = path;
			if (!this.visible)
				mask_mc.gotoAndStop(1);
			
		}
		
		public function SetBuffStatus(cooldown:Number, count:int):void
		{
			BufTime = cooldown;
			BuffCount = count;
		}
		
		public function Hide(hide:Boolean):void
		{	
			isNeedToShowup = !hide;
			this.visible = !hide? (iconpath != null && iconpath.length != 0) : false;
		}
	}
}