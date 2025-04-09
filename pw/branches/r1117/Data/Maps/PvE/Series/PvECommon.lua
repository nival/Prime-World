
immortalFlags = {}

function PvECommonInit( reconnecting )
	if not reconnecting then
		SetGlobalVar( "PvECommon_Quests", {} )
		SetGlobalVar( "PvECommon_Followflags", {} )
	end
end
function PvECommonReconnect()
	local quests = GetGlobalVar( "PvECommon_Quests" )
	function RestoreQuests( quests )
		DebugTrace("RESTORING QUESTS:")
		for i,q in pairs(quests) do
			if q.active then 
				DebugTrace("Active:"..i..", signal="..tostring(q.hasSignal)..", progress="..tostring(q.progress));
				if q.hero == nil or LuaGetLocalHero() == q.hero then
					LuaAddSessionQuest( q.id, unpack( q.params ) )
					if q.hasSignal == true then
						LuaSessionQuestUpdateSignal( q.id, q.id.."Signal", q.signalX, q.signalY )	
					end
					if q.progress > 0 then
						LuaUpdateSessionQuest( q.id, q.progress )
					end
				end
			else 
				DebugTrace("Inactive:"..i);
			end
		end
	end
	AddTriggerEnd(RestoreQuests, quests)
end

function ClearAreaAndGoToNextArea( heroName, areaName, nextAreaName )
	--LuaUnitAddFlag( heroName, ForbidDeath )
	LuaDebugTrace("STARTED: [ClearAreaAndGoToNextArea]. her: "..heroName..", area1: "..areaName..", next area: "..nextAreaName)
	local x,y,r = LuaGetScriptArea( areaName )
	LuaHeroAIGuardScriptArea( heroName, areaName, true )
	while enemyHeroes[ heroName ].isHidden == false and DistanceUA( heroName, areaName ) > r do SleepState() end
	LuaDebugTrace("DEBUG: [ClearAreaAndGoToNextArea]. Destination area "..areaName.." reached")
	if enemyHeroes[ heroName ].isHidden == true then return end
	while #LuaGetCreepsInArea( x, y, r, playerFactionFlag ) > 0 and enemyHeroes[ heroName ].isHidden == false do SleepState() end
	LuaDebugTrace("DEBUG: [ClearAreaAndGoToNextArea]. area "..areaName.." cleared. Go to the next area "..nextAreaName)
	if enemyHeroes[ heroName ].isHidden == true then return end
	LuaHeroAIGuardScriptArea( heroName, nextAreaName, true )
	LuaDebugTrace("FINISHED: [ClearAreaAndGoToNextArea]. her: "..heroName..", area1: "..areaName..", next area: "..nextAreaName)
