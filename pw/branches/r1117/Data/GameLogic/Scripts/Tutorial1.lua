-- Tutorial Mission 1 script v.1.8 (by Grey)

include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

M_PI2 = 1.57

function Init()
	LuaGroupHide( "Mission2", true )
	LuaSetSpawnCreeps( false )
	AddStateEnd( PlotObjectives )
	
    rotateTime = 0.7
	rotateTimeTunder = 0.5 -- cпециальное время разворота героя, если герой = Гром
	creepCap = 14 -- лимит на кол-во юнитов 
	
	debugModeOn = false

	debug1Intro = false
	debug2Jaba = false
	debug10FirstCreeps = false
--	debug3Prime = false
	debug4Warlord = false
	debug5Briefing = false
	debug6Enemy = false
	
	debug7TalentTutor1 = false
	debug8TalentTutor2 = true
	debugLastHits = false
	LuaEnableEventLogging (true)
	
end

function PlotObjectives()
	LuaDebugTrace ("   ------ Это СКРИПТ первой ТЕСТОВОЙ КАРТЫ  ----------------------------------------------------------------------")
	LuaSetAdventureControlsEnabled( true, true ) -- Это здесь временно, пока Илья не исправит курсор после диалогов
if true then ------БОЛЬШОЕЙ БЛОК ПОДГОТОВКИ
	LuaSetAchievmentsEnabled( false )
	
	if LuaIsHeroMale("local") then  -- загружаем специальные талант сеты для этой миссии (названия прописаны в словаре)
		LuaLoadTalantSet( "local", "TM1_Tunder_Set" )
		LuaDebugTrace( "DEBUG: игрок = муж.") 
	else
		LuaLoadTalantSet( "local", "TM1_Firefox_Set" )
		LuaDebugTrace( "DEBUG: игрок = жен.") 
	end

	FACTION_PLAYER = LuaGetLocalFaction()
	FACTION_ENEMY = 3 - FACTION_PLAYER
	function selectByFaction( a, b ) 	-- select by player faction
		if ( FACTION_PLAYER == 1 ) then
			return a
		else
			return b
		end
	end

	ALLY_HERO = selectByFaction( "01", "11" )
	ALLY_HERO_FROG = selectByFaction( "02", "12" )
	ENEMY_HERO = selectByFaction( "10", "00" )
	ENEMY_HERO_USELESS_1 = selectByFaction( "11", "01" )
	ENEMY_HERO_USELESS_2 = selectByFaction( "12", "02" )	
	ENEMY_BARRACKS = selectByFaction( "BarracksB_m1", "BarracksA_m1" )
	ENEMY_MAINBUILDING = selectByFaction( "MainB", "MainA" )
	ENEMY_TOWER = selectByFaction( "TowerB1_m1", "TowerA1_m1" )
	ALLY_MAINBUILDING = selectByFaction( "MainA" , "MainB" )
	ALLY_MAIN_SPAWNER = selectByFaction( "TM1_MainSpawner_D", "TM1_MainSpawner_A" )
	ENEMY_MAIN_SPAWNER = selectByFaction( "TM1_MainSpawner_A", "TM1_MainSpawner_D" )	
	ENEMY_CREEP_MELEE = selectByFaction( "CreepMeleeB", "CreepMeleeA" )
	ENEMY_CREEP_RANGED = selectByFaction( "CreepRangeB", "CreepRangeA" )
	ALLY_CREEP_MELEE = selectByFaction( "CreepMeleeA", "CreepMeleeB" )
	ALLY_CREEP_RANGED = selectByFaction( "CreepRangeA", "CreepRangeB" )
	
	if ( FACTION_PLAYER == 1 ) then 	-- set sight ranges
		LuaSetUnitStat( "BarracksA_m1", 14, 6 )
		LuaSetUnitStat( "TowerA1_m1",   14, 10 )
		LuaSetUnitStat( "MainA",        14, 33 )
		LuaSetUnitStat( "FountainA",    14, 20 )
		LuaSetUnitStat( "local",        14, 15 )
	else
		LuaSetUnitStat( "BarracksB_m1", 14, 6 )
		LuaSetUnitStat( "TowerB1_m1",   14, 10 )
		LuaSetUnitStat( "MainB",        14, 33 )
		LuaSetUnitStat( "FountainB",    14, 20 )
		LuaSetUnitStat( "local",        14, 15 )
	end
	
	LuaSetUnitStat( "FountainA", 2, 0 )
	LuaSetUnitStat( "FountainB", 2, 0 )
	LuaSetUnitStat( "TowerA1_m1", 0, 1200 )
	LuaSetUnitStat( "TowerB1_m1", 0, 1200 )
	LuaSetUnitStat( "BarracksB_m1", 0, 1000 )
	LuaSetUnitStat( "BarracksA_m1", 0, 1000 )
	LuaSetUnitStat( "MainA", 0, 900 )
	LuaSetUnitStat( "MainB", 0, 900 )
	LuaSetUnitStat( "MainA", 15, 110 )
	LuaSetUnitStat( "MainB", 15, 110 )
	EnemyCreep1 = selectByFaction( "M1_EnemyCreepA1", "M1_EnemyCreepB1" )
	
	LuaCameraObserveUnit( "local" )
	LuaHeroAddFlag( "local", ForbidAutoAttack )
	LuaHeroAddFlag( "local", ForbidDeath )
	StartTrigger( HeroImmortalCheat )
	endCreepControl = false
		
	cinemaPos1 = GetScriptArea( selectByFaction( "FrogCinema1_A_m1", "FrogCinema1_B_m1" ) )
	cinemaPos2 = GetScriptArea( selectByFaction( "FrogCinema2_A_m1", "FrogCinema2_B_m1" ) )
	cinemaPos3 = GetScriptArea( selectByFaction( "FrogCinema3_A_m1", "FrogCinema3_B_m1" ) )
	cinemaPos4 = GetScriptArea( selectByFaction( "FrogCinema4_A_m1", "FrogCinema4_B_m1" ) )
	cinemaPos5 = GetScriptArea( selectByFaction( "FrogCinema5_A_m1", "FrogCinema5_B_m1" ) )
	cinemaPos6 = GetScriptArea( selectByFaction( "M1_FrogCinema6_D", "M1_FrogCinema6_A" ) )
	riverTalk1Pos = GetScriptArea( selectByFaction( "M1_FrogCinema7_D", "M1_FrogCinema7_A" ) )
	riverTalk2Pos = GetScriptArea( selectByFaction( "M1_FrogCinema8_D", "M1_FrogCinema8_A" ) )
	Obj1Pos = GetScriptArea( selectByFaction( "ObjectiveA1_m1", "ObjectiveB1_m1" ) )
	Obj3Pos = GetScriptArea( selectByFaction( "ObjectiveA3_m1", "ObjectiveB3_m1" ) ) -- место рождения героя-игрока. Раньше использовался в квесте про хил, теперь только в синематике про возрождение жабы
	lastCinemaPos0 = GetScriptArea( selectByFaction( "M1_EnemyCreepB1", "M1_EnemyCreepA1" ) )	
--	lastCinemaPos1 = GetScriptArea( selectByFaction( "FrogStartPlaceB_m1", "FrogStartPlaceA_m1" ) ) -- место рождения вражеской лягушки. Используем в финале для своей лягушки. 
	lastCinemaPos1 = GetScriptArea( selectByFaction( "FrogCinema1_A_m1", "FrogCinema1_B_m1" ) )
	lastCinemaPos2 = GetScriptArea( selectByFaction( "ObjectiveB1_m1", "ObjectiveA1_m1" ) )
	
	eliteTeleportPoint = GetScriptArea( selectByFaction( "M1_ForbidZone1_A", "M1_ForbidZone1_D" ) )
	--commonTeleportPoint = GetScriptArea( selectByFaction( "M1_EnemyCreepA2", "M1_EnemyCreepB2" ) ) -- используем точки спавна вражеских крипов для первого спавна наших крипов во время ролика (чтобы его можно было бы скипть)
	commonTeleportPoint = GetScriptArea( selectByFaction( "M1_TeleportPointForCreeps_D", "M1_TeleportPointForCreeps_A" ) )
	
	blockZone1 = GetScriptArea( selectByFaction( "M1_ForbidZone1_D", "M1_ForbidZone1_A" ) )
	blockZone2 = GetScriptArea( selectByFaction( "M1_ForbidZone2_D", "M1_ForbidZone2_A" ) )	
	BLOCK_AREA_1 = selectByFaction( "TM1_BlockArea1_D", "TM1_BlockArea1_A" )
	BLOCK_AREA_2 = "TM1_BlockAreaCentral"
	BLOCK_AREA_3 = selectByFaction( "TM1_BlockArea1_A", "TM1_BlockArea1_D" )
	
