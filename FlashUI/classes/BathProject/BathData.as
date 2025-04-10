package 
{
	import flash.text.TextField;
	
	public class BathData 
	{
		public	var	IsActive: Boolean;
		public	var	IsWorking: Boolean;
		public	var	TitleText: String;
		public	var	BathTimer: int;
		public	var	MathTimer: int;
		public	var	BathProgress: Number;		
		public	var	CurrentProgress: Number;
		public	var	IsFaded: Boolean;
		//public	var	IsPremium: Boolean;
		
		public	var	CycleCost: BathCostResource;
		public	var BathBonus: BathBounusResource;
		public var Index:int;
	}	
}