end
----------------------------------------------------------
--------------------- Quests -----------------------------
-- internal
function FillQuest( hero, questName, isPrimary, isCritical, ... )
	local quests = GetGlobalVar("PvECommon_Quests")
	local questNameFull = questName
	if hero then questNameFull = questName.."_"..hero end
	local q = { id = questName, hero = hero, hasSignal = false, progress = 0, critical = isCritical, primary = isPrimary, completed = false, active = true }	
	quests[ questNameFull ] = q
	
	local params = {...}
	local x, y = params[#params-1], params[#params]
	if type(x) == "number" and type(y) == "number" then
		q.hasSignal = true
		q.signalX = x
		q.signalY = y
		table.remove( params, #params )
		table.remove( params, #params )
	end	
	if #params <= 0 then params = {0} end 
	q.params = params
	
	return q
end
-- AddQuest( questName, isPrimary, isCritical, [name1, value1, ...], [signalX, signalY] )
function AddQuest( questName, isPrimary, isCritical, ... )
	LuaDebugTrace("STARTED: [AddQuest] for quest "..questName)
	local q = FillQuest( nil, questName, isPrimary, isCritical, ... )
	if q.hasSignal == true then
		LuaSessionQuestUpdateSignal( questName, questName.."Signal", q.signalX, q.signalY )		
		AddTriggerEnd( UpdateMinimapQuestSignal, questName,q.signalX, q.signalY )
	end	
	LuaAddSessionQuest( questName, unpack( q.params ) )
end

function AddPersonalQuest( hero, questName, isPrimary, isCritical, ... )
	LuaDebugTrace("STARTED: [AddPersonalQuest] "..questName.." for hero "..hero )
	
	local questNameFull = questName.."_"..hero
	local q = FillQuest( hero, questName, isPrimary, isCritical, ... )
	if LuaGetLocalHero() == hero then
		if q.hasSignal == true then
			LuaSessionQuestUpdateSignal( questName, questName.."Signal", q.signalX, q.signalY )		
			AddTriggerEnd( UpdateMinimapQuestSignal, questNameFull, q.signalX, q.signalY )
		end	
		LuaAddSessionQuest( questName, unpack( q.params ) )	
	end
end

-- SetQuestParams( questName, name1, value1, ... )
function SetQuestParams( questName, ... )
	local quests = GetGlobalVar("PvECommon_Quests")
	local q = quests[questName]
	if q == nil or not q.active then
		LuaDebugTrace("[SetQuestProgress] Quest not exists or inactive:"..questName)
		return
	end
	q.params = {...}

	if not q.hero or LuaGetLocalHero() == q.hero then
		LuaUpdateSessionQuestText( q.id, ... )
	end
end

function SetQuestProgress( questName, progress )
	local quests = GetGlobalVar("PvECommon_Quests")
	local q = quests[questName]
	if q == nil or not q.active then
		LuaDebugTrace("[SetQuestProgress] Quest not exists or inactive:"..questName)
		return
	end
	if q.progress > progress then 
		LuaDebugTrace("[SetQuestProgress] Decreasing progress:"..tostring(q.progress).."->"..tostring(progress) )
	end
	q.progress = progress
	if not q.hero or LuaGetLocalHero() == q.hero then
		LuaUpdateSessionQuest( q.id, q.progress )
	end
end

function UpdateMinimapQuestSignal( questName, x, y )
	local quests = GetGlobalVar("PvECommon_Quests")
	while quests[ questName ].hasSignal == true do
		if dialogRunLock == false then
			LuaCreateMinimapSignal( x, y )
		end
		quests[questName].signalX = x
		quests[questName].signalY = y
		
		WaitState(10)
	end
end

function SignalOnMinimap( signalArea )
	local x,y,r = LuaGetScriptArea( signalArea )
	LuaCreateMinimapSignal( x, y )
end

function IsQuestComplete( questName )
	local quests = GetGlobalVar("PvECommon_Quests")
	local q = quests[questName]
	if q == nil then
		LuaDebugTrace("[CompleteQuest] Quest not exists or inactive:"..questName)
		return true
	end
    return q.completed
end

function IsQuestActive( questName )
	local quests = GetGlobalVar("PvECommon_Quests")
	local q = quests[questName]
	if q == nil then
		LuaDebugTrace("[CompleteQuest] Quest not exists or inactive:"..questName)
		return false
	end
    return q.active
end

function CountQuests( isActive, isCompleted, isPrimary, isCritical )
	local quests = GetGlobalVar("PvECommon_Quests")
    local cnt = 0
	for i,quest in pairs(quests) do
        if isActive == nil or isActive == quest.active then 
            if isCompleted == nil or isCompleted == quest.completed then 
                if isPrimary == nil or isPrimary == quest.primary then 
                    if isCritical == nil or isCritical == quest.critical then 
                        cnt = cnt + 1
                    end
                end
            end
        end
	end
    return cnt
end
function CompleteQuest( questName, hero )	
	LuaDebugTrace("STARTED: [CompleteQuest] for quest "..questName)
	local quests = GetGlobalVar("PvECommon_Quests")
	local q = quests[questName]
	
	if q == nil or not q.active then
		LuaDebugTrace("[CompleteQuest] Quest not exists or inactive:"..questName)
		return
	end
	if not q.hero or LuaGetLocalHero() == q.hero then
		if q.hasSignal == true then
			LuaSessionQuestRemoveSignal( q.id, questName.."Signal" )	
		end
		LuaRemoveSessionQuest( q.id )	
	end
	q.hasSignal = false
	q.completed = true
	q.active = false	
	
	DebugTrace("[CompleteQuest] ACTIVE QUESTS:")
	for i,quest in pairs(quests) do
		if quest.active then 
			DebugTrace("[CompleteQuest] quest: "..i)
		end
	end
	DebugTrace("[CompleteQuest] ACTIVE AND NOT PRIMARY QUESTS:")
	for i,quest in pairs(quests) do
		if quest.active and not quest.primary then 
			DebugTrace("[CompleteQuest] quest: "..i)
		end
	end
	DebugTrace("[CompleteQuest] COMPLETED QUESTS:")
	for i,quest in pairs(quests) do
		if quest.completed then 
			DebugTrace("[CompleteQuest] quest: "..i)
		end
	end
	DebugTrace("[CompleteQuest] COMPLETED AND CRITICAL AND NOT PRIMARY QUESTS:")
	for i,quest in pairs(quests) do
		if quest.critical and quest.completed and not quest.primary then 
			DebugTrace("[CompleteQuest] quest: "..i)
		end
	end
end
----------------------------------------------------------
----------------------------------------------------------

function SignalWhileUnitNotInArea( unitName, signalX, signalY, signalAreaRadius, interval )	
	local signal = {x = signalX, y = signalY}	
	local elapsedSleeps = 0
	if interval == nil then 
		interval = 10000 
		LuaDebugTrace("[SignalWhileUnitNotInArea] interval is nil")
	else
		LuaDebugTrace("[SignalWhileUnitNotInArea] interval = "..interval)
	end
	
	HintArrow( signal, 3 )
	LuaCreateMinimapSignal( signalX, signalY )
	
	repeat
		if elapsedSleeps % 60 == 0 then
			LuaCreateMinimapSignal( signalX, signalY )
		end
		if elapsedSleeps > interval * GetStepsCountInSecond() then break end
		if dialogRunLock == true then break end
		elapsedSleeps = elapsedSleeps + 1
		SleepState()
	until DistanceUP( unitName, signalX, signalY ) <= signalAreaRadius
	
	HintArrow("")
end

function HintLineWait( hint, delay )
	LuaSetHintLine( hint, "None" )
	WaitState( delay )
	LuaSetHintLine( "", "None" )
end

function TeleportUnitList( unitList, destinationX, destinationY )
	LuaDebugTrace("STARTED: [TeleportUnitList] for destination point: x = "..destinationX..", y = "..destinationY)
	local x,y = 0,0
	local unitX, unitY = 0,0
	for i=1, #unitList do
		unitX, unitY = LuaUnitGetPosition( unitList [i] )
		if unitX ~= nil  and unitY ~= nil then
			x = x + unitX
			y = y + unitY
		end
	end
	local averageX, averageY = 0,0
	averageX = x / #unitList
	averageY = y / #unitList
	local relativePosition = {}
	for i=1, #unitList do
		unitX, unitY = LuaUnitGetPosition( unitList[i])
		relativePosition[unitList[i]] = { x = unitX - averageX, y = unitY - averageY }		
	end
	for i=1, #unitList do
		LuaCreatureTeleportTo( unitList[i], destinationX + relativePosition[unitList[i]].x, destinationY + relativePosition[unitList[i]].y )
		LuaDebugTrace("DEBUG: [TeleportUnitList]. Creature "..unitList[i].." has been teleported")
	end
	LuaDebugTrace("FINISHED: [TeleportUnitList]")
end

function AreUnitsInArea( units, area, all )
	local x,y,r = LuaGetScriptArea( area )
	local count = 0
	if all == true then
		for i=1,#units do
			if IsUnitInArea( units[i], area ) == true then
				count = count + 1
			end
		end
		if count == #units then return true
		else return false end
	else
		for i=1,#units do
			if IsUnitInArea( units[i], area ) == true then
				return true
			end
		end
		return false
	end
end

function AreUnitsNearPoint( units, x, y, r, all )
	local count = 0
	if #units == 0 then return false end
	if all == true then
		for i=1,#units do
			if not UnitIsRealyDead( units[i] ) then
				if IsUnitInArea( units[i], x,y,r ) == true then
					count = count + 1
				end
			end
		end
		if count == #units then return true
		else return false end
	else
		for i=1,#units do
			if not UnitIsRealyDead( units[i] ) then
				if IsUnitInArea( units[i], x,y,r ) == true then
					return true
				end
			end
		end
		return false
	end
end

function ChangeUnitListFaction(unitList, newFaction)
	for i=1, #unitList do 
		LuaSetCreepFaction(unitList[i], newFaction)
		LuaDebugTrace("[ChangeUnitListFaction]: unit "..unitList[i].." has faction "..newFaction)
	end
end

function PlayAnimationUnitList( unitList, play, loop )
	if unitList == nil then 
		LuaDebugTrace("ERROR: [ForceAnimationUnitList]. unitList is nil") 
		return
	end
	if play == true then
		for i=1, #unitList do LuaForceAnimation( unitList[i], "attack", loop ) end
	elseif play == false then
		for i=1, #unitList do LuaStopForcedAnimation( unitList[i] ) end
	else
		LuaDebugTrace("ERROR: [ForceAnimationUnitList]. Wrong parameter play")
	end
end

function SetAreaHealthful( areaName )
	LuaDebugTrace("STARTED: [SetAreaHealthful] for area "..areaName)
	local x,y,r = LuaGetScriptArea( areaName )
	local playerCreeps = LuaGetCreepsInArea( x, y, r, playerFactionFlag )
	local isUnderAttack = false
	while true do
		while #LuaGetCreepsInArea( x, y, r, enemyFactionFlag )	> 0 do SleepState() end
		WaitState(5)
		while #GetWoundedCreepsInArea( areaName ) > 0 do
			playerCreeps = LuaGetCreepsInArea( x, y, r, playerFactionFlag )
			isUnderAttack = false
			for i=1, #playerCreeps do
				if LuaIsUnitAttacked( playerCreeps[i] ) then 
					isUnderAttack = true
					break 
				end
			end
			if isUnderAttack then break end
			AddUnitListHealth( LuaGetCreepsInArea( x, y, r, playerFactionFlag ), 30 )
			WaitState(1)			
		end		
	end	
end

function GetWoundedCreepsInArea( areaName )
	local x,y,r = LuaGetScriptArea( areaName )
	local creeps = LuaGetCreepsInArea( x, y, r, playerFactionFlag )	
	local wounded = {}
	for i=1, #creeps do		
		if LuaUnitGetHealth( creeps[i] ) < LuaGetUnitStat( creeps[i], StatLife ) then
			table.insert( wounded, creeps[i] )
		end
	end	
	return wounded
end

-- WAITS ================================

function WaitForSpawnerUnitsDead( spawnerName )
	WaitForUnitListDead( GetSpawnerUnits( spawnerName ) )
end

function WaitWhileSomeoneIsAlive( unitList )
	LuaDebugTrace("STARTED: [WaitWhileSomeoneIsAlive]")
	PrintArray( unitList )
	local someoneIsAlive = true
	local dead, exist = false, false
	while someoneIsAlive do
		someoneIsAlive = false		
		for i=1, #unitList do
			dead, exist = LuaUnitIsDead( unitList[i] )
			if not dead and exist then
				someoneIsAlive = true
				break
			end
		end
		SleepState()
	end	
	LuaDebugTrace("FINISHED: [WaitWhileSomeoneIsAlive]")
end

function WaitForUnitsAreDead( unitList )
	while not UnitsAreDead( unitList ) do
		SleepState()
	end
end

function UnitsAreDead( unitList )
	local totalUnits = #unitList
	local dead, exist = false, false
	local killed
	
	killed = 0
	for i=1, #unitList do
		dead, exist = LuaUnitIsDead( unitList[i] )
		if dead or not exist or LuaGetUnitType( unitList[i] ) == UnitTypeSummon then
			killed = killed + 1
		end
	end
	if killed == totalUnits then
		return true		
	end
	return false
end

function SetUnitImmortal( unitName, enable )
	LuaDebugTrace("STARTED: [SetUnitImmortal] for unit "..unitName..". Mode is "..tostring(enable))
	local unitImmortalFlag = unitName.."_immortalFlag" 
	
	if enable == false then 
		immortalFlags[unitImmortalFlag] = false 
		LuaDebugTrace("DEBUG: [SetUnitImmortal]. Disabled for unit "..unitName)
		return
	end	
	
	LuaUnitAddFlag( unitName, ForbidDeath )	
	immortalFlags[unitImmortalFlag] = true
	
	local unitHealth = LuaUnitGetHealth( unitName )
	while immortalFlags[unitImmortalFlag] == true do		
		--LuaDebugTrace("DEBUG: [SetUnitImmortal]. unit "..unitName.." has "..unitHealth.." hp")
		while LuaUnitGetHealth( unitName ) >= unitHealth and immortalFlags[unitImmortalFlag] == true do SleepState() end
		--LuaDebugTrace("DEBUG: [SetUnitImmortal]. unit "..unitName.." takes damage. Restoring health")
		LuaSetUnitHealth( unitName, unitHealth )
		--DebugTrace("[SetUnitImmortal] health for unit "..unitName.." restored ")
		SleepState()
	end
	LuaUnitRemoveFlag( unitName, ForbidDeath )
	LuaDebugTrace("FINISHED: [SetUnitImmortal] for unit "..unitName)
end

function SetUnitListImmortal( unitList, enable )
	for i=1, #unitList do AddTriggerEnd( SetUnitImmortal, unitList[i], enable ) end
end

function WaitForUnitListDead( unitList )
	while #unitList~=0 do SleepState() end
end

function AIFollowSpawnerCreatures( follower, spawnerName )
	LuaDebugTrace("STARTED: [AIFollowSpawnerCreatures]")
	local units = GetSpawnerUnits( spawnerName )
	--LuaDebugTrace( "DEBUG: unit name is "..units[1] )
	while true do
		if #units ~= 0 then
			local unitName = units[#units]
			LuaHeroAIFollowHero( follower, unitName )			
			while UnitIsRealyDead( unitName ) == false do SleepState() end				
		else
			LuaDebugTrace("FINISHED: [AIFollowSpawnerCreatures]")
			return
		end
		SleepState()
	end	
end

function HeroRetreat( heroName, criticalHP, areaName, followUnits )
	LuaUnitAddFlag( heroName, ForbidDeath )
	LuaDebugTrace("STARTED: [HeroRetreat]")
	
	while LuaUnitGetHealth( heroName ) > criticalHP do SleepState() end
	
	LuaDebugTrace("DEBUG: [HeroRetreat] hero "..heroName.." takes critical damage")	
	LuaUnitAddFlag( heroName, ForbidTakeDamage )
	LuaHeroAIDisable( heroName )
	StartDialog_EnemyHeroWounded( heroName )
	LuaSetUnitStat( heroName, StatMoveSpeed, 100)
	--ForcedMoveToArea( {heroName}, areaName, 1)
	local areaX, areaY, areaR = LuaGetScriptArea( areaName )
	while not IsUnitInArea( heroName, areaName) do
		if LuaCanCreatureMoveTo( heroName, areaX, areaY, 0 ) then
			LuaCreatureMoveTo( heroName, areaX, areaY, 0 )
		else
			DebugTrace("[HeroRetreat] hero "..heroName.." can't reach area "..areaName..".")	
			LuaForceAnimation( heroName, "channeling", -1)
			LuaPlaceAttachedEffect( heroName.."teleportEffect", "teleport", heroName )
			WaitState(2)
			LuaCreatureTeleportTo( heroName, areaX, areaY )
			LuaStopForcedAnimation( heroName )
			SleepState()
			DebugTrace("[HeroRetreat] hero "..heroName.." teleported to area "..areaName)
			break
		end
		SleepState()
	end	
		
	LuaUnitRemoveFlag( heroName, ForbidTakeDamage )	
	LuaUnitRemoveFlag( heroName, ForbidDeath )
	LuaSetUnitStat( heroName, StatMoveSpeed, 56)
	LuaSetUnitHealth( heroName, 3000 )
	LuaCreatureHide( heroName, true )
	enemyHeroes[ heroName ].isHidden = true

	LuaDebugTrace("FINISHED: [HeroRetreat]")
end

function WaitForUnitInArea(unitName, areaName)
	LuaDebugTrace("WaitForUnitInArea STARTED")
	local x,y, radius = LuaGetScriptArea( areaName )
	if  type(unitName) == "string" then
		while DistanceUA( unitName, areaName ) > radius do SleepState() end
	elseif type(unitName) =="table" then		
		while true do
			for i=1, #unitName do 
				if DistanceUA( unitName[i], areaName ) < radius then return end
			end	
			SleepState()
		end
	end
	if  type(unitName) == "string" then
		LuaDebugTrace("TRACE: WaitForUnitInArea for area "..areaName.." and unit "..unitName.." FINISHED")
	end
end

function WaitForAllUnitsInArea( unitList, areaName )
	LuaDebugTrace("WaitForAllUnitsInArea STARTED")
	local x, y, radius = LuaGetScriptArea(areaName)
	local ux, uy = 0,0
	local allIn = false
	while not allIn do
		allIn = true
		for i=1,#unitList do
			ux, uy = LuaUnitGetPosition(unitList[i])				
			if math.sqrt(DistanceSquared(ux, uy, x, y)) > radius then 
				allIn = false;
				break;
			end
		end
		SleepState()
	end
	LuaDebugTrace("WaitForAllUnitsInArea: all "..#unitList.." units in area "..areaName)
	return
end

function WaitForUnitOutArea(unitName, areaName)
	LuaDebugTrace("WaitForUnitOutArea STARTED")
	local hx, hy = 0,0
	local x, y, radius = LuaGetScriptArea(areaName)
	repeat
		hx, hy = LuaUnitGetPosition(unitName)
		SleepState()	
	until math.sqrt(DistanceSquared(hx, hy, x, y)) > radius
	LuaDebugTrace("TRACE: WaitForUnitOutArea for area "..areaName.." and unit "..unitName.." FINISHED")
end

function WaitForUnitListInArea( unitList, areaName )
	LuaDebugTrace("WaitForUnitListInArea STARTED")
	local x, y, radius = LuaGetScriptArea(areaName)
	local ux, uy = 0,0
	while true do
		for i=1,#unitList do
			ux, uy = LuaUnitGetPosition(unitList[i])				
			if math.sqrt(DistanceSquared(ux, uy, x, y)) <= radius then 
				LuaDebugTrace("WaitForUnitListInArea: unit "..unitList[i].." has arrived in area "..areaName)
				return
			end
		end
		SleepState()
	end
end

function WaitForUnitNearUnit( units1, units2, distance)
	LuaDebugTrace("STARTED: [WaitForUnitNearUnit]")
    
    local unitTypes = {}
    
	local function checkUnitDead( unit )
        if unitTypes[unit] ~= UnitTypeHeroMale and unitTypes[unit] ~= UnitTypeHeroFemale then
            local dead = LuaUnitIsDead( unit )
            if dead then
                LuaDebugTrace("[WaitForUnitNearUnit] unit "..unit.." is dead. Exiting.");
            end
            return dead
        end
        return false
	end
    local function fillTypes( units )
        if type( units ) == "string" then
            unitTypes[units] = LuaGetUnitType(units)
        elseif type( units ) == "table" then
            for i=1, #units do
                unitTypes[units[i]] = LuaGetUnitType(units[i])
            end
        end
    end

	local function checkUnitsDead(u1,u2)
		return checkUnitDead( u1 ) or checkUnitDead( u2 );
	end
	
    fillTypes( units1 )
    fillTypes( units2 )
    
	if ( type( units1 ) == "string" and type( units2 ) == "string") then
		while true do
			if checkUnitsDead( units1, units2 ) then return end
			if DistanceUU( units1, units2) < distance then return	end
			SleepState()
		end
	elseif ( type( units1 ) == "table" and type( units2 ) == "string") then
		LuaDebugTrace("DEBUG: type table - string")
		while true do
			for i=1, #units1 do
				if checkUnitsDead( units1[i], units2 ) then return end
				if DistanceUU( units1[i], units2) < distance then return end
			end
			SleepState()
		end
	elseif ( type( units1 ) == "string" and type( units2 ) == "table") then
		while true do
			for i=1, #units2 do
				if checkUnitsDead( units1, units2[i] ) then return end
				if DistanceUU( units1, units2[i]) < distance then return	end
			end
			SleepState()
		end
	elseif ( type( units1 ) == "table" and type( units2 ) == "table") then
		while true do
			for i=1, #units2 do
				for j=1, #units1 do
					if checkUnitsDead( units1[j], units2[i] ) then return end
					if DistanceUU( units1[j], units2[i]) < distance then return end
				end
			end	
			SleepState()
		end
	end	
end

function IsUnitNearUnit( units1, units2, distance )
	if ( type( units1 ) == "string" and type( units2 ) == "string") then
		if DistanceUU( units1, units2) < distance then return true end
		return false
	elseif ( type( units1 ) == "table" and type( units2 ) == "string") then
		LuaDebugTrace("DEBUG: type table - string")
		for i=1, #units1 do
			if DistanceUU( units1[i], units2) < distance then return true end
		end	
		return false
	elseif ( type( units1 ) == "string" and type( units2 ) == "table") then		
		for i=1, #units2 do
			if DistanceUU( units1, units2[i]) < distance then return true end
		end
		return false
	elseif ( type( units1 ) == "table" and type( units2 ) == "table") then
		for i=1, #units2 do
			for j=1, #units1 do
				if DistanceUU( units1[j], units2[i]) < distance then return true end
			end
		end	
		return false
	end	
end

function IsUnitNearPoint( units, pointX, pointY, distance )
	if type( units ) == "string"  then
		if not UnitIsRealyDead( units ) then
			if DistanceUP( units, pointX, pointY ) < distance then
				return true
			end
		end
	elseif type( units ) == "table" then
		for i=1, #units do
			if not UnitIsRealyDead( units[i] ) then
				if DistanceUP( units[i], pointX, pointY ) < distance then
					return true
				end
			end
		end	
	end
	return false
end

function WaitForUnitNearPoint( units, pointX, pointY, distance )
	LuaDebugTrace("STARTED: [WaitForUnitNearPoint] for point "..pointX..", "..pointY.." and distance = "..distance)
	while not IsUnitNearPoint( units, pointX, pointY, distance ) do SleepState() end
	LuaDebugTrace("FINISHED: [WaitForUnitNearPoint] for point "..pointX..", "..pointY.." and distance = "..distance)
end

function GetNearestUnitToUnit( unitList, unit )
	local nearestUnit = unitList[1]
	local minDistance = DistanceUU( nearestUnit, unit )
	for i=2, #unitList do
		if DistanceUU( unitList[i], unit ) < minDistance then 
			minDistance = DistanceUU( unitList[i], unit ) 
			nearestUnit = unitList[i]
		end
	end
	return nearestUnit
end

function WaitForUnitIsVisible( units )
	WaitForUnitIsVisibleForTime( units, 1 )
end

function WaitForUnitIsVisibleForTime( _units, steps )
	LuaDebugTrace("STARTED: [WaitForUnitIsVisible]")
	local units;
	if type(_units) == "string" then
		units = {_units}
	else 
		units = _units
	end
	
	local stepsVisible = 0;
	while true do
		local hasVisible = false;
		for i=1, #units do
			if LuaIsUnitVisible( units[i] ) == true then 
				hasVisible = true
				break
			end
		end
		if hasVisible then 
			stepsVisible = stepsVisible + 1
		else 
			stepsVisible = 0
		end
			
		if  stepsVisible >= steps then return end
		SleepState()
	end
	LuaDebugTrace("FINISHED: [WaitForUnitIsVisible]")
end

function WaitForUnitHealth( unitName, value, relation )	
	local dead, exist = LuaUnitIsDead( unitName )
	if dear or not exist then 
		LuaDebugTrace("unit "..unitName.." is dead or not exist!")
		return
	end
	LuaDebugTrace("STARTED: [WaitForUnitStatValue] for unit "..unitName..", value = "..value..", relation is "..relation)
	if relation=="==" then
		repeat SleepState() until LuaUnitGetHealth( unitName ) == value 
	elseif relation == nil or relation == "<" then
		repeat SleepState() until LuaUnitGetHealth( unitName ) < value 		
	elseif relation == "<=" then
		repeat SleepState() until LuaUnitGetHealth( unitName ) <= value 
	elseif relation == ">" then
		repeat SleepState() until LuaUnitGetHealth( unitName ) > value 
	elseif relation == ">=" then
		repeat SleepState() until LuaUnitGetHealth( unitName ) >= value 
	else
		LuaDebugTrace("ERROR: [WaitForUnitStatValue] unknown value for parameter relation")
	end
	LuaDebugTrace("FINISHED: [WaitForUnitStatValue]")
end

function IsHeroAlive( heroName )
    return not LuaUnitIsDead( heroName )
end

function StartUnitFollowUnit( follower, leader )
	LuaDebugTrace("STARTED: StartUnitFollowUnit")
	local flagName = tostring(follower)..tostring(leader)
	local FOLLOW_DISTANCE=7
	local followflags = GetGlobalVar("PvECommon_Followflags")
	--LuaDebugTrace("DEBUG: flagName = "..flagName)
	table.insert(followflags, flagName)
	while IsValueExists( flagName, followflags ) == true do
		--LuaDebugTrace("DEBUG while 1 in")
		while DistanceUU( follower, leader ) > FOLLOW_DISTANCE and IsValueExists( flagName, followflags ) == true do
			local x,y  = LuaUnitGetPosition( leader )
			--LuaDebugTrace("x,y = "..x..", "..y)
			LuaCreatureMoveTo( follower, x, y, 0 )
			--LuaDebugTrace("DEBUG: creature moved")
			SleepState()
		end
		--LuaDebugTrace("DEBUG: destination reached")
		while DistanceUU( follower, leader ) <= FOLLOW_DISTANCE and IsValueExists( flagName, followflags ) == true do
			SleepState() 
		end
		--LuaDebugTrace("DEBUG: start follow again")
		SleepState()
	end
	LuaDebugTrace("FINISHED: StartUnitFollowUnit for pair "..flagName)
end

function FinishUnitFollowUnit( follower, leader )
	local flagName = tostring(follower)..tostring(leader)
	local followflags = GetGlobalVar("PvECommon_Followflags")
	for i=1, #followflags do
		if followflags[i]==flagName then
			table.remove(followflags, i)
			return
		end
	end
	LuaDebugTrace("ERROR: no such follower-leader pair as "..follower..leader.." in the followflags list")
end

function StartUnitListFollowUnit( unitList, leader )
	for i=1, #unitList do
		AddTriggerEnd(StartUnitFollowUnit, unitList[i], leader )
	end
end

function FinishUnitListFollowUnit( unitList, leader )
	for i=1, #unitList do
		FinishUnitFollowUnit( unitList[i], leader )
	end
end

function ForcedMoveToArea(unitList, areaName, delay)
	LuaDebugTrace("ForcedMoveToArea: STARTED")
	local x,y,radius = LuaGetScriptArea(areaName)
	while AreUnitsDead(unitList)==false do
		MoveUnitsToPoint(unitList, x, y, 0)
		for i=1, #unitList do
			if DistanceUA(unitList[i], areaName) < radius then
				--LuaDebugTrace("ForcedMoveToArea: Destination reached!")
				return
			end
		end
		WaitState(delay)		
		--LuaDebugTrace("ForcedMoveToArea: WAIT")
	end
	LuaDebugTrace("WARNING! ForcedMoveToArea: All units are dead")
end

function ForcedMoveToPosition(unitList, x, y, radius, delay)
	LuaDebugTrace("ForcedMoveToArea: STARTED")
	while AreUnitsDead(unitList)==false do
		MoveUnitsToPoint(unitList, x, y, 0)
		for i=1, #unitList do
			if DistanceUP(unitList[i], x, y) < radius then
				LuaDebugTrace("ForcedMoveToArea: Destination reached!")
				return
			end
		end
		WaitState(delay)		
		--LuaDebugTrace("ForcedMoveToArea: WAIT")
	end
	LuaDebugTrace("WARNING! ForcedMoveToArea: All units are dead")
end


function MoveUnitsToPoint(unitList, x, y, r)
	--LuaDebugTrace("MoveUnitsToPoint: STARTED")
	if #unitList == 0 then 
		LuaDebugTrace("ERROR: MoveUnitsToPoint: no units in list "..unitsList)
		return
	end
	for i=1, #unitList do
		LuaCreatureMoveTo(unitList[i], x, y, 0)		
	end
end


function MoveSpawnerCreatures(spawnerName, x, y, r)
	LuaDebugTrace("TRACE: MoveSpawnerCreatures STARTED!")
	--LuaDebugTrace("TRACE: X = "..x.."; Y = "..y.."; R = "..r)
	local units = GetSpawnerUnits( spawnerName )
	for i=1, #units do
		LuaCreatureMoveTo(unit[i], x, y, r)
	end
	--LuaDebugTrace("FINISHED: MoveSpawnerCreatures STARTED!")	
end

function DistanceUA(unitName, areaName)
	local x,y,radius = LuaGetScriptArea(areaName)
	local ux,uy = LuaUnitGetPosition(unitName)
	return math.sqrt(DistanceSquared(ux,uy,x,y))
end

function DistanceUU(unitName1, unitName2)
	if type( unitName1 ) == "string" then
		local ux1,uy1 = LuaUnitGetPosition(unitName1)
		local ux2,uy2 = LuaUnitGetPosition(unitName2)
		return math.sqrt(DistanceSquared(ux1,uy1,ux2,uy2))
	elseif type( unitName1 ) == "table" then
		local distances = {}
		for i=1, #unitName1 do distances[i] = DistanceUU( unitName1[i], unitName2 )	end
		return MinInArray( distances )
	end
end

function MinInArray( array )
	local minValue = array[1]
	for i=2, #array do
		if array[i] < minValue then minValue = array[i] end
	end
	return minValue
end

function MaxInArray( array )
	local maxValue = array[1]
	for i=2, #array do
		if array[i] > maxValue then maxValue = array[i] end
	end
	return maxValue
end

function DistanceUP(unitName, x, y)	
	local ux, uy = LuaUnitGetPosition( unitName )
	return math.sqrt(DistanceSquared( ux, uy, x, y))
end

function DistancePP(x1, y1, x2, y2)		
	return math.sqrt(DistanceSquared( x1, y1, x2, y2))
end

function UnitsTalking( unit1, unit2, rotateTime )	
	if type(unit1) == "string" then 
		LuaUnitClearStates( unit1 )
		LuaUnitClearStates( unit2 )
		local x1,y1 = LuaUnitGetPosition( unit1 )
		local x2,y2 = LuaUnitGetPosition( unit2 )		
		LuaRotateHero( unit2, x1, y1, rotateTime, false )
		LuaRotateHero( unit1, x2, y2, rotateTime, false )
		LuaDebugTrace("[UnitsTalking]  unit "..unit1.." and "..unit2.." are talking")
		LuaDebugTrace("[UnitsTalking] unit1 position x, y = "..x1..", "..y1)
		LuaDebugTrace("[UnitsTalking] unit2 position x, y = "..x2..", "..y2)
	elseif type( unit1) == table then		
		local rotTime = unit2
		local averageX, averageY = 0, 0
		local x,y = 0, 0
		local units = GetAliveUnits( unit1 )
		for i=1, #units do
			LuaUnitClearStates( units[i] )
		end
		for i=1, #units do
			x, y = LuaUnitGetPosition( units[i] )
			averageX = averageX + x
			averageY = averageY + y
		end
		averageX = averageX / #units
		averageY = averageY / #units
		for i=1, #units do
			LuaRotateHero( units[i], averageX, averageY, rotTime, false )
		end
	end
end

function GetAliveUnits( unitList )	
	local dead, found = false, true
	aliveUnits = {}
	for i=1, #unitList do
		dead, found = LuaUnitIsDead( unitList[i] )
		if not dead and found then
			table.insert( aliveUnits, unitList[i] )
		end
	end
	return aliveUnits
end

function WaitForPhraseFinished( phraseID )
	while LuaIsPhraseFinished( phraseID ) == false do SleepState() end
end

-- SET GET UNITS ==============================
manualHealthLevelUnits = {}

function SetUnitMinHealth( unitName, level, enable )
	local dead, found = LuaUnitIsDead( unitName )
	if found and not dead then
		LuaUnitAddFlag( unitName, ForbidDeath )
		if enable == true then
			manualHealthLevelUnits[ unitName ] = true
			while manualHealthLevelUnits[ unitName ] == true do
				if LuaUnitGetHealth( unitName ) < level then
					LuaSetUnitHealth( unitName, level )
				end
				SleepState()
			end
			LuaUnitRemoveFlag( unitName, ForbidDeath )
			DebugTrace("[SetUnitMinHealth] unit "..unitName.." has not min health level and he is pathetic mortal creature now")
			return
		elseif enable == false then
			manualHealthLevelUnits[ unitName ] = false
			return
		end
	else
		LuaDebugTrace("ERROR: [SetUnitMinHealth] unit "..unitName.." is not found or dead.")
	end
end

function LevelUpHero( heroName, level )
	if level > 36 then level = 36 end
	if level > LuaHeroGetLevel( heroName ) then
		local n=0	
		for i=0, 5 do
			for j = 0, 5 do
				if not LuaHeroIsTalentActivated( heroName, i, j ) then
					LuaHeroActivateTalent( heroName, i, j, false )					
				end
				n = n + 1
				if n == level then 
					return
				end
			end
		end
	else
		LuaDebugTrace("WARNING! [LevelUpHero] Hero "..heroName.." already has level greater than "..level)
	end
end

function LevelUpHero2( heroName, level )
	DebugTrace("STARTED: [LevelUpHero2] for hero "..heroName.." with level "..LuaHeroGetLevel( heroName ).." and level to up "..level)
	if level > 36 then level = 36 end
	if level > LuaHeroGetLevel( heroName ) then
		SetGlobalVar("enemyHeroLevel", level)
		local n = LuaHeroGetLevel( heroName )
		for i=0, 5 do
			for j = 0, 5 do
				if not LuaHeroIsTalentActivated( heroName, i, j ) then
					LuaHeroActivateTalent( heroName, i, j, false )			
					n = n + 1
					if n == level then 						
						return
					end
				end
			end
		end
	else
		LuaDebugTrace("WARNING! [LevelUpHero] Hero "..heroName.." already has level greater than "..level)
	end
end

function RestoreUnitHealth( unitName )
	local dead, found = LuaUnitIsDead( unitName )
	if not dead and found then 
		if LuaUnitGetHealth( unitName ) < LuaGetUnitStat( unitName, StatLife ) then
			LuaSetUnitHealth( unitName, LuaGetUnitStat( unitName, StatLife ) )
			DebugTrace("[RefillUnitHealth] health for unit "..unitName.." has been restored")
		end
	else
		LuaDebugTrace("WARNING! [RestoreUnitHealth] unit "..unitName.." is not found or dead! Can't restore health!")
	end
end

function UnitIsRealyDead( unitName )
	if type( unitName ) == "string" then
		local dead, exist = LuaUnitIsDead( unitName )
		if exist == false then LuaDebugTrace("ERROR: UnitIsRealyDead, no such unit with name "..unitName.." on the map") return true end
		
		return dead or LuaGetUnitType( unitName ) == UnitTypeSummon
	elseif type( unitName ) == "table" then
		local deadCount = 0
		for i=1, #unitName do
			if UnitIsRealyDead( unitName[i] ) then
				deadCount = deadCount + 1
			end
		end
		if deadCount == #unitName then
			return true
		else 
			return false
		end
	end
end

function SetUnitListHealth( unitList, health, isRandom, deviation)
	for i=1, #unitList do
		local hp = health
		if isRandom == true then
			hp = health + math.random(-deviation, deviation)			
		end
		LuaSetUnitHealth( unitList[i], hp)
	end
end

function AddUnitListHealth( unitList, health, isRandom, deviation )
	LuaDebugTrace("STARTED: [AddUnitListHealth]")
	for i=1, #unitList do
		local hp = health
		if isRandom == true then
			hp = health + math.random(-deviation, deviation)			
		end
		LuaSetUnitHealth( unitList[i], LuaUnitGetHealth(unitList[i]) + hp)
	end
	LuaDebugTrace("FINISHED: [AddUnitListHealth]")
end

function SetUnitsFlag(units, flag, enable, isHero)
	if units == nil then 
		LuaDebugTrace("ERROR: [UnitListClearStates] unitList is nil") 
		return
	end
	local dead, found	
	if enable==true then
		for i=1, #units do 
			dead, found = LuaUnitIsDead( units[i] )
			if isHero==true then
				if found then
					DebugTrace("[SetUnitsFlag] add flag "..flag.." for unit "..units[i])
					LuaUnitAddFlag(units[i], flag)				
				else
					DebugTrace("WARNING: [SetUnitsFlag] unit "..units[i].." doesnt exist. Can't add flag "..flag)
				end
			else
				if found and not dead then
					DebugTrace("[SetUnitsFlag] add flag "..flag.." for unit "..units[i])
					LuaUnitAddFlag(units[i], flag)				
				else
					DebugTrace("WARNING: [SetUnitsFlag] unit "..units[i].." doesnt exist. Can't add flag "..flag)
				end
			end
		end
	else
		for i=1, #units do 
			dead, found = LuaUnitIsDead( units[i] )
			if isHero==true then
				if found then
					DebugTrace("[SetUnitsFlag] remove flag "..flag.." for unit "..units[i])			
					LuaUnitRemoveFlag(units[i], flag)			
				else
					DebugTrace("WARNING: [SetUnitsFlag] unit "..units[i].." doesnt exist at all. Can't remove flag "..flag)
				end
			else 
				if found and not dead then
					DebugTrace("[SetUnitsFlag] remove flag "..flag.." for unit "..units[i])			
					LuaUnitRemoveFlag(units[i], flag)			
				else
					DebugTrace("WARNING: [SetUnitsFlag] unit "..units[i].." doesnt exist at all. Can't remove flag "..flag)
				end			
			end
		end
	end	
end

function SetUnitsFlagList(units, flags, enable, isHero )
	for i=1, #flags do SetUnitsFlag(units, flags[i], enable, isHero) end
	LuaDebugTrace("DEBUG: SetUnitsFlagList FINISHED")
end

function GetNearestPointToPointList( pointX, pointY, pointList )
	local distances = {}
	local x, y = pointList[1].x, pointList[1].y
	local name = "undefined"
	local path = "undefined"
	local minDistance = DistancePP( pointX, pointY, x, y )
	if pointList[1].name ~= nil then name = pointList[1].name end
	if pointList[1].path ~= nil then path = pointList[1].path end
	for i=2, #pointList do		
		if DistancePP( pointX, pointY, pointList[i].x, pointList[i].y ) < minDistance then
			x, y = pointList[i].x, pointList[i].y
			if pointList[i].name ~= nil then name = pointList[i].name end
			if pointList[i].path ~= nil then path = pointList[i].path end
			minDistance = DistancePP( pointX, pointY, pointList[i].x, pointList[i].y )
		end		
	end	
	if pointList[1].name ~= nil and pointList[1].path ~= nil then
		return x, y, name, path
	elseif pointList[1].name ~= nil then 
		return x, y, name
	else
		return x, y
	end
end

function GetNearestPointToUnit( pointList, unitName )
	local unitX, unitY = LuaUnitGetPosition( unitName )
	local x, y = 0, 0
	local destinations = {}
	for i=1, #pointList do
		x, y = pointList[i][1], pointList[i][1]		
		if pointList[i][3] ~= nil then
			table.insert( destinations, {x, y, DistanceUP( unitName, x, y ), pointList[i][3] } )
		else
			table.insert( destinations, {x, y, DistanceUP( unitName, x, y ) } )
		end
	end
	local nearestPointX, nearestPointY, nearestDistance = destinations[1][1], destinations[1][2], destinations[1][3]
	if destinations[1][4] ~= nil then
		nearestPointName = destinations[1][4]
	end
	for i=1, #destinations do
		if destinations[i][3] < nearestDistance then
			nearestPointX, nearestPointY, nearestDistance = destinations[i][1], destinations[i][2], destinations[i][3]
			if nearestPointName ~= nil then
				nearestPointName = destinations[i][4]
			end
		end
	end
	if nearestPointName ~= nil then
		return nearestPointX, nearestPointY, nearestPointName
	else
		return nearestPointX, nearestPointY
	end
end

function GetNearestUnit( x, y, unitList )
	if unitList == nil then 
		LuaDebugTrace("ERROR: [GetNearestUnit] unitList is nil")
		return nil
	end
	if #unitList == 0 then 
		LuaDebugTrace("WARNING: [GetNearestUnit] unitList is empty") 
		return nil
	end
	local nearestUnit = unitList[1]
	local nearestDistance = DistanceUP( unitList[1], x, y)
	for i=2, #unitList do
		if DistanceUP( unitList[i], x, y ) < nearestDistance and DistanceUP( unitList[i], x, y ) > 0.1 then
			nearestDistance = DistanceUP( unitList[i], x, y )
			nearestUnit = unitList[i]
		end
	end
	return nearestUnit
end

function ExtractNearestUnit( x, y, unitList ) -- Find nearest to (x,y) unit, remove it from unitList and return it
	local minDistanceTolerance = 0.1
	if unitList == nil then 
		LuaDebugTrace("ERROR: [ExtractNearestUnit] unitList is nil")
		return nil
	end
	if #unitList == 0 then 
		LuaDebugTrace("WARNING: [ExtractNearestUnit] unitList is empty") 
		return nil
	end
	local nearestUnit = unitList[1]
    local nearestUnitIndex = 1
	local nearestDistance = DistanceUP( unitList[1], x, y)
	for i=2, #unitList do
		if DistanceUP( unitList[i], x, y ) < nearestDistance and DistanceUP( unitList[i], x, y ) > minDistanceTolerance then
			nearestDistance = DistanceUP( unitList[i], x, y )
			nearestUnit = unitList[i]
            nearestUnitIndex = i
		end
	end
    table.remove( unitList, nearestUnitIndex )
	return nearestUnit
end

function GetNearestUnitsArray( x, y, unitList, count ) --Функция работает неправильно!
	LuaDebugTrace("STARTED: [GetNearestUnitsArray]")
	if unitList == nil then 
		LuaDebugTrace("ERROR: [GetNearestUnitsArray] unitList is nil")
		return nil
	end
	if #unitList == 0 then 
		LuaDebugTrace("WARNING: [GetNearestUnitsArray] unitList is empty") 
		return nil
	end
	if count == nil then 
		LuaDebugTrace("ERROR: [GetNearestUnitsArray] parameter count is missing.") 
		return 
	end
	if count > #unitList then
		LuaDebugTrace("ERROR: [GetNearestUnitsArray] parameter count is greater than unitList length.") 
		return 
	end
	local nearestUnits = CopyArray( unitList )
	PrintArray( nearestUnits )
	local distances = {}
	for i=1, #nearestUnits do
		distances[ nearestUnits[i] ] = DistanceUP( nearestUnits[i], x, y )
	end
	table.sort( distances )
	PrintArray( distances )
	local nearestNUnits = {}
	local n = 0
	for unitName, distance in pairs( distances ) do
		if n > count then break end
		table.insert( nearestNUnits, unitName )
		n = n + 1
	end
	PrintArray( nearestNUnits )
	return nearestNUnits
end

function DebugTrace( str )
	if debageTraceOn == true then
		LuaDebugTrace("DEBUG: "..str)
	end
end

function UnitListClearStates(unitList)
	if unitList == nil then 
		LuaDebugTrace("ERROR: [UnitListClearStates] unitList is nil") 
		return
	end
	for i=1, #unitList do LuaUnitClearStates(unitList[i]) end
	LuaDebugTrace("DEBUG: UnitListClearStates FINISHED")
end

function IsUnitAttackedByObject( unit, object )
	local isAttacked = false
	if type(unit) == "string" and type(object) == "string" then
		return LuaIsUnitAttackedByObject( unit, object )
	elseif type(unit) == "string" and type( object ) == "table" then
		for i=1, #object do
			if LuaIsUnitAttackedByObject( unit, object[i] )==true then
				return true
			end
		end
		return false
	elseif type(unit) == "table" and type( object ) == "table" then
		for i=1, #object do
			for j=1, #unit do
				if LuaIsUnitAttackedByObject( unit[j], object[i] )==true then
					return true
				end
			end
		end	
		return false
	elseif type(unit) == "table" and type( object ) == "string" then
		for j=1, #unit do
			if LuaIsUnitAttackedByObject( unit[j], object )==true then
				return true
			end
		end	
		return false
	end
	LuaDebugTrace("ERROR: [IsUnitAttackedByObject] Wrong parameters!")
end

function IsUnitAttacked( unit )
	local isAttacked = false
	if type(unit) == "string" then
		return LuaIsUnitAttacked( unit )
	elseif type(unit) == "table" then
		for i=1, #unit do
			if LuaIsUnitAttacked( unit[i] )==true then
				return true
			end
		end
		return false
	end
	LuaDebugTrace("ERROR: [IsUnitAttackedByObject] Wrong parameters!")
end

function WaitForUnitTakesDamage( unitName, damage )
	local initHealth = LuaUnitGetHealth( unitName )	
	local dmg = 0
	if damage ~= nil then
		dmg = damage
	else
		dmg = 0
	end
	while true do
		if LuaUnitGetHealth( unitName ) < initHealth - dmg then break end
		if LuaUnitGetHealth( unitName ) > initHealth then initHealth = LuaUnitGetHealth( unitName ) end
		SleepState()
	end
end


function CreatureListHide(creatures, enable)
	for i=1,#creatures do LuaCreatureHide(creatures[i], enable) end
end

-- ARRAYS ==============================================

function IsValueExists( value, array )
	for i=1, #array do
		if array[i]==value then return true	end
	end
	return false
end

function IsValueExists2( value, array )
	for i, v in pairs(array) do
		if v==value then return true end
	end
	return false
end

function GetValueIndexByName(name, array)
	for i=1, #array do
		if array[i].name == name then
			return i
		end
	end
	LuaDebugTrace("WARNING: GetValueIndexByName no such value with name "..name.." returned value -1")
	return -1
end

function CopyArray( arrayFrom )
	local arrayTo = {}
	for i=1, #arrayFrom do
		table.insert( arrayTo, arrayFrom[i] )
	end
	return arrayTo
end

function CopyArray2( arrayFrom )
	local arrayTo = {}
	for i, v in pairs( arrayFrom ) do
		arrayTo[ i ] = v
	end
	return arrayTo
end

function RemoveRandomElementsFromArray( elementsCount, arrayFrom )
	if elementsCount > #arrayFrom then 
		LuaDebugTrace("ERROR: [RemoveRandomElementsFromArray] Attempt to remove "..elementsCount.." elements from array with length "..#arrayFrom)
		return nil
	end
	local array = CopyArray( arrayFrom )
	for i=1, elementsCount do
		table.remove( array, LuaRandom(1, #array) )
	end
	return array
end

function RandomIntArray( minValue, maxValue, length, hasRepeats )
	local array = {}
	for i=1, length do
		array[i] = LuaRandom( minValue, maxValue )
	end
end

function ShuffleArray( arr )
	local array = CopyArray( arr )
    table.sort( array )
	--PrintArray( array )
	local j = #array
	local k = 1
	local tmp
	while j > 1 do
		k = LuaRandom( 1, j-1 )
		tmp = array[j]
		array[j] = array[k]
		array[k] = tmp
		j = j - 1
	end
	--PrintArray( array )
	return array
end

function PrintArray( array )
	LuaDebugTrace("Array: ")
	for i, v in pairs( array ) do 
		LuaDebugTrace("DEBUG: array["..i.."] = "..tostring(v)) 
	end
end

function PrintTable( tbl, indent)
    indent = indent or 0;

    local keys = {};
    for k in pairs(tbl) do
        table.insert( keys, k );
    end
    
    table.sort(keys, 
        function(a, b)
            local ta, tb = type(a), type(b);
            if (ta ~= tb) then
                return ta < tb;
            else
                return a < b;
            end
        end
    );
    
    LuaDebugTrace( string.rep('  ', indent)..'{' );
    
    indent = indent + 1;
    for k, v in pairs(tbl) do

        local key = k;
        if (type(key) == 'string') then
            if not (string.match(key, '^[A-Za-z_][0-9A-Za-z_]*$')) then
                key = "['"..key.."']";
            end
        elseif (type(key) == 'number') then
            key = "["..key.."]";
        end

        if (type(v) == 'table') then
          if (next(v)) then
            LuaDebugTrace( string.rep('  ', indent)..tostring(key).." =" );
            PrintTable(v, indent);
          else
            LuaDebugTrace(string.rep('  ', indent)..tostring(key).."= {},");
          end 
        elseif (type(v) == 'string') then
            LuaDebugTrace(string.rep('  ', indent)..tostring(key).." = '"..v.."',");
        else
            LuaDebugTrace(string.rep('  ', indent)..tostring(key).." = '"..tostring(v).."',");
        end
  end
  indent = indent - 1;
  LuaDebugTrace( string.rep('  ', indent)..'}' );
end

function ConcatArrays( array1, array2 )
	local array = {}
	array = CopyArray( array1 )
	for i=1, #array2 do
		table.insert( array, array2[i] )
	end
	return array
end

function ArrayRemoveElement( array, element )
	local arr = {}
	for i,v in pairs( array ) do
		if v ~= element then
			table.insert( arr, v )
		end
	end
	return arr
end

function table.removekey(table, key)
    local element = table[key]
    table[key] = nil
    return element
end

function NumberToCaseString( nmbr, case, gender )
	local str = "колбасина"
	if case ==  "accusative" and gender =="female" then
		if nmbr == 1 then str = "первую"
		elseif nmbr == 2 then str = "вторую"
		elseif nmbr == 3 then str = "третью"
		elseif nmbr == 4 then str = "четвертую"
		elseif nmbr == 5 then str = "пятую"
		elseif nmbr == 6 then str = "шестую"
		elseif nmbr == 7 then str = "седьмую"
		elseif nmbr == 8 then str = "восьмую"
		elseif nmbr == 9 then str = "девятую"
		elseif nmbr == 10 then str = "десятую"
		elseif nmbr == 11 then str = "одиннадцатую"
		elseif nmbr == 12 then str = "двенадцатую"
		elseif nmbr == 13 then str = "тринадцатую"
		elseif nmbr == 14 then str = "четырнадцатую"
		elseif nmbr == 15 then str = "пятнадцатую"
		elseif nmbr == 16 then str = "шестнадцатую"
		elseif nmbr == 17 then str = "семнадцатую"
		elseif nmbr == 18 then str = "восемнадцатую"
		elseif nmbr == 19 then str = "девятнадцатую"
		elseif nmbr == 20 then str = "двадцатую"
		end
	end
	return str
end

function SetGlobalVarWhenTimeIsUp( varName, Time, value)
	LuaDebugTrace("STARTED: [SetGlobalVarWhenTimeIsUp] for "..varName..", Time = "..Time.." and value = "..tostring(value))
	local timer = 0
	while timer < Time do
		timer = timer + GetStepLengthInSeconds()
		SleepState()
	end
	SetGlobalVar( varName, value )
	DebugTrace("[SetGlobalVarWhenTimeIsUp]: "..varName.." = "..tostring(value))
end