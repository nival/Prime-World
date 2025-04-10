package  {
	
	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	
	public class Main extends MovieClip {
		
		
		public function Main() 
		{
			//getChild(this);
		}
		function getChild(container:Object):void
		{
		var numChild:int = container.numChildren();
			for(var i:int =0 ; i<numChild; i++)
			{
				var child:Object = this.getChildAt(i);
				
				trace(child.name);
				if(child.numChildren>0)
				{
					getChild(child);
				}
				else
				{
					return;
				}
			}
		}
	}
}
