function FirstBorovikEncounter()
	LuaDebugTrace("STARTED: [FirstBorovikEncounter]")
	
	if debugCompleteObjectiveBorovik then 
		LuaKillUnit( "borovikRightHut" )
		LuaKillUnit( "borovikRightHut" )
        AddQuest( "destroyBorovikHuts", false, true )	
        CompleteQuest( "destroyBorovikHuts" )
		DebugTrace("[FirstBorovikEncounter] debug mode: borovik huts destroyed.")
		return
	end
	
    local waitTime = 0;
    while waitTime < 600 do		
        if IsUnitNearUnit( "borovikLeftHut", {witcher, mainHero }, 35 ) then
            break;
        end
        if IsUnitNearUnit( "borovikRightHut", {witcher, mainHero }, 20 ) then
            break;
        end
        SleepState()
		waitTime = waitTime + 1
    end

    local activeSpawner 
    if waitTime >= 600 or IsUnitNearUnit( "borovikLeftHut", {witcher, mainHero }, 35 ) then
        activeSpawner = "borovikLeft"
    else 
        activeSpawner = "borovikRight"
    end
    
	LuaCreatureHide( "borovikLeftHut", false )
	LuaCreatureHide( "borovikRightHut", false )    
    
	local boroviks = SpawnerSpawn( activeSpawner, factionEnemy, true )	
	WaitForBorovik( boroviks )
	StartDialog_borovikEncounter( boroviks[1] )	
    
	WaitForUnitListDead( GetSpawnerUnits( activeSpawner ) )
	
	--SpawnerSpawn( "borovikLeft", factionEnemy, true )
	--WaitForBorovik();
	--StartDialog_secondBorovikEncounter()	
	AddQuest( "destroyBorovikHuts", false, true )	
	
	destroyedBorovkHuts = 0
	AddTriggerEnd( DestroyBorovikHut, "Left" )
	AddTriggerEnd( DestroyBorovikHut, "Right" )
end

spawnedBoroviks = {}

function WaitForBorovik( boroviks )
	
	spawnedBoroviks = boroviks
	
	local heroes = {mainHero, witcher, iva}
	local safeZoneX,safeZoneY, safeZoneR = LuaGetScriptArea( "gateLeftAmbush" )
	local inSafeZone = {}
	local startDialog = false
	while not startDialog do
		for i=1, #boroviks do
			local ux,uy = LuaUnitGetPosition(boroviks[i])
			if not inSafeZone[boroviks[i]] and DistanceSquared(ux,uy,safeZoneX,safeZoneY) < safeZoneR*safeZoneR then
				LuaUnitAddFlag( boroviks[i], ForbidAttack + ForbidAutoAttack + ForbidTakeDamage + ForbidAutotargetMe )
				inSafeZone[boroviks[i]] = 1
				LuaDebugTrace("DEBUG: [WaitForBorovik] borovik is in safe zone ")
			end
			if inSafeZone[boroviks[i]] and DistanceSquared(ux,uy,safeZoneX,safeZoneY) > safeZoneR*safeZoneR then
				LuaUnitRemoveFlag( boroviks[i], ForbidAttack + ForbidAutoAttack + ForbidTakeDamage + ForbidAutotargetMe )
				inSafeZone[boroviks[i]] = nil
				LuaDebugTrace("DEBUG: [WaitForBorovik] borovik is out of safe zone ")
			end
		
			for j=1, #heroes do
				if DistanceUU( heroes[j], boroviks[i]) < 12 then 
					startDialog = true;
					LuaDebugTrace("DEBUG: [WaitForBorovik] borovik near hero ")
				end
			end
			if LuaUnitGetHealth( boroviks[i] ) < 200 then
				startDialog = true
				LuaDebugTrace("DEBUG: [WaitForBorovik] borovik damaged enough")
			end
		end	
		SleepState()
	end
	for i=1, #boroviks do
		if inSafeZone[boroviks[i]] then
			LuaUnitRemoveFlag( boroviks[i], ForbidAttack + ForbidAutoAttack + ForbidTakeDamage + ForbidAutotargetMe )
			LuaDebugTrace("DEBUG: [WaitForBorovik] borovik is out of safe zone 2")
		end
	end

	WaitForUnitIsVisibleForTime( boroviks, 2 )
	LuaDebugTrace("DEBUG: [WaitForBorovik] borovik is visible")
end



function DestroyBorovikHut( side )	
	local hutName = "borovik"..side.."Hut"
	local attacker = "borovik"..side
	local guard = "borovik"..side.."Guard"
	
	LuaUnitRemoveFlag( hutName, ForbidTakeDamage )
	
	SpawnerSpawn( guard, factionEnemy, true )
	LuaSetCreepFaction( hutName, factionEnemy )
	
	AddTriggerEnd( HomeSweetHomeDefense, attacker, hutName )
	
	while wavesStarted == false do SleepState() end
	--LuaDebugTrace("DEBUG: [DestroyBorovikHut]. Waves started. Borovik attacks!")
	AddTriggerEnd( BorovikAttacks, attacker, hutName )
end

function BorovikAttacks( attacker, hutName )
	--LuaDebugTrace("STARTED: [BorovikAttacks] Attacker is "..attacker..". Hut is "..hutName)
	while UnitIsRealyDead( hutName ) == false do 
		--LuaDebugTrace("DEBUG: [BorovikAttacks]. Attacker "..attacker.." form hut "..hutName.." wants attack!")
		SpawnerSpawn( attacker, factionEnemy )
		WaitState(90)
		SleepState() 
	end 
	LuaDebugTrace("FINISHED: [BorovikAttacks]")
end

function HomeSweetHomeDefense( attacker, hutName )
	LuaDebugTrace("STARTED: [HomeSweetHomeDefense]")
    local hutX, hutY = LuaUnitGetPosition( hutName )
    
	while LuaUnitGetHealth( hutName ) > (BOROVIK_HUT_HEALTH / 4) and not isMissonFinished do SleepState() end
	if isMissonFinished then
		CompleteQuest( "destroyBorovikHuts" )
		return
	end
	SpawnerSpawn( attacker, factionEnemy, true )

	LuaDebugTrace("FINISHED: [HomeSweetHomeDefense]. No more Boris Borovich available")
	while UnitIsRealyDead( hutName )==false and not isMissonFinished do SleepState() end
	while AreSpawnerUnitsDead( attacker ) == false and not isMissonFinished do SleepState() end
	if isMissonFinished then
		CompleteQuest( "destroyBorovikHuts" )
		return
	end
	LuaDebugTrace("Hut "..hutName.." destroyed")	
	destroyedBorovkHuts = destroyedBorovkHuts + 1
	StartDialog_BorovikHutDestroyed( hutX, hutY )
	if destroyedBorovkHuts ~= #borovikHuts then
		LuaUpdateSessionQuest( "destroyBorovikHuts", destroyedBorovkHuts )	
	else
		CompleteQuest( "destroyBorovikHuts" )
		LuaHeroAddPrime( mainHero, 500 )
		LuaHeroAddPrime( witcher, 500 )
	end
end