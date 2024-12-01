package Controllers
{
	import Events.ShowDialogEvent;
	import flash.display.MovieClip;
	import flash.events.EventDispatcher;
	import Events.WindowVisibleControllerEvent;
	import BaseClasses.BaseDragObject;
	import Enums.EWindows;
	public class WinVisabilityController
	{
		private var windows:Array;
		private var buttons:Array;
		private var nonClickableMovieclip:MovieClip;
		private var isWindowSticked:Boolean = false;
		private var mousePosition:Number = -1;
		private const STICK_GAP_SIZE:int = 14;
		private var isFinalAnimationWasShowed:Boolean = false;
		
		private var DELETE_STICKING_LISTENER:Boolean = true;
		private var isEscMenuShowing:Boolean = false;
		private var isHideAllWindows:Boolean;
		private var mainSceen:MovieClip;
		private var isTalentSetCanBeShowed:Boolean = true;
		
		public function WinVisabilityController(winArr:Array, butArr:Array, _mainSceen:MovieClip)
		{
			mainSceen = _mainSceen;
			mainSceen.addEventListener(WindowVisibleControllerEvent.OPEN_CLOSE, WindowEventHandler);
			mainSceen.addEventListener(WindowVisibleControllerEvent.OPEN, OpenWindow);
			mainSceen.addEventListener(ShowDialogEvent.EVENT_TYPE, ShowDialog);
			
			if (!DELETE_STICKING_LISTENER)
			{
				mainSceen.addEventListener(WindowVisibleControllerEvent.WINDOW_MOVING, WindowMoving);
				winArr[EWindows.WINDOW_INVENTORYBAR].StickWindow = winArr[EWindows.WINDOW_SHOPBAR];
			}
			
			winArr[EWindows.WINDOW_SHOPBAR].x = winArr[EWindows.WINDOW_INVENTORYBAR].x - winArr[EWindows.WINDOW_SHOPBAR].windowWidth;
			
			buttons = butArr;
			windows = winArr;
		}
		
		public function set NonClickableMov(clip:MovieClip):void
		{
			nonClickableMovieclip = clip;
		}
		
		private function OpenWindow(e:WindowVisibleControllerEvent):void 
		{
			e.stopPropagation();
			ShowSomeWindow(e.id);
		}
		
		private function WindowEventHandler(e:WindowVisibleControllerEvent):void
		{
			SwitchWindowState(e.id);
		}
		
		public function IsWindowVisible(winId:int):Boolean
		{
			if (windows[winId] == null) return false;
			
			return windows[winId].visible;
		}
		
		public function SwitchWindowState(winId:int):void
		{
			if (windows[winId] == null) return;
			
			if (windows[winId].visible)
				HideSomeWindow(winId)
			else
				ShowSomeWindow(winId);
		}
		
		public function HideSomeWindow(winId:int):void
		{			
			if (windows[winId] == null) return;
		
			if (!isHideAllWindows && windows[winId].visible)
				SoundController.PlaySound(SoundController.UI_CLOSE);
			
			windows[winId].visible = false;
			
			if (buttons[winId] != null)
				buttons[winId].setOffState();
			
				
			switch (winId) 
			{
				case EWindows.WINDOW_OPTIONSBAR :
					if (isEscMenuShowing)
					{
						windows[EWindows.WINDOW_ESCMENUBAR].visible = true;
						FSCommands.Send(FSCommands.PREFERENCE_COMPONENT_CANCEL);
					}
					break;
				case EWindows.WINDOW_ESCMENUBAR:
					FSCommands.Send(FSCommands.ESCMENU_CONTINUE);
					isEscMenuShowing = false;
					EscapeMenuShowing(winId);
					break;
				case EWindows.WINDOW_INVENTORYBAR:
					if (windows[EWindows.WINDOW_SHOPBAR].visible)
						HideSomeWindow(EWindows.WINDOW_SHOPBAR);
					break;
				case EWindows.WINDOW_SHOPBAR:
					windows[EWindows.WINDOW_SHOPBAR].EndDragItem();
					windows[EWindows.WINDOW_SHOPBAR].HideTooltip();
					FSCommands.Send(FSCommands.SHOP_CLOSED, '');
					break;
				case EWindows.WINDOW_MESSAGEBOX :
					if (isEscMenuShowing)
						mainSceen.setChildIndex(windows[EWindows.WINDOW_ESCMENUBAR], mainSceen.numChildren - 1);
					else
						nonClickableMovieclip.visible = false;
					break;
				case EWindows.WINDOW_REPORT:
					FSCommands.Send(FSCommands.REPORT_WINDOW_OPENED, FSCommands.DISABLE);
			}	
		}
		
		private function ShowDialog(e:ShowDialogEvent):void 
		{
			windows[EWindows.WINDOW_MESSAGEBOX].PrepareDialog( e.dialogHeader, e.dialogText, e.OnYesFunction, e.OnNoFunction, e.OkDialog);
			ShowSomeWindow(EWindows.WINDOW_MESSAGEBOX);
		}
		
		public function ShowSomeWindow(winId:int):void
		{
			if (windows[winId] == null) return;

			if (isFinalAnimationWasShowed && winId!=EWindows.WINDOW_SELECTIONCHARSTAT && winId!=EWindows.WINDOW_SELECTIONTALANTBAR && winId!=EWindows.WINDOW_REPORT && winId!=EWindows.WINDOW_MESSAGEBOX) return;
			
			if (isEscMenuShowing&&winId!=EWindows.WINDOW_OPTIONSBAR&&winId!=EWindows.WINDOW_MESSAGEBOX) return;
			
			if (winId == EWindows.WINDOW_TALENTSBAR && !isTalentSetCanBeShowed) return;
			
			PlayOpenSound(winId);
			
			windows[winId].visible = true;
			mainSceen.setChildIndex(windows[winId], mainSceen.numChildren - 1);
			
			windows[winId].SetOnStartPosition();
			
			switch(winId) 
			{
				case EWindows.WINDOW_OPTIONSBAR : 
					windows[EWindows.WINDOW_ESCMENUBAR].visible = false;
					break;
				case EWindows.WINDOW_ESCMENUBAR :
					FSCommands.Send(FSCommands.ESCMENU_SHOW);
					isEscMenuShowing = true;
					EscapeMenuShowing(winId);
					break;
				case EWindows.WINDOW_SHOPBAR :
					if (!windows[EWindows.WINDOW_INVENTORYBAR].visible)
						ShowSomeWindow(EWindows.WINDOW_INVENTORYBAR);
					break;
				case EWindows.WINDOW_MESSAGEBOX : 
					nonClickableMovieclip.alpha = 0;
					mainSceen.setChildIndex(nonClickableMovieclip, mainSceen.numChildren - 2);
					nonClickableMovieclip.visible = true;
					break;
			}	
			
			if (buttons[winId] != null)
				buttons[winId].setOnState();	
		}
		
		private function PlayOpenSound(winId:int):void 
		{
			if (isHideAllWindows) return;
			if (windows[winId].visible) return;
			if (winId == EWindows.WINDOW_ESCMENUBAR || winId == EWindows.WINDOW_OPTIONSBAR)
				SoundController.PlaySound(SoundController.UI_OPEN_SMALL)
			else
				SoundController.PlaySound(SoundController.UI_OPEN_BIG);
				
		}
		
		private function EscapeMenuShowing(winId):void
		{
			nonClickableMovieclip.alpha = 0;
			mainSceen.setChildIndex(nonClickableMovieclip, mainSceen.numChildren - 2);
			nonClickableMovieclip.visible = windows[winId].visible;
			
			if (windows[winId].visible)
				FSCommands.Send(FSCommands.ESCMENU_DISABLEHOTKEYS, FSCommands.ENABLE);
			else 
				FSCommands.Send(FSCommands.ESCMENU_DISABLEHOTKEYS, FSCommands.DISABLE); 
			
			if (!windows[winId].isPlayingMiniGame) 
				return;
			
			if (windows[winId].visible)
				FSCommands.Send(FSCommands.MINIGAMEMENU_OPENED);
			else 
				FSCommands.Send(FSCommands.MINIGAMEMENU_CLOSED); 
			
		}	
		
		public function get CloseButtonTooltip():String
		{
			return windows[0].CloseButtonTooltip;
		}
		
		public function set CloseButtonTooltip(value:String):void
		{
			for each (var window:MovieClip in windows)
			{
				if (window != null)
					window.CloseButtonTooltip = value;
			}
		}
				
		
		public function WindowMoving(e:WindowVisibleControllerEvent):void
		{
			var draggedWindow:BaseDragObject = windows[e.id];		
			var minimalGap:int = int.MAX_VALUE;
			var closerWindow:BaseDragObject = null;
		
			if (draggedWindow.isWindowStick)
			{	if (Math.abs(Math.abs(draggedWindow.mouseX)-Math.abs(draggedWindow.startDragPosition)) > STICK_GAP_SIZE)
				{
					draggedWindow.isWindowStick = false;
					//move window for delta
					draggedWindow.RestartStickDrag(false);
					draggedWindow.StickWindow=null;
					draggedWindow.x = draggedWindow.x + Math.abs(draggedWindow.mouseX) - Math.abs(draggedWindow.startDragPosition);
					
					return;
				}
			}
			
			//find the closest window
			for (var i:int = 0; i < windows.length;i++)
			{
				if (windows[i] == null || windows[i].visible == false) continue;
					
				if (i == e.id || i == EWindows.WINDOW_ESCMENUBAR) continue;
				
				var newGap:Number = GetGapBetweenWindows(draggedWindow, windows[i]);

				if (newGap == -1) continue;
							
				if (minimalGap >= newGap)
				{
					minimalGap = newGap;
					closerWindow = windows[i];
				}
			}
			
			if (closerWindow == null ||minimalGap >STICK_GAP_SIZE)
			{
				draggedWindow.StickWindow=null;
				return;
			}
			
			var draggedIsLeft : Boolean = draggedWindow.x < closerWindow.x;
			var offsetFromClosest:int = draggedIsLeft? ( -draggedWindow.windowWidth-1 ) : closerWindow.windowWidth;
			
			draggedWindow.x = closerWindow.x + offsetFromClosest;
			
			draggedWindow.isWindowStick = true;
			draggedWindow.StickWindow=closerWindow;
			draggedWindow.RestartStickDrag(true);			
		} 
		
		public function GetGapBetweenWindows(dragged:BaseDragObject, window:BaseDragObject):int
		{
			var gap:int=-1;
			
			if (dragged.x + dragged.windowWidth <= window.x+5)
			{
				gap = Math.abs(window.x - dragged.windowWidth - dragged.x);
				
			}
			
			if (window.x + window.windowWidth <= dragged.x+5)
			{
				gap= Math.abs(dragged.x - window.windowWidth - window.x);
			}
			
			
			return gap;
		}
		
		public function ShowFinalAnimation():void
		{
			isFinalAnimationWasShowed = true;
			for (var i:int = 0; i < windows.length; i++)
			{
				if (windows[i] != null && windows[i].visible)
					windows[i].AnimationClosing();
			}
		}
		
		public function HideAllWindows():void 
		{
			isHideAllWindows = true;
			
			for (var i:int = 0; i < EWindows.WINDOWS_COUNT; i++)
			{
				HideSomeWindow(i);
			}
			
			isHideAllWindows = false;
		}
		
		public function ShowTalentsSet(show:Boolean):void 
		{
			isTalentSetCanBeShowed = show;
		}
	}
}