package MainScreen 
{
	import BaseClasses.BaseResizableObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	public class Version extends BaseResizableObject
	{
		public var back:MovieClip;
		public var versionTxt:TextField;
		
		public function Version()
		{
			this.visible = false;
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			
			this.x = 0;
			this.y = stage.stageHeight - back.height * scale;
		}
		
		public function SetVersion(text:String):void
		{
			this.visible = true;
			versionTxt.text = text;
			back.width = versionTxt.textWidth;
		}
	}
}