-- Расставляем и прячем остальных героев
	allyHeroPos = GetScriptArea( selectByFaction( "AllyHeroA_m1", "AllyHeroB_m1" ) )
	frogStartPos = GetScriptArea( selectByFaction( "FrogStartPlaceA_m1", "FrogStartPlaceB_m1" ) )
	LuaCreatureTeleportTo( ALLY_HERO, allyHeroPos.x, allyHeroPos.y ) -- objective 3
	LuaCreatureTeleportTo( ALLY_HERO_FROG, frogStartPos.x, frogStartPos.y )
	LuaSetUnitStat( ALLY_HERO_FROG, 0, 260 )
	LuaSetUnitStat( ALLY_HERO_FROG, 3, 50 )
	LuaHeroSetForbidRespawn( ALLY_HERO_FROG, true )
	LuaUnitApplyApplicatorFromUnit( ALLY_HERO_FROG, ENEMY_TOWER, "DamageOnlyFromSenderAppl" )	
	LuaSetUnitStat( "local", 15, 80 )
	LuaSetUnitStat( "local", 16, 70 )
	LuaSetUnitStat( "local", 10, 0 )
	LuaSetUnitStat( ALLY_HERO, 10, 0 )
	LuaSetUnitStat( ALLY_HERO, 12, 0 )
	LuaCreatureHide( ALLY_HERO, true ) -- прячем Воеводу до поры до времени
	LuaCreatureHide( ENEMY_HERO_USELESS_1, true )
	LuaCreatureHide( ENEMY_HERO_USELESS_2, true )
	LuaSetUnitStat( ENEMY_MAINBUILDING, 2, 12 ) -- уменьшаем ГЗ дальность стрельбы пока жив баррак
	
-- прячем весь УИ кроме акшнбара
	LuaShowAllUIBlocks( false )
	LuaShowUIBlock( "TalentsSetBlock", false )
	LuaShowUIBlock( "ActionBarEscBtn", true )
	LuaShowUIBlock( "PlayerHeroBlock", true )
	LuaShowUIBlock( "ActionBarTalentBtn", false ) -- возможно когда починят ассерт можно будет убрать
	LuaShowUIBlock( "SelectionBlock", false )
  LuaShowUIBlock( "ChatBlock", false )
  LuaShowUIBlock( "LockActionBar", false )
	
	LuaBlockActionBarChange(true) -- и блокируем возможно переставлять таланты по акшн-бару (или убирать их)
end -- конец ПОДГОТОВКИ

 --------------------------------------------------------------------------------------------------------------------------------------------------
 -- ОСНОВНОЙ БЛОК ---------------------------------------------------------------------------------------------------------------------------------

	LuaCameraObserveUnit( "local" )

	if not debugModeOn or debug1Intro then    -- ПЕРВЫЙ СИНЕМАТИК. С КАСТОМНОЙ КАМЕРОЙ
		RemoveWarfogAll( true ) 
		cameraName = selectByFaction( "/Maps/Tutorial/cameraA1.CSPL", "/Maps/Tutorial/cameraB1.CSPL" )
		cameraTime = selectByFaction( 44, 41 )
		StartCinematic ("TM1_D01")   -- отслеживаем в логах
			LuaSplineCameraTimed( cameraName, cameraTime)
		EndCinematic()
		RemoveWarfogAll( false )	
	end
	
	LuaAddSessionQuest( selectByFaction("TM1_Q01p_D", "TM1_Q01p_A" ) )
	LuaAddSessionQuest( "TM1_Q03s" )
 	HintArrow( Obj1Pos, selectByFaction(3.5 , 2) )
	PlaceObjectiveMarker( "obj1", Obj1Pos.x, Obj1Pos.y )
	GreyWait( 2, HintAboutMove )-- ЛКМ/ПКМ хинтлайн про движение  
	
 ----objective: Move and reveal warfog ---------------------------------------	
	WaitForUnitInArea( "local", Obj1Pos )  -- Ждем прихода героя в точку возле Жабы
	GreyWaitEnd()
	LuaUnitClearStates( "local" )
	RemoveObjectiveMarker( "obj1" )
	HintArrow("")
	ShowHintline("")
	LuaRemoveSessionQuest( "TM1_Q03s" )
	LuaAddSessionQuest( "TM1_Q04s" ) -- отслеживаем в логах
	
	Obj2Pos = GetScriptArea( selectByFaction( "ObjectiveA2_m1", "ObjectiveB2_m1" ) )
	
  
	if not debugModeOn or debug10FirstCreeps then   --------------- Создаем вражеских разведчиков	 --------------
		x, y = LuaGetScriptArea( EnemyCreep1 )
		LuaCreateCreep( "Creep1_1", ENEMY_CREEP_MELEE, x, y, FACTION_ENEMY, selectByFaction( -M_PI2, M_PI2 ) )
		LuaCreateCreep( "Creep1_2", ENEMY_CREEP_RANGED, x, y - 3, FACTION_ENEMY, selectByFaction( -M_PI2, M_PI2 ) )
		DecreaseUnitSight( "Creep1_1", true )
		DecreaseUnitSight( "Creep1_2", true )
		LuaUnitApplyApplicatorFromUnit( "Creep1_1", "local", "DamageOnlyFromSenderAppl" )
		LuaUnitApplyApplicatorFromUnit( "Creep1_2", "local", "DamageOnlyFromSenderAppl" )
	end
  
------- Беседа с жабой	 -----------
	if not debugModeOn or debug2Jaba then
		NeedToPauseAfterPhrases( "D03_EndConversation", "D03_HalfNarrator" )
		StartCinematic ("TM1_D03") 
			HeroTalking( "local", ALLY_HERO_FROG )
			
			WaitForPhraseEnd( "D03_EndConversation" )
			--LuaPauseDialog( true )
			RotateHeroTo( "local", Obj2Pos )
			RotateHeroTo( ALLY_HERO_FROG, Obj2Pos )
			Wait(rotateTime) --ждем окончания поворота
			WaitForMoveTo( ALLY_HERO_FROG, Obj2Pos, 11 )
			Wait(2)
			CameraMove( Obj2Pos.x, Obj2Pos.y, 2.5 )
			LuaPauseDialog( false )
			
			WaitForPhraseEnd( "D03_HalfNarrator" )
			--LuaPauseDialog( true )
			Wait(3.5)
			PlaceObjectiveMarker( "obj2", Obj2Pos.x, Obj2Pos.y )
			LuaPauseDialog( false )
	    EndCinematic()
		CameraReturn( 1 )
	else
		PlaceObjectiveMarker( "obj2", Obj2Pos.x, Obj2Pos.y )
	end
	HintArrow( Obj2Pos, 0 )
	
	LogSessionEvent ("Wait hero in the second point") -- отслеживаем в логах
	
	WaitForUnitInArea( "local", Obj2Pos ) -- ЖДЕМ ПОКА ИГРОК ПОЯВИТСЯ У ВТОРОГО МАРКЕРА
	LuaUnitClearStates( "local" )
	RemoveObjectiveMarker( "obj2" )
	HintArrow("")
	LuaRemoveSessionQuest( "TM1_Q04s" )
	--LuaStartDialog( "TM1_D04" )
	
		

    if not debugModeOn or debug10FirstCreeps then -- ВРАЖЕСКИЕ РАЗВЕДЧИКИ. ОБУЧЕНИЕ АТАКИ. ---------------------------------------
		LuaAddSessionQuest( "TM1_Q05s" ) -- отслеживаем в логах
		MarkEnemy( "Creep1_1", true )
		MarkEnemy( "Creep1_2", true )
		StartTrigger( Kill2CreepsObjective )	
		HintAboutAttack()

		WaitForHeroDealedDamage( "local", 5 )
		--GreyWaitEnd()	 -- он похоже здесь не нужен
		DecreaseUnitSight( "Creep1_1", false )
		DecreaseUnitSight( "Creep1_2", false )	
	--MarkEnemy( "Creep1_1", false )
	--MarkEnemy( "Creep1_2", false )
	--Wait ( 2 )
	--LuaStartDialog( "TM1_D04_3" )

-- Хинтлайн про смену клавиш мыши		
		ShowHintline( "TM1_D04_4", false)
		LuaDebugTrace( "DEBUG: вызываем хинтлайн про смену КМ") 
		GreyWait( 6, ShowHintline, "")

		WaitForUnitsDead( { "Creep1_1", "Creep1_2" } )
