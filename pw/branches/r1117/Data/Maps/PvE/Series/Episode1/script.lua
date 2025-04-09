include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")
include ("Maps/PvE/Series/PvECommon.lua")
include ("Maps/PvE/Series/Episode1/spawners.lua")
include ("Maps/PvE/Series/Episode1/dialogs.lua")
include ("Maps/PvE/Series/Episode1/Objective_Pets.lua")
include ("Maps/PvE/Series/Episode1/Objective_Boroviks.lua")
include ("Maps/PvE/Series/Episode1/Objective_Towers.lua")
include ("Maps/PvE/Series/Episode1/Objective_Sirin.lua")
include ("Maps/PvE/Series/Episode1/CreepStats.lua")


debugTestExplosion = false
ARTEFACT_EXPLOSION_DELAY = 1.8

debugSkipDialogs = false

debugCompleteObjectiveTowers = false
debugCompleteObjectiveBorovik = false
debugCompleteObjectivePets = false
debugCompleteAmbushedTroops = false
debugTestLastButOneWave = false
debugTestKogotAndKlyk = false

debugSkipBoroviks = false
debugStartFromBase = false

debageTraceOn = true

debugSetMainHeroAlmostImmortal = false
debugSetWitcherAlmostImmortal = false

-- эффект зарядки 
--/Effects/Buffs/ColdCharged/_.EFFT
--/Effects/Buffs/Runes/_Blue.PRXY
--/Effects/Environment/TerrainDamage/_.EFFT
--/Effects/General/Teleport/_Cast.EFFT
--/Effects/Buffs/Berserk/_LightningBlue.EFFT
--/Effects/Buffs/Defence/_Blue.EFFT
--/Effects/Buffs/EnergyBurst/_Cycle.EFFT
--/Effects/Debuffs/Explosion/_Prime.PRXY - взрыв прайма
--/Effects/Debuffs/Explosion/_Techno.PRXY - взрыв
--/Effects/Environment/TerrainDomination/_Cast.PRXY - зеленое светящееся пропадающее облако
--/Effects/Environment/TreeTransactions/_FXStart_b.PRXY пропадающее синее спиралевидное сияние





--/Effects/Debuffs/Burn/_Blue.EFFT загадочная голубая хрень
--/Effects/Debuffs/Cloud/_Paint.EFFT загадочная голубая хрень 2
--/Effects/Debuffs/Crystal/_Enemy.EFFT летают кристаллы
--/Effects/Debuffs/Freeze/_Partial.EFFT голубой кристалл висит в воздухе
--/Effects/Debuffs/Shock/_.PRXY маленькая сферическая хрень с молниями
--/Effects/Environment/TerrainDomination/_A.EFFT



--/Effects/Debuffs/DoT/_Long.EFFT ацкое зеленое облако

--/Effects/Debuffs/Roots/_EvilCycle.PRXY некая зеленая светящаяся хрень с корнями

--/Effects/Debuffs/Shine/_Rainbow.PRXY радужный круг с лучами

--/Effects/Debuffs/Tornado/_Magic.EFFT Клевый синий ураганчик


FACTION_DOCT = 1
FACTION_ADORN = 2
FACTION_NEUTRAL = 0

HERO_DOCT = "00"
HERO_DOCT_WITCHER = "01"
HERO_DOCT_IVA = "02"
HERO_DOCT_PETOWNER = "03"

CREEPS_DOCT_AMBUSHED = "creepDoct"

HERO_ADORN = "10"
HERO_ADORN_WITCHER = "11"
HERO_ADORN_IVA = "12"
HERO_ADORN_PETOWNER = "13"
HEROES = {"01","02","03","04","05","11","12","13","14","15"}
TOWERS_DOCT = { "towerLeftDoct", "towerUpDoct", "towerRightDoct" }
TOWERS_ADORN = { "towerLeftAdorn", "towerUpAdorn", "towerRightAdorn" }
STATUS_DEAD_FLAGS = {ForbidMove, ForbidAutotargetMe, ForbidTakeDamage, ForbidAutoAttack, ForbidPlayerControl, ForbidLifeRestore, ForbidAttack, Stun}
STATUS_HEALER_FLAGS = {ForbidAutoAttack, ForbidInteract, ForbidPlayerControl, ForbidAttack, ForbidMove}
STATUS_CHANNELING_FLAGS = {ForbidAutoAttack, ForbidInteract, ForbidPlayerControl, ForbidAttack, ForbidMove}


CREEPS_ADORN_AMBUSHED = "creepAdorn"

ARTIFACT_LIMIT = 40
BOROVIK_HUT_HEALTH = 1000

mainHero = HERO_DOCT
witcher = HERO_DOCT_WITCHER
iva = HERO_DOCT_IVA
petOwner = HERO_DOCT_PETOWNER
klyk = "13"
kogot = "14"
creepsAmbushed = CREEPS_DOCT_AMBUSHED
factionName = "Doct"
factionEnemyName = "Adorn"
factionPlayer = FACTION_DOCT
factionEnemy = FACTION_NEUTRAL
factionEnemyCrap = FACTION_ADORN
towers = TOWERS_DOCT
towerRange = LuaGetUnitStat( towers[1], StatVisibilityRange )
killedNeutralCreepsCount=0
killedDoctCreepsCount=0
killedAdornCreepsCount=0
wavesStarted = false
kogotIsKilled = false
isMissonFinished = false
endIsNear = false
playerFactionFlag = 2
enemyFactionFlag = 1
sleeps = 0
convertedCreepsCount = 0
gatheredTowerPart = 0
totalTowerParts = 0
repairedTowers = 0
pets = {}
criticalQuestsCount = 3
readyForSecondPart = false
playerMeetsIva = false




castleX, castleY, castleR = LuaGetScriptArea("ruinedCastle")


enemyHeroes = {}
towersList = {}

function Init()
	PvECommonInit( reconnecting )
	SpawnersInit( reconnecting )
	
	LuaCreatureHide( "bottom2Adorn", true )
	LuaCreatureHide( "templeAdorn", true )
	LuaCreatureHide( "bottom2Doct", true )		
	LuaCreatureHide( "templeDoct", true )
	
	if LuaGetLocalFaction() == FACTION_DOCT then
		LuaCreatureHide(HERO_ADORN, true)
		LuaCreatureHide(HERO_ADORN_WITCHER, true)
		LuaCreatureHide(HERO_ADORN_IVA, true)
		
		--Настройка башен
		CreatureListHide(TOWERS_ADORN, true)
		
		LuaCreatureHide( "bottomAdorn", true )

	else
		LuaCreatureHide(HERO_DOCT, true)
		LuaCreatureHide(HERO_DOCT_WITCHER, true)
		LuaCreatureHide(HERO_DOCT_IVA, true)

		mainHero = HERO_ADORN
		witcher = HERO_ADORN_WITCHER
		iva = HERO_ADORN_IVA
		petOwner = HERO_ADORN_PETOWNER
		klyk = "03"
		kogot = "04"
		creepsAmbushed = CREEPS_ADORN_AMBUSHED
		factionName = "Adorn"
		factionEnemyName = "Doct"
		factionPlayer = FACTION_ADORN
		factionEnemyCrap = FACTION_DOCT -- фракция, которой принадлежат наши крипы, которые не должны быть видны под туманом войны. Сейчас это вражеская фракция и под нее настроены тултипы в advMapSettings. 
		towers = TOWERS_ADORN
		playerFactionFlag = 4
		
		--Настройка башен
		CreatureListHide(TOWERS_DOCT, true)
		
		LuaCreatureHide( "bottomDoct", true )		

	end
	
	LuaCreatureHide( petOwner, true )
	LuaCreatureHide( iva, true )		
    
	LuaCreatureHide( klyk, true )
    LuaSetCreepFaction( klyk, factionEnemy )
	LuaCreatureHide( kogot, true )
    LuaSetCreepFaction( kogot, factionEnemy )
	
	LuaSetSpawnNeutralCreeps(false)
	LuaSetSpawnCreeps(false)
	LuaSetManualGameFinish( true )
    LuaSetNatureProgress( 0.5, 0.5 )
	
	if debugTestExplosion then
		LuaCreatureHide( kogot, false )
		AddStateEnd( TestExplosion )
		return
	end
	
	LuaHeroSetForbidRespawn( klyk, true )
	LuaHeroSetForbidRespawn( kogot, true )
	
	enemyHeroes[ kogot ] = {isHidden = true}
	enemyHeroes[ klyk ] = {isHidden = true}
	
	LuaUnitAddFlag( iva, ForbidMove )
	LuaSetUnitStat( iva, StatLife, 2000 )
	LuaSetUnitHealth( iva, 2000 )
	
	ivaX, ivaY = LuaGetScriptArea( "startWaves" )


	LuaApplyPassiveAbility( klyk, "CantDeath" )
	LuaApplyPassiveAbility( kogot, "CantDeath" )
	LuaApplyPassiveAbility( klyk, "applUncontrollable" )
	LuaApplyPassiveAbility( kogot, "applUncontrollable" )
	
	southReinforcements = "southReinforcements"..factionName
	gateCenterGuard = "gateCenterGuard"..factionName
	ivaGuard = "ivaGuard"..factionName
	gateUpGuard = "gateUpGuard"..factionName
	gateRightGuard = "gateRightGuard"..factionName
	gateLeftGuard = "gateLeftGuard"..factionName
	
	mainHeroPetAbilityId = LuaApplyPassiveAbility ("local", "pet")

	
	towerLeft = "towerLeft"..factionName
	towerUp = "towerUp"..factionName
	towerRight = "towerRight"..factionName
	
	SetUnitsFlagList(towers, {ForbidAttack, ForbidDeath, ForbidTakeDamage, ForbidAutotargetMe, ForbidSelectTarget }, true)
	
	for i=1, #towers do 
		LuaSetUnitHealth(towers[i], 1) 
		if factionPlayer == FACTION_DOCT then
			LuaPlaceAttachedEffect("smoke"..towers[i], "smokeA", towers[i])
			LuaPlaceAttachedEffect("fireAndSmoke"..towers[i], "fireAndSmokeA", towers[i])
		else
			LuaPlaceAttachedEffect("smoke"..towers[i], "smokeB", towers[i])
			LuaPlaceAttachedEffect("fireAndSmoke"..towers[i], "fireAndSmokeB", towers[i])
		end		
		LuaPlaceAttachedEffect("towerBroken"..towers[i], "towerBrokenEffect",towers[i])
		LuaSetUnitStat( towers[i], StatVisibilityRange, 0 )
	end
	
	LuaCreatureHide( "towerUpBottom"..factionEnemyName, true )
	LuaCreatureHide( "towerLeftBottom"..factionEnemyName, true )
	LuaCreatureHide( "towerRightBottom"..factionEnemyName, true )
	
	SetUnitsFlagList( {"borovikLeftHut", "borovikRightHut"}, {ForbidTakeDamage}, true)
	borovikHuts = {"borovikLeftHut", "borovikRightHut"}
	for i=1, #borovikHuts do
		LuaCreatureHide( borovikHuts[i], true )
	end
	
	if debugSetMainHeroAlmostImmortal then
		LuaSetUnitStat( mainHero, StatLifeRegenerationAbsolute, 200 )
	end
	if debugSetWitcherAlmostImmortal then
		LuaSetUnitStat( witcher, StatLifeRegenerationAbsolute, 200 )		
	end
	

	--AddStateEnd( TST )
	AddStateEnd( Main )
