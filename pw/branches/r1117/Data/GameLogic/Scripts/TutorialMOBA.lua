
include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

local function DeferredInit()
	PlotObjectives ()
				
	StartTrigger( SecondaryQuestTracker )

	AddStateTop( PrimaryQuestTracker )
end

-- Перед тем, как игроку показать область обязательно лочим ему все действия
function Init()

	scriptWorkOn = true
	
	HintPause = false
	
	HintHeroIsLeaveBase = false
	HintDestroyEnemyBarrack = false
	DestroedEnemyBarrack = false
	DestroedMainBuilding = false
	UseTerrainFlag = false
	FirstTowerDestroy = false
	FirstTowerDestroyHint = false
	SecondTowerDestroyForPing = false
	LineTowersDestroed = false
	LuaEnableEventLogging (true)	
	-- БЛОК НАСТРОЙКИ ДЕБАГГЕРА
	debugModeOn = false
	
	debugCameraCinematic = false
	debugFirstBuyTalent = true
	debugKillSolders = true
	debugKillCreeps = true
	debugPortalUse = true
	debugPickGlyph = true
	debugTerrainFlagUp = true
	debugNearShop = true
	debugNearCat = true
	debugNearDragon = true
	debugTowersAttack = true
	debugKills = true
	debugAssists = true
	debugMiniGameOn = true
	
	-- КОНЕЦ БЛОКА НАСТРОЙКИ
	
	if( scriptWorkOn ) then
	
		AddLocalStateTop(DeferredInit)
		
	end

end

function PlotObjectives()
	LuaSetSpawnCreeps( false )
	LuaSetSpawnNeutralCreeps( false )
	LuaSetCreepsLevelupPaused (true)
	
	-- Блокируем соответствующий интерфейс
	LuaShowUIBlock( "EscMenuSurrenderButton" , false) 
	LuaShowUIBlock( "EscMenuRunToCastleButton" , false)
	LuaShowUIBlock( "ChatBlock", false )	
	-- Закончили с интерфейсом
	
	-- Принудительно загружаем дефолтовые талант сеты для туториала (названия прописаны в словаре)
	if LuaIsHeroMale("local") then  
		LuaLoadTalantSet( "local", "Tutorial_Firefox_Set" )
		LuaDebugTrace( "DEBUG: игрок = муж.") 
	else
		LuaLoadTalantSet( "local", "Tutorial_Firefox_Set" )
		LuaDebugTrace( "DEBUG: игрок = жен.") 
	end
	-- Закончили с талантсетами
	
	FLAGSPOLES_ADORN_FIRST = { "Flag_Top_B1", "Flag_Mid_B1", "Flag_Bot_B1"}
	FLAGSPOLES_DOCT_FIRST = { "Flag_Top_A1", "Flag_Mid_A1", "Flag_Bot_A1" }
	FLAGSPOLES_ADORN_SECOND = { "Flag_Top_B2", "Flag_Mid_B2" , "Flag_Bot_B2" }
	FLAGSPOLES_DOCT_SECOND = { "Flag_Top_A2", "Flag_Mid_A2", "Flag_Bot_A2" }
	
	FLAGSPOLES_NEUTRAL = { "Flag_Top_N", "Flag_Mid_N", "Flag_Bot_N" }
	
	FIRST_TOWERS_DOCT = { "TopTowerA_1", "MidTowerA_1", "BotTowerA_1" }
	FIRST_TOWERS_ADORN = { "TopTowerB_1", "MidTowerB_1", "BotTowerB_1" }

	SECOND_TOWERS_DOCT = { "TopTowerA_2", "MidTowerA_2", "BotTowerA_2" }
	SECOND_TOWERS_ADORN = { "TopTowerB_2", "MidTowerB_2", "BotTowerB_2" }
	
	THIRTH_TOP_TOWERS_DOCT = { "TopTowerA_3_1", "TopTowerA_3_2"}
	THIRTH_TOP_TOWERS_ADORN = { "TopTowerB_3_1", "TopTowerB_3_2"}
	
	THIRTH_MID_TOWERS_DOCT = { "MidTowerA_3_1", "MidTowerA_3_2" }
	THIRTH_MID_TOWERS_ADORN = { "MidTowerB_3_1", "MidTowerB_3_2" }
	
	THIRTH_BOT_TOWERS_DOCT = { "BotTowerA_3_1", "BotTowerA_3_2" }
	THIRTH_BOT_TOWERS_ADORN = { "BotTowerB_3_1", "BotTowerB_3_2" }
	
	THIRTH_TOWERS_DOCT = { "TopTowerA_3_1", "TopTowerA_3_2", "MidTowerA_3_1", "MidTowerA_3_2", "BotTowerA_3_1", "BotTowerA_3_2"}
	THIRTH_TOWERS_ADORN = { "TopTowerB_3_1", "TopTowerB_3_2", "MidTowerB_3_1", "MidTowerB_3_2", "BotTowerB_3_1", "BotTowerB_3_2" }
	
	TOP_LINE_DOCT = { "TopTowerA_1", "TopTowerA_2", "TopTowerA_3_1", "TopTowerA_3_2", "TopArsenal_A" }
	TOP_LINE_ADORN = { "TopTowerB_1", "TopTowerB_2", "TopTowerB_3_1", "TopTowerB_3_2", "TopArsenal_B" }
	
	MID_LINE_DOCT = { "MidTowerA_1", "MidTowerA_2", "MidTowerA_3_1", "MidTowerA_3_2", "MidArsenal_A" }
	MID_LINE_ADORN = { "MidTowerB_1", "MidTowerB_2", "MidTowerB_3_1", "MidTowerB_3_2", "MidArsenal_B" }
	
	BOT_LINE_DOCT = { "BotTowerA_1", "BotTowerA_2", "BotTowerA_3_1", "BotTowerA_3_2", "BotArsenal_A" }
	BOT_LINE_ADORN = { "BotTowerB_1", "BotTowerB_2", "BotTowerB_3_1", "BotTowerB_3_2", "BotArsenal_B" }
	
	TOTAL_TOWERS_DOCT = { "TopTowerA_1", "MidTowerA_1", "BotTowerA_1", "TopTowerA_2", "MidTowerA_2", "BotTowerA_2", "TopTowerA_3_1", "TopTowerA_3_2", "MidTowerA_3_1", "MidTowerA_3_2", "BotTowerA_3_1", "BotTowerA_3_2" }
	TOTAL_TOWERS_ADORN = { "TopTowerB_1", "MidTowerB_1", "BotTowerB_1", "TopTowerB_2", "MidTowerB_2", "BotTowerB_2", "TopTowerB_3_1", "TopTowerB_3_2", "MidTowerB_3_1", "MidTowerB_3_2", "BotTowerB_3_1", "BotTowerB_3_2" }
	
	BARACK_DOCT = { "TopArsenal_A", "MidArsenal_A", "BotArsenal_A" }
	BARACK_ADORN = { "TopArsenal_B", "MidArsenal_B", "BotArsenal_B" }
	
	FactionSetup()
	
	ImageSetup()
	
	MiniGameStart = false
	
	LineHint = false
	StartHint = true
	
	AlarmTimer = 0
	AlarmCoolDown = 20
	sound1Timer = 0
	sound1 = false
	
	SoldersNumb = 0
	CreepsFoundCount = 0
	timerUseTalents = 0
	usedTalentCount = 0
	usedTalentCountNeeded = 2
	someTalentUsed = false
	AboutMove = false
	aboutMoveID = false
	idleTime = 0
	playerChangeLock = false
	changeLockTime = 0
	localHeroBaseAttackMul = 1.3
	
	-- Настройка указателей на ближайшую башню
	HintDirectionOn = false
	TopTowerDirOn = false
	MidTowerDirOn = false
	BotTowerDirOn = false
	currentIndex = 1
	LuaDirectionHintSet( "DirectionHintMtrl", 4, 2, 0 )
	-- Конец подготовки
	
	if not debugModeOn or debugFirstBuyTalent then -- Переменные для покупки таланта
		FirstBouthDone = false
		currentLevel = 1 
		forButLevel = 1
		ChechCount = 0
	end
		
	if not debugModeOn or debugKillSolders then
		SolderFound = false
		KillSoldersDone = false
		KillSoldersHint = false
		solderTypeMask = BitMask( UnitTypeCreep, UnitTypeSiegeCreep )
		soldersFactionMask = 2 ^ FACTION_ENEMY
		solderKills = 0
	end
	
	if not debugModeOn or debugTowersAttack then
		towerTypeMask = BitMask( UnitTypeTower )
		noSiegeTypeMask = BitMask( UnitTypeCreep )
		heroMask = BitMask( UnitTypeHeroMale )
		
		towersFactionMask = 2 ^ FACTION_ENEMY
		allySoldersFactionMask = 2 ^ FACTION_PLAYER
		
		FindAttackTower = false
		TowerAttackCooldown = 30
		TowerAttackTimer = TowerAttackCooldown
		AttackedHeroAlone = false
		TowerAttackWithSiege = false
	end
	
	if not debugModeOn or debugKillCreeps then
		CreepsFound = false
		creepTypeMask = BitMask( UnitTypeNeutralCreep, UnitTypeNeutralChampion )
		signalCreepX, signalCreepY = LuaGetScriptArea(selectByFaction ("Tutorial_CreepsSpawn_A", "Tutorial_CreepsSpawn_B")) 
		creepFactionMask = 1
		KillCreepsDone = false
		CreepsQuest = false
	end
	
	if not debugModeOn or debugKills then
		KillEnemyHero = false
		lastKills = 0
	end
	
	if not debugModeOn or debugAssists then
		AssistEnemyHero = false
		lastAssists = 1
	end
	
	if not debugModeOn or debugNearCat then
		CatFound = false
		bossTypeMask = BitMask( UnitTypeNeutralBoss )
		creepFactionMask = 1
	end
	
	if not debugModeOn or debugNearDragon then
		DragonFound = false
		if( bossTypeMask == nil) then
			bossTypeMask = BitMask( UnitTypeNeutralBoss )
		end
		creepFactionMask = 1
	end
	
	if not debugModeOn or debugTerrainFlagUp then
		TerrainFlagUp = false -- запоминаем говорили мы про флаг или нет
		flagpoleTypeMask = BitMask(UnitTypeFlagpole)
	end
	
	
	if not debugModeOn or debugPickGlyph then
		GlyphFind = false
		glyphTypeMask = BitMask( UnitTypePickupable )
		creepFactionMask = 1
	end
	
	if not debugModeOn or debugNearShop then
		AboutShop = false
		shopTypeMask = BitMask( UnitTypeShop )
		shopFactionMask = 2 ^ FACTION_PLAYER
	end
	
	
	if not debugModeOn or debugPortalUse then
		usePortalOn = false
		PortalQuestDone = false
	end
	
	if not debugModeOn or debugMiniGameOn then
		MiniGameOn = false
		minigame1PlaceX, minigame1PlaceY = LuaUnitGetPosition(selectByFaction ("MiniGame_A", "MiniGame_B")) 
		minigame2PlaceX, minigame2PlaceY = LuaGetScriptArea(selectByFaction ("Tutorial_MidPoint_A", "Tutorial_MidPoint_B")) 
		questMiniGame = false
		questMiniGameDone = false
		MiniGameEND = false
	end
