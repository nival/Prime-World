package
{
	import classes.Enums.EBubbledElements;
	import fl.motion.CustomEase;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.geom.Rectangle;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import fl.controls.Button;
	
	import EscMenu.Preferences;
	import Components.*;
	import Controllers.*;
	import Interfaces.*;
	import Enums.*;
	import TalentBar.*;
	import ShopBar.*;
	import InventoryBar.*;
	import StatisticBars.*;
	
	public class MainInterfaceTest extends Sprite
	{
		private var Interface:MainInterface;
		private var preferenceInterface:Preferences;
		
		//	private var main:Main;
//		private var but:bb;
//		private var but1:bb;
		private var names_arr:Array = [];
		private var ico_arr:Array = [];
		private var icoPath:String = 'art/ico/talents/';
		private var heroDead:Boolean = false;
		
		private var classes_arr:Array = [];
		private var players:uint = 0;
		private var numSlotShop:int = 0;
		
		private var inventoryItems:int;
		
		private var filledDataCategories:Array = [];
		
		private var fullTest:Boolean = false;
		private var EnterMini:Boolean = true;
		private var _main:Main;
		
		private var chatChannel:int = 1;
		private var showSelection:Boolean = true;
		private var isLeftPlayer:Boolean;
		
		private var buttons:Array = new Array();
		private var newMan:Boolean = true;
		private var iconPathsArr:Array = new Array();
		private var tutorialBlocks:Array = new Array();
		
		public function MainInterfaceTest(mainInterface:MainInterface, main:Main)
		{
			tutorialBlocks = [ETutorialBlocks.ActionBarBlock, ETutorialBlocks.ActionBarEscBtn, ETutorialBlocks.MoneyBlock, ETutorialBlocks.ActionBarTalentBtn, ETutorialBlocks.PlayerHeroBlock, ETutorialBlocks.SelectionBlock, ETutorialBlocks.ActionBarInventoryBtn, ETutorialBlocks.MiniMapBlock, ETutorialBlocks.ActionBarCharStatBtn, ETutorialBlocks.ActionBarStatisticBtn, ETutorialBlocks.EnemyTeamMateBlock, ETutorialBlocks.FriendlyTeamMateBlock, ETutorialBlocks.ActionBarQuestBtn, ETutorialBlocks.ActionBarSocialBtn, ETutorialHighlitedObjects.PortalButton];
			
			Interface = mainInterface;
			_main = main;
			
			main.addEventListener(KeyboardEvent.KEY_UP, OnKeyboardEvent)
			main.addEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			names_arr = ['[Ginas]Fragnomore', '[boobs]patrik2', '[feet]даркДрагон3', '[feet]Warband4', 'Панамка5', '[feet]Greck6', 'Lenin7', '[feet]Тор8', '[feet]папай маряк9', '[feet]Linda10', "newMan11", '[Ginas]Fragnomore', '[boobs]patrik2', '[feet]даркДрагон3', '[feet]Warband4', 'Панамка5', '[feet]Greck6', 'Lenin7', '[feet]Тор8', '[feet]папай маряк9', '[feet]Linda10'];
			ico_arr = ['01.png', '02.png', '03.png', '04.png', '05.png', '06.png', '07.png', '08.png', '09.png', '10.png', '11.png', '12.png', '13.png', '14.png', '01.png', '02.png', '03.png', '04.png', '05.png', '06.png', '07.png', '08.png', '09.png', '10.png', '11.png', '12.png', '13.png', '14.png'];
			classes_arr = ['класс1', 'класс2', 'класс3', 'класс4', 'класс5', 'класс6', 'класс7', 'класс8', 'класс9', 'класс10', 'класс11', 'класс12', 'класс13']
			
			for (i = 0; i < ico_arr.length; i++)
			{
				iconPathsArr[i] = icoPath + ico_arr[i];
				trace("iconPathsArr[" + i + "]=" + iconPathsArr[i]);
			}
			
			var i:int = 0;
			for (i = 0; i < 20; i++)
			{
				filledDataCategories.push(false);
			}
			
			var myTimer:Timer = new Timer(1000, 1);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete)
			myTimer.start();
			
			function onComplete(e:TimerEvent):void
			{
				Localization.LocalizationComplete();
				
				Interface.ShowFPS(true);
				
				preferenceInterface = _main.PreferencesInterface;
				
				Interface.ShowSpawnCreepsAnnouncement(icoPath + ico_arr[13], icoPath + ico_arr[13], "До выхода солдат осталось");
				
				for (var j:int = 0; j < 11; j++)
				{
					var timeOfVis:Number = 2;
					
					if (j < 2)
						timeOfVis = 0;
					
					Interface.SetErrorMessage(j, "ErrorMessage " + j, true, timeOfVis);
				}
				
				Interface.AddChannel(1, "Chanel1", 0xffffff, true, true, true);
				Interface.AddChannel(2, "Chanel2", 0xff0000, false, true, true);
				Interface.AddChannel(3, "Chanel3", 0x00ff00, true, false, true, true, 1);
				Interface.AddChannel(4, "Chanel4", 0x000000, true, true, true, true, 2);
				//	Interface.AddChannel(5, "Chanel5", 0x000000, true, true, false);
				//	Interface.AddChannel(6, "Chanel6", 0x000000, true, true, false);
				//	Interface.AddChannel(7, "Chanel7", 0x000000, true, true, true);
				//	Interface.AddChannel(8, "Chanel8", 0x000000, true, true,true);
				Interface.SetDefaultChannel(1);
				Interface.AddChannelShortCut(1, "s");
				Interface.AddChannelShortCut(2, "sss");
				Interface.AddChannelShortCut(3, "5");
				Interface.AddChannelShortCut(4, "1");
				
				Interface.AddFriend(names_arr[0]);
				Interface.AddFriend(names_arr[1]);
				Interface.AddFriend(names_arr[2]);
				Interface.AddFriend(names_arr[3]);
				Interface.AddFriend(names_arr[4]);
				
				Interface.SetClientVersion("Test.Version.0.10.02023045");
				
				for (var k:int = 0; k < 4; k++)
				{
					Interface.AddReportItem(k, "Жалоба " + k);
				}
				
				Interface.SetReportCounters(3, 3);
				
				var forces:Array = [0, 110, 200];
				var colors:Array = [0xffffff, 0xff0000, 0x000000];
				
				Interface.SetForceColors(forces, colors);
				trace("--------Finished-----------");
				
				
				Interface.SetBindString("editline_wordleft  'CTRL' + 'LEFT'" );
				Interface.SetBindString("cmd_action_bar_slot1 'Ctrl' + 'Lsdadsadasd'");
				Interface.SetBindString("cmd_action_bar_slot2 'B'");
				Interface.SetBindString("cmd_action_bar_slot3 'd'");
				Interface.SetBindString("cmd_action_bar_slot4 'e'");
				Interface.SetBindString("cmd_action_bar_slot5 't'");
				Interface.SetBindString("cmd_action_bar_slot6 'Ctrl' + 'W'");
				Interface.SetBindString("cmd_action_bar_slot7 'f'");
				Interface.SetBindString("cmd_action_bar_slot8  'k'");
				Interface.SetBindString("cmd_action_bar_slot9 'l'");
				Interface.SetBindString("cmd_action_bar_slot10 'm'");
				Interface.SetBindString("exit_game 'ALT' + 'X'");
			}
			
			FSCommands.testing = true;
			
			GenerateButton("Прогнать полный тест", TestAll);
			GenerateButton("Тест TeamInfo", TestTeamInfo);
			GenerateButton("Тест Статистики", TestStatisticData);
			GenerateButton("Тест CharStat", TestCharStat);
			GenerateButton("Тест TalantBar", TestTalantBar);
			GenerateButton("Тест LevelUp ", TestLevel);
			GenerateButton("Тест InventoryBar", TestInventoryBar);
			GenerateButton("Тест ActionBar и GlobalCoolDown", TestActionBarAndCoolDown);
			GenerateButton("Тест наполнения денег", TestGoldAndNafta);
			GenerateButton("Экран победы", TestEndScreen);
			GenerateButton("Тест сигналов на миникарте", TestMiniMapAddSignal);
			GenerateButton("Тест импульсный бафф", TestImpulsBuff);
			GenerateButton("Тест баффов", TestBuffs);
			GenerateButton("Вход в миниигру", TestEnterMiniGame);
			GenerateButton("Пустить таймер на героя", TestNewTimer);
			GenerateButton("Показать ипульсный бафф", TestShowImpulsBuff);
			GenerateButton("Скрыть ипульсный бафф", TestHideImpulsBuff);
			GenerateButton("Показать-Скрыть-показать ипульсный бафф", TestShowHideImpulsBuff);
			GenerateButton("Вывести финальную статистику", TestFinalStatistic);
			GenerateButton("Тест личной статистики", TestPrivateStat);
			GenerateButton('Экран поражения', TestEndDScreen);
			GenerateButton('Открыть магазин', TestOpenShop);
			GenerateButton('Поменять героя', TestHeroChange);
			GenerateButton('Заполнить магазин', TestShopItems);
			GenerateButton('Тест channelingBar', TestChanneling);
			GenerateButton('Тест ErrorMessage', TestErrorMessage);
			GenerateButton('Тест Устроить смерть герою', TestHeroDeath);
			GenerateButton('Тест Написать эррорМесадж', TestShowErrorMessage);
			GenerateButton('Тест Анноунсментов', TestAnnouncement);
			GenerateButton('Игрок сбежал', TestPlayerLeft);
			GenerateButton('Таймер на выход крипов', TestCripSpownTimer);
			GenerateButton('Тест бара статистики', TestBarStats);
			GenerateButton('Тест меню настроек', TestPreferences);
			GenerateButton('Тест локализации', TestLocalization);
			GenerateButton('Тест талантбара Селекшена', TestSelectionTalentBar);
			GenerateButton('Тест смены иконки в импульсном бафе', TestImpulseBuffIconChange);
			GenerateButton('Добавить сообщение в чат', TestChatFilling);
			GenerateButton('Поменялись настройки', TestPrefChanged);
			GenerateButton('Добавить награды', TestAddAwards);
			GenerateButton('Показать/скрыть селект', TestShowHideSelect);
			GenerateButton('Показать голосовалку', TestShowVoteMenu);
			GenerateButton('Скрыть голосовалку', TestHideVoteMenu);
			GenerateButton('Тест Длинных имён', TestLongNames);
			GenerateButton('Тест игрок сбежал - вернулся', TestLeftAndBack);
			GenerateButton('Вызвать диалог о выходе, без эскейп меню', TestTryExit);
			GenerateButton('Заместить игрока.', TestAddNewPlayer);
			GenerateButton('Запустить эффект для яйца дракона.', TestEgg);
			GenerateButton('Запустить туториал.', TestTutorial);
			GenerateButton('Добавить квест', TestQuestTrackerAdd);
			GenerateButton('Удалить квест', TestQuestTrackerRemove);
			GenerateButton('Показать баббл', TestBubbleShowing);
			GenerateButton('Показать/скрыть хинтлайн', TestHintlineShowing);
			GenerateButton('Показать/скрыть буффы в туториале', TestTutorialBuffsShowing);
			GenerateButton('Тест статусов в кнопке портала', TestPortalButton);
			GenerateButton('Тест талантов на ману', TestTalentOnMana);
			GenerateButton('Показать/скрыть синематик', HideShowCinematic);
			GenerateButton('Показать/скрыть пролистывание', HideShowCinematicSkipButton);
			GenerateButton('Тест драгонвальда', TestDragonvald);
			GenerateButton('Тест скриптового окна сообщений', TestMessageBox);
			GenerateButton('Lock/Unlock actionBar', TestLockActionBar);
			GenerateButton('ChangeMyHeroRaiting', TestChangeMyHeroRaiting);
			GenerateButton('SetFirstWin', TestFirstWinState);
			GenerateButton('Change my hero test', TestChangeHero);
			GenerateButton('TestChangeTalentIsActiveState', TestChangeTalentIsActiveState);
			GenerateButton('TestPveBacks', TestPweBack);
			GenerateButton('ChangeChannel', TestChangeChannel);
			GenerateButton('Report Window', ReportWindowTest);
			GenerateButton('RemoveQuest+ShowCinematic', TutorialQuestRemoveAndCinematic);
			GenerateButton('Tutoruial  SHowUIBlock', TutorialShowUIBlock);
			GenerateButton('QuestHint Show', ShowQuestHint);
			GenerateButton('Вкл/выкл кнопки в эскейп-меню', TestEscMenuButtonDisable);
		}
		
		private function GenerateButton(label:String, listener:Function):void
		{
			var newButton:Button = new Button();
			newButton.label = label;
			
			AddButtonFunction(newButton, buttons.length == 0 ? null : buttons[buttons.length - 1]);
			
			function AddButtonFunction(NewButt:Button, oldButt:Button):void
			{
				if (oldButt == null)
				{
					NewButt.y = 130;
				}
				else
				{
					NewButt.y = oldButt.y + 20;
					NewButt.x = oldButt.x;
				}
				if (NewButt.y >= 700)
				{
					NewButt.y = 130;
					NewButt.x = oldButt.x + 220;
				}
				
				buttons.push(NewButt);
				NewButt.width = 200;
				_main.addChild(NewButt);
			}
			
			newButton.addEventListener(MouseEvent.CLICK, listener);
		
		}
		
		private var buffsShow:Boolean = false;
		
		private function TestTutorialBuffsShowing(e:MouseEvent):void
		{
			Interface.ShowUIBlock(ETutorialBlocks.Buffs, buffsShow);
			buffsShow = !buffsShow;
		}
		
		private function OnAddedToStage(e:Event):void
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			stage.addEventListener(KeyboardEvent.KEY_UP, OnKeyboardEvent)
		}
		
		private function OnKeyboardEvent(e:KeyboardEvent):void
		{
			trace("e.keyCode " + e.keyCode + " e.altKey " + e.altKey + " e.ctrl " + e.ctrlKey);
			
			if (e.keyCode == 192)
			{
				for (var i:int = 0; i < buttons.length; i++)
				{
					buttons[i].visible = !buttons[i].visible
				}
			}
			
			if (e.keyCode == 13)
			{
				Interface.EnterPressed();
			}
			
			if (e.keyCode == 27)
			{
				Interface.OnEscape();
			}
		}
		
		private function TestAll(e:MouseEvent):void
		{
			fullTest = true;
			TestTeamInfo();
		}
		
		private function SetDataForTeam(myHero:int = 1):void //Заполняет начальные параметры героев
		{
			if (filledDataCategories[DataCategories.TEAM_DATA])
				return;
			
			filledDataCategories[DataCategories.TEAM_DATA] = true;
			
			Interface.SetOurHeroIdententity(myHero, 1, EFraction.ELF_FACTION, iconPathsArr[0], names_arr[0], false, 4);
			var male:Boolean = true;
			
			for (var i:int = 1; i < 6; i++)
			{
				var team:int = 0; //= Math.random() * 3;
				var team2:int = Math.random() * 3;
				
				if (i == 1 || i == 2 || i == 3)
					team = 2;
				else
					team = 1;
				
				trace(names_arr[i - 1] + " team " + team + "  " + names_arr[i + 4] + " team " + team2);
				
				Interface.SetFriendlyHeroIdentity(i, names_arr[i - 1], classes_arr[i - 1], icoPath + ico_arr[i - 1], male, false, i * 25, 1, 1, 100.34, icoPath + ico_arr[i - 1], "tooltip " + i,true, team, iconPathsArr[i - 1], names_arr[i - 1]);
				Interface.SetEnemyHeroIdentity(i + 5, names_arr[i + 4], classes_arr[i + 4], icoPath + ico_arr[i + 4], !male, true, i * 15, 2, 2, 300.35, icoPath + ico_arr[i + 4], "raiting " + i,true, team2, iconPathsArr[i + 4], names_arr[i + 4]);
				Interface.ShowHeroPortrait(i);
				Interface.ShowHeroPortrait(i + 5);
				Interface.SetHeroParams(i, 1, 20, 1000, 20, 1000, true, 0, 0, i + 10, i + 10);
				Interface.SetHeroParams(i + 5, 1, 1000, 1000, 1000, 1000, false, 0, 0, i + 5);
				male = !male;
				
				if (i == 1)
				{
					Interface.SetCharStatUnit(false, 1, icoPath + ico_arr[i - 1], names_arr[i - 1], EFraction.ELF_FACTION, 1);
				}
			}
		}
		
		private function TestAddNewPlayer(e:MouseEvent):void
		{
			if (newMan)
			{
				Interface.SetFriendlyHeroIdentity(5, names_arr[10], classes_arr[10], icoPath + ico_arr[10], true, false, 120, 1, 1, 1010, icoPath + ico_arr[10], "raiting " + 10,false,0, iconPathsArr[5], names_arr[5]);
				Interface.SetHeroParams(5, 12, 400, 4000, 400, 4000, true, 0, 0, 5, 5);
			}
			else
			{
				Interface.SetFriendlyHeroIdentity(5, names_arr[1], classes_arr[1], icoPath + ico_arr[1], true, false, 120, 1, 1, 1010, icoPath + ico_arr[1], "raiting " + 1,false,0, iconPathsArr[1], names_arr[1]);
				Interface.SetHeroParams(5, 12, 400, 4000, 400, 4000, true, 0, 0, 6, 6);
			}
			
			Interface.SetHeroGameProgress(5, 0, 0, 0, 0, 0);
			newMan = !newMan;
		}
		
		private function ReportWindowTest(e:MouseEvent):void
		{
			Interface.ShowHideWindow(EWindows.WINDOW_REPORT);
		}
		
		private function SetStatisticsData():void //Заполняет данные в окне статистики
		{
			if (filledDataCategories[DataCategories.STATISTIC_DATA])
				return;
			
			SetDataForTeam();
			filledDataCategories[DataCategories.STATISTIC_DATA] = true;
			
			for (var i:int = 1; i <= 10; i++)
			{
				Interface.SetHeroGameProgress(i, 1, 1, 1, 1, 0);
			}
			
			Interface.SetGameProgress(0.3, 0.3, 0, 0);
		}
		
		private function SetCharStatData():void //Заполняет данные в окне чар-стата
		{
			if (filledDataCategories[DataCategories.CHARSTAT_DATA])
				return;
			
			SetDataForTeam();
			filledDataCategories[DataCategories.CHARSTAT_DATA] = true;
			
			var addit:int = Math.round(Math.random() * 40) - 20;
			var addit1:int = Math.round(Math.random() * 40) - 20;
			var addit2:int = Math.round(Math.random() * 40) - 20;
			var addit3:int = Math.round(Math.random() * 40) - 20;
			var addit4:int = Math.round(Math.random() * 40) - 20;
			var addit5:int = Math.round(Math.random() * 40) - 20;
			var addit6:int = Math.round(Math.random() * 20) - 10;
			
			Interface.SetBaseStat(false, EStat.STAT_ATTACKSPEED, 10, addit, true);
			Interface.SetBaseStat(false, EStat.STAT_STRENGTH, 10, addit1, false);
			Interface.SetBaseStat(false, EStat.STAT_INTELLECT, 10, addit2, true);
			Interface.SetBaseStat(false, EStat.STAT_DEXTERITY, 10, addit3, false);
			Interface.SetBaseStat(false, EStat.STAT_STAMINA, 10, addit4, true);
			Interface.SetBaseStat(false, EStat.STAT_WILL, 10, addit5, false);
			Interface.SetBaseStat(false, EStat.STAT_MOVESPEED, 30, addit6, true);
			
			Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_DAMAGEMIN, 100);
			Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_DAMAGEMAX, 200);
			Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_ATTACKSPERSECOND, 123);
			Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_CRITCHANCE, 10);
		}
		
		private function SetTalantsData():void // Заполняет окно талантов, без заполнения статусов талантов
		{
			var i:int
			var j:int
			if (filledDataCategories[DataCategories.TALANT_DATA])
			{
				for (i = 0; i < 6; i++)
				{
					for (j = 0; j < 6; j++)
					{
						Interface.SetTalentState(i, j, TalentUIState.BOUGHT);
					}
				}
				
				return;
			}
			
			filledDataCategories[DataCategories.TALANT_DATA] = true;
			
			var isActive:Boolean = true;
			var ind:int = -1;
			for (var t:int = 0; t < 36; t++)
			{
				
				var col:int = t / 6;
				var raw:int = t % 6;
				var ico:int = Math.round(Math.random() * 9);
				ind = t;
				if (ind > 6)
					ind = -1;
				
				var upgrLevel:int = Math.round(Math.random() * 3);
				
				Interface.SetTalentIcon(col, raw, icoPath + ico_arr[ico], icoPath + ico_arr[ico + 1], isActive, ind, upgrLevel, false, t);
				isActive = !isActive;
			}
			
			for (i = 0; i < 6; i++)
			{
				for (j = 0; j < 6; j++)
				{
					Interface.SetTalentState(i, j, TalentUIState.BOUGHT);
				}
			}
		}
		
		private function SetSelectionTalantsData():void // Заполняет окно талантов селекшена, без заполнения статусов талантов
		{
			var i:int
			var j:int
			var isActive:Boolean = false;
			
			for (var t:int = 0; t < 36; t++)
			{
				var col:int = t / 6;
				var raw:int = t % 6;
				var ico:int = Math.round(Math.random() * 9);
				
				Interface.SetSelectionTalentIcon(col, raw, icoPath + ico_arr[ico], isActive, 0);
				isActive = !isActive;
			}
			
			for (i = 0; i < 6; i++)
			{
				for (j = 0; j < 6; j++)
				{
					Interface.SetSelectionTalentState(i, j, j & 2);
				}
			}
		}
		
		private function SetDataForLevel():void
		{
			SetTalantsData();
			
			for (var i:int = 0; i < 6; i++)
			{
				for (var j:int = 0; j < 6; j++)
				{
					Interface.SetTalentState(i, j, TalentUIState.CANBUY);
				}
			}
		}
		
		private function SetInventoryData(count:int):void // Заполняет окно инвентаря иконками.
		{
			if (filledDataCategories[DataCategories.INVENTORY_DATA])
				return;
			
			filledDataCategories[DataCategories.INVENTORY_DATA] = true;
			var i:int;
			
			for (i = 0; i < count; i++)
			{
				Interface.SetInventoryItemIcon(i, icoPath + '14.png');
				
			}
			
			for (i = 0; i < count; i++)
			{
				Interface.SetInventoryItemState(i, 1, 0, 0, 0);
			}
		
		}
		
		private function SetActionBarData():void // Заполняет экшнбар
		{
			var numbers:int = 10;
			var i:int = 0;
			SetTalantsData();
			SetInventoryData(numbers);
			
			for (i = 0; i < numbers; i++)
			{
				var count:int = Math.round(Math.random() * 10 - 0.5);
				var state:int = Math.round(Math.random() * 6);
				Interface.SetInventoryItemState(i, count + 1, state, 0, 0);
			}
			
			for (i = 0; i < 6; i++)
			{
				//		var col:int = Math.random() * 6;
				//		var raw:int = Math.random() * 6;
				
				var col:int = i;
				var raw:int = i;
				
				Interface.AddInventoryItemToActionBar(i);
			}
		}
		
		private function SetBuffsData():void
		{
			
			var randomHeroe:int = Math.round(Math.random() * 9);
			var randomLevel:int = Math.round(Math.random() * 25);
			
			var hpMax:int = Math.round(Math.random() * 3000);
			var hpCur:int = Math.round(Math.random() * hpMax);
			
			var mnMax:int = Math.round(Math.random() * 3000);
			var mnCur:int = Math.round(Math.random() * mnMax);
			
			var vis:Boolean = hpMax > 1500;
			
			var enemOrUs:Boolean = randomHeroe > 5;
			
			Interface.setSelectionInfoIcon(icoPath + ico_arr[randomHeroe], -3, true);
			Interface.SetSelectionParams(names_arr[randomHeroe], randomLevel, hpCur, hpMax, mnCur, mnMax, enemOrUs, 0.5, 5, 5);
		}
		
		/* Тестирует тим инфо, рандомно меняет значения уровней, ХП, маны, видим-невидим, выпихивает рандомно селекшен.
		   эти изменения будут заметны и в чар стате и в статистике
		 */
		private function TestTeamInfo(e:MouseEvent = null):void
		{
			SetDataForTeam();
			
			Interface.ShowHideWindow(EWindows.WINDOW_STATISTICBAR);
			var male:Boolean = true;
			
			var myTimer:Timer = new Timer(400, 30);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete)
			myTimer.start();
			
			function onTick(e:TimerEvent):void
			{
				var randomHeroe:int = 1 + Math.round(Math.random() * 8);
				var randomLevel:int = Math.round(Math.random() * 25);
				
				var hpMax:int = Math.round(Math.random() * 3000);
				var hpCur:int = Math.round(Math.random() * hpMax);
				
				var mnMax:int = Math.round(Math.random() * 3000);
				var mnCur:int = Math.round(Math.random() * mnMax);
				
				var vis:Boolean = hpMax > 1500;
				
				var enemOrUs:Boolean = randomHeroe > 5;
				
				Interface.setSelectionInfoIcon(icoPath + ico_arr[randomHeroe], randomHeroe, male);
				Interface.SetSelectionParams(names_arr[randomHeroe], randomLevel, hpCur, hpMax, mnCur, mnMax, enemOrUs, 0.5, 5, 5);
				male = !male;
				Interface.SetHeroParams(randomHeroe, randomLevel, hpCur, hpMax, mnCur, mnMax, vis, 0, 0, 6, 6);
				
				if (randomHeroe == 1)
				{
					Interface.SetCharStatUnitParams(false, randomHeroe, randomLevel, hpCur, hpMax, mnCur, mnMax, true);
				}
			}
			
			function onComplete(e:TimerEvent):void
			{
				Interface.ShowHideWindow(EWindows.WINDOW_STATISTICBAR);
				
				var t1:int = 50;
				var t2:int = 30;
				var t3:int = 40;
				
				var myTimer1:Timer = new Timer(300, 50);
				myTimer1.addEventListener(TimerEvent.TIMER, onTick1)
				myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete1)
				myTimer1.start();
				
				function onTick1(e:TimerEvent):void
				{
					t1--;
					t2--;
					t3--;
					Interface.SetHeroParams(1, 5, 100, 1000, 200, 2000, true, t1, 0, 5, 5);
					Interface.SetCharStatUnitParams(false, 1, 5, 100, 1000, 200, 2000, true);
					Interface.SetHeroParams(3, 5, 200, 1000, 200, 1000, true, t2, 0, 6, 6);
					Interface.SetHeroParams(8, 5, 200, 1000, 200, 1000, false, t3, 0, 7, 7);
				}
			}
			
			function onComplete1(e:TimerEvent):void
			{
				Interface.ShowHideWindow(EWindows.WINDOW_STATISTICBAR);
				if (fullTest)
					TestStatisticData();
			}
		}
		
		private function TestStatisticData(e:MouseEvent = null):void //тест статистики - меняет кол-во убийств, смертей и т.п. и показывает захват территории.
		{
			SetStatisticsData();
			
			Interface.ShowHideWindow(EWindows.WINDOW_STATISTICBAR);
			var GameProgress:Number = 0;
			
			var myTimer:Timer = new Timer(50, 1000);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			
			var myTimer1:Timer = new Timer(3000, 5);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick1)
			myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete);
			myTimer1.start();
			
			Interface.PlayerLeft(2);
			Interface.PlayerLeft(7);
			
			function onTick():void
			{
				GameProgress += 0.1;
			}
			
			function onTick1():void
			{
				var dwarfTerr:Number = Math.random();
				var ElfTerr:Number = Math.random() * (1 - dwarfTerr);
				
				Interface.SetGameProgress(dwarfTerr, ElfTerr, GameProgress, 0);
			
			}
			
			var myTimer2:Timer = new Timer(300, 40);
			myTimer2.addEventListener(TimerEvent.TIMER, onTick2)
			myTimer2.start();
			
			function onTick2(e:TimerEvent):void
			{
				var randomHeroe:int = Math.round(Math.random() * 100);
				var randomkills:int = Math.round(Math.random() * 100);
				var randomdeaths:int = Math.round(Math.random() * 100);
				var randomassists:int = Math.round(Math.random() * 100);
				var randomscore:int = Math.round(Math.random() * 1000);
				var randomprime:int = Math.round(Math.random() * 100000);
				Interface.SetHeroGameProgress(randomHeroe, randomkills, randomdeaths, randomassists, randomscore, randomprime);
			}
			
			function onComplete(e:TimerEvent):void
			{
				Interface.SetGameProgress(0.5, 0.5, GameProgress, 0);
				
				var Tim:Timer = new Timer(1000);
				myTimer2.addEventListener(TimerEvent.TIMER_COMPLETE, TimCOMPLETE)
				myTimer2.start();
			}
			
			function TimCOMPLETE(e:TimerEvent):void
			{
				Interface.ShowHideWindow(EWindows.WINDOW_STATISTICBAR);
				if (fullTest)
				{
					TestCharStat();
				}
			}
		}
		
		private function TestCharStat(e:MouseEvent = null):void // меняет значения в чарстате, которые не получаются из тиминфо.
		{
			SetCharStatData();
			
			Interface.ShowHideWindow(EWindows.WINDOW_CHARSTATBAR);
			
			var myTimer1:Timer = new Timer(300, 30);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick)
			myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete)
			myTimer1.start();
			
			function onTick():void
			{
				
				var addit:int = Math.round(Math.random() * 40) - 20;
				var addit1:int = Math.round(Math.random() * 40) - 20;
				var addit2:int = Math.round(Math.random() * 40) - 20;
				var addit3:int = Math.round(Math.random() * 40) - 20;
				var addit4:int = Math.round(Math.random() * 40) - 20;
				var addit5:int = Math.round(Math.random() * 40) - 20;
				var addit6:int = Math.round(Math.random() * 20) - 10;
				
				var rand:int = Math.round(Math.random() * 40)
				var rand1:int = Math.round(Math.random() * 40)
				var rand2:int = Math.round(Math.random() * 40)
				var rand3:int = Math.round(Math.random() * 40)
				var rand4:int = Math.round(Math.random() * 40)
				var rand5:int = Math.round(Math.random() * 40)
				var rand6:int = Math.round(Math.random() * 20)
				
				Interface.SetBaseStat(false, EStat.STAT_ATTACKSPEED, rand, addit, true);
				Interface.SetBaseStat(false, EStat.STAT_STRENGTH, rand1, addit1, false);
				Interface.SetBaseStat(true, EStat.STAT_INTELLECT, rand2, addit2, true);
				Interface.SetBaseStat(false, EStat.STAT_DEXTERITY, rand3, addit3, false);
				Interface.SetBaseStat(false, EStat.STAT_STAMINA, rand4, addit4, true);
				Interface.SetBaseStat(false, EStat.STAT_WILL, rand5, addit5, false);
				Interface.SetBaseStat(false, EStat.STAT_MOVESPEED, rand6, addit6, true);
				
				var randEnColor:int = Math.round(Math.random() * 20) - 10;
				var randLifeColor:int = Math.round(Math.random() * 20) - 10;
				
				Interface.SetBaseStat(false, EStat.STAT_LIFE, 10, randLifeColor, true);
				Interface.SetBaseStat(false, EStat.STAT_ENERGY, 10, randLifeColor, true);
				
				var randDamMin:int = Math.round(Math.random() * 700)
				var randDamMax:int = Math.round(Math.random() * 300) + randDamMin;
				var randAtackSp:int = Math.round(Math.random() * 200)
				var randCrit:int = Math.round(Math.random() * 100)
				
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_DAMAGEMIN, randDamMin);
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_DAMAGEMAX, randDamMax);
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_ATTACKSPERSECOND, randAtackSp);
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_CRITCHANCE, randCrit);
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_PENETRATIONTOTAL, randCrit - 4);
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_BODYDEFENCE, randCrit + 2);
				Interface.SetDerivativeStat(false, EDerivativeStat.DERIVATIVESTAT_SPIRITDEFENCE, randCrit + 4);
			}
			
			function onComplete(e:TimerEvent):void
			{
				Interface.ShowHideWindow(EWindows.WINDOW_CHARSTATBAR);
				if (fullTest)
				{
					TestTalantBar();
				}
			}
		}
		
		// тест талантбара - сначала меняются значения куплено-не куплено и т.п., потом по активно/неактивно и т.п.
		// кулдаун
		
		private function TestTalantBar(e:MouseEvent = null):void
		{
			SetTalantsData();
			
			Interface.ShowHideWindow(EWindows.WINDOW_TALENTSBAR);
			
			var myTimer1:Timer = new Timer(100, 50);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick)
			myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComlplete)
			myTimer1.start();
			
			function onTick(e:TimerEvent):void
			{
				var col:int = Math.random() * 6;
				var raw:int = Math.random() * 6;
				var state:int = Math.random() * 4;
				
				Interface.SetTalentState(raw, col, state);
			}
			function onComlplete(e:TimerEvent):void
			{
				for (var i:int = 0; i < 6; i++)
				{
					for (var j:int = 0; j < 6; j++)
					{
						Interface.SetTalentState(i, j, 0);
					}
				}
				Interface.ShowHideWindow(EWindows.WINDOW_TALENTSBAR);
				if (fullTest)
				{
					TestLevel();
				}
			}
		}
		
		private function TestLevel(e:MouseEvent = null):void
		{
			SetDataForTeam();
			SetDataForLevel();
			
			Interface.ShowHideWindow(EWindows.WINDOW_TALENTSBAR);
			
			var myTimer:Timer = new Timer(300, 36);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete);
			myTimer.start();
			var i:int = 0;
			function onTick(e:TimerEvent):void
			{
				i += 1;
				Interface.SetHeroParams(1, i, 100, 100, 100, 100, true, 0, 0, 1, 1);
				Interface.SetCharStatUnitParams(false, 1, i, 100, 100, 100, 100, true);
				Interface.SetHeroParams(2, i, 100, 100, 100, 100, true, 0, 0, 2, 2);
				Interface.SetHeroParams(3, i, 100, 100, 100, 100, true, 0, 0, 3, 3);
				Interface.SetHeroParams(4, i, 100, 100, 100, 100, true, 0, 0, 4, 4);
				Interface.SetHeroParams(5, i, 100, 100, 100, 100, true, 0, 0, 5, 5);
				Interface.SetHeroParams(6, i, 100, 100, 100, 100, true, 0, 0, 6, 6);
				Interface.SetHeroParams(7, i, 100, 100, 100, 100, true, 0, 0, 7, 7);
				Interface.SetHeroParams(8, i, 100, 100, 100, 100, true, 0, 0, 8, 8);
				Interface.SetHeroParams(9, i, 100, 100, 100, 100, true, 0, 0, 9, 9);
				Interface.SetHeroParams(10, i, 100, 100, 100, 100, true, 0, 0, 10, 10);
			}
			
			function onComplete(e:TimerEvent):void
			{
				
				Interface.ShowHideWindow(EWindows.WINDOW_TALENTSBAR);
				if (fullTest)
				{
					TestInventoryBar();
				}
			}
		}
		
		private function TestInventoryBar(e:MouseEvent = null):void //тест инвентори бара, добавляются, меняются, для трёх включаю кулдаун, 
		{
			var numbers:int = 20;
			var t1Max:int = 50;
			var t2Max:int = 40;
			var t3Max:int = 20;
			var t1:int = t1Max;
			var t2:int = t2Max;
			var t3:int = t3Max;
			
			SetInventoryData(numbers);
			
			Interface.ShowHideWindow(EWindows.WINDOW_INVENTORYBAR);
			
			var myTimer1:Timer = new Timer(500, 10);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick)
			myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComlplete)
			myTimer1.start();
			
			function onTick(e:TimerEvent):void
			{
				for (var i:int = 0; i < numbers; i++)
				{
					var count:int = Math.round(Math.random() * 10 - 0.5);
					var state:int = Math.round(Math.random() * 6);
					Interface.SetInventoryItemState(i, count, state, 0, 0);
				}
			}
			function onComlplete(e:TimerEvent):void
			{
				
				var myTimer:Timer = new Timer(300, 55);
				myTimer.addEventListener(TimerEvent.TIMER, onTick1)
				myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComlplete1)
				myTimer.start();
			}
			
			function onTick1(e:TimerEvent):void
			{
				Interface.SetInventoryItemState(1, 1, 0, t1, t1Max);
				Interface.SetInventoryItemState(2, 2, 1, t2, t2Max);
				Interface.SetInventoryItemState(3, 3, 2, t3, t3Max);
				t1--;
				t2--;
				t3--;
			}
			
			function onComlplete1(e:TimerEvent):void
			{
				Interface.ShowHideWindow(EWindows.WINDOW_INVENTORYBAR);
				if (fullTest)
				{
					TestActionBarAndCoolDown();
				}
			}
		}
		
		private function TestActionBarAndCoolDown(e:MouseEvent = null):void //Заполняются таланты и инвентарь, рандомные закидываются через один в экшн бар, включается глобальный кулдаун.
		{
			Interface.ShowHideWindow(EWindows.WINDOW_INVENTORYBAR);
			Interface.ShowHideWindow(EWindows.WINDOW_TALENTSBAR);
			SetActionBarData();
			
			var maxCoold:Number = 80;
			
			var t:Number = maxCoold;
			var isAlternative:Boolean = false;
			var myTimer1:Timer = new Timer(300, t);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick1)
			myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete1);
			myTimer1.start();
			
			function onTick1(e:TimerEvent):void
			{
				t--;
				Interface.SetTalentStatus(2, 2, ActionBarSlotState.NOT_ENOUGHT_MANA, t, maxCoold, isAlternative);
				Interface.SetTalentStatus(3, 3, ActionBarSlotState.NOT_ENOUGHT_MANA, t, maxCoold, isAlternative);
				isAlternative = !isAlternative;
			}
			
			function onComplete1(e:TimerEvent):void
			{
				t = 80;
				
				var myTimer:Timer = new Timer(300, t);
				myTimer.addEventListener(TimerEvent.TIMER, onTick)
				myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete);
				myTimer.start();
				
				function onTick(e:TimerEvent):void
				{
					t--;
					Interface.SetGlobalCooldown(t, 80);
				}
				
				function onComplete(e:TimerEvent):void
				{
					Interface.ShowHideWindow(EWindows.WINDOW_INVENTORYBAR);
					Interface.ShowHideWindow(EWindows.WINDOW_TALENTSBAR);
					if (fullTest)
					{
						TestGoldAndNafta();
					}
				}
			}
		}
		
		private function TestGoldAndNafta(e:MouseEvent = null):void
		{
			var nafta:int = 0;
			var gold:int = 10;
			
			var myTimer:Timer = new Timer(10, 10000);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			
			function onTick(e:TimerEvent):void
			{
				Interface.SetHeroDevelopmentParams(nafta, gold);
				nafta += 10;
				gold += 10;
			}
		
		}
		
		private function TestEndScreen(e:MouseEvent):void
		{
			Interface.GameEnd(true, icoPath + '01.png', false);
		}
		
		private function TestEndDScreen(e:MouseEvent):void
		{
			Interface.GameEnd(true, icoPath + '01.png', false);
		}
		
		private function TestMiniMapAddSignal(e:MouseEvent):void
		{
			var myTimer:Timer = new Timer(100, 5);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			
			function onTick(e:TimerEvent):void
			{
				var X:Number = Math.random();
				var Y:Number = Math.random();
				Interface.AddSignal(X, Y);
			}
		}
		
		private function TestShowHideImpulsBuff(e:MouseEvent):void
		{
			//Interface.ShowImpulseBuff(icoPath + '01.png');
			Interface.HideImpulseBuff(true, true);
			Interface.ShowImpulseBuff(icoPath + '01.png');
		}
		
		private function TestImpulsBuff(e:MouseEvent):void
		{
			var closed:Boolean = false;
			
			var myTimer:Timer = new Timer(5000, 1);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			
			Interface.ShowImpulseBuff(icoPath + '01.png');
			
			function onTick(e:TimerEvent):void
			{
				
				var buy:Boolean = Math.round(Math.random() * 2) > 1;
				var key:Boolean = Math.round(Math.random() * 2) > 1;
				Interface.HideImpulseBuff(buy, key);
			}
		}
		
		private function TestShowImpulsBuff(e:MouseEvent):void
		{
			Interface.ShowImpulseBuff(icoPath + '01.png');
		}
		
		private function TestHideImpulsBuff(e:MouseEvent):void
		{
			var buy:Boolean = Math.round(Math.random() * 2) > 1;
			var key:Boolean = Math.round(Math.random() * 2) > 1;
			Interface.HideImpulseBuff(buy, key);
		}
		
		private function TestBuffs(e:MouseEvent):void
		{
			SetBuffsData();
			
			var i:int = 0;
			var pozitive:Boolean = true;
			var randomNum:int = Math.round(Math.random() * 21);
			var randomNum2:int = Math.round(Math.random() * 21);
			
			var t1:Number = 0;
			var t2:Number = 0;
			
			var myTimer:Timer = new Timer(200, 22);
			var myTimer1:Timer = new Timer(200, 24);
			myTimer.addEventListener(TimerEvent.TIMER, onTick);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick1);
			
			myTimer.start();
			
			var newTimer:Timer = new Timer(1000, 40);
			newTimer.addEventListener(TimerEvent.TIMER, onTickCooldown);
			
			function onTick(e:TimerEvent):void
			{
				var randomIco:int = Math.floor(Math.random() * (ico_arr.length - 1));
				var randomIco2:int = Math.floor(Math.random() * (ico_arr.length - 1));
				
				Interface.SetBuffIcon(false, icoPath + ico_arr[randomIco], i, pozitive);
				Interface.SetBuffIcon(true, icoPath + ico_arr[randomIco2], i, !pozitive);
				Interface.SetBuffStatus(false, i, 0, 1);
				Interface.SetBuffStatus(true, i, 0, 1);
				pozitive = !pozitive;
				i++;
				if (i == 22)
					RemoveBuff();
			}
			
			function RemoveBuff():void
			{
				myTimer.stop();
				myTimer1.start();
				i = 22
			}
			
			function onTick1(e:TimerEvent):void
			{
				Interface.SetBuffIcon(false, "", i, pozitive);
				Interface.SetBuffIcon(true, "", i, !pozitive);
				i--;
				if (i == -1)
					StartCoolDown();
			}
			
			function StartCoolDown():void
			{
				
				for (var j:int = 0; j <= 14; j++)
				{
					var randomIco:int = Math.floor(Math.random() * (ico_arr.length - 1));
					var randomIco2:int = Math.floor(Math.random() * (ico_arr.length - 1));
					
					Interface.SetBuffIcon(false, icoPath + ico_arr[randomIco], j, pozitive);
					Interface.SetBuffIcon(true, icoPath + ico_arr[randomIco2], j, !pozitive);
					pozitive = !pozitive;
				}
				newTimer.start();
			}
			
			function onTickCooldown(e:TimerEvent):void
			{
				Interface.SetBuffStatus(false, randomNum, t1, 3);
				Interface.SetBuffStatus(false, randomNum2, t2, 2);
				t1 += 0.1;
				t2 += 0.1;
			}
		}
		
		private function TestEnterMiniGame(e:MouseEvent):void
		{
			
			if (EnterMini)
				Interface.EnterMinigame();
			else
				Interface.LeaveMinigame()
			EnterMini = !EnterMini;
		}
		
		private function TestFinalStatistic(e:MouseEvent):void
		{
			_main.addFinalStatistic();
		}
		
		private function TestNewTimer(e:MouseEvent):void
		{
			SetDataForTeam();
			
			var t:int = 660;
			var myTimer:Timer = new Timer(100, 700);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			
			function onTick(e:TimerEvent):void
			{
				Interface.SetHeroParams(1, 4, 100, 1000, 100, 1000, true, t, 0, 5, 5);
				t--;
			}
		}
		
		private function TestPrivateStat(e:MouseEvent):void
		{
			SetStatisticsData();
			
			var arrExp:Array = new Array();
			arrExp = [0, 300, 720, 1360, 2260, 3260];
			
			Interface.SetStatisticExperienceBar(1500, 0, arrExp, 0);
			
			var i:int;
			for (i = 1; i < 11; i++)
			{
				Interface.SetFinalHeroTitle(i, "Титул " + i, icoPath + ico_arr[i], i);
				for (var j:int = 0; j < 3; j++)
				{
					Interface.AddHeroExploit(i, icoPath + ico_arr[i], j);
					
				}
				
				for (var k:int = 0; k < 15; k++)
				{
					Interface.AddHeroResults(i, icoPath + ico_arr[i], i + k + 1000000, "Результат " + k);
				}
				
			}
		}
		
		private function TestOpenShop(e:MouseEvent):void
		{
			Interface.ShowShop(true);
		}
		
		private function TestHeroChange(e:MouseEvent):void
		{
			var randomHer:int = Math.floor(Math.random() * 4) + 6;
			Interface.SetOurHeroIdententity(randomHer, CurrentGameStatistics.HUMAN_FACTION, 2, iconPathsArr[0], names_arr[0], false);
		}
		
		private function TestShopItems(e:MouseEvent):void
		{
			var index:int = Math.random() * 20;
			numSlotShop = 25;
			
			Interface.SetShopItemsCount(numSlotShop);
			
			for (var n:int = 0; n < numSlotShop; n++)
			{
				var num:int = int(Math.random() * ico_arr.length);
				
				Interface.SetShopItemIcon(n, icoPath + ico_arr[num]);
			}
			
			Interface.SetShopItemState(Math.random() * numSlotShop, Math.random() * 2)
		
		}
		
		private function TestChanneling(e:MouseEvent):void
		{
			SetDataForTeam();
			
			var myTimer:Timer = new Timer(100, 105);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			var t:Number = -0.01;
			
			Interface.setSelectionInfoIcon(icoPath + '01.png', 4, true);
			
			function onTick(e:TimerEvent):void
			{
				Interface.SetHeroParams(1, 4, 200, 1000, 200, 1000, true, 0, t, 5, 5);
				Interface.SetSelectionParams("Человек 1", 6, 200, 1000, 200, 1000, false, t, 1, 1);
				t += 0.01;
			}
		
		}
		
		private function TestErrorMessage(e:MouseEvent):void
		{
			var myTimer:Timer = new Timer(4000, 11);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete);
			myTimer.start();
			var i:int = 0;
			
			function onTick(e:TimerEvent):void
			{
				Interface.ShowErrorMessage(i, true);
				i++;
			}
			
			function onComplete(e:TimerEvent):void
			{
				Interface.ShowErrorMessage(1, false);
			}
		}
		
		private function TestHeroDeath(e:MouseEvent):void
		{
			SetDataForTeam();
			
			if (!heroDead)
				Interface.SetHeroParams(1, 2, 200, 1000, 200, 1000, true, 100, 0.5, 4, 4);
			else
				Interface.SetHeroParams(1, 2, 200, 1000, 200, 1000, true, 0, 0.5, 4, 4);
			
			heroDead = !heroDead;
		}
		
		private function TestShowErrorMessage(e:MouseEvent):void
		{
			Interface.ShowErrorEvent("Левый мессадж, не входящий в энам", true, 3);
		}
		
		private function TestAnnouncement(e:MouseEvent):void
		{
			for (var i:int = 0; i < 5; i++)
			{
				Interface.SetAnnouncementPart(true, icoPath + '05.png', 8, (i == 0 || i == 2 || i == 4) ? "Егерь" + i : "Кенни c именем длинным, длинным,длинным именем" + i, EFraction.ELF_FACTION);
				Interface.SetAnnouncementPart(false, icoPath + '01.png', 3, (i == 0 || i == 1 || i == 3) ? "Егерь" + i : "Плохой,длинный ник с троеточием", EFraction.HUMAN_FACTION);
				Interface.ShowAnnouncement("Они убили кенни! " + i, 2, i);
			}
		
		}
		
		private function TestCripSpownTimer(e:MouseEvent):void
		{
			var time:int = 3610;
			var myTimer:Timer = new Timer(1000, time);
			myTimer.addEventListener(TimerEvent.TIMER, onTick);
			myTimer.start();
			
			var t:int = 560;
			
			function onTick(e:TimerEvent):void
			{
				time--;
				t++;
				Interface.SetGameProgress(0.3, 0.4, t, time);
			}
		}

		var _currentIcon:int = -1;
		
		private function TestPlayerLeft(e:MouseEvent):void
		{
			//	SetDataForTeam();
			if (_currentIcon == -1)
			{
				Interface.PlayerLeft(3, 1);
				_currentIcon = 1;
				return;
			}
			
			if (_currentIcon == 1)
			{
				_currentIcon = 0;
				Interface.PlayerLeft(3, 0);
				return;
			}
			
			
			Interface.PlayerRecconected(3);
			_currentIcon = -1;
			
			
		}
		
		private function TestBarStats(e:MouseEvent):void
		{
			TestFinalStatistic(e);
			
			var time:int = 90;
			var myTimer:Timer = new Timer(3000, time);
			myTimer.addEventListener(TimerEvent.TIMER, onTick);
			myTimer.start();
			
			var arrExp:Array = new Array();
			arrExp = [0, 300, 720, 1360, 2260, 3260];
			
			function onTick(e:TimerEvent):void
			{
				var prevExp:int = Math.round(Math.random() * 1500);
				var earned:int = Math.round(Math.random() * 200);
				
				Interface.SetStatisticExperienceBar(0, 600, arrExp, 100);
			}
		}
		
		private function TestPreferences(e:MouseEvent):void
		{
			var comboArr:Array = [1, 2, 3, 4, 5, 6, 7, 8, 9];
			
			preferenceInterface.AddCheckBoxControl("windowed_tb");
			preferenceInterface.AddCheckBoxControl("leftClick_tb");
			preferenceInterface.AddComboBoxControl("graphic", comboArr);
			preferenceInterface.AddComboBoxControl("resolution", comboArr);
			preferenceInterface.AddSliderControl("sfx_mc", 100);
			preferenceInterface.AddSliderControl("voice_mc", 5);
			preferenceInterface.AddSliderControl("music_mc", 10);
			
			preferenceInterface.SetControlValue("windowed_tb", 0, true);
			preferenceInterface.SetControlValue("leftClick_tb", 1, true);
			preferenceInterface.SetControlValue("graphic", 3, true);
			preferenceInterface.SetControlValue("resolution", 1, true);
			preferenceInterface.SetControlValue("sfx_mc", 30, true);
			preferenceInterface.SetControlValue("voice_mc", 3, true);
			preferenceInterface.SetControlValue("music_mc", 5, true);
		
		/*
		   preferenceInterface.AddCheckBoxControl(1, "checkbox");
		   preferenceInterface.AddComboBoxControl(2, comboArr, "combo");
		   preferenceInterface.AddCheckBoxControl(3, "checkbox");
		   preferenceInterface.AddComboBoxControl(4, comboArr, "combo");
		   preferenceInterface.AddCheckBoxControl(5, "checkbox");
		
		   preferenceInterface.SetControlValue(4, 3, true);
		 */
		}
		
		private function TestLocalization(e:MouseEvent):void
		{
			Localization.CharStarBar_AttackPerSecondText = "test";
			Localization.CharStarBar_AttackSpeedText = "test";
			Localization.CharStarBar_BodyDefenceText = "test";
			Localization.CharStarBar_CritChanseText = "test";
			Localization.CharStarBar_CritMissText = "test";
			Localization.CharStarBar_DamageText = "test";
			Localization.CharStarBar_DexterityText = "test";
			Localization.CharStarBar_EnergyText = "test";
			Localization.CharStatBar_HeaderText = "test";
			Localization.CharStarBar_IntellectText = "test";
			Localization.CharStarBar_LifeText = "test";
			Localization.CharStarBar_MoveSpeedText = "test";
			Localization.CharStarBar_SpiritDefenceText = "test";
			Localization.CharStarBar_StaminaText = "test";
			Localization.CharStarBar_StrengthText = "test";
			Localization.CharStarBar_WillText = "test";
			Localization.CharStarBar_LevelLabelText = "test";
			Localization.DefeatScreen_DefeatText = "test";
			Localization.DetailedStatisticBar_AchivmentsHeaderText = "test";
			Localization.DetailedStatisticBar_ResultsHeaderText = "test";
			Localization.EndGameScreens_CloseBtnLabel = "test";
			Localization.EscMenuBar_ContinueBtnLabel = "test";
			Localization.EscMenuBar_ExitBtnLabel = "test";
			Localization.EscMenuBar_HeaderText = "test";
			Localization.EscMenuBar_OptionsBtnLabel = "test";
			Localization.EscMenuBar_RunToCityBtnLabel = "test";
			Localization.EscMenuBar_StopLevelBtnLabel = "test";
			Localization.EscMenuBar_SurrenderBtnLabel = "test";
			Localization.FinalStatisticBar_CloseBtnLabel = "test";
			Localization.FinalStatisticBar_OpenDetailedStatisticBtnLabel = "test";
			Localization.FinalStatisticBar_OpenStatisticBtnLabel = "test";
			Localization.InventoryBar_HeaderText = "test";
			Localization.PersonalStatisticBar_AchivmentsHeaderText = "test";
			Localization.PersonalStatisticBar_AwardsHeaderText = "test";
			Localization.ShopBar_HeaderText = "test";
			Localization.StatisticBar_CloseBtnLabel = "test";
			Localization.StatisticBar_HeaderText = "test";
			Localization.TalantsBar_HeaderText = "test";
			Localization.VictoryScreen_VictoryText = "test";
			
			//Tooltips-----------------------------------
			Localization.Tooltip_AllWindowsCloseBtn = "test";
			Localization.Tooltip_OpenTeamBtn = "test";
			Localization.Tooltip_CloseTeam = "test";
			Localization.Tooltip_MinimapTimer = "test";
			Localization.Tooltip_MinimapCameraBtn = "test";
			Localization.Tooltip_MinimapToggledCameraBtn = "test";
			Localization.Tooltip_MinimapSignalBtn = "test";
			Localization.Tooltip_ActionBarTalentWindowOn = "test";
			Localization.Tooltip_ActionBarTalentWindowOff = "test";
			Localization.Tooltip_ActionBarCharStatWindowOn = "test";
			Localization.Tooltip_ActionBarCharStatWindowOff = "test";
			Localization.Tooltip_ActionBarInventoryWindowOn = "test";
			Localization.Tooltip_ActionBarInventoryWindowOff = "test";
			Localization.Tooltip_ActionBarStatisticBarWindowOn = "test";
			Localization.Tooltip_ActionBarStatisticBarWindowOff = "test";
			Localization.Tooltip_ActionBarEscMenuWindowOn = "test";
			Localization.Tooltip_StatisticBarKillsIcon = "test";
			Localization.Tooltip_StatisticBarDeathsIcon = "test";
			Localization.Tooltip_StatisticBarAssistIcon = "test"
			Localization.Tooltip_StatisticBarScoreIcon = "test"
			Localization.Tooltip_InventoryBarSortBtn = "test";
			Localization.Tooltip_InventoryBarSplitBtn = "test";
			Localization.Tooltip_NaftaBtn = "test";
			
			Localization.LocalizationComplete();
		}
		
		private function TestSelectionTalentBar(e:MouseEvent):void
		{
			SetSelectionTalantsData();
			
			Interface.SetSelectionTalentBarUnitID(2);
			Interface.ShowHideWindow(EWindows.WINDOW_SELECTIONTALANTBAR);
			
			var myTimer:Timer = new Timer(400, 30);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.start();
			var lev:int = 1;
			function onTick(e:TimerEvent):void
			{
				Interface.SetHeroParams(2, lev, 100, 1000, 200, 2000, true, 0, 0, 5, 5);
				Interface.SetSelectionTalentState(1, 1, 4);
				
				lev++;
			}
		
		}
		
		private function TestImpulseBuffIconChange(e:MouseEvent):void
		{
			Interface.ResetImpulsBuff(icoPath + '02.png');
		}
		
		private function TestChatFilling(e:MouseEvent):void
		{
			var channelText:String = "Сообщение от игрока номер " + chatChannel;
			
			if (chatChannel == 3)
				channelText = "Это очень длинное сообщение, которое как-то тут отображается на несколько строк, вот."
			
			Interface.AddMessage(chatChannel, "[Guild]Player" + chatChannel, channelText);
			
			chatChannel++;
			if (chatChannel == 5)
				chatChannel = 1;
		}
		
		private function TestEnterPress(e:MouseEvent):void
		{
			Interface.EnterPressed();
		}
		
		private function TestPrefChanged(e:MouseEvent):void
		{
			preferenceInterface.ActivateAbilityToChange(true);
		}
		
		private function TestAddAwards(e:MouseEvent):void
		{
			for (var j:int = 0; j < 6; j++)
			{
				Interface.AddOurHeroAward(j, icoPath + ico_arr[j], j, false, true);
			}
			
			var isFirstWin:Boolean = true;
			
			for (var i:int = 0; i < 15; i++)
			{
				Interface.AddOurHeroAward(i, icoPath + ico_arr[i], i, isFirstWin);
				isFirstWin = !isFirstWin;
			}
			
			Interface.FinishAwarding();
		}
		
		private function TestShowHideSelect(e:MouseEvent):void
		{
			var randomHeroe:int = 1 + Math.round(Math.random() * 8);
			
			if (showSelection)
				Interface.setSelectionInfoIcon(icoPath + ico_arr[randomHeroe], randomHeroe, true);
			else
				Interface.setSelectionInfoIcon("", randomHeroe, true);
			showSelection = !showSelection;
		}
		
		private function TestShowVoteMenu(e:MouseEvent):void
		{
			Interface.ShowVoteWindow(120, false);
			
			var count:int = int(Math.random() * 3 + 2);
			
			var conced:int = int(Math.random() * count);
			var decl:int = int(Math.random() * (count - conced));
			
			Interface.SetSurrenderVoteStatus(conced, decl, count);
		}
		
		private function TestHideVoteMenu(e:MouseEvent):void
		{
			Interface.HideVoteWindow();
		}
		
		private function TestLongNames(e:MouseEvent):void
		{
			Interface.SetOurHeroIdententity(1, 1, 1, iconPathsArr[0], names_arr[0], false);
			var male:Boolean = true;
			
			for (var i:int = 1; i < 6; i++)
			{
				Interface.SetFriendlyHeroIdentity(i, names_arr[i - 1] + "1" + names_arr[i - 1] + "2" + names_arr[i - 1] + "3" + names_arr[i - 1] + "4" + names_arr[i - 1] + "5" + names_arr[i - 1] + "6" + names_arr[i - 1], classes_arr[i - 1], icoPath + ico_arr[i - 1], male, true, 120, 1, 1, i * 1000, icoPath + ico_arr[i + 4], "raiting " + i,false,0, iconPathsArr[i - 1], names_arr[i - 1]);
				Interface.SetEnemyHeroIdentity(i + 5, names_arr[i + 4] + "1" + names_arr[i + 4] + "2" + names_arr[i + 4] + "3" + names_arr[i + 4] + "4" + names_arr[i + 4] + "5" + names_arr[i + 4] + "6" + names_arr[i + 4], classes_arr[i + 4], icoPath + ico_arr[i + 4], !male, true, 120, 2, 1, i * 1000, icoPath + ico_arr[i + 4], "raiting " + i,false,0, iconPathsArr[i + 4], names_arr[i + 4]);
				Interface.ShowHeroPortrait(i);
				Interface.ShowHeroPortrait(i + 5);
				Interface.SetHeroParams(i, 1, 20, 1000, 20, 1000, true, 0, 0, i + 10, i + 10);
				Interface.SetHeroParams(i + 5, 1, 1000, 1000, 1000, 1000, false, 0, 0, i + 5, i + 5);
				male = !male;
				
				if (i == 1)
				{
					Interface.SetCharStatUnit(false, 1, icoPath + ico_arr[i - 1], names_arr[i - 1], 1, 1);
				}
			}
			
			var randomHeroe:int = 1 + Math.round(Math.random() * 8);
			
			Interface.setSelectionInfoIcon(icoPath + ico_arr[randomHeroe], randomHeroe, true);
			
			Interface.SetSelectionParams("LongName1LongName2LongName3LongName4LongName5LongName6LongName7", 3, 100, 1000, 100, 10000, true, 0, 3, 3);
		}
		
		private function TestLeftAndBack(e:MouseEvent):void
		{
			if (!isLeftPlayer)
				Interface.PlayerLeft(1);
			else
				Interface.PlayerRecconected(1)
			
			isLeftPlayer = !isLeftPlayer;
		}
		
		private function TestTryExit(e:MouseEvent):void
		{
			Interface.ShowTryExit();
		}
		
		private function TestEgg(e:MouseEvent):void
		{
			Interface.SetMinimapEffect(0, 0);
			Interface.UpdateMinimapEffect(0, 0.5, 0.5);
			
			Interface.SetMinimapEffect(1, 1);
			Interface.UpdateMinimapEffect(1, 0.25, 0.25);
			Interface.SetMinimapEffect(2, 1);
			Interface.UpdateMinimapEffect(2, 0.75, 0.25);
			
			Interface.SetMinimapEffect(3, 2);
			Interface.UpdateMinimapEffect(3, 0.25, 0.75);
			Interface.SetMinimapEffect(4, 2);
			Interface.UpdateMinimapEffect(4, 0.75, 0.75);
		}
		
		private var startTut:Boolean = true;
		
		private var hints:Array = ["hint1", "hint2 Looooooooooooooooooooooooooooooong", "", "hint3", "hint4 Looooooooooooooooooooooooooooooong"];
		private var hintindex:int = 0;
		private var talentSetBlock:Boolean = false;
		
		private var isCinematicShowng:Boolean;
		
		private function TutorialShowUIBlock(e:MouseEvent):void 
		{
			Interface.ShowAllUIBlocks(talentSetBlock);
			talentSetBlock = !talentSetBlock;
		}
		
		private function TestTutorial(e:MouseEvent):void
		{
			trace(Interface.GetNamedDisplayObject(EBubbledElements.BUBBLED_QUEST_TRACKER, false));
			
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.CAMERA_BTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ALERT_BTN, true);
			//	return;
			/*			if (startTut)
			   {
			   Interface.StartCinematic();
			   Interface.ShowCinematicNPC(icoPath + ico_arr[3], "testNPC");
			   Interface.ShowCinematicMessage("Test message? for fun");
			   Interface.ShowCinematicNextButton(true);
			   }
			   else
			   {
			   Interface.StopCinematic();
			   Interface.ShowCinematicNPC("", "");
			   Interface.ShowCinematicMessage("");
			   }
			
			   startTut = !startTut;
			
			 return;*/
			
			SetDataForTeam();
			Interface.setSelectionInfoIcon(icoPath + ico_arr[3], 3, true);
			Interface.SetSelectionParams("LongName1LongName2LongName3LongName4LongName5LongName6LongName7", 3, 100, 1000, 100, 10000, true, 0, 3, 3);
			
			for (var i:int = 1; i < 6; i++)
			{
				Interface.ShowTutorialHeroLevelHighlight(i, true);
				Interface.ShowTutorialHeroLevelHighlight(i + 5, true);
				
			}
			
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.SelectionLevel, true);
			
			return;
			Interface.ShowAllUIBlocks(talentSetBlock);
			
			Interface.ShowUIBlock(ETutorialBlocks.TalentsSetBlock, talentSetBlock);
			
			talentSetBlock = !talentSetBlock;
			
			if (!isCinematicShowng)
			{
				Interface.StartCinematic();
				Interface.ShowCinematicNPC(icoPath + ico_arr[2], hints[2]);
				Interface.ShowCinematicNPC(icoPath + ico_arr[3], hints[4]);
			}
			else
				Interface.StopCinematic();
			
			isCinematicShowng = !isCinematicShowng;
			
			return;
			if (hintindex == hints.length)
				hintindex = 0;
			
			Interface.SetQuestHintLine(hints[hintindex]);
			
			hintindex++;
			return;
			
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.CAMERA_BTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ALERT_BTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.HEALTHBAR, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.MANABAR, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.DOWNLEVELHIGHLIGHT, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.TOPLEVELHIGHLIGHT, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ACTIONBARCHARSTATBTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ACTIONBARESCBTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ACTIONBARINVENTORYBTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ACTIONBARSTATISTICBTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.ACTIONBARTALENTBTN, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.TALENT_SET_SECOND_LEVEl, true);
			Interface.ShowTutorialElementHighLight(ETutorialHighlitedObjects.PortalButton, true);
			
			return;
			Interface.ShowTutorialHeroHighlight(3, true);
			
			var highlightTimer:Timer = new Timer(3000, 11);
			var index:int = 0;
			highlightTimer.addEventListener(TimerEvent.TIMER, OnHighlightTick);
			highlightTimer.start();
			
			function OnHighlightTick(e:TimerEvent):void
			{
				Interface.ShowTutorialActionBarItemHighlight(index, true);
				Interface.ShowTutorialShopItemHighlight(index, true);
				Interface.ShowTutorialInventoryItemHighlight(index, true);
				Interface.ShowTutorialTalentHighlight(index, 1, true)
				
				Interface.ShowTutorialActionBarItemHighlight(index - 1, false);
				Interface.ShowTutorialShopItemHighlight(index - 1, false);
				Interface.ShowTutorialInventoryItemHighlight(index - 1, false);
				Interface.ShowTutorialTalentHighlight(index - 1, 1, false)
				index++;
			}
			
			SetDataForTeam();
			Interface.ShowAllUIBlocks(false);
			
			var myTimer:Timer = new Timer(400, tutorialBlocks.length);
			myTimer.addEventListener(TimerEvent.TIMER, onTick)
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnComplete)
			myTimer.start();
			
			var npcTimer:Timer = new Timer(600, 7);
			npcTimer.addEventListener(TimerEvent.TIMER, onNpcTick)
			//var cinematicDialogTimer:Timer = new Timer(1, 5);
			//cinematicDialogTimer.addEventListener(TimerEvent.TIMER, onCinematicTick)
			
			var showNpc:Boolean = false;
			var count:int = 0;
			
			function onTick(e:TimerEvent):void
			{
				if (count < tutorialBlocks.length)
					Interface.ShowUIBlock(tutorialBlocks[count], true);
				
				count++;
			}
			
			Interface.ShowUIBlock(ETutorialBlocks.PlayerHeroBlock, true);
			Interface.ShowUIBlock(ETutorialBlocks.TopPlayerBlock, true);
			Interface.ShowUIBlock(ETutorialBlocks.ChatBlock, false);
			
			function OnComplete(e:TimerEvent):void
			{
				npcTimer.start();
			}
			
			function onNpcTick(e:TimerEvent):void
			{
				if (showNpc)
					Interface.ShowNPC(icoPath + ico_arr[3], "testNPC")
				else
					Interface.HideNPC();
				
				showNpc = !showNpc;
			}
		}
		
		private var questIndex:int = 0;
		private var priority:Boolean;
		
		private function TestQuestTrackerAdd(e:MouseEvent):void
		{
			priority = !priority;
			questIndex++;
			
			Interface.AddQuest(questIndex, priority, "Короткий текст ", 10);
			Interface.UpdateQuest(questIndex, 5);
			Interface.UpdateQuestText(questIndex, "Длинный текст на несколько строчек с целью проверить анимацию получения и удаления");
		}
		
		private function TestQuestTrackerRemove(e:MouseEvent):void
		{
			Interface.RemoveQuest(questIndex);
			questIndex--;
			if (questIndex < 0)
				questIndex = 0;
		}
		
		private var showBubble:Boolean = true;
		
		private function TestBubbleShowing(e:MouseEvent):void
		{
			Interface.ShowBubble(EBubbledElements.BUBBLED_BOTTLE, showBubble, "За убийство врагов герой получает прайм, за прайм герой может активировать таланты."); //EBubbledElements.BUBBLED_BOTTLE);
			Interface.ShowBubble(EBubbledElements.IMPULSETALENT, showBubble, EBubbledElements.IMPULSETALENT);
			Interface.ShowBubble(EBubbledElements.TALENT_SET_SECOND_LEVEl, showBubble, "Обратите внимание, теперь вам доступна вторая строка талантов. Чем выше строка, тем сильнее таланты."); // EBubbledElements.BUBBLED_TALENT_SET_SECOND_LEVEl);
			
			Interface.ShowBubble(EBubbledElements.ACTIONBARCHARSTATBTN, showBubble, EBubbledElements.ACTIONBARCHARSTATBTN);
			Interface.ShowBubble(EBubbledElements.ACTIONBARESCBTN, showBubble, EBubbledElements.ACTIONBARESCBTN);
			Interface.ShowBubble(EBubbledElements.ACTIONBARINVENTORYBTN, showBubble, EBubbledElements.ACTIONBARINVENTORYBTN);
			Interface.ShowBubble(EBubbledElements.ACTIONBARSTATISTICBTN, showBubble, EBubbledElements.ACTIONBARSTATISTICBTN);
			Interface.ShowBubble(EBubbledElements.ACTIONBARTALENTBTN, showBubble, EBubbledElements.ACTIONBARTALENTBTN);
			Interface.ShowBubble(EBubbledElements.BUBBLED_QUEST_TRACKER, showBubble, EBubbledElements.BUBBLED_QUEST_TRACKER);
			Interface.ShowBubble(EBubbledElements.BUBBLED_SIGNAL_BUTTON, showBubble, EBubbledElements.BUBBLED_SIGNAL_BUTTON);
			Interface.ShowBubble(EBubbledElements.CAMERA_BTN, showBubble, EBubbledElements.CAMERA_BTN);
			Interface.ShowBubble(EBubbledElements.BUBBLED_CHANNELIN_BAR, showBubble, EBubbledElements.BUBBLED_CHANNELIN_BAR);
			Interface.ShowBubble(ETutorialHighlitedObjects.PortalButton, showBubble, ETutorialHighlitedObjects.PortalButton);
			Interface.ShowTalentBubble(1, 4, showBubble, "TalentSet", EBubbleViewType.LeftClickElement);
			Interface.ShowActionBarButtonBubble(3, showBubble, "ActionBarButton");
			Interface.ShowShopBarButtonBubble(6, showBubble, "ShopBarButton", EBubbleViewType.RightClickElement);
			Interface.ShowInventoryBarButtonBubble(7, showBubble, "InventoryButton", EBubbleViewType.NextButtonElement);
			Interface.ShowHeroBubble(3, showBubble, "HeroBubble", EBubbleViewType.RightClickElement);
			Interface.ShowHeroBubble(1, showBubble, "HeroBubble", EBubbleViewType.RightClickElement);
			Interface.ShowHeroBubble(6, showBubble, "HeroBubble", EBubbleViewType.RightClickElement);
			showBubble = !showBubble;
		}
		
		private var hintType:int = 0;
		
		private function TestHintlineShowing(e:MouseEvent):void
		{
			
			var text:String = "";
			switch (hintType % 4)
			{
				case 0: 
					text = "test text sdfsdfsdfsdfsdfdsfsdfsd_[EOL]";
					break;
				case 1: 
					text = "12";
					break;
				case 2: 
					text = "text";
					break;
				case 3: 
					text = " text text";
					break;
			}
			Interface.SetQuestHintLine(text, hintType < 4 ? "None" : "LeftClick");
			hintType = (hintType + 1) % 8;
		}
		
		private function TestPortalButton(e:MouseEvent):void
		{
			var maxCoold:Number = 80;
			
			var t:Number = maxCoold;
			
			var myTimer1:Timer = new Timer(500, 20);
			myTimer1.addEventListener(TimerEvent.TIMER, onTick)
			myTimer1.addEventListener(TimerEvent.TIMER_COMPLETE, onComlplete)
			myTimer1.start();
			
			function onTick(e:TimerEvent):void
			{
				var count:int = Math.round(Math.random() * 10 - 0.5);
				var state:int = Math.round(Math.random() * 6);
				Interface.SetPortalStatus(state, 0, 100);
			}
			
			function onComlplete(e:TimerEvent):void
			{
				var myTimer:Timer = new Timer(300, t);
				myTimer.addEventListener(TimerEvent.TIMER, onTick)
				myTimer.start();
				
				function onTick(e:TimerEvent):void
				{
					t--;
					Interface.SetGlobalCooldown(t, 80);
				}
			}
		}
		
		private function TestTalentOnMana(e:MouseEvent):void
		{
			SetTalantsData();
			
			Interface.SetTalentStatus(0, 0, 3, 0, 0, false);
		}
		
		private var showCinematicSkip:Boolean = false;
		
		private function HideShowCinematicSkipButton(e:MouseEvent):void
		{
			showCinematicSkip = !showCinematicSkip;
			
			Interface.ShowCinematicNextButton(showCinematicSkip);
		}
		
		private var inCinematic:Boolean = false;
		
		private function HideShowCinematic(e:MouseEvent):void
		{
			inCinematic = !inCinematic;
			
			if (inCinematic)
			{
				Interface.StartCinematic();
				Interface.ShowCinematicNPC(icoPath + ico_arr[3], "testNPC");
				Interface.ShowCinematicMessage("Test message? for fun");
			}
			else
				Interface.StopCinematic();
		}
		
		private function TestDragonvald(e:MouseEvent):void
		{
			Interface.ShowCTEUi(true);
			
			var timer:Timer = new Timer(600, 50);
			timer.addEventListener(TimerEvent.TIMER, OnTick);
			timer.start();
			var fraction:Boolean = true;
			
			function OnTick(e:TimerEvent):void
			{
				Interface.SetCTEAltarStatus(fraction ? 1 : 2, int(Math.random() * 100), 100, Math.random() * 6);
				fraction = !fraction;
			}
		}
		
		private function TestMessageBox(e:MouseEvent):void
		{
			Interface.ShowMessageBox("Тест заголовка", "Рыба рыба рыба рыба рыба рыба рыба рыба рыба рыба рыба", false);
		}
		private var lock:Boolean = true;
		
		private function TestLockActionBar(e:MouseEvent):void
		{
			Interface.LockActionBar(lock);
			lock = !lock;
		}
		
		private function TestChangeMyHeroRaiting(e:MouseEvent):void
		{
			Interface.SetAwardDeltaRaiting(10, icoPath + ico_arr[1], "new Tooltip");
		}
		
		public function TestFirstWinState(e:MouseEvent):void
		{
			Interface.SetFirstWin(icoPath + ico_arr[1], "первая победа, мужииик");
		}
		
		private var heroId:int = 0;
		private var fraction:int = 1;
		private var redMates:Array = [2, 3, 5, 6];
		private var blueMates:Array = [0, 1, 4, 7];
		
		public function TestChangeHero(e:MouseEvent):void
		{
			Interface.SetOurHeroIdententity(heroId, fraction, EFraction.ELF_FACTION, iconPathsArr[0], names_arr[0], false);
			var male:Boolean = true;
			
			for (var j:int = 0; j < blueMates.length; j++)
			{
				Interface.SetFriendlyHeroIdentity(fraction == 1 ? blueMates[j] : redMates[j], names_arr[j + 1 - 1] + names_arr[j + 1 - 1] + names_arr[j + 1 - 1] + names_arr[j + 1 - 1], classes_arr[j + 1 - 1], icoPath + ico_arr[j + 1 - 1], male, true, 120, fraction == 1 ? 1 : 2, 1, 100, icoPath + ico_arr[j + 1 - 1], "tooltip " + j,true,0, iconPathsArr[j + 1 - 1], names_arr[j + 1 - 1]);
				Interface.SetEnemyHeroIdentity(fraction == 1 ? redMates[j] : blueMates[j], names_arr[j + 5 - 1] + names_arr[j + 5 - 1] + names_arr[j + 5 - 1] + names_arr[j + 5 - 1], classes_arr[j + 5 - 1], icoPath + ico_arr[j + 5 - 1], male, true, 120, fraction == 1 ? 2 : 1, 1, 100, icoPath + ico_arr[j + 5 - 1], "tooltip " + j + 5,true,0, iconPathsArr[j + 5 - 1], names_arr[j + 5 - 1]);
				Interface.ShowHeroPortrait(redMates[j]);
				Interface.ShowHeroPortrait(blueMates[j]);
			}
			
			heroId = heroId == 0 ? 2 : 0;
			fraction = fraction == 1 ? 2 : 1;
		}
		private var activeTalentTest:Boolean;
		
		public function TestChangeTalentIsActiveState(e:MouseEvent):void
		{
			SetTalantsData();
			
			Interface.SetTalentIcon(0, 0, icoPath + ico_arr[0], "", activeTalentTest, 2, 1, false, 100);
			
			activeTalentTest = !activeTalentTest;
		}
		
		public function TestPweBack(e:MouseEvent):void
		{
			Interface.SetPveBacks(icoPath + ico_arr[1], icoPath + ico_arr[2], icoPath + ico_arr[3]);
			Interface.SetOurHeroIdententity(1, 1, 1, iconPathsArr[0], names_arr[0], false);
			Interface.SetFriendlyHeroIdentity(1, "name", "class1", icoPath + ico_arr[5], true, false, 100, 1, 1, 100, icoPath + ico_arr[6], "tooltip", true,0, iconPathsArr[1], names_arr[1]);
		}
		
		private var channelId:int = 1;
		
		private function TestChangeChannel(e:MouseEvent):void
		{
			if (channelId == 1)
				channelId = 2;
			else
				channelId = 1;
			
			Interface.OpenChanel(channelId);
		}
		
		private function TutorialQuestRemoveAndCinematic(e:MouseEvent):void
		{
			for (var i:int = 0; i < 2; i++)
			{
				Interface.RemoveQuest(questIndex);
				questIndex--;
				if (questIndex < 0)
					questIndex = 0;
			}
		
		/*inCinematic = !inCinematic;
		
		   if (inCinematic)
		   {
		   Interface.StartCinematic();
		   Interface.ShowCinematicNPC(icoPath + ico_arr[3], "testNPC");
		   Interface.ShowCinematicMessage("Test message? for fun");
		   }
		   else
		 Interface.StopCinematic();*/
		}
	
		
		private var questHintShowCount:int = 1; 
		private var iconCount :int = 0;
		public function ShowQuestHint(e:MouseEvent):void
		{
			Interface.ShowQuestHint(questHintShowCount.toString(), "Подсказка номер " + questHintShowCount, "Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount +"Текст подсказки " + questHintShowCount , icoPath + ico_arr[iconCount]);
			questHintShowCount++;
			iconCount++;
			if (iconCount >= ico_arr.length)
				iconCount = 0;
		}
		
		
		private var buttonForDisable:Array = [ETutorialBlocks.EscMenuOptionsButton, ETutorialBlocks.EscMenuSurrenderButton, ETutorialBlocks.EscMenuRunToCastleButton,
											  ETutorialBlocks.EscMenuExitButton,ETutorialBlocks.EscMenuStopZumaLevelButton,ETutorialBlocks.EscMenuContinueButton]
		
		private var curIndex:int = 0;
		public function TestEscMenuButtonDisable(e:MouseEvent):void
		{
			Interface.ShowAllUIBlocks(true);
			Interface.ShowUIBlock(buttonForDisable[curIndex], false);
			
			curIndex++;
			if (curIndex >= buttonForDisable.length)
				curIndex = 0;
		}
		
	}
}
