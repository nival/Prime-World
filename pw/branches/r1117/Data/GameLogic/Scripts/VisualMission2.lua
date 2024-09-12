------------------------------------------------------------------------------------------------------
-- Mission2.lua 
------------------------------------------------------------------------------------------------------
include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")

-- Перед тем, как игроку показать область обязательно лочим ему все действия
function Init()
	LuaDebugTrace ("Mission2")
	-- Прячем не нужных юнитов, в случае тест скрипта лишних героев. Должен быть только один и бот Воеводы.
	LuaGroupHide ("Mission1", true)
	--LuaGroupHide ("Mission2", false)
	LuaDebugTrace ("Mission2True")
end
