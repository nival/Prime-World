function InitPetOwnerQuest()
	LuaDebugTrace("STARTED: [InitPetOwnerQuest]")
	PET_FLAGS = { ForbidAutoAttack, ForbidInteract, ForbidPlayerControl, ForbidAttack, ForbidDeath, ForbidSelectTarget }

	
	if debugCompleteObjectivePets then
		DebugTrace("[InitPetOwnerQuest] debug mode. Pet owner waits for waves start.")
        AddQuest( "petOwnerQuest", false, true )
        CompleteQuest( "petOwnerQuest" )
        
		while not wavesStarted do SleepState() end
		DebugTrace("[InitPetOwnerQuest] debug mode. Waves started.")
		local x,y,radius = LuaGetScriptArea("petOwnerGuardArea")
		--LuaCreatureHide( petOwner, false ) -- показываем Хагри игроку
		LuaCreatureMoveTo( petOwner, x, y, 0 )
		SleepState(2)
		LuaHeroAIGuardScriptArea( petOwner, "petOwnerGuardArea", true )
		DebugTrace("[InitPetOwnerQuest] debug mode. Pet owner goes to guard castle area.")
		return
	end	

	SpawnPet( "petDog" )
	SpawnPet( "petCat" )
	SpawnPet( "petDuck" )
	
	WaitForUnitInArea( mainHero, "petOwnerArea" ) -- Ждем, когда игрок окажется в нужной нам области

	LaunchSpawnPet( "petDog" )
	LaunchSpawnPet( "petCat" )
	LaunchSpawnPet( "petDuck" )

	petOwnerObjectiveObtained = false
	
	LuaCreatureHide( petOwner, false ) -- показываем Хагри игроку
	WaitState(0.5)
	local x,y,r = LuaGetScriptArea( "petOwnerPosition" )
	LuaCreatureTeleportTo( petOwner, x, y )
	--LuaHeroSetForbidRespawn( petOwner, true ) 
	SpawnerSpawn( "petOwnerAttackers", factionEnemy, true )
	
	AddTriggerEnd( TerminateQuestWhenPetOwnerIsDead )
	
	LuaHeroAIGuardScriptArea( petOwner, "petOwnerPosition", true )
	
	local effX, effY = LuaGetScriptArea( "petOwnerArea" )
	LuaPlaceStandaloneEffect("petOwnerEffect", "neutralTerrain", effX, effY)
	LuaChangeNatureMapXY( effX, effY, 12, -1, FACTION_NEUTRAL )
	LuaChangeNatureMapXY( x, y, 12, -1, FACTION_NEUTRAL )

	LuaUnitApplyApplicator( petOwner, "quest_questionYellow" )

	while AreSpawnerUnitsDead( "petOwnerAttackers" ) == false or DistanceUU( mainHero, petOwner ) > 12 do SleepState() end
	if petsQuestTerminated == true then return end
	
	LuaAddHeroToInfoPanel( petOwner )
	StartDialog_PetOwnerQuest()
	petOwnerObjectiveObtained = true

	AddQuest( "petOwnerQuest", false, true )
	for i,v in pairs(pets) do
		LuaSetCreepFaction( i, factionEnemy )
	end

	LuaUnitRemoveApplicator( petOwner, "quest_questionYellow"  )
	LuaUnitApplyApplicator( petOwner, "quest_questionGrey" )
		
	AddTriggerEnd( PetOwnerQuestComplete )
end

function TerminateQuestWhenPetOwnerIsDead()	
	petsQuestTerminated = false
	while UnitIsRealyDead( petOwner ) == false and not isMissonFinished do SleepState() end
	DebugTrace("[TerminateQuestWhenPetOwnerIsDead] pet owner is dead")
	petsQuestTerminated = true
	CompleteQuest( "petOwnerQuest" )
end

