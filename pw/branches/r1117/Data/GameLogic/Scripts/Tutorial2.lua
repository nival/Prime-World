-- Tutorial Mission 2 script v.05 (by Grey)
 -- Таблица скриптовых элементов на карте
 -- В начале имени всегда "M2_", в конце если надо "_D"/"_A", которое указывает на то, в чьей версии скрипта используется область
 -- M2_Flag1_B, M2_Flag1_А, M2_FlagMiddle - флаги
 -- M2_Point1_Middle - регион в центр, радиус 17
 -- M2_EnemyHero1_A, M2_EnemyHero1_D - место спавно 1го вражеского героя
 -- M2_Shop_D, M2_Shop_A - магазины
 

include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

M_PI2 = 1.57

function Init() --Отключаем ненужные объекты и спавны
    --Вызовы флеша здесь ЗАПРЕЩЕНЫ!!!

	LuaGroupHide( "Mission1", true )
	LuaSetSpawnCreeps( false )
	--LuaCreatureHide( "01", true ) -- hide another ally hero
	AddStateEnd( BeginSpawnCreeps )
	
	rotateTime = 0.7
	rotateTimeTunder = 0.5 -- cпециальное время разворота героя, если герой = Гром
	creepCap = 14 -- лимит на кол-во юнитов 
	debugModeOn = false
	debug1Intro = false -- Первый синематик
	debug2Intro = false -- Второй синематик
	debug1Jaba = false -- сцена с Жабой
	debug1AllyHeal = false -- сцена с лечащимся союзником
	debug1BuyPotion = false -- просим купить поушен
	debugTerrainOn = false -- все про флаги
	debugMidPointFight = false -- бой у центрального флага
	debugRatCatcherDead = true -- убийство Крысолова
	debugTalentsBuy = false -- все про покупку талантов
	debugFirstTowerScene = false -- рассказываем про сиджа и лиса радуется
	debugFirstFightVsHero = true -- убийство двух героев
	debugSecondFightVsHero = true -- убийство третьего героя
	LuaEnableEventLogging (true)
--	StartTrigger( Obj7_CheckFlagIsRising )
	-- это добавил Семашко, чтобы во второй миссии ничего не сломалось
	--LuaGroupHide( "TM1_BlockAreaCentral", false )
end  

function BeginSpawnCreeps ( some ) -- НАЧАЛСЯ СКРИПТ ВТОРОЙ ТЕСТОВОЙ КАРТЫ
	LuaDebugTrace ("   ------ НАЧАЛСЯ СКРИПТ ВТОРОЙ ТЕСТОВОЙ КАРТЫ (его делает Крукович если что) ")
-- Изменения переменных в зависимости от фракции игрока
	-- select by player faction
	FACTION_PLAYER = LuaGetLocalFaction()
	FACTION_ENEMY = 3 - FACTION_PLAYER
	local function selectByFaction( a, b )
		if ( FACTION_PLAYER == 1 ) then
			return a
		else
			return b
		end
	end	

	local function generateCreepNames( name, wave, count )
		local arr = {}
		for i = 1, count do
			arr[i] = name .. "_w" .. wave .. "_c" .. i
		end
		return arr
	end
	
	local function FlagIsLocal ( line, flagNumber ) -- функция проверят, что указанный флаг принадлежит фракции игрока
		if LuaFlagGetFaction( line, flagNumber) == LuaGetLocalFaction() then
			LuaDebugTrace("DEBUG: этот флаг принадлежит игроку!")
			return true
		end
		return false
	end
-- конец

if true then-- БЛОК ПОДГОТОВКИ, расставляем юниты, прячем всех врагов.
	LuaSetAchievmentsEnabled( false )

    LuaDebugTrace( "DEBUG: БЛОК ПОДГОТОВКИ" )
	ALLY_HERO = selectByFaction( "02", "12" )
	ALLY_HERO_1 = selectByFaction( "01", "11" )
	ENEMY_HERO_1 = selectByFaction( "10", "00" )
	ENEMY_HERO_2 = selectByFaction( "11", "01" )
	ENEMY_HERO_3 = selectByFaction( "12", "02" )
	ENEMY_TOWER_1 = selectByFaction( "TowerB1_m2", "TowerA1_m2" )
	ENEMY_TOWER_2 = selectByFaction( "TowerB2_m2", "TowerA2_m2" )
	ALLY_TOWER_1 = selectByFaction( "TowerA1_m2", "TowerB1_m2" )
	ALLY_TOWER_2 = selectByFaction( "TowerB1_m2", "TowerA1_m2" )
	ENEMY_BARRACKS = selectByFaction( "BarracksB_m2", "BarracksA_m2" )
	ENEMY_BARRACKS2 = selectByFaction( "BarrackB2", "BarrackA2" )
	ALLY_BARRACKS2 = selectByFaction( "BarrackA2", "BarrackB2" )
	ALLY_MAINBUILDING = selectByFaction( "MainA" , "MainB" )
	ALLY_MAIN_SPAWNER = selectByFaction( "CreepsA", "CreepsB" )
	ENEMY_MAIN_SPAWNER = selectByFaction( "CreepsB", "CreepsA" )	
	ENEMY_MAINBUILDING = selectByFaction( "MainB", "MainA" )
	ENEMY_CREEP_MELEE = selectByFaction( "CreepMeleeB", "CreepMeleeA" )
	ENEMY_CREEP_RANGED = selectByFaction( "CreepRangeB", "CreepRangeA" )
	ENEMY_CREEP_SIEGE = selectByFaction( "CreepSiegeB", "CreepSiegeA" )
	ALLY_CREEP_SIEGE = selectByFaction( "CreepSiegeA", "CreepSiegeB" )
	ALLY_Secondery_LockTiles = selectByFaction( "TM1_BlockArea1_D", "TM1_BlockArea1_A" )
	ENEMY_Secondery_LockTiles = selectByFaction( "TM1_BlockArea1_A", "TM1_BlockArea1_D" )
	ENEMY_HERO_TOWER = selectByFaction( "EnemyHeroMoveB_m2", "EnemyHeroMoveA_m2" )

-- Прячем Лису и Жабу, пока летает камера
	LuaCreatureHide( ALLY_HERO_1, true ) 
	LuaCreatureHide( ALLY_HERO, true ) -- прячем ненужных героев
	LuaCreatureHide( ENEMY_HERO_2, true )
-- конец

	allyShop = selectByFaction ( "M2_Shop_D", "M2_Shop_A" )
	-- Опредиления для квестов
		KillEnemyRatcatcher = selectByFaction("TM2_Q23as", "TM2_Q23ds")
		KillEnemyFrog = selectByFaction("TM2_Q02as", "TM2_Q02ds")
		KillSiege = selectByFaction("TM2_Q35as", "TM2_Q35ds")
		KillEnemyRockman = selectByFaction("TM2_Q36ds", "TM2_Q36as")
		QuestMainbuilding = selectByFaction("TM2_Q34dp", "TM2_Q34ap")
	-- Конец
	_FlagToMark = selectByFaction ("M2_Flag1_A", "M2_Flag1_B")
	_FlagEnemy = selectByFaction ("M2_Flag1_B", "M2_Flag1_A")
	FlagPosition = GetScriptArea( selectByFaction ("M2_FirstFlagPostion_A", "M2_FirstFlagPostion_B") )
--	enemyHero1_Pos = GetScriptArea( selectByFaction( "M2_EnemyHero1_D", "M2_EnemyHero1_A" ) )  
	LuaDebugTrace( "DEBUG: КОНЕЦ БЛОК ПОДГОТОВКИ" )

	LuaSetUnitStat( "FountainA", 2, 0 )
	LuaSetUnitStat( "FountainB", 2, 0 )
	LuaSetUnitStat( "TowerA1_m2", 0, 1200 )
	LuaSetUnitStat( "TowerB1_m2", 0, 1200 )
	LuaSetUnitStat( "TowerA2_m2", 0, 2000 )
	LuaSetUnitStat( "TowerB2_m2", 0, 2000 )
	LuaSetUnitStat( "BarracksB_m2", 0, 1000 )
	LuaSetUnitStat( "BarracksA_m2", 0, 1000 )
	LuaSetUnitStat( "MainA", 0, 2000 )
	LuaSetUnitStat( "MainB", 0, 2000 )
	
	-- Запоминаем, что в начале игры герои не могут умирать
if not debugModeOn or debugRatCatcherDead then 
	heroesImmortal = true
	LuaUnitAddFlag( ALLY_HERO_1, ForbidDeath )
	LuaUnitAddFlag( "local", ForbidDeath )
	StartTrigger( UnitImmortalCheat, ALLY_HERO_1, 20)
	StartTrigger( UnitImmortalCheat, "local", 20)
end
	
	-- запоминаем точки для камеры
	cinemaPos1 = GetScriptArea( selectByFaction( "RatCamB_m2", "RatCamA_m2" ) )
	cinemaPos2 = GetScriptArea( selectByFaction( "ObjectiveA2_m2", "ObjectiveB2_m2" ) )
	cinemaPos3 = GetScriptArea( selectByFaction( "HeroStartA1_m2", "HeroStartB1_m2" ) )
	Obj3Pos = GetScriptArea( selectByFaction( "M2_2EnemyHero1_A", "M2_2EnemyHero1_D" ) )
	Obj2Pos = GetScriptArea( selectByFaction( "M2_EnemyHero1_A", "M2_EnemyHero1_D" ) )
	Obj4Pos = GetScriptArea( selectByFaction( "AllyHeroMoveB_m2", "AllyHeroMoveA_m2" ) )
	cinemaPos4 = GetScriptArea( selectByFaction( "CinematicHeroA_m2", "CinematicHeroB_m2" ) )
	cinemaPos5 = GetScriptArea( selectByFaction( "CinematicAllyA_m2", "CinematicAllyB_m2" ) )
	cinemaPos6 = GetScriptArea( selectByFaction("HeroShopA_m2" , "HeroShopB_m2") )
	cinemaPos7 = GetScriptArea( selectByFaction( "TowerZone1_B_m2", "TowerZone1_A_m2" ) )
	cinemaPos8 = GetScriptArea( selectByFaction( "CinematicMainBuilding_A", "CinematicMainBuilding_B" ) )
	cinemaPos9 = GetScriptArea( selectByFaction( "M2_Flag1Check_A", "M2_Flag1Check_B" ) )
	cinemaPos10 = GetScriptArea( selectByFaction( "ObjectiveA3_m2", "ObjectiveB3_m2" ) )
	cinemaPos11 = GetScriptArea( selectByFaction( "M2_CamFlag1_A", "M2_CamFlag1_B") )
	cinemaPos12 = GetScriptArea( selectByFaction( "ObjectiveA3_m1", "ObjectiveB3_m1" ) ) -- место рождения героев на фонтане
	EnemyHeroMovePos = GetScriptArea( selectByFaction( "EnemyHeroMoveB_m2", "EnemyHeroMoveA_m2" ) )
	PointMiddle = GetScriptArea("M2_WaitHero")
	cinemaPos13 = GetScriptArea( selectByFaction( "CinematicHero3B2_m2", "CinematicHero3A2_m2") )
	cinemaPos14 = GetScriptArea( selectByFaction( "CinematicHero1B2_m2", "CinematicHero1A2_m2") )
	cinemaPos15 = GetScriptArea( selectByFaction( "FountainBCinema_m2", "FountainACinema_m2") )
	enemyHeroMove = GetScriptArea( selectByFaction( "NearArsenalB_m2", "NearArsenalA_m2" ) )
	cinemaPos16 = GetScriptArea( selectByFaction( "RatWaitPointB_m2", "RatWaitPointA_m2" ) )

	-- прячем элементы УИ которые будут позже появляться в миссии
	LuaShowUIBlock( "ChatBlock", false )
	LuaShowUIBlock( "ActionBarInventoryBtn", false )
	LuaShowUIBlock( "ActionBarSocialBtn", false )
	LuaShowUIBlock( "ActionBarStatisticBtn", false )
	LuaShowUIBlock( "FriendlyTeamMateBlock", false )
	LuaShowUIBlock( "EnemyTeamMateBlock", false )
	LuaShowUIBlock( "PortalBtn", false )
	LuaShowUIBlock( "LockActionBar", false )
	LuaGroupHide( ALLY_Secondery_LockTiles, true ) -- разрешаем игроку идти к первому флагу

	
	if not debugModeOn or debug1Intro then -- ПЕРВЫЙ СИНЕМАТИК. С КАСТОМНОЙ КАМЕРОЙ
		LuaUnitAddFlag (ALLY_TOWER_1, ForbidPick) 
		LuaUnitAddFlag ("local", ForbidPick)
		LuaUnitAddFlag (ALLY_BARRACKS2, ForbidPick) 
		LuaCameraLock (false)
		LuaCameraObserveUnit( "local" )
		cameraName = selectByFaction( "/Maps/Tutorial/cameraA2_1.CSPL", "/Maps/Tutorial/cameraB2_1.CSPL" )
		cameraTime = 20
		NeedToPauseAfterPhrases("D33_p3","D33_p4")
		StartCinematic ("TM2_D33") -- отслеживаем в логах
		LuaSplineCameraTimed (cameraName, cameraTime)
		LuaDebugTrace( "DEBUG: TeleportTo 215!") 
		
		LuaCreatureTeleportTo( "local", cinemaPos3.x, cinemaPos3.y )	
	
		if not debugModeOn or debug1Jaba then -- Синематик "Погоня жабы за лесой"
			AddSetPrime( "local", 0)
			LuaSetUnitHealth( ALLY_HERO_1, 250 )
			LuaSetUnitStat( ALLY_HERO_1, 3, 50 )
			LuaSetUnitStat( ENEMY_HERO_2, 3, 50 )
			LuaSetUnitHealth( ENEMY_HERO_2, 800 )
			LuaHeroActivateTalent (ENEMY_HERO_2, 2, 0, true)
			allyHeroPos = GetScriptArea( selectByFaction( "AllyHeroMoveA_m2", "AllyHeroMoveB_m2" ) )
			frogStartPos = GetScriptArea( selectByFaction( "EnemyHeroMoveA_m2", "EnemyHeroMoveB_m2" ) )
			LuaCreatureTeleportTo( ALLY_HERO_1, allyHeroPos.x, allyHeroPos.y ) -- objective 3
			LuaCreatureTeleportTo( ENEMY_HERO_2, frogStartPos.x, frogStartPos.y )
		end
		
		WaitForPhraseEnd( "D33_p3" )
		LuaDebugTrace( "DEBUG: Ждем D33_p3")
		LuaPauseDialog( true )
		LuaDebugTrace( "DEBUG: Ожидание закончилось!") 
		RemoveWarfogAll( false )
		LuaCameraLock (true)
