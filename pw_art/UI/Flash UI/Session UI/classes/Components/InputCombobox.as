package Components 
{
	import Events.PWComponentValueEvent;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.text.TextFieldType;
	public class InputCombobox extends PWCombobox 
	{
		private var privateChannelColor:uint;
		private var autoFillRowsContainer:PWListContainer;//контейнер для строк автозаполнения.
		private var autoFillRows:Array = new Array();//Массив со строками
		private var autoFillscrollBar:ScrollBar;
		private var autoFillFrame:Frame;
		private var visibleList:Array = new Array()
		public function InputCombobox() 
		{
			txt.type = TextFieldType.INPUT;
			txt.addEventListener(KeyboardEvent.KEY_UP, OnTextInput);
		}
		
		public function ComboBoxColor(channelColor:uint):void 
		{
			privateChannelColor = channelColor;
			txt.textColor = channelColor;
			for each (var item:ComboBoxRow in rows) 
			{
				item.TextColor = privateChannelColor;
			}
			
			for each (var autoFillItem:ComboBoxRow in autoFillRows) 
			{
				autoFillItem.TextColor = privateChannelColor;
			}
		}
		
		override protected function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e); 
			txt.mouseEnabled = true;

			autoFillFrame = new Frame();
			autoFillFrame.y = button_mc.height;
			autoFillFrame.Image = 'frameChat_png';
			autoFillFrame.visible = false;
			
			addChild(autoFillFrame);
			
			autoFillRowsContainer = new PWListContainer();
			autoFillRowsContainer.y = rowsContainer.y;
			addChild(autoFillRowsContainer);
			autoFillRowsContainer.RowWidth(button_mc.width);
	
			autoFillRowsContainer.ScrollBarUp = MoveScrollBarUp;
			autoFillRowsContainer.ScrollBarDown = MoveScrollBarDown;
			
			autoFillRowsContainer.addEventListener(PWComponentValueEvent.CHANGE, OnAutoFillRowClick);
		}
	
		override protected function OnKeyDown(e:KeyboardEvent):void 
		{
			if (autoFillRowsContainer.visible) return;
			
			super.OnKeyDown(e);
		}
		
		private function OnTextInput(e:KeyboardEvent):void 
		{
			if (e.keyCode == 13)
				return;
			
			ListVisible(false);
			
			autoFillFrame.visible = true;
			autoFillRowsContainer.visible = true;
			
			if (autoFillscrollBar!=null && autoFillscrollBar.Enabled)
				autoFillscrollBar.visible = true;
				
			if (e.keyCode == 40)
			{
				autoFillRowsContainer.MoveSelectDown();
				return;
			}
			if (e.keyCode == 38)
			{
				autoFillRowsContainer.MoveSelectUp();	
				return;
			}
			
			UpdateAutoFillVisualisation();
		}
		
		
		
		private function UpdateAutoFillVisualisation():void 
		{
			visibleList = new Array();
			
			for each (var item:ComboBoxRow in autoFillRows) 
			{
				if (item.Text.indexOf(txt.text)==0 || txt.text.length == 0 ||(item.Text.indexOf(txt.text)!=0 && item.ID==0))
					visibleList.push(item);
					
				if (visibleList.length == autoFillRowsContainer.MaxRowCount)
					break;
			}

			autoFillRowsContainer.SetVisibleItems(visibleList);	
			
			if (autoFillscrollBar != null)
			{
				autoFillscrollBar.RecalcContentHeight();
				autoFillscrollBar.ResetToStartPosition();
				autoFillscrollBar.visible = autoFillRowsContainer.ActualHeight <= autoFillRowsContainer.ScrollableHeight && autoFillRowsContainer.visible;
				autoFillRowsContainer.RowWidth(button_mc.width - (autoFillscrollBar.visible ?  scrollBarWidth : 0));
			}
			
			if (autoFillRowsContainer.ActualHeight <= autoFillRowsContainer.ScrollableHeight)
				autoFillFrame.setSize(button_mc.width - scrollBarWidth , autoFillRowsContainer.ActualHeight);
			else
				autoFillFrame.setSize(button_mc.width, autoFillRowsContainer.ScrollableHeight);
			
		}
		
		public function MoveScrollBarDown():void
		{
			if (autoFillscrollBar == null || !autoFillscrollBar.visible) return;
			autoFillscrollBar.ScrollDown(null);
		}
		
		public function MoveScrollBarUp():void
		{
			if (autoFillscrollBar == null || !autoFillscrollBar.visible) return;
			autoFillscrollBar.ScrollUp(null);
		}
		
		override public function set SelectedIndex(value:int):void 
		{
			if (rows[value] == null) return;
				
			super.SelectedIndex = value;
			
			if (value == 0)
				txt.text = "";
				
			stage.focus = txt;
		}
		
		override public function AddComboBoxRow(value:String):int 
		{
			var index:int = super.AddComboBoxRow(value);
			
			ComboBoxColor(privateChannelColor);
			return index;
		}
		
		public function AddAutoFillRow(value:String):void 
		{
			if (value == "") return;
			
			var row:ComboBoxRow = new ComboBoxRow();
			row.Text = value;
			row.ComponentName = this.name;			
			row.TextColor = privateChannelColor;
			autoFillRowsContainer.AddElement(row);
			autoFillRows.push(row);
			
			if(autoFillRowsContainer.ActualHeight < autoFillRowsContainer.ScrollableHeight)
			{
				autoFillRowsContainer.RowWidth(button_mc.width - scrollBarWidth)
				
				autoFillFrame.setSize(button_mc.width - scrollBarWidth, autoFillRowsContainer.ActualHeight);

				if (autoFillscrollBar == null)
				{
					autoFillscrollBar = new ScrollBar();
					autoFillscrollBar.addEventListener('SCROLL_INIT', scrollInit);					
				}
			}
			else
			{
				autoFillFrame.setSize(button_mc.width, autoFillRowsContainer.ScrollableHeight);	
			}
			
			if (autoFillscrollBar != null)
			{
				autoFillscrollBar.RecalcContentHeight();
				autoFillscrollBar.visible = autoFillRowsContainer.visible;
			}
		}
		private function scrollInit(e:Event):void
		{
			autoFillscrollBar.SetScrollableContent(autoFillRowsContainer);
			autoFillscrollBar.addEventListener(MouseEvent.CLICK, OnScrollClick);
			this.addChild(autoFillscrollBar);
		}
		
		private function OnAutoFillRowClick(e:PWComponentValueEvent):void 
		{
			e.stopPropagation();
			SetAutoFillSelectedItem(e.componentValue);
		}
		
		public function SetAutoFillSelectedItem(index:int):void
		{
			CloseDropList();
			
			if(autoFillRows[index]!=null)
				txt.text = autoFillRows[index].Text;
				
			if (index == 0)
				txt.text = "";
				
			UpdateAutoFillVisualisation();	
		}
		
		
		override public function CloseDropList():void 
		{
			super.CloseDropList();
			CloseAutoFillList();
		}
		
		public function AutoFillSelectin():Boolean 
		{
			return autoFillRowsContainer.selectedItem != -1;
		}
		
		private function CloseAutoFillList():void
		{
			autoFillFrame.visible = false;
			autoFillRowsContainer.visible = false;
			
			if (autoFillscrollBar!=null)
				autoFillscrollBar.visible = false;
				
			UpdateAutoFillVisualisation();	
		}
		
		
		override protected function OnShowList(e:MouseEvent):void 
		{
			super.OnShowList(e);
			
			if (rowsContainer.visible)
				CloseAutoFillList();
		}
		
		public function EnterPressed():void
		{
			if (autoFillRowsContainer.selectedItem == -1) return;
			
			SetAutoFillSelectedItem(visibleList[autoFillRowsContainer.selectedItem].ID);
		}
		
		override protected function OnStageClick(e:MouseEvent):void 
		{
			super.OnStageClick(e);
			
			CloseAutoFillList();
		}
	}

}