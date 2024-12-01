package LoaderSources 
{
	import flash.events.Event;
	import flash.events.EventDispatcher;
	
	public class LoaderLocalization 
	{
		public static var CompleteEventDispatcher:EventDispatcher = new EventDispatcher();
	
		public static var BotName:String = "Бот";
		public static var ChatInputComboBox_EnterName:String = "Введите имя";
		public static var ChatBar_CantFindPlayer:String = "Сообщение не отправлено - игрок не найден";
		public static var TeamMateRaitingTooltip:String = "<br>Рейтинг героя"
		public  static var OurPlayerRaitingTooltip:String = "<br>Рейтинг героя<br>Победа: +{0}<br>Поражение: -{1}";
		public static var ExitButtonText:String = "Выход";
		public static var PremiumAccountTooltip:String = "В замке игрока {0} наступил Золотой Век!<br>В случае победы все игроки его команды получат дополнительный талант. В случае поражения только игрок {0} получит дополнительный талант"
		
		//ContextMenu
		public static var ContextMenu_AddFriend:String = "Добавить в друзья";
		public static var ContextMenu_Message:String = "Личное сообщение";
		public static var ContextMenu_Ignore:String = "Игнорировать";
		public static var ContextMenu_RemoveIgnore:String = "Простить";
		public static var ContextMenu_Complain:String = "Пожаловаться";
		
		static public var RestrictedChatSymbols:String = "";
		public static var PreferenceMenu_ReceiveRegularChatMessages:String = "Сообщения в чате сессии от других игроков";
		public static var Tooltip_PreferenceMenu_ReceiveRegularChatMessages:String = "Выключив эту опцию, вы перестанете получать обычные сообщения от других игроков в чате сесии.";
		
		// Chat messages
		public static var ChatMessage_Ignore:String = "Игрок {0} добавлен в список игнорируемых";
		public static var ChatMessage_RemoveIgnore:String = "Игрок {0} удалён из списка игнорируемых";
		
		public static function LocalizationComplete():void
		{	
			CompleteEventDispatcher.dispatchEvent(new Event(Event.COMPLETE));
		}
		
	}

}