end

function TestExplosion()
	DebugTrace("[TestExplosion] STARTED")
	local x, y = LuaGetScriptArea( "mainHeroPosition" )
	LuaCreatureTeleportTo( mainHero, x, y )
	LuaCameraObserveUnit( mainHero )
	x, y = LuaGetScriptArea( "witcherPosition" )
	LuaCreatureTeleportTo( kogot, x, y )
	LuaHeroAIDisable( kogot )
	LuaAddHeroToInfoPanel( kogot )
	LuaCreatureHide( iva, false )

	LuaUnitAddFlag( kogot, ForbidMove + ForbidAttack + ForbidAutoAttack + ForbidUseTalents )
	LuaUnitAddFlag( iva, ForbidMove + ForbidAttack + ForbidAutoAttack + ForbidUseTalents )
	local n = 0
	while true do
		n = n + 1
		LuaForceAnimation( iva, "channeling", -1 ) 
		x, y = LuaUnitGetPosition( iva )
		LuaPlaceAttachedEffect("ChannelingArtifact"..n, "chargeArtefactEnd", iva)
		
		while not UnitIsRealyDead( kogot ) do SleepState() end
		x, y = LuaUnitGetPosition( kogot )

		LuaPlaceStandaloneEffect("EffectShockWave"..n, "shockWaveKogot", x, y)
		LuaChangeNatureMapXY( x, y, 100, -1, FACTION_NEUTRAL )
		WaitState(5)
		x, y = LuaUnitGetPosition( iva )		
		LuaPlaceStandaloneEffect("EffectShockWaveArtifact"..n, "shockWave", x, y)
		if ARTEFACT_EXPLOSION_DELAY > 0 then
			WaitState(ARTEFACT_EXPLOSION_DELAY)
		end
		LuaChangeNatureMapXY( x, y, 100, -1, factionPlayer )
		LuaStopForcedAnimation( iva )
		LuaRemoveStandaloneEffect( "ChannelingArtifact"..n )
		WaitState(5)
		if UnitIsRealyDead( kogot ) then
			LuaHeroRespawn( kogot )
		end
		LuaDebugTrace("Kogot is alive!")
		x, y = LuaGetScriptArea( "witcherPosition" )
		LuaCreatureTeleportTo( kogot, x, y )
		SleepState()
	end
end

function Main()
	if factionPlayer == FACTION_DOCT then 
		LuaChangeNatureMap("allMap", FACTION_ADORN, FACTION_DOCT)
	end
	local x,y = LuaUnitGetPosition(mainHero)
	LuaSetUnitStat( mainHero, StatEnergyRegeneration, 0.6 )		-- скорость регенерации энергии героя 0.6%
	
	LuaShowUIBlock( "ActionBarStatisticBtn", false ) -- отключаем вызов окна статистики
	LuaShowUIBlock( "ChatBlock", false ) -- отключаем показ чата
    
	AddTriggerEnd( WatchForMainHeroForce )
    AddTriggerEnd( LevelupTimer )
	
	LuaAddHeroToInfoPanel( witcher )
	

	
	AddTriggerEnd( ShowKoboldsTent )
	
	AddTriggerEnd( InitPetOwnerQuest )
	
	AddTriggerEnd( SetAreaHealthful, "gateLeft" )
	AddTriggerEnd( SetAreaHealthful, "gateUp" )
	AddTriggerEnd( SetAreaHealthful, "gateRight" )
	AddTriggerEnd( SetAreaHealthful, "centerHealthArea" )
	
	--LuaApplyPassiveAbility( mainHero, "applRevive")
	
	SleepState()
	
	AddTriggerEnd( SirinQuest )

	
	--Засады
	--AddTriggerEnd( Ambush, "roadAmbush1", "road1", mainHero )
	
	AddTriggerEnd( Ambush, "forestAmbushArea", "forestAmbushers", mainHero )
	AddTriggerEnd( Ambush, "forestAmbushArea2", "forestAmbushers2", mainHero )
	AddTriggerEnd( Ambush, "forestAmbushArea3", "forestAmbushers3", mainHero )
	AddTriggerEnd( Ambush, "forestAmbushArea4", "forestAmbushers4", mainHero )
	AddTriggerEnd( Ambush, "forestAmbushArea5", "forestAmbushers5", mainHero )
	AddTriggerEnd( Ambush, "forestAmbushArea6", "forestAmbushers6", mainHero )
	AddTriggerEnd( Ambush, "forestAmbushArea7", "forestAmbushers7", mainHero )
	
	AddTriggerEnd( GateReinforcements, "Center" )
	
	AddStateEnd( MissionIntro )	
	AddStateEnd( Objective1_ReachRuinedCastle )
	AddStateEnd( Objective2_DefendCastle )
	
	
	--local x,y = LuaUnitGetPosition( mainHero )
	--LuaChangeNatureMapXY( x, y, 100, -1, factionPlayer )
	--LuaSetVisMapMode(3)
	--SleepState()

	--TeleportTest()
	
	--AddStateEnd( WaveLastButOne )
	--StartDialog_test()
end


function WatchForMainHeroForce()
    local force = LuaHeroGetForce( mainHero )
    
    DebugTrace( "[WatchForMainHeroForce] Force= "..tostring(force) )
    FillCreepStatsArray( force )
	HeroesRefineRate( force )
    
    while true do
        WaitState( 2 )
        local newForce = LuaHeroGetForce( mainHero )
        if newForce ~= force then
            force = newForce
            DebugTrace( "[WatchForMainHeroForce] Force= "..tostring(force) )
            FillCreepStatsArray( force )
			HeroesRefineRate( force )
        end
    end
end

function HeroesRefineRate( force )
	HERO_REFINE_RATE = 0.08 * force - 10.2
	LuaHeroSetRefineRate( klyk, HERO_REFINE_RATE )
	LuaHeroSetRefineRate( kogot, HERO_REFINE_RATE )
	LuaHeroSetRefineRate( witcher, HERO_REFINE_RATE )
	LuaHeroSetRefineRate( petOwner, HERO_REFINE_RATE )
   	LuaAddHeroToInfoPanel( witcher )
	DebugTrace("[HeroesRefineRate] HERO_REFINE_RATE = "..HERO_REFINE_RATE)
end

function ShowKoboldsTent()
	LuaSetCreepFaction( "koboldsAreaOpener", factionPlayer )
	SleepState();
	LuaCreatureHide( "koboldsAreaOpener", true )
end

function MissionIntro()
    if not debugStartFromBase then
        StartDialog_missionIntro()
    end
	AddTriggerEnd( WitcherFollowHero )
	AddTriggerEnd( MoveHeroWhenResurrects )
end

