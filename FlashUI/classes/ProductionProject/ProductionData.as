package 
{
	import flash.text.TextField;
	
	public class ProductionData 
	{
		public	var	IsActive: Boolean;
		public	var	IsWorking: Boolean;
		public	var	TitleText: String;
		public	var	ProductionTimer: int;
		public	var	MathTimer: int;
		public	var	ProductionProgress: Number;		
		public	var	CurrentProgress: Number;
		public	var	IsFaded: Boolean;
		//public	var	IsPremium: Boolean;
		
		public	var	CycleCost: ProductionCostResource;
		public	var ProductionBonus: ProductionBounusResource;
		public var Index:int;
	}	
}