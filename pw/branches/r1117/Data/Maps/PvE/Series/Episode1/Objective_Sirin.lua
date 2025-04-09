
--global var
isTameQuestAdded = false

function SirinQuest()
	boarMasterSpawner = "boarMaster"..factionName
	SpawnerSpawn( boarMasterSpawner, factionPlayer )	
	boarMaster = GetSpawnerUnits( boarMasterSpawner )[1]
	
	LuaUnitAddFlag( boarMaster, ForbidMove )
	LuaUnitAddFlag( boarMaster, ForbidTakeDamage )
	LuaUnitApplyApplicator( boarMaster, "quest_questionYellow" )
    LuaSetCreepWarfogFaction( boarMaster, factionEnemyCrap )
	
	while not IsUnitInArea( mainHero, "boarMasterArea" ) or not LuaIsUnitVisible( boarMaster) do SleepState() end
    LuaSetCreepWarfogFaction( boarMaster, factionPlayer )
	LuaUnitRemoveFlag( boarMaster, ForbidTakeDamage )
	
	if UnitIsRealyDead( boarMaster ) == true then return end
	
	StartDialog_boarMasterQuest()
	LuaUnitRemoveApplicator( boarMaster, "quest_questionYellow" )
	LuaUnitApplyApplicator( boarMaster, "quest_questionGrey" )
	AddQuest( "boarMasterQuest", false, false )
	
	SpawnerSpawn( "Sirin", factionEnemy, true )
	for i=1, #GetSpawnerUnits("Sirin") do
		LuaApplyPassiveAbility( GetSpawnerUnits("Sirin")[i], "CantDeath" )
		LuaUnitAddFlag( GetSpawnerUnits("Sirin")[i], ForbidDeath )
	end
	boars = "boars"..factionName
	SpawnerSpawn( boars, factionPlayer )
	SetUnitsFlagList( GetSpawnerUnits( boars ), { ForbidAutoAttack, ForbidInteract, ForbidPlayerControl, ForbidAttack, ForbidDeath, ForbidSelectTarget, ForbidTakeDamage, ForbidMove }, true )
	
	local oneSirinAlive = false
	local sirins = GetSpawnerUnits("Sirin") 
	local aliveSirins = #sirins
	
	while aliveSirins ~= 1 do 
		if isMissonFinished then 
			CompleteQuest("boarMasterQuest") 
			return
		end
		sirins = GetSpawnerUnits("Sirin") 
		for i=1, #sirins do
			if not UnitIsRealyDead( sirins[i] ) then
				if LuaUnitGetHealth( sirins[i] ) < 2 then
					if aliveSirins == 1 then break end
					LuaUnitRemoveFlag( sirins[i], ForbidDeath )		
					DebugTrace("[SirinQuest] Unit "..sirins[i].." has been killed")
					LuaKillUnit( sirins[i] )
					aliveSirins = aliveSirins - 1				
				end
			end
		end
		SleepState() 
	end

	sirin = GetSpawnerUnits("Sirin")[1]
	DebugTrace("[SirinQuest] Sirin has name "..sirin)
	LuaUnitRemoveFlag( sirin, ForbidDeath )
	LuaSetUnitStat( sirin, StatMoveSpeed, LuaGetUnitStat( mainHero, StatMoveSpeed ) ) 
	
	AddTriggerEnd( SirinTreachery )
	SirinFollowHero() --ждем, пока Сирин приведут на базу или убьют
    DebugTrace("[SirinQuest] SirinFollowHero finished" )
	if isTameQuestAdded then CompleteQuest("tameSirin") end	
    isTameQuestAdded = true -- квест про возвращение на базу выдавать уже не нужно
end



