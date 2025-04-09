

dialogRunLock = false
savedCameraState = nil

function WaitForDialogStart()
	while dialogRunLock do
		SleepState()
	end;
	dialogRunLock = true;
end

function PrepareScene( sceneCenterX, sceneCenterY, moveToCenterTime, setPause )
	LuaDebugTrace("STARTED: [PrepareScene]")
	WaitForDialogStart()
	LuaSetAdventureControlsEnabled( false, false )
	if setPause == nil then
		LuaSetCinematicPause( true )
	elseif setPause == true then
		LuaSetCinematicPause( true )
	end
    
    if not savedCameraState then 
        local x, y, zoom = LuaCameraGetPos()
        savedCameraState = { x = x, y = y, zoom = zoom }
    end
    
	LuaCameraLock( true )
	LuaCameraMoveToPosTimed( sceneCenterX, sceneCenterY, moveToCenterTime )
	LuaDebugTrace("FINISHED: [PrepareScene]")
end

function FastPepareScene()
	LuaDebugTrace("STARTED: [FastPepareScene]")
	WaitForDialogStart()
	LuaSetAdventureControlsEnabled( false, false )
    if not savedCameraState then 
        local x, y, zoom = LuaCameraGetPos()
        savedCameraState = { x = x, y = y, zoom = zoom }
    end
    LuaCameraLock( true )
    LuaDebugTrace("FINISHED: [FastPepareScene]")
end

function ClearScene( moveBackTime, sceneCenterX, sceneCenterY )
	DebugTrace("STARTED: [ClearScene]")
    if moveBackTime == nil then moveBackTime = 1 end
    local zoom = 0
    if savedCameraState then zoom = savedCameraState.zoom end
    
	if sceneCenterX == nil then
        if savedCameraState then 
            DebugTrace("[ClearScene] using saved position ")
            sceneCenterX, sceneCenterY = savedCameraState.x, savedCameraState.y
		elseif not UnitIsRealyDead( mainHero ) then
            DebugTrace("[ClearScene] using main hero position ")
			sceneCenterX, sceneCenterY = LuaUnitGetPosition( mainHero )
		end
	end		
    
    LuaCameraMoveToPosTimed( sceneCenterX, sceneCenterY, moveBackTime )	
    WaitState( moveBackTime )
    if zoom > 0 then 
        LuaZoomCamera( zoom, 0.5 )
        WaitState(0.5)
    end

	LuaCameraLock( false )
	LuaSetCinematicPause( false )
	LuaSetAdventureControlsEnabled( true, true )
    
	savedCameraState = nil
	dialogRunLock = false;
end

function StartDialog_missionIntro()
	if debugSkipDialogs then return end
	local x,y,r = LuaGetScriptArea( "crossroad" )
		
	LuaSetAdventureControlsEnabled( false, false )
	--LuaSetCinematicPause( true )
	LuaCameraLock( true )
	
	LuaCreatureMoveTo( mainHero, x, y, 0 )
    WaitState( 1.5 )
	LuaCreatureMoveTo( witcher, x, y, 0 )
    WaitState( 1 )
    
	WaitForUnitInArea( mainHero, "crossroad" )
	SleepState()
    
	UnitsTalking( mainHero, witcher, 0.1 )
	
	--SpawnerSpawn("test", factionPlayer )
	--WaitState(3)
	--for i=1, #GetSpawnerUnits("test") do
	--	x, y = LuaUnitGetPosition( GetSpawnerUnits("test")[i] )
	--	LuaPlaceStandaloneEffect( "effect"..i, "convert", x, y)
	--	LuaReplaceCreep(GetSpawnerUnits("test")[i], "/Creeps/Minions/Minion1/CTF_S4.CREEP", factionEnemy)
	--end
		
	
	
	local dialogName = "missionIntro"

	LuaStartCinematic( dialogName )
	
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	LuaDebugTrace("DEBUG: [StartDialog_missionIntro] dialog finished")
	
	ClearScene()
