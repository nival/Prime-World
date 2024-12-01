package Controllers 
{
	import Components.Bar;
	import flash.display.DisplayObject;
	import Strokes.*;
	import Components.ButtonRound;
	import fl.transitions.Tween;
	import flash.display.MovieClip;

	public class TutorialHighlighter 
	{
		private var tutorialHighLight:Stroke;
		private var _control:MovieClip;
		private var _highLightStroke:String;
		private var _xOffSet:Number;
		private var _yOffSet:Number;
		private var _xAddition:Number;
		private var _yAddition:Number;
		private var sizeControl:DisplayObject;
		
		public static const SquadStrokeType:String = "SquadStroke";
		public static const RoundStrokeType:String = "RoundStroke";
		
		public function TutorialHighlighter(control:MovieClip, _sizeControl:DisplayObject, highLightStroke:String, xOffSet:Number = 0, yOffset:Number = 0, xAddition:Number = 0, yAddition:Number = 0) 
		{
			sizeControl = _sizeControl;
			_control = control;
			_highLightStroke = highLightStroke;
			_xOffSet = xOffSet;
			_yOffSet = yOffset;
			_xAddition = xAddition;
			_yAddition = yAddition;
		}
		
		private function GetHighlight():Stroke 
		{
			if (_highLightStroke==RoundStrokeType) 
			{
				return new RoundStroke();
			}
			
			return new SquadStroke();
		}
		
		
		public function ShowTutorialHighlight():void
		{
			if (tutorialHighLight != null)
				return;
				
			tutorialHighLight = GetHighlight();
			tutorialHighLight.x = _xOffSet;
			tutorialHighLight.y = _yOffSet;
			var newWidth:Number = 0;
			var newHeight:Number = 0;
			
			var controlForSize:DisplayObject = sizeControl == null? _control : sizeControl;

			tutorialHighLight.setSize(controlForSize.width + _xAddition, controlForSize.height+_yAddition );
				
			_control.addChild(tutorialHighLight);
			_control.setChildIndex(tutorialHighLight,_control.numChildren - 1);
			//_control.addChildAt(tutorialHighLight, _control.numChildren - 1);	
		}
		
		public function HideTutorialHighlight():void
		{
			if (tutorialHighLight == null)
				return;
				
			_control.removeChild(tutorialHighLight);	
			tutorialHighLight = null;
		}
	}

}