--		LuaCameraObserveUnit( "local" )
		LuaUnitRemoveFlag (ALLY_TOWER_1, ForbidPick) 
		LuaUnitRemoveFlag ("local", ForbidPick)
		LuaUnitRemoveFlag (ALLY_BARRACKS2, ForbidPick)
	end	
 
if debugModeOn or debug1Intro then 	
	RemoveWarfogAll( true )	-- должно стоять перед паузой
end
		-- set sight ranges
	if ( FACTION_PLAYER == 1 ) then -- опредиляемся с фракцией
		LuaSetUnitStat( "BarracksA_m1", 14, 6 )
		LuaSetUnitStat( "TowerA1_m1",   14, 10 )
		LuaSetUnitStat( "MainA",        14, 33 )
		LuaSetUnitStat( "FountainA",    14, 20 )
		LuaSetUnitStat( "local",        14, 15 )
		LuaDirectionHintSet( "DirectionHintMtrl", 4, 2, 0 )
	else
		LuaSetUnitStat( "BarracksB_m1", 14, 6 )
		LuaSetUnitStat( "TowerB1_m1",   14, 10 )
		LuaSetUnitStat( "MainB",        14, 33 )
		LuaSetUnitStat( "FountainB",    14, 20 )
		LuaSetUnitStat( "local",        14, 15 )
		LuaDirectionHintSet( "DirectionHintMtrl", 4, 2, 0 )
	end
	
	
if LuaIsHeroMale("local") then  -- В зависимости от пола игрока опредиляем свойства миссии
	LuaLoadTalantSet( "local", "TM2_Tunder_Set" )
	LuaDebugTrace( "DEBUG: Поздравляю, у вас мальчик!") 
	HeroGenderQuest = "TM2_Q03ms"
	HeroGender = "TM2_D02_0_M"
	HeroGenderHint = "TM2_D02_1_M"
	SaveHeroQuest = selectByFaction( "TM2_Q01m_B", "TM2_Q01m_A" )
	LuaSetUnitStat( "local", 15, 80 )
	LuaSetUnitStat( "local", 16, 70 )
else
	LuaLoadTalantSet( "local", "TM2_Firefox_Set" )
	LuaDebugTrace( "DEBUG: Поздравляю, у вас девочка!") 
	HeroGenderQuest = "TM2_Q03fs"
	HeroGender = "TM2_D02_0_F"
	HeroGenderHint = "TM2_D02_1_F"
	SaveHeroQuest = selectByFaction( "TM2_Q01f_B", "TM2_Q01f_A" )
	LuaSetUnitStat( "local", 15, 70 )
	LuaSetUnitStat( "local", 16, 80 )
end
	
	LuaDebugTrace( "DEBUG: TeleportTo 175!") 
	LuaUnitAddFlag( ENEMY_TOWER_1, ForbidTakeDamage ) -- первую башню нельзя уничтожить

if not debugModeOn or debugRatCatcherDead then	
	LuaUnitAddFlag( ENEMY_HERO_1, ForbidTakeDamage ) -- пока до героя не добежали, убить его нельзя и он никого не бьет
	LuaUnitAddFlag( ENEMY_HERO_1, ForbidAutoAttack )
end
	
if not debugModeOn or debugTerrainOn then
	LuaUnitAddFlag("local", ForbidInteract ) -- нельзя поднять первый флаг, пока мы не рассказли про него
end
	genderLevel, genderColumn = FindGender( ALLY_HERO_1 )
end		
	LuaBlockActionBarChange(true) -- и блокируем возможно переставлять таланты по акшн-бару (или убирать их)

-- конец БЛОКА ПОДГОТОВКИ

	if LuaHeroIsTalentActivated("local", 0, 0) == false then -- Покупаем игроку А1 талант
		LuaHeroActivateTalent("local", 0, 0, false)
	end		

	StartTrigger( OnlyPlayerCanKillAtThisPoint, ALLY_TOWER_1, 35 )
	checkGender=true -- чтобы союзник не покупал себе гендер
	BlockAreaCentral = GetScriptArea ("TM1_BlockAreaCentral")
	StartTrigger( ForbidZone, BlockAreaCentral )
	StartTrigger( DrinkPotion, 50 ) -- подсказка, чтобы игрок когда мало ХП пил поушен
	StartTrigger( MyHeroDead, "local" )
	-- Запускаем триггеры, чтобы враги росли в уровне так же, как и мы.
	StartTrigger(HeroesLevelUp,"local",ENEMY_HERO_1, 0)
	StartTrigger(HeroesLevelUp,"local",ENEMY_HERO_2, 0)
if not debugModeOn or debugMidPointFight then 
	HeroesLevelUp_ENEMY_HERO_3_8Levels = StartTrigger(HeroesLevelUp,"local",ENEMY_HERO_3, 4)
end	
	
	if debugModeOn and debug1Intro and not debug1Jaba then 
		EndCinematic ()
	end
	
	LuaCreatureHide( ALLY_HERO_1, false ) 
	LuaCreatureHide( ENEMY_HERO_2, false )
	
if not debugModeOn or debug1Jaba then	
	LuaAddSessionQuest( SaveHeroQuest )
	LuaCreatureMoveTo( ALLY_HERO_1, cinemaPos2.x, cinemaPos2.y, 2 )
	Wait (0.3) -- задержка, чтобы лягушка успела сагрится
	LuaCreatureMoveTo( ENEMY_HERO_2, cinemaPos2.x, cinemaPos2.y, 2 )
	LuaDebugTrace( "DEBUG: TeleportTo 222!") 
	LuaUnitAddFlag(ENEMY_HERO_2, ForbidAutotargetMe ) -- чтобы башни по пути не били лягушку
	-- Запускаем видео ролик
		LuaUnitAddFlag( "local", ForbidAutoAttack )
		WaitForHeroNearUnit( "local", ALLY_HERO_1, selectByFaction(25,25) )
		LuaPauseDialog( false )
		LuaDebugTrace( "DEBUG: Ждем D33_p4")
		WaitForPhraseEnd( "D33_p4" )
		LuaPauseDialog( true )
		WaitForUnitInArea( ENEMY_HERO_2, cinemaPos2.x, cinemaPos2.y, selectByFaction(13,11) ) -- ждем, когда лягушка окажется в нужной точке, чтобы заставить ее прыгать
		LuaPauseDialog( false )
		EndCinematic ()  --add by Grey
		RotateHeroTo( "local", cinemaPos2)
		forFrogPlace = {}
		forFrogPlace.x, forFrogPlace.y = LuaHeroGetPosition( ALLY_HERO_1 ) -- запоминаем координаты союзника на этот момент
		LuaHeroUseTalentPos (ENEMY_HERO_2, 2, 0, selectByFaction(forFrogPlace.x+2.5,forFrogPlace.x-2.5), selectByFaction(forFrogPlace.y+1,forFrogPlace.y+1.5)) -- прыжок на союзника
		LuaDebugTrace( "DEBUG: TeleportTo 232!") 

		
		--BuyGender () -- функция про покупку гендера
		LuaHeroRemoveFlag( "local", ForbidAutoAttack )
		LuaHeroRemoveFlag(ENEMY_HERO_2, ForbidAutotargetMe )
		LuaShowUIBlock( "ImpulseTalent", false )
		AddSetPrime( "local", 250)
		AddSetPrime( ALLY_HERO_1, 0)
		WaitState (0.7) -- нужно, чтобы жаба успела приземлиться
		LuaUnitAttackUnit(ENEMY_HERO_2, ALLY_HERO_1) -- опять заставляем Жабу атаковать союзника
		LuaCameraLock (true)
		localPlace = {}
		localPlace.x, localPlace.y = LuaHeroGetPosition ("local")
		CameraWaitPosition( localPlace.x , localPlace.y , 1)
		LuaDebugTrace( "DEBUG: TeleportTo 239!") 
		LuaCameraLock (false)
		LuaCameraObserveUnit ("local")
	-- Конец видео ролика
-- Конец


if true then -- Кино, где Жаба возмущается
		LuaUnitAddFlag( "local", ForbidPlayerControl )
		LuaUnitClearStates ("local")
		LuaUnitClearStates (ENEMY_HERO_2)
		LuaUnitClearStates (ALLY_HERO_1)
--		LuaStartCinematic ( "TM2_D04" )
		ConstructWaitConditionState (HelthDownPercent, ENEMY_HERO_2, 60)
		NeedToPauseAfterPhrases("D06_p2", "D06_p3")
		StartCinematic ( "TM2_D06" )
		LuaHeroRemoveFlag( "local", ForbidPlayerControl )
end	-- Конец кино
	
	LuaPauseDialog( true )
	LuaDebugTrace( "DEBUG: Ждем пока лягушка умрет" )
	WaitForUnitsDead( ENEMY_HERO_2 )
	LuaPauseDialog( false )
	AddSetPrime( "local", 70)
	AddSetPrime( ALLY_HERO_1, 0)
	WaitForPhraseEnd( "D06_p1" )
	LuaCameraObserveUnit ("")
	WaitState (1.5) -- ждем пока доиграется анимация смерти Лягушки
-- Конец части
end

if not debugModeOn or debug1AllyHeal then	
-- Синематик "Союзник прибежал лечится"
		allyHeroMove = GetScriptArea( selectByFaction( "ObjectiveA4_m2", "ObjectiveB3_m1" ) )
		LuaCameraLock (true)
		LuaCameraObserveUnit( "" )	
		LuaCameraMoveToPosTimed ( cinemaPos10.x, cinemaPos10.y , 3)
		LuaCreatureMoveTo( "local", cinemaPos6.x, cinemaPos6.y, 1 )
		LuaCreatureMoveTo( ALLY_HERO_1, x, y, 1 )
		WaitForUnitInArea( ALLY_HERO_1, allyHeroMove.x, allyHeroMove.y, 10 )
			WaitForPhraseEnd( "D06_p2" )	 
		 WaitForUnitInArea( "local", cinemaPos6.x, cinemaPos6.y, 1 )
		 RotateHeroTo ( "local", allyHeroMove)
			LuaPauseDialog( false )
			WaitForPhraseEnd( "D06_p3" )
		 LuaCreatureHide( ENEMY_HERO_2, true )
		 WaitForUnitInArea( ALLY_HERO_1, allyHeroMove.x, allyHeroMove.y, 1 )
		 RotateHeroTo ( ALLY_HERO_1, cinemaPos6)
		 LuaPauseDialog( false )
		x, y = LuaUnitGetPosition ("local")
	EndCinematic ()
	if isCameraLocked then
		LuaDebugTrace( "Debug: до синематика было isCameraLocked = "..tostring(isCameraLocked)..", в этот момент надо привязать камеру")
		LuaCameraObserveUnit ("local")
	end
	LuaRemoveSessionQuest( SaveHeroQuest )
-- Конец синематика	
	
if not debugModeOn or debug1BuyPotion then -- Part 4: "Ждем пока игрок не купит себе хилинг потион"
	LuaAddSessionQuest( selectByFaction("TM2_Q34dp", "TM2_Q34ap") )
	LuaUnitAddFlag( "local", ForbidMove)
	LuaDebugTrace( "DEBUG: Купи хилинг потион!" )
	MarkEnemy( allyShop, true)
	LuaAddSessionQuest( "TM2_Q04s" ) -- отслеживаем в логах
	shopPos1 = {}
	shopPos1.x, shopPos1.y = LuaUnitGetPosition (allyShop)
	LuaSessionQuestUpdateSignal( "TM2_Q04s", "Q204_s1", shopPos1.x, shopPos1.y)
	StartTrigger( DoNotCloseShopUI ) -- ЛКМ/ПКМ хинтлайн про покупку
--	HintBuyIt ()
	WaitForOpenUI (WINDOW_SHOPBAR)
		if LuaIsWindowVisible (WINDOW_TALENTSBAR) then 
			LuaShowUIBlock ("Talents", false)
			windowTalentsCloe = true
		end
		if LuaIsWindowVisible (WINDOW_CHARSTATBAR) then 
			LuaShowUIBlock ("CharStats", false)
			windowCharStat = true
		end
		if LuaIsWindowVisible (WINDOW_SELECTIONCHARSTAT) then 
			LuaShowUIBlock ("SelectionCharStats", false)
			windowSelectCharStat = true
		end 
		if LuaIsWindowVisible (WINDOW_SELECTIONTALANTBAR) then
			LuaShowUIBlock ("SelectionTalents", false)
			windowSelectTalents = true
		end
		LuaShowUIBlock ("TalentsSetBlock", false)
	ShowHintline("")
	GreyWaitEnd()
	LuaBeginBlockSection() 
		LuaAddNonBlockedElement( "ShopBar", true )
		LuaAddNonBlockedElement( "InventoryBar", true )
		LuaAddNonBlockedElement( "Hintline", true )
		LuaAddNonBlockedElement( "QuestTracker", true )
		-- НАДО ОТКРЫВАТЬ ТУЛТИПЫ В ЭТОМ СОСТОЯНИИ!!!
	LuaEndBlockSection( 0 )
	ShowBubble( "TM2_D04_1", "Shop", 0, 0) -- отслеживаем в логах
	LuaShowTutorialShopItemHighlight (0, true) -- подсветка нужного нам слота
	ConstructWaitConditionState( LuaHeroHasConsumable, "local", "HealingPotion" )
	LuaShowTutorialShopItemHighlight (0, false ) 
	LuaDebugTrace( "DEBUG: Он купил его!" )
	MarkEnemy( allyShop, false)	
	LuaRemoveSessionQuest( "TM2_Q04s" )
	LuaShowUIBlock( "MoneyBlock", true )
	getSlotPotion = LuaGetInventoryItemActionBarIndex ("HealingPotion") 
	ShopTutorialOver = true
	LuaShowUIBlock( "ActionBarTalentBtn", true )
		LuaAddNonBlockedElement( "Hintline", true )
		LuaAddNonBlockedElementActionBar( getSlotPotion, true )
	ShowBubbleButton( "TM2_D04_2", "ActionBar", getSlotPotion) -- отслеживаем в логах
--	LuaShowTutorialActionBarItemHighlight (1, true) -- подсветка нужного нам слота в ActionBar-e
	WaitForBubbleClick()

	LogSessionEvent ("ActionBar agree to popup heal potion") -- отслеживаем в логах

	LuaShowUIBlock( "ActionBarInventoryBtn", true )
	LuaShowUIBlock( "ImpulseTalent", true )