end

function StartDialog_firstChangeTerrainEncounter()
	if debugSkipDialogs then return end
	local x,y = LuaUnitGetPosition( witcher )	
	PrepareScene(x, y, 1)

	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	
	local dialogName = "firstChangeTerrainEncounter"

	LuaStartCinematic( dialogName )
	while LuaIsPhraseFinished( "witcherWarning" )==false do SleepState() end 
	
	LuaSetCinematicPause( false )
	--LuaSplineCameraTimedNew("/Maps/PvE/Series/Episode1/firstEncounter_1.CSPL", 6)
	local area = "roadAmbushForest"
	if not IsUnitInArea( mainHero, "roadAmbushForest" ) then
		area = "roadAmbushRoad"
	end
	local x,y,r = LuaGetScriptArea( area )
	--LuaSetVisMapMode( 3 ) 	
	--LuaCreatureHide( mainHero, true )
	--LuaCreatureHide( witcher, true )
	LuaPlaceStandaloneEffect("testeff", "neutralTerrain", x, y)
	for i=1, 20 do
		LuaChangeNatureMapXY( x,y, 1+i, -1, FACTION_NEUTRAL)
		SleepState(8)
		--if not LuaIsSplineCameraActive() then break end
	end
	--while LuaIsSplineCameraActive() do SleepState() end
	

	--LuaCreatureHide( mainHero, false )
	--LuaCreatureHide( witcher, false )
	SleepState()
	--LuaSetVisMapMode( -1 )
	--LuaCreatureHide( mainHero, false )
	--LuaCreatureHide( witcher, false )
	
	--LuaSplineCameraTimedNew("camera_changeTerrain_heroSurvey", 9)
	--while LuaIsSplineCameraActive() do SleepState() end


	while LuaIsDialogFinished( dialogName )==false do SleepState() end 	
	LuaSetCinematicPause( true )
	
	LuaDebugTrace("DEBUG: [StartDialog_test] dialog finished")
	
	ClearScene()
end

function StartDialog_meetIva()
	if debugSkipDialogs then return end
	local x,y = LuaUnitGetPosition( iva )
	
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	LuaUnitClearStates( iva )	
	PrepareScene(x, y, 1, false )
	local mainHeroX, mainHeroY = LuaUnitGetPosition( mainHero )
	local elapsedSleeps = 0
	while DistanceUU( mainHero, iva ) > 7 do
		LuaCreatureMoveTo( mainHero, x, y, 5)		
		LuaCreatureMoveTo( witcher, x, y, 5)
		elapsedSleeps = elapsedSleeps + 1
		if elapsedSleeps > 3 then
			if DistanceUP( mainHero, mainHeroX, mainHeroY ) < 0.1 then
				DebugTrace("[StartDialog_meetIva] main hero is blocked!")
				break
			end
		end
		SleepState()
	end		
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	UnitsTalking( {mainHero, witcher, iva}, 0.1 )	
	LuaSetCinematicPause( true )

	local dialogName = "meetIva"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	LuaDebugTrace("DEBUG: [StartDialog_test] dialog finished")
	ClearScene()
end

