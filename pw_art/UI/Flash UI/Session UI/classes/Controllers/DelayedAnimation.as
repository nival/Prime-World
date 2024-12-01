package Controllers
{
	public class DelayedAnimation 
	{
		private var showAnimation:Function;
		private var closeAnimation:Function;
		private var iconPath:String;
		private var itemWasBought:Boolean;
		private var isClosedByKeyboard:Boolean;
		
		private var isShowIsTheLast:Boolean = true;
		
		private var callObject:Object = null;
		
		public function DelayedAnimation(_callObject:Object)
		{
			callObject = _callObject;
		}
		
		public function setShowAnimation(func:Function, path:String):void
		{
			isShowIsTheLast = true;
			
			closeAnimation = null;
			showAnimation = func;
			
			iconPath = path;
		}
		
		public function setCloseAnimation(func:Function, wasBought:Boolean,closedByKeyboard):void
		{
			isShowIsTheLast = false;
			
			closeAnimation = func;
			showAnimation = null;
			
			itemWasBought = wasBought;
			isClosedByKeyboard = closedByKeyboard;
			
		}
		
		public function PlayAnimation():void
		{
			var animation:Function = isShowIsTheLast? showAnimation: closeAnimation;
			
			ResetAnim();
						
			if (isShowIsTheLast)
			{
				animation.call(callObject, iconPath);
			}
			else 
			{
				animation.call(callObject, itemWasBought, isClosedByKeyboard);
			}
		}
		
		public function ResetAnim():void
		{
			showAnimation = null;
			closeAnimation = null;
		}
		
		public function get HasAnimation():Boolean
		{
			return showAnimation != null||closeAnimation != null;
		}
	}
}