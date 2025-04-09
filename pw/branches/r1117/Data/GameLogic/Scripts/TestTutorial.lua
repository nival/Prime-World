------------------------------------------------------------------------------------------------------
-- TestTutorial.lua 
-- used for CxxTest
-- DO NOT MODIFY!
------------------------------------------------------------------------------------------------------
include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")

-- Перед тем, как игроку показать область обязательно лочим ему все действия
function Init()
	LuaDebugTrace ("Мир создается")
	-- Прячем не нужных юнитов, в случае тест скрипта лишних героев. Должен быть только один и бот Воеводы.
	LuaGroupHide ("TutorialMission2", true)
	-- Прячем Воеводу
	LuaCreatureHide ("01", true)
	-- Запрещаем спавнится солдатам
	LuaSetSpawnCreeps (false)
	LuaDebugTrace ("Init загрузился")
	AddStateEnd (Step1, "local")
	-- AddStateTop (HeroPositionValidate( hero , 114, 126, 15 ) -- ждем когда игрок окажется в указанной координате 
end

-- Adds wait state on the top and calls sleep for the parent state
function Wait( t )
	AddStateTop( WaitState, t )
	SleepState()
end

function HeroPositionValidateState( hero, x, y, accuracy )	
	while true do
		local hx, hy = LuaHeroGetPosition( hero )
		if ( math.abs( x - hx ) <= accuracy and math.abs( y - hy ) <= accuracy ) then
			LuaDebugTrace( "Point reached! Hero position: " .. hx .. ":" .. hy )
			LuaMessageToChat( "Checkpoint!" )
			return
		end
		SleepState()
	end
end

function HeroPositionValidate( hero, x, y, accuracy )
	AddStateTop( HeroPositionValidateState, hero, x, y, accuracy  )
	SleepState()
end

function CameraMoveAndBackState( x, y ) -- Функция на перемещение камеры
	LuaHeroAddFlag ("local", ForbidPlayerControl)
	LuaCameraLock (true)
	LuaDebugTrace ("Блокировали передвижение юнита")

	Wait( 1 ) -- определится со временем
	LuaDebugTrace ("Камера начала свое движение")

	LuaCameraMoveToPosTimed( x, y, 2 ) -- 2 время движения камеры	

	Wait( 4 ) -- определится со временем, добавляем время перемещения камеры в точку
	LuaDebugTrace ("Остановились в нужной координате")

	LuaCameraMoveToUnit ("local")
	LuaHeroRemoveFlag ("local", ForbidPlayerControl)
	LuaCameraLock (false)
	LuaMessageToChat("В эту область отправился патруль, помогите ему.") 
end

function CameraMoveAndBack( x, y )
	AddStateTop( CameraMoveAndBackState, x, y )
	SleepState()
end

function Step1 (hero)
	-- Отправляем Воеводу в нужную нам точку
	LuaCreatureTeleportTo( "01", 120, 123 ) -- определить координаты
	LuaMessageToChat( "Приветствуем Вас в игре PrimeWorld" )

	CameraMoveAndBack( 120, 123 )

	HeroPositionValidate( "local", 114, 126, 15 ) -- определится с координатами и расстоянием

	LuaHeroAddFlag ("local", ForbidPlayerControl)
	LuaHeroAddFlag ("local", ForbidMove)
	LuaHeroAddFlag ("local", ForbidAttack)
	LuaHeroAddFlag ("local", ForbidTakeDamage)

	CameraMoveAndBack( 120, 123 ) -- определится с координатами
	LuaDebugTrace ("Камера передвинута в нужное место")
	
	LuaCreatureHide ("01", false)
	-- Создаем солдат в указанном спавне
	LuaSpawnerSpawnWave ("SoldersA")
	LuaSpawnerSpawnWave ("SoldersB")
	Wait( 2 ) -- определится со временем, на появление крипов

	LuaMessageToChat("Воевода - Вперед! В атаку!")
	-- Заставляем их атаковать друг друга (их 4-о), при это узнаем их имена
	LuaCreatureMoveTo ("SolderA_w1_c1", 124, 126, 4)
	LuaCreatureMoveTo ("SolderA_w1_c2", 128, 127, 4)
	LuaCreatureMoveTo ("SolderB_w1_c1", 124, 126, 4)
	LuaCreatureMoveTo ("SolderB_w1_c2", 128, 127, 4)
	
	Wait( 1 ) -- определится со временем, на появление крипов

	-- Заставляем Воеводу атаковать врагов
	LuaDebugTrace("Воевода атакует солдат")
	LuaCreatureMoveTo ("01", 124, 126, 2)
	LuaHeroRemoveFlag ("local", ForbidPlayerControl)
	LuaHeroRemoveFlag ("local", ForbidMove)
	LuaHeroRemoveFlag ("local", ForbidAttack)
	LuaHeroRemoveFlag ("local", ForbidTakeDamage)
	LuaSetSpawnCreeps (true)
end