end

function FactionSetup()
	FACTION_PLAYER = LuaGetLocalFaction()
	FACTION_ENEMY = 3 - FACTION_PLAYER
	
	function selectByFaction( a, b ) 	-- select by player faction
		if ( FACTION_PLAYER == 1 ) then
			return a			
		else
			return b
		end
	end
	
	function selectByGender( a, b ) 	-- select by player faction
		if ( LuaIsHeroMale("local")) then
			return a			
		else
			return b
		end
	end
	
	BOSS_CAT_HOME  = GetScriptArea("BossCat_Home")
	BOSS_DRAGON_HOME = GetScriptArea("BossDragon_Home")
	
	CAMERA_START_ON = GetScriptArea("Flag_Mid_N")
	CAMERA_START_ON.x, CAMERA_START_ON.y = LuaUnitGetPosition("Flag_Mid_N")
	
	MY_BASE_COORDINATE = GetScriptArea( selectByFaction ("Tutorial_DoctBase", "Tutorial_AdornBase"))
	MY_BASE_RADIUS = 90
	pushLineNumber = 0
	enemyAiTurnOn = true
	controllerAICoolDown = 50
	timerControllerAI = controllerAICoolDown
	
	-- КОГДА У ИГРОКА МАЛО ЗДОРОВЬЯ
	LowHpTimer = 0
	LowHpCoolDown = 90
	-- КОНЕЦ ПОДГОТОВКИ
	
	-- КОГДА У ИГРОКА МНОГО ПРАЙМА, НО ОН ТУПИТ
	ALotPrimeCoolDown = 90
	ALotPrimeTimer = ALotPrimeCoolDown
	ALotPrimeWait = 20
	ReactWaitTimer = 0
	questPrime = {350, 500, 675, 825, 1160, 1600, 1600 }
	questLevel = {1, 4, 8, 12, 16, 20, 37 }
	currentPrimeIndex = 1
	heroLevel = 1
	lastLevel = 0
	-- КОНЕЦ ПОДГОТОВКИ

	-- Здоровье вражеским башням
	firstTowersHP = 3000
	secondTowersHP = 2600
	lastTowersHP = 1100
	enemyMainBuildingHP = 3000
	enemyBarracksHP = 1000
	-- Конец 
	
	-- Настройка характеристик вражеских ботов
	statsHero = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed }
	enemyHeroLow = 0
	statsModifier = 0.8
	-- Конец настройки
	
	currentQuestDialog = 1
	dialogQuestTable = {"TSound_2_1", "TSound_2_2", "TSound_2_3"}
	
	ENEMY_FIRST_TOWERS = selectByFaction ( FIRST_TOWERS_ADORN, FIRST_TOWERS_DOCT)
	ENEMY_SECOND_TOWERS = selectByFaction ( SECOND_TOWERS_ADORN, SECOND_TOWERS_DOCT)

	firstTopTower = {}
	firstMidTower = {}
	firstBotTower = {}
	
	TopTowerDefence = false
	MidTiwerDefence = false
	BotTowerDefence = false
	MB_TowerDefence = false

	ENEMY_LAST_TOP_TOWERS = selectByFaction ( THIRTH_TOP_TOWERS_ADORN, THIRTH_TOP_TOWERS_DOCT)
	ENEMY_LAST_MID_TOWERS = selectByFaction ( THIRTH_MID_TOWERS_ADORN, THIRTH_MID_TOWERS_DOCT)
	ENEMY_LAST_BOT_TOWERS = selectByFaction ( THIRTH_BOT_TOWERS_ADORN, THIRTH_BOT_TOWERS_DOCT)

	ENEMY_LAST_TOWERS = selectByFaction ( THIRTH_TOWERS_ADORN, THIRTH_TOWERS_DOCT)
	
	ENEMY_TOP_LINE = selectByFaction ( TOP_LINE_ADORN, TOP_LINE_DOCT )
	ENEMY_MID_LINE = selectByFaction ( MID_LINE_ADORN, MID_LINE_DOCT )
	ENEMY_BOT_LINE = selectByFaction ( BOT_LINE_ADORN, BOT_LINE_DOCT )
	
	ENEMY_TOWERS = selectByFaction ( TOTAL_TOWERS_ADORN, TOTAL_TOWERS_DOCT)
	
	ENEMY_BARRACK = selectByFaction( BARACK_ADORN, BARACK_DOCT ) -- группа арсеналов, а не 1 из них
	ENEMY_MAINBUILDING = selectByFaction("MainBuildingB", "MainBuildingA")
	
	ALLY_FIRST_TOWERS = selectByFaction ( FIRST_TOWERS_DOCT, FIRST_TOWERS_ADORN)
	ALLY_MAINBUILDING = selectByFaction("MainBuildingA", "MainBuildingB")
	
	QUEST_DestroyMainBuilding = "TQ_05p"
	
	PLAYER_HERO = selectByFaction( "00", "10" )
	ALLY_HERO_1 = selectByFaction( "01", "11" )
	ALLY_HERO_2 = selectByFaction( "02", "12" )
	ALLY_HERO_3 = selectByFaction( "03", "13" )
	ALLY_HERO_4 = selectByFaction( "04", "14" )
	ENEMY_HERO_1 = selectByFaction( "10", "00" )
	ENEMY_HERO_2 = selectByFaction( "11", "01" )
	ENEMY_HERO_3 = selectByFaction( "12", "02" )
	ENEMY_HERO_4 = selectByFaction( "13", "03" )
	ENEMY_HERO_5 = selectByFaction( "14", "04" )
	ENEMY_HERO_LIST = {ENEMY_HERO_1, ENEMY_HERO_2, ENEMY_HERO_3, ENEMY_HERO_4, ENEMY_HERO_5}

	TOP_ENEMY_HERO = { ENEMY_HERO_1, ENEMY_HERO_2 }
	MID_ENEMY_HERO = { ENEMY_HERO_3 }
	BOT_ENEMY_HERO = { ENEMY_HERO_4, ENEMY_HERO_5 } 
	
	-- Подписываемся на события с миниигрой
		LuaSubscribeUnitEvent(PLAYER_HERO,EventMinigameStarted,"OnMinigameStarted")
		LuaSubscribeUnitEvent(PLAYER_HERO,EventMinigameExit,"OnMinigameEnd")
		LuaSubscribeUnitEvent(PLAYER_HERO,EventMinigameLevelStarted,"OnMinigameLevelStarted")
		LuaSubscribeUnitEvent(PLAYER_HERO,EventMinigameLevelFailed,"OnMinigameLevelFailed")
		LuaSubscribeUnitEvent(PLAYER_HERO,EventMinigameLevelWon,"OnMinigameLevelWon")
	-- Конец блока
	
	NeedPrimeForBuy = 300 -- условие на триггер для покупки таланта, вбиваем кол-во прайма

	if not debugModeOn or debugCameraCinematic then
		cameraName1 = selectByFaction( "/Maps/Multiplayer/MOBA/cameraA.CSPL", "/Maps/Multiplayer/MOBA/cameraB.CSPL" )
		cameraTime1 = 15
		
		CinematicCameraOn = false
		CinematicCameraSTART = false
		CinematicCameraSECOND = false
		CinematicCameraEnd = false
	end
end

function PlayerOut () 	-- Ждем когда игрок попед в одну из трех областей, и сохраняем это для статистики.

	LuaSetSpawnCreeps( true )
	LuaSetSpawnNeutralCreeps( true )
	LuaSetCreepsLevelupPaused ( false )
	LuaSetAchievmentsEnabled(true)
	
	AllAiOn() -- Запускаем ботов
	-- 
end

