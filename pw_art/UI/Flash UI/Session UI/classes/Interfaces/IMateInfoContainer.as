package Interfaces
{
	import BaseClasses.MateInfoBase;
	
	public interface IMateInfoContainer 
	{
		function getNewMateInfo():MateInfoBase;
		function ResetMateState():void;
		function ResetMateSelection():void;
		function GetStartPositions():Array;
		function ShowChain(i:int, show:Boolean):void;
		function HideChains():void;
	}
	
}
