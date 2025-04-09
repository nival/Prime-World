

--constants
RATS_SPAWNER_PAIRS = { 
	{10,3}, {2,3}, {2,9}, --down
	{3,9}, {3,4}, --left
	{4,5}, {9,5}, {4,7}, {9,7}, -- top
	{7, 8}, {7,10} -- right
	} -- пары спавнеров flagKillersSpawner*
RATS_SPAWNER_PAIRS_COUNT = 4 -- количество пар точек, между которыми будут бегать крысы
RATS_TO_KILL = 20 -- Сколько нужно убить крыс, чтобы выполнить задание
RATS_SPAWN_INTERVAL = 3 --время между спавнами крыс
RATS_OBJECTIVE_TIME = 40 

function QuestRatsInvasion()

	LuaDebugTrace("STARTED: [QuestRatsInvasion]")
	local pairsCopy = CopyArray( RATS_SPAWNER_PAIRS )
	-- выбираем из массива всех пар несколько случайных пар точек, между которыми будут бегать крысы
	LuaRandom( 1, 10 )
	for i = 1, RATS_SPAWNER_PAIRS_COUNT do
		k = LuaRandom( i, #pairsCopy )
		LuaDebugTrace( tostring(i) .."->"..k )
		local tmp = pairsCopy[i]
		pairsCopy[i] = pairsCopy[k]
		pairsCopy[k] = tmp
	end
	
	-- запускаем между выбранными парами "поток" крыс
	for i = 1, RATS_SPAWNER_PAIRS_COUNT do
		if LuaRandom( 1, 10 ) <= 5 then
			AddTriggerEnd( RatsStream, pairsCopy[i][1], pairsCopy[i][2] )
		else 
			AddTriggerEnd( RatsStream, pairsCopy[i][2], pairsCopy[i][1] )
		end
	end
	
	local initStep = GetGameStep()
	local stepsCountInSecond = GetStepsCountInSecond()
	local objectiveTime = RATS_OBJECTIVE_TIME * stepsCountInSecond
	SetGlobalVar( "ratsInvasion_ratsCount", 0 )
	SetGlobalVar( "ratsInvasion_inProgress", 1 )
	
	AddQuest( "ratsInvasion", false, false )	
	AddQuest( "questTimer", false, false )
	LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestReceivedEvent") -- показываем анонсмент "получен квест"
	SetQuestParams( "questTimer", "sec", objectiveTime / stepsCountInSecond )
	
	while objectiveTime > 0 and ( GetGlobalVar( "ratsInvasion_ratsCount" ) < RATS_TO_KILL ) do -- пока время не вышло и не убито достаточное количество крыс
		SleepState()
		objectiveTime = objectiveTime - 1
		if objectiveTime % stepsCountInSecond == 0 then
			SetQuestParams( "questTimer", "sec", objectiveTime / stepsCountInSecond ) -- обновляем счетчик таймера
		end
		SetQuestProgress( "ratsInvasion", GetGlobalVar( "ratsInvasion_ratsCount" ) ) -- обновляем счетчик крыс
	end
	
	--выдача награды героям 
	if GetGlobalVar( "ratsInvasion_ratsCount" ) >= RATS_TO_KILL then -- если задание выполнено
		for i=1, #allyHeroes do
			--LuaHeroAddPrime( allyHeroes[i], 500 ) 
			LuaUnitApplyApplicatorFromUnit(allyHeroes[i], allyHeroes[i], "AddNaftaForExplode") -- выдаем прайм аппликатором, потому что тогда от героя отлетает сообщение, сколько получено прайма
		end
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestCompletedEvent") -- показываем анонсмент "Задание выполнено"
		local dead, exist = LuaUnitIsDead( "local" )
		if not dead and exist then
			local x, y = LuaUnitGetPosition( "local" )
			LuaPlaceClientEffect( "fireWork", x, y) -- если герой жив, то показываем над ним эффект фейерверка
		end
	else -- если задание было провалено
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent") -- выдаем аноснмент "Задание провалено"
	end
	
	SetGlobalVar( "ratsInvasion_inProgress", nil ) 
	SetGlobalVar( "ratsInvasion_ratsCount", nil )
	
	-- очистка после завершения квеста
	CompleteQuest("questTimer")
	CompleteQuest("ratsInvasion")

	LuaDebugTrace("FINISHED: [QuestRatsInvasion]")
end

-- функция создающая поток крыс от одной точки до другой
function RatsStream( fromNum, toNum )
	LuaDebugTrace("STARTED: [RatsStream] "..fromNum.." -> "..toNum)
	
	-- функция склеивающая массивы
	local function MergeArray( arrayFrom, arrayTo )
		for i = 1, #arrayFrom do
			table.insert( arrayTo, arrayFrom[i] )
		end
	end
	
	local fromX, fromY = LuaGetScriptArea( "flagkillersSpawner"..fromNum )
	local toX, toY = LuaGetScriptArea( "flagkillersSpawner"..toNum )

	local creeps = {}
	-- в зависимости от фракции игрока выставляем тип крысы
	local ratFaction = "Doct"
	if LuaGetLocalFaction() == FACTION_DOCT then ratFaction = "Adorn" end
	while GetGlobalVar( "ratsInvasion_inProgress" ) do -- пока задание активно
		local spawned = SpawnerSpawn( "ratInvaders"..ratFaction, factionEnemy ) -- спавним крысу
		MergeArray( spawned, creeps ) -- добавляем всех наспавнихшихся крыс к массиву creeps
		TeleportUnitList( spawned, fromX, fromY ) -- телепортим крыс в точку старта потока
		for i = 1, #spawned do
			LuaSetCreepBehavior( spawned[i], "MoveTo", toX, toY, 1, 1 ) -- отправляем их бежать до точки конца потока
			LuaSubscribeUnitEvent( spawned[i], EventDeath, "OnRatKilled" ) -- в случае смерти крысы, запустить функцию OnRatKilled
			AddTriggerEnd( RemoveRat, spawned[i], toX, toY ) -- запускаем функцию, которая удалит крысу, когда она добежит до конечной точки
		end
				
		local waitTimer = RATS_SPAWN_INTERVAL
		while GetGlobalVar( "ratsInvasion_inProgress" ) and waitTimer > 0 do
			SleepState()
			waitTimer = waitTimer - GetStepLengthInSeconds()
		end
	end

	-- cleanup rats
	creeps = GetOnlyAliveUnits( creeps )
	for i = 1, #creeps do
		LuaKillUnit( creeps[i] )
	end
	
	LuaDebugTrace("FINISHED: [RatsStream] "..fromNum.." -> "..toNum)
end 

-- Функция удаляющая крысу, когда она добегает до цели
function RemoveRat( rat, toX, toY )	
	LuaDebugTrace("STARTED: [RemoveRat] for "..rat..", x = "..toX..", y = "..toY)
	while true do
		if UnitIsRealyDead( rat ) then 
			LuaDebugTrace("[RemoveRat] "..rat.." is dead ") 
			return
		end
		if GetGlobalVar( "ratsInvasion_inProgress" ) ~= 1 then 
			LuaDebugTrace("[RemoveRat] for rat "..rat..". ratsInvasion_inProgress = "..tostring(GetGlobalVar( "ratsInvasion_inProgress" ))) 
			return
		end
		if DistanceUP( rat, toX, toY ) < 3 then -- если до конечной точки осталось меньше 3-х метров
			LuaDebugTrace("[RemoveRat] rat "..rat.." is near to destination" )
			LuaForceAnimation( rat, "unsummon", 1 ) -- запускаем анимацию ансаммона
			while not UnitIsRealyDead( rat ) and DistanceUP( rat, toX, toY ) > 1 do SleepState() end -- крыса продолжает бежать, проигрывая анимацию ансаммона, пока до цели не окажется меньше метра, 
			LuaDebugTrace("[RemoveRat] rat "..rat.." is hidden and killed" )
			--LuaCreatureHide( rat, true )
			LuaUnsubscribeUnitEvent( rat,  EventDeath ) -- отписываемся от функции, запускаемой при смерти крысы
			LuaKillUnit( rat ) --убиваем крысу
			break
		end
		SleepState()
	end
	LuaDebugTrace("FINISHED: [RemoveRat] for "..rat..", x = "..toX..", y = "..toY)
end

-- функция, которая запускается при смерти крысы
-- она считает, сколько крыс убили игроки
function OnRatKilled( rat )
	LuaDebugTrace("OnRatKilled: killed "..rat )
	if GetGlobalVar( "ratsInvasion_inProgress" ) then
		IncGlobalVar( "ratsInvasion_ratsCount" ) -- увеличиваем значение переменной ratsInvasion_ratsCount, в которой мы храним количество убитых игроками крыс
	end
end