--		ShowHintline( "" )
		LuaRemoveSessionQuest( "TM1_Q05s" )
	end
	Wait(0.3) 
	LuaGroupHide( BLOCK_AREA_1 , true ) -- открываем проход дальше

-- ОБУЧЕНИЕ ПОКУПКЕ ТАЛАНТА ---------------------------------------
if not debugModeOn or debug7TalentTutor1 then -- ОБУЧЕНИЕ ПОКУПКЕ ТАЛАНТА -------		
	LuaSetPause( true ) 
	LuaSetAdventureControlsEnabled( false, true )
	LuaUnitClearStates( "local" )
 ----включаем отключенный интерфейс
	LuaShowUIBlock( "ActionBarBlock", true )
	LuaShowUIBlock( "MoneyBlock", true )
	--	LuaShowUIBlock( "ImpulseTalent", true )
	LuaAddSessionQuest( "TM1_Q11s" )  -- отслеживаем в логах
 ----первая часть, бабл рассказывающий про индикатор прайма
	SetPrime( 315 )
	LuaBeginBlockSection()
		LuaAddNonBlockedElement( "NaftaBottle", true )
		LuaAddNonBlockedElement( "Hintline", true )
	LuaEndBlockSection( 0.5 )
	LuaDebugTrace( "DEBUG: 1" )
	ShowBubbleButton("TM1_D05_1", "PrimeBottle" )
	
 ----вторая часть, "купи импульсный талант"
	WaitForBubbleClick()
	LuaDebugTrace( "DEBUG: 22" )
	LuaShowUIBlock( "ImpulseTalent", true )
	LuaClearBlocking( 0 )
	LuaBeginBlockSection()
		LuaAddNonBlockedElement( "ImpulseTalent", true )
		LuaAddNonBlockedElement( "Hintline", true )
	LuaEndBlockSection( 0 )	
	LuaDebugTrace( "DEBUG: 4444" )
	ShowBubble("TM1_D05_2", "ImpulseTalent" ) -- отслеживаем в логах
	LuaDebugTrace( "DEBUG: Activate talent 0,0" )
	
 ----третья часть, клик-бабл со словами про талант в акшн баре
	ConstructWaitConditionState( LuaHeroIsTalentActivated, "local", 0 , 0)
	
 	LuaUnitApplyApplicatorFromUnit( "local", ALLY_MAINBUILDING, "LockAbility1" ) -- запрет на использование молота	
	
	LuaEndBlockSection( 0 )	
	LuaBeginBlockSection()
		LuaAddNonBlockedElement( "NaftaBottle", true )
		LuaAddNonBlockedElement( "Hintline", true )
		LuaAddNonBlockedElementActionBar( 0, true )
	LuaEndBlockSection( 0 )
	--ShowHintline( "TM1_D05" )
	--GreyWait( 4, ShowHintline, "" )
	LuaRemoveSessionQuest( "TM1_Q11s" )
	LuaAddSessionQuest( "TM1_Q06s" ) -- отслеживаем в логах
	HideLastBubble()
	ShowBubbleButton("TM1_D06", "ActionBar", 0 )
	
 ----четвертая часть, снимаем паузу когда закрыли 3ий и последний бабл
	WaitForBubbleClick()
	LuaSetAdventureControlsEnabled( true, true )
	LuaSetPause( false )
	LuaClearBlocking( 0.5 ) --highlight
else
	SetPrime( 15 )
	LuaHeroActivateTalent( "local", 0, 0, false )
	LuaShowUIBlock( "ActionBarBlock", true )
	LuaShowUIBlock( "MoneyBlock", true )
	LuaShowUIBlock( "ImpulseTalent", true )
end	
-- cinematic and objective: Minimap and Warlord ---------------------------------------
 
 if true then ---- подготовка к синематику про Воеводу в беде
	x, y = LuaGetScriptArea( selectByFaction( "M1_EnemyCreepA2", "M1_EnemyCreepB2" ) )
	xRanged, yRanged = LuaGetScriptArea( selectByFaction( "M1_EnemyCreepA2ranged", "M1_EnemyCreepB2ranged" ) )
	Soldiers2Names = { "Creep2_1", "Creep2_2", "Creep2_3", "Creep2_4" }
	LuaCreateCreep( Soldiers2Names[1], ENEMY_CREEP_MELEE, x, y, FACTION_ENEMY, 0 )
	LuaCreateCreep( Soldiers2Names[2], ENEMY_CREEP_MELEE, x, y - 4, FACTION_ENEMY, 0 )
	LuaCreateCreep( Soldiers2Names[3], ENEMY_CREEP_MELEE, x, y - 6, FACTION_ENEMY, 0 )
	if LuaIsHeroMale("local") then 
		LuaCreateCreep( Soldiers2Names[4], ENEMY_CREEP_RANGED, xRanged, yRanged, FACTION_ENEMY, 0 ) --ренжед крип только для мальчиков
	else
		LuaCreateCreep( Soldiers2Names[4], ENEMY_CREEP_MELEE, x, y - 8, FACTION_ENEMY, 0 ) --а этот милишник только для девочек
	end 

	LuaCreatureHide( ALLY_HERO, false )
	LuaSetUnitHealth( ALLY_HERO, 505 )
	
	ForAll( Soldiers2Names, ReduceDmgAndOnlyPlayerCanKill  )
	ReduceDmgAndOnlyPlayerCanKill( ALLY_HERO )

	LuaSetUnitHealth( Soldiers2Names[1], 241 )
	LuaSetUnitHealth( Soldiers2Names[2], 203 )
	LuaSetUnitHealth( Soldiers2Names[3], 258 )
end  ---- конец подготовки

	if not debugModeOn or debug4Warlord then  -- Синематик про Воеводу в беде
		NeedToPauseAfterPhrases( "D07p_BeforeShowWarlord", "D07p_Warlord" )
		StartCinematic( "TM1_D07" ) -- отслеживаем в логах
			LuaPauseDialog( true )
			WaitForMoveTo( ALLY_HERO_FROG, "local" , 5 )
			RotateHeroTo( "local", ALLY_HERO_FROG )	
			Wait(rotateTime) --ждем окончания поворота
			LuaPauseDialog( false )
			
			WaitForPhraseEnd( "D07p_JabaTalk" )
			RotateHeroTo( "local", ALLY_HERO )
			Wait(rotateTime) --ждем окончания поворота
			
			WaitForPhraseEnd( "D07p_BeforeShowWarlord" )
			--LuaPauseDialog( true )
			--RotateHeroTo( "local", ALLY_HERO )
			--Wait(rotateTime) --ждем окончания поворота
			CameraMove( allyHeroPos.x, allyHeroPos.y , 3)
			LuaPauseDialog( false )
			
			WaitForPhraseEnd( "D07p_Warlord" )
			--LuaPauseDialog( true )
			CameraReturn( 3 )
			LuaPauseDialog( false )
		EndCinematic()
	end
	LuaAddSessionQuest( "TM1_Q07s" ) -- отслеживаем в логах
	HintArrow( allyHeroPos )
	LuaShowUIBlock( "MiniMapBlock", true )

--говорим про отвязку камеры и мигаем кнопкой
	LuaSetUnitStat( "local", 2, 1 ) -- уменьшаем радиус атаки герою, чтобы он не мог убить крипа не зайдя в зону обучения
	CameraBtnHint( )

	StartTrigger( CameraAwayWarning ) -- функция, которая выводит хинтлайн, как вернуть камеру к герою

--триггер чтобы начать обучение использованию талантов	
	talentWasNotUsed = true  --специальная переменная, если игрок поюзал талант до туториала, туториал по использованию талантов не запускаем
	StartTrigger( CheckTalentUse ) --проверка, использовал ли игрок талант
	if LuaIsHeroMale("local") then 
		practiceTarget = GetScriptArea( selectByFaction( "M1_EnemyCreepA2ranged", "M1_EnemyCreepB2ranged" ) )
	else
		practiceTarget = GetScriptArea( selectByFaction( "M1_EnemyCreepA2", "M1_EnemyCreepB2" ) )
	end
	WaitForUnitInArea( "local", practiceTarget ) -- ждем пока игрок не окажется в предлах досягаемости крипа на котором будем тренировать таргетинг
	HintArrow("")
	
