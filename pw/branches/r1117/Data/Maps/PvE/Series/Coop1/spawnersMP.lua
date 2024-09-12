--[[ SPAWNERS 
--Interface: 
function SpawnersInit( reconnecting )
function SpawnersReconnect()
function PrintSpawnerUnitsList( spawnerName )
function AreSpawnerUnitsDead( spawnerName )
function AreSpawnerListUnitsDead( spawnerList )
function GetSpawnerUnits( spawnerName )
function GetSpawnerPosition( spawnerName )
function SpawnerSpawn( spawnerName, faction )

uses global var isMissonFinished
]]

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

function SpawnersReconnect()
	LuaDebugTrace("SpawnersReconnect: " );
	creeps = GetGlobalVar( "Spawner_Creeps" )
	spawners = GetGlobalVar( "Spawner_Spawners" )
end


function PrintSpawnerUnitsList( spawnerName )
	local sp = spawners[spawnerName]
	if sp then 
		LuaDebugTrace("TRACE: spawner "..spawnerName.." units list:")
		for j=1, #sp.unitsList do
			LuaDebugTrace("value ["..j.."] = "..sp.unitsList[j])
		end
	end
end

function AreSpawnerUnitsDead( spawnerName )
	return #GetSpawnerUnits( spawnerName ) == 0;
end

function AreSpawnerListUnitsDead( spawnerList )
	for i=1,#spawnerList do
		if not AreSpawnerUnitsDead( spawnerList[i] ) then 
			return false
		end
	end
	--LuaDebugTrace("FINISHED: [AreSpawnerListUnitsDead]. All units in spawner list are dead")
	return true
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
	if #units > 0 then
		return LuaUnitGetPosition( units[1] )
	end
end


function SpawnerSpawn( spawnerName, faction )
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
		
		creeps[ creepName ] = {faction = LuaGetUnitFaction(creepName), alive = true}
	end
	LuaDebugTrace("TRACE: SpawnerSpawn("..spawnerName..") FINISHED...")
	return spawned;
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

function TrackSpawnerCreatures()
	--LuaDebugTrace("TRACE: TrackSpawnerCreatures STARTED")
	while not GetGlobalVar("isMissonFinished") do 
		for name,v in pairs(spawners) do
			for k=1, #v.unitsList do
				local unitName = v.unitsList[k]
				local dead, found = LuaUnitIsDead( unitName )
				local turnedSummon = found and not dead and LuaGetUnitType( unitName ) == UnitTypeSummon;
				if dead or not found or turnedSummon then 						
					table.remove(v.unitsList, k)
					creeps[ unitName ].alive = false
					LuaDebugTrace("DEBUG: unit "..unitName.." has removed from array")				
					break
				end
			end
		end
		SleepState();
	end
end
