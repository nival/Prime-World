package Interfaces 
{
	import TalentBar.Talent;
	
	public interface IShowImpulseTalent 
	{
		function AddImpulseTalent(talent:Talent, topLevel:int, minLevel:int):void;
		function RemoveImpulseTalent(talent:Talent):void;
		function ShowImpulseTalent():void;
	}	
}