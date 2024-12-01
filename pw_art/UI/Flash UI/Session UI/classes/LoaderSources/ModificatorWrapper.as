package LoaderSources 
{
	import BaseClasses.BaseResizableObject;
	import LoaderSources.Modificator;
	import flash.display.MovieClip;
	import flash.events.Event;
	public class ModificatorWrapper  extends BaseResizableObject
	{
		private var modificators:Array = new Array();
		private var offsetX:Number = 5;
		private var srartBottomOffset:Number;
		
		public function ModificatorWrapper()
		{
			srartBottomOffset = initialStage.y - this.y;
		}
		
		public function AddModeDescription(iconPath:String, id:int)
		{
			var newItem:Modificator = new Modificator();
			this.addChild(newItem);
			
			newItem.SetData(id, iconPath);
			modificators.push(newItem);
			
			
			ArrangeModificators();
		}
		
		private function ArrangeModificators():void 
		{
			var posX:Number = 0;
			
			for each (var item:Modificator in modificators) 
			{
				if (item == null) continue;
					
				item.x = posX;
				posX += item.width + offsetX;
			}
			
			BaseBarObjectResize();
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			super.BaseBarObjectResize();
			this.x = (stage.stageWidth - this.width) / 2 ;
			this.y = stage.stageHeight - srartBottomOffset * scale;		
		}
	}

}