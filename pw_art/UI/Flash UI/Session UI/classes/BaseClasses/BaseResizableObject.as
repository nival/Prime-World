package BaseClasses
{
	
	import Events.ResolutionScaleEvent;
	import fl.transitions.TweenEvent;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	
	public class BaseResizableObject extends MovieClip 
	{
		public var curPosition:Point=new Point(1,1);
		protected var initialStage:Point = new Point(1280, 1024);
		protected var initialSize:Point = new Point(1, 1);
		private var oldStage:Point = new Point(1280, 1024);
		private var proportion:Number;
		public var startPozition:Point = new Point();
		
		protected var positionOnCenter:Number;
		protected var scale:Number = 1;
		protected var startXPosition:Number;
		protected var startYPosition:Number;
		protected var tweenThisAlpha:Tween;
		
		protected var isAddedToStage:Boolean = false;
		
		protected var useWidthScale:Boolean = false;
		
		private var scaleCoef:Number = 1;
		private var _isNeedToShowBackAfterCinematic:Boolean;
		public function BaseResizableObject() 
		{	
			this.stop();
			
			proportion = initialStage.x / initialStage.y;
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			tweenThisAlpha = new Tween(this, 'alpha', Strong.easeOut, 0, 1, 20);
			tweenThisAlpha.addEventListener(TweenEvent.MOTION_STOP, OnTweenFinished)
			this.visible = true;
		}
		
		public function get isNeedToShowBackAfterCinematic():Boolean
		{
			return _isNeedToShowBackAfterCinematic;
		}
		
		public function set isNeedToShowBackAfterCinematic( value:Boolean )
		{
			_isNeedToShowBackAfterCinematic = value;
		}
		
		public function AddedToStage(e:Event):void
		{	
			
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
			this.width = Math.floor(this.width);
			this.height = Math.floor(this.height);
			
			
			initialSize.x = this.width;
			initialSize.y = this.height;
			oldStage.x = initialStage.x;
			oldStage.y = initialStage.y;
		
			positionOnCenter = (stage.stageWidth/2 - this.x)/this.width;
			
			curPosition.x = this.x;
			curPosition.y = this.y;
			
			startPozition.x = this.x;
			startPozition.y = this.y;
			startXPosition = this.x;
			startYPosition = this.y;
			BaseBarObjectResize();
			
			stage.addEventListener(Event.RESIZE, BaseBarObjectResize);
			stage.addEventListener(ResolutionScaleEvent.EVENT_TYPE, SetScaleKoeff);
			
			isAddedToStage = true;
		}
		
		private function SetScaleKoeff(e:ResolutionScaleEvent):void 
		{
			scaleCoef = e.ResolutionKoeff;
		}
		
		protected function BaseBarObjectResize(e:Event=null):void
		{	
			var StageScaleX: Number = stage.stageWidth / oldStage.x;
			var StageScaleY: Number = stage.stageHeight / oldStage.y;
			
			var oldWidth:Number = WidthForPosition;
			var oldHeight:Number = this.height;
			RescaleThisBar( stage.stageWidth / initialStage.x, stage.stageHeight / initialStage.y); //change size
			//change placement
			if (curPosition.x<oldStage.x/2)
				this.x = curPosition.x * StageScaleX;
			else
			{
				var offsetX:Number = (oldStage.x - curPosition.x - oldWidth ) ;

				this.x = stage.stageWidth - offsetX * StageScaleX - WidthForPosition;
			}
			
			if (curPosition.y <= oldStage.y / 2) 
				this.y = curPosition.y * StageScaleY;
				
			else
			{
				var offsetY:Number = (oldStage.y - curPosition.y - oldHeight ) ;
				this.y = stage.stageHeight - offsetY * StageScaleY - this.height;
			}
					
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
			curPosition.x = this.x;
			curPosition.y = this.y;
			
			if (startPozition.x < oldStage.x / 2)
			{
				startPozition.x*=StageScaleX;
			}
			else
			{
				var startPosOffsetX:Number = (oldStage.x - startPozition.x - oldWidth ) ;
				
				startPozition.x = stage.stageWidth - startPosOffsetX*StageScaleX - WidthForPosition;
			}
			if (startPozition.y <= oldStage.y / 2) 
				startPozition.y *= StageScaleY;
			else
			{
				var startPosOffsetY:Number = (oldStage.y - startPozition.y - oldHeight ) ;
				this.y = stage.stageHeight - startPosOffsetY * StageScaleY - this.height;
			}
			
			oldStage.x = stage.stageWidth;
			oldStage.y = stage.stageHeight;
		}
		
		private function RescaleThisBar(scaleByWidth:Number,scaleByHeight:Number):void
		{		
			var newProportion:Number = stage.stageWidth / stage.stageHeight;
			useWidthScale = newProportion < proportion;
	//		scale = useWidthScale? scaleByWidth: scaleByHeight;
		
			scale = 1;
	
			var scaledWidth:Number = initialStage.x * scaleCoef;
			
			if (stage.stageWidth <= scaledWidth) 
				scale = (stage.stageWidth / scaledWidth);
						
			scale *= scaleCoef;
			
			this.scaleX = scale;
			this.scaleY = scale;
			this.width = Math.floor(this.width);
			this.height = Math.floor(this.height);
		}
		
		
		protected function set CurrentPosition(point:Point):void
		{
			var scaleX: Number = stage.stageWidth / initialStage.x;
			var scaleY: Number = stage.stageHeight / initialStage.y;
			
			curPosition.x = point.x; //scaleX;
			curPosition.y = point.y; //scaleY;
		}
		
		public function ShowFinalAnimation():void
		{
			this.play();
			this.addFrameScript(this.totalFrames-1, StopPlay);
		}
		
		private function StopPlay():void
		{
			this.stop();
			this.visible = false;
		}
		
		protected function get WidthForPosition():Number 
		{
			return this.width;
		}
		
		
		public function ShowCinematicDialog():void
		{
			isNeedToShowBackAfterCinematic = this.visible;
			tweenThisAlpha.stop();
			tweenThisAlpha.begin = this.alpha;
			tweenThisAlpha.finish = 0;
			tweenThisAlpha.start();
		}
		
		public function HideCinematicDialog():void
		{
			tweenThisAlpha.stop();
			tweenThisAlpha.begin = this.alpha;
			tweenThisAlpha.finish = 1;
			tweenThisAlpha.start();
			this.visible = isNeedToShowBackAfterCinematic;
		}
		
		private function OnTweenFinished(e:TweenEvent):void 
		{
			if (alpha == 0)
				visible = false;
		}
	}
}