function StartDialog_Towers()
	if debugSkipDialogs then return end
	local x,y = LuaUnitGetPosition( mainHero )
	PrepareScene(x, y, 2)
	NeedToPauseAfterPhrases("towersIntroOverview", "towersIntroWestTower", "towersIntroNorthTower", "towersIntroKoboldHut")
	LuaStartCinematic( "towersIntro" )
	WaitForPhraseFinished( "towersIntroOverview" )
		
	x,y = LuaUnitGetPosition( towerLeft )
		
	LuaCameraMoveToPosTimed( x, y, 1 )
	WaitState(2)
	LuaPauseDialog( false )
	
	WaitForPhraseFinished( "towersIntroWestTower" )

	LuaDebugTrace("DEBUG: [TowersObjective] second phrase ends")
	x,y = LuaUnitGetPosition( towerUp )
	
	LuaCameraMoveToPosTimed( x, y, 1 ) 
	WaitState(2)
	LuaPauseDialog( false )
	
	WaitForPhraseFinished( "towersIntroNorthTower" )
	LuaDebugTrace("DEBUG: [TowersObjective] third phrase ends")
	x,y = LuaUnitGetPosition( towerRight )

	LuaCameraMoveToPosTimed( x, y, 1 ) 
	WaitState(2)
	LuaPauseDialog( false )

	WaitForPhraseFinished( "towersIntroKoboldHut" )
	LuaDebugTrace("DEBUG: [TowersObjective] last phrase ends")
	local r
	x,y,r = LuaGetScriptArea( "AreaBurglarTowerLeft1" )

	LuaCameraMoveToPosTimed( x, y, 3 ) 
	WaitState(3)
	LuaPauseDialog( false )

	while LuaIsDialogFinished( "towersIntro" )==false do SleepState() end
	
	ClearScene( 3 )
end


function StartDialog_GoToIva()
	if debugSkipDialogs then return end
	local x,y = LuaUnitGetPosition( witcher )
		
	PrepareScene(x, y, 1 )

	UnitsTalking( {mainHero, witcher }, 0.1 )		

	local dialogName = "GoToIva"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	
	ClearScene()
end

function StartDialog_borovikEncounter( borovik )
	if debugSkipDialogs then return end
	local x,y = LuaUnitGetPosition( borovik )
		
	PrepareScene( x, y, 1 )
	UnitsTalking( {mainHero, borovik, witcher}, 0.1 )

	local dialogName = "borovikEncounter"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	
	ClearScene()
end

function StartDialog_secondBorovikEncounter()
	if debugSkipDialogs then return end
	local x,y = LuaUnitGetPosition( GetSpawnerUnits("borovikLeft")[1] )
	LuaDebugTrace("STARTED: [StartDialog_secondBorovikEncounter]")
	
	PrepareScene( x, y, 1 )
	UnitsTalking( {mainHero, "borovikLeft_w2_c1", witcher}, 0.1 )
	
	local dialogName = "secondBorovikEncounter"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	
	ClearScene()
end

step1Counter = 0
step2Counter = 0
function StartDialog_TowerRepaired( towerName, xstart, ystart, step, callback )
	local x,y = LuaUnitGetPosition( towerName )
	
    FastPepareScene() 
	LuaCameraMoveToPosTimed( xstart, ystart, 1 );
	WaitState(0.5)
	
	LuaCameraMoveToPosTimed( x, y, 2 ) 
	
	WaitState(1.3)
	
	local stepCounter = 0
	if step == 1 then 
		step1Counter = step1Counter + 1
		stepCounter = step1Counter
	else
		step2Counter = step2Counter + 1 
		stepCounter = step2Counter
	end

    WaitState( 1.2 )
    callback()	
	local dialogName = "towerRepaired"..step.."_"..stepCounter
	if step==1 then
		SleepState(3)
		LuaRemoveStandaloneEffect( "fireAndSmoke"..towerName )
	elseif step==2 then
		LuaRemoveStandaloneEffect( "smoke"..towerName )
		LuaRemoveStandaloneEffect( "towerBroken"..towerName )
	end
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()
end

savedGroups = 0
function StartDialog_GateGuardSaved( side )
	if debugSkipDialogs then return end
	
	savedGroups = savedGroups + 1
	
	LuaDebugTrace("STARTED: [StartDialog_GateGuardSaved]")	
	local x,y = LuaUnitGetPosition( mainHero )
		
	PrepareScene(x, y, 1)
	
	local dialogName = "GateGuardSaved_"..savedGroups

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()

	LuaDebugTrace("FINISHED: [StartDialog_GateGuardSaved]")	
end