if talentWasNotUsed then-- ОБУЧЕНИЕ ИСПОЛЬЗОВАНИЮ ТАЛАНТОВ ---------------------------------------
	LuaUnitRemoveApplicator ("local", "LockAbility1") -- убираем запрет на использование молота
	isHintLineShow = true -- чтобы не показывать предупреждение об удаленной камере
	LuaSetPause( true ) 
	--LuaSetAdventureControlsEnabled( false, true ) -- нельзя здесь ставить, т.к. иначе игроки не смогут воспользоваться горячей клавишей
	LuaUnitClearStates( "local" )
	LuaSetUnitStat( "local", 3, 0 ) -- делаем герою скорость = 0, чтобы он не мог уйти с места
	LuaBeginBlockSection()
		LuaAddNonBlockedElement( "Hintline", true )
		LuaAddNonBlockedElementActionBar( 0, true )
	LuaEndBlockSection( 0.5 )
	HideLastBubble()
	Wait(0.3)
	ShowBubble("TM1_D08_1", "ActionBar", 0 ) -- отслеживаем в логах
	LuaShowTutorialActionBarItemHighlight( 0, true )
	LuaDebugTrace( "DEBUG: Use any talent" )
	LuaGetLastTalentClicked() -- нужно здесь, чтобы сбросить предыдущий клик для покупки 1го таланта
	ConstructWaitConditionState( Check1stTalentClick )
	--LuaSetAdventureControlsEnabled( true, true ) -- нельзя здесь ставить, т.к. иначе игроки не смогут воспользоваться горячей клавишей
	LuaSetPause( false ) 
	HideLastBubble()	
	ConstructWaitConditionState( CheckTalentUse ) -- ждем пока игрок поюзает талант
	LuaSetUnitStat( "local", 3, 50 ) -- возвращаем герою скорость
	LuaSetUnitStat( "local", 2, 14 ) --возвращаем радиус атаки, как был
	ShowBubble( "TM1_D08_3" , "ActionBar", 0 )
	Wait(6) -- было 12 сек, делаем в два раза меньше для хинта
	HideLastBubble() 
	ShowHintline( "TM1_D08_4", false)
else
	LuaSetUnitStat( "local", 2, 14 ) --возвращаем радиус атаки, как был
end 	
  
-- objective: Save Warlord ---------------------------------------
	WaitForUnitsDead( Soldiers2Names )
	ShowHintline( "" )
	isHintLineShow = false -- чтобы показывать предупреждение об удаленной камере
	LuaHeroRemoveFlag( "local", ForbidAutoAttack )	
	LuaRemoveSessionQuest( "TM1_Q07s" )
	LuaRemoveSessionQuest( selectByFaction("TM1_Q01p_D", "TM1_Q01p_A" ) )

  
--РОЛИК ПРО ЖАБУ И БАШНЮ (BRIFING) ---------	
	LuaGroupHide( BLOCK_AREA_2 , true )
	if not debugModeOn or debug5Briefing then 
		NeedToPauseAfterPhrases( "D09_BeforeBriefing", "D9p_StartBriefing", "D9p_EnemyMB", "D9p_Arsenal", "D9p_Tower", "D9p_Death", "D9p_Potions" )
		StartCinematic ( "TM1_D09" ) -- отслеживаем в логах
			LuaPauseDialog( true )
				LuaCreatureHide( ENEMY_HERO, true )  -- прячем ЧГ, чтобы не светился в ролике
				WaitForMoveTo("local", ALLY_HERO, 6 )
				RotateHeroTo( ALLY_HERO, "local" )
			LuaPauseDialog( false )
			
			WaitForPhraseEnd("D09_BeforeBriefing")	
			--LuaPauseDialog( true )
				RotateHeroTo( ALLY_HERO, riverTalk1Pos )
				Wait(rotateTime) --ждем окончания поворота
				LuaCameraObserveUnit( ALLY_HERO )
				MoveTo( ALLY_HERO, riverTalk1Pos, 0)
				Wait(1)
				WaitForMoveTo( "local", riverTalk2Pos, 0)
			LuaPauseDialog( false )
			
			WaitForPhraseEnd("D9p_StartBriefing")
			--LuaPauseDialog( true )
        LuaDebugTrace( "Debug: начинаем брифинг" )
				LuaCameraObserveUnit( "" )
				RemoveWarfogAll( true ) 
        LuaDebugTrace( "Debug: камера поехала" )
				CameraMove( cinemaPos6.x , cinemaPos6.y , 3)
			LuaPauseDialog( false )
			
			WaitForPhraseEnd("D9p_EnemyMB")
			--LuaPauseDialog( true )
				LuaCreatureTeleportTo( ALLY_HERO_FROG, cinemaPos4.x, cinemaPos4.y )
				CameraMove(cinemaPos2.x , cinemaPos2.y , 3)
			LuaPauseDialog( false )
			
			WaitForPhraseEnd("D9p_Arsenal")
			--LuaPauseDialog( true )
				CameraMove(cinemaPos3.x , cinemaPos3.y , 4)
				LuaDebugTrace( "Debug: камера на Башне" )
			LuaPauseDialog( false )
			
			WaitForPhraseEnd( "D9p_Tower" )
			--LuaPauseDialog( true )
				Wait( 3 )
				LuaCreatureMoveTo( ALLY_HERO_FROG, cinemaPos5.x, cinemaPos5.y, 15)
				WaitForUnitInArea( ALLY_HERO_FROG, cinemaPos5.x, cinemaPos5.y, 3) 
			LuaPauseDialog( false )
			WaitForPhraseEnd( "D9p_Death" )
			
			WaitForUnitsDead( ALLY_HERO_FROG )
			Wait(0.5)
			LuaPauseDialog( false )
					LuaSpawnerSpawnWave( ALLY_MAIN_SPAWNER )
					Wait(0.2)
					ForAll( NameAllLivingCreepsFromSpawner( ALLY_MAIN_SPAWNER ), CommonTeleport )
					PeriodicalSpawn( ALLY_MAIN_SPAWNER , 12.5, creepCap)
				RemoveWarfogAll( false )
				CameraReturn( 3 )
				HeroTalking( "local" , ALLY_HERO)
				LuaCreatureHide( ENEMY_HERO, false ) 
			
		EndCinematic()
	else
		PeriodicalSpawn( ALLY_MAIN_SPAWNER , 12.5, creepCap)
		LuaCreatureTeleportTo( ALLY_HERO_FROG, cinemaPos5.x, cinemaPos5.y )
	end -- конец ролика ---
	
	--StartTrigger( CreepControl2, ALLY_MAIN_SPAWNER, 15 ) -- функция, которая будет убивать союзных крипов, если их наспавниться больше этого числа
  ----Выдаем потионы лечения
	isHintLineShow = true -- чтобы бабл не перебивала сообщение об отвязанной камере
	LuaHeroTakeConsumable( "local", "HealingPotion" ) -- прописан в dictionary 
	LuaHeroTakeConsumable( "local", "HealingPotion" )
	LuaHeroTakeConsumable( "local", "HealingPotion" )
	Wait( 1 ) -- необходимая задержка иначе бабл не успеет появится
	ShowBubbleButton("TM1_D10_2", "ActionBar", 1 ) -- отслеживаем в логах
	StartTrigger( DrinkPotion, 50 )

	LuaAddSessionQuest( selectByFaction("TM1_Q02p_D", "TM1_Q02p_A" ) )
	LuaSessionQuestUpdateSignal( "TM1_Q02p", "Q02_s1", cinemaPos6.x, cinemaPos6.y)
	LuaAddSessionQuest( "TM1_Q08s" )	
	LuaSessionQuestUpdateSignal( "TM1_Q08s", "Q08_s1", cinemaPos5.x, cinemaPos5.y)
	HintArrow( ENEMY_TOWER )
	
	Wait( 1 ) 
	LuaCreatureMoveTo( ALLY_HERO, Obj1Pos.x, Obj1Pos.y , 100 ) -- Воевода идет на базу	

-- Блок подготовки вражеской башни
	LuaUnitAddFlag( "local", ForbidTakeDamage) --вешаем этот флаг на героя, чтобы башня на него случайно не переагрилась
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_TOWER, 25 )
	x, y = LuaUnitGetPosition( ENEMY_TOWER )
	LuaDebugTrace( "Attack tower" )
	MarkEnemy( ENEMY_TOWER, true )
	LuaSpawnerSpawnWave( ENEMY_MAIN_SPAWNER ) --спавним 1ую волну врагов, чтобы они уперлись в непроходимую стенку
	
