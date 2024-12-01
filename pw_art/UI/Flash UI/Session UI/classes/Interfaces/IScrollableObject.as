package Interfaces
{
	import flash.display.DisplayObject;
	
	public interface IScrollableObject 
	{
		function get ScrollableHeight():Number; // вся скролируемая область
		function get StepSize():Number;
		
		function get x():Number;
		function get y():Number;
		function set y (value:Number) : void;
		function get width():Number;
		function get ActualHeight():Number;  //видимая часть скролироваемого объекта
		function set mask (value:DisplayObject) : void;
		function get TopMargin():Number;
		function get BottomMargin():Number;
	}
	
	
}