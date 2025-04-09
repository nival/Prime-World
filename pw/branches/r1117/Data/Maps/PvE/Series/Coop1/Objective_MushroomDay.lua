
-- Отображает счетчик времени в интерфейсе квестов. Технически - просто еще один квест "questTimer",
-- который отображает время. Вызывается в функции QuestLittleBoroviks()
-- quest - имя квеста, duration - продолжительность квеста в секундах
function TimerQuestMushroomDayUpdate( quest, duration )
	while IsQuestActive( quest ) and duration >= 0 do -- пока квест активен и время не вышло
		SetQuestParams( quest, "sec", duration) -- выставляем время 
		WaitState( 1 ) -- ждем секунду
		duration = duration - 1 -- уменьшаем время на секунду
	end
	SetGlobalVar("Quest_mushroomDay_timeIsUp", true) 
end

-- Выдаем квест, контролируем его состояние, комплитим или фейлим его.
function QuestLittleBoroviks()
	LuaDebugTrace("STARTED: [QuestLittleBoroviks]")
	local randomPointsIndexes = {}
	local QUEST_DURATION = 120 -- продолжительность квеста
	local TOTAL_BOROVIKS = 10 -- сколько всего боровиков будет спавниться
	local ARTIFACT_COUNTER_BONUS = ARTIFACT_COUNTER_BONUS or 20 -- сколько очков будет прибавлено к счетчику артефакта
	--local REWARD_HERO_PRIME = 500 -- награда герою за выполнение квеста
	
	AddQuest( "mushroomDay", false, false ) -- выдаем квест про боровиков
	AddQuest( "questTimer", false, false )	-- выдаем дополнительный квест-таймер
	SetQuestParams( "questTimer", "sec", QUEST_DURATION ) -- передаем квесту-таймеру параметры
	LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestReceivedEvent") -- показываем аноносмент "получено задание"
	
	AddTriggerEnd( TimerQuestMushroomDayUpdate, "questTimer", QUEST_DURATION ) -- Запускаем функцию, которая будет убавлять счетчик времени в квесте-таймере
	
	SetGlobalVar( "Quest_mushroomDay_deadBoroviks", 0 ) -- счетчик дохлых боровиков
	SetGlobalVar( "Quest_mushroomDay_timeIsUp", false ) -- переменная для проверки того, не кончилось ли время квеста
	SetGlobalVar( "Quest_mushroomDay_timeToAttackBase", false ) 
	--AddTriggerEnd( SetGlobalVarWhenTimeIsUp, "Quest_mushroomDay_timeIsUp", QUEST_DURATION, true )
	
	for i=1, 28 do randomPointsIndexes[i] = i end -- заполняем массив randomPointsIndexes значениями от 1 до 28
	randomPointsIndexes = ShuffleArray( randomPointsIndexes ) -- перемешиваем его
	local tmp = CopyArray( randomPointsIndexes ) -- копируем его во временный массив tmp
	randomPointsIndexes = {} -- обнуляем исходный массив randomPointsIndexes
	for i=1, TOTAL_BOROVIKS do randomPointsIndexes[i] = tmp[i] end	-- теперь суем в него столько значений из tmp, сколько у нас боровиков
	table.sort( randomPointsIndexes ) -- сортируем (чтобы не было ассинков)
	
	
	for i=1, TOTAL_BOROVIKS do
		AddTriggerEnd( SpawnLittleBoroviks, randomPointsIndexes[i] ) -- спавним боровика в каждой из выбранных рандомных точек
	end
	
	local superabilityUsesCounter = GetGlobalVar( "superabilityUsesCount" )	
	while true do
		if GetGlobalVar( "Quest_mushroomDay_deadBoroviks" ) == TOTAL_BOROVIKS or GetGlobalVar( "superabilityUsesCount" ) > superabilityUsesCounter  then -- если все наспавнившиеся боровики перебиты
			DebugTrace("[QuestLittleBoroviks]: objective completed")
			CompleteQuest( "mushroomDay" ) -- комплитим квест
			CompleteQuest( "questTimer" ) -- и квест-таймер тоже комплитим
			LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestCompletedEvent") -- показываем анонсмент "задание выполнено"
			for i=1, #allyHeroes do
				--LuaHeroAddPrime( allyHeroes[i], REWARD_HERO_PRIME )
				LuaUnitApplyApplicatorFromUnit(allyHeroes[i], allyHeroes[i], "AddNaftaForExplode") -- ВЫДАЕМ каждому герою прайм
			end
			
			local newArtifactValue = GetGlobalVar( "superability_killsCounter" ) + ARTIFACT_COUNTER_BONUS -- добавляем к счетчику артефакта бонусные очки
			if newArtifactValue > SUPERABILITY_KILLS_COUNTER then newArtifactValue = SUPERABILITY_KILLS_COUNTER end	-- если вдруг получилось больше 100, приравниваем счетчик артефакта 100		
			SetGlobalVar("superability_killsCounter", newArtifactValue)
			
			SetQuestProgress( "chargeArtefact", GetGlobalVar( "superability_killsCounter" ) ) -- выставляем в интерфейсе новое значение счетчика артефакта
			local dead, exist = LuaUnitIsDead( "local" )
			if not dead and exist then -- если герой игрока жив
				local x, y = LuaUnitGetPosition( "local" )
				LuaPlaceClientEffect( "fireWork", x, y) --показать над ним фейерверк
			end
			break
		end
		if GetGlobalVar( "Quest_mushroomDay_timeIsUp" ) == true then -- если время квеста вышло или рванул артефакт
			DebugTrace("[QuestLittleBoroviks]: objective failed")
			SetGlobalVar( "Quest_mushroomDay_timeToAttackBase", true )			
			CompleteQuest( "mushroomDay" ) -- фейлим основной квест
			CompleteQuest( "questTimer" )	-- и квест-таймер тоже фейлим
			LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent") -- показываем анонсмент "задание провалено"
			break -- выходим из цикла
		end
		SleepState()
	end