--УНИЧТОЖЕНИЕ БАШНИ
	LuaShowUIBlock( "ImpulseTalent", false ) -- блокируем УИ быстрой покупки таланта, чтобы она не мигала после смерти башни
	WaitForUnitsDead( ENEMY_TOWER ) 
	isHintLineShow = false
	SetPrime( 200 )
	HintArrow( "" )
	LuaUnitRemoveFlag( "local", ForbidTakeDamage) --башня мертва и теперь герой опять уязвим
	LuaShowUIBlock( "ImpulseTalent", true ) -- позволяем игроку снова видеть блок "быстрой покупки таланта"
	PeriodicalSpawn( ENEMY_MAIN_SPAWNER , 20, creepCap )
	EnemyHeroMovePos = GetScriptArea( selectByFaction( "EnemyHeroMoveB_m1", "EnemyHeroMoveA_m1" ) ) 
	MoveTo( ENEMY_HERO, EnemyHeroMovePos , 1) --выдвигаем вражеского героя на начальную позицию
	HintArrow( ENEMY_BARRACKS, selectByFaction(1.5,0) )
	LuaUnitAddFlag( ENEMY_BARRACKS, ForbidTakeDamage) -- пока жив герой, барак нельзя атаковать
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_BARRACKS, 25 )
	LuaGroupHide( BLOCK_AREA_3 , true ) -- убираем 3ую непроходимую зону
	CreateAllyCreepsForEnemyMB() -- создаем крипов возле вражеского ГЗ, чтобы их потом убить в ролике
	LuaRemoveSessionQuest( "TM1_Q08s" )
	LuaAddSessionQuest( "TM1_Q09s" )
	LuaSessionQuestUpdateSignal( "TM1_Q09s", "Q09_s1", cinemaPos2.x, cinemaPos2.y)

-- objective: TALENT SET BUY ----------------------------------------------------------------------------------------------------------
	Wait( selectByFaction( 1.8, 2.4 ) ) -- пауза, чтобы дать проиграться анимации разрушения башни
	if not debugModeOn or debug8TalentTutor2 then 
		isHintLineShow = true
		AdvancedTalentBuyTutorial() -- вызов функции с туториалом про покупки из талант сета
		isHintLineShow = false
	else
		LuaShowUIBlock( "TalentsSetBlock", true )
		LuaShowUIBlock( "ActionBarTalentBtn", true )
		LuaShowUIBlock( "ImpulseTalent", false )
		SetPrime( 1150 )
	end
	LuaRemoveSessionQuest( "TM1_Q12s" )

	CreepControl3() -- функция следит за тем, чтобы один крипы не победили других слишком быстро
	creepControl5Stop = false -- переменная, чтобы потом отключить умирание крипов возле ГЗ (см. след. строку)
	StartTrigger( CreepControl5 ) -- а эта функция затем, чтобы союзные крипы не смели раньше времени приближаться к вражескому ГЗ

-- ОБУЧЕНИЕ ЛАСТ ХИТУ -------------------------------------------------------------------------------------------------------------------	
	Wait(2)
	if not debugModeOn or debugLastHits then LastHitTutorial() end  
		
--ВРАЖЕСКИЙ ГЕРОЙ  ----------------------------------------------------------------------------------------------------------------------
	LuaDebugTrace( "Debug: Enemy hero block" )
	NearArsenalPos = GetScriptArea( selectByFaction( "NearArsenalB_m1", "NearArsenalA_m1" ) ) -- enemy arsenal
	LuaSetUnitStat( ENEMY_HERO, 3, 0 )
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_HERO, 90 )	
	LuaHeroActivateTalent( ENEMY_HERO, 0, 0, false )
	
	WaitForUnitInArea( "local", NearArsenalPos )
	if not debugModeOn or debug6Enemy then 
		LuaHeroAddFlag( "local", ForbidAutoAttack ) 
		StartCinematic( "TM1_D15", true ) -- отслеживаем в логах
			HintArrow("")
			LuaSetUnitStat( ENEMY_HERO, 3, 45 )
			LuaHeroAddFlag( ENEMY_HERO, ForbidAutoAttack ) 
			LuaPauseDialog( true )
			LuaHeroAddFlag( "local", ForbidTakeDamage ) 
			LuaHeroAddFlag( ENEMY_HERO, ForbidTakeDamage ) 
			MoveTo( ENEMY_HERO, "local", 7 )
			LuaPauseDialog( false )
			RotateHeroTo( "local", ENEMY_HERO )
		EndCinematic()
		isHintLineShow = true -- чтобы не показывать предупреждение об удаленной камере
		LuaHeroRemoveFlag( "local", ForbidAutoAttack )
		LuaHeroAddFlag( ENEMY_HERO, ForbidAutoAttack ) 
		LuaHeroRemoveFlag( "local", ForbidTakeDamage ) 
		LuaHeroRemoveFlag( ENEMY_HERO, ForbidTakeDamage ) 
		StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_HERO, 20 )
	else
		--LuaCreatureTeleportTo( ENEMY_HERO, EnemyHeroMovePos.x, EnemyHeroMovePos.y )
	end
	LuaHeroUseTalent( ENEMY_HERO, 0, 0 )
	StartTrigger( RepetableAttackPlayer, ENEMY_HERO )
	GreyWait ( 1.2, ShowHintline, "TM1_D15_2" )
	--ShowHintline( "TM1_D15_2" )
	LuaAddSessionQuest( "TM1_Q10s" )
	MarkEnemy( ENEMY_HERO, true )

--ЖДЕМ СМЕРТИ ВРАЖЕСКОГО ГЕРОЯ -------------------------------------------------------------------------------------------------------------
	LuaHeroSetForbidRespawn( ENEMY_HERO, true )
  WaitForUnitsDead( ENEMY_HERO )
  
	LogSessionEvent ("Enemy hero dead") -- отслеживаем в логах
  
	MarkEnemy( ENEMY_HERO, false )
	ShowHintline( "" )
	isHintLineShow = false -- чтобы опять показывать предупреждение об удаленной камере
	HintArrow(ENEMY_BARRACKS, selectByFaction(3.5,1) )
	LuaUnitRemoveFlag( ENEMY_BARRACKS, ForbidTakeDamage)
	LuaRemoveSessionQuest( "TM1_Q10s" )
	
	MarkEnemy( ENEMY_HERO, false )	
	--	LuaStartDialog( "TM1_D16" )


-- objective: Barracks  ---------------------------------------
	MarkEnemy( ENEMY_BARRACKS, true )
	LuaUnitAddFlag( ENEMY_MAINBUILDING, ForbidTakeDamage )

	WaitForUnitsDead( ENEMY_BARRACKS ) -- Ждем разрушения бараков
	LuaDebugTrace( "Debug:  барак разрушен, спавним элитников " )
	HintArrow("")
	LuaRemoveSessionQuest( "TM1_Q09s" )
	StopAllPeriodicalSpawn() -- отключаем респавн крипов. Союзных потом включим в "AfterBarrackCinema"
	LuaSetManualGameFinish (true)

	AfterBarrackCinema() 
	
	LogSessionEvent ("After barrack destroed cinema") -- отслеживаем в логах
	
	LuaUnitRemoveFlag ( ENEMY_MAINBUILDING, ForbidTakeDamage )
	LuaSetUnitStat( ENEMY_MAINBUILDING, 2, 26 )
	StartTrigger( OnlyPlayerCanKillAtThisPoint, ENEMY_MAINBUILDING, 35 ) -- только игрок может добить ГЗ
	HintArrow( ENEMY_MAINBUILDING )
	
-- objective: destroy MAIN BUILDING
	
	WaitForUnitsDead( ENEMY_MAINBUILDING )
	isHintLineShow = true -- чтобы не показывать предупреждение об удаленной камере
	if LastHitTutorial then
		LuaRemoveSessionQuest( "TM1_Q13s" )
		LuaDebugTrace( "DEBUG: обучение ластхиту закончилось" )
		LastHitTutorial = false
	end
	HintArrow("")
	RemoveWarfogAll( true ) 	
	 LuaDebugTrace( "Debug:  ГЗ разрушено, запускаем ролик " )	
	LuaRemoveSessionQuest( selectByFaction("TM1_Q02p_D", "TM1_Q02p_A" ) )
	StartCinematic ( "TM1_D21" ) -- отслеживаем в логах
		LuaCreatureTeleportTo( ALLY_HERO_FROG, lastCinemaPos0.x, lastCinemaPos0.y)		
		WaitForMoveTo( ALLY_HERO_FROG, "local", 6)
		RotateHeroTo( "local", ALLY_HERO_FROG )
	EndCinematic()
	isCinematicCurrentlyPlayed = true -- чтобы не появлялось никаких левых текстов и реплик
	ShowHintline( "" )
	Wait (1) --Задержка перед концом игры нужна, чтобы экран не затемнялся--
	LuaGameFinish( selectByFaction ( 2, 1) )	
end

------------------------------------------------------------------------------------------------------------------------------------------------
----- КОНЕЦ ОСНОВНОГО БЛОКА --------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------