function PrimaryQuestTracker()
	QuestTrackerTime = 3 -- интервал для анимации убирания квеста и добавления нового
	
	EnemyTowersSetup()
	EnemyBarracksSetup()
	LuaSetUnitStat("local", 18, LuaGetUnitStat("local", 18)*localHeroBaseAttackMul)
	LuaApplyPassiveAbility (ALLY_MAINBUILDING, "AbilityBuffHeroes")
	CreateArrows() -- Создаем указатели направлений лайна
	
	TerrainUp()
	
	if LuaCameraGetLock () then
		LuaCameraObserveUnit( "" )
	end
	
	idleX, idleY = LuaUnitGetPosition ( "local" )
	-- Ждем пока игрок покинет базу

	SetGlobalVar("currentPQ", "01")
	WaitForHeroLeaveArea ( "local", MY_BASE_COORDINATE.x, MY_BASE_COORDINATE.y, MY_BASE_RADIUS)
	EndQuest( "TQ_01p" )
	
	SetGlobalVar("currentPQ", "02")
	
	Wait (QuestTrackerTime) -- интервал на анимации GUI заданий
	
	PlayerOut ()
	
	HintHeroIsLeaveBase = true
	
	ConstructWaitConditionState(CheckDialogFalse)
	
	-- Уничтожить первую башню на любой линии
	StartQuest( "TQ_02p" )
	WaitSomeUnitDead( ENEMY_FIRST_TOWERS )
	EndQuest( "TQ_02p" )

	SetGlobalVar("currentPQ", "WaitSecondTowerDestroy")
	
	Wait (QuestTrackerTime) -- интервал на анимации GUI заданий
	
	ConstructWaitConditionState(CheckDialogFalse)
	
	StartQuest( "TQ_03p" ) -- Уничтожить последние бани на любой линии
		
	FirstTowerDestroy = true -- включаем хинт, что уничтожать башню это хорошо

	WaitSomeUnitDead( ENEMY_SECOND_TOWERS ) -- ждем, когда уничтожат одну башню из второго ряда
	SecondTowerDestroyForPing = true  -- отслеживаем уничтожение второй башни, чтобы отключить пинги на миникарте, сообщающие об атаке на союзную башню
	SetGlobalVar("currentPQ", "03")
	
	LogSessionEvent ( "Second_Tower_Destroyed" ) -- отслеживаем в логах

	ConstructWaitConditionState( GroupTowersDead, ENEMY_LAST_TOP_TOWERS, ENEMY_LAST_MID_TOWERS, ENEMY_LAST_BOT_TOWERS )
	EndQuest( "TQ_03p" )
	SetGlobalVar("currentPQ", "04")
	
	Wait (QuestTrackerTime) -- интервал на анимации GUI заданий
	
	LuaSetManualGameFinish (true) -- переходим на ручной контроль за завершением игры
	
	-- Уничтожить один из Арсеналов
	ConstructWaitConditionState(CheckDialogFalse)
	
	StartQuest( "TQ_04p" )
	
	LineTowersDestroed = true
	
	ConstructWaitConditionState( DestroyedBarrack, ENEMY_BARRACK)
	EndQuest( "TQ_04p" )
	SetGlobalVar("currentPQ", "05")
	
	Wait (QuestTrackerTime) -- интервал на анимации GUI заданий

	ConstructWaitConditionState(CheckDialogFalse)
	
	-- Уничтожте главное здание!
	StartQuest( QUEST_DestroyMainBuilding, true )

	DestroedEnemyBarrack = true -- включаем хинт, что уничтожать баррак это хорошо

	WaitForUnitsDead( ENEMY_MAINBUILDING )
	LogSessionEvent ( "EnemyMainBuilderDestroyed" ) -- отслеживаем в логах

	
	EndQuest( QUEST_DestroyMainBuilding, true )
	DestroedMainBuilding = true
	
	Wait (2) --Задержка перед концом игры нужна, чтобы экран не затемнялся--
	LuaDebugTrace( "Debug:  Туториал завершен!" )
	LuaGameFinish( selectByFaction ( 2, 1) ) -- нужна функция, которая будет следить за нашем зданием, а вообще нужна нам эта проверка?
end


function SecondaryQuestTracker()
		
	while not HintPause and not CinematicCameraOn and not DestroedMainBuilding do

		x, y = LuaUnitGetPosition ( "local" )
		dead = LuaUnitIsDead( "local" ) -- проверяем умер игрок или нет
		currentLevel = LuaHeroGetLevel("local")
		health, maxHealth = LuaUnitGetHealth( "local" )
		
		if(currentLevel ~= lastLevel) then
			lastLevel = currentLevel
			LogSessionEvent ( "MyHeroLevel_" ..lastLevel ) -- отслеживаем в логах
		end
		
		-- Вражеский баррак уничтожен, какие плюшки мы получим за это?!
		if HintHeroIsLeaveBase then
	
			-- Первая башня уничтожена, как хорошо уничтожать башни!
			if FirstTowerDestroy then 
			
				if not FirstTowerDestroyHint and CheckDialogFalse() then
					FirstTowerDestroyHint = true									
					SimpleHint ( "TD_19", 8 )
				end

				if LineTowersDestroed and CheckDialogFalse() then
					LineTowersDestroed = false
					SimpleHint ( "TD_22", 8 )
				end		
			
				if DestroedEnemyBarrack and not HintDestroyEnemyBarrack and CheckDialogFalse() then
					HintDestroyEnemyBarrack = true
					PushHints ( "TD_13", Image13 )
				end		

				if not debugModeOn and DestroedEnemyBarrack then EnemyAIController() end
			end
			
			EnemyBuildingController(15) -- вешаем иммун на башни, пока игрок их не уничтожит
			
			ArrowsControl() -- Указатель на текующие цели в игре
			
			-- Когда про портал уже рассказали и у нас снова мало Здоровья
			if PortalQuestDone then 
		
				if LowHpTimer > LowHpCoolDown and CheckDialogFalse() then
				
					if health/maxHealth < 0.4 and not LuaIsUnitAttacked("local") and not dead then
						SimpleHint ("TD_17", 8)
						LowHpTimer = 0
					end
				else			
					LowHpTimer = LowHpTimer + GetStepLengthInSeconds()
				end
			end
			
			-- Ждем, когда у героя игрока станет мало Здоровья и он использует портал
			if (not debugModeOn or debugPortalUse) and not usePortalOn and not LuaIsUnitAttacked("local") and not PortalQuestDone then UsePortal(50, dead, health, maxHealth) end
			
			-- Рассказываем про лок камеры
			if not debugModeOn then CameraLockChangeHint(3) end

			-- Когда у игрока бьет башня, а он один
			if (not debugModeOn or debugTowersAttack) then AttackedByTower(x, y, 16) end
			
			-- Когда враги бьют мои башни
			if not debugModeOn and not SecondTowerDestroyForPing then AllyTowersAttacked() end
			
			-- Первая смерть игрока
			if (not debugModeOn or debugFirstDeath) and not FirstDeath then WaitFirstDeath(dead, 2) end 
			
			-- Ждем, когда игрок вернется на базу и окажется около магазина
			if (not debugModeOn or debugNearShop) and not AboutShop and not dead then WaitNearShop(x, y, 11, 2) end 
			
			-- Ждем, когда игрок наткнется на не поднятый флаг
			if (not debugModeOn or debugTerrainFlagUp) and not TerrainFlagUp then WaitTerrainFlagUp(x, y, 16) end 
		
			-- Ждем первую покупку таланта
			if (not debugModeOn or debugFirstBuyTalent) and not FirstBouthDone then WaitFirstBuyTalent() end 
			
			-- Ждем, когда игрок встретит солдат врага
			if not debugModeOn then WaitHeroNearEnemySolder(x, y, 10, 1) end 
			
			-- Выполнил задание на убийства солдат и мы рассказывем, что ластхитить их это еще лучше
			if (not debugModeOn or debugKillSolders) and KillSoldersDone and not KillSoldersHint and CheckDialogFalse() then SimpleHint ( "TD_21", 8 ) KillSoldersHint = true end
			
			-- Ждем, когда игрок встретит любого нейтрального крипа		
			if (not debugModeOn or debugKillCreeps)	then WaitHeroNearCreep(x, y, 10 ) end
			
			-- Ждем, когда игрок наткнется на глиф и поднимит его
			if (not debugModeOn or debugPickGlyph) and not GlyphFind then PickUpGlyph(x, y, 14) end 
			
			-- Встретили Баюна
			if (not debugModeOn or debugNearCat) and not CatFound then WaitFindCat(x, y, 14, BOSS_CAT_HOME.x, BOSS_CAT_HOME.y) end 
			
			-- Встретили Горыныча 
			if (not debugModeOn or debugNearDragon) and not DragonFound then WaitFindDragon(x, y, 14, BOSS_DRAGON_HOME.x, BOSS_DRAGON_HOME.y) end 
			
			-- Проверяем, что игрок сделал ассист на вражеском герое в первый раз
			if (not debugModeOn or debugAssists) then HeroKillsAssisted () end
			
			if (not debugModeOn or debugAssists) then EnemyHeroKilled () end
			
			MainBuildingDestroyed () -- На случай если разрушили нашу базу
				
			EnemyHeroUpdate() -- Нерфим статы вражеским героям
			
			-- Ждем если есть рядом нейтральный крипы или солдаты, чтобы игрок использовал талант
			if CreepsFoundCount > 0 or SoldersNumb > 0 and CheckDialogFalse() then WaitUseTalents("TD_24", 30) end
			
		else 
			if not StartHint then
				StartHint = true
				PushHints ( "TD_01", Image1 )
			end	
			
			-- ПЕРВЫЙ СИНЕМАТИК!
			if (not debugModeOn or debugCameraCinematic) and not CinematicCameraEnd then 
				CameraCinematic("TD_00")
				firstCameraLocked = LuaCameraGetLock() -- это старый лок камеры
			end

			if not debugModeOn and CinematicCameraEnd then 
				
				CameraLockChangeDetected()
				
				if not AboutMove and CheckDialogFalse() then 
					WaitPlayerMove(idleX, idleY, 4) -- Учим игрока муваться, если он не умеет	 
				else					
					if not LineHint and CheckDialogFalse() then
						LineHint = true
						PushHints ( "TD_03", Image3 ) -- Рассказываем про линии
					end
					
					if LineHint and not sound1 and CheckDialogFalse() then
					sound1Timer = sound1Timer + GetStepLengthInSeconds()
						if sound1Timer > 2 then
							sound1 = true
							sound1Timer = 0
							LuaDebugTrace( "DEBUG: TSound_3 START!!!") 
							SimpleHint ( "TSound_3", 8 ) 
						end
					end
				end

			end
		end
		
		-- Когда у игрока много прайма и он тупит
		if not debugModeOn and (FirstBouthDone or ChechCount == 1) then ALotPrime() end
		
		-- Ждем, когда игрок окажется около миниигры
		if (not debugModeOn or debugMiniGameOn) and not MiniGameOn then WaitToTheMinigame() end 

		SleepState()
	end