function StartDialog_AmbushedCreepsWin()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_AmbushedCreepsWin]")	
	local x,y = LuaUnitGetPosition( mainHero )
		
	PrepareScene(x, y, 1)
	
	local dialogName = "retreatTroopsOutroWin"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 	
	ClearScene()
	
	LuaDebugTrace("FINISHED: [StartDialog_AmbushedCreepsWin]")	
end

heroesInPlace = 0 

function EnsureHeroIsAliveAndNear( hero, x, y, ensureRadius, moveToRadius, lookOn )
    if not IsHeroAlive( hero ) then 
        DebugTrace("[EnsureHeroIsAliveAndNear] Hero "..hero.." is dead. Resurrecting")		
        LuaHeroRespawn( hero )
        WaitState( 1.5 )
    end
    
    if DistanceUP( hero, x, y ) > ensureRadius then
        DebugTrace("[EnsureHeroIsAliveAndNear] Hero "..hero.." is too far. Moving closer")		
        if lookOn then
            LuaCameraLock( false )
            LuaCameraObserveUnit( hero )
        end
        if DistanceUP( hero, x, y ) > 35 then
            LuaCreatureTeleportTo( hero, x + moveToRadius, y )
            SleepState()
        else 
            while DistanceUP( hero, x, y ) > ensureRadius do 
                LuaCreatureMoveTo( hero, x, y, moveToRadius )
                SleepState() 
            end            
        end
        DebugTrace("[EnsureHeroIsAliveAndNear] Hero "..hero.." is near enemy hero")		
    end
    heroesInPlace = heroesInPlace + 1
end

function StartDialog_EnemyHeroLastWord( enemyHero )
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_KogotLastWord]")	
	local x,y = LuaUnitGetPosition( enemyHero )
		
	PrepareScene( x, y, 0.2, false )
	
	local dialogName = "KogotLastWord"
	if enemyHero == klyk then dialogName = "KlykLastWord" end
    
    SetUnitsFlagList( {witcher},{ ForbidMove }, false, true)
    heroesInPlace = 0
    AddTriggerEnd( EnsureHeroIsAliveAndNear, mainHero, x, y, 15, 5, false )
    AddTriggerEnd( EnsureHeroIsAliveAndNear, witcher, x, y, 15, 5, false )

    while heroesInPlace < 2 do 
        SleepState() 
    end    
    SetUnitsFlagList( {witcher},{ ForbidMove }, true, true)
    
    LuaCameraLock( true )
    LuaCameraMoveToPosTimed( x, y, 0.2 )
    WaitState( 0.2 )
	LuaSetCinematicPause( true )

	LuaStartCinematic( dialogName )
	LuaDebugTrace("[StartDialog_EnemyHeroLastWord] Cinematic started")
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	LuaDebugTrace("DEBUG: [StartDialog_KogotLastWord] dialog finished")
	
	ClearScene( 0.2, x, y )

	LuaDebugTrace("FINISHED: [StartDialog_KogotLastWord]")	
end

function StartDialog_EnemyHeroKilledByPlayer( enemyHero )
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_KogotKilledByPlayer]")	
	local x,y = LuaUnitGetPosition( enemyHero )
	
	PrepareScene( x, y, 1 )
	
	local dialogName = "KogotKilledByPlayer"
	if enemyHero == klyk then dialogName = "KlykKilledByPlayer" end

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	-- ClearScene здесь не нужен, это часть большого диалога EnemyHeroKilledByPlayer/WitcherKillsEnemyHero -> EnemyHeroExplosion -> creepsTransformed/ArtefactAlmostCharged
    LuaSetCinematicPause(false)
    SetUnitsFlagList( {witcher},{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract}, false, true)
end

