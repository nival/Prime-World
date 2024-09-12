include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

ZombieSpawnDelay = 1
KilledHeroProc = 100
KilledBySummonProc = 50
KilledByMeleeAAProc = 100
KilledByRangedAAProc = 70
KilledByAbilityProc = 30

function Init( reconnecting )
	if not reconnecting then
		LuaApplyPassiveAbility ("MainBuildingA", "MainBuildingBuff") -- раздаем статус своим зданиям
		LuaApplyPassiveAbility ("MainBuildingB", "MainBuildingBuff")
	end
end


function OnUnitDie( victimId, killerId, lastHitterId, deathParamsInfo )
	if killerId == -1 then
		return
	end
	
	if LuaGetUnitVariableById( victimId, "InventorSpecial" ) ~= 0 then
		local dbid = "SuperInventor"
		local faction = LuaGetUnitFactionById( killerId )
		LuaCreateZombieById( victimId, dbid, faction )
		return
	end

	local victimType = LuaGetUnitTypeById( victimId )
	local killerType = LuaGetUnitTypeById( killerId )
	
	if killerType ~= UnitTypeHeroMale or LuaHeroIsCloneById( killerId ) then
		return
	end
		
	local heroIsKilled = victimType == UnitTypeHeroMale and not LuaHeroIsCloneById( victimId )
	
	if victimType ~= UnitTypeCreep and victimType ~= UnitTypeSiegeCreep and not heroIsKilled then
		return
	end
	
	if LuaGetUnitVariableById( victimId, "ImZombie" ) ~= 0 then
		return
	end
	
	local lastHitterType = LuaGetUnitTypeById( lastHitterId )
	
	local killedBySummon = lastHitterType == UnitTypeSummon or lastHitterType == UnitTypeDummyUnit
	local killedByAutoAttack = deathParamsInfo.isAutoAttack
	local killedByMelee = deathParamsInfo.isMelee
	
	local check = false
	local roll = LuaRandom( 0, 100 )
	if heroIsKilled then -- если был убит герой (как угодно)
		LuaDebugTrace( "Killed hero" )
		check = roll < KilledHeroProc
	elseif killedBySummon then -- если был убит крип суммоном
		LuaDebugTrace( "Killed by summon" )
		check = roll < KilledBySummonProc
	elseif killedByMelee then -- если  был убит крип милишной автоатакой героя
		LuaDebugTrace( "Killed by melee" )
		check = roll < KilledByMeleeAAProc
	elseif killedByAutoAttack then -- если был убит крип ренджовой автоатакой героя
		LuaDebugTrace( "Killed by ranged" )
		check = roll < KilledByRangedAAProc
	else -- если был убит крип абилкой героя
		LuaDebugTrace( "Killed by ability" )
		check = roll < KilledByAbilityProc
	end
	
	if not check then
		return
	end
	
	local dbid
	if heroIsKilled then
		dbid = "SuperZombie"
	else
		dbid = "Zombie"
	end
	
	local faction = LuaGetUnitFactionById( killerId )
	if faction == 1 then
		dbid = dbid .. "A"
	else
		dbid = dbid .. "B"
	end

	AddTriggerTop( SpawnZombie, victimId, dbid, faction )
end

function SpawnZombie( victimId, dbid, faction )
	WaitState( ZombieSpawnDelay )
	LuaCreateZombieById( victimId, dbid, faction )
end