end

function CheckDialogFalse() -- спрашиваем, а запущен у нас сейчас диалог или нет (true - если запущен)
	local dialogContinie = LuaIsDialogFinished ("")
	
	--LuaDebugTrace( "CheckDialogFalse: " ..tostring(dialogContinie)) 
	if dialogContinie and not HintPause then
		return true
	else
		return false
	end
end
	
	
function ImageSetup() -- A (M,F), B(M,F)
	Image1 = selectByFaction(selectByGender( "Image_M_A", "Image_F_A"), selectByGender("Image_M_B", "Image_F_B")) 
	Image2 = selectByFaction(selectByGender( "Image_2m_A", "Image_2f_A"), selectByGender("Image_2m_B", "Image_2f_B"))
	Image3 = selectByFaction(selectByGender( "Image_3m_A", "Image_3f_A"), selectByGender("Image_3m_B", "Image_3f_B"))
	Image4 = selectByFaction(selectByGender( "Image_4m_A", "Image_4f_A"), selectByGender("Image_4m_B", "Image_4f_B"))
	Image5 = selectByFaction(selectByGender( "Image_5m_A", "Image_5f_A"), selectByGender("Image_5m_B", "Image_5f_B"))
	Image6 = selectByFaction(selectByGender( "Image_6m_A", "Image_6f_A"), selectByGender("Image_6m_B", "Image_6f_B"))
	Image7 = selectByFaction(selectByGender( "Image_7m_A", "Image_7f_A"), selectByGender("Image_7m_B", "Image_7f_B"))
	Image8 = selectByFaction(selectByGender( "Image_8m_A", "Image_8f_A"), selectByGender("Image_8m_B", "Image_8f_B"))
	Image9 = selectByFaction(selectByGender( "Image_9m_A", "Image_9f_A"), selectByGender("Image_9m_B", "Image_9f_B"))
	Image10 = selectByFaction(selectByGender( "Image_10m_A", "Image_10f_A"), selectByGender("Image_10m_B", "Image_10f_B"))
	Image11 = selectByFaction(selectByGender( "Image_11m_A", "Image_11f_A"), selectByGender("Image_11m_B", "Image_11f_B"))
	Image13 = selectByFaction(selectByGender( "Image_13m_A", "Image_13f_A"), selectByGender("Image_13m_B", "Image_13f_B"))
	Image14 = selectByFaction(selectByGender( "Image_14m_A", "Image_14f_A"), selectByGender("Image_14m_B", "Image_14f_B"))
	Image15 = selectByFaction(selectByGender( "Image_15m_A", "Image_15f_A"), selectByGender("Image_15m_B", "Image_15f_B"))
	Image16 = selectByFaction(selectByGender( "Image_16m_A", "Image_16f_A"), selectByGender("Image_16m_B", "Image_16f_B"))
	Image20 = selectByFaction(selectByGender( "Image_20m_A", "Image_20f_A"), selectByGender("Image_20m_B", "Image_20f_B"))
	Image23 = selectByFaction(selectByGender( "Image_23m_A", "Image_23f_A"), selectByGender("Image_23m_B", "Image_23f_B"))

end

function TerrainUp()
	-- ПОДНИМАЕМ ФЛАГИ ЗА ОБЕ СТОРОНЫ
	table.foreach(FLAGSPOLES_ADORN_SECOND, function(k,v) LuaCaptureTheFlag( v , 2, true) LuaDebugTrace("LuaCaptureTheFlag: " ..tostring(v)) end)
	table.foreach(FLAGSPOLES_DOCT_SECOND, function(k,v) LuaCaptureTheFlag( v , 1, true) LuaDebugTrace("LuaCaptureTheFlag: " ..tostring(v)) end)
	
	table.foreach(FLAGSPOLES_ADORN_FIRST, function(k,v) LuaCaptureTheFlag( v , 2, true) LuaDebugTrace("LuaCaptureTheFlag: " ..tostring(v)) end)
	table.foreach(FLAGSPOLES_DOCT_FIRST, function(k,v) LuaCaptureTheFlag( v , 1, true) LuaDebugTrace("LuaCaptureTheFlag: " ..tostring(v)) end)
	-- ЗАКОНЧИЛИ ПОДНИМАТЬ ФЛАГИ
end

function EnemyTowersSetup()
	table.foreach(ENEMY_FIRST_TOWERS, function(k,v)
		LuaSetUnitStat( v, 0, firstTowersHP)
		LuaApplyPassiveAbility(v, "DecreaseTowerDamage" ) 
	end)
	
	table.foreach(ENEMY_SECOND_TOWERS, function(k,v) 
		LuaSetUnitStat( v , 0, secondTowersHP) 
		LuaApplyPassiveAbility(v, "DecreaseTowerDamage" ) 
	end)
	
	table.foreach(ENEMY_LAST_TOWERS, function(k,v) 
		LuaSetUnitStat( v , 0, lastTowersHP) 
		LuaApplyPassiveAbility(v, "DecreaseTowerDamage" ) 
	end) 
	
	LuaSetUnitStat( ENEMY_MAINBUILDING, 0, enemyMainBuildingHP )
	
end

function EnemyBarracksSetup()

	table.foreach(ENEMY_BARRACK, function(k,v) LuaSetUnitStat( v, 0, enemyBarracksHP) end)
end

function AllAiOn()
	LuaAISwitcher(ALLY_HERO_1, true, tonumber(0))
	LuaAISwitcher(ALLY_HERO_2, true, tonumber(1))
	LuaAISwitcher(ALLY_HERO_3, true, tonumber(2))
	LuaAISwitcher(ALLY_HERO_4, true, tonumber(2))
	
	table.foreach(TOP_ENEMY_HERO, function(k,v) LuaAISwitcher(v, true, tonumber(0)) end) 
	table.foreach(MID_ENEMY_HERO, function(k,v) LuaAISwitcher(v, true, tonumber(1)) end)
	table.foreach(BOT_ENEMY_HERO, function(k,v) LuaAISwitcher(v, true, tonumber(2)) end)
end

function AllyAIPush(numberLine)
	if numberLine == 0 then
		LuaAISwitcher(ALLY_HERO_2, false, 0)
		LuaAISwitcher(ALLY_HERO_3, false, 0)
		LuaAISwitcher(ALLY_HERO_4, false, 0)
		
		LuaAISwitcher(ALLY_HERO_2, true, tonumber(numberLine))
		LuaAISwitcher(ALLY_HERO_3, true, tonumber(numberLine))
		LuaAISwitcher(ALLY_HERO_4, true, tonumber(numberLine))
	elseif numberLine == 1 then
		LuaAISwitcher(ALLY_HERO_1, false, 0)
		LuaAISwitcher(ALLY_HERO_3, false, 0)
		LuaAISwitcher(ALLY_HERO_4, false, 0)
		
		LuaAISwitcher(ALLY_HERO_1, true, tonumber(numberLine))
		LuaAISwitcher(ALLY_HERO_3, true, tonumber(numberLine))
		LuaAISwitcher(ALLY_HERO_4, true, tonumber(numberLine))
	else 
		LuaAISwitcher(ALLY_HERO_1, false, 0)
		LuaAISwitcher(ALLY_HERO_2, false, 0)
		
		LuaAISwitcher(ALLY_HERO_1, true, tonumber(numberLine))
		LuaAISwitcher(ALLY_HERO_2, true, tonumber(numberLine))
	end
end