function SirinTreachery()
	LuaUnitAddFlag( sirin, ForbidDeath )
	local encounter = 0
	isTameQuestAdded = false
	while true do		
		while UnitIsRealyDead( sirin ) == false do
			if LuaUnitGetHealth( sirin ) < 100 or LuaGetUnitFaction( sirin )~=factionEnemy then				
				break
			end	
			SleepState()
		end
		if UnitIsRealyDead( sirin ) == true then return end
		if isMissonFinished then 
			CompleteQuest("boarMasterQuest") 
			return
		end
		LuaApplyPassiveAbility ( sirin, "dispell")
		if encounter == 0 then
			StartDialog_SirinCaptured()
			--AddQuest( "tameSirin" )
			AddTriggerEnd( BoarMasterFriendsReleased )			
		elseif encounter == 1 then
			StartDialog_SirinAskMercy()			
			LuaShowMessageBox("MsgBoxHeader_spareSirin", "MsgBoxDescription_spareSirin")
			LuaSetPause(true)
			while LuaGetMessageBoxResult() == MSGBOX_NOT_CLOSED do 	SleepState() end
			LuaSetPause(false)
			if LuaGetMessageBoxResult() == MSGBOX_NO then 
				LuaUnitRemoveFlag( sirin, ForbidDeath )
				DebugTrace("MSGBOX_NO")
				return 
			else
                if not isTameQuestAdded then -- если 
                    AddQuest( "tameSirin", false, false )	
                    isTameQuestAdded = true
                end
			end
			DebugTrace("MSGBOX_YES")
		elseif encounter == 2 then
            if isTameQuestAdded then CompleteQuest("tameSirin") end	
			LuaUnitRemoveFlag( sirin, ForbidDeath )
			return 
		end
		encounter = encounter + 1
		
		LuaSetCreepFaction( sirin, factionPlayer )
		LuaSetUnitHealth( sirin, 300 )
		LuaUnitRemoveFlag( sirin, ForbidDeath )
		
		for i=1, 40 do -- ждем 40 секунд, если Сирин помирает, выходим. После этого сирин снова может предать.
			if UnitIsRealyDead(sirin) == true then 
				if isTameQuestAdded then CompleteQuest("tameSirin") end				
				return 
			end
			WaitState(1)
		end
        LuaDebugTrace( "[SirinTreachery]. Sirin ready to betray" )
				
		while true do			
			if UnitIsRealyDead(sirin) == true then -- если Сирин помер, выходим из функции
				if isTameQuestAdded then CompleteQuest("tameSirin") end
				return
			end
			local sirinX, sirinY = LuaUnitGetPosition( sirin )
			if LuaIsUnitAttacked( sirin ) == true and #LuaGetCreepsInArea( sirinX, sirinY, 6, enemyFactionFlag ) > 0 then --Сирин предает, если атакован и рядом есть вражеские крипы
				DebugTrace("[SirinTreachery]. Sirin betrays player. Released by enemy")				
				break
			end
			if UnitIsRealyDead( mainHero )== true and IsUnitInArea( sirin, "ruinedCastle" )==false then --Сирин предает, если главный герой помер, но дело происходит не на базе
				DebugTrace("[SirinTreachery]. Sirin betrays player. Main hero is dead")
				break
			end
			SleepState()
		end
		if endIsNear then return end
		StartDialog_SirinBetraysPlayer()
		
		LuaSetCreepFaction( sirin, factionEnemy )		
		LuaUnitAddFlag( sirin, ForbidDeath )
		
		SleepState()		
	end
end

function SirinFollowHero(  )
	LuaDebugTrace("STARTED: [SirinFollowHero]")
	local targetX, targetY = LuaUnitGetPosition( mainHero )
	DebugTrace("[SirinFollowHero]. hero "..mainHero.." position. x = "..targetX..", y = "..targetY)
	
	while true do
		while true  do
			if UnitIsRealyDead( sirin )==true then return end
			if LuaGetUnitFaction( sirin ) ~= factionPlayer or IsUnitInArea( sirin, "centerHealthArea")==true then break end			
			if DistanceUU( mainHero, sirin ) > 5 then 
				targetX, targetY = LuaUnitGetPosition( mainHero )
				LuaCreatureMoveTo( sirin, targetX + math.random( -2,2 ), targetY + math.random( -2, 2 ), 0 )
			end
			SleepState(3)
		end					
		if IsUnitInArea(sirin, "centerHealthArea") == true then
			local areaX, areaY, radius = LuaGetScriptArea( "centerHealthArea" )
			LuaCreatureMoveTo( sirin, areaX, areaY, 2 )
			StartDialog_SirinAtBase()
			LuaSetCreepBasePlace( sirin, areaX, areaY )
			return
		else 
			while LuaGetUnitFaction(sirin) == factionEnemy do 
				if UnitIsRealyDead( sirin )==true then return end 
				SleepState() 
			end
		end		
		SleepState()		
	end
end

function BoarMasterFriendsReleased()	
	for i=1, #GetSpawnerUnits( boars ) do
		LuaForceAnimation( GetSpawnerUnits( boars )[i], "happy", 1 )
	end
	WaitState(3)
	SetUnitsFlagList( GetSpawnerUnits( boars ), { ForbidAutoAttack, ForbidInteract, ForbidPlayerControl, ForbidAttack, ForbidDeath, ForbidSelectTarget, ForbidTakeDamage, ForbidMove }, false )
	for i=1, #GetSpawnerUnits( boars ) do
		LuaStopForcedAnimation( GetSpawnerUnits( boars )[i] )
		DebugTrace("[BoarMasterFriendsReleased] forced animation stopped for unit"..GetSpawnerUnits( boars )[i])
	end
	ForcedMoveToArea( GetSpawnerUnits( boars ), "boarMasterArea", 1 )
    if not UnitIsRealyDead( boarMaster ) then
        WaitForUnitNearUnit( GetSpawnerUnits( boars ), boarMaster, 4)
        SetUnitsFlagList( GetSpawnerUnits( boars ), {ForbidMove }, true )
    end
    if not UnitIsRealyDead( boarMaster ) then
        WaitForUnitNearUnit( mainHero, boarMaster, 10 )		
    end
	if not UnitIsRealyDead( boarMaster ) then
		StartDialog_boarMasterQuestCompleted()
		SetUnitsFlagList( GetSpawnerUnits( boars ), {ForbidMove }, false )
		LuaUnitRemoveApplicator( boarMaster, "quest_questionGrey" )
		LuaUnitRemoveFlag( boarMaster, ForbidMove )
		--AddTriggerEnd( ForcedMoveToArea, {boarMaster}, "gateUp", 1 )
	end
	CompleteQuest( "boarMasterQuest" )
	LuaHeroAddPrime( mainHero, 500 )
	LuaHeroAddPrime( witcher, 500 )
	--AddTriggerEnd( ForcedMoveToArea, GetSpawnerUnits( boars ), "gateUp", 1 )	
end

