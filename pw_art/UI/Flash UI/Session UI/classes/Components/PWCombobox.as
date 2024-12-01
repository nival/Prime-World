package Components
{
	
	import Controllers.SoundController;
	import flash.events.KeyboardEvent;
	import Interfaces.IPWComponents;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.WButton;
	import flash.events.MouseEvent;
	import flash.display.Shape;
	import flash.text.TextField;
	import flash.display.Sprite;
	import flash.geom.Rectangle;
	
	public class PWCombobox extends MovieClip  implements IPWComponents
	{
		private var rowsNumber:Number = 0;//количество строк
		
		protected var rowsContainer:PWListContainer;//контейнер для строк
		protected var rows:Array = new Array();//Массив со строками
		
		private var disable:Boolean = false;
		
		private var scrollBar:ScrollBar;
		private var selectedIndex:int=-1;
		private var isScrollBarNeeded:Boolean = true;
		
		protected var frame:Frame;
				
		public var button_mc:WButton;//наша кнопка для отображения строк
		public var txt:TextField;
		public var arrow_mc:PWComboboxArrow;
		
		private var isMouseOver:Boolean = false;
		
		 //отступ от верхнего края фрейма (подложки), такой же отступ идёт и от низу.
		
		protected var scrollBarWidth:Number = 21; // для убирания на ширину скроллбара.
		private const arrowZone:int = 37//ширина площади для стрелки.
		
		public function PWCombobox()
		{	
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
		}
		
		protected function AddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			
			txt.mouseEnabled = false;
			
			arrow_mc.mouseEnabled = false;
			button_mc.addEventListener(MouseEvent.CLICK, OnShowList);
			button_mc.addEventListener(MouseEvent.DOUBLE_CLICK, OnShowList);
			button_mc.addEventListener(MouseEvent.MOUSE_OVER, OnButtonOver);
			button_mc.addEventListener(MouseEvent.MOUSE_OUT, OnButtonOut);
			stage.addEventListener(MouseEvent.CLICK, OnStageClick);
			this.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			button_mc.addEventListener(MouseEvent.MOUSE_DOWN, OnMouseDown);
			
		//	stage.addEventListener(KeyboardEvent.KEY_DOWN, OnKeyDown);
			
			rowsContainer = new PWListContainer();
			
			frame = new Frame();
			frame.y = button_mc.height;
			frame.Image = 'frameChat_png';
			frame.visible = false;
			
			var xOffset:int = 11;
			var yOffset:int = 17
			var scaleRectWidth:int = 106; // ширина прямоугольника для скейла, пришлось захардкодить.
			
			var rect:Rectangle = new Rectangle(xOffset, yOffset, scaleRectWidth, Math.max(0,int(button_mc.height - yOffset * 2)) );
			button_mc.ConvertBitmapToScaleBitmap(rect);
				
			configUI();
		}
		
		protected function OnKeyDown(e:KeyboardEvent):void 
		{
			if (e.keyCode == 13) return;
			
			if (!rowsContainer.visible) return;
			
			if (e.keyCode == 40)
			{
				rowsContainer.MoveSelectDown();
				return;
			}
			if (e.keyCode == 38)
			{
				rowsContainer.MoveSelectUp();	
				return;
			}
		}
		
		protected function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			var w:Number = super.width;
			var h:Number = super.height;
			super.scaleX = super.scaleY = 1;
			rotation = r;
			
			addChild(frame);
			addChild(rowsContainer);
			rowsContainer.addEventListener(PWComponentValueEvent.CHANGE, OnRowClick);

			setSize(w, h);
			rowsContainer.RowWidth(button_mc.width);
		}
		public function setSize(_width:Number, _height:Number):void
		{
			button_mc.SetScaleBitmapSizes(_width, _height);
			txt.width = _width - txt.x - arrowZone;  // ширина поля со стрелкой. 
			txt.y = button_mc.y + (button_mc.height - txt.textHeight)/2;
			arrow_mc.x = _width - arrowZone + (arrowZone - arrow_mc.width)/2;
			arrow_mc.y = (_height - arrow_mc.height) / 2;
			
			rowsContainer.y = _height;
			
			frame.setSize(button_mc.width, rowsContainer.ActualHeight);
			frame.y = _height;
		}
		private function OnMouseOut(e:MouseEvent):void 
		{
			isMouseOver = false;
		}
		private function OnButtonOut(e:MouseEvent):void
		{
			arrow_mc.OnOut(e);
		}
		private function OnMouseOver(e:MouseEvent):void 
		{
			isMouseOver = true;
		}
		private function OnButtonOver(e:MouseEvent):void
		{
			arrow_mc.OnOver(e);
		}
		private function OnMouseDown(e:MouseEvent):void
		{
			arrow_mc.OnDown(e);
		}
		
		protected function OnStageClick(e:MouseEvent):void 
		{
			if (rowsContainer.visible && !isMouseOver)
				OnShowList(null);
		}
	
		private function OnRowClick(e:PWComponentValueEvent):void 
		{
			SelectedIndex = e.componentValue;
			OnShowList(null);
		}

		public function set MaxRowCount(value:Number):void
		{
			rowsContainer.MaxRowCount = value;
		}
		public function get MaxRowCount():Number
		{
			return rowsContainer.MaxRowCount;
		}
		
		public function AddComboBoxRow(value:String):int
		{
			if (value == "")
				return -1;
			
			var row:ComboBoxRow = new ComboBoxRow();
			row.Text = value;
			row.ComponentName = this.name;
			rowsContainer.AddElement(row);
			rows.push(row);
			
			if (SelectedIndex == -1)
				SelectedIndex = 0;
				
			if(rowsContainer.ActualHeight < rowsContainer.ScrollableHeight)
			{
				rowsContainer.RowWidth(button_mc.width - scrollBarWidth)
				
				frame.setSize(button_mc.width - scrollBarWidth, rowsContainer.ActualHeight);

				if (scrollBar == null)
				{
					scrollBar = new ScrollBar();
					this.addChild(scrollBar);
					scrollBar.SetScrollableContent(rowsContainer);
					scrollBar.addEventListener(MouseEvent.CLICK, OnScrollClick);
				}
			}
			else
			{
				frame.setSize(button_mc.width, rowsContainer.ScrollableHeight);
			}
			
			if (scrollBar != null)
			{
				scrollBar.RecalcContentHeight();
				scrollBar.visible = rowsContainer.visible;
			}
			
			return rows.length - 1;
		}
		
		public function SetRowTextColor(index:int,color:uint):void
		{
			if (rows[index] == null)
				return;
				
			rows[index].TextColor = color;	
		}
		
		public function set SelectedIndex(index:int):void
		{
			if (rows[index] == null)
				return;

			for each (var item:ComboBoxRow in rows) 
			{
				item.ShowSelectRectangle(false);
			}	
			
			selectedIndex = index;
			rowsContainer.selectedItem = index;
			txt.text = rows[index].Text;
			txt.textColor = rows[index].TextColor;
			rows[selectedIndex].ShowSelectRectangle(true);
		}
		
		public function get SelectedIndex():int
		{
			return selectedIndex;
		}
		
		public function ShowScrollBar(_isNeeded:Boolean):void
		{
			isScrollBarNeeded = _isNeeded;
		}
		
		protected function OnShowList(e:MouseEvent):void  //только открывает список, потому как переключение идёт наверху.
		{
			if (disable) return;
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_BIG);
			arrow_mc.OnUp(e);
			
			if(rows.length == 0)return;
			
			ListVisible(!rowsContainer.visible);
		}
	
		protected function ListVisible(show:Boolean):void
		{
			rowsContainer.visible = show;
			frame.visible = show;
			
			if (scrollBar != null)
				scrollBar.visible = show;
		}
		
		public function CloseDropList():void 
		{
			if (rowsContainer != null && rowsContainer.visible)
				OnShowList(null);
		}
		
		/* INTERFACE classes.Interfaces.IPWComponents */
		
		public function set Value(value:int):void
		{
			SelectedIndex = value;
		}
		
		public function set Disable(value:Boolean):void
		{
			disable = value;
			
			this.alpha = disable? 0.5:1;
			button_mc.mouseEnabled = !disable
		}
		
		protected function OnScrollClick(e:MouseEvent):void 
		{
			e.stopPropagation();
		}
		
		public function GetRows():Array
		{
			return rows;
		}
		
	}
}