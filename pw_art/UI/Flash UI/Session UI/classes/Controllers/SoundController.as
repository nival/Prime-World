package Controllers 
{
	import flash.media.Sound;
	import flash.utils.Dictionary;
	public class SoundController 
	{
		public static const BUTTON_CANCEL_SMALL:String = "Cancel_small";
		public static const BUTTON_PRESS_BIG:String = "Press_big";
		public static const BUTTON_PRESS_SMALL:String = "Press_small";
		public static const BUY_SOUND:String = "Buy_sound";
		public static const CHAT_SOUND:String = "Chat_sound";
		public static const ERROR_SOUND:String = "Error_Sound";
		public static const GET_SCROLL_SOUND:String = "Get_Scroll";
		public static const MINIMAP_ALERT:String = "Minimap_alert";
		public static const SELECTION:String = "Selection";
		public static const UI_CLOSE:String = "UI_close";
		public static const UI_OPEN_BIG:String = "Ui_open_big";
		public static const UI_OPEN_SMALL:String = "Ui_open_small";
		public static const MENU_OPEN:String = "menu_open";
		public static const NEW_LEVEL:String = "new_level";
		
		private static var buttonCancel_small:Sound;
		private static var buttonPress_big:Sound;
		private static var buttonPress_small:Sound;
		private static var buySound:Sound;
		private static var chatSound:Sound;
		private static var Error_Sound:Sound;
		private static var getScrollSound:Sound;
		private static var MinimapAlert:Sound;
		private static var Selection:Sound;
		private static var UIClose:Sound;
		private static var UIOpen_big:Sound;
		private static var UIOpen_small:Sound;
		private static var menu_openSound:Sound;
		private static var new_levelSound:Sound;
		
		private static var sounds:Dictionary = new Dictionary();

		
		public static function Init()
		{
			buttonCancel_small = new Button_cancel_small_sound();
			buttonPress_big = new Button_press_big_sound();
			buttonPress_small = new Button_press_small_sound();
			buySound = new Buy_sound();
			chatSound = new Chat_sound();
			Error_Sound = new Error_sound();
			getScrollSound = new GetScroll_sound();
			MinimapAlert = new MinimapAlert_sound();
			Selection = new Selection_sound();
			UIClose = new UiClose_sound();
			UIOpen_big = new UiOpen_big_sound();
			UIOpen_small = new UiOpen_small_sound();
			menu_openSound = new menu_open();
			new_levelSound = new new_level();
			
			buttonCancel_small["soundEvent"] = "buttonCancel_small";
			buttonPress_big["soundEvent"] = "buttonPress_big";
			buttonPress_small["soundEvent"] = "buttonPress_small";
			buySound["soundEvent"] = "buy";
			chatSound["soundEvent"] = "chat";
			Error_Sound["soundEvent"] = "error";
			getScrollSound["soundEvent"] = "getScroll";
			MinimapAlert["soundEvent"] = "minimap_alert";
			Selection["soundEvent"] = "Selection";
			UIClose["soundEvent"] = "UIClose";
			UIOpen_big["soundEvent"] = "UIOpen_big";
			UIOpen_small["soundEvent"] = "UIOpen_small";
			menu_openSound["soundEvent"] = "menu_open";
			new_levelSound["soundEvent"] = "NewLevel";
			
		
			sounds[BUTTON_CANCEL_SMALL] = buttonCancel_small;
			sounds[BUTTON_PRESS_BIG] = buttonPress_big;
			sounds[BUTTON_PRESS_SMALL] = buttonPress_small;
			sounds[BUY_SOUND] = buySound;
			sounds[CHAT_SOUND] = chatSound;
			sounds[ERROR_SOUND] = Error_Sound;
			sounds[GET_SCROLL_SOUND] = getScrollSound;
			sounds[MINIMAP_ALERT] = MinimapAlert;
			sounds[SELECTION] = Selection;
			sounds[UI_CLOSE] = UIClose;
			sounds[UI_OPEN_BIG] = UIOpen_big;
			sounds[UI_OPEN_SMALL] = UIOpen_small;
			sounds[MENU_OPEN] = menu_openSound;
			sounds[NEW_LEVEL] = new_levelSound;
		}
		
		public static function PlaySound(soundName:String):void
		{
			var sound:Sound = sounds[soundName];
			
			if (sound == null) return;
		
			sound.play();
		}
		
		
	}

}