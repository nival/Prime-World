package 
{
	import flash.events.Event;
	import flash.events.EventDispatcher;

	public class Localization
	{
		public static var CompleteEventDispatcher:EventDispatcher = new EventDispatcher();
		
		//TalantsBar
		public static var TalantsBar_HeaderText:String = "Таланты";
		//CharStat
		public static var CharStatBar_HeaderText:String = "Герой";
		public static var CharStarBar_LifeText:String = "Здоровье:";
		public static var CharStarBar_EnergyText:String = "Энергия:";
		public static var CharStarBar_StrengthText:String = "Сила:";
		public static var CharStarBar_IntellectText:String = "Разум:";
		public static var CharStarBar_AttackSpeedText:String = "Проворство:";
		public static var CharStarBar_DexterityText:String = "Хитрость:";
		public static var CharStarBar_StaminaText:String = "Стойкость:";
		public static var CharStarBar_WillText:String = "Воля:";
		public static var CharStarBar_MoveSpeedText:String = "Скорость";
		public static var CharStarBar_DamageText:String = "Урон:";
		public static var CharStarBar_AttackPerSecondText:String = "Атак в секунду:";
		public static var CharStarBar_CritChanseText:String = "Шанс крита:";
		public static var CharStarBar_CritMissText:String = "Пробивание:";
		public static var CharStarBar_BodyDefenceText:String = "Защита тела:";
		public static var CharStarBar_SpiritDefenceText:String = "Защита духа:";
		public static var CharStarBar_LevelLabelText:String = "Уровень";
		public static var CharStatBar_ThisIsImportantStat:String = "Данная характеристика важна для этого героя";
		public static var CharStarBar_RaitingLabelText:String = "Рейтинг";
		public static var CharStarBar_LeaguePlaceLabelText:String = "Место";
		
		//InventoryBar
		public static var InventoryBar_HeaderText:String = "Инвентарь";
		
		//ShopBar
		public static var ShopBar_HeaderText:String = "Магазин";
		
		//StatisticBar
		public static var StatisticBar_HeaderText:String = "Статистика боя";
		public static var StatisticBar_CloseBtnLabel:String = "Закрыть";
		
		//EscMenu
		public static var EscMenuBar_HeaderText:String = "Меню";
		public static var EscMenuBar_ContinueBtnLabel:String = "Продолжить";
		public static var EscMenuBar_SurrenderBtnLabel:String = "Сдаться";
		public static var EscMenuBar_OptionsBtnLabel:String = "Настройки";
		public static var EscMenuBar_RunToCityBtnLabel:String = "Сбежать в город";
		public static var EscMenuBar_ExitBtnLabel:String = "Выход";
		public static var EscMenuBar_StopLevelBtnLabel:String = "Прервать уровень";
		public static var EscMenuBar_SkipBtnLabel:String = "Пропустить обучение";
	
		
		//FinalStatisticBar
		public static var FinalStatisticBar_HeaderText:String = "Статистика";
		public static var FinalStatisticBar_CloseBtnLabel:String = "Закрыть";
		public static var FinalStatisticBar_OpenDetailedStatisticBtnLabel:String = "Детально";
		public static var FinalStatisticBar_OpenStatisticBtnLabel:String = "Статистика";
		public static var FinalStatisticBar_ReturnToStatisticBtnLabel:String = "Назад"; // UNUSED
		public static var FinalStatisticBar_PartyLabel:String = "Желаете продолжить игру с теми же союзниками?";
		public static var FinalStatisticBar_PartyButtonYes:String = "Да";
		public static var FinalStatisticBar_PartyButtonNo:String = "Нет";
		
		//DetailedStatisticBar
		public static var DetailedStatisticBar_AchivmentsHeaderText:String = "Достижения";
		public static var DetailedStatisticBar_ResultsHeaderText:String = "Результаты";
		
		
		//PersonalStatisticBar
		public static var PersonalStatisticBar_AchivmentsHeaderText:String = "Достижения";
		public static var PersonalStatisticBar_AwardsHeaderText:String = "Награды";
		public static var PersonalStatisticBar_AwardsWaiting:String = "Идет получение наград. Пожалйста, подождите...";
		
		//Defeate
		public static var DefeatScreen_DefeatText:String = "Поражение";
		public static var EndGameScreens_CloseBtnLabel:String = "Продолжить";
		
		//Victory
		public static var VictoryScreen_VictoryText:String = "Победа";
		
		//Tooltips-----------------------------------
		public static var Tooltip_AllWindowsCloseBtn:String  = "Закрыть окно";
		public static var Tooltip_OpenTeamBtn:String  	 = "Показать команду";
		public static var Tooltip_CloseTeam:String  	 = "Скрыть команду";
		
		public static var Tooltip_MinimapTimer:String = "Время игры";
		public static var Tooltip_MinimapCameraBtn:String  = "Привязать камеру";
		public static var Tooltip_MinimapToggledCameraBtn:String = "Отвязать камеру";
		public static var Tooltip_MinimapSignalBtn:String  = "Послать сигнал";
				
		public static var Tooltip_ActionBarTalentWindowOn:String = "Таланты (T)";
		public static var Tooltip_ActionBarTalentWindowOff:String = "Таланты (T)";
		
		public static var Tooltip_ActionBarCharStatWindowOn:String = "Герой (C)";
		public static var Tooltip_ActionBarCharStatWindowOff:String = "Герой (C)";

		public static var Tooltip_ActionBarInventoryWindowOn:String = "Инвентарь (B)";
		public static var Tooltip_ActionBarInventoryWindowOff:String = "Инвентарь (B)";
		
		public static var Tooltip_LockActionBarBtnUp:String  = "Закрепить таланты";
		public static var Tooltip_LockActionBarBtnDown:String  = "Открепить таланты";
		
		public static var Tooltip_ActionBarCuestLogWindowOn:String = "";
		public static var Tooltip_ActionBarCuestLogWindowOff:String = "";
		
		public static var Tooltip_ActionBarSocialBarWindowOn:String = "";
		public static var Tooltip_ActionBarSocialBarWindowOff:String = "";
		
		public static var Tooltip_ActionBarStatisticBarWindowOn:String = "Статистика (Tab)";
		public static var Tooltip_ActionBarStatisticBarWindowOff:String = "Cтатистика (Tab)";
		
		public static var Tooltip_ActionBarEscMenuWindowOn:String = "Меню (Esc)";
		public static var Tooltip_ActionBarEscMenuWindowOff:String = "";
		
		public static var Tooltip_StatisticBarKillsIcon:String   = "Убийства";
		public static var Tooltip_StatisticBarDeathsIcon:String  = "Смерти";
		public static var Tooltip_StatisticBarAssistIcon:String  ="Поддержки"
		public static var Tooltip_StatisticBarScoreIcon:String   = "Очки"
		
		public static var Tooltip_InventoryBarSortBtn:String  	= "Сортировать";
		public static var Tooltip_InventoryBarSplitBtn:String  = "Разделить";
		
		public static var Tooltip_NaftaBtn:String  = "Таланты (T)";
		
		public static var Tooltip_StatBarPrevExperience:String  = "Опыт на начало сессии:";
		public static var Tooltip_StatBarEarnedExperience:String  = "Заработанный опыт:";
		public static var Tooltip_StatBarEarnedByCourageExperience:String  = "Опыт от Бодрости:";
		public static var Tooltip_StatBarLeftExperience:String  = "Оставшийся опыт до получения следующего уровня:";
		
		public static var Tooltip_PreferenceMenu_ReceiveRegularChatMessages:String = "Выключив эту опцию, вы перестанете получать обычные сообщения от других игроков в чате сесии.";
		
		public static var Tooltip_FinalStatisticBar_PartyMarker:String = "Игрок согласился продолжить игру в том же составе";
		public static var Tooltip_FinalStatisticBar_Mute:String = "Игрок не может писать в чат";
		
		//ContextMenu
		public static var ContextMenu_Watch:String = "Следить";
		public static var ContextMenu_Follow:String = "Следовать за";
		public static var ContextMenu_Character:String = "Характеристики";
		public static var ContextMenu_Talents:String = "Таланты";
		public static var ContextMenu_AddFriend:String = "Добавить в друзья";
		public static var ContextMenu_Message:String = "Личное сообщение";
		public static var ContextMenu_Ignore:String = "Игнорировать";
		public static var ContextMenu_RemoveIgnore:String = "Простить";
		public static var ContextMenu_StartSpectate:String = "Следить";
		public static var ContextMenu_Complain:String = "Пожаловаться";
		public static var ContextMenu_Leave:String = "Сбежать";

		//Preferences
		public static var PreferenceMenu_Header:String = "Настройки";
		public static var PreferenceMenu_GraphicLable:String = "Графика";
		public static var PreferenceMenu_ResolutionLabel:String = "Разрешение экрана";
		public static var PreferenceMenu_GraphicQualityLabel:String = "Качество графики";
		public static var PreferenceMenu_WindowModeLabel:String = "Оконный режим";
		public static var PreferenceMenu_Warning:String = "Внимание: изменения в Замке вступят в силу после перезапуска игры.";
		public static var PreferenceMenu_AcceptBtn:String = "Подтвердить";
		public static var PreferenceMenu_CancelBtn:String = "Отменить";
		public static var PreferenceMenu_SoundLabel:String = "Звук";
		public static var PreferenceMenu_SoundVolumeLabel:String = "Громкость звуков";
		public static var PreferenceMenu_MusicVolumeLabel:String = "Громкость музыки";
		public static var PreferenceMenu_VoiceVolumeLabel:String = "Громкость голоса";
		public static var PreferenceMenu_GameLabel:String = "Игра";
		public static var PreferenceMenu_LeftClickLabel:String = "Передвижение по левому клику";
		public static var PreferenceMenu_UseBadWordsFilter:String = "Использовать мат-фильтр";
		public static var PreferenceMenu_CloseBtn:String = "Закрыть";
		public static var PreferenceMenu_CommonVolume:String = "Общая громкость";
		public static var PreferenceMenu_ReceiveRegularChatMessages:String = "Сообщения в чате сессии от других игроков";
		
		//Shortcuts
		public static var ShortcutsMenu_Header:String = "Клавиши";
		public static var ShortcutsMenu_ActionBarHeader:String = "Ячейки талантов";
		public static var ShortcutsMenu_ActionBarSlot1:String = "Ячейка 1";
		public static var ShortcutsMenu_ActionBarSlot2:String = "Ячейка 2";
		public static var ShortcutsMenu_ActionBarSlot3:String = "Ячейка 3";
		public static var ShortcutsMenu_ActionBarSlot4:String = "Ячейка 4";
		public static var ShortcutsMenu_ActionBarSlot5:String = "Ячейка 5";
		public static var ShortcutsMenu_ActionBarSlot6:String = "Ячейка 6";
		public static var ShortcutsMenu_ActionBarSlot7:String = "Ячейка 7";
		public static var ShortcutsMenu_ActionBarSlot8:String = "Ячейка 8";
		public static var ShortcutsMenu_ActionBarSlot9:String = "Ячейка 9";
		public static var ShortcutsMenu_ActionBarSlot10:String = "Ячейка 10";
		public static var ShortcutsMenu_SelfCast:String = "Использовать на себя";
		public static var ShortcutsMenu_Portal:String = "Портал";
		public static var ShortcutsMenu_ActionBarLockOff:String = "Временно разблокировать ячейки";
		
		public static var ShortcutsMenu_GameActionHeader:String = "Бой";
		public static var ShortcutsMenu_Move:String = "Двигаться без атаки";
		public static var ShortcutsMenu_Attack:String = "Атаковать";
		public static var ShortcutsMenu_Hold:String = "Остановиться";
		public static var ShortcutsMenu_ToggleHealthbars:String = "Показать/скрыть здоровье солдат";
		
		public static var ShortcutsMenu_SmartCharHeader:String = "Быстрые сообщения";
		public static var ShortcutsMenu_OpenSmartChat:String = "Вызов меню";
		public static var ShortcutsMenu_SmartChat1:String = "Враг покинул линию";
		public static var ShortcutsMenu_SmartChat2:String = "Враг вернулся";
		public static var ShortcutsMenu_SmartChat3:String = "Нужна помощь";
		public static var ShortcutsMenu_SmartChat4:String = "Нужен фонарь";
		public static var ShortcutsMenu_SmartChat5:String = "Собираемся вместе";
		public static var ShortcutsMenu_SmartChat6:String = "Нужен свиток";
		public static var ShortcutsMenu_SmartChat7:String = "Все молодцы";
		
		public static var ShortcutsMenu_WindowsHeader:String = "Окна в бою";
		public static var ShortcutsMenu_OpenChat:String = "Открыть/закрыть чат";
		public static var ShortcutsMenu_OpenGlobalChat:String = "Открыть общий чат";
		public static var ShortcutsMenu_OpenTeamChat:String = "Открыть час команды";
		public static var ShortcutsMenu_ShowStatistics:String = "Статистика";
		public static var ShortcutsMenu_ShowCharStats:String = "Герой";
		public static var ShortcutsMenu_ShowInventory:String = "Инвентарь";
		public static var ShortcutsMenu_ShowTalents:String = "Таланты";
		
		public static var ShortcutsMenu_CameraHeader:String = "Камера в бою";
		public static var ShortcutsMenu_HeroCenter:String = "Центрировать на герое";
		public static var ShortcutsMenu_CameraUp:String = "Вверх";
		public static var ShortcutsMenu_CameraDown:String = "Вниз";
		public static var ShortcutsMenu_CameraLeft:String = "Влево";
		public static var ShortcutsMenu_CameraRight:String = "Вправо";
		public static var ShortcutsMenu_CameraRotateLeft:String = "Повернуть влево";
		public static var ShortcutsMenu_CameraRotateRight:String = "Повернуть вправо";
		
		//VoteMenu
		public static var VoteMenu_YesLabel:String = "Вы голосовали ЗА";
		public static var VoteMenu_NoLabel:String = "Вы голосовали ПРОТИВ";
		public static var VoteMenu_YesButton:String = "За";
		public static var VoteMenu_NoButton:String = "Против";
		public static var VoteMenu_SurrenderText:String = "Сдаться?";

		//MessageBox
		public static var MessageBox_Header:String = "Выход";
		public static var MessageBox_YesBtn:String = "Да";
		public static var MessageBox_NoBtn:String = "Нет";
		
		public static var MessageBox_LeaveToLobby:String = "Вы действительно хотите выйти в город?";
		public static var MessageBox_LeaveToLobbyFromTraining:String = "Вы действительно хотите выйти в город?";
		public static var MessageBox_ExitGame:String = "Вы действительно хотите выйти из игры?";
		public static var MessageBox_ExitTrainingGame:String = "Вы действительно хотите выйти из игры c ботами?";
		public static var MessageBox_ExitSkipTutorial:String = "Вы действительно хотите прервать обучение?\nОбучение можно будет пройти позже.";
		
		//ChatInputTextBox
		public static var ChatInputComboBox_EnterName:String = "Введите имя";
		public static var ChatBar_CantFindPlayer:String = "Сообщение не отправлено - игрок не найден";
		
		public static var BubbleNextButton:String = "Продолжить"
		static public var InventoryBar_PrimeCountLabel:String = "Количество прайма";
		
		public static var PremiumAccountTooltip:String = "В замке игрока {0} наступил Золотой Век!<br>В случае победы все игроки его команды получат дополнительный талант. В случае поражения только игрок {0} получит дополнительный талант"
		public static var PersonalStatisticBar_PremiumAwardsHeaderText:String = "Награды за золотой век";
		static public var Tooltip_StatisticBarPrimeIcon:String = "Заработанный прайм:";
		static public var StatisticsThousendsIndificator:String = " т."
		
		static public var Tooltip_StatisticBarTeamKillsIcon:String = "Количество убийств команды";
		static public var Tooltip_StatisticBarTeamPrimeIcon:String = "Заработанный командой прайм";
		
		static public var RestrictedChatSymbols:String = "";
		
		//Report Window
		static public var ReportWindow_Header:String = "Жалобы";
		static public var ReportWindow_ReportChioceTExt:String = "Причина:";
		static public var ReportWindow_HintTExt:String = "Вы собираетесь отправить жалобу на игрока";
		static public var ReportWindow_ReportButton:String = "Отправить";
		static public var ReportWindow_CancelButton:String = "Отменить";
		static public var ReportWindow_CloseBtnLabel:String = "Закрыть";
		static public var ReportWindow_MessageBoxText:String = "Вы уже пожаловались на этого игрока!";
		static public var ReportWindow_MessageBoxHeader:String = "Ошибка!";
		static public var ReportWindow_HintEmptyText:String = "Пожаловаться на игрока";
		static public var ReportWindow_MessageNoReportDataHeader:String = "Ошибка";
		static public var ReportWindow_MessageNoReportDataText:String = "Ошибка связи с сервером жалоб. Попробуйте перезапустить игру.";
		static public var ReportWindow_CounterTooltip:String = "Количество доступных жалоб. Оно восстанавливается каждые сутки.";
		//Share Button
		static public var ShareButtonTooltip:String = "Поделиться";
		static public var ShareMessageBoxHeader:String = "Поделиться";
		static public var ShareMessageBoxText:String = "Поделиться статистикой боя с друзьями?<br>(будет открыто окно браузера)";
		
		static public var ReportWindow_DefaultText:String = "Выберите тип жалобы";
		
		static public var QuestHint_DefaultText:String = "Закрыть подсказку";
		
		// Smart Chat
		static public var SmartChat_Back:String = "Назад";
		static public var SmartChat_Cancel:String = "Отмена";
		//Smart Chat button tooltip
		static public var Tooltip_chatBtn:String = "Краткие сообщения (V)";
		
		// Chat messages
		public static var ChatMessage_Ignore:String = "Игрок {0} добавлен в список игнорируемы";
		public static var ChatMessage_RemoveIgnore:String = "Игрок {0} удалён из списка игнорируемы";
		
		public static function LocalizationComplete():void
		{
			CompleteEventDispatcher.dispatchEvent(new Event(Event.COMPLETE));
		}
	}
}