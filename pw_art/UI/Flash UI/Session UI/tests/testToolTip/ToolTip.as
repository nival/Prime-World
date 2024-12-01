package 
{

	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFieldAutoSize;
	import flash.display.DisplayObject;
	import flash.display.Stage;
	import src.ButtonTooltipEvent;
	import flash.display.DisplayObjectContainer;

	public class ToolTip extends Sprite
	{
		private var toolTip_txt:TextField;

		public  var tooltip:String = '';
		private var X:Number = 0;
		private var Y:Number = 0;
		//здесь объект myFrame и его свойства доступны, потому что этот объект - ToolTip создается уже после того, как все объекты добавлены на стейдж
		private var frameTooltip:Frame;
		private var main:DisplayObjectContainer;
		
		public var target:DisplayObject;

		public function ToolTip(_main:Main)
		{
			main = _main;
			this.visible = false;
			this.mouseEnabled = false;
			this.mouseChildren = false;

			//из-за нашей "великолепной" сборки, не могу просто создать обычный объект из класса и вставить его сюда а просто вытаскиваю его из библиотеки,
			//потому что он доступен отовсюду." - LoL by Alexander Kosulin =)

			frameTooltip = new Frame(true) ;
			this.addChild(frameTooltip);

			toolTip_txt = new TextField  ;
			
			//apply font
			var textFormat:TextFormat= new TextFormat();
			textFormat.size = 20;
			
			toolTip_txt.defaultTextFormat = textFormat;
			
			//отступ 5 pix
			toolTip_txt.x = 5;
			toolTip_txt.y = 5;
			//дефолтовые настройки
			toolTip_txt.width = 15;
			toolTip_txt.height = 15;
			
			toolTip_txt.textColor = 0xffffff;
			toolTip_txt.selectable = false;
			toolTip_txt.autoSize = TextFieldAutoSize.LEFT;
			this.addChild(toolTip_txt);

			frameTooltip.setSize(25,25);
		}
		public function tooltipHandler(e:ButtonTooltipEvent):void
		{
			
			tooltip = e.tooltip;
			
			if (e.x != -1 && e.y != -1)
			{
				X = e.x;
				Y = e.y;
			}
			
			target = e.target as DisplayObject;
			
			switch (e.action)
			{
				case ButtonTooltipEvent.ACTION_TYPE_IN :
					{
						ShowTooltip();
						break;
					};

				case ButtonTooltipEvent.ACTION_TYPE_OUT :
					{
						HideTooltip();
						break;
					};
				default :
					trace('bad ButtonTooltipEvent');
			}
		}

		public function ShowTooltip():void
		{
			if (tooltip == '')
			{
				return;
			}
			//настроил на глаз расположение тултипа относительно поинта объекта			

			if (tooltip == toolTip_txt.text)
			{
				showTooltip();
				return;
			}

			toolTip_txt.text = tooltip;
			
			toolTip_txt.width = 400;

			if (toolTip_txt.width > 100)
			{
				//если строка слишком длинная, то жестко прописываем width это предотвращает автосайз по width,
				//соответственно переносим по словам
				toolTip_txt.wordWrap = true;
				toolTip_txt.width = 100;
			}
			else if (toolTip_txt.width < 25)
			{
				//если текст по ширине меньше чем 25(поскольку мы не можем сделать рамку меньше, мы должны его просто выровнить по центру)
				frameTooltip.setSize(25,toolTip_txt.height+8);

				toolTip_txt.x = (frameTooltip.width - toolTip_txt.width)/2;
				toolTip_txt.y = (frameTooltip.height - toolTip_txt.height)/2;
			}
			else
			{
				//иначе возвращаем автосайз
				toolTip_txt.autoSize = TextFieldAutoSize.LEFT;
				toolTip_txt.wordWrap = false;
			}

		
			if (toolTip_txt.height < 25)
			{
				frameTooltip.setSize(toolTip_txt.width+8,25);

				toolTip_txt.x = (frameTooltip.width - toolTip_txt.width)/2;
				toolTip_txt.y = (frameTooltip.height - toolTip_txt.height)/2;
			}
			else
			{
				//8 - потому что 5 отступ + 5-2 это скидка на толщину рамки
				frameTooltip.setSize(toolTip_txt.width+8,toolTip_txt.height+8);
			}
			
			showTooltip();
			
		}
		function showTooltip():void
		{
			/*
			if(X + target.width + this.width>=main.stage.stageWidth)
			{
				if(Y + target.height + this.height>=main.stage.stageHeight)
				{
					this.y = Y - this.height;
				}
				else
				{
					this.y = Y + target.height;
				}
				this.x = main.stage.stageWidth - this.width;
			}
			else if(Y + target.height + this.height>=main.stage.stageHeight)
			{
				this.x = X + target.width;
				this.y = main.stage.stageHeight - this.height;
			}
			else
			{
				this.x = X + target.width;
				this.y = Y + 5;
			}*/
			
			this.x  = 0;
			this.y 	= 0;
			main.setChildIndex(this,main.numChildren - 1);
			this.visible = true;
		}			

		private function HideTooltip():void
		{
			this.visible = false;
		}
	}
}