package Interfaces
{

	public interface IActionButton
	{
		function GlobalCoolDown(_cooldown:Number,_maxCooldown:Number):void;
		
		function Cooldown(_cooldown:Number,_maxCooldown:Number):void;
		function set iconPath(_path:String):void;
		function set State(_state:int):void;
		function get State():int;
		function set count(value:int):void;
		function DontShowCoolDownEndAnimation():void;
	}
}