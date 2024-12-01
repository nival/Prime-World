package Utils 
{
	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import flash.utils.getDefinitionByName;
	
	public class AnimatedPortraitsUtils 
	{		
		public static function ClearContainer(container:MovieClip):void
		{
			var childs:Array  = new Array();
			for (var i:int = 0; i < container.numChildren; i++) 
			{
				childs.push(container.getChildAt(i));
			}
			
			for each (var child:DisplayObject in childs) 
			{
				container.removeChild(child);
			}
		}
		
		public static function FindClassObject(path:String, isAnimatedAvatar:Boolean):Object
		{
			if (!isAnimatedAvatar)
			{
				return null;
			}
			
			var pathSplit:Array = path.split("/");
			var fileSplit:Array = (pathSplit[pathSplit.length - 1] as String).split(".");
			var className:String = (pathSplit[pathSplit.length - 2] as String) + (fileSplit[0] as String);
			
			//var className:String = "HighlanderFaceA";
			
			var classObject:Object = null;			
			try
			{
				classObject = getDefinitionByName(className);
			}
			catch (e:ReferenceError)
			{
                classObject = null;
            }
			
			return classObject;
		}	
	}
}