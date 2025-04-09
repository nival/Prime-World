-- Задание "Побей кобольдов". Выдается после взрыва артефакта и 30-ти секундной паузы
function Objective_RecaptureFlags()
	LuaDebugTrace("STARTED: Objective_RecaptureFlags")
	while not flagsInitCompleted do SleepState() end
	
	local REWARD_HERO_PRIME = 500
	local OBJECTIVE_TIME = 90 -- время на выполнение задания. Как только оно заканчивается, задания комплитится
	local supportUnits = {"Sirin1", "Sirin1", "Vodyanoi1", "Assassin1", "Assassin2"} -- юниты, которых можно было бы пускать как поддержку к кобольдам. Временно отключено
		
	AddQuest("defeatKobolds", false, false)
	LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestReceivedEvent")
	AddTriggerEnd( Objective_RecaptureFlagsTimer, OBJECTIVE_TIME) -- вешает в список квестов таймер "до следующей атаки осталось:"
	
	local spawned = {}
	local startPoints = {}
	local spawnerPoints = {}
	local randomPoints = {1,2,3,4,5,6,7,8,9} -- индексы для точек спавна кобольдов
	randomPoints = ShuffleArray( randomPoints ) -- перемешиваем их
	for i=1, 4 do -- spawnerPoints - в этих точках будем спавнить кобольдов, которые будут завхатывать флаги. Всего таких точек 4
		table.insert( spawnerPoints, "flagkillersSpawner"..randomPoints[i] ) -- создаем массив точек спавна кобольдов на базе randomPoints. Имена вида "flagkillersSpawner" - это имена зон на карте.
	end
	PrintArray( spawnerPoints )
	
	
	for i=1, #spawnerPoints do
		local dirX, dirY, r = LuaGetScriptArea( spawnerPoints[i] )
		table.insert(startPoints, {x = dirX, y = dirY })
	end

	--AddTriggerEnd( SpawnSupportUnits, supportUnits  )
    
	SetGlobalVar( "ObjectiveDefeatKobolds_killedKoboldsCount", 0 )	-- счетчик убитых кобольдов
	AddTriggerEnd(StartRecaptureFlags, startPoints ) -- начать захватывать флаги

	local initStep = GetGameStep()
	local totalKobolds = 20
	local timeIsUp = false
	
	while GetGlobalVar("ObjectiveDefeatKobolds_killedKoboldsCount") < totalKobolds do 
		SetQuestProgress( "defeatKobolds", GetGlobalVar("ObjectiveDefeatKobolds_killedKoboldsCount") ) -- выставляем количество убитых кобольдов
		SleepState()
		if GetGameStep() - initStep > OBJECTIVE_TIME * GetStepsCountInSecond() then -- смотрим, не коничлось ли время на задание, если да, то выходим из цикла
			LuaDebugTrace("[Objective_RecaptureFlags] Time is up!")
			timeIsUp = true
			break
		end
	end
	LuaDebugTrace("DEBUG: [Objective_RecaptureFlags]: all kobolds are dead")
	if not IsQuestComplete( "defeatKoboldsTimer" ) then 
        CompleteQuest("defeatKoboldsTimer")
    end
	CompleteQuest("defeatKobolds")		
	if not timeIsUp then -- если успели за 90 секунд
		for i=1, #allyHeroes do
			--LuaHeroAddPrime( allyHeroes[i], REWARD_HERO_PRIME )
			LuaUnitApplyApplicatorFromUnit(allyHeroes[i], allyHeroes[i], "AddNaftaForExplode")
		end
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestCompletedEvent")
		local dead, exist = LuaUnitIsDead( "local" )
		if not dead and exist then
			local x, y = LuaUnitGetPosition( "local" )
			LuaPlaceClientEffect( "fireWork", x, y) 
		end
	else
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent")
	end
end


-- Выставляем кобольдам стартовые точки спавна и отправляем их атаковать ближайший флаг
function StartRecaptureFlags( startPoints )
	local raisedFlagpoles2 = {}
	for k in pairs( raisedFlagpoles ) do table.insert( raisedFlagpoles2, k ) end
	table.sort( raisedFlagpoles2 ) -- сортировка нужна для корректного реконнекта
	
	-- пробегаемся по всем поднятым флагам
    for n = 1, #raisedFlagpoles2 do
        local flagName = raisedFlagpoles2[n]
        local startX, startY = 0, 0
		local flagX, flagY = LuaUnitGetPosition( flagName )
	
        startX, startY = GetNearestPointToPointList( flagX, flagY, startPoints ) -- спавним кобольдов в той точке из startPoints (всего 4), которая ближе всех к данному флагу
        
        DebugTrace("[StartRecaptureFlags] standard flag recapture ("..flagName..") started")
        AddTriggerEnd( SpawnToPointAndGoAttackFlag, "Kobolds", startX, startY, flagName ) -- спавним кобольдов и отправляем атаковать указанный флаг
        WaitState(2)
    end
