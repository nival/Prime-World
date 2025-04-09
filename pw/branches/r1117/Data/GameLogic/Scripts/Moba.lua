include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

function OnUnitDie( victimId, killerId, lastHitterId, deathParamsInfo )

	if LuaGetUnitVariableById( victimId, "Boss_Dragon" ) ~= 0 then
		local dbid = "Dragon"
		local faction = LuaGetUnitFactionById( killerId )

		local lastWave = LuaSpawnerGetLastWave( "Boss_Dragon" )
		local strSpawnDragonPoint = tostring( "Boss_Dragon_w".. lastWave.. "_c1" )
		local IdSpawnDragonPoint = LuaGetUnitIdByObjectName( strSpawnDragonPoint )

		LuaCreateZombieById( IdSpawnDragonPoint, dbid, faction )

		LuaKillUnit( strSpawnDragonPoint )
	end
	
	if LuaGetUnitVariableById( victimId, "InventorSpecial" ) ~= 0 then
		local dbid = "SuperInventor"
		local faction = LuaGetUnitFactionById( killerId )
		LuaCreateZombieById( victimId, dbid, faction )
	else
		return
	end
end