--	LuaShowTutorialActionBarItemHighlight (1, false)
	if LuaIsWindowVisible( WINDOW_INVENTORYBAR )==true then -- если окно инвентаря до сих пор открыто
		LuaShowTutorialElementHighlight ("ActionBarInventoryBtn", true)
		LuaAddNonBlockedElement( "ActionBarInventoryBtn", true )
		ShowBubble( "TM2_D04_3", "ActionBarInventoryBtn")
		WaitForCloseUI ( WINDOW_INVENTORYBAR ) -- ждем пока игрок не закроет окна инвентаря
		
		LogSessionEvent ("close inventorybar with heal potion") -- отслеживаем в логах
		
		LuaShowTutorialElementHighlight ("ActionBarInventoryBtn", false)
		HideLastBubble()
	end
	LuaClearBlocking( 0 )
	LuaUnitRemoveFlag( "local", ForbidMove)
		LuaShowUIBlock ("TalentsSetBlock", true)
		if windowTalentsCloe then
			LuaShowUIBlock ("Talents", true)
			windowTalentsCloe = false
		end
		if windowCharStat then 
			LuaShowUIBlock ("CharStats", true)
			windowCharStat = false
		end
		if windowSelectCharStat then 
			LuaShowUIBlock ("SelectionCharStats", true)
			windowSelectCharStat = false
		end
		if windowSelectTalents then
			LuaShowUIBlock ("SelectionTalents", true)
			windowSelectTalents = false
		end	
end
-- Конец истории по хилинг потион
end


-- Отправляем союзника вместе с героем
	StartTrigger(AllyLevelUp,"local",ALLY_HERO_1, 0, 2)
	LuaShowUIBlock( "FriendlyTeamMateBlock", true )
	StartTrigger(AllyHeroDead, ALLY_HERO_1)
	LuaDebugTrace( "DEBUG: Теперь отправляемся вместе!" )
    Part2 = true	

if not debugModeOn or debug2Intro then -- ВТОРОЙ СИНЕМАТИК. С КАСТОМНОЙ КАМЕРОЙ	

	NeedToPauseAfterPhrases("D17_p1", "D17_p3")
	StartCinematic ( "TM2_D17" )
-- Гром и Лиса за ручку идут к арсеналу, чтобы посмотреть на базу врага
--	ConstructWaitConditionState( LuaIsPhraseFinished, "D17_p1" )
	LuaCameraLock (false)
	LuaPauseDialog( true )
	if not isCameraLocked then
		LuaDebugTrace( "Debug: до синематика было isCameraLocked = "..tostring(isCameraLocked)..", в этот момент надо привязать камеру")
		LuaCameraObserveUnit ("local")
	end
	LuaCreatureMoveTo( "local", cinemaPos4.x, cinemaPos4.y, 1 )
	LuaCreatureMoveTo( ALLY_HERO_1, cinemaPos5.x, cinemaPos5.y, 1 )
	LuaCreatureTeleportTo( ENEMY_HERO_3, cinemaPos13.x, cinemaPos13.y )
	LuaCreatureTeleportTo( ENEMY_HERO_1, cinemaPos14.x, cinemaPos14.y )
	RotateHeroTo ( ENEMY_HERO_3, ALLY_MAINBUILDING )
	RotateHeroTo ( ENEMY_HERO_1, ALLY_MAINBUILDING )
	Wait(rotateTime)
	WaitForUnitInArea( "local", cinemaPos4.x, cinemaPos4.y, 1 )
	WaitForUnitInArea( ALLY_HERO_1, cinemaPos5.x, cinemaPos5.y, 1 )
	RotateHeroTo ( "local", ENEMY_MAINBUILDING )
	RotateHeroTo ( ALLY_HERO_1, ENEMY_MAINBUILDING )
	Wait(rotateTime)
	LuaForceAnimation (ENEMY_HERO_3, "happy", 7)
	LuaForceAnimation (ENEMY_HERO_1, "happy", 7)
		if true then -- чтобы камера не видела ничего лишнего
			LuaUnitAddFlag (ALLY_TOWER_1, ForbidPick) 
			LuaUnitAddFlag ("local", ForbidPick)
			LuaUnitAddFlag (ALLY_HERO_1, ForbidPick)
			LuaUnitAddFlag (ALLY_HERO_1, ForbidTakeDamage) 
			LuaUnitAddFlag (ALLY_HERO_1, ForbidInteract)
			LuaUnitAddFlag (ENEMY_HERO_3, ForbidPick) 
			LuaUnitAddFlag (ENEMY_HERO_1, ForbidPick)
			LuaUnitAddFlag (ENEMY_BARRACKS2, ForbidTakeDamage) 
			LuaUnitAddFlag (ENEMY_BARRACKS2, ForbidInteract)
			LuaUnitAddFlag ("local", ForbidTakeDamage) 
			LuaUnitAddFlag ("local", ForbidInteract)
		end
		RemoveWarfogAll( true ) 
--		LuaSetCinematicPause (true)
	if not isCameraLocked then
		LuaDebugTrace( "Debug: до синематика было isCameraLocked = "..tostring(isCameraLocked)..", в этот момент надо отвязать")
		LuaCameraObserveUnit ("")
	end
		cameraName = selectByFaction( "/Maps/Tutorial/cameraA2_2.CSPL", "/Maps/Tutorial/cameraB2_2.CSPL" )
		cameraTime = 15
		LuaPauseDialog( false )
		ConstructWaitConditionState( LuaIsPhraseFinished, "D17_p1" )
--		StartCinematic ("TM2_D01")
		--LuaPauseDialog( true )
		LuaCameraLock (true)
		LuaZoomCamera(60, 0)
		LuaCameraMoveToPos (cinemaPos8.x, cinemaPos8.y)
		LuaSplineCameraTimed( cameraName, cameraTime)
			LuaDebugTrace( "DEBUG: SecondCinematic 536!") 
		LuaPauseDialog( false )
		ConstructWaitConditionState( LuaIsPhraseFinished, "D17_p3" )
		--LuaPauseDialog( true )
			LuaUnitRemoveFlag (ALLY_HERO_1, ForbidPick)
			LuaUnitRemoveFlag ("local", ForbidPick)
			LuaUnSetCameraFree ()
		LuaCameraLock (false)
		CameraReturn (6)
		LuaPauseDialog( false )
		EndCinematic ()
		
		LogSessionEvent ("TM2_D17 cinematic end") -- отслеживаем в логах
		
		LuaDebugTrace( "DEBUG: SecondCinematic End 548!") 
		--LuaCameraLock (true)
		if true then -- чтобы камера не видела ничего лишнего
			LuaUnitRemoveFlag (ENEMY_BARRACKS2, ForbidTakeDamage) 
			LuaUnitRemoveFlag (ENEMY_BARRACKS2, ForbidInteract)
			LuaUnitRemoveFlag (ALLY_HERO_1, ForbidTakeDamage) 
			LuaUnitRemoveFlag (ALLY_HERO_1, ForbidInteract)
			LuaUnitRemoveFlag ("local", ForbidTakeDamage) 
			LuaUnitRemoveFlag ("local", ForbidInteract)
			LuaUnitRemoveFlag (ENEMY_HERO_3, ForbidPick)
			LuaUnitRemoveFlag (ENEMY_HERO_1, ForbidPick)
			LuaUnitRemoveFlag (ALLY_TOWER_1, ForbidPick)
		end
		RemoveWarfogAll( false )
end		

		LuaHeroAIFollowHero (ALLY_HERO_1, "local")
		LuaDirectionHintShow( LuaUnitGetPosition ( ENEMY_MAINBUILDING) )
		LuaUnitAddFlag (ALLY_BARRACKS2, ForbidPick)
		LuaUnitAddFlag (ALLY_BARRACKS2, ForbidPick)
		LuaUnitAddFlag (ENEMY_BARRACKS2, ForbidTakeDamage) 
		LuaUnitAddFlag (ENEMY_BARRACKS2, ForbidInteract)
		LuaUnitAddFlag (ALLY_BARRACKS2, ForbidTakeDamage) 
		LuaUnitAddFlag (ALLY_BARRACKS2, ForbidInteract)
--	

if not debugModeOn or debugTerrainOn then -- Синематик про поднятие флага
		WaitForUnitInArea( "local", FlagPosition ) -- Ждем пока герой не пройдет мимо флага
		NeedToPauseAfterPhrases( "D07_p1" )
		StartCinematic( "TM2_D07" )	
--		LuaCameraLock( true )
		LuaDirectionHintHide()
--		WaitForUnitIdle( "local" )
		RotateHeroTo( "local", ALLY_HERO_1 )
--		ConstructWaitConditionState( LuaIsPhraseFinished, "D07_p1" )
		WaitForPhraseEnd( "D07_p1" )
		CameraMove ( cinemaPos11.x , cinemaPos11.y , 2)
		MarkEnemy( _FlagToMark, true)
		LuaCameraLock (true)
		WaitState(1) -- небольшая задержка, чтобы камера не прыгала от точки к точке
		LuaCameraLock (false)
		CameraReturn (2)
		LuaPauseDialog( false )
		EndCinematic()
		LuaUnitRemoveFlag( "local", ForbidInteract ) -- теперь можно поднимать флаг, мы лочим еще в начале скрипта
		HintArrow(selectByFaction("M2_Flag1_A","M2_Flag1_B"), selectByFaction(1.5,0))
	-- Конец синематика
-- конец Part 2.
	
-- Создаем сиджа, который будет поднимать флаги на стороне врага
	LuaDebugTrace( "DEBUG: Try Siege create." )
	EnemySiege1 = selectByFaction( "EnemyHeroMoveB_m2", "EnemyHeroMoveA_m2" )
	x, y = LuaGetScriptArea( EnemySiege1 )
	LuaCreateCreep( "CreepS1", ENEMY_CREEP_SIEGE, x, y, FACTION_ENEMY, selectByFaction( -M_PI2, M_PI2 ))
	DecreaseUnitSight( "CreepS1", true )
	LuaDebugTrace( "DEBUG: Siege create." )
	LuaUnitAddFlag( "CreepS1", ForbidTakeDamage )
-- Сидж создан
	
-- Part X: "Иди и подними первый фракционный флаг!"
	LuaDebugTrace( "DEBUG: Raise flag objective!" )
	_FlagID = selectByFaction ( 0, 2)
	
	-- Отправляем Сиджа поднимать флаг у себя
		LuaDebugTrace( "DEBUG: Пытаемся отправить сиджа к флагу." )
		x, y = LuaGetScriptArea( selectByFaction ("AllyHeroB_m1", "AllyHeroA_m1") )
		LuaDebugTrace( "DEBUG: Взяли координаты для флага." )
		LuaCreatureTeleportTo( "CreepS1", x, y )
		LuaDebugTrace( "DEBUG: Сидж отправлен к первому флагу." )
	-- Сидж отправлен

end
	
if not debugModeOn or debugMidPointFight then	 
	-- Заранее отправляем к 1 башне героя
		LuaUnitAddFlag( ENEMY_HERO_3, ForbidAutoAttack )
		LuaUnitAddFlag( ENEMY_HERO_3, ForbidTakeDamage )
		LuaDebugTrace( "DEBUG: Отправили героя к первому флагу" )
		x, y = LuaGetScriptArea( selectByFaction ("AllyHeroB_m1", "AllyHeroA_m1") )
		LuaCreatureTeleportTo( ENEMY_HERO_3, x, y )
		LuaCreatureHide( ENEMY_HERO_3, true )
	-- Герой отправлен
end

	FlagMark = {} -- для флагов!

if not debugModeOn or debugTerrainOn then	
--	MarkEnemy( _FlagToMark, true)
	LuaAddSessionQuest( "TM2_Q05s" )
	Wait(0.5)
	HintTakeIt ()-- ЛКМ/ПКМ хинтлайн про флаг
	FlagMark.x, FlagMark.y = LuaUnitGetPosition (_FlagToMark)
	LuaSessionQuestUpdateSignal( "TM2_Q05s", "Q205_s1", FlagMark.x, FlagMark.y)
	ConstructWaitConditionState( LuaFlagIsRising, 1, _FlagID)
	-- Запускаем синематик про ченнелинг на флаге
		LuaDebugTrace( "DEBUG: Ахтунг! кто-то поднимает флаг 1!" )
		GreyWaitEnd()
		LuaDirectionHintHide()
		LuaSetHintLine("","None")	
		--NeedToPauseAfterPhrases() -- Grey. Здесь бы поставить это, да вот только паузу нужно делать во время первой реплики
		FirstTerrainOnCinema ("TM2_D08")
		LuaPauseDialog( true )
		MarkEnemy( _FlagToMark, false)
--		ConstructWaitConditionState (FlagsTakeAlly, 1, _FlagID) 
		PushFlagsUp (1, _FlagID, "local", FACTION_PLAYER) -- ждем пока флаг окончательно поднимится
		LuaPauseDialog( false )
			WaitForPhraseEnd( "D08_p1" )
--			WaitForUnitIdle( "local" )
		--RotateHeroTo( "local", ALLY_HERO_1 )
		EndCinematic()
	-- Конец синематика
	LuaRemoveSessionQuest( "TM2_Q05s" )
	--LuaCameraObserveUnit ("local")
	LuaDebugTrace( "DEBUG: Первый флаг поднят!" )
	HintArrow ("M2_FlagMiddle", selectByFaction(1.5,0)) -- стрелка на центральный флаг
	WaitState (2) -- задержка между синематиками, иначе картинка дергается
-- конец
end

if not debugModeOn or debugFirstTowerScene then -- Заранее создаем своего сиджа
		x, y = LuaGetScriptArea( selectByFaction ("M2_FirstFlagPostion_A", "M2_FirstFlagPostion_B"))
		LuaCreateCreep( "CreepS2", ALLY_CREEP_SIEGE, x, y, FACTION_PLAYER, selectByFaction( M_PI2, -M_PI2 ))
		LuaUnitAddFlag( "CreepS2", ForbidAutoAttack )
		LuaUnitAddFlag( "CreepS2", ForbidTakeDamage )
		LuaDebugTrace( "DEBUG: Siege create." )
		DecreaseUnitSight( "CreepS2", true )
		LuaCreatureHide( "CreepS2", true ) 
		LuaDebugTrace( "DEBUG: Siege hide." )
	-- Все настройки для сиджа выставили
end
   
if not debugModeOn or debugTalentsBuy then
	 AdvancedTalentBuyTutorial () -- учим игрока преобретать таланты снова с рассказом, про родную землюи