function PetOwnerQuestComplete()
	LuaDebugTrace("STARTED: [PetOwnerQuestComplete]")
	local totalPets = 3
	local returnedPets = 0
	local heroBringNewPet = false
	local tamedPetsCount = 0
	local petOwnerX, petOwnerY = LuaUnitGetPosition( petOwner )
	
	WaitForUnitOutArea( mainHero, "petOwnerPosition" )
	local x,y,radius = LuaGetScriptArea( "petOwnerPosition" )
	local lastDialogFinishTime = 0
	
	while totalPets~=returnedPets do
		if petsQuestTerminated==true then return end
		if DistanceUU( petOwner, mainHero ) < radius then
			tamedPetsCount = 0
			for name,v in pairs(pets) do
				if v.tamed == true and v.returned == false then 
					tamedPetsCount = tamedPetsCount + 1
					v.returned = true
					returnedPets = returnedPets + 1 
					LuaCreatureMoveTo( name, petOwnerX, petOwnerY, 1)
					WaitState(1)			
					LuaCreatureHide( name, true )
					--LuaApplyPassiveAbility( petOwner, v.applicatorName )
					DebugTrace("ability applied for pet "..name)
					LuaUpdateSessionQuest( "petOwnerQuest", returnedPets )
				end
			end
			if tamedPetsCount > 0 and returnedPets~=totalPets then								
				StartDialog_PetOwnerHappy()
				LuaForceAnimation( petOwner, "happy", 1 )
				WaitState(4)
				LuaStopForcedAnimation( petOwner )
				DebugTrace("[PetOwnerQuestComplete] Pet owner is happy! returnedPets = "..returnedPets)
			elseif tamedPetsCount == 0 then		
				if GetGameStep() - lastDialogFinishTime > 30 then
					if IsUnitInArea( petOwner, "petOwnerPosition" ) then
						local pX, pY = LuaUnitGetPosition( petOwner )
						if #LuaGetCreepsInArea( pX, pY, 10, enemyFactionFlag) == 0 then
							StartDialog_PetsNotReturnedYet()
							lastDialogFinishTime = GetGameStep()
						end
					end
				end
			end
			if returnedPets~=totalPets then
				WaitForUnitOutArea( mainHero, "petOwnerPosition" )
			end
		end
		SleepState()
	end
	
	StartDialog_PetOwnerQuestCompleted()
	CompleteQuest( "petOwnerQuest" )
	LuaHeroAddPrime( mainHero, 500 )
	LuaHeroAddPrime( witcher, 500 )
	LuaForceAnimation( petOwner, "happy", 1 )
	WaitState(4)
	LuaStopForcedAnimation( petOwner )
	WaitState(1)
	LuaUnitRemoveApplicator( petOwner, "quest_questionGrey" )
	LuaHeroSetForbidRespawn( petOwner, false ) 
	local respX, respY = LuaGetScriptArea( "petOwnerResurrectPoint" )
	LuaHeroSetRespawnPoint( petOwner, respX, respY )
	local x,y,radius = LuaGetScriptArea("petOwnerGuardArea")
	SleepState()
	LuaCreatureMoveTo( petOwner, x, y, 0 )	
	SleepState()
	LuaHeroAIGuardScriptArea( petOwner, "petOwnerGuardArea", true )	
	LevelUpHero( petOwner,  LuaHeroGetLevel( mainHero )+1 )
	for name,v in pairs(pets) do
		LuaApplyPassiveAbility( iva, v.applicatorName )
	end
end

function SpawnPet( petSpawnerName )
	LuaDebugTrace("STARTED: [SpawnPet] for spawner "..petSpawnerName)
	SpawnerSpawn( petSpawnerName, factionPlayer, false )
end

function LaunchSpawnPet(petSpawnerName)
	local petName = petSpawnerName.."_w"..spawners[petSpawnerName].wave.."_c1"
	DebugTrace("[SpawnPet]. petName = "..petName)
	
	SetUnitsFlagList( {petName}, PET_FLAGS, true, true)
	LuaApplyPassiveAbility( petName, "CantDeath" )
	DebugTrace("[SpawnPet] ability CantDeath applied")
	--LuaUnitAddFlag( petName, ForbidTakeDamage )
	
	pets[ petName ] = { tamed = false, maxHP = LuaGetUnitStat(petName, StatLife), returned = false, applicatorName = petSpawnerName }
	LuaDebugTrace("pets["..petName.."] = { tamed = "..tostring(pets[petName].tamed)..", returned = "..tostring(pets[petName].returned)..", applicatorName = "..tostring(pets[petName].applicatorName).."}")

	AddTriggerEnd( PetPromenade, petName )
	AddTriggerEnd( SetUnitImmortal, petName, true )
	AddTriggerEnd( TamePet, petName )
	
	LuaDebugTrace("FINISHED: [SpawnPet]")	
end