function EnemyAIController()

	if(timerControllerAI >= controllerAICoolDown) then
		LuaDebugTrace( "EnemyAIController: pushLineNumber:" ..pushLineNumber) 
		timerControllerAI = 0
		if pushLineNumber == 0 then
			LuaAISwitcher(ENEMY_HERO_3, false, 0)
			LuaAISwitcher(ENEMY_HERO_4, false, 0)
			LuaAISwitcher(ENEMY_HERO_5, false, 0)
						
			LuaAISwitcher(ENEMY_HERO_3, true, tonumber(1))
			LuaAISwitcher(ENEMY_HERO_4, true, tonumber(2))
			LuaAISwitcher(ENEMY_HERO_5, true, tonumber(2))
		
		elseif pushLineNumber == 1 then		
			LuaAISwitcher(ENEMY_HERO_1, false, 0)
			LuaAISwitcher(ENEMY_HERO_2, false, 0)
			LuaAISwitcher(ENEMY_HERO_4, false, 0)
			LuaAISwitcher(ENEMY_HERO_5, false, 0)
		
			LuaAISwitcher(ENEMY_HERO_1, true, tonumber(0))
			LuaAISwitcher(ENEMY_HERO_2, true, tonumber(0))
			LuaAISwitcher(ENEMY_HERO_4, true, tonumber(2))
			LuaAISwitcher(ENEMY_HERO_5, true, tonumber(2))
			
		else 		
			LuaAISwitcher(ENEMY_HERO_1, false, 0)
			LuaAISwitcher(ENEMY_HERO_2, false, 0)
			LuaAISwitcher(ENEMY_HERO_3, false, 0)
		
			LuaAISwitcher(ENEMY_HERO_1, true, tonumber(0))
			LuaAISwitcher(ENEMY_HERO_2, true, tonumber(0))
			LuaAISwitcher(ENEMY_HERO_3, true, tonumber(1))
		end
	else 
		timerControllerAI = timerControllerAI + GetStepLengthInSeconds()
	end
end

function CameraCinematic (currentCinematicName)

	CinematicCameraOn = true
	
	LuaSetAdventureControlsEnabled( false, false )
	
	LuaCameraObserveUnit( "" )
	
	RemoveWarfogAll( true )
	
	_, _, cameraRodBeforeCinematic = LuaCameraGetPos();
	LuaStartCinematic ( currentCinematicName ) -- Диалог с кнопочкой, который мы будем ждать
	LuaSplineCameraTimedNew (cameraName1, cameraTime1) -- Собственно сам синематик

	while not CinematicCameraSTART do -- Ждем пока закончится ролик или игрок отменит его
	
		if LuaIsDialogFinished (currentCinematicName) or not LuaIsSplineCameraActive() then
			CinematicCameraSTART = true
			LuaSplineCameraShutdown()
			LuaDebugTrace( "DEBUG: First CINEMATIC END!!!") 
		end
		SleepState()
	end
	
	LuaCameraObserveUnit( "local" )
	LuaZoomCamera( cameraRodBeforeCinematic, 0.5 )
	
	RemoveWarfogAll( false )
	LuaSetAdventureControlsEnabled( true, true )
	
	local timer = 0
	
	while timer < 3 do
		timer = timer + GetStepLengthInSeconds()
		SleepState ()
	end
	
	StartQuest( "TQ_01p" )
	
	CinematicCameraEnd = true	
	CinematicCameraOn = false
end

function AttackedByTower (x, y, distance) 
	if TowerAttackTimer < TowerAttackCooldown then
		TowerAttackTimer = TowerAttackTimer + GetStepLengthInSeconds()
	else
		if LuaIsUnitAttacked("local") then 
			if LuaGetUnitsInArea( towersFactionMask, towerTypeMask, x, y, distance) >= 1 then  
				table.foreach(ENEMY_TOWERS, 
				function(k,v) local dead = LuaUnitIsDead( v )
					if dead == false then
						if LuaIsUnitAttackedByObject( "local", v ) then
							tx, ty = LuaUnitGetPosition ( v ) -- для того, чтобы понять кто находится рядом с башней в момент атаки
							
							if LuaGetUnitsInArea( allySoldersFactionMask, solderTypeMask, tx, ty, distance) <= 0 then
							
								AttackedHeroAlone = true
								LogConverterStart("Alone_" ..v)
								return
								
							elseif LuaGetUnitsInArea( allySoldersFactionMask, noSiegeTypeMask, tx, ty, distance) <= 0 and not TowerAttackWithSiege then
							
								LogConverterStart("WithSiege_" ..v)
								AttackedHeroWithSiege = true
								return
								
							elseif SomeEnemyHeroAttacked( v ) == true then
												
								LogConverterStart("TryEnemyHero_" ..v)
								AttackedHero = true
								return								
							end
						end
					else 
						LogConverterStart("EnemyTowerLost_" .. v)
						table.remove(ENEMY_TOWERS, k)
					end
				end)	
			end
		end
	end
	if AttackedHeroAlone then
		AttackedHeroAlone = false
		TowerAttackTimer = 0
		LuaDebugTrace("Hero was staing alone!")
		PushHints ("TD_04", Image4)
		
	elseif AttackedHeroWithSiege and not TowerAttackWithSiege then
		AttackedHeroWithSiege = false
		TowerAttackWithSiege = true
		TowerAttackTimer = 0
		LuaDebugTrace("Hero was staing with siege!")
		PushHints ("TD_14", Image14)
		
	elseif AttackedHero then	
		AttackedHero = false
		TowerAttackTimer = 0
		PushHints ("TD_23", Image23)
		
	end	
end

function SomeEnemyHeroAttacked ( attackedObj )

	local findHeroAttacked = false

	if string.find( attackedObj, "Top", 1, true ) then 
		
		findHeroAttacked = table.foreach(TOP_ENEMY_HERO, 
		function(k, v) local dead = LuaUnitIsDead( v )
			if dead == false then
				if LuaIsUnitAttackedByObject( v, "local" ) then
					return true								
				end
			end
		end)

	elseif string.find( attackedObj, "Mid", 1, true ) then 
		
		findHeroAttacked = table.foreach(MID_ENEMY_HERO, 
		function(k, v) local dead = LuaUnitIsDead( v )
			if dead == false then
				if LuaIsUnitAttackedByObject( v, "local" ) then
					return true								
				end
			end
		end)

	elseif string.find( attackedObj, "Bot", 1, true ) then 

		findHeroAttacked = table.foreach(BOT_ENEMY_HERO, 
		function(k, v) local dead = LuaUnitIsDead( v )
			if dead == false then
				if LuaIsUnitAttackedByObject( v, "local" ) then
					return true								
				end
			end
		end)		
	end	

	if findHeroAttacked == nil then
		findHeroAttacked = false
	end
	
	return findHeroAttacked
	
end

function ALotPrime ()
	ALotPrimeTimer = ALotPrimeTimer + GetStepLengthInSeconds()
	
	if ALotPrimeTimer > LowHpCoolDown then
		local heroPrime = LuaHeroGetPrime("local")
		
		if currentLevel ~= heroLevel then
			heroLevel = LuaHeroGetLevel("local")
			if heroLevel >= questLevel[currentPrimeIndex] then
				currentPrimeIndex = currentPrimeIndex + 1
			end
		end
		
		if heroPrime >= questPrime[currentPrimeIndex] then
			ReactWaitTimer = ReactWaitTimer + GetStepLengthInSeconds()
		elseif ReactWaitTimer > 0 then
			ReactWaitTimer = 0
			--LuaDebugTrace( "DEBUG: heroPrime=: "..tostring(heroPrime) )
		end
	end
	
	if ReactWaitTimer > ALotPrimeWait then
		PushHints ("TD_09", Image9) -- хинт на то, как активировать таланты
		ALotPrimeTimer = 0
		ReactWaitTimer = 0
	end
end

function WaitUseTalents(hintID, waitTime)
	
	if usedTalentCount < usedTalentCountNeeded then 
		if not someTalentUsed and LuaHeroGetMana("local") > 200 then
			if timerUseTalents > waitTime then
				if CheckDialogFalse() then
					timerUseTalents = 0		
					usedTalentCount = usedTalentCount + 1
					SimpleHint( hintID, 8 )	
				end
			else
				timerUseTalents = timerUseTalents + GetStepLengthInSeconds()
			end
		else
			someTalentUsed = false
			timerUseTalents = 0
		end	
	end
end

function WaitFirstBuyTalent()

	if currentLevel <= forButLevel then	
		if ChechCount == 0 then
			ChechCount = ChechCount + 1
			
			LogConverterStart("TQ_06s")
			PushHints ("TD_02", Image2) -- хинт на то, как активировать таланты
			StartQuest( "TQ_06s" )
		end		
	elseif ChechCount == 1 then
		FirstBouthDone = true
		ChechCount = ChechCount + 1
		
		EndQuest( "TQ_06s" )
		LogConverterEND("TQ_06s")
	else
		FirstBouthDone = true
	end
end

function WaitFirstDeath(dead, waitTime)
	
	if dead then
		local timer = 0
		HintPause = true
		while timer < waitTime do
			timer = timer + GetStepLengthInSeconds()
			SleepState ()
		end
		HintPause = false
		FirstDeath = true
		SimpleHintHigh ("TD_18", 8 )
	end
end 

function WaitFindDragon(x, y, distance, hx, hy)

	local BossNumb = LuaGetUnitsInArea( creepFactionMask, bossTypeMask, x, y, distance)
	
	if BossNumb >= 1 and DistanceSquared( hx, hy, x, y ) < distance * distance then
		PushHints ("TD_16", Image16)
		DragonFound = true
	end
end

function WaitFindCat(x, y, distance, hx, hy)

	local BossNumb = LuaGetUnitsInArea( creepFactionMask, bossTypeMask, x, y, distance)
	
	if BossNumb >= 1 and DistanceSquared( hx, hy, x, y ) < distance * distance then
		PushHints ("TD_15", Image15)
		CatFound = true
	end
end

function WaitHeroNearEnemySolder( x, y, distance, unitCount)

	local canStartKillEnemySoldiersQuest = not SolderFound and not KillSoldersDone

	if not canStartKillEnemySoldiersQuest then
		return
	end

	SoldersNumb = LuaGetUnitsInArea( soldersFactionMask, solderTypeMask, x, y, distance)	

	if SoldersNumb < unitCount then
		return
	end

	StartQuest( "TQ_07s" )
	LogConverterStart("TQ_07s")
	SolderFound = true