end	 
	 
	LuaGroupHide( "TM1_BlockAreaCentral", true ) -- разрешаем игроку идти на речку
	RemoveTrigger( ForbidZone )
	 
if not debugModeOn or debugTerrainOn then -- Part 10: "Иди и подними центральный флаг!"
	-- Ожидание на то, когда игрок окажется рядом с флагом
	LuaCreatureHide( "CreepS1", true )
	MarkEnemy( "M2_FlagMiddle", true)
	LuaAddSessionQuest( "TM2_Q06s" ) -- отслеживаем в логах
	FlagMark.x, FlagMark.y = LuaUnitGetPosition ("M2_FlagMiddle")
	LuaSessionQuestUpdateSignal( "TM2_Q06s", "Q206_s1", FlagMark.x, FlagMark.y)

	WaitForUnitInArea( "local", PointMiddle)
	LuaDebugTrace( "DEBUG: Игрок на нужном расстоянии") 
	LuaDirectionHintHide()	-- убераем указатель на центральный флаг
		-- Когда пришел, лочим управление и создаем сиджа, который поднимает флаг
			LuaCreatureHide( "CreepS1", false)
			LuaCameraLock (true)
			LuaUnitAddFlag( "local", ForbidPlayerControl )
			LuaUnitAddFlag( "local", ForbidAutoAttack )
			LuaUnitAddFlag( "local", ForbidTakeDamage )
			LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
			LuaUnitAddFlag( ALLY_HERO_1, ForbidAutoAttack )
			LuaHeroAIDisable ( ALLY_HERO_1 )
			LuaUnitClearStates ("local")
			LuaSetUnitStat( "CreepS1", 3, 80 )
			--LuaCameraObserveUnit ("")
--			LuaPauseDialog( true )
			NeedToPauseAfterPhrases("D10_Tech")  --add by Grey
			StartCinematic ( "TM2_D10" )
			LuaPauseDialog( true )
			-- Отправляем Сиджа поднимать флаг у себя
				LuaDebugTrace( "DEBUG: Пытаемся отправить сиджа ко 2 флагу." )
				x, y = LuaGetScriptArea( "M2_MiddleFlagPoint" )
				LuaDebugTrace( "DEBUG: Взяли координаты для центрального флага." )
--				LuaCreatureMoveTo( "CreepS1", x, y, 1 )
				LuaUnitInvokeItsAbility( "CreepS1", 1, "flag_11")
				LuaDebugTrace( "DEBUG: Сидж отправлен к центральному флагу." )
			-- Сидж отправлен
			ConstructWaitConditionState (LuaIsUnitVisible, "CreepS1")
			LuaPauseDialog( false )
			WaitForPhraseEnd( "D10_Tech" )
			Wait(0.5) --add by Grey, чтобы игрок успел разглядеть крипа
			--LuaPauseDialog( false )
			LuaSetUnitStat( "CreepS1", 3, 60 )
			LuaCameraMoveToPosTimed ( x , y , 2)
			--LuaPauseDialog( false )
			--WaitForPhraseEnd( "D10_p1" )
			--LuaPauseDialog( true )
			ConstructWaitFlagsUp ( 1, 1, "CreepS1", FACTION_ENEMY ) -- ждем пока флаг окончательно поднимится
			LuaSetUnitStat( "CreepS1", 3, 44 )
			LuaPauseDialog( false )
			EndCinematic()
			CameraReturn(2)
			LuaUnitAddFlag ("M2_FlagMiddle", ForbidPick)
			LuaUnitAddFlag ("M2_FlagMiddle", ForbidInteract)
			LuaUnitAddFlag ("M2_FlagMiddle", ForbidTakeDamage)
			LuaHeroRemoveFlag( "local", ForbidTakeDamage )
			LuaHeroRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
			LuaHeroRemoveFlag( ALLY_HERO_1, ForbidAutoAttack )
			LuaHeroRemoveFlag( "local", ForbidPlayerControl )
			MarkEnemy( "M2_FlagMiddle", false)
--			LuaHeroAIDisable ( ALLY_HERO_1 )
			LuaHeroAIFollowHero (ALLY_HERO_1, "local")
	LuaAddSessionQuest( KillSiege )
	MarkEnemy( "CreepS1", true)
	x, y = LuaGetScriptArea( selectByFaction ("AllyHeroA_m1", "AllyHeroB_m1") )
	LuaDebugTrace( "DEBUG: Взяли координаты для флага." )
	LuaUnitRemoveFlag( "CreepS1", ForbidTakeDamage )
	LuaCreatureMoveTo( "CreepS1", x, y, 1 )
	WaitForUnitsDead( "CreepS1" ) -- ждем пока игрок убьет сиджа
	LuaRemoveSessionQuest( KillSiege )
	
	LogSessionEvent ("Enemy siege killed on the mid flag") -- отслеживаем в логах
	
--	MarkEnemy( "CreepS1", false)
	MarkEnemy( "M2_FlagMiddle", true)
	HintArrow ("M2_FlagMiddle", selectByFaction(1.5,0))
	LuaUnitRemoveFlag( "M2_FlagMiddle", ForbidPick )
	LuaUnitRemoveFlag( "M2_FlagMiddle", ForbidInteract )
	LuaUnitRemoveFlag( "M2_FlagMiddle", ForbidTakeDamage )
end


if not debugModeOn or debugMidPointFight then -- Битва с героем у центрального флага
--	ConstructWaitConditionState( LuaFlagIsRising, 1, 1 )
	LuaUnitAddFlag ( ENEMY_TOWER_1, ForbidAutoAttack ) -- чтобы башня не атаковала пока мы поднимаем флаг
	LuaUnitAddFlag ( "local", ForbidAutoAttack )
	LuaUnitAddFlag ( ALLY_HERO_1, ForbidAutoAttack )	
	LuaUnitAddFlag( "local", ForbidTakeDamage )
	LuaUnitAddFlag( "local", ForbidAutotargetMe )
	LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
	LuaUnitAddFlag( ALLY_HERO_1, ForbidAutotargetMe )
	ConstructWaitConditionState (FlagsTakeAlly, 1, 1) 
	NeedToPauseAfterPhrases( "D14_p1" )	

	StartCinematic ( "TM2_D14" ) -- отслеживаем в логах
	LuaUnitRemoveFlag( "local", ForbidTakeDamage )
	LuaUnitRemoveFlag( "local", ForbidAutotargetMe )
	LuaUnitRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
	LuaCreatureHide( ENEMY_HERO_3, false ) -- для синематика выпускаем Рокота!
	LuaHeroRemoveFlag( "local", ForbidAutoAttack )	
	if isCameraLocked then
		LuaDebugTrace( "Debug: до синематика было isCameraLocked = "..tostring(isCameraLocked)..", в этот момент надо отвязать")
		LuaCameraObserveUnit ("")
	end
	-- Начало синематека и рассказ про сильного героя
		LuaUnitAddFlag( "local", ForbidTakeDamage ) -- иначе могут быть случае, когда башня бьет героя в момент поднятия флага
		LuaUnitAddFlag(ENEMY_HERO_3, ForbidAutotargetMe ) -- чтобы башни по пути не били враж героя
		LuaUnitAddFlag( "local", ForbidPlayerControl )
		LuaUnitAddFlag( "local", ForbidAutoAttack )
		LuaUnitAddFlag( "local", ForbidAutotargetMe )
		LuaUnitAddFlag( ENEMY_HERO_3, ForbidAutoAttack )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidAutotargetMe )
		LuaHeroAIDisable ( ALLY_HERO_1 )
		LuaDirectionHintHide()
		MarkEnemy( "M2_FlagMiddle", false)
	-- конец первой части синематика
	LuaHeroRemoveFlag( ENEMY_HERO_3, ForbidAutoAttack )
	LuaDebugTrace( "DEBUG: Отправили героя3 к центральному флагу." )
	UnitMoveTo( ENEMY_HERO_3, PointMiddle, 7 )
		WaitForPhraseEnd( "D14_p1" )
	WaitForUnitIdle( "local" )
		LuaPauseDialog( false )
		WaitForPhraseEnd( "D14_p2" )
	RotateHeroTo( "local", PointMiddle) -- нас интересуют именно координаты, куда идет вражеский герой
	RotateHeroTo ( ALLY_HERO_1, PointMiddle)
	LuaRemoveSessionQuest( "TM2_Q06s" )
	-- Начало второй части синематика
		LuaCameraLock (true)
		WaitForMoveTo( ENEMY_HERO_3, PointMiddle, 0)
		RotateHeroTo ( ENEMY_HERO_3, "local" )
		ConstructWaitConditionState( LuaIsPhraseFinished, "D14_p2" )
		LuaShowTutorialOvertipLevelHighlight ( ENEMY_HERO_3, true ) -- Забронировал место, под мерцание уровня над головой героя
		ConstructWaitConditionState( LuaIsPhraseFinished, "D14_p4" )
		PlaceMarker ( "obj2", Obj2Pos.x, Obj2Pos.y ) -- указатель на земле, куда нужно отвести враж. героя 
		ConstructWaitConditionState( LuaIsDialogFinished, "TM2_D14" )
		x, y = LuaUnitGetPosition ("local")
		EndCinematic()
 
		HintArrow(Obj2Pos,0) -- указатель в направлении к месту, куда нужно отвести враж. героя
		LuaCameraLock (false)
		LuaHeroRemoveFlag( "local", ForbidTakeDamage )
		LuaHeroRemoveFlag( "local", ForbidPlayerControl )
		LuaHeroRemoveFlag( "local", ForbidAutoAttack )
		LuaHeroRemoveFlag( "local", ForbidAutotargetMe )
		LuaHeroRemoveFlag(ENEMY_HERO_3, ForbidAutotargetMe )
		LuaHeroRemoveFlag(ENEMY_HERO_3, ForbidAutoAttack )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidAutotargetMe )
		LuaUnitRemoveFlag ( "local", ForbidAutoAttack )
		LuaUnitRemoveFlag ( ALLY_HERO_1, ForbidAutoAttack )
		LuaShowTutorialOvertipLevelHighlight ( ENEMY_HERO_3, false )
	-- Конец синематика	
	LuaHeroRemoveFlag( ENEMY_HERO_3, ForbidTakeDamage )
	-- Квестовая обвязка
		HighHeroPos1 = {}
		HighHeroPos1.x, HighHeroPos1.y = LuaUnitGetPosition (ENEMY_HERO_3)
		LuaAddSessionQuest( "TM2_Q14s" )
		LuaSessionQuestUpdateSignal( "TM2_Q14s", "Q214_s1", HighHeroPos1.x, HighHeroPos1.y)
	-- Конец квестовой обвязки
	if isCameraLocked then
		LuaDebugTrace( "Debug: до синематика было isCameraLocked = "..tostring(isCameraLocked)..", в этот момент надо отвязать")
		LuaCameraObserveUnit ("local")
	end
 
	LuaHeroAttackUnit(ENEMY_HERO_3, "local")
	LuaHeroAIFollowHero (ALLY_HERO_1, "local")
	LuaShowTutorialElementHighlight( "SelectionLevel", true )
	WaitForUnitsDead( ENEMY_HERO_3 ) -- ждем пока враг будет повержен
	LuaShowTutorialElementHighlight( "SelectionLevel", false )
	RemoveLastMarker() --changed by Grey
 
	LuaDirectionHintHide()
	LuaUnitRemoveFlag( ENEMY_TOWER_1, ForbidAutoAttack )
end
	
 
	PeriodicalSpawn( ALLY_MAIN_SPAWNER , 18, creepCap) -- запускаем спавн солдат
 
	LuaDebugTrace( "DEBUG: Let the spawn begin!" )

if not debugModeOn or debugMidPointFight then	
	LuaRemoveSessionQuest( "TM2_Q14s" )
	RemoveTrigger(HeroesLevelUp_ENEMY_HERO_3_8Levels) -- больше крутой герой не растет в уровне выше нас
	StartTrigger(HeroesLevelUp,"local",ENEMY_HERO_3, 0)
	checkGender=false -- теперь союзник покупает себе гендерку
	LuaUnitAddFlag ( "local", ForbidAutoAttack )
	LuaUnitAddFlag ( ALLY_HERO_1, ForbidAutoAttack )	
	LuaUnitAddFlag( "local", ForbidTakeDamage )
	LuaUnitAddFlag( "local", ForbidAutotargetMe )
	LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
	LuaUnitAddFlag( ALLY_HERO_1, ForbidAutotargetMe )
	-- Запускаем синематик после смерти героя, он же дает время солдатам добежать до центра
		
		StartCinematic( "TM2_D15" ) -- отслеживаем в логах
		LuaPauseDialog( true )
		WaitState (2.5) -- таймер на проигрывание смерти героя
		HeroTalking ( "local", ALLY_HERO_1 )
		Wait(rotateTime) --ждем окончания поворота
		LuaForceAnimation (ALLY_HERO_1, "happy", 0) -- запускаем анимацию герою, пускай радуется :)
		LuaCreatureHide (ENEMY_HERO_3 , true)
		LuaPauseDialog( false )
		EndCinematic()
		LuaStopForcedAnimation (ALLY_HERO_1)
	-- Конец синематика
	LuaHeroRemoveFlag( "local", ForbidTakeDamage )
	LuaHeroRemoveFlag( "local", ForbidAutotargetMe )
	LuaUnitRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
	LuaUnitRemoveFlag( ALLY_HERO_1, ForbidAutotargetMe )
	LuaUnitRemoveFlag ( "local", ForbidAutoAttack )
	LuaUnitRemoveFlag ( ALLY_HERO_1, ForbidAutoAttack )
end
	
-- Part 22 : Уничтожить башню 1
		LuaUnitRemoveFlag( ENEMY_TOWER_1, ForbidTakeDamage ) -- теперь башню можно уничтожить
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_TOWER_1, 15 )
		LuaDebugTrace( "DEBUG: Уничтожить башню!" )
		RemoveWarfogTarget (ENEMY_TOWER_1, true)
		MarkEnemy( ENEMY_TOWER_1, true )
		HintArrow( ENEMY_TOWER_1, 0)
		TowerPos1 = {}
		TowerPos1.x, TowerPos1.y = LuaUnitGetPosition (ENEMY_TOWER_1)
	LuaAddSessionQuest( "TM2_Q22p" )
		LuaSessionQuestUpdateSignal( "TM2_Q22p", "Q222_p1", TowerPos1.x, TowerPos1.y)
	
