

function GorynychObjective( direction )
	LuaDebugTrace("STARTED: [GorynychObjective]")
	while GetGlobalVar( "stopSpawnStandardWaves" ) do SleepState() end	-- ждем, пока не прекратится стандартное набегание волн мобов
	DebugTrace("[GorynychObjective] Gorynych spawn time!")
	LuaSpawnerSpawnWave( "Gorynych" )
	local creep = "Gorynych_w1_c1"
	UpgradeCreepStats( creep ) -- выставляем Горынычу правильные статы
	LuaSetCreepFaction( creep, factionEnemy ) 
	WaitState(1.5)
	local startPositionX, startPositionY = LuaGetScriptArea( direction.."EnemySpawnerArea" )
	LuaCreatureTeleportTo( creep, startPositionX, startPositionY )
	
	RED_DIFFICULTY = RED_DIFFICULTY or false
	
	--AddTriggerEnd( HintLineWait, "hintLine_defeatGorynich", 5 )
    LuaUnitApplyApplicatorFromUnit( allyHeroes[1], allyHeroes[1], "gorynychSpawnedEvent" ) -- показываем анонсмент "Приближается змей Горыныч"
	
	AddQuest("killGorynich") -- Добавляем задание "Одолейте Змея Горыныча"
	
	AddTriggerEnd( GorynychSoldierSupport, direction ) -- Поддержка Горыныча, всякая мелочь
	AddTriggerEnd( GorynychBossesSupport, direction ) -- Поддержка Горыныча, толстяки
	AddTriggerEnd( GorynychMoving, direction ) -- Отправляем Горыныча атаковать направление
    
    local dead
	repeat
		dead = LuaUnitIsDead( creep )
		SleepState()
	until dead -- ждем пока Горыныч не подохнет. Даже на знаю зачем ждем.
    
	LuaDebugTrace("FINISHED: [GorynychObjective]")
end

-- Отправляем Горыныча на бой и радуемся, если он сдох
function GorynychMoving( direction )
	LuaDebugTrace("STARTED: [GorynychMoving] for direction"..direction)
	local creep = "Gorynych_w1_c1"
	local pathName = direction.."Path"
	LuaSetCreepBehavior( creep, "PathMove", pathName, 5 ) -- Отправляем Горыныча вдоль пути "PathMove" (есть такой объект на карте)
	local dead, exist
	local x, y
		
	repeat
		dead, exist = LuaUnitIsDead( creep )
		if not dead then
			x,y =  LuaUnitGetPosition( creep )
		end
		SleepState()
	until dead --ждем пока Горыныч не подохнет, проверяем его координаты
	LuaPlaceStandaloneEffect("victoryEffect", "fireWorks", x, y) -- ежели помер, в месте где он двинул кони проигрываем победный фейерверк
	AddTriggerEnd( KillAllCreeps ) --убиваем всех крипов
	WaitState(3)

    local factionLoser 
    if factionPlayer == FACTION_DOCT then factionLoser = FACTION_ADORN else factionLoser = FACTION_DOCT end
    CompleteQuest("killGorynich")
	
	-- reset special points
	for i = 1, #allyHeroes do
		LuaSetHeroSpecialPoints( allyHeroes[i], 0 )
	end
	
	LuaGameFinish( factionLoser ) -- not factionEnemy, 'cause factionEnemy in now NEUTRAL
	PrintArray( SPAWNEDCREEPS )
end


-- Поддержка Горыныча мелкими крипами. В текущей версии состоит исключительно из Кобольдов сбивателей флагов
-- Спавнятся раз в 15 секунд, пока Горыныч жив
function GorynychSoldierSupport( direction )
	--local supportUnits = {"Kobolds", "Kobolds", "DemolitionMan2", "Kobolds1", "Satyrs1", "Vodyanoi1", "Assida1"}
	local supportUnits = {"Kobolds"}
	local logicMod = GetGlobalVar("logicMod")
	local waitGorynychSupportInterval = 15
	if RED_DIFFICULTY then
		waitGorynychSupportInterval = waitGorynychSupportInterval * (1 - 0.3 * logicMod) 
	end
	local dead, exist = LuaUnitIsDead( "Gorynych_w1_c1" )
	while  not dead do
		local spawned = SpawnerSpawn( supportUnits[LuaRandom(1, #supportUnits) ], factionEnemy )		
		
		PushPathAndApplyFlagBonus( spawned, direction )
		
		LuaDebugTrace("STARTED: [GorynychMoving] creeps inverval: "..waitGorynychSupportInterval)
		LuaDebugTrace("STARTED: [GorynychMoving] logmodOn: "..logicMod)
		
		WaitState( waitGorynychSupportInterval + LuaRandom( -2, 2) )
		dead, exist = LuaUnitIsDead( "Gorynych_w1_c1" )
	end
end		

-- Поддержка Горыныча чемпионами. Спавнятся по 3 штуки раз в минуту.
function GorynychBossesSupport( direction )
	local dead, exist = LuaUnitIsDead( "Gorynych_w1_c1" )
	local logicMod = GetGlobalVar("logicMod")
	local groups = {"LeshijAlone", "KikimorAlone", "Spriggan1", "Spriggan2", "Assassin1" } -- из этих групп выбираем боссов
	local waitBossInterval = 40
	if RED_DIFFICULTY then
		waitBossInterval = waitBossInterval * (1 - 0.5 * logicMod) 
	end
	
	LuaDebugTrace("STARTED: [GorynychMoving] boss creeps inverval: "..waitBossInterval)
	while not dead do -- пока Горыныч жив
		for i=1, 3 do
			local spawned = SpawnerSpawn( groups[LuaRandom(1,#groups)], factionEnemy )	-- спавним случайную группу
			PushPathAndApplyFlagBonus( spawned, direction )		
			WaitState(4) -- через 4 секунды следующая группа боссов
		end
		WaitState( waitBossInterval )
		dead, exist = LuaUnitIsDead( "Gorynych_w1_c1" )
	end
end