end

function LogConverterStart(questID)
	local saveQuestID = "S" .. GetGlobalVar("currentPQ").. "_" .. questID
	local startQuestID = GetGlobalVar("currentPQ")
	LogSessionEvent ( saveQuestID ) -- отслеживаем в логах
	LuaDebugTrace( "LogEvent: saveQuestID: " ..saveQuestID.. ", startQuestID: "..startQuestID )
	SetGlobalVar("ForLog_".. questID, startQuestID)
end

function LogConverterEND(questID)
	local saveQuestID = "E" .. GetGlobalVar("currentPQ").. "_" ..questID .. "_S" ..GetGlobalVar("ForLog_" .. questID)
	LogSessionEvent ( saveQuestID ) -- отслеживаем в логах
	LuaDebugTrace( "LogEvent: saveQuestID: " .. saveQuestID )
end

function UsePortal(warnPercent, dead, health, maxHealth)
	
	if ( health / maxHealth <=  warnPercent / 100 ) and not usePortalOn and not dead then
		usePortalOn = true
		PushHints ("TD_06", Image6 )
		StartQuest( "TQ_08s" )
		LogConverterStart("TQ_08s")
	end
end

function OnTalentCastProcessed(persistenceId, ownerId)

	local ownerType = LuaGetUnitObjectNameById( ownerId )

	if ownerType == PLAYER_HERO then

		if persistenceId == "tutorial_Portal" then
			LogSessionEvent ( "PortalDone" )

			if not PortalQuestDone then 
				LowHpTimer = 0
				PortalQuestDone = true
		
				if usePortalOn then
					EndQuest( "TQ_08s" )
					LogConverterEND("TQ_08s")
					LuaHeroAddPrime("local", 200)
				end
			end
		else 
			someTalentUsed = true --Заюзан какой-то другой талант
		end
	end
end

function WaitHeroNearCreep( x, y, distance)

	local canStartKillCreepsQuest = not CreepsFound and not KillCreepsDone

	if not canStartKillCreepsQuest then
		return
	end

	CreepsFoundCount = LuaGetUnitsInArea( 1, creepTypeMask, x, y, distance)

	if CreepsFoundCount < 1 then
		return
	end
	
	PushHints ( "TD_11", Image11 )
	StartQuest( "TQ_09s" )
	LogConverterStart("TQ_09s")
	CreepsFound = true
	CreepsQuest = true
end

function PickUpGlyph (x, y, distance)

	local glyphFoundCount = LuaGetUnitsInArea( 1, glyphTypeMask, x, y, distance)
	
	if glyphFoundCount >= 1 then
		PushHints ( "TD_07", Image7 )
		LogConverterStart("TQ_10s")
		LuaSubscribeUnitEvent( "local", EventPickup, "playerPickUpGlyph" )
		GlyphFind = true
		StartQuest( "TQ_10s" )
	end
end

function playerPickUpGlyph ()
	LuaUnsubscribeUnitEvent ("local", EventPickup)

	EndQuest( "TQ_10s" )
	LogConverterEND("TQ_10s")
	LuaHeroAddPrime("local", 200)
end

function WaitToTheMinigame()
	
	if HintHeroIsLeaveBase and IsHeroInArea( "local", minigame1PlaceX, minigame1PlaceY, 12 ) then
		MiniGameOn = true
		PushHints ( "TD_08", Image8 )
	elseif HintHeroIsLeaveBase and IsHeroInArea( "local", minigame2PlaceX, minigame2PlaceY, 10 ) then
		MiniGameOn = true
		PushHints ( "TD_08", Image8 )
	elseif MiniGameEND then
		MiniGameOn = true
		local timer = 0
		while timer < 1 do
			timer = timer + GetStepLengthInSeconds()
			SleepState ()
		end
		PushHints ( "TD_08", Image8 )
	end
end

function OnMinigameEnd()
	if (not MiniGameOn) then
		MiniGameEND = true
	end
	LogConverterStart("MinigameEnd")
	MiniGameStart = false
end

function OnMinigameStarted()
	MiniGameStart = true
	LogConverterStart("MinigameStart")
	if not questMiniGame then
		questMiniGame = true
		StartQuest( "TQ_11s" )
	end
end

function OnMinigameLevelStarted()
	LogConverterStart("ScrollLevelStart")
end

function OnMinigameLevelFailed()
	LogConverterStart("ScrollLevelFailed")
end

function OnMinigameLevelWon()
	LogConverterStart("ScrollLevelWin")
	if questMiniGame and not questMiniGameDone then
		questMiniGameDone = true
		EndQuest( "TQ_11s" )
		LuaHeroAddPrime("local", 200)
	end
end

function WaitTerrainFlagUp (x, y, distance)
		
	local flagpoleCount = LuaGetUnitsInArea( 1, flagpoleTypeMask, x, y, distance)
	
	if flagpoleCount >= 1 then
		TerrainFlagUp = true
		PushHints ( "TD_05", Image5 )
	end
	
end

function WaitNearShop (x, y, distance, waitTime) --проблема, что срабатывает практически мгновенно при ресуректе, нужно добавить таймер
		
	local shopeCount = LuaGetUnitsInArea( shopFactionMask, shopTypeMask, x, y, distance)
	
	if shopeCount >= 1 and not dead then
		AboutShop = true
		local timer = 0
		while timer < waitTime do
			timer = timer + GetStepLengthInSeconds()
			SleepState ()
		end
		PushHints ( "TD_10", Image10  )
	end
	
end

function OnHintDialogClose(dialogId)
	someButttonBubbleWasClicked = true
end

function PushHints ( hintID, ImageID)
	HintPause = true
	
	while MiniGameStart do
		SleepState ()
	end
	
	LuaSetPause( true )

	while LuaIsWindowVisible(WINDOW_ESCMENUBAR) or LuaIsWindowVisible(WINDOW_OPTIONSBAR) or DestroedMainBuilding do
		SleepState ()
	end
	
	local hintPhraseID = hintID .. "_1"

	someButttonBubbleWasClicked = false
	
	LuaSetAdventureControlsEnabled( false, true )

	LuaBeginBlockSection()
		LuaAddNonBlockedElement( "QuestHint", true )
	LuaEndBlockSection( 0.5 )
	
	LuaDebugTrace( "PushHints: " ..hintID)
	LuaShowHintDialog(hintID, hintPhraseID, ImageID)
	
	while not someButttonBubbleWasClicked and not DestroedMainBuilding and not MiniGameStart do
		someButttonBubbleWasClicked = false
		SleepState()
	end
	
	LuaDebugTrace( "PushHintsEND: " ..hintID)
	LuaSetAdventureControlsEnabled( true, true )
	LuaSetPause( false )

	LuaClearBlocking( 0.5 ) --highlight
	
	local timer = 0
	while timer < 1.5 do
		timer = timer + GetStepLengthInSeconds()
		SleepState ()
	end
	
	HintPause = false
end

function SimpleHint (hintID, dialogTime, icon) -- прерывается при первой смерти игрока

	while MiniGameStart do
		SleepState ()
	end

	if icon == nil then
		icon = "None"
	end

	LuaDebugTrace( "SimpleHint: " ..hintID)	
	ShowHintline( hintID, false, icon )
	
	local timer = 0
	if not FirstDeath then 
		while timer < dialogTime and not dead and not MiniGameStart do
			dead = LuaUnitIsDead( "local" )
			timer = timer + GetStepLengthInSeconds()
			SleepState ()
		end
	else 
		while timer < dialogTime and not MiniGameStart do
			dead = LuaUnitIsDead( "local" )
			timer = timer + GetStepLengthInSeconds()
			SleepState ()
		end
	end
	
	ShowHintline( "" )
	LuaDebugTrace( "SimpleHintEND: " ..hintID)
end

function SimpleHintHigh (hintID, dialogTime, icon)

	if icon == nil then
		icon = "None"
	end
	
	ShowHintline( hintID, false, icon )
	LuaDebugTrace( "SimpleHintHigh: " ..hintID)
	
	local timer = 0
	while timer < dialogTime  do
		timer = timer + GetStepLengthInSeconds()
		SleepState ()
	end
	
	ShowHintline( "" )
	LuaDebugTrace( "SimpleHintHighEND: " ..hintID)
 
end

function StartQuest( questID, faction )

	local dialogID = questID..tostring("_Dialog")	
	
	local _questID = questID
	
	if faction == nil then faction = false end
	
	if faction == true then
		_questID = questID .. tostring(selectByFaction("_A", "_B"))
	end

	LuaAddSessionQuest( _questID )
		
	if CheckDialogFalse() then
		LuaDebugTrace( "StartQuest: " ..dialogID)
		LuaStartDialog( dialogID )	
	end
		
end

function EndQuest( questID, faction )

	local _questID = questID

	if faction == nil then faction = false end
	
	if faction == true then
		_questID = questID .. tostring(selectByFaction("_A", "_B"))
	end

	LuaRemoveSessionQuest( _questID )

	if CheckDialogFalse() and not HintPause then
		if currentQuestDialog < GetTableSize(dialogQuestTable) then 
			currentQuestDialog = currentQuestDialog + 1
		else
			currentQuestDialog = 1
		end

		LuaStartDialog( dialogQuestTable[currentQuestDialog] )
		LuaDebugTrace( "StartQuest: " ..dialogQuestTable[currentQuestDialog])
	end
end