if not debugModeOn or debugRatCatcherDead then 	
-- Заранее отправляем к 2 башне героя
	LuaCreatureTeleportTo( ENEMY_HERO_1, EnemyHeroMovePos.x, EnemyHeroMovePos.y )
	StartTrigger( RatcatcherDead, ENEMY_HERO_1 ) -- если крысолов будет убит без участия игрока
	LuaCreatureHide( ENEMY_HERO_1, true ) -- прячем крысолова, чтобы с ним ничего раньше не случилось
end
	
	LuaUnitAddFlag( ENEMY_TOWER_2, ForbidDeath )
	
if not debugModeOn or debugTalentsBuy then	
	HeroCanTakeTalent ("local", 10) -- запускаем проверку, на то, как скоро игрок покупает талант
end
	
	WaitForUnitsDead( ENEMY_TOWER_1 )
		LuaGroupHide( ENEMY_Secondery_LockTiles, true ) -- разрешает игроку идти ко второй башне
		LuaDirectionHintHide()	
	LuaRemoveSessionQuest( "TM2_Q22p" )
	
if not debugModeOn or debugFirstTowerScene then 
	-- Делаем синематик, иначе нельзя
		LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaUnitAddFlag( "local", ForbidTakeDamage )
		LuaCameraObserveUnit ("local")
	
	NeedToPauseAfterPhrases( "D22_p1", "D22_p2" )
	StartCinematic ( "TM2_D22" ) -- отслеживаем в логах
	AddTriggerTop (AllyHappyInTower, ALLY_HERO_1, "local", cinemaPos7, 1)
	
	-- Создаем своего сиджа, чтобы поднимал нам флаги
		SiegeFlag = selectByFaction ("AllyHeroA_m1", "AllyHeroB_m1")
		LuaDebugTrace( "DEBUG: Ждем пока игрок подойдет к третьему флагу!" )
	--	if LuaFlagGetFaction( 1, 0) == FACTION_ENEMY then
			LuaDebugTrace( "DEBUG: Не наш флаг, показываем синематик!" )
			LuaCreatureHide( "CreepS2", false ) 
			siegeMove = GetScriptArea( selectByFaction ("M2_FirstFlagPostion_B", "M2_FirstFlagPostion_A") )
			LuaSetUnitStat( "CreepS2", 3, 60 ) -- делаем высокую скорость сиджу, чтобы быстро все делал
			LuaSetUnitHealth( _FlagEnemy, 1 ) -- чтобы сидж сразу уничтожал вражеский флаг
			UnitMoveTo( "CreepS2", siegeMove, 10 )
			WaitForPhraseEnd( "D22_p1" )
			--LuaPauseDialog( true )
--			WaitForMoveTo( "CreepS2", siegeMove, 8 )
			LuaDebugTrace( "DEBUG: Отправляем сиджа." )
			_FlagIDAlly = selectByFaction (2, 0)
			FlagMark.x, FlagMark.y = LuaUnitGetPosition (_FlagEnemy)
			CameraMove( FlagMark.x, FlagMark.y, 2) -- отправляем камеру к флагу, чтобы смотреть как он поднимается
			LuaCameraLock( true )
			ConstructWaitFlagsUp ( 1, _FlagIDAlly, "CreepS2", FACTION_PLAYER )
			LuaCameraLock( false ) 
			LuaPauseDialog( false )
			WaitForPhraseEnd( "D22_p2" )
			LuaCreatureMoveTo( "CreepS2", EnemyHeroMovePos.x, EnemyHeroMovePos.y, 1 ) -- затем отправляем сиджа умирать к крысолову
			LuaUnitRemoveFlag( "CreepS2", ForbidTakeDamage ) -- Теперь нашего сиджа можно убить
			LuaSetUnitStat( "CreepS2", 3, 40 )
			CameraReturn(1)
			LuaPauseDialog( false )
--			ConstructWaitConditionState( LuaIsPhraseFinished, "D22_p1" )
	--	end
	-- Надо его отправить поднимать третий флаг, пока игроки болтают.
	StopAllPeriodicalSpawn()
	LuaSetSpawnCreeps( true )
	EndCinematic ()
	LuaHeroAIFollowHero ( ALLY_HERO_1, "local")
	LuaHeroRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
	LuaHeroRemoveFlag( "local", ForbidTakeDamage )
	LuaHeroRemoveFlag( ALLY_HERO_1, ForbidAutoAttack )
-- Конец синематика
-- End Башня разрушена
end

-- Part 29 : Уничтожить башню 2
--	LuaCreatureHide( ENEMY_HERO_3, true ) -- разрешаем игроку идти к крысолову
	HintArrow( ENEMY_TOWER_2, selectByFaction(1.5,0) )
	LuaAddSessionQuest( "TM2_Q29p" )
	LuaDebugTrace( "Уничтожить вторую башню!" )
	RemoveWarfogTarget (ENEMY_TOWER_2, true)
	MarkEnemy( ENEMY_TOWER_2, true )
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_TOWER_2, 15 )
	TowerPos2 = {}
	TowerPos2.x, TowerPos2.y = LuaUnitGetPosition (ENEMY_TOWER_2)
	LuaAddSessionQuest( "TM2_Q29p" )
	LuaSessionQuestUpdateSignal( "TM2_Q29p", "Q229_s1", TowerPos2.x, TowerPos2.y)

if not debugModeOn or debugRatCatcherDead then 		
	RatKilling () -- функция где мы выполняем убийство крысолова
	Wait (2.5) -- ждем пока проиграется анимация смерти крысолова
	GUITeamBlock() -- Рассказываем про портреты врагов и союзников
	TestHeroRespawning (ENEMY_HERO_1, 0.5)
	Wait (0.5) 
	LuaCreatureHide( ENEMY_HERO_1, true )
	LuaDebugTrace( "DEBUG: Крысолова спрятали" )	
end
	
--	LuaStartDialog( "TM2_D27" )
	LuaUnitRemoveFlag( ENEMY_TOWER_2, ForbidDeath ) -- до этого момента вторая башня не может быть разрушена
	WaitForUnitsDead( ENEMY_TOWER_2 )
	LuaRemoveSessionQuest( "TM2_Q29p" )
-- конец
	
-- Part 30 : Уничтожить Арсенал
	LuaAddSessionQuest( "TM2_Q30p" ) -- отслеживаем в логах
	LuaDebugTrace( "DEBUG: Уничтожить Арсенал!" )
	BarracksPos1 = {}
	BarracksPos1.x, BarracksPos1.y = LuaUnitGetPosition (ENEMY_BARRACKS)
	LuaSessionQuestUpdateSignal( "TM2_Q30p", "Q230_s1", BarracksPos1.x, BarracksPos1.y)
	RemoveWarfogTarget (ENEMY_BARRACKS, true)
	MarkEnemy( ENEMY_BARRACKS, true )
	HintArrow ( ENEMY_BARRACKS, selectByFaction(1.5,0))
	WaitForUnitsDead( ENEMY_BARRACKS )
	HintArrow( ENEMY_MAINBUILDING,0)
--	LuaUnitRemoveApplicator( ENEMY_BARRACKS, "ArrowUnitAppl" )
	LuaSetManualGameFinish (true)
	LuaRemoveSessionQuest( "TM2_Q30p" )

	LuaUnitAddFlag( ENEMY_MAINBUILDING, ForbidDeath ) -- главное здание нельзя убить
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_MAINBUILDING, 10 ) -- только игрок может уничтожить ГЗ

if not debugModeOn or debugFirstFightVsHero then -- Part 31 : Убить обоих героев	

if not debugModeOn then -- поддержка для дебага
	LuaCreatureHide( ENEMY_HERO_3, false )
	LuaCreatureHide( ENEMY_HERO_1, false )
elseif debugModeOn and debugMidPointFight then
	LuaCreatureHide( ENEMY_HERO_3, false )
	LuaDebugTrace( "DEBUG: Открыли нам ЧГ")
elseif debugModeOn and debugRatCatcherDead then
	LuaCreatureHide( ENEMY_HERO_1, false )
	LuaDebugTrace( "DEBUG: Открыли нам Крысолова")
end
		StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_HERO_1, 10 )
		StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_HERO_3, 10 )
		LuaUnitAddFlag( ENEMY_HERO_1, ForbidTakeDamage )
		LuaUnitAddFlag( ENEMY_HERO_3, ForbidTakeDamage )
		LuaUnitAddFlag( ENEMY_HERO_1, ForbidAutoAttack )
		LuaUnitAddFlag( ENEMY_HERO_3, ForbidAutoAttack )
		BuildingPos1 = {}
		BuildingPos1.x, BuildingPos1.y = LuaUnitGetPosition (ENEMY_MAINBUILDING)
		LuaSessionQuestUpdateSignal( selectByFaction("TM2_Q34dp", "TM2_Q34ap"), "Q234_s1", BuildingPos1.x, BuildingPos1.y)
		Objective31 = GetScriptArea( selectByFaction("ObjectiveB31_m2", "ObjectiveA31_m2"))
		Objective31a = GetScriptArea( selectByFaction( "HeroPointB1_m2", "HeroPointA1_m2"))
		Objective31b = GetScriptArea( selectByFaction( "HeroPointB2_m2", "HeroPointA2_m2"))
	--	WaitState (1) -- тех задержка, чтобы было время между разрушением арсенала и битвой с героями
		WaitForUnitInArea ("local", Objective31)	
	NeedToPauseAfterPhrases( "D32_p3" )	
	StartCinematic ( "TM2_D32", true ) -- отслеживаем в логах
	LuaHeroAIDisable( ALLY_HERO_1 )
	RemoveWarfogAll( true ) 
	LuaDirectionHintHide()
	LuaCameraLock (true)
	LuaCreatureMoveTo( ENEMY_HERO_1, Objective31a.x, Objective31a.y, 1 )
	LuaCreatureMoveTo( ENEMY_HERO_3, Objective31b.x, Objective31b.y, 1 )
		WaitForPhraseEnd( "D32_p3" )
	WaitForUnitInArea(ENEMY_HERO_1, Objective31a)
	WaitForUnitInArea(ENEMY_HERO_3, Objective31b)
		LuaPauseDialog( false )
		WaitForPhraseEnd( "D32_p4" )
	StartTrigger (EnemyUnitsDead, ENEMY_HERO_1, ENEMY_HERO_3)
	LuaAddSessionQuest( KillEnemyRatcatcher ) -- убить первого героя
	LuaAddSessionQuest( KillEnemyRockman ) -- убить второго героя
		LuaCameraObserveUnit ("")
	-- Работа с камерой 
		LuaSetCinematicPause (true)
		LuaUnitClearStates ("local")
	--	CameraMovePos1 = {}
	--	CameraMovePos1.x, CameraMovePos1.y = LuaUnitGetPosition (ENEMY_HERO_1)
	--	CameraWaitPosition ( CameraMovePos1.x , CameraMovePos1.y , 3)
	EndCinematic()
		LuaCameraObserveUnit ("local")
		RemoveWarfogAll( false ) 
	--	CameraReturn (1)
		LuaUnitRemoveFlag( ENEMY_HERO_1, ForbidTakeDamage )
		LuaUnitRemoveFlag( ENEMY_HERO_3, ForbidTakeDamage )
		LuaUnitRemoveFlag( ENEMY_HERO_1, ForbidAutoAttack )
		LuaUnitRemoveFlag( ENEMY_HERO_3, ForbidAutoAttack )
		MarkEnemy( ENEMY_HERO_1, true )
		MarkEnemy( ENEMY_HERO_3, true )
		Wait (0.2) -- чтобы игрок понял, что уже все закончилось
		LuaHeroAIFollowHero( ALLY_HERO_1, "local" )
		LuaHeroAttackUnit (ENEMY_HERO_1, ALLY_HERO_1)
		LuaHeroAttackUnit (ENEMY_HERO_3, ALLY_HERO_1)
		LuaSetCinematicPause (false)
		LuaCameraLock (false)
	-- конец
	ConstructWaitConditionState( EnemyUnitsWellDone )
	LuaDebugTrace( "DEBUG: Все мертвы")
	RemoveWarfogTarget (ENEMY_MAINBUILDING, true)
	MarkEnemy( ENEMY_MAINBUILDING, true )
	HintArrow( ENEMY_MAINBUILDING,0)
	Wait (2.5) -- время на анимацию смерти вражеского героя
	LuaCreatureHide (ENEMY_HERO_3 , true)
	LuaCreatureHide (ENEMY_HERO_1 , true)
end	

if not debugModeOn or debugSecondFightVsHero then -- победить запыхавшуюся Жабу	
	-- Запускаем третьего героя
	WaitForUnitInArea ("local", Objective31)
	if not debugModeOn then 
		LuaCreatureHide (ENEMY_HERO_2 , false)
	elseif debugModeOn and debug1Jaba then
		LuaCreatureHide (ENEMY_HERO_2 , false)
		LuaDebugTrace( "DEBUG: Открыли нам Жабу")
	end
--		LuaUnitClearStates ("local")
		LuaUnitAddFlag( ENEMY_HERO_2, ForbidTakeDamage )
		LuaUnitAddFlag( ENEMY_HERO_2, ForbidAutoAttack )
		LuaUnitAddFlag( "local", ForbidAutoAttack )
		LuaUnitAddFlag( "local", ForbidTakeDamage )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidAutoAttack )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_HERO_2, 10 )
	-- Запускаем синематик про подоспевшую жабу
	x, y = LuaUnitGetPosition ("local")
	LuaCreatureMoveTo( ENEMY_HERO_2, x, y, 5 )
	StartCinematic ( "TM2_D29", true )
	LuaPauseDialog( true )
	LuaDirectionHintHide()
	WaitForUnitInArea( ENEMY_HERO_2, x, y, 10 )
	LuaPauseDialog( false )
	EndCinematic()
		LuaCameraLock (false)
		LuaAddSessionQuest( KillEnemyFrog ) -- квест на убийство Жабы
		MarkEnemy( ENEMY_HERO_2, true)
		LuaCameraObserveUnit ("local")
	Wait (0.2)
		LuaDebugTrace( "DEBUG: Камера вернулась." )
	LuaSetCinematicPause (false)
		LuaUnitRemoveFlag( ENEMY_HERO_2, ForbidAutoAttack )
		LuaUnitRemoveFlag( ENEMY_HERO_2, ForbidTakeDamage )
		LuaUnitRemoveFlag( "local", ForbidAutoAttack )
		LuaUnitRemoveFlag( "local", ForbidTakeDamage )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidAutoAttack )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
	-- конец синематика
	LuaHeroAttackUnit (ENEMY_HERO_2, "local")
	WaitForUnitsDead( ENEMY_HERO_2 )
		MarkEnemy( ENEMY_HERO_2, false)
		LuaDebugTrace( "DEBUG: Молодец, с тобой мы победили!" )
	LuaRemoveSessionQuest( KillEnemyFrog )
	NeedToPauseAfterPhrases("D35_p1")
	StartCinematic ( "TM2_D35", true ) -- отслеживаем в логах
		LuaUnitClearStates ("local")
		LuaUnitAddFlag( "local", ForbidAutoAttack )
		LuaUnitAddFlag( "local", ForbidTakeDamage )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidAutoAttack )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
	ConstructWaitConditionState( LuaIsPhraseFinished, "D35_p1" )
		RemoveWarfogAll( true )
		LuaCameraLock (true)
		LuaCameraMoveToPosTimed (cinemaPos15.x , cinemaPos15.y, 2)