function WitcherFollowHero()
	DebugTrace("STARTED: [WitcherFollowHero]")
	while true do
		DebugTrace("[WitcherFollowHero] witcher starts follow main hero")
		LuaHeroAIFollowHero( witcher, mainHero )
		while not UnitIsRealyDead( mainHero ) do SleepState() end
		DebugTrace("[WitcherFollowHero] main hero is dead! Witcher goes to guard castle area")
		if playerMeetsIva then
			if not UnitIsRealyDead( witcher ) then
				LuaHeroAIGuardScriptArea( witcher, "ruinedCastle", true )

                while UnitIsRealyDead( mainHero ) do SleepState() end
				DebugTrace("[WitcherFollowHero] main hero returns! ")
			else
				while UnitIsRealyDead( witcher ) == false do SleepState() end
			end
		end
		SleepState()
	end
	DebugTrace("FINISHED: [WitcherFollowHero]")
end

function Ambush( areaName, spawnerName, heroName )
	LuaDebugTrace("STARTED: [Ambush] for area ["..areaName.."], spawner ["..spawnerName.."] and hero ["..heroName.."]")
	WaitForUnitInArea( mainHero, areaName )
	local x,y,r = LuaGetScriptArea( areaName )
	LuaPlaceStandaloneEffect("Effect"..areaName..spawnerName, "neutralTerrain", x, y)
	LuaChangeNatureMap( areaName, -1, FACTION_NEUTRAL)
	WaitState(1)
	SpawnerSpawn( spawnerName, factionEnemy, true )
	LuaDebugTrace("FINISHED: [Ambush] for area ["..areaName.."], spawner ["..spawnerName.."] and hero ["..heroName.."]")
end

function Objective1_ReachRuinedCastle()
	LuaDebugTrace("TRACE: Objective1_ReachRuinedCastle STARTED")

    if debugStartFromBase then
        LuaCreatureHide( "lockNextUp", true )
        LuaCreatureHide( "lockNextDown", true )        
        local teleportAreaX, teleportAreaY, r = LuaGetScriptArea("mainHeroPosition")
        LuaCreatureTeleportTo( mainHero, teleportAreaX, teleportAreaY )	
        teleportAreaX, teleportAreaY, r = LuaGetScriptArea("witcherPosition")
        LuaCreatureTeleportTo( witcher, teleportAreaX, teleportAreaY )	      
        LuaCameraMoveToPos( teleportAreaX, teleportAreaY )
    else 
        AddTriggerEnd( RoadEvents )
    end
    
	AddQuest( "reachCastle", true, false )
	
	castleAreaX, castleAreaY, castleAreaR = LuaGetScriptArea( "ruinedCastle" )
	while not IsUnitInArea( mainHero, "ruinedCastle" ) and #LuaGetCreepsInArea( castleAreaX, castleAreaY, castleAreaR, playerFactionFlag ) == 0 do
		SleepState()
	end
	LuaDebugTrace("TRACE: Castle Reached!!!")
	
	if LuaGetLocalFaction() == FACTION_DOCT then		
		LuaCreatureHide( "bottom2Doct", false )		
		LuaCreatureHide( "templeDoct", false )
	else
		LuaCreatureHide( "bottom2Adorn", false )
		LuaCreatureHide( "templeAdorn", false )
	end
	
	
	local playerX, playerY = LuaGetScriptArea("playerResurrectPoint")
	local witcherX, witcherY = LuaGetScriptArea("witcherResurrectPoint")
	LuaHeroSetRespawnPoint( mainHero, playerX, playerY )
	LuaHeroSetRespawnPoint( witcher, witcherX, witcherY )	
	
	
	SpawnerSpawn( "ivaAmbushers", factionEnemy, true )
	SpawnerSpawn("ivaGuard"..factionName)
	
	LuaCreatureHide( iva, false )
	local ivaX, ivaY = LuaGetScriptArea( "startWaves" )
	LuaCreatureTeleportTo( iva, ivaX, ivaY )
	--local x, y = LuaGetScriptArea( "ruinedCastle" ) -- отключил, почему-то задается не корректный поворот Ивы
	rotateTime = 0.3
	RotateHeroTo( iva, "towerUpAdorn" )	
	
	
	LuaCreatureHide( "antiblinker1", true )
	LuaCreatureHide( "antiblinker2", true )
	LuaCreatureHide( "antiblinker3", true )
	LuaUnitApplyApplicator( iva, "quest_questionYellow" )
	
	
	SetUnitListHealth ( GetSpawnerUnits( ivaGuard ), 150, true,  100)
	SetUnitListHealth ( GetSpawnerUnits( "ivaAmbushers" ), 100, true,  30)
	
	SetUnitListImmortal( GetSpawnerUnits( ivaGuard ), true )
	SetUnitListImmortal( GetSpawnerUnits( "ivaAmbushers" ), true )
	AddTriggerEnd( SetUnitImmortal, iva, true )
	
	while IsUnitNearUnit( {mainHero, witcher}, GetSpawnerUnits( "ivaAmbushers" ), 9 ) == false and IsUnitAttackedByObject( GetSpawnerUnits( "ivaAmbushers" ), {mainHero, witcher} )==false do
		SleepState()
	end
	
	SetUnitListImmortal( GetSpawnerUnits( ivaGuard ), false )
	SetUnitListImmortal( GetSpawnerUnits( "ivaAmbushers" ), false )
	AddTriggerEnd( SetUnitImmortal, iva, false )
	
	AddTriggerEnd( IvaMustSurvive )	
	AddTriggerEnd( EnemyAtTheGateWarning )
	
	LuaAddHeroToInfoPanel( iva )
	CompleteQuest( "reachCastle" )
	
	WaitForSpawnerUnitsDead( "ivaAmbushers" )	
	
	StartDialog_meetIva()
	
	playerMeetsIva = true
	
	AddQuest( "IvaQuestGoOut", true, false )
	LuaCreatureHide( "castlelock1", true )
	LuaCreatureHide( "castlelock2", true )
	LuaCreatureHide( "castlelock3", true )
	
	LuaUnitRemoveApplicator( iva, "quest_questionYellow" )
	LuaUnitApplyApplicator( iva, "quest_questionGrey" )	
	
	AddTriggerEnd( GateReinforcements, "Right" )	
	AddTriggerEnd( GateReinforcements, "Left" )
	AddTriggerEnd( GateReinforcements, "Left2" )
	AddTriggerEnd( GateReinforcements, "Up" )
	
	AddTriggerEnd( GoToIvaWhenSecondaryObjectivesCompleted )
	
	if debugSkipBoroviks == false then
		AddTriggerEnd( FirstBorovikEncounter )
	end
	
	AddTriggerEnd( TowersObjective )
		
	WaitForUnitOutArea( mainHero, "startWaves")	
	local continue = true
	while true do
		while true do
			local areaX, areaY, areaR = LuaGetScriptArea( "startWaves" )
			local cameraX, cameraY = LuaCameraGetPos()
			if (DistanceUA( mainHero, "startWaves") < areaR and DistanceUP( mainHero, cameraX, cameraY ) < 25 ) or readyForSecondPart == true then	
				break
			end
			SleepState()
		end
		if readyForSecondPart then
			StartSecondPart()
			return
		end
		LuaShowMessageBox("MsgBoxHeader_startWaves", "MsgBoxText_startWaves")		
		LuaSetPause(true)
		while LuaGetMessageBoxResult() == MSGBOX_NOT_CLOSED do 	SleepState() end
		LuaSetPause(false)
		if LuaGetMessageBoxResult() == MSGBOX_YES then
			continue = true
			if repairedTowers ~= #towers then
				LuaShowMessageBox("MsgBoxHeader_AreYouSureStartWaves", "MsgBoxDescription_AreYouSureStartWaves")
				LuaSetPause(true)
				while LuaGetMessageBoxResult() == MSGBOX_NOT_CLOSED do 	SleepState() end
				LuaSetPause(false)
				if LuaGetMessageBoxResult() == MSGBOX_YES then
					continue = true
				else
					continue = false
				end
			end
			if continue then				
				StartSecondPart()
				return
			end
		end
		WaitForUnitOutArea( mainHero, "startWaves")
		SleepState()
	end
end

function StartSecondPart()
	LuaDebugTrace("STARTED: [StartSecondPart")
	wavesStarted = true	
	WaitState(0.3)
	LuaUnitClearStates( witcher )
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( iva )
	LuaSetCinematicPause(true)
	LuaFadeScene( 0, 3 )
	WaitState( 4 )
	if not IsHeroAlive( witcher ) then 
		LuaHeroRespawn( witcher )	
	end
	local teleportAreaX, teleportAreaY, r = LuaGetScriptArea("mainHeroPosition")
	LuaCreatureTeleportTo( mainHero, teleportAreaX, teleportAreaY )	
	teleportAreaX, teleportAreaY, r = LuaGetScriptArea("witcherPosition")
	LuaCreatureTeleportTo( witcher, teleportAreaX, teleportAreaY )	
	
	RestoreUnitHealth( witcher )
	RestoreUnitHealth( mainHero )
	RestoreUnitHealth( iva )
	RestoreUnitHealth( petOwner )	

	local creepGuards = GetPlayerCreeps( factionPlayer, true )
	for i=1, #creepGuards do
		RestoreUnitHealth( creepGuards[i] )
	end
	
	WaitState(1)
	LuaFadeScene( 255, 1 )
	LuaSetCinematicPause(false)
	WaitState( 1 )
