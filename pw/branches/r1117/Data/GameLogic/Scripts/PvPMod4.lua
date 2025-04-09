include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

LuaDebugTrace( "PvPMod4.lua launched!" )

function Init( reconnecting )
	if not reconnecting then
		LuaApplyPassiveAbility ("MainBuildingA", "MainBuildingBuff") -- раздаем статус ГЗ
		LuaApplyPassiveAbility ("MainBuildingB", "MainBuildingBuff")
		
		for team = 0, 1 do
			for hero = 0, 4 do
				currentHero = tostring(team) .. tostring(hero)
				LuaHeroTakeConsumable ( currentHero, "NaftaPotion2000" ) -- прописан в dictionary 
				LuaHeroTakeConsumable ( currentHero, "RemoveCooldown" ) -- прописан в dictionary 
			end
		end
				
	end
end