--		CameraWaitPosition ( cinemaPos15.x , cinemaPos15.y, 3 )
		WaitState(2) -- небольшая задержка, чтобы камера не прыгала от точки к точке
		LuaCreatureHide (ENEMY_HERO_2 , true)
		LuaPauseDialog( false )
	EndCinematic()
		LuaCameraLock (false)
		--LuaCameraObserveUnit ("")
		CameraReturn (1)
		RemoveWarfogAll( false )
		LuaUnitRemoveFlag( "local", ForbidAutoAttack )
		LuaUnitRemoveFlag( "local", ForbidTakeDamage )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidAutoAttack )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaSetUnitStat( "FountainA", 2, 22 ) -- чтобы фонтаны атаковали
		LuaSetUnitStat( "FountainB", 2, 22 )
		HintArrow( ENEMY_MAINBUILDING,0)
 -- главное здание теперь можно уничтожить
		LuaDebugTrace( "Теперь осталось разрушить их ГЗ!" )
end
-- конец
	 -- снова запускаем спавн крипов ALLY_MAIN_SPAWNER
		LuaSetSpawnCreeps( false )
		periodicalSpawnStop = false -- снова запускаем спавн крипов ALLY_MAIN_SPAWNER
		PeriodicalSpawn( ALLY_MAIN_SPAWNER , 18, creepCap)
	 --

	LuaUnitRemoveFlag( ENEMY_MAINBUILDING, ForbidDeath )
	BuildingPos1 = {}
	BuildingPos1.x, BuildingPos1.y = LuaUnitGetPosition (ENEMY_MAINBUILDING)
	LuaSessionQuestUpdateSignal( selectByFaction("TM2_Q34dp", "TM2_Q34ap"), "Q234_s1", BuildingPos1.x, BuildingPos1.y)
	WaitForUnitsDead( ENEMY_MAINBUILDING )
	LuaDirectionHintHide ()
	LuaRemoveSessionQuest( selectByFaction("TM2_Q34dp", "TM2_Q34ap") )
	RemoveWarfogAll( true ) 
	StartCinematic ("TM2_D31", true) -- отслеживаем в логах
	EndCinematic()
	Wait (0.5) --Задержка перед концом игры нужна, чтобы экран не затемнялся--
	LuaGameFinish( selectByFaction ( 2, 1) )
end

function RatKilling () -- Part 23: Убиваем крысолова	
	LuaCreatureHide( ENEMY_HERO_1, false ) -- теперь крысолов в боевой готовности
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_HERO_1, 25 )
		LuaHeroSetForbidRespawn( ALLY_HERO_1, true )
		LuaHeroSetForbidRespawn( "local", true )
--		LuaHeroSetForbidRespawn( ENEMY_HERO_1, true )
	WaitForUnitInArea( ENEMY_HERO_1, EnemyHeroMovePos )
	WaitForUnitInArea( "local", cinemaPos16.x, cinemaPos16.y, 20 )
	if HeroDeadCinematicStart or KillsTimeStart then
		while HeroDeadCinematicStart or KillsTimeStart do
--			LuaDebugTrace( "DEBUG: Ждем пока другие сценарии закончат свою работу." )
			SleepState() 
		end
		RatKillingStart = true
	else
		RatKillingStart = true
	end
		LuaUnitAddFlag( ALLY_HERO_1, IgnoreInvisible )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidAutoAttack )
		LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaUnitAddFlag( "local", ForbidAutoAttack )
		LuaUnitAddFlag( "local", ForbidTakeDamage )
		LuaUnitAddFlag( "local", ForbidAutotargetMe )
		LuaHeroAIDisable( ALLY_HERO_1 )
		x, y = LuaUnitGetPosition (ENEMY_HERO_1)
	LuaCreatureMoveTo( ALLY_HERO_1, x, y, 12 )
	LuaAddSessionQuest( KillEnemyRatcatcher )
	--LuaCameraObserveUnit ("")
	LuaUnitRemoveFlag( ALLY_HERO_1, ForbidDeath ) 
	LuaUnitRemoveFlag( "local", ForbidDeath )
	heroesImmortal = false --отменяем бессмертие героев
	
	NeedToPauseAfterPhrases("D23_Tech", "D23_p5", "D23_p6")
	StartCinematic ( "TM2_D23" ) -- синематик с Крысоловом под своей башней
	MarkEnemy( ENEMY_TOWER_2, false )
	LuaDirectionHintHide()
	LuaCameraMoveToPosTimed ( cinemaPos1.x , cinemaPos1.y , 2)
	RotateHeroTo( ENEMY_HERO_1, "local")
	Wait(rotateTime) -- ждем окончания поворота
	LuaSetCinematicPause (true)
--	WaitForPhraseEnd("D23_p2" ) -- by Grey
		x, y = LuaUnitGetPosition ("local")
	LuaDebugTrace( "DEBUG: Камера вернулась." )
	WaitForPhraseEnd( "D23_p4" )
	LuaSetCinematicPause (false)
	LuaPauseDialog( true ) -- не трогать!
-- Сцена, где крысолов притягивает союзника
		LuaHeroRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaHeroRemoveFlag( ALLY_HERO_1, ForbidAutoAttack )
		LuaHeroRemoveFlag( ENEMY_HERO_1, ForbidTakeDamage )
--		LuaHeroRemoveFlag( ENEMY_HERO_1, ForbidAutoAttack )
		LuaUnitAttackUnit( ALLY_HERO_1, ENEMY_HERO_1 ) -- тут лиса бросается на врага, чтобы убить его под башней
		LuaUnitAttackUnit(ENEMY_HERO_1, ALLY_HERO_1) -- отправляем крысолова к напарнику
		allyHero = {}
		allyHero.x, allyHero.y = LuaUnitGetPosition ( ALLY_HERO_1 )
		LuaCreatureMoveTo( ENEMY_HERO_1, allyHero.x, allyHero.y, 10 ) -- вдруг крысолов не будет видеть цель, так пускай бежит туда, где она должна стоять
	WaitForHeroNearUnit( ENEMY_HERO_1, ALLY_HERO_1, 10 ) -- ждем, когда крысолов окажется рядом с союзником
		LuaUnitClearStates( ENEMY_HERO_1 )
	if not LuaHeroCanActivateTalent (ENEMY_HERO_1, 0 , 1) then -- проверка, вдруг у Крысолова нет нужного нам таланта
		LuaHeroActivateTalent (ENEMY_HERO_1, 0 , 1, true)
	end
		LuaHeroUseTalentUnit (ENEMY_HERO_1, 0, 1, ALLY_HERO_1) -- крысолов дудит на свою цель
	LuaPauseDialog( false ) -- не трогать!
	WaitForPhraseEnd( "D23_Tech" ) -- не трогать!
	Wait (1) -- ждем пока он доиграет анимацию дудочки
		LuaCreatureMoveTo( ENEMY_HERO_1, Obj4Pos.x, Obj4Pos.y, 1 ) -- крысолов тащит свою цель под башню
	WaitForUnitInArea( ENEMY_HERO_1, Obj4Pos ) -- ждем пока он ее дотащит
		LuaCreatureMoveTo( ENEMY_HERO_1, EnemyHeroMovePos.x, EnemyHeroMovePos.y, 3 )
--	Part23=true Включаем, что если Крысолов умер без нас, он опять ресается и идет под башню (Откл. т.к. Бажит!)
--		LuaHeroAIGuardScriptArea (ENEMY_HERO_1, ENEMY_HERO_TOWER ) -- привязываем Крысолова, чтобы тусил под башней
		LuaHeroRemoveFlag( ENEMY_HERO_1, ForbidAutoAttack )
	LuaPauseDialog( false )	
	WaitForPhraseEnd( "D23_p5" )
	
	LuaKillUnit ( ALLY_HERO_1 ) -- надо, чтобы крысолов ее убивал
	WaitForUnitsDead( ALLY_HERO_1 )
	LogSessionEvent ("Ratcatcher quest: Ally hero dead") -- отслеживаем в логах
	
	Wait (2.5) -- время на проигрывание анимации смерти дружественного героя
			CameraMove (cinemaPos12.x, cinemaPos12.y, 3)
			if not LuaHeroIsRespawning (ALLY_HERO_1) then
				LuaHeroRespawn (ALLY_HERO_1)
				LuaDebugTrace( "DEBUG: Умирая ты всегда воскреснешь на базе!" )
			end
			WaitState (1.5) -- ждем пока возрадится дружеский герой
	LuaPauseDialog( false )
	WaitForPhraseEnd( "D23_p6" )
			LuaUnitAddFlag( ALLY_HERO_1, ForbidAutoAttack )
			LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )	
	NeedUsePortal (ALLY_HERO_1, "local") -- телепорт Лисы к герою
	LuaPauseDialog( false )
	WaitForPhraseEnd( "D23_p7" )
	LuaDebugTrace( "DEBUG: NeedUsePortal закончился!" )

	LuaDebugTrace( "DEBUG: Фраза D23_p6 закончилась!" )
	LuaShowUIBlock( "PortalBtn", true ) -- открываем кнопку "Портал"
--			LuaDebugTrace( "DEBUG: Включили паузу" )
--			LuaSetCinematicPause (true)
	EndCinematic ()
--			LuaSetCinematicPause (false)
	isCinematicCurrentlyPlayed = true
	LuaHeroAIDisable( ENEMY_HERO_1 )
		LuaSetAdventureControlsEnabled( false, true )
		LuaSetCinematicPause (true)
	LuaBeginBlockSection() 
		LuaAddNonBlockedElement ("PortalBtn", true)
	LuaEndBlockSection( 0 )
		LuaShowTutorialElementHighlight ( "PortalBtn", true )
		ShowBubbleButton( "TM2_D23_1", "PortalBtn")
		WaitForBubbleClick()
		
		LogSessionEvent ("Ratcatcher quest: player push the bubble button of portal") -- отслеживаем в логах
		
	LuaClearBlocking( 0 )
	LuaShowTutorialElementHighlight ( "PortalBtn", false )
		WaitState (0.1)
	LuaHeroAIFollowHero (ALLY_HERO_1, "local")
	MarkEnemy( ENEMY_HERO_1, true )
	HintArrow(ENEMY_HERO_1,0)
		LuaSetCinematicPause (false)
		LuaSetAdventureControlsEnabled( true, true )
		LuaHeroRemoveFlag( "local", ForbidAutoAttack )
		LuaHeroRemoveFlag( "local", ForbidTakeDamage )
		LuaHeroRemoveFlag( "local", ForbidAutotargetMe )
		LuaHeroRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaHeroRemoveFlag( ALLY_HERO_1, ForbidAutoAttack )
		RatKillingStart = false
	
	isCinematicCurrentlyPlayed = false
	WaitState (0.5)
	LuaUnitAttackUnit(ENEMY_HERO_1, "local")
	WaitForUnitsDead( ENEMY_HERO_1 ) -- ждем пока игрок расправится с Крысоловом	
	LuaShowUIBlock( "EnemyTeamMateBlock", true )
	LuaDebugTrace( "DEBUG: Крысолов мертв!" )
		MarkEnemy( ENEMY_HERO_1, false )
		MarkEnemy( ENEMY_TOWER_2, true )
		LuaDirectionHintShow( LuaUnitGetPosition( ENEMY_TOWER_2 ) )
	LuaRemoveSessionQuest( KillEnemyRatcatcher )
end
-- Part 25-26: ждем смерти героя, чтобы воскресить
function MyHeroDead(name)	
	dead, found = LuaUnitIsDead(name)
	if dead and found and not ImDeadFirst and not isCinematicCurrentlyPlayed then -- показываем синематик один раз после первой смерти
		ImDeadFirst = true
		LuaDebugTrace( "DEBUG: Игрок умер!" )
		TestHeroRespawning (name, 2.5)
			LuaCameraObserveUnit (name)
		ShowHintline( "TM2_D25_1", false )	-- отслеживаем в логах
		WaitState (7) -- время которое будет висеть хинт
		ShowHintline("")
		--StartCinematic ( "TM2_D25" )
		--EndCinematic()
		if Part2 then
			LuaHeroAIFollowHero (ALLY_HERO_1, "local")
			LuaDebugTrace( "DEBUG: Мы отправили союзника за нами" )
		end
		return false
	elseif dead and found then
			LuaDebugTrace( "DEBUG: Игрок опять умер!" )
--		LuaHeroSetForbidRespawn( "local", true )
--			WaitState(4)
		TestHeroRespawning (name, 2.5)
--		LuaHeroSetForbidRespawn( "local", false )
			LuaCameraObserveUnit ("local")
			WaitState(2)
		if Part2 then
			LuaHeroAIFollowHero (ALLY_HERO_1, "local")
			LuaDebugTrace( "DEBUG: Мы отправили союзника за нами" )
		end	
	end
	return false
end

function AllyHeroDead(ALLY_HERO_1)
	dead, found = LuaUnitIsDead(ALLY_HERO_1)
	if dead and found and not RatKillingStart then
		LuaDebugTrace( "DEBUG: союзник опять умер!" )
		LuaHeroSetForbidRespawn( ALLY_HERO_1, true )
		TestHeroRespawning (ALLY_HERO_1, 1)
		WaitState (2) -- ждем пока герой воскреснет
		LuaHeroAIFollowHero (ALLY_HERO_1, "local")
	end
	return false
end

function RatcatcherDead(name)	
	dead, found = LuaUnitIsDead(name)
	if dead and found and Part23 then
		LuaDebugTrace( "DEBUG: крысолов умер" )
		TestHeroRespawning (name, 2.5)
		WaitState (2.5) -- ждем пока герой воскреснет
		LuaCreatureMoveTo( name, EnemyHeroMovePos.x, EnemyHeroMovePos.y, 3 )
	end
	return false
end

