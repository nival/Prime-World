package LoaderSources
{
	import Enums.EFraction;
	import flash.events.Event;
	import fl.controls.Button;
	import flash.events.MouseEvent;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class LoaderInterfaceTest
	{
		private var loaderInterface:LoaderInterface
		private var main:LoaderMain;
		private var names_arr:Array = [];
		private var ico_arr:Array = [];
		private var icoPath:String = 'art/ico/flags/';
		private var classes_arr:Array = [];
		private var chatChannel:int = 1;
		
		private var buttons:Array = new Array();
		
		public function LoaderInterfaceTest(_loader:LoaderInterface,_mainWindow:LoaderMain)
		{
			names_arr = ['[NIN]FragnomoreMoreMore','[party]patrik2','даркДрагон3','Warband4','Панамка5','[Nrds]Greck6','Lenin7','[WWWWW]Тор8','папай маряк9','[linnn]Linda10'];
			ico_arr = ['01.png','02.png','03.png','04.png','05.png','06.png','07.png','08.png','09.png','10.png','11.png','12.png','13.png','14.png'];
			classes_arr = ['класс1', 'класс2', 'класс3', 'класс4', 'класс5', 'класс6', 'класс7', 'класс8', 'класс9', 'класс10']
			
			loaderInterface = _loader;
			main = _mainWindow;
			FSCommands.testing = true;
			var forces:Array = [0, 110, 200];
			var colors:Array = [0xffffff, 0xff0000, 0x000000];
					
			loaderInterface.SetForceColors(forces, colors);
			loaderInterface.AddChannel(1, "Chanel1", 0xffffff, true, true,true);
			loaderInterface.AddChannel(2, "Chanel2", 0xff0000, false, true,true);
			loaderInterface.AddChannel(3, "Chanel3", 0x00ff00, true, false,true) ;
			loaderInterface.AddChannel(4, "Chanel4", 0x000000, true, true, true);
			
			loaderInterface.SetDefaultChannel(1);
			loaderInterface.AddChannelShortCut(1, "s");
			loaderInterface.AddChannelShortCut(2, "sss");
			loaderInterface.AddChannelShortCut(3, "5");
			loaderInterface.AddChannelShortCut(4, "1");
			
			GenerateButton("Протестировать загрузку игроков", TestPlayers);
			GenerateButton("Локализация", TestLocalization);
			GenerateButton( 'Добавить сообщение в чат', TestChatFilling);
			GenerateButton('Нажать Enter', TestEnterPress);
			GenerateButton('добавить каналы', AddChannels);
			GenerateButton( 'добавить модификаторы', TestModeDescription);
			GenerateButton( 'Поменять статус', TestLoaderState);
			GenerateButton('Новичок - не новичок', TestNovice);
			GenerateButton('Тестировать премиум', TestHeroPremium);
			GenerateButton('Тестировать компонент мощи команд', TestTeamForce);
		}
		
		private function GenerateButton(label:String, listener:Function):void 
		{
			var newButton:Button = new Button();
			newButton.label = label;
			
			AddButtonFunction(newButton, buttons.length==0?null:buttons[buttons.length-1]);
			
			function AddButtonFunction(NewButt:Button,oldButt:Button):void
			{
				if (oldButt == null) 
				{
					NewButt.y = 230;
				}
				else 
				{
					NewButt.y = oldButt.y + 20;
					NewButt.x = oldButt.x;
				}
				if (NewButt.y >= 700) 
				{ 
					NewButt.y  = 130;
					NewButt.x = oldButt.x+220;
				}
				
				buttons.push(NewButt);
				NewButt.width = 200;
				main.addChild(NewButt);
			}
			
			newButton.addEventListener(MouseEvent.CLICK, listener);
			
		}
		
		
		private function TestPlayers(e:MouseEvent):void
		{
			loaderInterface.SetTip("Тестовый совет, тупо поржать");
			
			var male:Boolean = true;
			
			loaderInterface.SetMapBack(icoPath + ico_arr[0], icoPath + ico_arr[5]);
			loaderInterface.SetPlayersFaction(2, 2);
			loaderInterface.SetOurHeroId(3, EFraction.ELF_FACTION);
			
			
			loaderInterface.SetLocales(icoPath + ico_arr[2], "MyTeam", icoPath + ico_arr[3], "enemy");
			
			for (var i:int = 0; i < 10; i++ )
			{
			loaderInterface.SetHeroIdentity(i, i % 2 + 1, names_arr[i], icoPath + ico_arr[i], 4, male, icoPath + ico_arr[i], 5, icoPath + ico_arr[i], names_arr[i]);
				loaderInterface.SetHeroLevel(i, i);
				loaderInterface.SetHeroForce(i, i * 25);
				loaderInterface.SetHeroRaiting(i, 1200+i*100,i*10+0.5,-(i*10+5)+0.3, false,icoPath + ico_arr[i],"rank "+i);
				male = !male;
			}
			
		//	loaderInterface.SetOurHeroId(3 , EFraction.ELF_FACTION);
			
			var myTimer:Timer = new Timer(100, 101);
			myTimer.addEventListener(TimerEvent.TIMER, onTick);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete);
			myTimer.start();
			var t:Number = 0;
			
			function onTick(e:TimerEvent):void
			{ 
				loaderInterface.SetHeroLoadProgress(0, t,false);
				loaderInterface.SetHeroLoadProgress(1, t,false);
				loaderInterface.SetHeroLoadProgress(2, t,false);
				loaderInterface.SetHeroLoadProgress(3, t,false);
				loaderInterface.SetHeroLoadProgress(4, t,false);
				loaderInterface.SetHeroLoadProgress(5, t,false);
				loaderInterface.SetHeroLoadProgress(6, t,false);
				loaderInterface.SetHeroLoadProgress(7, t,false);
				loaderInterface.SetHeroLoadProgress(8, t,false);
				loaderInterface.SetHeroLoadProgress(9, t,false);
				loaderInterface.SetHeroLoadProgress(10, t,false);				
				t++; 
			}
			
			function onComplete(e:TimerEvent):void
			{
				loaderInterface.SetHeroLoadProgress(2, 0,true);
			}
		}
		
		private function TestLocalization(e:MouseEvent):void 
		{
			LoaderLocalization.BotName = "Boooooooooooooot with long name";
			LoaderLocalization.ContextMenu_Ignore = "Ignore"
			LoaderLocalization.ContextMenu_RemoveIgnore
			LoaderLocalization.LocalizationComplete()
		}
		
		private function TestChatFilling(e:MouseEvent):void
		{
			var channelText:String = "Сообщение от игрока номер " + chatChannel;
			
			if (chatChannel == 3)
				channelText="Это очень длинное сообщение, которое как-то тут отображается на несколько строк, вот."
			
			loaderInterface.AddMessage(chatChannel, "[Guild]Player" + chatChannel,channelText);
			
			chatChannel++;
			if (chatChannel == 5)
				chatChannel = 1;
		}
		
		private function TestEnterPress(e:MouseEvent):void 
		{
			loaderInterface.EnterPressed();
		}
		
		
		private function AddChannels(e:MouseEvent):void 
		{
			loaderInterface.AddChannel(1, "Chanel1", 0xffffff, true, true,true);
			loaderInterface.AddChannel(2, "Chanel2", 0xff0000, false, true,true);
			loaderInterface.AddChannel(3, "Chanel3", 0x00ff00, true, false,true);
			loaderInterface.AddChannel(4, "Chanel4", 0x000000, true, true, true);
			loaderInterface.AddChannel(5, "Chanel5", 0x000000, true, true, false);
			loaderInterface.AddChannel(6, "Chanel6", 0x000000, true, true, false);
			loaderInterface.SetDefaultChannel(1);
			loaderInterface.AddChannelShortCut(1, "s");
			loaderInterface.AddChannelShortCut(2, "sss");
			loaderInterface.AddChannelShortCut(3, "5");
			loaderInterface.AddChannelShortCut(4, "1");
		}
		
		private function TestModeDescription(e:MouseEvent):void 
		{
			loaderInterface.AddModeDescription(icoPath + ico_arr[1], 1);
			loaderInterface.AddModeDescription(icoPath + ico_arr[2], 2);
		//	loaderInterface.AddModeDescription(icoPath + ico_arr[3], 3);
		}
		
		private var statusesList:Array = ["Новый статус","Новый статус Новый статусНовый статусНовый статус","Новый статус","Новый статусНовый статусНовый статус","Новый статус"]
		
		private function TestLoaderState(e:MouseEvent):void 
		{
			var index:int = 0;
			
			loaderInterface.SetLoadingState(true);
			
			var myTimer:Timer = new Timer(600, statusesList.length);
			myTimer.addEventListener(TimerEvent.TIMER, onTick);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onComplete);
			myTimer.start();
			
			function onTick(e:TimerEvent):void
			{
				loaderInterface.SetLoadingStatusText(statusesList[(index < statusesList.length? index:0)]);
				index++;
			}
			
			function onComplete(e:TimerEvent):void
			{
				loaderInterface.SetLoadingState(false);
			}
		}
		
		private var isNovice:Boolean;
		private function TestNovice(e:MouseEvent):void 
		{
			loaderInterface.SetHeroRaiting(3, 100, 10, 1000, true, icoPath + ico_arr[1], "rank 1");
			isNovice = !isNovice;
		}
		
		private function TestHeroPremium(e:MouseEvent):void 
		{
			loaderInterface.SetHeroPremium(0, true, 1);
			loaderInterface.SetHeroPremium(1, false, 1);
			loaderInterface.SetHeroPremium(2, true, 1);
			loaderInterface.SetHeroPremium(3, true, 1);
			loaderInterface.SetHeroPremium(4, false, 1);
			loaderInterface.SetHeroPremium(5, true, 2);
			loaderInterface.SetHeroPremium(6, false, 2);
			loaderInterface.SetHeroPremium(7, false, 2);
			loaderInterface.SetHeroPremium(8, true, 2);
			loaderInterface.SetHeroPremium(9, false, 2);
		}
		private function TestTeamForce(e:MouseEvent):void 
		{
			loaderInterface.SetTeamForce("100500", "100500");
			//loaderInterface.SetTeamForce();
		}
		
	}
}