function StartDialog_WitcherKillsEnemyHero( enemyHero )
	LuaDebugTrace("STARTED: [StartDialog_WitcherKillsEnemyHero]")	
	local x,y = LuaUnitGetPosition( witcher )
		
	PrepareScene(x, y, 1)

	local dialogName = "WitcherWantsKillKogot"
	if enemyHero == klyk then dialogName = "WitcherWantsKillKlyk" end

	LuaStartCinematic( dialogName )
	while LuaIsPhraseFinished( "WitcherKillsKogot_Witcher1" ) == false do SleepState() end
	LuaSetCinematicPause(false)
	LuaPauseDialog( true )	
	
	LuaHeroAIDisable( witcher )
	
	if IsHeroAlive( witcher ) then	
		if LuaUnitGetHealth( witcher ) < 400 then
			LuaSetUnitHealth( witcher, 400 )
			LuaDebugTrace("DEBUG: [StartDialog_WitcherKillsKogot] witcher wounded. Health added")
		end
	else
		LuaHeroRespawn( witcher )
		SleepState()
		DebugTrace("[StartDialog_WitcherKillsKogot] witcher resurrected")
	end
	
	SetUnitsFlagList( {witcher},{ForbidMove, ForbidAutotargetMe, ForbidAutoAttack, ForbidAttack, ForbidInteract}, false, true)
	
	SleepState()
		
	LuaCameraObserveUnit( witcher )
	while not LuaIsUnitAttackedByObject( enemyHero, witcher ) do 		
		if not IsHeroAlive( witcher ) then			
            LuaHeroRespawn( witcher )
			SleepState()
			DebugTrace("[StartDialog_WitcherKillsKogot] witcher resurrected")
		end
		LuaUnitAttackUnit( witcher, enemyHero )
		SleepState() 
	end
	WaitState(1)
	LuaUnitRemoveFlag( enemyHero, ForbidDeath )
	LuaKillUnit( enemyHero )
	DebugTrace("[StartDialog_WitcherKillsKogot] Kogot has been killed")
	
	LuaPauseDialog( false )
	LuaSetCinematicPause( true )
	
	DebugTrace("[StartDialog_WitcherKillsKogot] wait for dialog finish")
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	LuaCameraObserveUnit( "" )
	-- ClearScene здесь не нужен, это часть большого диалога EnemyHeroKilledByPlayer/WitcherKillsEnemyHero -> EnemyHeroExplosion -> creepsTransformed/ArtefactAlmostCharged
    LuaSetCinematicPause(false)
	LuaDebugTrace("FINISHED: StartDialog_WitcherKillsKogot")
end


function StartDialog_KlykFirstEncounter()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_KlykFirstEncounter]")	
	
	local x,y = LuaUnitGetPosition( klyk )
	
	PrepareScene(x, y, 0.5, false)

	WaitState(0.5)
	LuaSetCinematicPause( true )
	UnitsTalking({klyk, mainHero, witcher}, 0.1)
	
	x,y = LuaUnitGetPosition( klyk )
	LuaCameraMoveToPosTimed( x, y, 0.1 )
	
	local dialogName = "KlykFirstEncounter"	
	
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()
end

function StartDialog_KogotFirstEncounter()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_KogotFirstEncounter]")
    
	local x,y = LuaUnitGetPosition( kogot )
		
	PrepareScene(x, y, 0.5, false)
	WaitState(0.5)
	LuaSetCinematicPause( true )
	
	UnitsTalking( {kogot, witcher, mainHero}, 0.1 )
	
	x,y = LuaUnitGetPosition( kogot )
	LuaCameraMoveToPosTimed( x, y, 0.1 )
	
	local dialogName = "KogotFirstEncounter"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()	
end

function StartDialog_KogotAndKlykEncounter()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_KogotAndKlykEncounter]")	
	local x,y = LuaUnitGetPosition( klyk )
		
	PrepareScene(x, y, 1)
	
	local dialogName = "KogotAndKlykEncounter"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()
end

function StartDialog_ArtefactCharge50()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_ArtefactCharge50]")
	local x,y = LuaUnitGetPosition( iva )
		
	PrepareScene(x, y, 3)
	WaitState(3)
	
	local dialogName = "ArtefactCharge50"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()