function TestHeroRespawning (name, wtime)
	if not LuaHeroIsRespawning (name) then
		WaitState (wtime) -- хоть какая-то пауза, иначе камера прыгает на респ
		LuaHeroRespawn (name)
		LuaDebugTrace( "DEBUG: Умирая ты всегда воскреснешь на базе!" )
	end
end

function NeedUsePortal (nameHero, targetPoint) -- задания про Телепорт
	x, y = LuaUnitGetPosition ( targetPoint )
	LuaHeroAIDisable( nameHero )
	LuaHeroUseConsumablePos (nameHero, "AllyTeleport", x+2, y+3)
	Wait (3) -- ждем чуть меньше времени ченнелинга = (4.5)
	CameraReturn (2)
	LuaDebugTrace( "DEBUG: Ждем когда лиса окажется рядом с героем!" )
	WaitForHeroNearUnit( targetPoint, nameHero, 10 )
	LuaDebugTrace( "DEBUG: Лиса рядом с героем!" )
	WaitState (0.5) -- задержка под эффект телепорта
end
	
function Part30 ()
	LuaDebugTrace( "DEBUG: Part30 запущен!" )
	while true do
		local hx, hy = LuaUnitGetPosition( "local" )
--		LuaDebugTrace( "DEBUG: Ждем когда игрок окажется в нужной точке!" )
		if ( DistanceSquared( hx, hy, enemyHeroMove.x, enemyHeroMove.y ) < 14 * 14 ) and not isCinematicCurrentlyPlayed then
			-- Работа с камерой 
				LuaDebugTrace( "DEBUG: Ура! игрок там!" )
				LuaSetCinematicPause (true)
				StartCinematic ( "TM2_D32" )
				LuaUnitClearStates ("local")
				LuaUnitClearStates (ENEMY_HERO_1)
--				LuaUnitClearStates (ENEMY_HERO_2)
				LuaUnitClearStates (ENEMY_HERO_3)
				CameraWaitPosition ( enemyHeroMove.x, enemyHeroMove.y, 3)
				CameraReturn (2)
				Wait (0.2)
				LuaDebugTrace( "DEBUG: Камера вернулась." )
				LuaSetCinematicPause (false)
		        x, y = LuaUnitGetPosition (ENEMY_HERO_1)
				LuaCreatureMoveTo( ENEMY_HERO_1, x, y, 12 )				
--				LuaCreatureMoveTo( ENEMY_HERO_2, x, y, 12 )				
				LuaCreatureMoveTo( ENEMY_HERO_3, x, y, 12 )				
				LuaHeroAttackUnit (ENEMY_HERO_1, ALLY_HERO_1)
--				LuaHeroAttackUnit (ENEMY_HERO_2, ALLY_HERO_1)
				LuaHeroAttackUnit (ENEMY_HERO_3, ALLY_HERO_1)
			-- конец
			return true
		end
	SleepState()
	end
end

function AllyLevelUp(heroName, unitName, bonus, timeWait)	
	local herolvl = LuaHeroGetLevel(heroName)
	local unitlvl = LuaHeroGetLevel(unitName)
	if (herolvl+bonus)>unitlvl then -- bonus - это на сколько юнит должен быть выше уровнем, чем указанный герой
		WaitState (timeWait)
		for level = 0, 5 do
			for column = 0, 5 do
				if checkGender==true and level==genderLevel and column == genderColumn then
					return false
				elseif LuaHeroIsTalentActivated(unitName, level, column) == false then
					LuaHeroActivateTalent(unitName, level, column, false)
					return false
				end
			end
		end
	end
	return false
end

function HeroCanTakeTalent(heroName) -- покупка таланта на более высоком ТУРе	
	LuaDebugTrace( "DEBUG: Смотрим, может активировать талант или нет?" )
	local maxLevel = LuaHeroGetTalentsLevel (heroName)
	for level = maxLevel, 0, -1 do
		for column = 0, 5 do
			canBuyTalent = LuaHeroCanActivateTalent (heroName, level, column)
			if canBuyTalent then
				LuaDebugTrace( "DEBUG: Проверяем какие он нам нашел level:" ..tonumber(level).. "column:" ..tonumber(column) )
				canBuyTalent = false
				LuaShowUIBlock( "ImpulseTalent", false )
				RemindTalentBuyTutorial(level, column)
				return true
			end
		end
	end
	return
end

function HeroCanTakeMoreTalent(heroName) -- у героя остался лишний прайм
	LuaDebugTrace( "DEBUG: Смотрим, может активировать талант или нет?" )
	local maxLevel = LuaHeroGetTalentsLevel (heroName)
	for level = maxLevel, 0, -1 do
		for column = 0, 5 do
			canBuyTalent = LuaHeroCanActivateTalent (heroName, level, column)
			if canBuyTalent then
				ShowBubble( "TM2_D41_2", "Talent", column, level)
				LuaDebugTrace( "DEBUG: Может, переходим к следующей функции" )
				CheckSuccessfulBuyTalent() -- ждем покупки таланта
				HideLastBubble()
				canBuyTalent = false
				return true
			end
		end
	end
	return
end

function RemindTalentBuyTutorial(level, column)
	DrinkPotionEnd ()
	if LuaIsWindowVisible (WINDOW_INVENTORYBAR) then
		LuaShowUIBlock ("Inventory", false)
		windowInventarCloe = true
	end	
	if LuaIsWindowVisible (WINDOW_CHARSTATBAR) then 
		LuaShowUIBlock ("CharStats", false)
		windowCharStat = true
	end
	if LuaIsWindowVisible (WINDOW_SELECTIONCHARSTAT) then 
		LuaShowUIBlock ("SelectionCharStats", false)
		windowSelectCharStat = true
	end 
	if LuaIsWindowVisible (WINDOW_SELECTIONTALANTBAR) then
		LuaShowUIBlock ("SelectionTalents", false)
		windowSelectTalents = true
	end
		LuaUnitAddFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaUnitAddFlag( "local", ForbidTakeDamage )
	canBuyTalent = false
	LuaSetPause( true ) -- byGrey
	LuaUnitClearStates( "local" )
	LuaSetAdventureControlsEnabled( false, true )
	LuaAddSessionQuest( "TM2_Q40" )
	LuaBeginBlockSection() 
		LuaAddNonBlockedElement( "TalentsBar", true )
		LuaAddNonBlockedElement( "NaftaBottle", true )
		LuaAddNonBlockedElement( "Hintline", true )
		LuaAddNonBlockedElement("QuestTracker", true)
			-- НАДО ОТКРЫВАТЬ ТУЛТИПЫ В ЭТОМ СОСТОЯНИИ!!!
	LuaEndBlockSection( 0 )
	ShowBubble("TM2_D40_1", "PrimeBottle")
	WaitForOpenUI( WINDOW_TALENTSBAR )
	StartTrigger( DoNotCloseTalentUI ) -- спец блок, чтобы не закрыли случаайно УИ до окончания туториала. 
	LuaDebugTrace( "DEBUG: Проверяем какие он нам нашел level:" ..tonumber(level).. "column:" ..tonumber(column) )
	local maxLevel = LuaHeroGetTalentsLevel ("local")
	for level = maxLevel, 0, -1 do
		for column = 0, 5 do
			canBuyTalent = LuaHeroCanActivateTalent ("local", level, column)
			if canBuyTalent then
				LuaDebugTrace( "DEBUG: Проверяем какие он нам нашел level:" ..tonumber(level).. "column:" ..tonumber(column) )
				canBuyTalent = false
				ShowBubble( "TM2_D41_1", "Talent", column, level)
				CheckSuccessfulBuyTalent() -- ждем покупки таланта
				HideLastBubble()
				LuaDebugTrace( "DEBUG: Покупка состоялась" )
--				return
--			else 
--				return
				HeroCanTakeMoreTalent("local")
			end	
		end
	end
	ConstructWaitFalseConditionState (HeroCanTakeMoreTalent, "local") -- просим активировать еще какой-нибудь доступный талант
	if LuaIsWindowVisible ( WINDOW_TALENTSBAR ) then
		ShowBubble( "TM2_D40_4", "PrimeBottle")
		WaitForCloseUI ( WINDOW_TALENTSBAR ) -- ждем пока игрок не закроет окна инвентаря
		HideLastBubble()
	end
	LuaShowUIBlock( "ImpulseTalent", true )
	LuaRemoveSessionQuest("TM2_Q40")
	
	LogSessionEvent ("Player bouth second part talents") -- отслеживаем в логах
	
	LuaClearBlocking( 0.8 )
	LuaSetPause( false ) -- byGrey
	LuaSetAdventureControlsEnabled( true, true )
		LuaUnitRemoveFlag( ALLY_HERO_1, ForbidTakeDamage )
		LuaUnitRemoveFlag( "local", ForbidTakeDamage )
	if LuaIsWindowVisible (WINDOW_INVENTORYBAR) then
		LuaShowUIBlock ("Inventory", false)
		windowInventarCloe = true
	end
	if windowCharStat then 
		LuaShowUIBlock ("CharStats", true)
		windowCharStat = false
	end
	if windowSelectCharStat then 
		LuaShowUIBlock ("SelectionCharStats", true)
		windowSelectCharStat = false
	end 
	if windowSelectTalents then
		LuaShowUIBlock ("SelectionTalents", true)
		windowSelectTalents = false
	end	
end

function HintBuyIt()	
	if LuaGetControlStyle() then   -- ЛКМ/ПКМ хинтлайн
		ShowHintline( "TM2_H01_LMC", true, "RightClick" )
--		LuaStartDialog( "TM1_D02_LMC" )
	else 
		ShowHintline( "TM2_H01_RMC", true, "LeftClick" )
	end
end

function HintTakeIt()	
	if LuaGetControlStyle() then   -- ЛКМ/ПКМ хинтлайн
		ShowHintline( "TM2_H02_RMC", true, "LeftClick" )
--		LuaStartDialog( "TM1_D02_LMC" )
	else 
		ShowHintline( "TM2_H02_LMC", true, "RightClick" )
	end
end

function ForbidZone( zoneName )
	if IsHeroInArea( "local", zoneName.x , zoneName.y, zoneName.radius ) then 
		LuaUnitClearStates( "local" )
--		return true
	end
	return false
end

function EnemyUnitsDead( firstNames, secondNames )
	while true do
		if not firstNamesDead then
			local dead, found = LuaUnitIsDead( firstNames )
			if dead and found then
				firstNamesDead=true
				MarkEnemy( firstNames, false )
				LuaHeroSetForbidRespawn (firstNames, true) 	
				LuaDebugTrace( "DEBUG: Умер firstNames!" )
				LuaRemoveSessionQuest( KillEnemyRatcatcher )
				if not secondNamesDead then
					MarkEnemy( secondNames, true )
					secondDeadLast = true
				end
			end
		end
		if not secondNamesDead then
			local dead, found = LuaUnitIsDead( secondNames )
			if dead and found then
				secondNamesDead=true
				MarkEnemy( secondNames, false)	
				LuaHeroSetForbidRespawn (secondNames, true)
				LuaDebugTrace( "DEBUG: Умер secondNames!" )	
				LuaRemoveSessionQuest( KillEnemyRockman )
				if not firstNamesDead then
					MarkEnemy( firstNames, true )
					firstDeadLast = true
				end		
		
			end
		end
		local dead, found = LuaUnitIsDead( ALLY_HERO_1 )
		if firstNamesDead==true and secondNamesDead==true then
			LuaDebugTrace( "DEBUG: Они все умерли!" )	
			return true
		elseif dead and found then
			LuaDebugTrace( "DEBUG: Союзник умер бъём игрока!" )
			if not firstNamesDead then
				LuaDebugTrace( "DEBUG: Первый враг не умер и бъёт игрока!" )
				LuaHeroAttackUnit (firstNames, "local")
			end
			if not secondNamesDead then
				LuaDebugTrace( "DEBUG: Второй враг не умер и бъёт игрока!" )
				LuaHeroAttackUnit (secondNames, "local")
			end
			return false
		else
			return false
		end
--		SleepState()
	end
end

function EnemyUnitsWellDone()
	if firstNamesDead==true and secondNamesDead==true then
		LuaDebugTrace( "DEBUG: Подтверждаю, что они все умерли!" )	
		if firstDeadLast then
			PlayCinematic ("TM2_D34") -- если последним умер Крысолов (отслеживаем в логах)
		else
			PlayCinematic ("TM2_D36") -- в остальных случаях значит, что последним умер ЧГ(отслеживаем в логах)		
		end
		return true
	else
		return false
	end
	LuaDebugTrace( "DEBUG: Проверяем на убийство" )
end

function NameAllLivingCreepsFromSpawner( spawnerName )
	local lastWaveNumb = LuaSpawnerGetLastWave( spawnerName )
	local arr = {}
	local ii = 1
	local creepsInWave = 10
	for i = 1, lastWaveNumb do
		for j = 1, creepsInWave do
			localName = spawnerName .. "_w" .. tostring(i) .. "_c" .. tostring(j)
			if not LuaUnitIsDead( localName ) then
--				local numberInArray = (i-1)*creepsInWave + j 
				arr[ ii ] = localName
				ii = ii +1
			end
		end
	end	
	return arr
end

function WaitHeroNearUnit( heroName, distance, unitCount)
	while true do
		if isCinematicCurrentlyPlayed == false then
			LuaDebugTrace( "DEBUG:WaitHeroNearUnit" )
			local creepTypeMask = BitMask( UnitTypeCreep, UnitTypeSiegeCreep )
			local factionMask = 2 ^ FACTION_ENEMY
			LuaDebugTrace( "DEBUG:WaitHeroNearUnit:" .. tostring( creepTypeMask ))
			LuaDebugTrace( "DEBUG:WaitHeroNearUnit:" .. tostring( factionMask ))
			while true do
				x, y = LuaUnitGetPosition ( heroName )
				local CreepsNumb = LuaGetUnitsInArea( factionMask, creepTypeMask, x, y, distance)
				LuaDebugTrace( "DEBUG:WaitHeroNearUnit:" .. tostring( CreepsNumb ) )
				LuaDebugTrace( "DEBUG:WaitHeroNearUnit:" .. tostring( x ) .. ":" .. tostring( y ) )
				if CreepsNumb >= unitCount then
					return
				end
				SleepState()
			end
		end
		SleepState()
	end
end