end

function GateReinforcements( side )
	LuaDebugTrace("STARTED: GateReinforcements for gate "..side)
	
	local allyCreepsSpawner = "gate"..side.."Guard"..factionName
	local enemyCreepsSpawner = "gate"..side.."Ambusher"
	local areaName = "gate"..side.."Ambush"
	local innerAreaName = areaName.."Inner"
	local x,y,r = LuaGetScriptArea( areaName )
	local inX, inY, inR = LuaGetScriptArea( innerAreaName )
	local allyCreeps = {}
	local enemyCreeps = {}
	
	if debugCompleteAmbushedTroops then
		DebugTrace("[GateReinforcements] debug mode. Spawner "..allyCreepsSpawner.." waits for waves start.")
		while not wavesStarted do SleepState() end
		DebugTrace("[GateReinforcements] debug mode. Waves started.")
		allyCreeps = SpawnerSpawn( allyCreepsSpawner, factionPlayer )
		local x,y,r = LuaGetScriptArea( "gate"..side )
		TeleportUnitList( allyCreeps, x, y )
		DebugTrace("[GateReinforcements] debug mode. Units from spawner "..allyCreepsSpawner.." were teleported")
		return
	end
	
	
	WaitForUnitInArea( { mainHero, witcher }, areaName )
	if wavesStarted then return end
	
	enemyCreeps = SpawnerSpawn( enemyCreepsSpawner, factionEnemy, true )
	allyCreeps = SpawnerSpawn( allyCreepsSpawner, factionPlayer )
    for i=1, #allyCreeps do
		LuaSetCreepWarfogFaction( allyCreeps[i], factionEnemyCrap )
	end
	SetUnitListHealth ( allyCreeps, 150, true,  60)
	SetUnitListHealth ( enemyCreeps, 250, true,  30)
	SetUnitListImmortal( allyCreeps, true )
	SetUnitListImmortal( enemyCreeps, true )
	LuaDebugTrace("DEBUG: [GateReinforcements] creeps spawned ")
	SleepState()
		
	while true do
	
		local notPets = GetNotPetCreepsInArea( inX, inY, inR, enemyFactionFlag )
		
		function countTrueEnemyCreeps()
			local res = 0
			for i = 1, #notPets do
				local found = false
				for j = 1, #spawnedBoroviks do
					found = found or (notPets[i] == spawnedBoroviks[j])
				end
				if not found then
					res = res + 1
				end
			end
			return res
		end
		
		if #enemyCreeps ~= countTrueEnemyCreeps() then
			DebugTrace("[GateReinforcements] enemy creeps spotted in area "..innerAreaName)
			PrintArray( GetNotPetCreepsInArea( inX, inY, inR, enemyFactionFlag ) )
			break
		end
		if AreUnitsInArea({witcher, mainHero, kogot, klyk}, innerAreaName) == true then
			DebugTrace("[GateReinforcements] hero spotted in area "..innerAreaName)
			break
		end
		if IsUnitAttackedByObject( enemyCreeps, {witcher, mainHero}) == true or IsUnitAttackedByObject( allyCreeps, {witcher, mainHero}) == true then
			DebugTrace("[GateReinforcements] creeps attacked by hero ")
			break
		end
		if endIsNear then
			SetUnitListImmortal( allyCreeps, false )
			SetUnitListImmortal( enemyCreeps, false )
			for i,unit in pairs(allyCreeps) do
				LuaKillUnit( unit )
				DebugTrace("[GateReinforcements] unit "..unit.." has been killed by script.")
			end
			for i,unit in pairs(enemyCreeps) do
				LuaKillUnit( unit )
				DebugTrace("[GateReinforcements] unit "..unit.." has been killed by script.")
			end
			return
		end
		SleepState()
	end

    for i=1, #allyCreeps do
		LuaSetCreepWarfogFaction( allyCreeps[i], factionPlayer)
	end    
	LuaDebugTrace("DEBUG: [GateReinforcements] hero is near creeps ")
	
	SetUnitListImmortal( allyCreeps, false )
	SetUnitListImmortal( enemyCreeps, false )
	
	while AreUnitsDead( allyCreeps ) == false and AreUnitsDead( enemyCreeps ) == false  do
		SleepState()
	end		
	if AreUnitsDead( allyCreeps ) == false then
		local spawnerX, spawnerY = GetSpawnerPosition( allyCreepsSpawner )
		while #LuaGetCreepsInArea(spawnerX, spawnerY, 12, enemyFactionFlag ) > 0 do SleepState() end
        
        local aliveAllyCreeps = {}
       	for i = 1,#allyCreeps do
            if not  LuaUnitIsDead( allyCreeps[i] )  then table.insert( aliveAllyCreeps, allyCreeps[i] )	end
        end
        
		if #aliveAllyCreeps > 0 then	--and IsUnitNearUnit({witcher, mainHero}, aliveAllyCreeps, 10) 		
			if allyCreepsSpawner~="gateCenterGuard"..factionName then
				WaitState(1)
				StartDialog_GateGuardSaved( side )		
			else
				StartDialog_AmbushedCreepsWin()
			end
		end
	end
	--for i=1, #allyCreeps do
		--local dead,exist = LuaUnitIsDead( allyCreeps[i] )
		--if not dead and exist then
		--	AddTriggerEnd( UnitGuardArea, allyCreeps[i], "gate"..side )
		--end
	--end
end

function UnitGuardArea( unit, areaName )
	LuaDebugTrace( "STARTED: [UnitGuardArea] unit "..unit.." guards area "..areaName )
	local NOT_IN_AREA_INTERVAL = 5
	local x,y,r = LuaGetScriptArea( areaName )
	while not UnitIsRealyDead( unit ) do
		LuaDebugTrace( "[UnitGuardArea] start while for unit "..unit.." and "..areaName )
		while IsUnitInArea( unit, areaName ) do SleepState() end
		LuaDebugTrace( "[UnitGuardArea] unit "..unit.." is not in area "..areaName )
		
		local sleep = 0
		while not IsUnitInArea( unit, areaName ) and sleep < NOT_IN_AREA_INTERVAL*50 do		
			SleepState()
			sleep = sleep + 1
		end	
		LuaDebugTrace("[UnitGuardArea] unit is in area or ")
		if sleep >= NOT_IN_AREA_INTERVAL*50 then
			LuaDebugTrace( "[UnitGuardArea] unit "..unit.." is not in area "..areaName.." more than 5 seconds" )
			while not IsUnitInArea( unit, areaName ) do	
				LuaCreatureMoveTo( unit, x + LuaRandom( 0, r/2), y + LuaRandom( 0, r/2) , 0)
				SleepState()
			end
			LuaDebugTrace( "[UnitGuardArea] unit "..unit.." has returned to area "..areaName )
		end
		SleepState()
	end
	LuaDebugTrace( "FINISHED: [UnitGuardArea] unit "..unit.." is dead ")
end

function RoadEvents()
	LuaDebugTrace("STARTED: [RoadEvents]")
	
	while IsUnitInArea( mainHero, "roadAmbushForest") == false and IsUnitInArea( mainHero, "roadAmbushRoad") == false do SleepState() end
	local side = "Up"
	if IsUnitInArea( mainHero, "roadAmbushRoad") == true then side = "Down" end
	
	StartDialog_firstChangeTerrainEncounter()
	SpawnerSpawn( "road1", factionEnemy, true )
	
	local ambushers = GetSpawnerUnits( "road1" )		
	
	local x,y = LuaUnitGetPosition( mainHero )
	while not IsUnitAttackedByObject( ambushers, witcher ) and not IsUnitAttackedByObject( witcher, ambushers) do 
		x,y = LuaUnitGetPosition( witcher )
		MoveUnitsToPoint( ambushers, x, y )
		SleepState()
	end
	DebugTrace("[RoadEvents]. Kobolds attacked")
	
	WaitForSpawnerUnitsDead( "road1" )	
	DebugTrace("[RoadEvents]. Kobolds are dead")

	LuaCreatureHide( "lockNextUp", true )
	LuaCreatureHide( "lockNextDown", true )
	
	SignalWhileUnitNotInArea( mainHero, castleX, castleY, castleR )
end

ATTACKS_INTERVAL = 10
WAVE_INTERVAL = 40

