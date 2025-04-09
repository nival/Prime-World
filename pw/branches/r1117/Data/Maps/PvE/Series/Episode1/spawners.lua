-- SPAWNERS
creeps = nil
spawners = nil

function SpawnersInit( reconnecting )
	creeps = {}
	spawners = {}

	LuaDebugTrace("SpawnersInit: "..tostring(reconnecting));
	if not reconnecting then
		SetGlobalVar( "Spawner_Creeps", creeps )
		SetGlobalVar( "Spawner_Spawners", spawners )
		AddTriggerEnd( TrackSpawnerCreatures )
	end
end

function PrintSpawnerUnitsList(spawnerName)
	for name, v in pairs(spawners) do
		if name == spawnerName then
			LuaDebugTrace("TRACE: spawner "..spawnerName.." units list:")
			for j=1, #v.unitsList do
				LuaDebugTrace("value ["..j.."] = "..v.unitsList[j])
			end
			break
		end
	end
end

function AreSpawnerUnitsDead( spawnerName )
	if #GetSpawnerUnits( spawnerName )==0 then
		return true
	else
		return false
	end
end

function AreSpawnerListUnitsDead( spawnerList )
	local deadSpawners = 0
	for i=1,#spawnerList do
		if AreSpawnerUnitsDead( spawnerList[i] ) == true then 
			deadSpawners = deadSpawners + 1
		end
	end
	if deadSpawners == #spawnerList then 
		return true
	else
		return false
	end
	LuaDebugTrace("FINISHED: [AreSpawnerListUnitsDead]. All units in spawner list are dead")
end

function GetSpawnerUnits( spawnerName )
	local sp = spawners[spawnerName]
	if sp then 
		return sp.unitsList;
	end
	LuaDebugTrace("ERROR! GetSpawnerUnits: no such spawner with name "..spawnerName)
	return {}
end

function GetSpawnerPosition( spawnerName )
	local units = GetSpawnerUnits( spawnerName )
	return LuaUnitGetPosition( units[1] )
end

function SpawnerSpawn( spawnerName, faction, applyAntiAoe )
	LuaDebugTrace("TRACE: SpawnerSpawn("..spawnerName..") STARTED...")
	local sp = spawners[spawnerName]
	if not sp then
		sp = { unitsList={} }
		spawners[spawnerName] = sp
	end
	
	sp.wave, sp.units = LuaSpawnerSpawnWave(spawnerName)
	--LuaDebugTrace("TRACE: spawned "..spawnerName..". WAVE = "..sp.wave.." count = "..sp.units)
	local spawned = {}
	for unit=1, sp.units do
		local creepName = spawnerName.."_w"..sp.wave.."_c"..unit
		table.insert( sp.unitsList, creepName )
		table.insert( spawned, creepName )
		if faction ~= nil then 
			LuaSetCreepFaction( creepName, faction ) 
		end
        UpgradeCreepStats( creepName )
		
        if applyAntiAoe then
            LuaApplyPassiveAbility( creepName, "decreaseDamageFromAbilities" ) 
        end
		creeps[ creepName ] = {faction = LuaGetUnitFaction(creepName), alive = true, level = LuaGetUnitStat( creepName, StatLevel )}
	end
	LuaDebugTrace("TRACE: SpawnerSpawn("..spawnerName..") FINISHED...")
	return spawned
end

function TrackSpawnerCreatures()
	--LuaDebugTrace("TRACE: TrackSpawnerCreatures STARTED")
	while not GetGlobalVar("isMissonFinished") do 
		for name,v in pairs(spawners) do
			for k=1, #v.unitsList do
				local unitName = v.unitsList[k]
				local dead, found = LuaUnitIsDead( unitName )
				local turnedSummon = found and not dead and LuaGetUnitType( unitName ) == UnitTypeSummon
				if dead or not found or turnedSummon then 						
					table.remove(v.unitsList, k)
					creeps[ unitName ].alive = false
					LuaDebugTrace("DEBUG: unit "..unitName.." has removed from array")				
					break
                else 
                    local level = LuaGetUnitStat( unitName, StatLevel )
                    if level ~= creeps[ unitName ].level then
                        UpgradeCreepStats( unitName )
                        creeps[ unitName ].level = level
                    end
				end
				creeps[ unitName ].faction = LuaGetUnitFaction( unitName )
			end
		end
		SleepState()
	end
end

function PrintCreeps()
	LuaDebugTrace("len = "..#creeps)
	for i,v in pairs(creeps) do
		LuaDebugTrace("name = "..i..", faction = ".. v.faction..", alive = "..tostring(v.alive))
	end
end

function GetPlayerCreeps( faction, alive )
	local arr = {}
	for i, v in pairs(creeps) do
		if v.faction == faction then
			if alive == nil then
				table.insert(arr, i)
			elseif alive and v.alive then 
                table.insert(arr, i)
            else 
				local dead, found = LuaUnitIsDead( i )
                local vdead = dead or not found or LuaGetUnitType( i ) == UnitTypeSummon
                if alive ~= vdead then
                    table.insert(arr, i)
                end
			end
		end
	end
	return arr
end
