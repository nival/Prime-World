function TowersObjective()
	LuaDebugTrace("STARTED: TowersObjective")
	
	TOWER_MAX_HEALTH = LuaGetUnitStat( towers[1], StatLife )
	--DebugTrace( "Tower full health = "..TOWER_MAX_HEALTH )
	
	if debugCompleteObjectiveTowers then
		DebugTrace("[TowersObjective] debug mode. Objective towers waits for waves start.")
		AddQuest( "repairTowers", false, true )
		CompleteQuest("repairTowers")
		
		while not wavesStarted do SleepState() end
		DebugTrace("[TowersObjective] debug mode. Waves started.")
		for i=1, #towers do
			LuaSetUnitHealth( towers[i], TOWER_MAX_HEALTH )
			LuaSetUnitStat( towers[i], StatVisibilityRange, towerRange )
			LuaRemoveStandaloneEffect( "fireAndSmoke"..towers[i] )
			LuaRemoveStandaloneEffect( "smoke"..towers[i] )
			LuaRemoveStandaloneEffect( "towerBroken"..towers[i] )
		end
		SetUnitsFlagList(towers, {ForbidAttack, ForbidDeath, ForbidTakeDamage, ForbidAutotargetMe, ForbidSelectTarget }, false)

		DebugTrace("[TowersObjective] debug mode. All towers are repaired.")
		return
	end
	
	while IsUnitInArea( mainHero, "gateLeft" )==false and IsUnitInArea( mainHero, "gateRight" )==false and IsUnitInArea( mainHero, "gateUp" )==false  do
		SleepState()
	end
	LuaDebugTrace("DEBUG: TowersObjective. mainHero is near tower")
	
	AddTriggerEnd( RepairTower, towerRight, {"BurglarTowerRight1", "BurglarTowerRight2"})	
	AddTriggerEnd( RepairTower, towerUp, {"BurglarTowerUp1", "BurglarTowerUp2"})
	AddTriggerEnd( RepairTower, towerLeft, {"BurglarTowerLeft1", "BurglarTowerLeft2"})
	AddTriggerEnd( CompleteQuestReapairTowers )
	
	
	StartDialog_Towers()

	AddQuest( "repairTowers", false, true )
end

function RepairTower( towerName, burglarSpawnersList )
	LuaDebugTrace("RepairTower DEBUG: STARTED")
	
	totalTowerParts = totalTowerParts + #burglarSpawnersList

	local x,y,r = 0,0,0
	local effectName1 = "error"
	local effectName2 = "error"
	local areaName = "error"
	
	local i
	for i=1, #burglarSpawnersList do
		SpawnerSpawn(burglarSpawnersList[i], factionEnemy, true)
		AddTriggerEnd( CheckBurglarsReinforcementsNeed, burglarSpawnersList[i] )
		areaName = "Area"..burglarSpawnersList[i]
		x,y,r = LuaGetScriptArea( areaName )
		effectName1 = "Effect"..burglarSpawnersList[i]
		
		LuaCreateGlyph( effectName1, "glyph", x, y );
		LuaEnableGlyph( effectName1, false );
	end
	
	local n=0
	local healthAdd = TOWER_MAX_HEALTH/#burglarSpawnersList
	local step=0
	local watchedGlyphs = {}
	
	while #burglarSpawnersList ~= 0 or #watchedGlyphs ~= 0 do
		if isMissonFinished == true then return end
		
		for n=1, #burglarSpawnersList do			
			if AreSpawnerUnitsDead( burglarSpawnersList[n] ) then
				effectName1 = "Effect"..burglarSpawnersList[n]
				LuaEnableGlyph( effectName1, true )
				x,y,r = LuaGetScriptArea( "Area"..burglarSpawnersList[n] );
				table.insert( watchedGlyphs, {name = effectName1, x = x, y = y } )
				table.remove(burglarSpawnersList, n)
				LuaDebugTrace("RepairTower DEBUG: units dead")
				break;
			end
		end
		for n=1, #watchedGlyphs do		
			local effectName = watchedGlyphs[n].name
			if not LuaIsObjectExists( effectName ) then
				step = step + 1		
				AddTriggerEnd( PickUpTowerGadget, watchedGlyphs[n] , step, towerName, healthAdd )				
				table.remove( watchedGlyphs, n )
				LuaDebugTrace("RepairTower DEBUG: tower repair step")
				break;
			end
		end
		SleepState()
	end
	
	LuaDebugTrace("RepairTower DEBUG: Tower has been repaired")
	SetUnitsFlagList({towerName}, {ForbidAttack, ForbidDeath, ForbidTakeDamage, ForbidAutotargetMe, ForbidSelectTarget }, false)		
end

function PickUpTowerGadget( effectObj, step, towerName, health )	
	function DoRepairTower()
        LuaSetUnitHealth( towerName, LuaUnitGetHealth( towerName ) + health)
    end
    LuaSetUnitStat( towerName, StatVisibilityRange, towerRange )
	
	StartDialog_TowerRepaired( towerName, effectObj.x, effectObj.y, step, DoRepairTower )
	WaitState(1)
	
	gatheredTowerPart = gatheredTowerPart + 1
	
	if step == 2 then
		repairedTowers = repairedTowers + 1
		LuaUpdateSessionQuest( "repairTowers", repairedTowers )
	end
	
end

function CompleteQuestReapairTowers()
	while gatheredTowerPart ~= totalTowerParts and not isMissonFinished do SleepState() end
	CompleteQuest("repairTowers")
	if not isMissonFinished then
		LuaHeroAddPrime( mainHero, 500 )
		LuaHeroAddPrime( witcher, 500 )
	end
	LuaDebugTrace("FINISHED:[CompleteQuestRepairTowers]")	
end

function CheckBurglarsReinforcementsNeed( spawnerName )
	LuaDebugTrace("STARTED: [CheckBurglarsReinforcementsNeed]")	
	local burglarsCount = #GetSpawnerUnits( spawnerName )
	while #GetSpawnerUnits( spawnerName ) > burglarsCount - 2 do SleepState() end
	LuaDebugTrace("DEBUG: Spawner has lost 2 defenders, check reinforcements need")
	if LuaHeroGetLevel( mainHero ) > 10 then SpawnerSpawn( spawnerName, factionEnemy, true ) end	
	WaitState(10) 
	if LuaHeroGetLevel( mainHero ) > 15 then SpawnerSpawn( spawnerName, factionEnemy, true ) end	
	LuaDebugTrace("FINISHED: [CheckBurglarsReinforcementsNeed]")
end