end

-- спавнит боровика в точке forestRandomPoint + pointIndex. Например,
-- если в pointIndex было передано 13, то боровик наспавнится в точке forestRandomPoint13
-- далее следит за его судьбой. Если боровик убит, обновляет счетчик квеста, если время квеста вышло,
-- отправляет боровика в атаку на базу.
function SpawnLittleBoroviks( pointIndex )
	LuaDebugTrace("STARTED [SpawnLittleBoroviks]: for point "..pointIndex)
	local x, y = LuaGetScriptArea( "forestRandomPoint"..pointIndex ) -- получаем координаты точки
	local spawned = SpawnerSpawn( "LittleBorovik", factionEnemy ) -- спавним боровика
	local ivaX, ivaY = LuaUnitGetPosition( ivaCreep ) -- сюда будем отправлять для атаки на базу
	TeleportUnitList( spawned, x, y ) -- ставим боровика в точку
	--LuaSetCreepBehavior( spawned[1], "MoveTo", x, y, 3, 10 )
	--LuaSetCreepBasePlace( spawned[1], x, y )
	LuaUnitAddFlag( spawned[1], ForbidAttack + ForbidAutoAttack ) -- запрещаем ему атаковать
	AddTriggerEnd( Migration, spawned[1] )	-- запускаем функцию, которая будет заставлять боровика менять позицию.
	while true do
		if UnitIsRealyDead( spawned[1] ) then -- если боровик помер			
			SetGlobalVar( "Quest_mushroomDay_deadBoroviks", GetGlobalVar( "Quest_mushroomDay_deadBoroviks" ) + 1 )	
			SetQuestProgress( "mushroomDay", GetGlobalVar( "Quest_mushroomDay_deadBoroviks" ) ) -- обновляем счетчик убитых боровиков в квесте
			LuaDebugTrace("[SpawnLittleBoroviks] "..spawned[1].." is dead. Dead boroviks count = "..GetGlobalVar( "Quest_mushroomDay_deadBoroviks" ))
			break
		end
		if GetGlobalVar( "Quest_mushroomDay_timeToAttackBase" ) then --если квест провален и пора атаковать базу
			LuaUnitRemoveFlag( spawned[1], ForbidAttack + ForbidAutoAttack ) -- разрешаем боровику атаковать
			LuaReplaceCreep( spawned[1], "bigBorovik", factionEnemy ) -- заменяем его на большого боровика
			UpgradeCreepStats( spawned[1] ) -- апгрейдим ему статы, в зависимости от сложности
			LuaSetCreepBehavior( spawned[1], "MoveTo", ivaX, ivaY, 1, 20 ) -- отправляем его атаковать базу
			LuaDebugTrace("[SpawnLittleBoroviks] unit "..spawned[1].." goes to base")
			break
		end
		SleepState()
	end
	LuaDebugTrace("FINISHED [SpawnLittleBoroviks]: for point "..pointIndex)
end

-- заставляет боровика периодически менять позицию. 
-- раз в 20 секунд боровик бежит, к ближайшей
-- точке из всех доступных на карте точек с именами вида forestRandomPoint<number>
function Migration( borovik )
	LuaDebugTrace("STARTED [Migration] for "..borovik)
	local points = {}
	local pointX, pointY = 0,0
	local borovikX, borovikY = LuaUnitGetPosition( borovik )	
	local newPointX, newPointY = 0, 0
	
	while IsQuestActive( "mushroomDay" ) do -- пока квест активен
		WaitState( 20 ) --ждем 20 секунд
		
		if UnitIsRealyDead( borovik ) or not IsQuestActive( "mushroomDay" ) then -- если боровик помер или квест завершился, выходим
			LuaDebugTrace("[Migration] borovik "..borovik.." is dead or quest is not active")
			return 
		end
				
		points = {} -- в points храним все доступные точки вида "forestRandomPoint"<number>, кроме точки, в которой стоит боровик
		for i=1, 28 do
			pointX, pointY = LuaGetScriptArea( "forestRandomPoint"..i) 
			if DistanceUP( borovik, pointX, pointY ) > 5 then
				table.insert( points, {x = pointX, y = pointY} )
			end
		end		
		
		newPointX, newPointY = GetNearestPointToPointList( borovikX, borovikY, points )	-- находим ближайшую точку к позиции боровика	
		LuaDebugTrace("[Migration] "..borovik.." goes to point "..newPointX..", "..newPointY)
		
		-- пока боровик жив и пока  расстояние до новой позиции меньше 4 и пока квест активен
		while not UnitIsRealyDead( borovik ) and DistanceUP( borovik, newPointX, newPointY ) > 4 and IsQuestActive( "mushroomDay" ) do
			LuaCreatureMoveTo( borovik, newPointX, newPointY, 0 ) -- заставляем боровика бежать к новой позиции
			WaitState(1)
		end
		SleepState()
	end
	LuaDebugTrace("FINISHED [Migration] for "..borovik)
end