function Objective2_DefendCastle()
	LuaDebugTrace("TRACE: Objective2_DefendCastle STARTED")
	--if not StartSecondPart then
		CompleteQuest( "IvaQuestGoOut" )
		LuaHeroAddPrime( mainHero, 500 )
		LuaHeroAddPrime( witcher, 500 )
	--end
	AddQuest( "DefendCastle", true, false )
	LuaHeroRemoveApplicator( iva, "quest_questionGrey" )
	
	if debugTestLastButOneWave then
		ARTIFACT_LIMIT = 13	
		AddTriggerEnd(Objective_ChargeArtifact)		
	else		
		WaveLeft0( WAVE_INTERVAL ) --Атака без героя
		
		WaveUp0( WAVE_INTERVAL ) --Атака без героя

		WaveLeft1( WAVE_INTERVAL ) --Атакует Клык и сбегает
			
		WaveRight0( WAVE_INTERVAL ) --Атака без героя
			
		WaveUp1( WAVE_INTERVAL ) -- Атакует Коготь и сбегает
		while enemyHeroes[ kogot ].isHidden == false or enemyHeroes[ klyk ].isHidden == false do SleepState() end
		LuaDebugTrace("DEBUG: [Objective2_DefendCastle] Kogot and Klyk are hidden")
		WaitForSpawnerUnitsDead( "up1" )
		LuaDebugTrace("DEBUG: [Objective2_DefendCastle] up1 units are dead")
		WaitForSpawnerUnitsDead( "upKobolds" )
		LuaDebugTrace("DEBUG: [Objective2_DefendCastle] upKobolds units are dead")
		WaitForSpawnerUnitsDead( "up1Satyrs" )
		LuaDebugTrace("DEBUG: [Objective2_DefendCastle] up1Satyrs units are dead")
		WaitForSpawnerUnitsDead( "up1Leshij" )
		LuaDebugTrace("DEBUG: [Objective2_DefendCastle] up1Leshij units are dead")		

		WaitForWitcherRevive()
		
		StartDialog_GoToIva()

		AddQuest( "goToIva", true, false, ivaX, ivaY )
		HintArrow( iva, 3 )
		
		WaitForUnitNearUnit( mainHero, iva, 8 )
		HintArrow("")
		StartDialog_StartArtefactCharge()
		
		CompleteQuest( "goToIva" )
		LuaHeroAddPrime( mainHero, 500 )
		LuaHeroAddPrime( witcher, 500 )
		--ARTIFACT_LIMIT = 20	-- Для удобства дебага. Закомментировать! 
		AddTriggerEnd(Objective_ChargeArtifact)		
		
		WaveLeft0( 40 ) --Атака без героя

		WaveUp0( 40 ) --Атака без героя
	end
	
	WaveLastButOne() -- Одновременно приходят Коготь и Клык 
end


function WaveLeft0( nextWaveDelay )
	local x,y,r = LuaGetScriptArea( "gateLeft" )	
	AddTriggerEnd( SignalWhileUnitNotInArea, mainHero, x, y, 27, 20 )
	
	SpawnerSpawn("left1", factionEnemy, true)
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("left1Satyrs", factionEnemy, true) --Сатиры
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("leftKobolds", factionEnemy, true) --Кобольды
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("left1Satyrs", factionEnemy, true) --Сатиры
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("left1Leshij", factionEnemy, true) --Леший

	local waveSpawners = {"left1", "left1Satyrs", "leftKobolds", "left1Leshij"}
	WaitOrDie( waveSpawners, nextWaveDelay )
end

function WaitOrDie( spawnersForDead, waitInterval )
	LuaDebugTrace("STARTED: [WaitOrDie] for spawners:")
	PrintArray( spawnersForDead )
	local initTime = GetGameStep()
	LuaDebugTrace("DEBUG: [WaitOrDie]. initTime = "..initTime)
	local elapsedTime = 0
	while true do
		if AreSpawnerListUnitsDead( spawnersForDead ) == true then
			LuaDebugTrace("DEBUG: [WaitOrDie] All units in spawners are dead!")
			break
		end
		elapsedTime = GetGameStep() - initTime
		--LuaDebugTrace("DEBUG: [WaitOrDie]. elapsedTime = "..elapsedTime)
		--LuaDebugTrace("DEBUG: [WaitOrDie]. waitInterval = "..waitInterval)
		if elapsedTime > waitInterval * GetStepsCountInSecond() then
			LuaDebugTrace("DEBUG: [WaitOrDie] Time is up!")
			break
		end
		SleepState()
	end
	LuaDebugTrace("FINISHED: [WaitOrDie] for spawners:")
end

function WaveRight0( nextWaveDelay )
	local x,y,r = LuaGetScriptArea( "gateRight" )
	AddTriggerEnd( SignalWhileUnitNotInArea, mainHero, x, y, 17, 20 )
	
	SpawnerSpawn("right1", factionEnemy, true)
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("rightKobolds", factionEnemy, true) --Кобольды
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("right1Satyrs", factionEnemy, true) --Сатиры
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("rightKobolds", factionEnemy, true) --Кобольды
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("right1", factionEnemy, true)
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn("right1Leshij", factionEnemy, true) --Леший
	local waveSpawners = {"right1", "right1Satyrs", "rightKobolds", "right1Leshij"}
	WaitOrDie( waveSpawners, nextWaveDelay )
end

function WaitEnemyHeroToStartAttack( hero )
    local stepsLeftVisible = 15
    while not IsUnitNearUnit( hero, { mainHero, witcher, iva }, 12 ) and stepsLeftVisible > 0 do
        if LuaIsUnitVisible( hero ) then 
            stepsLeftVisible = stepsLeftVisible - 1
        end
        SleepState()
    end    
end

function WaveLeft1( nextWaveDelay )
	local x,y,r = LuaGetScriptArea( "gateLeft" )
	AddTriggerEnd( SignalWhileUnitNotInArea, mainHero, x, y, 27, 20 )
	
	local waveSpawners = {"left1", "leftKobolds", "left1Leshij"}
	
	SpawnerSpawn( waveSpawners[1], factionEnemy, true ) --Рогатики	
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[2], factionEnemy, true ) --Кобольды
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[3], factionEnemy, true ) --Леший
	WaitState( ATTACKS_INTERVAL )
	
	WaitForSpawnerUnitsDead( waveSpawners[1] )
	WaitForSpawnerUnitsDead( waveSpawners[2] )
	WaitForSpawnerUnitsDead( waveSpawners[3] )
	
	WaitForWitcherRevive()
		
	--Place Klyk and attack
	local x,y,r = LuaGetScriptArea("leftEnemySpawnerArea")	
	LuaCreatureHide( klyk, false )
	enemyHeroes[ klyk ].isHidden = false
	--LuaSetUnitStat( klyk, StatLifeRegenerationAbsolute, 30 )
	LuaDebugTrace("DEBUG: [WaveLeft1]. Klyk is not hidden")
	
	if LuaHeroGetLevel( klyk ) < LuaHeroGetLevel( mainHero )+3 then
		LevelUpHero( klyk, LuaHeroGetLevel( mainHero )+3 ) 
	end
	
	LuaCreatureTeleportTo( klyk, x, y)
	AddTriggerEnd( SpeedUpUnitWhileNotVisible, klyk, 56, 110, true )
	LuaHeroAIPushPath( klyk, "leftPath", true )
	
	SleepState()
	
	AddTriggerEnd( HeroRetreat, klyk, 300, "retreatPointLeft" )
    WaitEnemyHeroToStartAttack( klyk )
	StartDialog_KlykFirstEncounter()
	
	WaitState( 5 )
	
	SpawnerSpawn( waveSpawners[3], factionEnemy, true ) --Леший
	WaitState( ATTACKS_INTERVAL )
	
	WaitOrDie( waveSpawners, nextWaveDelay )	
end



function WaveUp0( nextWaveDelay )
	local x,y,r = LuaGetScriptArea( "gateUp" )
	AddTriggerEnd( SignalWhileUnitNotInArea, mainHero, x, y, 27, 20 )
	
	local waveSpawners = {"up1", "up1Satyrs", "upKobolds", "up1Leshij"}
	
	SpawnerSpawn( waveSpawners[1], factionEnemy, true)
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[2], factionEnemy, true) --Сатиры
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[1], factionEnemy, true)
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[3], factionEnemy, true) --Кобольды
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[4], factionEnemy, true) --Леший
	WaitOrDie( waveSpawners, nextWaveDelay )
end



function WaveUp1( nextWaveDelay )
	LuaDebugTrace("DEBUG: UP WAVE 1 STARTED")
	local x,y,r = LuaGetScriptArea( "gateUp" )
	AddTriggerEnd( SignalWhileUnitNotInArea, mainHero, x, y, 27, 20 )
	
	local waveSpawners = { "up1", "upKobolds", "up1Satyrs", "up1Leshij" }
	
	SpawnerSpawn( waveSpawners[1], factionEnemy, true)	
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[2], factionEnemy, true)	
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[1], factionEnemy, true)	
	WaitState( ATTACKS_INTERVAL )

	SpawnerSpawn( waveSpawners[2], factionEnemy, true)	
	WaitState( ATTACKS_INTERVAL )
	
	SpawnerSpawn( waveSpawners[3], factionEnemy, true)

	WaitForSpawnerUnitsDead( waveSpawners[1] )
	WaitForSpawnerUnitsDead( waveSpawners[2] )
	WaitForSpawnerUnitsDead( waveSpawners[3] )	
	
	WaitForWitcherRevive()
	
	local x,y,r = LuaGetScriptArea("upEnemySpawnerArea")	
	--LuaDebugTrace("DEBUG: spawner position: "..x..", "..y)
	LuaCreatureHide( kogot, false )
	enemyHeroes[ kogot ].isHidden = false
	--LuaSetUnitStat( kogot, StatLifeRegenerationAbsolute, 30 )
	LuaDebugTrace("DEBUG: klyk unhides")
	LuaCreatureTeleportTo( kogot, x, y)
	LuaDebugTrace("DEBUG: klyk teleported")
	
	if LuaHeroGetLevel( kogot ) < LuaHeroGetLevel( mainHero )+3 then
		LevelUpHero( kogot, LuaHeroGetLevel( mainHero )+3 ) 
	end
	
	SleepState()
	AddTriggerEnd( SpeedUpUnitWhileNotVisible, kogot, 56, 110, true )
	LuaHeroAIPushPath( kogot, "upPath", true )
	AddTriggerEnd( HeroRetreat, kogot, 300, "retreatPointUp", GetSpawnerUnits("up1Satyrs") )	
    WaitEnemyHeroToStartAttack( kogot )
	AddTriggerEnd( StartDialog_KogotFirstEncounter ) 
	
	WaitState( 5 )
	
	SpawnerSpawn( waveSpawners[2], factionEnemy, true)
	WaitState( ATTACKS_INTERVAL )

	LuaDebugTrace("Leshij attack!")
	SpawnerSpawn( waveSpawners[4], factionEnemy, true)
