function QuestThreeFatman()
	local randomPointsIndexes = {}
	local FATMEN_COUNT = 3 -- количество толстяков
	local ARTIFACT_COUNTER_BONUS = ARTIFACT_COUNTER_BONUS or 20 -- какое количество очков к счетчику артефакта следует прибавить в случае выполнения задания	

	
	AddQuest( "threeFatmen", false, false )
	--AddTriggerEnd( HintLineWait, "objectiveActive", 4 )
	LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestReceivedEvent") -- показываем анонсмент "Получено задание"
	
	SetGlobalVar( "Quest_threeFatmen_deadFatmen", 0 ) 
	SetGlobalVar( "Quest_threeFatmen_escapedFatmen", 0 )
		
	randomPointsIndexes = {18, 17, 25, 4, 5, 7, 6, 14, 12, 16} -- индексы точек, в которых могут наспавнится толстяки. Точки - это зоны на карте с названиями вида forestRandomPoint<number>
	randomPointsIndexes = ShuffleArray( randomPointsIndexes )	-- перемешиваем массив
	local tmp = CopyArray( randomPointsIndexes )
	randomPointsIndexes = {}
	for i=1, FATMEN_COUNT do randomPointsIndexes[i] = tmp[i] end	
	table.sort( randomPointsIndexes )
	
	for i=1, FATMEN_COUNT do
		AddTriggerEnd( SpawnFatman, randomPointsIndexes[i] ) -- запускаем функцию, которая наспавнит толстяка
	end
	
	while true do
		if GetGlobalVar( "Quest_threeFatmen_deadFatmen" ) == FATMEN_COUNT and GetGlobalVar( "Quest_threeFatmen_escapedFatmen" ) == 0 then -- если задание выполнено (все 3 толстяка уничтожены)
			CompleteQuest( "threeFatmen" )
			CompleteQuest( "questTimer" )
			LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestCompletedEvent") -- показываем анонсмент "Получено задание"
			for i=1, #allyHeroes do
				LuaUnitApplyApplicatorFromUnit(allyHeroes[i], allyHeroes[i], "AddNaftaForExplode") -- выдаем каждому герою 500 прайма за выполнение задания
			end
			
			local newArtifactValue = GetGlobalVar( "superability_killsCounter" ) + ARTIFACT_COUNTER_BONUS -- новое значение для счетчика заряженности артефакта
			if newArtifactValue > SUPERABILITY_KILLS_COUNTER then newArtifactValue = SUPERABILITY_KILLS_COUNTER end	-- если новое значение оказалось больше 100, приравнять его 100			
			SetGlobalVar("superability_killsCounter", newArtifactValue)
			
			SetQuestProgress( "chargeArtefact", GetGlobalVar( "superability_killsCounter" ) ) --выставить в интерфейсе квеста про зарядку артефакта новое значение для счетчика
			local dead, exist = LuaUnitIsDead( "local" )
			if not dead and exist then
				local x, y = LuaUnitGetPosition( "local" )
				LuaPlaceClientEffect( "fireWork", x, y) -- вешаем над героем эффект фейерверка
			end
			return
		end
		if GetGlobalVar( "Quest_threeFatmen_escapedFatmen" ) + GetGlobalVar( "Quest_threeFatmen_deadFatmen" ) >= FATMEN_COUNT then -- если задание провалено (все уцелевшие толстяки смогли уйти с карты)
			--AddTriggerEnd( HintLineWait, "objectiveFailed", 4 )
			CompleteQuest( "threeFatmen" )
			CompleteQuest( "questTimer" )
			LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent") --показываем анонсмент "Задание провалено"
			return
		end
		SleepState()
	end
end

-- если рядом с толстяком нет ни одного героя
-- спавнить периодически сигнал на минимапе
function SpawnSignalOnMinimap( period, unit )
	for i=1, 3 do
		if UnitIsRealyDead( unit ) then break end
		local x, y = LuaUnitGetPosition( unit )		
		local near = false
		for i=1, #allyHeroes do		
			local dead, exist = LuaUnitIsDead( allyHeroes[i] )
			if not dead and exist then
				if DistanceUU( allyHeroes[i], unit ) <= 10 then
					near = true
					break
				end
			end
		end
		if not near then
			LuaCreateMinimapSignal( x, y )		
		end
		WaitState( period )
	end
end

