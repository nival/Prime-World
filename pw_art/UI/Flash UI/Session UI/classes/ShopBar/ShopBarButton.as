package ShopBar
{
	import Controllers.SoundController;
	import fl.transitions.TweenEvent;
	import flash.display.Loader;
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import flash.geom.Point;
	import flash.display.BlendMode;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.URLRequest;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;

	import DragAndDrop.ShopDragOBject;
	import Events.MouseRightEvents;
	import DragAndDrop.DnDController;
	import Events.ErrorEvent;
	import Enums.EErrorMessageType;
	import Components.IcoShop;
	import Enums.ShopUIState;
	import Strokes.*;
	
	public class ShopBarButton extends MovieClip
	{
		private var configPath:String = 'art/general/';
		private var isButtonDown:Boolean = false;
		private const myTime:Number = 7;
		private var id:int;
		public var type:String;
		public var path:String;
		private var isFilled:Boolean = false;
		private var _status:int = -1;
		
		//reference
		public var ico_mc:IcoShop;
		public var over_mc:MovieClip;
		public var up_mc:MovieClip;
		public var overDown_mc:MovieClip;
		public var down_mc:MovieClip;
		public var hightLight_mc:MovieClip;
		public var nafta_mc:MovieClip;
		
		private var over_bm:DisplayObject;
		private var overDown_bm:DisplayObject;
		private var down_bm:DisplayObject;
		private var hightLight_bm:DisplayObject;
		private var up_bm:DisplayObject;
		private var nafta_bm:DisplayObject;
		
		private var	tweenOut:Tween;
		private var	tweenIn:Tween;
		
		private var isTooltipShowing:Boolean = false;
		private var downPosition:Point = new Point( -10, -10);
		private var tutorialHighLight:SquadStroke;
		
		public function ShopBarButton()
		{
			type = ico_mc.type;
			path = ico_mc.path;
			
			nafta_mc.visible = false;

			this.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT,onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN,onDown);
			this.addEventListener(MouseEvent.MOUSE_UP,onUp);
			this.addEventListener(MouseRightEvents.RIGHT_CLICK, BuyItem);
			this.addEventListener(MouseEvent.MOUSE_MOVE, MouseMoveOverThis);
			this.buttonMode = true;
			this.mouseChildren = false;

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
			
			var naftaPosition:Point = new Point(nafta_mc.x, nafta_mc.y);
			
			nafta_bm = ConvertFromMovieToBitmap(nafta_mc);
			nafta_bm.x = naftaPosition.x;
			nafta_bm.y = naftaPosition.y;
			
			up_mc = null;
			over_mc = null;
			down_mc = null;
			overDown_mc = null;
			hightLight_mc = null;
			nafta_mc = null;
			
			over_bm.visible = false;
			overDown_bm.visible = false;
		
			disable();
			
		}
		
		private function ConvertFromMovieToBitmap(dispObject:MovieClip):DisplayObject
		{
			
			var bitm:DisplayObject = dispObject.getChildAt(0) as DisplayObject;
			
			
			this.addChildAt(bitm, this.getChildIndex(dispObject));
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
		
		private function MouseMoveOverThis(e:MouseEvent):void
		{
			if (DnDController.isDragging||downPosition.x==-10||downPosition.y==-10) return;
			
			if (!isFilled)
				return;
				
			var dragRadius:Number = 4;
			var curRadius:Number = Math.sqrt(Math.abs(this.mouseX - downPosition.x) * Math.abs(this.mouseX - downPosition.x) + Math.abs(this.mouseY - downPosition.y) * Math.abs(this.mouseY - downPosition.y));
			
			
			if (isButtonDown && curRadius >= dragRadius && enabled)
				StartDragThis();
		}
		
		protected function StartDragThis():void
		{
			DnDController.StartDrag(new ShopDragOBject(this));
		}
		
		private function onOver(e:MouseEvent):void
		{
			if (!isFilled) return;
			
			if(enabled)
			{
				if (isButtonDown)
				{
					down();
				}
				else
				{
					over();
				}
			}
		
			FSCommands.Send(FSCommands.SHOPITEM_TOOLTIP, FSCommands.TOOLTIP_SHOW + ' ' + ID.toString());
			isTooltipShowing = true;
		}
		
		private function onOut(e:MouseEvent):void
		{
			if (!isFilled) return;
				
			if(enabled)
			{
				if (isButtonDown)
				{
					ico_mc.onUp();
				}
			
				
				downPosition.x = -10;
				downPosition.y = -10;
				
				up();
			}
			
			isButtonDown = false;
			FSCommands.Send(FSCommands.SHOPITEM_TOOLTIP, FSCommands.TOOLTIP_HIDE + ' ' + ID.toString());
			isTooltipShowing = false;
		}
		
		private function onDown(e:MouseEvent):void
		{
			if (!isFilled||!enabled) return;
			
			isButtonDown = true;
			downPosition.x = this.mouseX;
			downPosition.y = this.mouseY;
			
			down();
			
			DnDController.HightLightingObject = null;
		}
		
		public function onUp(e:MouseEvent):void
		{
			if (!enabled) 
			{
				isButtonDown = false;
				return;
			}
			
			if (!isFilled||!isButtonDown) return;
			
			ico_mc.onUp();
			over();
			
			isButtonDown = false;
	
			downPosition.x = -10;
			downPosition.y = -10;
			
			if (DnDController.isDragging)
				return;
				
				
			BuyItem();
		}
		
		public function BuyItem(e:MouseEvent=null):void
		{
			if (!isFilled||!enabled) return;
			
			if (_status==ShopUIState.NOTENOUGH_PRIME)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY));
				return;
			}
			
			FSCommands.Send(FSCommands.SHOPITEM_CLICK, ID.toString());
			
			SoundController.PlaySound(SoundController.BUY_SOUND);
		}
		
		public function set iconPath(value:String):void
		{
			if (ico_mc == null) return;
			ico_mc.ico = value;
		}
		
		public function get iconPath():String
		{
			if (ico_mc == null) return "";
			return ico_mc.ico;
		}
		
		public function set Status(value:int):void
		{
			_status = value;
		}
		
		public function set Filled(value:Boolean):void
		{
			isFilled = value;
		}
		
		public function HideTooltip():void
		{
			if (isTooltipShowing)
			{
				FSCommands.Send(FSCommands.SHOPITEM_TOOLTIP, FSCommands.TOOLTIP_HIDE + ' ' + ID.toString());
				isTooltipShowing = false;
			}
		}
		
		private function up()
		{
			up_bm.visible = true;
			over_bm.visible = true;
			down_bm.visible = false;
			overDown_bm.visible = false;
			hightLight_bm.visible = true;
			
			StartOutAnimation(over_bm);
			
			tweenIn.obj = overDown_bm;
			tweenIn.stop();
		}
		private function down()
		{
			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = true;
			overDown_bm.visible = true;
			hightLight_bm.visible = false;
			
			tweenIn.obj = over_bm;
			tweenIn.stop();
			
			StartOutAnimation(overDown_bm);
			
			ico_mc.onDown();
		}
		private function over()
		{
			up_bm.visible = true;
			over_bm.visible = true;
			down_bm.visible = false;
			overDown_bm.visible = false;
			hightLight_bm.visible = true;
			
			StartInAnimation(over_bm);
		}
		private function overDown()
		{
			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = false;
			overDown_bm.visible = true;
			hightLight_bm.visible = false;
			
			StartInAnimation(overDown_bm);
		}
		public function unNafta():void
		{
			enabled = false;
			
			nafta_bm.visible = true;
			ico_mc.disable();
			
			tweenIn.obj= over_bm
			tweenOut.obj= over_bm
			tweenIn.stop();
			tweenOut.stop();
			
			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = false;
			hightLight_bm.visible = false;
		}
		public function enable():void
		{
			enabled = true;
			nafta_bm.visible = false;
			
			up_bm.visible = true;
			over_bm.visible = false;
			down_bm.visible = false;
			hightLight_bm.visible = true;

			ico_mc.enable();
		}
		public function disable():void
		{
			enabled = false;
			nafta_bm.visible = false;
			
			tweenIn.obj =  over_bm
			tweenOut.obj= over_bm
			tweenIn.stop();
			tweenOut.stop();
			
			up_bm.visible = false;
			over_bm.visible = false;
			down_bm.visible = false;
			hightLight_bm.visible = false;

			ico_mc.disable();
		}
		public function set ID(_id:int):void
		{
			id = _id;
		}
		public function get ID():int
		{
			return id;
		}
		
		public function ShowTutorialHighlight():void
		{
			if (tutorialHighLight != null)
				return;
				
			tutorialHighLight = new SquadStroke();
			
			this.addChildAt(tutorialHighLight, this.numChildren - 1);	
			
			tutorialHighLight.setSize(this.width, this.height);
		}
		
		public function HideTutorialHighlight():void
		{
			if (tutorialHighLight == null)
				return;
				
			this.removeChild(tutorialHighLight);	
			tutorialHighLight = null;
		}
		
	}
}