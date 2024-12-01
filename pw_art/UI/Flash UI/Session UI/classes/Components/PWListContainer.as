package Components 
{
	import flash.display.MovieClip;
	import Interfaces.IScrollableObject;
	
	public class PWListContainer  extends MovieClip implements IScrollableObject
	{
		
		private var actualHeight:Number = 100;
		private var stepSize:Number = 10;
		private var scrolableHeight:Number = 18;
		private var rows:Array = new Array();
		private var rowContainerOffset:Number = 3;
		private var rowHeight:Number = 24;
		private var rowWidth:Number = 1
		private var maxRowCount:Number = 5;
		private var scrollBarWidth:Number = 24;
		
		public var selectedItem:int = -1;
		private var _visibleList:Array = new Array();
		public var lowerItem:int;
		public var higherItem:int;
		public var ScrollBarUp:Function;
		public var ScrollBarDown:Function;
		
		public function PWListContainer()
		{
			visible = false;
			stepSize = rowHeight;
			actualHeight = maxRowCount * rowHeight + 2 * rowContainerOffset;
			_visibleList = rows;
			
			higherItem = 0;
			lowerItem = maxRowCount-1;
		}
		
		public function set MaxRowCount(value:Number):void
		{
			maxRowCount = value;
			actualHeight = maxRowCount * rowHeight + 2 * rowContainerOffset;
		}
		
		public function get MaxRowCount():Number
		{
			return maxRowCount;
		}
		
		public function SetVisibleItems(visibleList:Array):void 
		{
			selectedItem = -1;
			higherItem = 0;
			lowerItem = maxRowCount - 1;
			
			var nextPos:Number = rowContainerOffset - 1;
			
			_visibleList = visibleList;
		
			for (var i:int = 0; i < rows.length; i++) 
			{
				var contains:Boolean = false;
				for (var j:int = 0; j < visibleList.length; j++) 
				{
					if (rows[i].ID == visibleList[j].ID)
						contains = true;
				}
				
				rows[i].y = contains ? nextPos : 0;
				rows[i].visible = contains;
				
				if (contains)
					nextPos += rowHeight;
			}
			
			UpdateSelectRectangle();
			
			scrolableHeight = nextPos + rowContainerOffset - 1;
		}
		
		public function RowWidth(value:Number)
		{
			rowWidth = value;
			
			if (rows.length == 0) return;
			
			for each (var item:ComboBoxRow in rows) 
			{
				item.SetWidth(rowWidth);
			}
		}
		
		public function AddElement(row:ComboBoxRow):void 
		{
			addChild(row);
			row.ID = rows.length;
			row.SetWidth(rowWidth); 
			row.SetHeigt(rowHeight);
			
			row.y = rows.length == 0? rowContainerOffset : rows[rows.length - 1].y + rowHeight;
			rows.push(row);
			
			scrolableHeight = rows.length * rowHeight + 2 * rowContainerOffset;
		}
		
		public function MoveSelectDown():void 
		{
			if (selectedItem == _visibleList.length - 1) return

			selectedItem++;
			
			UpdateSelectRectangle();
		}
		
		public function MoveSelectUp():void 
		{
			if (selectedItem == 0) return;
			
			if (selectedItem == -1)
			{
				selectedItem = 0
			}
			else	
			{
				selectedItem--;
			}
			
			UpdateSelectRectangle();
		}
		
		private function UpdateSelectRectangle():void
		{
			for each (var item:ComboBoxRow in _visibleList) 
			{
				item.ShowSelectRectangle(false);
			}
			
			if (selectedItem > lowerItem)
			{
				lowerItem++;
				higherItem++;

				ScrollBarDown.call();
			}
			
			if (selectedItem < higherItem)
			{
				lowerItem--;
				higherItem--;

				ScrollBarUp.call();
			}
			if (_visibleList[selectedItem]!=null)
				_visibleList[selectedItem].ShowSelectRectangle(true);
		}
		
		/* INTERFACE Interfaces.IScrollableObject */
		
		public function get TopMargin():Number 
		{
			return 5;
		}
		
		public function get BottomMargin():Number 
		{
			return 8;
		}
		
		public function get ScrollableHeight():Number
		{
			return scrolableHeight;
		}
		
		public function get StepSize():Number
		{
			return stepSize;
		}
		
		public function set StepSize(value:Number):void
		{
			stepSize = value;
		}
		
		public function get ActualHeight():Number
		{
			return actualHeight;
		}
		override public function get width():Number
		{
			return rowWidth+scrollBarWidth;
		}
	}
}
