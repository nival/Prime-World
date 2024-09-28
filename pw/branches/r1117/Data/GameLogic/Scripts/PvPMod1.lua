include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

LuaDebugTrace( "PvPMod1.lua launched!" )

function Init( reconnecting )
	if not reconnecting then
		LuaApplyPassiveAbility ("MainBuildingA", "MainBuildingBuff") -- раздаем статус своим зданиям
		LuaApplyPassiveAbility ("MainBuildingB", "MainBuildingBuff")
	end
end

function OnUnitDie( victimId, killerId, lastHitterId, deathParamsInfo )

	if LuaGetUnitVariableById( victimId, "InventorSpecial" ) ~= 0 then
		local dbid = "SuperInventor"
		local faction = LuaGetUnitFactionById( killerId )
		LuaCreateZombieById( victimId, dbid, faction )
	else
		return
	end
end