package Components 
{
	
	import Controllers.SoundController;
	import Interfaces.IPWComponents;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.geom.Rectangle;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import src.Desaturate;
	import src.WButton;
	
	public class PWSlider extends MovieClip implements IPWComponents
	{
		private var disabled:Boolean = false;
		private var dragRectangle:Rectangle;
		private var currentValue:int = 0;

		private var sectionWidth:Number = 0;
		private var sectionsCount:int = 10;
		private var isSliderDragging:Boolean;
		
		//ref
		public var sliderBack_mc:MovieClip;
		public var slider_btn:WButton;
		public var sliderBody_mc:MovieClip;
		
		public function PWSlider() 
		{
			super.scaleX = super.scaleY = 1;
			sliderBody_mc.width = slider_btn.x;
			slider_btn.addEventListener(MouseEvent.MOUSE_DOWN, OnMouseDown);
			dragRectangle = new Rectangle(sliderBack_mc.x, slider_btn.y, sliderBack_mc.width,0);
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			sectionWidth = sliderBack_mc.width / sectionsCount;
			
			this.addEventListener(MouseEvent.CLICK, onSliderLineClick);
		}
		
		private function AddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			stage.addEventListener(MouseEvent.MOUSE_UP, OnMouseUp);
		}
		
		public function SetSize(_width:Number, _height:Number):void
		{
			sliderBack_mc.width = _width;
			dragRectangle.width = _width;
		}
		public function setSize(_width:Number, _height:Number):void
		{
			sliderBack_mc.setSize(_width, _height);
			dragRectangle.width = _width;
		}
		private function OnMouseDown(e:MouseEvent):void
		{
			if (disabled) return;
			
			isSliderDragging = true;
			slider_btn.startDrag(false, dragRectangle);
			stage.addEventListener(MouseEvent.MOUSE_MOVE, MoveSlider);
		}
		private function OnMouseUp(e:MouseEvent):void
		{
			if (disabled) return;
			
			if(isSliderDragging)
				SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
				
			isSliderDragging = false;
			slider_btn.stopDrag();
			stage.removeEventListener(MouseEvent.MOUSE_MOVE, MoveSlider);

			SetSliderPosition(currentValue * sectionWidth);
		}
		
		public function set Disable(value:Boolean):void
		{
			disabled = value;
			
			if(disabled)
				Desaturate.desaturate(this);
			else
				Desaturate.saturate(this);
		}
		
		public function SetSectionsCount(value:int):void
		{
			sectionWidth = sliderBack_mc.width / (value-1);
			sectionsCount = value-1;
		}
		
		public function set Value(value:int):void
		{
			if (isSliderDragging) return;
			
			currentValue = value;
			SetSliderPosition(sectionWidth * currentValue);
		}
		
		private function onSliderLineClick(e:MouseEvent):void 
		{ 
			if (this.mouseX < sliderBack_mc.x||this.mouseX > sliderBack_mc.x+sliderBack_mc.width) return;		
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
			
			slider_btn.x = this.mouseX;
			sliderBody_mc.width = slider_btn.x;
			
			var prevValue:int = currentValue; 
			
			currentValue = int(slider_btn.x / sectionWidth);
			currentValue = slider_btn.x >sliderBack_mc.x+ currentValue * sectionWidth + sectionWidth / 2? currentValue + 1 : currentValue;			
			
			if(prevValue!=currentValue)
				dispatchEvent(new PWComponentValueEvent(PWComponentValueEvent.CHANGE, currentValue,this.name));
			
		}
		
		private function MoveSlider(e:MouseEvent):void
		{	
			var prevValue:int = currentValue; 
			
			sliderBody_mc.width = slider_btn.x;
			currentValue = int(slider_btn.x / sectionWidth);
			currentValue = slider_btn.x >currentValue * sectionWidth + sectionWidth / 2? currentValue + 1 : currentValue;			
			
			if(prevValue!=currentValue)
				dispatchEvent(new PWComponentValueEvent(PWComponentValueEvent.CHANGE, currentValue,this.name));
		}
		
		private function SetSliderPosition(posX:Number):void
		{
			slider_btn.x = posX+sliderBack_mc.x;
			sliderBody_mc.width = slider_btn.x;
		}
	}
}