-- функция, которая спавнит толстяка,
-- отправляет его убегать с карты и следит за его успехами
function SpawnFatman( pointIndex )
	LuaDebugTrace("STARTED: [SpawnFatman] for point "..pointIndex )
	local x, y = LuaGetScriptArea( "forestRandomPoint"..pointIndex )-- координаты случайной точки на карте, откуда толстяк начнет свой путь
	local spawned = SpawnerSpawn( "LeshijBig", factionEnemy ) -- спавним толстяка
	local fatman = spawned[1] -- в этом спавнере только 1 крип, так что наш толстяка это 1-е значение в массиве 
	LuaApplyPassiveAbility( fatman, "flagpolesBonus" ) -- выдаем бонус от флагов
	LuaUnitAddFlag( fatman, ForbidAutoAttack + ForbidAttack + ForbidSelectTarget ) -- запрещаем толстяку атаковать
	LuaCreatureTeleportTo( fatman, x, y ) -- отправляем его в его точку, откуда он выйдет в поход
	AddTriggerEnd( SpawnSignalOnMinimap, 10, fatman  )	-- спавним на минимап сигналом, если рядом с толстяком нет ни одного героя
	
	local directions = GetAvailableDirections()
	
	-- выбираем точку, в которую будет убегать толстяк
	local escapePoints= {} 
	for i=1, #directions do
		local pointName = directions[i].."EnemySpawnerArea"
		local pointX, pointY = LuaGetScriptArea( pointName )
		local pathName = directions[i].."Path"
		escapePoints[i] = {name = pointName, x = pointX, y = pointY, path = pathName} -- кладем в массив escapePoints координаты всех конечных точек дорог на карте
	end
	local escapePointX, escapePointY, escapePointName, escapePath = GetNearestPointToPointList( x, y, escapePoints ) --выбираем из них ближайшую к толстяку (геометрически ближайшую)
	
	AddTriggerEnd( RemoveFatmanWhenHeEscapes, fatman, escapePointX, escapePointY, escapePath ) -- запускаем функцию, которая удалит толстяка, когда он дойдет до финальной точки своего пути
	WaitState(10) -- толстяк ждет 10 секунд перед тем, как пойти (дает героям фору)
	if UnitIsRealyDead( fatman ) then -- если он вдруг помер за эти 10 секунд
		LuaDebugTrace("[SpawnFatman] fatman "..fatman.." is dead!")
		SetGlobalVar( "Quest_threeFatmen_deadFatmen", GetGlobalVar( "Quest_threeFatmen_deadFatmen" ) + 1 )--инкрементим количество уничтоженных толстяков
		SetQuestProgress( "threeFatmen", GetGlobalVar( "Quest_threeFatmen_deadFatmen" ) ) -- выставляем в интерфейсе обновленное значение количества уничтоженных толстяков
		LuaDebugTrace("[SpawnFatman] Quest_threeFatmen_deadFatmen = "..GetGlobalVar( "Quest_threeFatmen_deadFatmen" ))
		return -- выходим
	end
	LuaSetCreepBehavior( fatman, "MoveTo",  escapePointX, escapePointY, 0) -- отправляем толстяка в его точку убегания
	
	while true do 
		if UnitIsRealyDead( fatman ) then -- если толстяк был уничтожен
			LuaDebugTrace("[SpawnFatman] fatman "..fatman.." is dead!")
			SetGlobalVar( "Quest_threeFatmen_deadFatmen", GetGlobalVar( "Quest_threeFatmen_deadFatmen" ) + 1 ) --инкрементим количество уничтоженных толстяков
			SetQuestProgress( "threeFatmen", GetGlobalVar( "Quest_threeFatmen_deadFatmen" ) ) -- выставляем в интерфейсе обновленное значение количества уничтоженных толстяков
			LuaDebugTrace("[SpawnFatman] Quest_threeFatmen_deadFatmen = "..GetGlobalVar( "Quest_threeFatmen_deadFatmen" ))
			break --выходим
		end
		if not IsQuestActive( "threeFatmen" ) then -- если квест завершен
			LuaDebugTrace("[SpawnFatman] quest threeFatmen is not active!")
			LuaKillUnit( fatman ) -- убиваем толстяка
			break --выходим
		end
		SleepState()
	end
end

-- функция, удаляющая толстяка с карты, когда он доходит до конца своего пути
function RemoveFatmanWhenHeEscapes( fatman, escapePointX, escapePointY, escapePath )
	LuaDebugTrace("STARTED: [RemoveFatmanWhenHeEscapes] for "..fatman)
	while not UnitIsRealyDead( fatman ) and IsQuestActive( "threeFatmen") do -- пока толстяк жив
		if DistanceUP( fatman, escapePointX, escapePointY ) < 7 then --если до финальной точки осталось меньше 7-и метров
			LuaDebugTrace("[RemoveFatmanWhenHeEscapes] "..fatman.." escapes")
			local fatmanEscape = true	
			LuaCreatureHide( fatman, true ) --прячем толстяка
			SetGlobalVar( "Quest_threeFatmen_escapedFatmen", GetGlobalVar( "Quest_threeFatmen_escapedFatmen") + 1 ) --инкрементим количество убежавших толстяков
			AddTriggerEnd( SpawnLeshijNextWave, escapePointX, escapePointY, escapePath ) -- запускаем функцию, которая будет спавнить свирепейников на направлении, куда убежал толстяк
			break
		end
		SleepState()
	end
	LuaDebugTrace("FINISHED: [RemoveFatmanWhenHeEscapes] for "..fatman)
end

-- функция, которая спавнит свирепейников на направлении, куда смог убежать толстяк
function SpawnLeshijNextWave( escapePointX, escapePointY, escapePath )
	LuaDebugTrace("STARTED: [SpawnLeshijNextWave] for point "..escapePointX..", "..escapePointY )
	local leshij = {"Leshij2", "Leshij1"} -- выбираем 1 из этих спавнеров для спавна
	local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
	for i=1, 3 do -- спавним 3 раза
		WaitState(20) -- каждые 20 секунд
		if GetGlobalVar("WaveInProgress") then 
			spawned = SpawnerSpawn( leshij[ LuaRandom(1,2) ], factionEnemy )
			TeleportUnitList( spawned, escapePointX, escapePointY )
			for i=1, #spawned do
				LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" )
				LuaSetCreepBehavior( spawned[i], "PathMove", escapePath, 20 ) 
			end
		end		
	end
	LuaDebugTrace("FINISHED: [SpawnLeshijNextWave] for point "..escapePointX..", "..escapePointY )
end