end

function StartDialog_StartArtefactCharge()	
	LuaDebugTrace("STARTED: [StartDialog_StartArtefactCharge]")
	local x,y = LuaUnitGetPosition( iva )
		
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	LuaUnitClearStates( iva )	
	
	PrepareScene(x, y, 1, false )
	
	local mainHeroX, mainHeroY = LuaUnitGetPosition( mainHero )
	local elapsedSleeps = 0
	while DistanceUU( mainHero, iva ) > 7 do
		LuaCreatureMoveTo( mainHero, x, y, 5)		
		LuaCreatureMoveTo( witcher, x, y, 5)
		elapsedSleeps = elapsedSleeps + 1
		if elapsedSleeps > 3 then
			if DistanceUP( mainHero, mainHeroX, mainHeroY ) < 0.1 then
				DebugTrace("[StartDialog_StartArtefactCharge] main hero is blocked!")
				break
			end
		end
		SleepState()
	end			
	
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	
	LuaSetCinematicPause( true )
	
	local dialogName = "StartArtefactCharge"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	ClearScene()
end

function StartDialog_ArtefactAlmostCharged( effectName )
	LuaDebugTrace("STARTED: [StartDialog_StartArtefactCharge]")
	
    -- PrepareScene здесь не нужен, это часть большого диалога EnemyHeroKilledByPlayer/WitcherKillsEnemyHero -> EnemyHeroExplosion -> creepsTransformed/ArtefactAlmostCharged
	local x,y = LuaUnitGetPosition( iva )
    LuaSetCinematicPause( true )
	LuaCameraLock( true )
	LuaCameraMoveToPosTimed( x, y, 3 )    
	
	WaitState(3)
	LuaRemoveStandaloneEffect( effectName )
	LuaPlaceAttachedEffect( "EffectChargeArtefact3", "chargeArtefactEnd", iva )
	WaitState(1)
	
	local dialogName = "ArtefactAlmostCharged"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 

	ClearScene( 1, x, y )
end

function StartDialog_IvaIsDead()
	LuaDebugTrace("STARTED: [StartDialog_StartArtefactCharge]")

	local x,y = LuaUnitGetPosition( iva )
		
	PrepareScene(x, y, 1)
	
	local dialogName = "IvaIsDead"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	
	ClearScene( 1, x, y )
end

function StartDialog_BorovikHutDestroyed( hutX, hutY )
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_StartArtefactCharge]")
	
    PrepareScene( hutX, hutY, 1 ) 
		
	local dialogName = "HutDestroyed"
	if destroyedBorovkHuts == 2 then dialogName = "HutDestroyed2" end

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	ClearScene()
end

function StartDialog_EnemyAtTheGateWarning( creepX, creepY )
	if debugSkipDialogs then return end
	if endIsNear then return end
	
	LuaDebugTrace("STARTED: StartDialog_EnemyAtTheGateWarning for unit witch x = "..creepX..", y = "..creepY )
	PrepareScene( creepX, creepY, 1 )
	--LuaSetVisMapMode(3)
	SleepState()
	
	
	local dialogName = "EnemyAtTheGateWarning"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	--LuaSetVisMapMode(-1)
	LuaCreateMinimapSignal( creepX, creepY )
	
	ClearScene()
	LuaDebugTrace("FINISHED: StartDialog_EnemyAtTheGateWarning")
end

function StartDialog_creepsTransformed( creeps, effectName )
	LuaDebugTrace("STARTED: StartDialog_creepsTransformed for unit ")
	local x,y = LuaUnitGetPosition( witcher )
    -- PrepareScene здесь не нужен, это часть большого диалога EnemyHeroKilledByPlayer/WitcherKillsEnemyHero -> EnemyHeroExplosion -> creepsTransformed/ArtefactAlmostCharged
    LuaSetCinematicPause( true )
	LuaCameraLock( true )
	LuaCameraMoveToPosTimed( x, y, 2 )    
    
	LuaRemoveStandaloneEffect( effectName )
	LuaPlaceAttachedEffect( "EffectChargeArtefact3", "chargeArtefactEnd", iva )
	
	local dialogName = "creepsTransformed"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 2 )
	LuaDebugTrace("FINISHED: StartDialog_creepsTransformed")
