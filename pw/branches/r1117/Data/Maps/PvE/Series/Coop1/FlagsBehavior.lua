
-- Constants
    FOREST_FLAG_POLES = {"leftCreepHutFlag3", "leftCreepHutFlag1", "leftCreepHutFlag2", "upCreepHutFlag1", "rightCreepHutFlag2", "rightCreepHutFlag1", "rightCreepHutFlag3", "downCreepHutFlag1"}
	CREEP_HUTS = {"leftCreepHut1", "leftCreepHut2", "leftCreepHut3", "downCreepHut1", "rightCreepHut1", "rightCreepHut2", "rightCreepHut3", "upCreepHut1"}

 -- Global vars
raisedFlagpoles = nil -- здесь храним все флаги на карте и их состояние. Если флагу соответствует true, значит он поднят, если false - значит опущен
flagsInitCompleted = false --transient


function FlagsInit( reconecting )	
    raisedFlagpoles = {}
	if not reconnecting then
		SetGlobalVar( "raisedFlagpoles", raisedFlagpoles )
	end
end
function FlagsReconnect()
   	raisedFlagpoles = GetGlobalVar( "raisedFlagpoles" )
    flagsInitCompleted = true
end

-- Настройка флагов
function FlagsStartup()	
	LuaDebugTrace("STARTED: [InitFlags]")
	flagsInitCompleted = false
	
	SetFlagChainNature( "leftPolygon", {"1", "2", "3"}, -1, FACTION_NEUTRAL ) -- назначаем тип начальный тип родной земли для цепочки флагов по левой дороге. "leftPolygon" - название зоны, подзоны {"1", "2", "3"} которой которая будет перекрашиваться при захвате флагов
	SetFlagChainNature( "upPolygon", {"1", "2", "3"}, -1, FACTION_NEUTRAL ) -- назначаем тип начальный тип родной земли для цепочки флагов по верхней дороге. "upPolygon" - название зоны, подзоны {"1", "2", "3"} которой которая будет перекрашиваться при захвате флагов
	SetFlagChainNature( "rightPolygon", {"1", "2", "3"}, -1, FACTION_NEUTRAL ) -- назначаем тип начальный тип родной земли для цепочки флагов по правой дороге. "rightPolygon" - название зоны, подзоны {"1", "2", "3"} которой которая будет перекрашиваться при захвате флагов
	SetFlagChainNature( "downPolygon", {"1", "2", "3"}, -1, FACTION_NEUTRAL ) -- назначаем тип начальный тип родной земли для цепочки флагов по нижней дороге. "downPolygon" - название зоны, подзоны {"1", "2", "3"} которой которая будет перекрашиваться при захвате флагов
	SetFlagChainNature( "leftCreepHutPolygon1", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "leftCreepHutPolygon3", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "downCreepHutPolygon1", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "rightCreepHutPolygon1", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "rightCreepHutPolygon2", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "rightCreepHutPolygon3", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "upCreepHutPolygon1", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	SetFlagChainNature( "leftCreepHutPolygon2", {"1"}, -1, FACTION_NEUTRAL ) -- инициализируем цепочку флагов (из одного флага ) для лесного флага
	local leftChainFlags = {"leftFlag1", "leftFlag2", "leftFlag3"} -- имена флагов в цепочке вдоль левой дороги
	local rightChainFlags = {"rightFlag1", "rightFlag2", "rightFlag3"} -- имена флагов в цепочке вдоль правой дороги
	local upChainFlags = {"upFlag1", "upFlag2", "upFlag3"} -- имена флагов в цепочке вдоль верхней дороги
	local downChainFlags = {"downFlag1", "downFlag2", "downFlag3"} -- имена флагов в цепочке вдоль нижней дороги
	for i=1, #leftChainFlags do raisedFlagpoles[ leftChainFlags[i] ] = false end -- добавляем в массив всех флагов raisedFlagpoles флаги левой дороги. Состояние "не поднят", то есть false
	for i=1, #rightChainFlags do raisedFlagpoles[ rightChainFlags[i] ] = false end -- добавляем в массив всех флагов raisedFlagpoles флаги правой дороги. Состояние "не поднят", то есть false
	for i=1, #upChainFlags do raisedFlagpoles[ upChainFlags[i] ] = false end -- добавляем в массив всех флагов raisedFlagpoles флаги верхней дороги. Состояние "не поднят", то есть false
	for i=1, #downChainFlags do raisedFlagpoles[ downChainFlags[i] ] = false end -- добавляем в массив всех флагов raisedFlagpoles флаги нижней дороги. Состояние "не поднят", то есть false
		
	CreateFlagChain( "leftChain", leftChainFlags, "leftPolygon", {"1", "2", "3"}, factionPlayer, FlagIsRaised ) -- инициализация цепочки флагов вдоль левой дороги. FlagIsRaised функция, которая будет запускаться при захвате/потере любого флага из цепочки
	CreateFlagChain( "upChain", upChainFlags, "upPolygon", {"1", "2", "3"}, factionPlayer, FlagIsRaised) -- инициализация цепочки флагов вдоль верхней дороги. FlagIsRaised функция, которая будет запускаться при захвате/потере любого флага из цепочки
	CreateFlagChain( "rightChain", rightChainFlags, "rightPolygon", {"1", "2", "3"}, factionPlayer, FlagIsRaised) -- инициализация цепочки флагов вдоль правой дороги. FlagIsRaised функция, которая будет запускаться при захвате/потере любого флага из цепочки
	CreateFlagChain( "downChain", downChainFlags, "downPolygon", {"1", "2", "3"}, factionPlayer, FlagIsRaised)	-- инициализация цепочки флагов вдоль нижней дороги. FlagIsRaised функция, которая будет запускаться при захвате/потере любого флага из цепочки
	CreateFlagChain( "leftCreepHutChain1", {"leftCreepHutFlag1"}, "leftCreepHutPolygon1", {"1"}, factionPlayer, ForestFlagRaised) --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	CreateFlagChain( "leftCreepHutChain2", {"leftCreepHutFlag2"}, "leftCreepHutPolygon2", {"1"}, factionPlayer, ForestFlagRaised) --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян	
	CreateFlagChain( "leftCreepHutChain3", {"leftCreepHutFlag3"}, "leftCreepHutPolygon3", {"1"}, factionPlayer, ForestFlagRaised)		 --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	CreateFlagChain( "downCreepHutChain1", {"downCreepHutFlag1"}, "downCreepHutPolygon1", {"1"}, factionPlayer, ForestFlagRaised)	 --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	CreateFlagChain( "rightCreepHutChain1", {"rightCreepHutFlag1"}, "rightCreepHutPolygon1", {"1"}, factionPlayer, ForestFlagRaised)	 --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	CreateFlagChain( "rightCreepHutChain2", {"rightCreepHutFlag2"}, "rightCreepHutPolygon2", {"1"}, factionPlayer, ForestFlagRaised)	 --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	CreateFlagChain( "rightCreepHutChain3", {"rightCreepHutFlag3"}, "rightCreepHutPolygon3", {"1"}, factionPlayer, ForestFlagRaised)	 --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	CreateFlagChain( "upCreepHutChain1", {"upCreepHutFlag1"}, "upCreepHutPolygon1", {"1"}, factionPlayer, ForestFlagRaised)	 --инициализация цепочки флагов (из одного флага) для зоны в лесу. ForestFlagRaised запускется если флаг захвачен/потерян
	
	
	for i=1, #FOREST_FLAG_POLES do -- для всех лесных флагов
		LuaCreatureHide( string.sub( FOREST_FLAG_POLES[i], 1, string.find( FOREST_FLAG_POLES[i], '%u') - 1).."GlyphSpawner"..string.sub( FOREST_FLAG_POLES[i], -1 ), true ) -- прячем спавнер глифа
		raisedFlagpoles[ FOREST_FLAG_POLES[i] ] = false -- добавляем в массив всех флагов наш флаг, говорим, что он опущен
		AddTriggerEnd( SpawnFlagDefenders, FOREST_FLAG_POLES[i] ) -- в функции SpawnFlagDefenders будем спавнить охрану флага
	end
	
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "leftCreepHutFlag1" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "leftCreepHutFlag2" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "leftCreepHutFlag3" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "downCreepHutFlag1" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "rightCreepHutFlag1" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "rightCreepHutFlag2" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "rightCreepHutFlag3" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	AddTriggerEnd( SpawnCreepsWhileFlagIsDown, "upCreepHutFlag1" ) -- пока флаг опущен, рядом с ним периодически спавнятся крипы и бегут на базу
	
	
	for i=1, #CREEP_HUTS do -- прячем все домики крипов, выставляем им иконки на минимапе
		local hutX, hutY = LuaUnitGetPosition( CREEP_HUTS[i] )
		local hutMinimapIcon = CREEP_HUTS[i].."icon"
		LuaPlaceMinimapIcon( hutMinimapIcon, MinmapIconCreepsStrong, hutX, hutY, 0 )
	end
	
	PrintArray( raisedFlagpoles )
    UpdateNatureProgress()
	
	AddQuest("raiseForestFlags", false, false ) -- выдаем задание "поднимите все флаги в лесу"
	
	AddTriggerEnd( CaptureForestFlags )
	
	WaitState(2)	
	flagsInitCompleted = true	

	LuaDebugTrace("FINISHED: [InitFlags]")
end

-- Спавним защитиков флагов в лесу
function SpawnFlagDefenders( flagName )
	LuaDebugTrace("STARTED: [SpawnFlagDefenders] for flag "..flagName)
	local flagX, flagY = LuaUnitGetPosition( flagName )
	local n = string.sub( flagName, -1 )
	local direction = string.sub( flagName, 1, string.find( flagName, '%u') - 1 )
	local areaName = tostring(direction).."CreepHutArea"..tostring(n)
	local areaX, areaY, r = LuaGetScriptArea( areaName )
	local spawned = {}
	
	WaitForUnitNearPoint( allyHeroes, flagX, flagY, 10 ) -- Ждем, когда кто-то из героев приблизится к флагу
	DebugTrace("[SpawnFlagDefenders] some hero is near flag "..flagName)
	if not raisedFlagpoles[ flagName ] then
		if flagName == "leftCreepHutFlag3" or flagName == "rightCreepHutFlag3" then -- если флаг рядом с домиком боровика, спавним боровика
			spawned = SpawnerSpawn( "OrdinaryBorovik", factionEnemy )				
		else
			spawned = SpawnerSpawn( "SatyrForest", factionEnemy )		-- если нет, то сатира
		end
		TeleportUnitList( spawned, areaX, areaY )	
        local x, y = LuaUnitGetPosition( ivaCreep )        
		for i = 1, #spawned do 
            LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" ) -- вешаем на наспавнихшихся крипов бонус от опущенных флагов
			--if not (flagName == "leftCreepHutFlag3" or flagName == "rightCreepHutFlag3") then			
				LuaSetCreepBehavior( spawned[i], "MoveTo", x, y, 2, 15 ) -- Отправляем их атаковать Иву
			--end
        end	
        
	end
	LuaDebugTrace("FINISHED: [SpawnFlagDefenders] for flag "..flagName)
end

-- Запускается каждый раз, когда флаг (не лесной) поднят или опущен
-- chainName - имя цепочки флагов
-- flagName - имя флага
-- polygonName - имя зоны
function FlagIsRaised( isRaised, chainName, flagName, polygonName )
	LuaDebugTrace("STARTED: [FlagIsRaised]")
	if not flagsInitCompleted then return end
	
	raisedFlagpoles[ flagName ] = isRaised
	if not isRaised then
        AddTriggerEnd( FlagIsCapturedUserFeedback,  flagName ) -- если флаг опущен, спамим на минимап сигналом и пишем в чат сообщение
	end
    UpdateNatureProgress()
end

-- запускается каждый раз, когда флаг в лесу поднят или опущен
-- chainName - имя цепочки флагов
-- flagName - имя флага
-- polygonName - имя зоны
function ForestFlagRaised( isRaised, chainName, flagName, polygonName )	
	DebugTrace("[ForestFlagRaised] for chain = "..chainName.." and flag "..flagName)	
		
	local direction = string.sub( chainName, 1, string.find( chainName, '%u') - 1 )
	local n = string.sub( chainName, -1 )
	
	local hutName = tostring(direction).."CreepHut"..tostring(n)		
	local glyphName = tostring(direction).."GlyphSpawner"..tostring(n)	
	local spawnerName = tostring(direction).."CreepHutSpawner"..tostring(n)	
	local hutX, hutY = LuaUnitGetPosition( hutName )
	local hutMinimapIcon = tostring(hutName).."icon"
	
	local prevStepRaisedFlags = GetRaisedForestFlags()
	local forestFlagsCount = #FOREST_FLAG_POLES
	
	raisedFlagpoles[ flagName ] = isRaised
	if prevStepRaisedFlags == forestFlagsCount and GetRaisedForestFlags() == forestFlagsCount - 1 then
		LuaDebugTrace("DEBUG: [ForestFlagRaised] quest Raise Forest Flags is active again ")
		AddQuest( "raiseForestFlags", false, false ) -- каждый раз, когда хотя бы один флаг в лесу не захвачен игроками, выдается квест "Захвати флаги в лесу"
	end	
    UpdateNatureProgress()
	
	SetQuestProgress("raiseForestFlags", GetRaisedForestFlags() )	-- выставляем в UI квеста количество захваченных флагов
			
	if not isRaised then -- если флаг опущен
		DebugTrace("[ForestFlagRaised] "..flagName.." is dropped down")	
				
		LuaCreatureHide( hutName, false ) -- ставим домик крипов
		LuaPlaceMinimapIcon( hutMinimapIcon, MinmapIconCreepsStrong, hutX, hutY, 0 ) --показываем на минимапе иконку домика
		LuaCreatureHide( glyphName, true ) -- убираем глиф
		
		AddTriggerEnd( FlagIsCapturedUserFeedback, flagName ) -- спамим на минимап сигнал, что флаг потерян, пишем в чат
	elseif isRaised then -- если флаг поднят
		DebugTrace("[ForestFlagRaised] "..flagName.." is raised")	
		
		LuaCreatureHide( hutName, true ) -- убираем домик крипов
		LuaRemoveMinimapIcon( hutMinimapIcon ) -- убираем иконку домика с минимапа
		LuaCreatureHide( glyphName, false )		 -- ставим на карту спавнер глифов
	end
	
	if GetRaisedForestFlags() == forestFlagsCount then -- если все лесные флаги под контролем игроков, комплитим квест
		CompleteQuest( "raiseForestFlags" )
	end
end

-- подсчитываем количество поднятых флагов и обновляем данные для экрана статистики
function UpdateNatureProgress()
    local flagsTotal, flagsRaised = 2 , 1   -- считаем, что у игрока и у чуди есть по одному "флагу", чтобы процент нашей земли не уходил в ноль и в единицу
    for n, raised in pairs( raisedFlagpoles ) do
        flagsTotal = flagsTotal + 1
        if raised then flagsRaised = flagsRaised + 1 end
    end
    if factionPlayer == FACTION_DOCT then 
        LuaSetNatureProgress( flagsRaised/ flagsTotal, 0 )
    else 
        LuaSetNatureProgress( 0, flagsRaised/ flagsTotal )
    end
end

-- Если флаг в лесу опущен, спавним с некоторой периодичностью крипов, которые будут идти на базу
function SpawnCreepsWhileFlagIsDown( flagName )
	DebugTrace("[SpawnCreepsWhileFlagIsDown] for flag "..flagName)
	local direction = string.sub( flagName, 1, string.find( flagName, '%u') - 1 )
	local n = string.sub( flagName, -1 )
	local spawnerName = tostring(direction).."CreepHutSpawner"..tostring(n)	
	local spawned = {}
	local lastSpawnStep
	local spawnInterval
	if FOREST_CREEP_MIN_SPAWN_INTERVAL == nil then
		spawnInterval = LuaRandom( 25, 45 )	-- случайный интервал, с которым будем спавнить
	else
		spawnInterval = LuaRandom( FOREST_CREEP_MIN_SPAWN_INTERVAL, FOREST_CREEP_MIN_SPAWN_INTERVAL + 20 )	
	end
	
	while not flagsInitCompleted do SleepState() end -- если мы здесь оказались до того, как флаги были инициализированы, ждем
	
	while GetGlobalVar("superabilityUsesCount") ~= 1 do SleepState() end -- ждем до первого взрыва артефакта (до этого не спавним)
	
	while true do
		while raisedFlagpoles[ flagName ] do SleepState() end -- пока флаг поднят, ждем, выходим, если опущен
		DebugTrace("[SpawnCreepsWhileFlagIsDown] flag "..flagName.." is dropped down")
		while not raisedFlagpoles[ flagName ] do 			-- пока флаг опущен
			spawned = SpawnerSpawn( spawnerName, factionEnemy ) -- спавним крипов
			for i = 1,#spawned do LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" ) end	-- вешаем на них бонус от опущенных флагов
			lastSpawnStep = GetGameStep()
			while GetGameStep() - lastSpawnStep < spawnInterval * GetStepsCountInSecond() do SleepState() end -- ждем spawnInterval	
			SleepState()
		end	
		DebugTrace("[SpawnCreepsWhileFlagIsDown] flag "..flagName.." is raised up")		
		SleepState()		
	end
end

-- для зоны polygonName с подзонами areas задается изначальный тип земли newNature
function SetFlagChainNature( polygonName, areas, oldNature, newNature )
	for i=1, #areas do
		LuaChangeNatureMapPolyArea( polygonName, areas[i], oldNature, newNature )
	end
end

-- Запускается в момент захвата флага
function FlagIsCapturedUserFeedback( flagName )
	if flagsInitCompleted then
		local flagX, flagY = LuaUnitGetPosition( flagName )		
		
		LuaCreateMinimapSignal( flagX, flagY ) -- спамим на минимап сигналом
		LuaUnitApplyApplicatorFromUnit( allyHeroes[1],  allyHeroes[1], "FlagIsLostMessageToChat" ) -- пишем в чат сообщение "Флаг потерян"
		--LuaSetHintLine( "flagCaptured", "None" )
		--WaitState(4)
		--LuaSetHintLine( "", "None" )
	end
end

-- Возвращает количество поднятых лесных флагов
function GetRaisedForestFlags()
	local raisedFlags = 0
	for flagName, isRaised in pairs( raisedFlagpoles ) do
		if string.find( flagName, "CreepHutFlag" ) ~= nil and isRaised then
			raisedFlags = raisedFlags + 1
		end
	end
	return raisedFlags
end

-- Отправляет кобольдов отбивать флаги в рамках стандартных волн мобов
-- Набегание начинается не раньше, чем после первого взрыва артефакта
function CaptureForestFlags()
	LuaDebugTrace("STARTED: [CaptureForestFlags]")
	local availableDirections = {}
	local direction = "left"
	local flagName = "leftCreepHutFlag1"
	local hutNumber = 1
	local directions = { left = {1, 2, 3}, right = {1, 2, 3}, up = {1}, down = {1} } -- направления и сопоставление им флагов в лесу. Например с направления left есть доступ к флагам, названия которых начинаются на "left", а заканчиваются на "1", "2" или "3" 
	local simultaneousDirections = 1	
	local minSpawnInterval = 25 
	
	while GetGlobalVar("superabilityUsesCount") ~= 1 do SleepState() end -- ждем до первого взрыва артефакта (до этого не спавним)
	
	while true do
		LuaDebugTrace("DEBUG: [CaptureForestFlags]: Waiting for next wave")
		
		WaitState( math.max( minSpawnInterval, 0 )  + 30 )  -- ждем minSpawnInterval, но не меньше 30-ти секунд

		while ( not GetGlobalVar( "WaveInProgress") ) do -- Если сейчас не время для стандартных волн, ждем
		 SleepState()
		end
		
		LuaDebugTrace("DEBUG: [CaptureForestFlags]: wait completed")
		availableDirections = {}
		
		for directionName, numbers in pairs( directions ) do
			if not forbiddenDirections[directionName] then
				for n=1, #numbers do
					table.insert( availableDirections, {directionName, numbers[n]} )
					LuaDebugTrace("DEBUG: [CaptureForestFlags]: value inserted")
				end
			end
		end
		
        table.sort(availableDirections, function(a, b) return a[1]..tostring(a[2]) < b[1]..tostring(b[2]) end ); -- сортировка массива. Нужно для корректного реконнекта
        
    	LuaDebugTrace("-----------------Available directions array----------------")
		for i=1, #availableDirections do			
			LuaDebugTrace( "direction: "..tostring(availableDirections[i][1])..", number: "..tostring(availableDirections[i][2]) )
		end
		
		if #availableDirections > 0 then
            simultaneousDirections = LuaRandom( 1, math.min( #availableDirections, 3 ) ) -- выбираем случайное направление для спавна и их количество
			for k=1, simultaneousDirections do -- по всем выбранным направлениям
            
				local directionIndex = LuaRandom( 1, #availableDirections )
            
				direction = availableDirections[ directionIndex ][1]
				hutNumber = availableDirections[ directionIndex ][2]
                table.remove( availableDirections, directionIndex )
                
				DebugTrace("[CaptureForestFlags] direction is "..direction..", hut number is "..hutNumber)
				
				local chainName = direction.."CreepHutChain"..hutNumber
				local flagName = direction.."CreepHutFlag"..hutNumber				
				local spawned = SpawnerSpawn( "Kobolds", factionEnemy ) -- спавним кобольдов
				for i=1, #spawned do
					LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" ) -- даем им бонус от опущенных флагов
				end
				local startPositionX, startPositionY = LuaGetScriptArea( direction.."EnemySpawnerArea" ) -- откуда идти
				local destinationX, destinationY = LuaUnitGetPosition( flagName ) -- куда идти
				
				TeleportUnitList( spawned, startPositionX, startPositionY ) 
								
				for i = 1,#spawned do
					LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" )										
					LuaSetCreepBehavior( spawned[i], "MoveTo", destinationX, destinationY, 3, 20 ) -- отправляем кобольдов захватывать флаг
					LuaSetUnitStat( spawned[i], StatMoveSpeed, 50)
					AddTriggerEnd( GoAttackWhenFlagDown, flagName, spawned ) -- Когда флаг будет захвачен, отправляем кобольдов атаковать базу
				end
			end
		end
		minSpawnInterval = minSpawnInterval - 1 -- уменьшаем интервал следующего спавна кобольдов на 1
		SleepState()		
	end
	LuaDebugTrace("FINISHED: [CaptureForestFlags]")
end

-- Заставляет кобольдов идти атаковать базу, когда флаг, к которому они шли, оказался опущен
function GoAttackWhenFlagDown( flagName, unitList )
	LuaDebugTrace("STARTED: [GoAttackWhenFlagDown] for flag "..flagName)
	local targetX, targetY = 0, 0
	
	while raisedFlagpoles[ flagName ] == true do -- пока флаг поднят, ждем
		SleepState()	
		if LuaUnitCheckFlag( flagName, ForbidTakeDamage ) then
			break
		end
	end
	LuaDebugTrace("[GoAttackWhenFlagRaised] flag "..flagName.." is down")

	local dead, exist = false, false
	local destinationX, destinationY = LuaUnitGetPosition( ivaCreep )
	
	for i=1, #unitList do
		dead, exist = LuaUnitIsDead( unitList[i] )
		if not dead and exist then
			LuaSetCreepBehavior( unitList[i], "MoveTo", destinationX, destinationY, 3, 20 ) -- отправляем кобольдов атаковать базу, как только флаг оказался опущен
		end
	end
end


-- Возвращает количество любых поднятых флагов
function GetRaisedFlagsCount()
	local n = 0
	for i,v in pairs( raisedFlagpoles ) do
		if v == true then n = n + 1 end
	end
	LuaDebugTrace("[GetRaisedFlagsCount] raised flags count = "..n)
	return n
end

-- Не используется
function SpawnSupportUnits( supportUnits )
	local directions = GetAvailableDirections()
	local UNITS_FROM_DIRECTION_COUNT = 1
	local spawned = {}
	for k=1, UNITS_FROM_DIRECTION_COUNT do
		for i=1, #directions do
			spawned = SpawnerSpawn( supportUnits[ LuaRandom(1, #supportUnits) ], factionEnemy )
			PushPathAndApplyFlagBonus( spawned, directions[i] )
		end
		WaitState(2)
	end
end