end

function WaveLastButOne()
	local x,y,r = LuaGetScriptArea( "gateRight" )
	if not debugTestKogotAndKlyk then
		AddTriggerEnd( SignalWhileUnitNotInArea, mainHero, x, y, 27, 20 )
		
		LuaDebugTrace("STARTED: [WaveLastButOne] ")
		SpawnerSpawn("right1", factionEnemy, true)
		WaitState(2)
		SpawnerSpawn("right1", factionEnemy, true)
		WaitState( ATTACKS_INTERVAL )
		
		SpawnerSpawn("right1Satyrs", factionEnemy, true) --Сатиры
		WaitState( ATTACKS_INTERVAL )
		
		SpawnerSpawn("rightKobolds", factionEnemy, true) --Кобольды
		WaitState( ATTACKS_INTERVAL )
		
		SpawnerSpawn("right1Leshij", factionEnemy, true) --Кобольды
		WaitState( ATTACKS_INTERVAL )
		
		WaitForSpawnerUnitsDead("right1")
		LuaDebugTrace("DEBUG: [WaveLastButOne] right1 spawner units are dead ")
		WaitForSpawnerUnitsDead("right1Satyrs")
		LuaDebugTrace("DEBUG: [WaveLastButOne] right1Satyrs spawner units are dead ")
		WaitForSpawnerUnitsDead("rightKobolds")
		LuaDebugTrace("DEBUG: [WaveLastButOne] rightKobolds spawner units are dead ")
		WaitForSpawnerUnitsDead("right1Leshij")
		LuaDebugTrace("DEBUG: [WaveLastButOne] right1Leshij spawner units are dead ")
	end
    
    WaitForWitcherRevive()
    
    local x,y,r = LuaGetScriptArea("rightEnemySpawnerArea")	
    
    LuaCreatureHide( klyk, false )
    enemyHeroes[ klyk ].isHidden = false
    LuaUnitAddFlag( klyk, ForbidDeath )
    LuaCreatureTeleportTo( klyk, x, y)
    SleepState()
    AddTriggerEnd( SpeedUpUnitWhileNotVisible, klyk, 56, 110, true )
    LuaHeroAIPushPath( klyk, "rightPath", true )
    LuaDebugTrace("DEBUG: [WaveLastButOne]. Klyk goes to castle")
    if LuaHeroGetLevel( klyk ) < LuaHeroGetLevel( mainHero )+3 then
        LevelUpHero( klyk, LuaHeroGetLevel( mainHero ) ) 
    end
    
    WaitState(1)
    
    LuaCreatureHide( kogot, false )
    enemyHeroes[ kogot ].isHidden = false
    LuaUnitAddFlag( kogot, ForbidDeath )
    LuaCreatureTeleportTo( kogot, x, y)
    SleepState()
    AddTriggerEnd( SpeedUpUnitWhileNotVisible, kogot, 56, 110, true )
    LuaHeroAIPushPath( kogot, "rightPath", true )
    LuaDebugTrace("DEBUG: [WaveLastButOne]. Kogot goes to castle")
    if LuaHeroGetLevel( kogot ) < LuaHeroGetLevel( mainHero )+3 then
        LevelUpHero( kogot, LuaHeroGetLevel( mainHero ) ) 
    end
    
    WaitForUnitNearUnit({mainHero, witcher, iva}, {kogot, klyk}, 12)
    StartDialog_KogotAndKlykEncounter()
    LuaUnitRemoveFlag( klyk, ForbidDeath )
    LuaUnitRemoveFlag( kogot, ForbidDeath )
    
    if not debugSetWitcherAlmostImmortal then
        LuaSetUnitStat( witcher, StatLifeRegenerationAbsolute, 70 )	
    end
    
    LuaHeroAIDisable( witcher )	
    if LuaUnitGetHealth( witcher ) < 400 then
        LuaSetUnitHealth( witcher, 400 )
        LuaDebugTrace("DEBUG: [WaveLastButOne] witcher wounded. Health added")
    end
    AddTriggerEnd( WitcherAttackKlyk )
    --witcherStatLifeRegenerationAbsolute = LuaGetUnitStat( witcher, StatLifeRegenerationAbsolute )
    --LuaSetUnitStat( witcher, StatLifeRegenerationAbsolute, 20 )
    LuaDebugTrace("DEBUG: [WaveLastButOne] witcher is immortal")	
    
    while not UnitIsRealyDead( klyk ) and not UnitIsRealyDead( kogot ) do SleepState() end
    LuaDebugTrace("DEBUG: [WaveLastButOne] klyk or kogot is dead")		

    LuaHeroAIFollowHero( witcher, mainHero )
    
    local aliveEnemyHero = kogot
    if UnitIsRealyDead( kogot ) then aliveEnemyHero = klyk end
    LuaUnitAddFlag( aliveEnemyHero, ForbidDeath )
    EnemyHeroExplosion( aliveEnemyHero ) 
end

function WitcherAttackKlyk()
	LuaDebugTrace("STARTED: [WitcherAttackKlyk]")
	while UnitIsRealyDead( klyk ) == false do
		if not UnitIsRealyDead( witcher ) then
			LuaUnitAttackUnit( witcher, klyk )
		end
		WaitState(1)
	end
end