end

function StartDialog_IvaDamaged()
	LuaDebugTrace("STARTED: [StartDialog_IvaDamaged]")
	local x,y = LuaUnitGetPosition( iva )
	PrepareScene( x, y, 2 )
	WaitState(1)
	
	local dialogName = "IvaDamaged"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	local x,y = LuaUnitGetPosition( iva )
	ClearScene( 0.2, x, y )
	LuaDebugTrace("FINISHED: [StartDialog_IvaDamaged]")
end

function StartDialog_PetOwnerQuest()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_PetOwnerQuest]")
	local x,y = LuaUnitGetPosition( petOwner )
	
	LuaUnitClearStates( mainHero )
	LuaUnitClearStates( witcher )
	PrepareScene( x, y, 1 )	
	UnitsTalking( petOwner, mainHero, 0.1 )
	
	local dialogName = "PetOwnerQuest"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene()
	LuaDebugTrace("FINISHED: [StartDialog_PetOwnerQuest]")
end

function StartDialog_PetsNotReturnedYet()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_PetsNotReturnedYet]")
	local x,y = LuaUnitGetPosition( petOwner )
	PrepareScene( x, y, 0.2 )
	UnitsTalking( petOwner, mainHero, 0.1 )
	
	local dialogName = "PetsNotReturnedYet"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_PetsNotReturnedYet]")
end

function StartDialog_PetOwnerHappy()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_PetOwnerHappy]")
	local x,y = LuaUnitGetPosition( petOwner )
	PrepareScene( x, y, 0.2 )
	UnitsTalking( petOwner, mainHero, 0.1 )
	
	local dialogName = "PetOwnerHappy"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_PetOwnerHappy]")
end

function StartDialog_PetOwnerQuestCompleted()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_PetOwnerQuestCompleted]")
	local x,y = LuaUnitGetPosition( petOwner )
	PrepareScene( x, y, 0.2 )
	UnitsTalking( petOwner, mainHero, 0.1 )
	
	local dialogName = "PetOwnerQuestCompleted"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_PetOwnerQuestCompleted]")
end

function StartDialog_EnemyHeroWounded( heroName )
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_EnemyHeroWounded]")
	local x,y = LuaUnitGetPosition( heroName )
	PrepareScene( x, y, 1 )
	local dialogName
	if heroName == klyk then
		dialogName = "KlykWounded"
	elseif heroName == kogot then
		 dialogName = "KogotWounded"
	else
		LuaDebugTrace("ERROR: dialog started for unknown hero "..heroName )
	end
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene()
	LuaDebugTrace("FINISHED: [StartDialog_EnemyHeroWounded]")
end

function StartDialog_SirinAskMercy()	
	LuaDebugTrace("STARTED: [StartDialog_SirinAskMercy]")
	local x,y = LuaUnitGetPosition( sirin )
	PrepareScene( x, y, 0.2 )
	
	local dialogName = "SirinAskMercy"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_SirinAskMercy]")
end

function StartDialog_SirinBetraysPlayer()
	LuaDebugTrace("STARTED: [StartDialog_SirinBetraysPlayer]")
	local x,y = LuaUnitGetPosition( sirin )
	PrepareScene( x, y, 0.2 )
	
	local dialogName = "SirinBetraysPlayer"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_SirinBetraysPlayer]")
end

function StartDialog_SirinCaptured()
	LuaDebugTrace("STARTED: [StartDialog_SirinCaptured]")
	local x,y = LuaUnitGetPosition( sirin )
	PrepareScene( x, y, 0.2 )
	local actors = {mainHero, sirin, witcher}
	if IsHeroAlive( witcher ) == false then actors = {mainHero, sirin} end
	UnitsTalking( actors, 0.1 )
	
	local dialogName = "SirinCaptured"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_SirinCaptured]")