function GUITeamBlock()
--	LuaCameraLock( true )
	isCinematicCurrentlyPlayed = true
	Wait (1) -- задержка, чтобы не было резкого перехода к этому туториалу
	CheckWindowsOpen ()
	LuaSetPause (true)
	DrinkPotionEnd ()
	LuaSetAdventureControlsEnabled( false, true )
	LuaBeginBlockSection() 
		LuaAddNonBlockedElementHero( ENEMY_HERO_1, true )
		LuaAddNonBlockedElementHero( ENEMY_HERO_2, true )
		LuaAddNonBlockedElementHero( ENEMY_HERO_3, true )
		LuaAddNonBlockedElementHero( "local", true )
		LuaAddNonBlockedElementHero( ALLY_HERO_1, true )
		LuaAddNonBlockedElementHeroBubble (ENEMY_HERO_1, true)
		LuaAddNonBlockedElement ("QuestTracker", true)
		-- НАДО ОТКРЫВАТЬ ТУЛТИПЫ В ЭТОМ СОСТОЯНИИ!!!
	LuaEndBlockSection( 0 )
--		LuaShowTutorialHeroHighlight ( ENEMY_HERO_1, true )
		ShowBubbleButton( "TM2_D26_1", "Hero", ENEMY_HERO_1 ) -- показываем сначала портрет крысолова
		WaitForBubbleClick()
			LuaAddNonBlockedElementHeroBubble (ALLY_HERO_1, true)
			LuaAddNonBlockedElement ("QuestTracker", true)
--		LuaShowTutorialHeroHighlight ( ENEMY_HERO_1, false ) 
		ShowBubbleButton( "TM2_D26_2", "Hero", ALLY_HERO_1 ) -- потом, показываем портрет нашего героя
		WaitForBubbleClick()
	LuaClearBlocking( 0 )
	LuaSetAdventureControlsEnabled( true, true )
	LuaSetPause (false)
	CheckWindowsEnd ()
	isCinematicCurrentlyPlayed = false
	-- Теперь союзник и герой могут умирать
end

function AllyHappyInTower (heroName1, heroName2, checkPoint, distance)
	LuaHeroAIDisable ( heroName1 )
	LuaUnitAddFlag( heroName1, ForbidAutoAttack )
	LuaCreatureMoveTo( heroName1, checkPoint.x, checkPoint.y, distance ) -- отправляем героя
	while not IsHeroInArea( heroName1, checkPoint.x, checkPoint.y, distance ) do
		SleepState()
	end
	WaitForUnitIdle( heroName1 )
	HeroTalking ( heroName2, heroName1 )
	Wait(rotateTime) --ждем окончания поворота
	LuaForceAnimation (heroName1, "happy", 3) -- запускаем анимацию герою, пускай радуется :)
end

function AdvancedTalentBuyTutorial()
	if LuaIsWindowVisible (WINDOW_INVENTORYBAR) then
		LuaShowUIBlock ("Inventory", false)
		windowInventarCloe = true
	end
	if LuaIsWindowVisible (WINDOW_CHARSTATBAR) then 
		LuaShowUIBlock ("CharStats", false)
		windowCharStat = true
	end
	if LuaIsWindowVisible (WINDOW_SELECTIONCHARSTAT) then 
		LuaShowUIBlock ("SelectionCharStats", false)
		windowSelectCharStat = true
	end 
	if LuaIsWindowVisible (WINDOW_SELECTIONTALANTBAR) then
		LuaShowUIBlock ("SelectionTalents", false)
		windowSelectTalents = true
	end
	LuaShowUIBlock( "ImpulseTalent", false )
	talentTutorialOver = false
	LuaSetPause( true ) -- by Grey
	LuaUnitClearStates( "local" )
	LuaSetAdventureControlsEnabled( false, true )
	LuaAddSessionQuest( "TM2_Q40" ) -- отслеживаем в логах
	LuaBeginBlockSection() 
		LuaAddNonBlockedElement( "TalentsBar", true )
		LuaAddNonBlockedElement( "NaftaBottle", true )
		LuaAddNonBlockedElement( "Hintline", true )
		LuaAddNonBlockedElement("QuestTracker", true)
		-- НАДО ОТКРЫВАТЬ ТУЛТИПЫ В ЭТОМ СОСТОЯНИИ!!!
	LuaEndBlockSection( 0 )
	WaitState (0.6)
	HideLastBubble() -- прячем бабл про потионы, если игрок не спрятал его сам
	AddSetPrime( "local", 300)
	AddSetPrime( ALLY_HERO_1, 0)
		Wait(0.1)	
	ShowBubble("TM2_D40_5", "PrimeBottle")
	WaitForOpenUI( WINDOW_TALENTSBAR )
	StartTrigger( DoNotCloseTalentUI ) -- спец блок, чтобы не закрыли случаайно УИ до окончания туториала. 
	ShowBubble( "TM2_D40_2", "Talent", 1, 0) -- отслеживаем в логах
	CheckSuccessfulBuyTalent() -- ждем покупки таланта
	talentTutorialOver = true
	Wait(0.1) -- нужно, чтобы флеш успел обновится для LuaGetTalentActionBarIndex
	firstTalent = LuaGetTalentActionBarIndex(1, 0) -- получаем номер слота в ActionBare
--	firstTalent = 2 -- временно!
		LuaAddNonBlockedElementActionBar( firstTalent, true )
	LuaShowTutorialActionBarItemHighlight ( firstTalent, true )
	ShowBubbleButton( "TM2_D40_3", "ActionBar", firstTalent)
	WaitForBubbleClick()
	HideLastBubble()
	LuaShowTutorialActionBarItemHighlight ( firstTalent, false )
	if LuaIsWindowVisible ( WINDOW_TALENTSBAR ) then
		ShowBubble( "TM2_D40_4", "PrimeBottle")
		WaitForCloseUI ( WINDOW_TALENTSBAR ) -- ждем пока игрок не закроет окна инвентаря
		HideLastBubble()
	end
	LuaClearBlocking( 0.8 )
	LuaRemoveSessionQuest("TM2_Q40")
	HideLastBubble()
	LuaSetAdventureControlsEnabled( true, true )
	LuaSetPause( false )
	LuaShowUIBlock( "ImpulseTalent", true )
	if windowInventarCloe then
		LuaShowUIBlock ("Inventory", true)
		windowInventarCloe = false
	end
	if windowCharStat then 
		LuaShowUIBlock ("CharStats", true)
		windowCharStat = false
	end
	if windowSelectCharStat then 
		LuaShowUIBlock ("SelectionCharStats", true)
		windowSelectCharStat = false
	end
	if windowSelectTalents then
		LuaShowUIBlock ("SelectionTalents", true)
		windowSelectTalents = false
	end	
end

function DoNotCloseTalentUI()
	if talentTutorialOver then return end
	if not LuaIsWindowVisible(WINDOW_TALENTSBAR) then
		LuaShowBubble( "PrimeBottle", true, "TM2_D40_5_Hint", "", 2) -- Используем здесь прямую функцию, а не обертку, т.к. событие может случиться в непредсказуемый момент и сломать другие баблы
	else
		LuaShowBubble( "PrimeBottle", false, "TM2_D40_5_Hint", "", 2) -- Используем здесь прямую функцию, а не обертку, т.к. событие может случиться в непредсказуемый момент и сломать другие баблы
	end
end

function DoNotCloseShopUI()
	if ShopTutorialOver then return true end
	if not LuaIsWindowVisible(WINDOW_SHOPBAR) and not showHintBuyIt then
		showHintBuyIt = true
		HintBuyIt ()
	elseif LuaIsWindowVisible(WINDOW_SHOPBAR) and showHintBuyIt then
		ShowHintline("")
		showHintBuyIt = false
	end
end

function BuyGender () -- Part 3: Buy Gender
	level, column = FindGender( "local" )
	if level >= 0 then
		LuaBeginBlockSection() 
			LuaAddNonBlockedElement( "TalentsBar", true )
			LuaAddNonBlockedElement( "NaftaBottle", true )
			LuaAddNonBlockedElement( "Hintline", true )
			LuaAddNonBlockedElement("QuestTracker", false)
			-- НАДО ОТКРЫВАТЬ ТУЛТИПЫ В ЭТОМ СОСТОЯНИИ!!!
		LuaEndBlockSection( 0 )
		WaitState (0.6)

		LuaSetAdventureControlsEnabled( false, true )
		LuaShowUIBlock( "ImpulseTalent", false )
		AddSetPrime( "local", 250)
		AddSetPrime( ALLY_HERO_1, 0)
		LuaSetPause (true)
		LuaAddSessionQuest( HeroGenderQuest )
		LuaDebugTrace( "DEBUG: Купи гендерный талант!" )
			ShowBubble( HeroGender, "PrimeBottle")
		WaitForOpenUI( WINDOW_TALENTSBAR )
		StartTrigger( DoNotCloseTalentUI )
			ShowBubble( HeroGenderHint, "Talent", column, level)
		ConstructWaitConditionState( CheckClickedTalent, level, column )
			HideLastBubble()
			talentTutorialOver = true	
		if LuaIsWindowVisible ( WINDOW_TALENTSBAR ) then
			ShowBubble( "TM2_D40_4", "PrimeBottle")
			WaitForCloseUI ( WINDOW_TALENTSBAR ) -- ждем пока игрок не закроет окна инвентаря
			HideLastBubble()
		end
		LuaClearBlocking( 0 )
		WaitState (0.3)
		LuaSetPause (false)
		LuaSetAdventureControlsEnabled( true, true )
		LuaRemoveSessionQuest( HeroGenderQuest )
	end
end

function WaitCinematic ()
	local state = function (...)
		if func == nil then
			LuaDebugTrace( debug.traceback() )
		end
		while true do
		LuaDebugTrace( "DEBUG: Ждем, пока синематик закончится" )
			if not isCinematicCurrentlyPlayed then
				return
			end
			SleepState()
		end
		AddStateTop( state, ... )
		SleepState()
	end
end

function RemoveWarfogAll( warfogState ) -- Если true - открываем варфог на все карте при условии, что на ней есть ГЗ с именем "MainA"
	if warfogState then
		LuaUnitApplyApplicatorFromUnit( ALLY_MAINBUILDING, "local", "RemoveWarfog")
	else
		LuaUnitRemoveApplicator( ALLY_MAINBUILDING, "RemoveWarfog")
	end
	
end

function RemoveWarfogTarget( targetName, warfogTargetState ) -- Если true - открываем варфог над целью 
	if warfogTargetState then
		LuaUnitApplyApplicatorFromUnit( targetName, "local", "RemoveShortWarfog")
	else
		LuaUnitRemoveApplicator( targetName, "RemoveShortWarfog")
	end
	
end

function CreepControl2( spawnerName, creepCap )
	if endCreepControl then 
		LuaDebugTrace("DEBUG: функция CreepContorl2 прекращает свою работу ")
		return true
	end
	local creepsArray = NameAllLivingCreepsFromSpawner( spawnerName )
	if # creepsArray > creepCap then 
		LuaDebugTrace("DEBUG: функция CreepContorl2 число существ в игре: " ..tostring(# creepsArray).." - убиваем одно" )
		LuaKillUnit( creepsArray[1] )
	end
end

function UnitImmortalCheat(unitName, warnPercent) -- функция, которая делает юнита бесмертным
	--if not unicId then
	if heroesImmortal then
		local health, maxHealth = LuaUnitGetHealth( unitName )
		local bonusHealthRegen = 5
		local currentPercent = health / maxHealth
		local damageDecresePercent = (1 - currentPercent) * 100 - 20
		LuaSetUnitStat( unitName , 27, damageDecresePercent)
		LuaSetUnitStat( unitName , 28, damageDecresePercent)
		--LuaDebugTrace("DEBUG: функция UnitImmortalCheat для ".. " работает")
		if ( currentPercent <=  warnPercent / 100 ) then
			LuaSetUnitStat( unitName , 11, bonusHealthRegen)
		else 
			LuaSetUnitStat( unitName , 11, 2)	
		end
	else
		LuaDebugTrace("DEBUG: функция UnitImmortalCheat отключенна ")
		return true
	end
end

function CheckWindowsOpen () -- если открыто окно талантов, принудительно закрываем его
	if LuaIsWindowVisible (WINDOW_TALENTSBAR) and LuaIsWindowVisible (WINDOW_INVENTORYBAR) then 
		LuaShowUIBlock ("Talents", false)
		LuaShowUIBlock ("Inventory", false)
		windowCloe = true
	elseif LuaIsWindowVisible (WINDOW_INVENTORYBAR) then
		LuaShowUIBlock ("Inventory", false)
		windowInventarCloe = true
	elseif LuaIsWindowVisible (WINDOW_TALENTSBAR) then 
		LuaShowUIBlock ("Talents", false)
		windowTalentsCloe = true
	end
	if LuaIsWindowVisible (WINDOW_CHARSTATBAR) then 
		LuaShowUIBlock ("CharStats", false)
		windowCharStat = true
	end
	if LuaIsWindowVisible (WINDOW_SELECTIONCHARSTAT) then 
		LuaShowUIBlock ("SelectionCharStats", false)
		windowSelectCharStat = true
	end 
	if LuaIsWindowVisible (WINDOW_SELECTIONTALANTBAR) then
		LuaShowUIBlock ("SelectionTalents", false)
		windowSelectTalents = true
	end
end

function CheckWindowsEnd () -- если открыто окно талантов, принудительно закрываем его (возвращаем то, что было отключено)
	if windowTalentsCloe then 
		LuaShowUIBlock ("Talents", true)
		windowTalentsCloe = false
	elseif windowInventarCloe then
		LuaShowUIBlock ("Inventory", true)
		windowInventarCloe = false
	elseif windowCloe then
		LuaShowUIBlock ("Talents", true)
		LuaShowUIBlock ("Inventory", true)
		windowCloe = false
	end	
	if windowCharStat then 
		LuaShowUIBlock ("CharStats", true)
		windowCharStat = false
	end
	if windowSelectCharStat then 
		LuaShowUIBlock ("SelectionCharStats", true)
		windowSelectCharStat = false
	end 
	if windowSelectTalents then
		LuaShowUIBlock ("SelectionTalents", true)
		windowSelectTalents = false
	end	
end

function FirstTerrainOnCinema (dialogName)
	LuaDebugTrace( "Debug: начало не стандартного синематика "..tostring(dialogName))
	LuaSetAdventureControlsEnabled( false, false )
	isCinematicCurrentlyPlayed = true
	local hx, hy = LuaCameraGetPos ()
	local x, y = LuaUnitGetPosition ("local")
	if not ( DistanceSquared( hx, hy, x, y ) < 0.01 ) and cameraReturn then -- на случай если игрок отвязал камеру
		CameraReturn (0.4)
	end
	currentCinematicName = dialogName
	LuaStartCinematic ( currentCinematicName )
end