function EnemyHeroExplosion( enemyHero )
	LuaDebugTrace("STARTED: [EnemyHeroExplosion]")
	endIsNear = true
	
	while LuaUnitGetHealth( enemyHero ) > 3 do SleepState() end
	LuaUnitAddFlag( enemyHero, ForbidTakeDamage )	
	LuaHeroAIDisable( enemyHero )
	
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	LuaUnitClearStates( enemyHero )
	LuaUnitClearStates( iva )
	
	local heroX, heroY = LuaUnitGetPosition( enemyHero )
	local nearestUnits = LuaGetCreepsInArea( heroX, heroY, 35, 7 )
	if #nearestUnits > 0 then
		SetUnitsFlagList( nearestUnits,{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract}, true)	
	end
	SetUnitsFlagList( towers,{ForbidAutoAttack, ForbidAttack, ForbidInteract}, true)
	SetUnitsFlagList( {witcher, enemyHero, iva},{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract, ForbidUseTalents, ForbidMoveSpecial}, true, true)
	if not UnitIsRealyDead( petOwner ) then
		SetUnitsFlagList( {petOwner},{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract, ForbidUseTalents}, true)
	end
	SetUnitsFlagList( {mainHero},{ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract}, true)

	LuaForceAnimation( enemyHero, "stun", -1 )
		
	StartDialog_EnemyHeroLastWord( enemyHero )
		
	SleepState()
	LuaSetUnitHealth( enemyHero, 50 )
	--LuaSetUnitStat( enemyHero, StatLifeRegenerationAbsolute, 35 )
	LuaApplyPassiveAbility ( enemyHero, "dispell")
	LuaDebugTrace("Ability dispell applied")
	WaitState(1)
	LuaUnitRemoveFlag( enemyHero, ForbidTakeDamage )
	LuaDebugTrace("DEBUG: [KogotExplosion] flags removed")
	AddTriggerEnd( RemoveMainHeroFlags )
	
	local x,y = LuaUnitGetPosition( enemyHero )
	
	local elapsedTime = 0
	local WITCHER_WAITING_TIME = 10
	local k=10
    
	while true do		
		if elapsedTime % 20 == 0 and elapsedTime ~= WITCHER_WAITING_TIME * GetStepsCountInSecond() then
			DebugTrace("[KogotExplosion] hintline " ..k)
			LuaSetHintLine( "kogotDeath_hintline_"..k, "None" )
			k = k - 1
		end
		if elapsedTime >= WITCHER_WAITING_TIME * GetStepsCountInSecond() then
			LuaSetHintLine( "", "None" )
		end

		SleepState()
		elapsedTime = elapsedTime + 1
		LuaDebugTrace("sleep")		
		if IsUnitAttackedByObject( enemyHero, mainHero ) then
			DebugTrace("[KogotExplosion] Enemy hero is attacked by player")
			LuaSetHintLine( "", "None" )
			WaitState(1)
			LuaUnitRemoveFlag( enemyHero, ForbidDeath )
			LuaKillUnit( enemyHero )
			StartDialog_EnemyHeroKilledByPlayer( enemyHero )			
			break
		end
		if elapsedTime > WITCHER_WAITING_TIME * GetStepsCountInSecond() then
			DebugTrace("[KogotExplosion] Time is up. Kogot attacked by witcher")			
			StartDialog_WitcherKillsEnemyHero( enemyHero )	
			LuaHeroAIFollowHero( witcher, mainHero )
			break
		end
	end
		
	LuaCameraMoveToPosTimed( x, y, 1 )
	WaitState(1)
	
	LuaPlaceStandaloneEffect("EffectShockWave2", "shockWaveKogot", x, y)
	LuaChangeNatureMapXY( x, y, 100, -1, FACTION_NEUTRAL )
	LuaDebugTrace("DEBUG: [Explosion] terrain changed")
	
	WaitState(2)		
	
	local ruinedCastleX, ruinedCastleY, ruinedCastleR = LuaGetScriptArea( "petOwnerGuardArea" )
	local playerCreeps1 = LuaGetCreepsInArea( ruinedCastleX, ruinedCastleY, ruinedCastleR + 15, playerFactionFlag )
	local playerCreeps2 = LuaGetCreepsInArea( x, y, 12, playerFactionFlag )
    local playerCreeps = {}
	for i = 1, #playerCreeps1 do
        if not pets[playerCreeps1[i]] then 
            table.insert( playerCreeps, playerCreeps1[i] )
        end
    end
	for i = 1, #playerCreeps2 do
		if not pets[playerCreeps2[i]] and not IsValueExists( playerCreeps2[i], playerCreeps ) then
			table.insert( playerCreeps, playerCreeps2[i] )
		end
	end
    
	convertedCreepsCount = #playerCreeps
	
	if #playerCreeps > 0 then

		local function ReplaceCreep( creep )
			unitX, unitY = LuaUnitGetPosition( creep )
			LuaPlaceStandaloneEffect( "effect"..creep, "convert", unitX, unitY )
			LuaReplaceCreep( creep, "convertedCreep", factionEnemy )
			LuaUnitAttackUnit( creep, iva )
			LuaDebugTrace("unit "..creep.." replaced and has faction "..factionEnemy)
		end
		
		local unitX, unitY = ivaX, ivaY
        
		local convertedUnit = ExtractNearestUnit( unitX, unitY, playerCreeps )
        if convertedUnit then
            local cameraX, cameraY = LuaUnitGetPosition( convertedUnit )
            LuaCameraMoveToPosTimed( cameraX, cameraY, 2 )
            WaitState(2)
            LuaZoomCamera( 35, 1 )
            WaitState(1)
            ReplaceCreep( convertedUnit )

            unitX, unitY = LuaUnitGetPosition( convertedUnit )
        end
        
		convertedUnit = ExtractNearestUnit( unitX, unitY, playerCreeps )
        if convertedUnit then
            local cameraX, cameraY = LuaUnitGetPosition( convertedUnit )
            LuaCameraMoveToPosTimed( cameraX, cameraY, 0.2 )
            WaitState(1)
            ReplaceCreep( convertedUnit )
            WaitState(1)
        end
		WaitState(1)
		LuaZoomCamera( 60, 1 )
        WaitState(2)
        
        if #playerCreeps > 0 then
            for i=1, #playerCreeps do
                ReplaceCreep( playerCreeps[i] )
            end	
            WaitState(2)
        end
		LuaDebugTrace("DEBUG: [Explosion] units changed")
	end
	
	LuaSetAdventureControlsEnabled( true, true )
    LuaCameraLock( false )
	if #nearestUnits > 0 then
		SetUnitsFlagList( nearestUnits,{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract}, false)	
	end
	SetUnitsFlagList( towers,{ForbidAutoAttack, ForbidAttack, ForbidInteract}, false)
	SetUnitsFlagList( {iva},{ForbidAutotargetMe, ForbidInteract}, false, true)
	if not UnitIsRealyDead( petOwner ) then
		SetUnitsFlagList( {petOwner},{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract, ForbidUseTalents}, false, true)
	end	
    
	LuaHeroAIFollowHero( witcher, mainHero )
	kogotIsKilled = true	
end


function Objective_ChargeArtifact()
	LuaDebugTrace("Objective_ChargeArtifact STARTED")

	
	local x,y = LuaUnitGetPosition( iva )
	local effectName = "EffectChargeArtefact"
	
	LuaPlaceAttachedEffect(effectName, "chargeArtefact", iva)
	LuaForceAnimation( iva, "channeling", -1 )
	SetUnitsFlagList( {iva}, STATUS_CHANNELING_FLAGS, true, true )
	
	AddQuest( "chargeArtefact", true, false )
	
	
	local kills = 0
	local progress = 0.01
	local prevKills = LuaHeroGetKillsTotal( mainHero ) + LuaHeroGetKillsTotal( witcher )
	
	while progress < 0.5 do
		kills = LuaHeroGetKillsTotal( mainHero ) + LuaHeroGetKillsTotal( witcher ) - prevKills 
		progress = kills / ARTIFACT_LIMIT
		LuaSetHeroProgress( iva, progress )
		LuaUpdateSessionQuest( "chargeArtefact", progress * 100  )
		if kogotIsKilled then break end
		SleepState()
	end
	local PROGRESS_LIMIT = 0.9
	
	if not kogotIsKilled then
		effectName = "EffectChargeArtefact2"
		StartDialog_ArtefactCharge50()
		LuaDebugTrace("DEBUG: [Objective_ChargeArtifact]. Artefect charge level: 50%")
		LuaPlaceAttachedEffect( effectName, "chargeArtefact2", iva)
		SleepState(1)
		LuaRemoveStandaloneEffect("EffectChargeArtefact")
		
		
		while kogotIsKilled == false do
			if progress < PROGRESS_LIMIT then
				kills = LuaHeroGetKillsTotal( mainHero ) + LuaHeroGetKillsTotal( witcher ) - prevKills 			
				progress = kills / ARTIFACT_LIMIT
				if progress < PROGRESS_LIMIT then
					LuaSetHeroProgress( iva, progress )
					LuaUpdateSessionQuest( "chargeArtefact", progress * 100 )
				end
			end
			SleepState()
		end
	else
		LuaRemoveStandaloneEffect(effectName)
	end
	progress = PROGRESS_LIMIT
	LuaDebugTrace("DEBUG: [Objective_ChargeArtifact]. Kogot is killed")
	
	LuaSetHeroProgress( iva, PROGRESS_LIMIT )
	LuaUpdateSessionQuest( "chargeArtefact", PROGRESS_LIMIT * 100  )
	if convertedCreepsCount > 0 then
		StartDialog_creepsTransformed( convertedUnit, effectName ) --показываем если после взрыва Когтя какие-то юниты поконвертились в чудь		
	else
		StartDialog_ArtefactAlmostCharged( effectName ) -- показываем, если в живых уже не было юнитов, которые могли бы поконвертится
	end	

	artifactCharged = false
	AddTriggerEnd( EndlessSpeedWaves )
	
	local REMAIN_CREEPS_TO_KILL = 5
	prevKills = LuaHeroGetKillsTotal( mainHero ) + LuaHeroGetKillsTotal( witcher )
	LuaDebugTrace("progress = "..progress)
	while progress < 1 do
		kills = LuaHeroGetKillsTotal( mainHero ) + LuaHeroGetKillsTotal( witcher ) - prevKills 
		LuaDebugTrace("kills = "..kills)
		progress = PROGRESS_LIMIT + (kills / REMAIN_CREEPS_TO_KILL) * (1 - PROGRESS_LIMIT)
		LuaDebugTrace("progress = "..progress)
		if progress >= 1 then break end
		LuaSetHeroProgress( iva, progress )
		LuaUpdateSessionQuest( "chargeArtefact", progress * 100  )
		SleepState()
	end
	CompleteQuest( "chargeArtefact" )
	
	artifactCharged = true
	
	LuaRemoveStandaloneEffect( "EffectChargeArtefact3" )
	SetUnitsFlagList( {iva}, STATUS_CHANNELING_FLAGS, false, true )
	LuaStopForcedAnimation( iva )
	LuaSetHeroProgress( iva, 0 )
	
	LuaUnitAddFlag( iva, ForbidDeath )
	StartDialog_ArtefactExplosion( ivaX, ivaY )	
	
	if ARTEFACT_EXPLOSION_DELAY > 0 then
		WaitState( ARTEFACT_EXPLOSION_DELAY )
	end
	LuaChangeNatureMapXY( x, y, 100, -1, factionPlayer )	
	
	LuaDebugTrace("DEBUG: [Objective_ChargeArtifact] Mega effect")	

	local enemyCreeps = GetPlayerCreeps( factionEnemy, true )
	PrintArray(enemyCreeps)
	for i=1, #enemyCreeps do 
		if string.find( enemyCreeps[i], "pet", 1, true ) == nil then
			LuaKillUnit( enemyCreeps[i] ) 
			DebugTrace("[Objective_ChargeArtifact] unit "..enemyCreeps[i].." killed by script")
		end
	end
	
	WaitState(3)
	StartDialog_ExplosionKillsHeroes()
	
	isMissonFinished = true
	LuaDebugTrace("OBJECTIVE COMPLETED! Hurrey! Arifact has been charged!")
	CompleteQuest( "DefendCastle" )
	WaitState(3)
	
	LuaPlaceStandaloneEffect("victoryEffect", "fireWorks", x, y)
    LuaCameraMoveToPosTimed( x, y, 0.5 ) 
    WaitState( 0.5 ) 
    
    local factionLoser 
    if factionPlayer == FACTION_DOCT then factionLoser = FACTION_ADORN else factionLoser = FACTION_DOCT end
	LuaGameFinish( factionLoser ) -- not factionEnemy, 'cause factionEnemy in now NEUTRAL