end

-- Спавним кобольдов в лесу и отправляем их 
function SpawnToPointAndGoAttackFlag( spawnerName, pointFromX, pointFromY, flagName )
	local spawned = SpawnerSpawn( spawnerName, factionEnemy ) -- спавним кобольдов
	local flagX, flagY = LuaUnitGetPosition( flagName )
	
	TeleportUnitList( spawned, pointFromX, pointFromY ) -- отправляем их в стартовую точку
	
	for k = 1,#spawned do
		LuaApplyPassiveAbility( spawned[k], "flagpolesBonus" )	--выдаем бонус от опущенных флагов									
		LuaSetCreepBehavior( spawned[k], "MoveTo", flagX, flagY, 3, 20 ) -- отправляем захватывать флаг
		LuaSetUnitStat( spawned[k], StatMoveSpeed, 50)				
	end
		
	local targetX, targetY = 0, 0
	local targetName = flagName
	local unitList = spawned	
	
	while not UnitsAreDead( unitList ) and GetRaisedFlagsCount() > 0 do -- пока жив кобольд из спавнера и еще есть флаги, которые можно поднять
		while raisedFlagpoles[ targetName ] == true and not UnitsAreDead( unitList ) do -- пока целевой флаг поднят и кобольд жив
			if LuaUnitCheckFlag( targetName, ForbidTakeDamage ) then -- если флаг опущен, выходим 
				LuaDebugTrace("[GoAttackWhenFlagRaised] flag "..flagName.." is invulnerable")
				break
			end
			SleepState()	
		end
		if UnitsAreDead( unitList ) or GetRaisedFlagsCount() == 0 then
			PrintArray( unitList )
			LuaDebugTrace("[SpawnToPointAndGoAttackFlag]: units are dead or no more flags")			
			break
		end
		LuaDebugTrace("[SpawnToPointAndGoAttackFlag] flag "..targetName.." is down")
		
		-- после того как целевой флаг захвачен, формируем новый массив flags, из которого выберем ближайший и отправим кобольда к нему
		local flags = {}
		local flagX, flagY = 0, 0		
		for flagname, isRaised in pairs( raisedFlagpoles ) do
			if isRaised and not LuaUnitCheckFlag(flagname, ForbidTakeDamage) then
				flagX, flagY = LuaUnitGetPosition( flagname )			
				table.insert( flags, {x = flagX, y = flagY, name = flagname} )			
			end
		end	
		
		local units = GetAliveUnits( unitList )
		PrintArray( units )
		local creepX, creepY = LuaUnitGetPosition( units[1] )
		targetX, targetY, targetName = GetNearestPointToPointList( creepX, creepY, flags ) -- ищем ближайший флаг к кобольду
		LuaDebugTrace("[SpawnToPointAndGoAttackFlag]: New target found: targetName = "..targetName..", x = "..targetX..", y = "..targetY)
				
		for k = 1,#units do							
			LuaSetCreepBehavior( units[k], "MoveTo", targetX, targetY, 3, 20 ) -- отправляем к найденному флагу кобольда
		end
		SleepState()
	end
	LuaDebugTrace("[SpawnToPointAndGoAttackFlag] no more flags. Go to attack base")
	
	local dead, exist = false, false
	local destinationX, destinationY = LuaUnitGetPosition( ivaCreep )
	
	-- если флагов больше не осталось и крип жив, он идет атаковать Иву
	for i=1, #unitList do
		dead, exist = LuaUnitIsDead( unitList[i] )
		if not dead and exist then
			LuaSetCreepBehavior( unitList[i], "MoveTo", destinationX, destinationY, 3, 20 )
		end
	end
	WaitForUnitsAreDead( unitList ) -- ждем пока кобольд издохнет
	if not IsQuestActive("defeatKobolds") then return end
	SetGlobalVar("ObjectiveDefeatKobolds_killedKoboldsCount", GetGlobalVar("ObjectiveDefeatKobolds_killedKoboldsCount") + 1)	-- увеличиваем на 1 количество убитых кобольдов
end



-- Вешает в список квестов специальный квест, нужный только для того, чтобы показывать сколько секунд осталось до следующей атаки (или что то же самое до конца задания про отражение атаки кобольдов)
function Objective_RecaptureFlagsTimer( OBJECTIVE_TIME )
	AddQuest("defeatKoboldsTimer", false, false )
	local n = 0
	repeat
		SetQuestParams( "defeatKoboldsTimer", "sec", OBJECTIVE_TIME - n) -- выставляем количество оставшихся секунд
		n =  n + 1
        if IsQuestComplete( "defeatKoboldsTimer" ) then 
            return
        end
		WaitState(1)
	until n == OBJECTIVE_TIME
	CompleteQuest("defeatKoboldsTimer")
end