end

function StartDialog_SirinAtBase()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_SirinAtBase]")
	local x,y = LuaUnitGetPosition( sirin )
	PrepareScene( x, y, 0.2 )
	
	local dialogName = "SirinAtBase"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_SirinAtBase]")
end

function StartDialog_boarMasterQuest()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_boarMasterQuest]")
	local x,y = LuaUnitGetPosition( boarMaster )
	PrepareScene( x, y, 0.2 )
	local actors = {mainHero, boarMaster, witcher}
	if IsHeroAlive( witcher ) == false then actors = {mainHero, boarMaster} end
	UnitsTalking( actors, 0.1 )
	
	local dialogName = "boarMasterQuest"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_boarMasterQuest]")
end

function StartDialog_boarMasterQuestCompleted()
	if debugSkipDialogs then return end
	LuaDebugTrace("STARTED: [StartDialog_boarMasterQuestCompleted]")
	local x,y = LuaUnitGetPosition( boarMaster )
	PrepareScene( x, y, 0.2 )
	UnitsTalking( {mainHero, boarMaster, witcher}, 0.1 )
	
	local dialogName = "boarMasterQuestCompleted"
	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end	
	
	ClearScene( 0.2 )
	LuaDebugTrace("FINISHED: [StartDialog_boarMasterQuestCompleted]")
end

function StartDialog_ArtefactExplosion( ivaX, ivaY )
	PrepareScene( ivaX, ivaY, 2 )
	
	local dialogName = "ArtefactExplosion"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	
	LuaPlaceStandaloneEffect("EffectShockWave", "shockWave", ivaX, ivaY)

	ClearScene( 0.1, ivaX, ivaY )
end

function StartDialog_GoAndReviveWitcher(  )
	local x, y = LuaUnitGetPosition( witcher )
	PrepareScene( x, y, 1 )
	
	local dialogName = "GoAndReviveWitcher"

	LuaStartCinematic( dialogName )
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 

	ClearScene()
end

function StartDialog_ExplosionKillsHeroes()
	local x,y = LuaUnitGetPosition( witcher )
	PrepareScene( x, y, 2 )
	
	local dialogName = "ExplosionKillsHeroes"

	LuaStartCinematic( dialogName )
	WaitState(1)
	while LuaIsPhraseFinished( "witcherIsDead" )==false do SleepState() end 
	LuaSetCinematicPause( false )
	LuaKillUnit( witcher )
	LuaHeroSetForbidRespawn( witcher, true )
	WaitState(2)
	
	
	if UnitIsRealyDead( petOwner ) == false then
		if IsUnitInArea( petOwner, "ruinedCastle") == true then
			x,y = LuaUnitGetPosition( petOwner )
			LuaCameraMoveToPosTimed( x, y, 2 )
			LuaKillUnit( petOwner )	
			LuaHeroSetForbidRespawn( petOwner, true )		
			WaitState(3)
		else
			LuaKillUnit( petOwner )	
			LuaHeroSetForbidRespawn( petOwner, true )				
		end
	end
	
	if UnitIsRealyDead( mainHero ) == false then
		x,y = LuaUnitGetPosition( mainHero )
		LuaCameraMoveToPosTimed( x, y, 2 )
		LuaKillUnit( mainHero )
		LuaHeroSetForbidRespawn( mainHero, true )
        LuaRemovePassiveAbility( mainHero, mainHeroPetAbilityId )
		LuaApplyPassiveAbility( iva, "pet" )
		WaitState(3)		
	end	
	
	while LuaIsDialogFinished( dialogName )==false do SleepState() end 
	
	x,y = LuaUnitGetPosition( iva )
	LuaSetCinematicPause( true )
	ClearScene( 2, x, y )
end