-- Эта функция вызывается автоматически, ее никуда в стейты вписывать не нужно
-- lastHitterId, deathParamsInfo - убирать нельзя, они нужны, для корректной работы функции
function OnUnitDie( victimId, killerId, lastHitterId, deathParamsInfo ) 

	local isKillEnemySoldiersQuestActive = SolderFound and not KillSoldersDone

	if killerId == -1 or victimId == -1 or not isKillEnemySoldiersQuestActive then
		return
	end
	
	local unitType = LuaGetUnitTypeById( victimId )
	local unitFaction = LuaGetUnitFactionById( victimId )
	local distanceFromMe = 20

	local heroId = LuaGetUnitIdByObjectName("local")

	local isEnemy = unitFaction == FACTION_ENEMY
	local isSoldier = unitType == UnitTypeCreep or unitType == UnitTypeSiegeCreep
	local isInRange = LuaUnitsInRange(heroId, victimId, tonumber(distanceFromMe))

	if isEnemy and isSoldier and isInRange then
		solderKills = (solderKills or 0) + 1

		LuaUpdateSessionQuest("TQ_07s", solderKills)

		local needKills = 5

		if solderKills < needKills then
			return
		end

		KillSoldersDone = true
		EndQuest( "TQ_07s" )
		LogConverterEND("TQ_07s")
		LuaHeroAddPrime("local", 200)
	end
end

function OnCreepSpawnerCleaned(spawnerName, killerId)
	
	LogConverterStart( "ClearSpawn_" ..spawnerName)

	local isKillCreepsQuestActive = CreepsFound and not KillCreepsDone
	local isBossSpawner = spawnerName == "Boss_Cat" or spawnerName == "Boss_Dragon"
	
	if killerId == -1 or isBossSpawner or not isKillCreepsQuestActive then
		return
	end

	local killerType = LuaGetUnitTypeById( killerId )
	local killerScriptId = LuaGetUnitObjectNameById(tonumber(killerId))
	
	LuaDebugTrace( "DEBUG: Spawner clean: " ..tostring(killerType).. ", где killerScriptId: " ..tostring(killerScriptId)) 
	
	if killerScriptId == PLAYER_HERO then
		KillCreepsDone = true
		EndQuest( "TQ_09s" )
		LogConverterEND("TQ_09s")
		LuaHeroAddPrime("local", 200)
	end
end

local lastKillStep = nil

function EnemyHeroKilled()
	local kills = LuaStatisticsGetTotalNumHeroKills("local")

	if kills <= lastKills then
		return
	end

	local step = GetGameStep()

	if lastKillStep == nil then
		lastKillStep = step
	end

	local delta = kills - lastKills
	local steps = step - lastKillStep

	lastKills = kills
	lastKillStep = step

	local dontGuard = (delta > 1) or (steps < 5)

	while delta > 0 do
		delta = delta - 1

		LogSessionEvent ( "KillEnemyHero", dontGuard ) -- отслеживаем в логах
	end
end

local lastAssistStep = nil

function HeroKillsAssisted()
	local assists = LuaStatisticsGetTotalNumHeroAssists("local")
	
	if assists <= lastAssists then
		return
	end

	if not AssistEnemyHero then
		AssistEnemyHero = true
		PushHints ( "TD_20", Image20 )
	end

	local step = GetGameStep()

	if lastAssistStep == nil then
		lastAssistStep = step
	end

	local delta = assists - lastAssists
	local steps = step - lastAssistStep

	lastAssists = assists
	lastAssistStep = step

	local dontGuard = (delta > 1) or (steps < 5)

	while delta > 0 do
		delta = delta - 1

		LogSessionEvent ( "AssistEnemyHero", dontGuard )
	end
end

function CreateArrows()
	--local placeArrowA = {x=29.8, y=189.6, z=-3.5}
	--local placeArrowB = {x=375.4, y=183, z=-0.3}
	
	local placeArrowA = {x=0, y=0, z=0}
	local placeArrowB = {x=0, y=0, z=0}

	local placeArrow = selectByFaction( placeArrowA, placeArrowB )
	local Arrow = selectByFaction( "ArrowsA", "ArrowsB" )
	
	LuaPlaceSimpleObject(Arrow, placeArrow.x, placeArrow.y, placeArrow.z)

end

function RemoveWarfogAll( warfogState ) -- Если true - открываем варфог на все карте при условии, что на ней есть ГЗ с именем "MainA"
	if warfogState then
		LuaUnitApplyApplicatorFromUnit( ALLY_MAINBUILDING, "local", "RemoveWarfog")
	else
		LuaUnitRemoveApplicator( ALLY_MAINBUILDING, "RemoveWarfog")
	end
end

function GroupTowersDead(name1, name2, name3)

	local name1Count = 0;
	local name2Count = 0;
	local name3Count = 0;

	if ( type( name1 ) == "table" ) and ( type( name2 ) == "table" ) and ( type( name3 ) == "table" ) then
		for i = 1, #name1 do
			local dead, found = LuaUnitIsDead( name1[i] )
			if ( dead == true ) then
				name1Count = name1Count + i
			end
		end
		for i = 1, #name2 do
			local dead, found = LuaUnitIsDead( name2[i] )
			if ( dead == true ) then
				name2Count = name2Count + i
			end
		end
		for i = 1, #name3 do
			local dead, found = LuaUnitIsDead( name3[i] )
			if ( dead == true ) then
				name3Count = name3Count + i
			end
		end
	end
	
	if name1Count >= 3 then
		LogSessionEvent ( "Last_TowersDestroyed_Top" )
		return true
	elseif name2Count >= 3 then
		LogSessionEvent ( "Last_TowersDestroyed_Mid" )
		return true
	elseif name3Count >= 3 then
		LogSessionEvent ( "Last_TowersDestroyed_Bot" )
		return true
	else 
		return false
	end
end

function DestroyedBarrack(name1)
	if ( type( name1 ) == "table" ) then
		for i = 1, #name1 do
			local dead, found = LuaUnitIsDead( name1[i] )
			if ( dead == true ) then
				pushLineNumber = i - 1
				LogSessionEvent ( "EnemyBarrackDestroed_" ..name1[i] ) -- отслеживаем в логах
				LuaDebugTrace("EnemyBarrackDestroed: " ..pushLineNumber)
				local mainX, mainY = LuaUnitGetPosition (ALLY_MAINBUILDING) --MY_BASE_COORDINATE.x, MY_BASE_COORDINATE.y -- 
				if pushLineNumber ~=0 then	LuaHeroAIDisable(ALLY_HERO_1) end
				if pushLineNumber ~=1 then  LuaHeroAIDisable(ALLY_HERO_2) end
				if pushLineNumber ~=2 then
					LuaHeroAIDisable(ALLY_HERO_3)
					LuaHeroAIDisable(ALLY_HERO_4)
				end;
				Wait(0.5)
				if pushLineNumber ~=0 then LuaUsePortalToPos (ALLY_HERO_1, mainX, mainY) end
				if pushLineNumber ~=1 then LuaUsePortalToPos (ALLY_HERO_2, mainX, mainY) end
				if pushLineNumber ~=2 then 
					LuaUsePortalToPos (ALLY_HERO_3, mainX, mainY)
					LuaUsePortalToPos (ALLY_HERO_4, mainX, mainY)
				end
				Wait(5)
				AllyAIPush(pushLineNumber)
				return true
			end
		end
		return false
	end
end

function AllyTowersAttacked()
	
	if AlarmTimer >= AlarmCoolDown then
		
		table.foreach(ALLY_FIRST_TOWERS, 
		function(k,v) local dead = LuaUnitIsDead( v )
			
			if dead == false then
				if LuaIsUnitAttacked(v) and CheckDialogFalse() then
					AlarmTimer = 0
					LuaDebugTrace("AllyTowersAttacked: " ..tostring( v ))
					local signalTowerX, signalTowerY = LuaUnitGetPosition( v )
					LuaCreateMinimapSignal( signalTowerX, signalTowerY )
					LuaStartDialog ( "TSound_1" )
					LogConverterStart("AllyTowerAttacked_" .. v)
					return true
				end
			else
				LuaDebugTrace( "AllyTowerDestroyed: "  ..tostring( v ))
				LogConverterStart("AllyTowerDestroyed_" .. v)
				table.remove(ALLY_FIRST_TOWERS, k)
			end
			
		end)
	else 

		AlarmTimer = AlarmTimer + GetStepLengthInSeconds()
		
	end
	
end

function MainBuildingDestroyed ()
	if AreUnitsDead( ALLY_MAINBUILDING ) then
		LuaDebugTrace( "Debug:  Туториал завершен!" )
		LuaGameFinish( selectByFaction ( 1, 2) )
	end
end

function EnemyHeroUpdate()
	table.foreach(ENEMY_HERO_LIST, 
	function(k,v) local dead = LuaUnitIsDead( v )
		if dead == false then
			EnemyHeroStats(v, statsHero, statsModifier)
		end
	end)
end

function EnemyHeroStats(hero, statsData, statModifier)
		
	local lastLevel = GetGlobalVar("lastLevel"..hero) 
	local currentLevel = LuaHeroGetLevel(hero)
		
	if ( lastLevel ~= currentLevel ) then
		SetGlobalVar( "lastLevel"..hero, currentLevel )
		
		local stats = statsData
		
		for i=1, #stats do
			local lastStat = GetGlobalVar("stat"..tostring(stats[i])..hero) 

			if(lastStat == nil) then lastStat = 0 end

			local modifierStat = (LuaGetUnitStat( hero, stats[i] ) - lastStat) * statModifier + lastStat
			LuaSetUnitStat( hero, stats[i], modifierStat)
			SetGlobalVar( "stat"..tostring(stats[i])..hero, modifierStat )
		end	 
	end