function PetPromenade( petName )
	LuaDebugTrace("STARTED: [PetPromenade] for pet "..petName)
	AddTriggerEnd( AllowHeroTamePetWhenNear, petName )
	while pets[ petName ].tamed == false do
		--nextTargetID = math.random(1,15)
		local nextArea = string.sub(petName,1, -7).."Point"..tostring(math.random(1,8))
		local x,y,r = LuaGetScriptArea( nextArea )
		DebugTrace( "[PetPromenade] nextArea is "..nextArea )
		while DistanceUA( petName, nextArea ) > r and pets[ petName ].tamed == false and DistanceUU(mainHero, petName) > 14 do 
			if petsQuestTerminated == true then
				LuaCreatureHide( petName, true )
				return
			end
			LuaCreatureMoveTo( petName, x, y, 0 )
			SleepState() 
		end
		if DistanceUU(mainHero, petName) < 14 then
			TryEvade( petName, string.sub(petName, 1, -7).."Point")
		end
		DebugTrace( petName.." has reached area "..nextArea )
		WaitState(3)
		SleepState()
	end
end

function TryEvade( petName, petPointName )	
    LuaDebugTrace("STARTED: [TryEvade] for pet "..petName)
	local prevDistance = DistanceUU( mainHero, petName )
	local x,y = 0,0 
	while DistanceUU( mainHero, petName ) < 14 and pets[ petName ].tamed == false do
		if DistanceUU( mainHero, petName ) < prevDistance then
			prevDistance = DistanceUU( mainHero, petName )
			for i=1, 8 do
				x,y,r = LuaGetScriptArea( tostring(petPointName)..tostring(i) )
				LuaCreatureMoveTo( petName, x, y, 0 ) 
				prevDistance = DistanceUU( mainHero, petName )
				SleepState()
				if DistanceUU( mainHero, petName ) > prevDistance or pets[ petName ].tamed then break end
			end		
		end
		SleepState()
	end
    LuaDebugTrace("FINISHED: [TryEvade] for pet "..petName)
end

function AllowHeroTamePetWhenNear( petName )
	LuaDebugTrace("STARTED: [AllowHeroTamePetWhenNear] for pet "..petName)
	while not pets[ petName ].tamed  do
        LuaUnitAddFlag( petName, ForbidAutotargetMe )
		LuaUnitAddFlag( petName, ForbidTakeDamage )
		while not IsUnitNearUnit( petName, mainHero, 16 ) and not petsQuestTerminated do SleepState() end
		DebugTrace("[AllowHeroTamePetWhenNear]. Pet "..petName.." is near main hero. Allow take damage")
		LuaUnitRemoveFlag( petName, ForbidTakeDamage )
        
		while IsUnitNearUnit( petName, mainHero, 16 ) and not petsQuestTerminated and not pets[ petName ].tamed do SleepState() end
		DebugTrace("[AllowHeroTamePetWhenNear]. Pet"..petName.." leaves main hero. Add flag forbid take damage")
		if petsQuestTerminated then return end
		SleepState()
	end
    LuaUnitRemoveFlag( petName, ForbidAutotargetMe )
	LuaDebugTrace("FINISHED: [AllowHeroTamePetWhenNear] for pet "..petName)
end

function TamePet( petName )
	LuaDebugTrace("STARTED: [TamePet] for pet "..petName)
	while petOwnerObjectiveObtained==false do SleepState() end
	DebugTrace("[TamePet] time to tame "..petName)
	while true do		
        if petsQuestTerminated then	return end
        if LuaIsUnitAttacked( petName ) then
            pets[ petName ].tamed = true
            AddTriggerEnd( PetFollowHero, petName )
            LuaSetCreepFaction( petName, factionPlayer )
            LuaUnitAddFlag( petName, ForbidTakeDamage )
            --AddTriggerEnd( ReturnPetToOwner, petName )
            LuaDebugTrace("FINISHED: [TamePet] for pet "..petName)
            return
        end
		SleepState()
	end
end

function PetFollowHero( petName )
	LuaDebugTrace("STARTED: [PetFollowHero] for pet "..petName)
	local heroX, heroY = 0, 0
	local followX, followY  = 0, 0

	while pets[ petName ].returned == false do
		if petsQuestTerminated==true then
			LuaCreatureHide( petName, true )
			LuaApplyPassiveAbility( mainHero, pets[petName].applicatorName )
			return
		end
		heroX, heroY = LuaUnitGetPosition( mainHero )
		followX, followY  = heroX + math.random(-2, 2), heroY + math.random(-2, 2)
		LuaCreatureMoveTo( petName, followX, followY, 0 )
		WaitState(1)
	end
	LuaDebugTrace("FINISHED: [PetFollowHero] for pet "..petName)
end