function HintAboutMove()   -- ЛКМ/ПКМ хинтлайн для движения	
	if LuaGetControlStyle() then   
		LuaDebugTrace( "DEBUG: вызываем хинтлайн для ЛКМ мува") 
		ShowHintline( "TM1_D02_LMC", true, "LeftClick")
	else
		LuaDebugTrace( "DEBUG: вызываем хинтлайн для РКМ мува") 
		ShowHintline( "TM1_D02_RMC", true, "RightClick")
	end
end

function HintAboutAttack()	-- ЛКМ/ПКМ хинтлайн для атаки 
	if LuaGetControlStyle() then   
		ShowHintline( "TM1_D04_2_LMC", true, "LeftClick")
		LuaDebugTrace( "DEBUG: вызываем хинтлайн для ЛКМ атаки") 
	else
		ShowHintline( "TM1_D04_2_RMC", true, "RightClick")
		LuaDebugTrace( "DEBUG: вызываем хинтлайн для РКМ атаки") 
	end
end

function CheckTalentUse() -- используется для обучения использовнию талантов
	if ( GetGameStep() - LuaHeroGetLastTalentUseStep( "local" ) <= 1 * GetStepsCountInSecond() ) then
		LuaRemoveSessionQuest( "TM1_Q06s" )
		ShowHintline( "" )
		LuaShowTutorialActionBarItemHighlight( 0, false )
		talentWasNotUsed = false
		return true
	end
	return false
end

function Check1stTalentClick() -- проверяем что кликнули талант 0 0, используется для обучения использовнию талантов
	local levelClick, columnClick = LuaGetLastTalentClicked()
--	LuaDebugTrace( "DEBUG: Перед проверкой" ..tostring(levelClick).." "..tostring(columnClick))
	local function MarkCreepForHint( creepName )
		if not LuaUnitIsDead( creepName ) then
			MarkEnemy( creepName , true)
		end		
	end
	if levelClick==0 and columnClick==0 then
		LuaDebugTrace( "DEBUG: Мы кликнули по таланту" ..tostring(levelClick).." "..tostring(columnClick))
		if LuaIsHeroMale("local") then MarkCreepForHint( "Creep2_4" ) 
		else ForAll( Soldiers2Names, MarkCreepForHint )	end
		ShowHintline( "TM1_D08_2", false) -- здесь никакого hint_beep, иначе скрипт будет падать.
		LuaClearBlocking( 0.5 ) --снимает затемнение
		return true
	end
	return false
end

function Kill2CreepsObjective()
	if LuaUnitIsDead( "Creep1_1" ) then 
		LuaUpdateSessionQuest( "TM1_Q05s", 1 )
	end
	if LuaUnitIsDead( "Creep1_2" ) then 
		LuaUpdateSessionQuest( "TM1_Q05s", 1 )
	end
end

function DrinkPotionTutorial()  -- СЕЙЧАС НЕ ИСПОЛЬЗУЕТСЯ, Т.К. НЕВОЗМОЖНО ПОД ПАУЗОЙ ПРОЧЕКАТЬ ВЫПИВАНИЕ ПОТИОНА
	potionSlotNumber = 1
	--LuaSetPause( true ) 
	LuaDebugTrace( "DEBUG: 55555555555" )
	LuaDebugTrace( "Debug: начало туториала про хиты" )	
	LuaShowTutorialActionBarItemHighlight( potionSlotNumber , true)	
	ShowBubble("TM1_D17_1", "ActionBar", 1)
	--ShowHintline( "TM1_D17_1" )	
		LuaDebugTrace( "DEBUG: 66666666666666666666666666666" )
--	WaitForHeroUseAnyConsumable( "local" )
			LuaDebugTrace( "DEBUG: 7777777777777777777777777777777777777" )
	--LuaSetPause( true ) 
	--ShowHintline( "" )
	--LuaShowActionBarButtonBubble( 1, false, "TM1_D14" )
	HideLastBubble()
	LuaDebugTrace( "Debug: начало туториала про хиты" )
		LuaDebugTrace( "DEBUG: 88888888888888888888888888888888888888888888888888888888" )	
	--	LuaShowTutorialElementHighlight( "HealthBar" , false ) -- если потом включу подсветку, тут надо будет ее отключить
end
 
 function CreepControl( creepTypeMaskString , factionMaskString)
	local creepTypeMask = tonumber( creepTypeMaskString )
	local factionMask = tonumber( factionMaskString )
	--local factionMask = 2 ^ FACTION_PLAYER -- маска для врагов.
	local enemyCreepsNumb = LuaGetUnitsInArea( factionMask, creepTypeMask, NearArsenalPos.x, NearArsenalPos.y, 130)
	local allyCreepsNumb = LuaGetUnitsInArea( factionMask, creepTypeMask, NearArsenalPos.x, NearArsenalPos.y, 130)
	LuaDebugTrace( "Debug: число вражьих крипов:"..tostring( enemyCreepsNumb) )
	LuaDebugTrace( "Debug: число союзных крипов:"..tostring( allyCreepsNumb ) )
	if enemyCreepsNumb > allyCreepsNumb + 2 then 
		-- как-нибудь ослабить врагов
	end
	if enemyCreepsNumb + 2 < allyCreepsNumb then 
		-- как-нибудь ослабить друзей
	end
end