end

function HintAboutMove(waitTime)   -- ЛКМ/ПКМ хинтлайн для движения	
	if LuaGetControlStyle() then   
		LuaDebugTrace( "DEBUG: вызываем хинтлайн для ЛКМ мува") 
		SimpleHint( "TD_25_LMC", waitTime, "LeftClick")
		aboutMoveID = false
	else
		LuaDebugTrace( "DEBUG: вызываем хинтлайн для РКМ мува") 
		SimpleHint( "TD_25_RMC", waitTime, "RightClick")
		aboutMoveID = false
	end
end

function WaitPlayerMove(ix, iy, waitTime)

	if not (DistanceSquared( ix, iy, x, y ) > 4 * 4) then --В идеале тут надо проверять на Idle, но это мы пока не можем фиксировать
		if idleTime > waitTime and not aboutMoveID then
			if CheckDialogFalse() then
				idleTime = 0
				aboutMoveID = true
				AboutMove = true
				HintAboutMove(6)

				local timer = 0
				while timer < 1.5 do
					timer = timer + GetStepLengthInSeconds()
					SleepState ()
				end

				SimpleHint( "TD_27", 6)

			end
		else
			idleTime = idleTime + GetStepLengthInSeconds()
		end
	else 
		AboutMove = true
		idleTime = 0
	end
end

function CameraLockChangeHint(waitTime) --Если игрок не сменил лок камеры
	if not playerChangeLock then
		local isCameraLocked = LuaCameraGetLock() -- проверяем на текущий лок камеры
			
		if isCameraLocked ~= firstCameraLocked then
			firstCameraLocked = isCameraLocked
			playerChangeLock = true			
			
		elseif changeLockTime > waitTime and CheckDialogFalse() then
			playerChangeLock = true
			SimpleHint( "TD_26", 6)

		else
			changeLockTime = changeLockTime + GetStepLengthInSeconds()
		end
	end
end

function CameraLockChangeDetected()
	if not playerChangeLock then
		local isCameraLocked = LuaCameraGetLock() -- проверяем на текущий лок камеры
	
		if isCameraLocked ~= firstCameraLocked then
			firstCameraLocked = isCameraLocked
			playerChangeLock = true
		end
	end
end

function ArrowsControl ()
	if IsHeroLeaveArea( "local", MY_BASE_COORDINATE.x, MY_BASE_COORDINATE.y, 175 ) then

		if not HintDirectionOn then
			HintDirectionOn = true
			LuaRemoveSimpleObject(selectByFaction("ArrowsA", "ArrowsB" )) --удаляем стрелки
		end
			
		local topTowerDist = DistanceSquared( x, y, firstTopTower.x, firstTopTower.y ) 
		local midTowerDist = DistanceSquared( x, y, firstMidTower.x, firstMidTower.y ) 
		local botTowerDist = DistanceSquared( x, y, firstBotTower.x, firstBotTower.y )
	
		if HintDirectionOn then
			local minDistance = math.min(topTowerDist, midTowerDist, botTowerDist)
			
			if minDistance == topTowerDist then
				
				LuaDirectionHintShow( firstTopTower.x, firstTopTower.y )
				
			elseif minDistance == midTowerDist then
				 
				LuaDirectionHintShow( firstMidTower.x, firstMidTower.y )
				
			elseif minDistance == botTowerDist then

				LuaDirectionHintShow( firstBotTower.x, firstBotTower.y )
			end
		end
	else
		if HintDirectionOn then
 
			HintDirectionOn = false

			CreateArrows()
			LuaDirectionHintHide()
		end
	end
end

function EnemyBuildingController(linePercent)
	if not DestroedEnemyBarrack then
		table.foreach(ENEMY_TOP_LINE,
		function(k,v) local dead = LuaUnitIsDead( v )

			if dead == false then

				if k < currentIndex then --если наш порядковый номер меньше текущего этапа
					firstTopTower.x = 10000
					firstTopTower.y = 10000
					if TopTowerDefence then -- будем удалять аппликатор, если он у нас есть\
						LuaUnitRemoveApplicator (v, "DamageOnlyFromSenderAppl")
						TopTowerDefence = false
					end
					return true

				elseif currentIndex == k then -- если наш порядковый номер актуален, участвуем в определении дистанции
					firstTopTower.x, firstTopTower.y = LuaUnitGetPosition ( v )

					if not TopTowerDefence then
						local health, maxHealth = LuaUnitGetHealth( v )

						if ( health / maxHealth <=  linePercent / 100 ) then
							LuaUnitApplyApplicatorFromUnit( v, "local", "DamageOnlyFromSenderAppl" )
							LuaDebugTrace( "Debug: ".. v ..  " объект может быть убит только игроком" )
							TopTowerDefence = true
						end
					end
					return true

				elseif currentIndex < k then -- если мы оказались выше, чем текущий этап, поднимаем этап на наш
					currentIndex = k 
					if TopTowerDefence then
						LuaDebugTrace( "DebugTopTowerDefence: убираем этот объект из списка" )
						TopTowerDefence = false
					end
					return true
				end
			else
				ENEMY_TOP_LINE[v] = nil				
			end
		end)
		
		table.foreach(ENEMY_MID_LINE, 
		function(k,v) local dead = LuaUnitIsDead( v )
			
			if dead == false then
				
				if k < currentIndex then
					firstMidTower.x = 10000
					firstMidTower.y = 10000
					if MidTowerDefence then -- будем удалять аппликатор, если он у нас есть\
						LuaUnitRemoveApplicator (v, "DamageOnlyFromSenderAppl")
						MidTowerDefence = false
					end
					return true
				
				elseif currentIndex == k then
					firstMidTower.x, firstMidTower.y = LuaUnitGetPosition ( v )
					if not MidTowerDefence then
						local health, maxHealth = LuaUnitGetHealth( v )

						if ( health / maxHealth <=  linePercent / 100 ) then
							LuaUnitApplyApplicatorFromUnit( v, "local", "DamageOnlyFromSenderAppl" )
							LuaDebugTrace( "Debug: ".. v ..  " объект может быть убит только игроком" )
							MidTowerDefence = true
						end
					end
					return true
				
				elseif currentIndex < k then
					currentIndex = k
					if MidTowerDefence then
						LuaDebugTrace( "DebugMidTowerDefence: убираем этот объект из списка" )
						MidTowerDefence = false
					end
					return true
				end
			else
				ENEMY_MID_LINE[v] = nil
			end
		end)
		
		table.foreach(ENEMY_BOT_LINE,
		function(k,v) local dead = LuaUnitIsDead( v )
				
			if dead == false then
			
				if k < currentIndex then
					firstBotTower.x = 10000
					firstBotTower.y = 10000
					if BotTowerDefence then -- будем удалять аппликатор, если он у нас есть\
						LuaUnitRemoveApplicator (v, "DamageOnlyFromSenderAppl")
						BotTowerDefence = false
					end
					
					return true
				
				elseif currentIndex == k then
					firstBotTower.x, firstBotTower.y = LuaUnitGetPosition ( v )
					if not BotTowerDefence then
						local health, maxHealth = LuaUnitGetHealth( v )

						if ( health / maxHealth <=  linePercent / 100 ) then
							LuaUnitApplyApplicatorFromUnit( v, "local", "DamageOnlyFromSenderAppl" )
							LuaDebugTrace( "Debug: ".. v ..  " объект может быть убит только игроком" )
							BotTowerDefence = true
						end
					end
					
					return true
				
				elseif currentIndex < k then
					currentIndex = k
					if BotTowerDefence then
						LuaDebugTrace( "DebugBotTowerDefence: убираем этот объект из списка" )
						BotTowerDefence = false
					end
					return true
				end
			else
				ENEMY_BOT_LINE[k] = nil
			end
		end)
	else
		local dead = LuaUnitIsDead( ENEMY_MAINBUILDING )
		
		if TopTowerDefence then -- будем удалять аппликатор, если он у нас есть\
			RemoveImmuneApplicator (ENEMY_TOP_LINE)
			TopTowerDefence = false
		end
		
		if MidTowerDefence then -- будем удалять аппликатор, если он у нас есть\
			RemoveImmuneApplicator (ENEMY_MID_LINE)
			MidTowerDefence = false
		end
		
		if BotTowerDefence then -- будем удалять аппликатор, если он у нас есть\
			RemoveImmuneApplicator (ENEMY_BOT_LINE)
			BotTowerDefence = false
		end
		
		if dead == false then
			firstTopTower.x = 10000
			firstTopTower.y = 10000
			
			firstMidTower.x, firstMidTower.y = LuaUnitGetPosition ( ENEMY_MAINBUILDING )
			
			firstBotTower.x = 10000
			firstBotTower.y = 10000
			if not MB_TowerDefence then
				local health, maxHealth = LuaUnitGetHealth( ENEMY_MAINBUILDING )

				if ( health / maxHealth <=  linePercent / 100 ) then
					LuaUnitApplyApplicatorFromUnit( ENEMY_MAINBUILDING, "local", "DamageOnlyFromSenderAppl" )
					LuaDebugTrace( "Debug: ".. ENEMY_MAINBUILDING ..  " объект может быть убит только игроком" )
					MB_TowerDefence = true
				end
			end
		end
	end
end

function RemoveImmuneApplicator (table1)
	table.foreach(table1, function(k,v) local dead = LuaUnitIsDead( v )
		if dead == false then 
			LuaUnitRemoveApplicator (v, "DamageOnlyFromSenderAppl") 
		end 
	end)
end