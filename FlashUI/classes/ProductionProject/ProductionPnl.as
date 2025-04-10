package 
{
	//import fl.controls.TextArea;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.ColorTransform;
	
	public class ProductionPnl extends MovieClip
	{
		public	var	close_btn: MyButton;
		public	var	desc_txt: TextField;
		public	var	bathItem_mc: ProductionItem;
		
	
		private var arrItems:Array = new Array();
		
		public function ProductionPnl()
		{
			bathItem_mc.visible = false;
			desc_txt.text = "Домики производственных циклов";
			close_btn.addEventListener(MouseEvent.MOUSE_DOWN, OnCloseClick);
			
			for (var i:int = 3; i >= 0; i--) 
			{
				var newItem:ProductionItem = new ProductionItem();
				this.addChild(newItem);
				newItem.x = bathItem_mc.GetWidth() * i + 3;
				newItem.y = bathItem_mc.y;
				arrItems.push(newItem);
			}
		}
		
		public function SetCyclesData(productionCycles:Array):void 
		{
			for (var i:int = 0; i < arrItems.length; i++) 
			{
				var item:ProductionItem = arrItems[i];
				
				item.SetCycle(productionCycles[i]);
			}
		}
		
		private function OnCloseClick(e:MouseEvent):void 
		{
			trace ("Close panel click");
		}
	}
}