end

function EndlessSpeedWaves()

	while not artifactCharged do
		SpawnerSpawn("upKobolds", factionEnemy, true)	
		for i=1, #GetSpawnerUnits( "upKobolds" ) do
			AddTriggerEnd( SpeedUpUnitWhileNotVisible, GetSpawnerUnits( "upKobolds" )[i], 40, 110 )
		end	

		SpawnerSpawn("left1", factionEnemy, true)
		for i=1, #GetSpawnerUnits( "left1" ) do
			AddTriggerEnd( SpeedUpUnitWhileNotVisible, GetSpawnerUnits( "left1" )[i], 40, 110 )
		end	
			
		SpawnerSpawn("right1", factionEnemy, true)
			for i=1, #GetSpawnerUnits( "right1" ) do
			AddTriggerEnd( SpeedUpUnitWhileNotVisible, GetSpawnerUnits( "right1" )[i], 40, 110 )
		end	
		WaitState( 15 )
	end
	
end

function IvaMustSurvive()
	LuaHeroSetForbidRespawn( iva, true ) 
	AddTriggerEnd( IvaHealthLevelWarning )
	while UnitIsRealyDead( iva ) == false do SleepState() end
	isMissonFinished = true
	StartDialog_IvaIsDead()
	LuaDebugTrace("TRACE: IvaMustSurvive: Iva is dead")
	LuaGameFinish( factionPlayer )
end

function CheckAmbushedUnits()
	LuaDebugTrace("CheckAmbushedUnits STARTED")
	while AreUnitsDead(GetSpawnerUnits(creepsAmbushed))==false do SleepState() end
	LuaDebugTrace("FAIL: all units in south group are dead. No help from south :( ")
end

function GoToIvaWhenSecondaryObjectivesCompleted()
	LuaDebugTrace("STARTED: GoToIvaWhenSecondaryObjectivesCompleted")
	local completedCriticals = 0
	local activeQuests = 0
	while true do
        if wavesStarted then return end
		completedCriticals = CountQuests( nil, true, false, true )
		activeQuests = CountQuests( true, nil, false, nil )
        
		if completedCriticals == criticalQuestsCount and activeQuests == 0 then break end
        
        WaitState( 1 )
	end
    if wavesStarted then return end
    
	LuaDebugTrace("DEBUG: [GoToIvaWhenSecondaryObjectivesCompleted] All critical secondary quests are completed")
	while UnitIsRealyDead( mainHero ) do SleepState() end
	while LuaIsUnitAttacked( mainHero ) do SleepState() end
    
    if wavesStarted then return end
    
	CompleteQuest( "IvaQuestGoOut" )
	AddQuest( "GoToIvaWhenSecondaryObjectivesCompleted", true, false, ivaX, ivaY ) 
	HintArrow( iva, 3 )
	local areaX, areaY, areaR = LuaGetScriptArea( "ruinedCastle" )
	while not wavesStarted do
		if DistanceUA( mainHero, "ruinedCastle" ) < 15 and #LuaGetCreepsInArea( areaX, areaY, areaR, enemyFactionFlag ) == 0 then
			break
		end
		SleepState()
	end	
	CompleteQuest( "GoToIvaWhenSecondaryObjectivesCompleted" )
	readyForSecondPart = true
	HintArrow( "" )
end

function MoveHeroWhenResurrects()
	local x, y = LuaGetScriptArea( "crossroad" )
	while not playerMeetsIva do
		while not UnitIsRealyDead( mainHero ) do SleepState() end
		DebugTrace("[MoveHeroWhenResurrects] main hero is dead")
		while UnitIsRealyDead( mainHero ) do SleepState() end
		DebugTrace("[MoveHeroWhenResurrects] main hero is alive again")
		if playerMeetsIva then return end
		LuaCreatureMoveTo( mainHero, x, y, 0 )
		SleepState()
	end
end

function WaitForWitcherRevive()
	while UnitIsRealyDead( witcher ) == true do SleepState() end
end

function SpeedUpUnitWhileNotVisible( unitName, initSpeed, desiredSpeed, onlyOnce)
	LuaDebugTrace("STARTED: [SpeedUpUnitWhileNotVisible] for unit "..unitName)
	if not LuaIsUnitVisible( unitName ) then
		LuaSetUnitStat( unitName, StatMoveSpeed, desiredSpeed)
	end
	while not UnitIsRealyDead( unitName ) do
		while not UnitIsRealyDead( unitName ) do
			if LuaIsUnitVisible( unitName ) then break end
			SleepState() 
		end
		
		LuaSetUnitStat( unitName, StatMoveSpeed, initSpeed)
		DebugTrace("[SpeedUpUnitWhileNotVisible] unit "..unitName.." has initial speed "..initSpeed )
		
		while not UnitIsRealyDead( unitName ) do
			if not LuaIsUnitVisible( unitName ) then break end
			SleepState() 
		end
		
		LuaSetUnitStat( unitName, StatMoveSpeed, desiredSpeed )
		DebugTrace("[SpeedUpUnitWhileNotVisible] unit "..unitName.." has new speed "..desiredSpeed )
		
		if onlyOnce == true then return end
		SleepState()
	end
end

function RemoveMainHeroFlags()
	local oldX, oldY = LuaUnitGetPosition( mainHero )
	local x,y = LuaUnitGetPosition( mainHero )
	while oldX == x and oldY == y do
		x,y = LuaUnitGetPosition( mainHero )
		SleepState()
	end	
	SetUnitsFlagList( {mainHero},{ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract}, false, true)
	LuaDebugTrace("FINISHED: [RemoveMainHeroFlags]")
end

function WaitForUnitMoved( unit )
	local oldX, oldY = LuaUnitGetPosition( unit )
	local x,y = LuaUnitGetPosition( unit )
	while oldX == x and oldY == y do
		x,y = LuaUnitGetPosition( unit )
		SleepState()
	end	
end

function IvaHealthLevelWarning()
	local ivaMaxHP = LuaGetUnitStat( iva, StatLife )
	LuaSetUnitStat( iva, StatLifeRegenerationAbsolute, 20 )	
	LuaDebugTrace("DEBUG: [IvaHealthLevelWarning]. iva max HP = "..ivaMaxHP)
	while true do
		while LuaUnitGetHealth( iva ) > (2 * ivaMaxHP / 3) do SleepState() end
		StartDialog_IvaDamaged()
		LuaPlaceAttachedEffect( "invulnerabilityEffect", "invulnerability", iva )
		AddTriggerEnd( SetUnitImmortal, iva, true )
		local delay = 15
		if DistanceUU( iva, mainHero ) > 80 then delay = 20 end
		WaitState( delay )
		AddTriggerEnd( SetUnitImmortal, iva, false )
		LuaRemoveStandaloneEffect( "invulnerabilityEffect" )
		WaitState(50)
	end
end

function EnemyAtTheGateWarning()
	local x,y,r = LuaGetScriptArea( "ruinedCastle" )
	
	while true do
		local stepsHasEnemy = 0;
		repeat 
			SleepState() 
			local enemyUnits = GetNotPetCreepsInArea( x, y, r, enemyFactionFlag, true )
			if #enemyUnits == 0 then
				stepsHasEnemy = 0
			else 
				stepsHasEnemy = stepsHasEnemy + 1
			end
		until stepsHasEnemy > 2 and DistanceUP( mainHero, x, y ) > r	
		
		local creepX, creepY = LuaUnitGetPosition( GetNotPetCreepsInArea( x, y, r, enemyFactionFlag, true )[1] )
		StartDialog_EnemyAtTheGateWarning( creepX, creepY )
		
		repeat SleepState() until #LuaGetCreepsInArea( x, y, r, enemyFactionFlag ) == 0		
		SleepState()
	end
end

function GetNotPetCreepsInArea( x, y, r, factionFlag, mustBeVisible )
	local petsN = 0
	for i,v in pairs(pets) do
		petsN = petsN + 1
	end
	--[[if petsN == 0 then
		return LuaGetCreepsInArea( x, y, r, factionFlag )
	end]]

	local allunits = LuaGetCreepsInArea( x, y, r, factionFlag )
	local notPetsUnits = {}
	local isPet = false
	for i=1, #allunits do
		isPet = false
		for name,v in pairs(pets) do
			if allunits[i] == name then 
				isPet = true 				
				break
			end
		end		
		if mustBeVisible == true then
			if not isPet and LuaIsUnitVisible( allunits[i] ) then			
				table.insert( notPetsUnits, allunits[i] )			
			end
		else
			if not isPet then			
				table.insert( notPetsUnits, allunits[i] )			
			end
		end
	end
	return notPetsUnits
end
