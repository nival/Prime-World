package ShopBar
{

	import Components.ScrollableContent;
	import Components.ScrollBar;
	import DragAndDrop.ShopDragOBject;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.events.Event;
	import BaseClasses.BaseDragObject;
	import Enums.ShopUIState;
	import DragAndDrop.DnDController;
	
	public class ShopBar extends BaseDragObject
	{
		private var shopBar_arr:Array;
		private var curItemCount:int = 0;
		
		public var merschant_mc:Merschant;
		public var merch:MovieClip;
		public var shopItem1_mc:ShopBarButton;
		public var shopItem2_mc:ShopBarButton;
		public var shopItem3_mc:ShopBarButton;
		public var shopItem4_mc:ShopBarButton;
		public var shopItem5_mc:ShopBarButton;
		public var shopItem6_mc:ShopBarButton;
		public var shopItem7_mc:ShopBarButton;
		public var shopItem8_mc:ShopBarButton;
		public var shopItem9_mc:ShopBarButton;
		public var shopItem10_mc:ShopBarButton;
		public var shopItem11_mc:ShopBarButton;
		public var shopItem12_mc:ShopBarButton;
		public var shopItem13_mc:ShopBarButton;
		public var shopItem14_mc:ShopBarButton;
		public var shopItem15_mc:ShopBarButton;
		public var shopItem16_mc:ShopBarButton;
		public var shopItem17_mc:ShopBarButton;
		public var shopItem18_mc:ShopBarButton;
		public var shopItem19_mc:ShopBarButton;
		public var shopItem20_mc:ShopBarButton;
		
		public var header_txt:TextField;		
		public var scrollBar:ScrollBar;
		
		private var shopScrollableContent:ScrollableContent
		private var columnsCount:int = 4;
		
		public function ShopBar()
		{			
			shopBar_arr = [shopItem1_mc,shopItem2_mc,shopItem3_mc,shopItem4_mc,shopItem5_mc,shopItem6_mc,shopItem7_mc,shopItem8_mc,shopItem9_mc,shopItem10_mc,shopItem11_mc,shopItem12_mc,shopItem13_mc,shopItem14_mc,shopItem15_mc,shopItem16_mc,shopItem17_mc,shopItem18_mc,shopItem19_mc,shopItem20_mc];
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
				
				merschant_mc.mouseEnabled = false;
				merschant_mc.mouseChildren = false;
		}
		
		override public function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);
			
			var startX:Number = shopItem1_mc.x;
			var startY:Number = shopItem1_mc.y;
			
			shopScrollableContent = new ScrollableContent(shopBar_arr,columnsCount, shopBar_arr.length / columnsCount);
			
			this.addChild(shopScrollableContent);
			shopScrollableContent.x = startX;
			shopScrollableContent.y = startY;
			
			scrollBar.SetScrollableContent(shopScrollableContent,false);
			scrollBar.RecalcContentHeight();
		}
		
		private function FillLocalization(e:Event):void
		{
			header_txt.text = Localization.ShopBar_HeaderText;
		}

		public function get iconArray():Array
		{
			return shopBar_arr;
		}

		public function SetShopItemsCount(count:int):void
		{
			if (shopBar_arr.length < count)
			{
				shopScrollableContent.AddShopButtons(count - shopBar_arr.length);
				scrollBar.RecalcContentHeight();
			}

			if (count < curItemCount)
				for (var i:int = count; i< curItemCount; i++)
				{
					SetShopItemIcon(i, "");
				}
							
			curItemCount = count;
			
		}
		public function SetShopItemIcon(index:int,path:String):void
		{
			if (index >= curItemCount) 
				return;
			
			if (path.length>0)				
				shopBar_arr[index].enable();
			else
				shopBar_arr[index].disable();
				
			shopBar_arr[index].ID = index;
			shopBar_arr[index].iconPath = path;
			shopBar_arr[index].Status = ShopUIState.CANBUY;
			shopBar_arr[index].Filled = path.length>0;
		}
		
		public function SetShopItemState(index:int, ShopItemState:int)
		{
			var item:ShopBarButton = shopBar_arr[index];

			if (item == null)
			{
				return;
			}
			
			item.Status = ShopItemState;
			
			switch (ShopItemState)
			{
				case ShopUIState.CANBUY :
					{
						item.enable();
						break;
					};
				case ShopUIState.NOTENOUGH_PRIME :
					{
						item.unNafta();
						break;
					};
				default :
					{
				}
			}
		}
		
		public function HideTooltip():void
		{
			for (var i:int = 0; i < shopBar_arr.length; i++)
			{
				shopBar_arr[i].HideTooltip(); 
			}
		}
		
		public function EndDragItem():void
		{
			if (DnDController.isDragging)
			{
				if (DnDController.DraggingObject is ShopDragOBject)
				{
					DnDController.EndDrag();
				}
			}
		}
		
		public function ResetShopItems():void
		{
			for (var i:int = 0; i < shopBar_arr.length; i++)
			{
				SetShopItemIcon(i, "");
			}
		}
		
		public function ShowTutorialShopBarItemHighlight(slot, show):void
		{
			var item:ShopBarButton = shopBar_arr[slot];

			if (item == null)
				return;
			
			if (show)
				item.ShowTutorialHighlight()
			else
				item.HideTutorialHighlight();
			
		}
		
		public function GetShopBarItem(index:int):MovieClip
		{
			if (index >= shopBar_arr.length||index<0) return null;
			
			return shopBar_arr[index];
		}
		
	}
}