--[[ function CreepControl2( spawnerName, creepsCap )
	if endCreepControl then 
		LuaDebugTrace("DEBUG: функция CreepContorl2 прекращает свою работу ")
		return true
	end
	local creepsArray = NameAllLivingCreepsFromSpawner( spawnerName )
	if # creepsАrray > creepsCap then 
		LuaDebugTrace("DEBUG: функция CreepContorl2 число существ в игре: " ..tostring(# creepsArray).." - убиваем одно" )
		LuaKillUnit( creepsArray[1] )
	end
end
]] --
function CreepControl3 ()
	-- StartTrigger( CreepControl2, ALLY_MAIN_SPAWNER, 14 )
	-- StartTrigger( CreepControl2, ENEMY_MAIN_SPAWNER, 9 )
	--creepsArray = NameAllLivingCreepsFromSpawner( ENEMY_MAIN_SPAWNER )
	--StartTrigger( function(creepsArray) if # creepsArray < 2 then LuaSpawnerSpawnWave( ENEMY_MAIN_SPAWNER ) end;  end) -- эта штука ассертит и вообще она не нужна -враги будут слишком быстро спавниться
end

function CreepControl4( unitName)
	local x, y = LuaUnitGetPosition( ENEMY_MAINBUILDING )
	if IsUnitInArea(unitName, x, y, 26 ) then 
		LuaDebugTrace("DEBUG: один крип подошел слишком близко к вражескому ГЗ! Tresspasser will be shot! " )
		LuaKillUnit( unitName ) 
	end
end

function CreepControl5()
	local creepsArray = NameAllLivingCreepsFromSpawner( ALLY_MAIN_SPAWNER )
	if creepControl5Stop then return end
	--	LuaDebugTrace("DEBUG: мы проверяем близость крипов рядом с ГЗ - 11" )
	ForAll( creepsArray, CreepControl4 )
--	LuaDebugTrace("DEBUG: мы проверяем близость крипов рядом с ГЗ - 22" )
end

function DisableMove( unitName )
	LuaSetUnitStat( unitName , 3, 0)
end 

function EliteCreepNames()
	local lastWaveNumb = LuaSpawnerGetLastWave( ALLY_MAIN_SPAWNER )
	local arr = {}
	local creepsInWave = 4
	for i = 1, creepsInWave do
		localName = ALLY_MAIN_SPAWNER .. "_w" .. tostring( lastWaveNumb ) .. "_c" .. tostring(i)
		arr[ i ] = localName
	end
	return arr	
end

function ForbidZone( zoneName )
--	LuaMessageToChat( "начало триггера, координаты "..tostring(zoneName.x).." "..tostring(zoneName.y).." "..tostring(zoneName.radius).." " )
	if IsHeroInArea( "local", zoneName.x , zoneName.y, zoneName.radius ) then 
		LuaUnitClearStates( "local" )
		LuaMessageToChat( "Вам пока рано сюда, закончите текущие задания" )
--		return true
	end
	return false
end

function HeroImmortalCheat()
	local warnPercent_2 = 30
	local health, maxHealth = LuaUnitGetHealth( "local" )
	local bonusHealthRegen = 18
	local currentPercent = health / maxHealth
	local damageDecresePercent = (1 - currentPercent) * 100
	LuaSetUnitStat( "local" , 27, damageDecresePercent)
	LuaSetUnitStat( "local" , 28, damageDecresePercent)
	if ( currentPercent <=  warnPercent_2 / 100 ) then
		LuaSetUnitStat( "local" , 11, bonusHealthRegen)
	else 
		LuaSetUnitStat( "local" , 11, 0)	
	end
end

function RepetableAttackPlayer( heroName )
	if LuaUnitIsDead( heroName) then
		return
	else
		LuaHeroAttackUnit( heroName, "local" )
	--	LuaHeroUseTalent( heroName, 0, 0 )
	end
end

function AfterBarrackCinema()
	LuaDebugTrace( "Debug: начало синематика ГЗ, элитников и возрождение жабы " )
	-- возможно остановить на месте всех союзных крипов
	NeedToPauseAfterPhrases( "D19p_EliteSpawn", "D19p_WarlordPunish")
	StartCinematic ( "TM1_D19" ) -- отслеживаем в логах
	    LuaHeroAddFlag( "local", ForbidTakeDamage ) -- на время синематика ГГ не получает вреда
		LuaHeroAddFlag( "local", ForbidAutoAttack )  -- и не атакует
	  -- WaitForPhraseEnd( "D19p_HeroComment" )
	  ---фраза нарратора про гвардию	
		--LuaPauseDialog( true )
		LuaCameraObserveUnit( "" )
		cameraMoveTime =4
		RemoveWarfogAll( true )
		LuaCameraMoveToPosTimed( Obj1Pos.x, Obj1Pos.y, cameraMoveTime)
		Wait(0.7) -- надо дать камере время удалиться от крипов
		ForAll( NameAllLivingCreepsFromSpawner( ALLY_MAIN_SPAWNER ) , function( unitName ) LuaCreatureHide( unitName, true ); end ) -- прячем союзных крипов
		ForAll( NameAllLivingCreepsFromSpawner( ENEMY_MAIN_SPAWNER ) , function( unitName ) LuaKillUnit( unitName ); end ) -- убиваем вражеских крипов
		creepControl5Stop = true
		endCreepControl = true
		Wait( cameraMoveTime - 0.5) -- надо дать камере время долететь до места
		RemoveWarfogAll( false )
		LuaSpawnerSpawnWave( ALLY_MAIN_SPAWNER )
		eliteCreepNamesArray = EliteCreepNames()
		Wait( 1 )
		--StartTrigger( CreepControl2, ALLY_MAIN_SPAWNER, 18 )
	--	LuaPauseDialog( false )
	   WaitForPhraseEnd( "D19p_EliteSpawn" )
	  ---фраза воеводы про гвардию
		--LuaPauseDialog( true )
		Wait( 2 )
		CameraMove(Obj3Pos.x, Obj3Pos.y, 1.5)
		LuaHeroRespawn( ALLY_HERO_FROG )
		Wait(1.5) --ждем, пока проиграется анимация возрождения--
		LuaPauseDialog( false )
	  ---фраза воеводы про жабу
	  
	  --- WaitForPhraseEnd( "D19p_FrogRessurect" )
	  ---фраза жабы	  
		--LuaPauseDialog( true )
		ForAll( NameAllLivingCreepsFromSpawner( ALLY_MAIN_SPAWNER ) , function( unitName ) 	LuaSetUnitStat( unitName, 3, 0 ); end )
		--HeroTalking( ALLY_HERO_FROG, ALLY_HERO )
		Wait(rotateTime) --ждем, пока доиграется анимация поворота--
		WaitForMoveTo( ALLY_HERO, ALLY_HERO_FROG, 7)
		HeroTalking( ALLY_HERO_FROG, ALLY_HERO )
 	--	LuaPauseDialog( false )
	   WaitForPhraseEnd( "D19p_Frog" )
	  ---фраза воеводы про наказание

	   WaitForPhraseEnd( "D19p_WarlordPunish" )
		--LuaPauseDialog( true )		
		RemoveWarfogAll( true ) 	
		cameraMoveTime =3
		LuaCameraMoveToPosTimed( cinemaPos1.x , cinemaPos1.y , cameraMoveTime)
		Wait( 2 ) -- Добавил сюда, чтобы ролик лучше смотрелся
		x, y = LuaUnitGetPosition( ENEMY_MAINBUILDING )
		ForAll( Soldiers3Names, function( unitName) LuaCreatureHide( unitName, false ) ; end) --- проявляем всех заранее созданных солдат и отправляем их на вражеское ГЗ
		ForAll( Soldiers3Names, function( unitName) if not LuaUnitIsDead(unitName) then LuaCreatureMoveTo( unitName, x, y , 2 ) end ; end) -- Здесь нужно использовать "LuaCreatureMoveTo", чтобы проверка дистанции встроеная в "MoveTo" не вызывала ассерт
		Wait( cameraMoveTime)
		RemoveWarfogAll( false )	
		PeriodicalSpawn( ALLY_MAIN_SPAWNER , 14, creepCap)
		WaitForUnitsDead( Soldiers3Names ) -- ждем пока крипы не сдохнут
		Wait(1) --и еще одну секунду для красоты
	   LuaPauseDialog( false )
		
	   WaitForPhraseEnd( "D19p_GZAoE" )
		--ForAll( eliteCreepNamesArray , function( unitName ) LuaCreatureTeleportTo( unitName, eliteTeleportPoint.x, eliteTeleportPoint.y ) end )
		ForAll( eliteCreepNamesArray , EliteTeleport )
		ForAll( eliteCreepNamesArray, function( unitName) if not LuaUnitIsDead(unitName) then LuaCreatureMoveTo( unitName, x, y , 2 ) end ; end)
	 	ForAll( NameAllLivingCreepsFromSpawner( ALLY_MAIN_SPAWNER ) , function( unitName ) 	LuaSetUnitStat( unitName, 3, 40 ); end )  
		CameraReturn( 2 )
		LuaHeroRemoveFlag( "local", ForbidTakeDamage ) 
		LuaHeroRemoveFlag( "local", ForbidAutoAttack ) 
		LuaDebugTrace( "Debug: конец кинематика про после барака" )	
	EndCinematic()
end 

eliteTelMod = 0
function EliteTeleport( unitName )
	LuaCreatureTeleportTo( unitName, eliteTeleportPoint.x + eliteTelMod, eliteTeleportPoint.y )
	eliteTelMod = eliteTelMod + 2
end

commonTelMod = 0
function CommonTeleport( unitName )
	LuaCreatureTeleportTo( unitName, commonTeleportPoint.x + commonTelMod, commonTeleportPoint.y )
	commonTelMod = commonTelMod + 2
end
 
function G5( t )
	RemoveWarfogAll( true )	
	cameraName = selectByFaction( "/Maps/Tutorial/cameraA1.CSPL", "/Maps/Tutorial/cameraB1.CSPL" )
--	LuaSetCameraFree( cameraName, 0)
--	Wait( 3 )
	LuaSplineCameraTimed( cameraName, tonumber(t))
	LuaStartCinematic ("TM1_D01") 
end

function G7( ID, modeIndex )
	LuaShowAllUIBlocks( true )
	if tonumber(modeIndex) > 0 then 
		modeOn = true
	else 
		modeOn = false
	end
	LuaShowTutorialHeroHighlight( ID, modeOn )
end

function ReduceDmgAndOnlyPlayerCanKill( unitName ) 
	LuaUnitApplyApplicatorFromUnit( unitName, "local", "DamageReducer" )
	StartTrigger(OnlyPlayerCanKillAtThisPoint, unitName, 25 )
end		

function CreateAllyCreepsForEnemyMB()
	--Создаем группу союзных крипов возле вражеского ГЗ, чтобы оно их потом пафосно убило в функции AfterBarrackCinema	
		x, y = LuaGetScriptArea( selectByFaction( "M1_SpawnCreepForMainBuilding_D", "M1_SpawnCreepForMainBuilding_A" ) )
		LuaDebugTrace( "DEBUG: координаты для крипов:"..tostring(x).. " & "..tostring(y) )
		Soldiers3Names = { "Creep3_1", "Creep3_2", "Creep3_3", "Creep3_4", "Creep3_5", "Creep3_6" }
		LuaCreateCreep( Soldiers3Names[1], ALLY_CREEP_MELEE, x + 3, y, FACTION_PLAYER, 0 )
		LuaCreateCreep( Soldiers3Names[2], ALLY_CREEP_RANGED, x, y, FACTION_PLAYER, 0 )
		LuaCreateCreep( Soldiers3Names[3], ALLY_CREEP_MELEE, x, y - 4, FACTION_PLAYER, 0 )
		LuaCreateCreep( Soldiers3Names[4], ALLY_CREEP_RANGED, x, y - 6, FACTION_PLAYER, 0 )
		LuaCreateCreep( Soldiers3Names[5], ALLY_CREEP_MELEE, x, y - 8, FACTION_PLAYER, 0 )
		LuaCreateCreep( Soldiers3Names[6], ALLY_CREEP_MELEE, x+4, y - 4, FACTION_PLAYER, 0 )
		LuaSetUnitStat( Soldiers3Names[2], 2, 8 )
		LuaSetUnitStat( Soldiers3Names[4], 2, 8 )
		ForAll( Soldiers3Names, function( unitName) LuaCreatureHide( unitName, true ) ; end)
	--конец создания группы союзных крипов
end

function AdvancedTalentBuyTutorial()
	LuaSetPause( true )
	LuaSetAdventureControlsEnabled( false, true )
	LuaAddSessionQuest( "TM1_Q12s" )
	HideLastBubble() -- прячем бабл про потионы, если игрок не спрятал его сам
--первый этап: покупаем А2 по кнопке квикБай	
	SetPrime( 375 )
		Wait(0.1)	
  	LuaBeginBlockSection() 
		LuaAddNonBlockedElement( "ImpulseTalent", true )
		LuaAddNonBlockedElement( "Hintline", true )
	LuaEndBlockSection( 0.5 )
	ShowBubble("TM1_D12_1", "ImpulseTalent") -- отслеживаем в логах
	
	ConstructWaitConditionState( LuaHeroIsTalentActivated, "local", 0 , 1)  ----ждем покупки таланта по квикбаю
	HideLastBubble()
	ShowBubbleButton("TM1_D12_4", "NaftaBottle") -- отслеживаем в логах
	WaitForBubbleClick() 

--третий этап: говорим открыть окно талантов, ждем пока игрок это сделает
	HideLastBubble()
	LuaClearBlocking( 0 )
	SetPrime( 375 )
	LuaShowUIBlock( "TalentsSetBlock", true )
	LuaShowUIBlock( "ActionBarTalentBtn", true )
	LuaShowUIBlock( "ImpulseTalent", false )
	LuaBeginBlockSection() 
		LuaAddNonBlockedElement( "TalentsBar", true )
		LuaAddNonBlockedElement( "NaftaBottle", true )
		LuaAddNonBlockedElement( "Hintline", true )
	LuaEndBlockSection( 0 )	
	ShowBubble( "TM1_D12_2", "PrimeBottle")
	Wait(0.1)	

	WaitForOpenUI( WINDOW_TALENTSBAR ) -- Ждем открытия УИ
	StartTrigger( DoNotCloseTalentUI ) -- спец блок, чтобы не закрыли случаайно УИ до окончания туториала. 
	talentTutorialOver = false
	HideLastBubble()
	ShowBubble( "TM1_D12_3", "Talent", 2, 0)  -- отслеживаем в логах
	 
	CheckSuccessfulBuyTalent() -- функция в коммоне
	HideLastBubble()
	LuaShowTutorialElementHighlight( "TalentSetSecondLevel" , true ) 
	ShowBubbleButton( "TM1_D12_5", "TalentSetSecondLevel")  -- отслеживаем в логах
	
	WaitForBubbleClick() 
	LuaShowTutorialElementHighlight( "TalentSetSecondLevel" , false ) 
	ShowBubbleButton( "TM1_D12_6", "Talent", 2, 1)  -- отслеживаем в логах (бабл про пассивные таланты)
	
	WaitForBubbleClick()
	ShowBubbleButton( "TM1_D12_7", "Talent", 4, 1) -- отслеживаем в логах (бабл про пассивные таланты)
	
	WaitForBubbleClick()  
	ShowBubble( "TM1_D12_8", "TalentSetSecondLevel") -- отслеживаем в логах
	SetPrime( 500 )
	--Wait(0.1)	
	CheckSuccessfulBuyTalent()
	HideLastBubble()
	--LuaShowTutorialElementHighlight( "TalentSetSecondLevel" , false ) 
	

	talentTutorialOver = true --больше мы не будем выводить бабл, который говорит, как включить окно талантов
--	if LuaIsWindowVisible ( WINDOW_TALENTSBAR ) then 
	ShowBubble( "TM1_D12_10", "PrimeBottle") -- отслеживаем в логах (бабл, чтобы игрок закрыл окно талантов)
	WaitForCloseUI ( WINDOW_TALENTSBAR ) 
	HideLastBubble()
--	end
	LuaSetAdventureControlsEnabled( true, true )
	LuaSetPause( false ) 
	LuaClearBlocking( 0 )
	LuaShowUIBlock( "ImpulseTalent", true )
	StartTrigger( HowToCloseTalentUI )
end

function HowToCloseTalentUI()
	if LuaIsWindowVisible(WINDOW_TALENTSBAR) then
		LuaShowBubble( "PrimeBottle", true, "TM1_D13_Hint", "", 2) -- Используем здесь прямую функцию, а не обертку, т.к. событие может случиться в непредсказуемый момент и сломать другие баблы
	else
		LuaShowBubble( "PrimeBottle", false, "TM1_D13_Hint", "", 2) -- Используем здесь прямую функцию, а не обертку, т.к. событие может случиться в непредсказуемый момент и сломать другие баблы
	end
end

function DoNotCloseTalentUI()
	if talentTutorialOver then return end
	if not LuaIsWindowVisible(WINDOW_TALENTSBAR) then
		LuaShowBubble( "PrimeBottle", true, "TM1_D12_9_Hint", "", 2) -- Используем здесь прямую функцию, а не обертку, т.к. событие может случиться в непредсказуемый момент и сломать другие баблы
	else
		LuaShowBubble( "PrimeBottle", false, "TM1_D12_9_Hint", "", 2) -- Используем здесь прямую функцию, а не обертку, т.к. событие может случиться в непредсказуемый момент и сломать другие баблы
	end
end

function RemoveWarfogAll( warfogState ) -- Если true - открываем варфог на всей карте
	if warfogState then
		LuaUnitApplyApplicatorFromUnit( ALLY_MAINBUILDING, "local", "RemoveWarfog")
	else
		LuaUnitRemoveApplicator( ALLY_MAINBUILDING, "RemoveWarfog")
	end
	
end

function LastHitTutorial()
	StartCinematic("TM1_D23") -- отслеживаем в логах
	EndCinematic()
	LuaAddSessionQuest( "TM1_Q13s" )
	LuaDebugTrace( "DEBUG: обучение ластхиту - до сих пор герой убил:"..tostring(LuaHeroGetKillsTotal( "local") ) )
	counterKills = 0
	StartTrigger( KillsCount, 5, LuaHeroGetKillsTotal( "local") )
end

function KillsCount( totalKillsNeeded, killsBeforeCount)
	if (LuaHeroGetKillsTotal( "local") - killsBeforeCount) > counterKills then
		counterKills = counterKills+1
		LuaUpdateSessionQuest ("TM1_Q13s", counterKills)	
		LuaDebugTrace( "DEBUG: обучение ластхиту, счетчик убийств увеличился и стал = "..tostring(counterKills))
		LastHitTutorial = true
	end
	if counterKills >= totalKillsNeeded then
		LuaRemoveSessionQuest( "TM1_Q13s" )
		LuaDebugTrace( "DEBUG: обучение ластхиту закончилось" )
		LastHitTutorial = false
		return true
	end
end

function CameraAwayWarning()
	distanceAway = 300
	if not isCinematicCurrentlyPlayed and not isHintLineShow then
		local xCam,yCam = LuaCameraGetPos()
		local xHero,yHero = LuaUnitGetPosition( "local" )
		if ( DistanceSquared( xCam, yCam, xHero, yHero ) >= distanceAway ) and cameraAwayHintOff and not isCinematicCurrentlyPlayed and not isHintLineShow then
			LuaDebugTrace( "DEBUG: Камера удалилась слишком далеко от игрока, дистанция между ними:"..tostring(DistanceSquared( xCam, yCam, xHero, yHero )))
			ShowHintline( "TM1_D07_2", false ) -- у этого хинтлайна отключен бип, чтобы ничего не забажило
			cameraAwayHintOff = false
		elseif ( DistanceSquared( xCam, yCam, xHero, yHero ) < distanceAway ) and not cameraAwayHintOff then
			ShowHintline("")
			cameraAwayHintOff = true
		end
	else
		--ShowHintline("")
		--cameraAwayHintOff = true	
	end
	return false
end

function CameraBtnHint()
	LuaShowTutorialElementHighlight("CameraBtn", true)
	ShowHintline("TM1_D07_3", false)
	Wait(5)
	ShowHintline("")
	LuaShowTutorialElementHighlight("CameraBtn", false)
	return true
end
