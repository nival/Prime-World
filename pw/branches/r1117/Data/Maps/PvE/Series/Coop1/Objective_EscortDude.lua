function QuestEscortDude()
	LuaDebugTrace("STARTED: [QuestEscortDude]")
	local ARTIFACT_COUNTER_BONUS = ARTIFACT_COUNTER_BONUS or 30 -- столько очков будет прибавлено к счетчику артефакта в случае выполнения задания
	
	SetGlobalVar( "Quest_escortDude_isEscaped", false )	
				
	local directions = {} -- здесь будем хранить все доступные для отступления беженца направления (те, которые закрыты для крипов)
		
	for direction, isForbidden in pairs( forbiddenDirections ) do
		if isForbidden then
			table.insert( directions, direction )
		end
	end
    table.sort( directions )


	if #directions == 0 then -- беженец может убежать только по "закрытой" для крипов дороге, если такой нет, квест не выдается
		LuaDebugTrace("ERROR! [QuestEscortDude]. No path to escape!")
		return
	end
	
	AddQuest( "escortDude", false, false )	
	LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestReceivedEvent") --выдаем анонсмент "Получено задание"
	-- выбираем тип беженца в зависимости от расы игрока
	local dudeSpawner = "unknown"
	if LuaGetLocalFaction() == FACTION_DOCT then
		dudeSpawner = "dude_doct" --если игрок играет за доктов, ставим на карту доктовского беженца
	else
		dudeSpawner = "dude_adorn" -- если за адорнийцев, то, соответственно, - адорнийского
	end
	
	local direction = directions[ LuaRandom(1, #directions ) ] --выбираем случайное направление из доступных 
	local endPointArea = direction.."EnemySpawnerArea" -- название зоны, которая находится в конце пути на выбранном направлении 
	local endPointX, endPointY = LuaGetScriptArea( endPointArea ) -- координаты этой зоны. В них будет бежать беженец
	
	local startPointX, startPointY = LuaGetScriptArea( direction.."_dudeStartPoint" ) -- позиция зоны, в которой беженец наспавнится.
	-- для каждого направления это своя зона. Все они распложены на базе. 
	local spawned = SpawnerSpawn( dudeSpawner, factionPlayer )
	local dude = spawned[1] 
	
	LuaUnitAddFlag( dude, ForbidDeath ) --временно запрещаем беженцу дохнуть
	LuaSetUnitHealth( dude, 2500 ) -- даем ему побольше здоровья
			
	LuaCreatureTeleportTo( dude, startPointX, startPointY ) -- ставим в стартовую позицию
	AddTriggerEnd( AmbushesChain, direction, dude ) -- запускаем последовательность атак на беженца
	LuaCreateMinimapSignal( startPointX, startPointY ) -- посылаем на минимап сигнал в стартовые координаты беженца
	WaitState(5)
	LuaCreateMinimapSignal( startPointX, startPointY ) -- повторяем сигнал через 5 секунд
	LuaUnitRemoveFlag( dude, ForbidDeath ) -- разрешаем беженцу дохнуть
	
	if UnitIsRealyDead( dude ) then -- если беженец умудрился сдохнуть
		LuaDebugTrace("[CheckDudeStatus] Dude is dead! Objective failed!")
		CompleteQuest( "escortDude" ) -- комплитим квест
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent") -- показываем анонсмент "задание провалено"
		return 
	end
	LuaSetCreepBehavior( dude, "MoveTo",  endPointX, endPointY, 0, 5 )		-- отправляем беженца в конечную точку на выбранном пути
		
	while true do
		if UnitIsRealyDead( dude ) then -- если беженец помер
			LuaDebugTrace("[CheckDudeStatus] Dude is dead! Objective failed!")
			CompleteQuest( "escortDude" ) -- комплитим квест
			LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent") -- показываем анонсмент "задание провалено"
			break
		end
		if DistanceUP( dude, endPointX, endPointY ) < 5 then -- если беженец  добежал
			LuaDebugTrace("[CheckDudeStatus] Dude is successfully escaped! Objective completed!")
			SetGlobalVar( "Quest_escortDude_isEscaped", true )	
			CompleteQuest( "escortDude" ) -- комплитим квест
			LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestCompletedEvent") -- показываем анонсмент "Задание выполнено"
			LuaCreatureHide( dude, true ) -- прячем беженца
			SleepState() 
			LuaKillUnit( dude ) -- убиваем его (да-да, он все равно умрет!)
			for i=1, #allyHeroes do
				LuaUnitApplyApplicatorFromUnit(allyHeroes[i], allyHeroes[i], "AddNaftaForExplode") -- даем героям прайм за выполнение задания
			end
			
			local newArtifactValue = GetGlobalVar( "superability_killsCounter" ) + ARTIFACT_COUNTER_BONUS
			if newArtifactValue > SUPERABILITY_KILLS_COUNTER then newArtifactValue = SUPERABILITY_KILLS_COUNTER end				
			SetGlobalVar("superability_killsCounter", newArtifactValue) 
			
			SetQuestProgress( "chargeArtefact", GetGlobalVar( "superability_killsCounter" ) ) -- добавляем к счетчику артефакта бонусные очки
			local dead, exist = LuaUnitIsDead( "local" )
			if not dead and exist then -- если герой игрока жив
				local x, y = LuaUnitGetPosition( "local" )
				LuaPlaceClientEffect( "fireWork", x, y) --показываем над ним фейерверк
			end
			break
		end
		SleepState()
	end
end

-- управляет цепочкой атак на беженца.
-- если прошло больше 17-ти секунд или беженец вошел в зону засады
-- его атакуют
function AmbushesChain( direction, dude )
	LuaDebugTrace("STARTED: [AmbushesChain] for direction "..direction)
	local waitTime = 17 -- время между спавнами крипов
	local ambushes = {}
	for i=1, 3 do -- выбираем в зависимости от направления 3 зоны, в которых будут спавнится крипы
		ambushes[i] = direction.."_objectiveEscortDudePoint"..tostring(i)
	end	
	local x, y = 0, 0
	for i=1, #ambushes do
		x, y = LuaGetScriptArea( ambushes[i] )
		--while DistanceUP( dude, x, y ) < 22 do SleepState() end
		local timer = 0
		while timer < waitTime do -- пока не прошло время ожидания
			if UnitIsRealyDead( dude ) then -- если беженец издох, выходим из функции
				LuaDebugTrace("[AmbushesChain] dude is dead!")
				return
			end
			if IsUnitInArea( dude, ambushes[i] ) then -- если беженец вошел в зону засады
				break -- выходим из цикла
			end
			timer = timer + GetStepLengthInSeconds()
			SleepState()
		end
		AddTriggerEnd( SpawnAmbushers, ambushes[i], dude )	-- спавним засаду	
	end
	LuaDebugTrace("FINISHED: [AmbushesChain] for direction "..direction)
end


-- спавнит засаду
function SpawnAmbushers( areaName, dude )
	LuaDebugTrace("STARTED: [SpawnAmbushers] for area "..areaName)
	local spawners = {"Kobolds1", "Rogatiki1", "Satyrs1", "Assida2", "Assassin1" } -- из этих спавнеров будут выбираться крипы для атак
	local n = 1
	local spawned = {}
	while not UnitIsRealyDead( dude ) do -- пока беженец жив
		LuaDebugTrace("[SpawnAmbushers] area "..areaName.." spawn number "..n)
		spawned = SpawnerSpawn( spawners[ LuaRandom(1, #spawners)] ) -- спавним случайный спавнер крипов
		for i=1,#spawned do
			LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" ) -- даем им бонус от флагов
		end
		local x, y = LuaGetScriptArea( areaName )
		TeleportUnitList( spawned, x, y ) 
		
		while not UnitIsRealyDead( dude ) do -- пока беженец жив
			local dudeX, dudeY = LuaUnitGetPosition( dude )
			if not UnitIsRealyDead( spawned ) then	-- и пока жив хоть кто-нибудь из наспавнившихся крипов		
				for i=1, #spawned do
					if not UnitIsRealyDead( spawned[i] ) then
						LuaSetCreepBehavior( spawned[i], "MoveTo",  dudeX, dudeY, 1, 5 ) -- бежать к беженцу (при этом они будут его атаковать)
					end
				end
			else
				LuaDebugTrace("[SpawnAmbushers] All creeps are dead!")
				break
			end
			WaitState(4) 
		end
		WaitState(9)
		n = n + 1
	end
	-- если мы здесь, беженец помер
	LuaDebugTrace("[SpawnAmbushers] for area "..areaName..", dude is dead, let's go to the base!")
	if not UnitIsRealyDead( spawned ) then -- если еще есть живые атакующие крипы
		LuaDebugTrace("[SpawnAmbushers] for area "..areaName..", there is someone alive!")
		local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
		for i=1, #spawned do
			if not UnitIsRealyDead( spawned[i] ) then
				LuaSetCreepBehavior( spawned[i], "MoveTo",  ivaX, ivaY, 3, 15 ) -- отправить крипов атаковать базу
				LuaDebugTrace("[SpawnAmbushers] for area "..areaName..", unit "..spawned[i].." goes to iva")
			end
		end
	end
	LuaDebugTrace("FINISHED: [SpawnAmbushers] for area "..areaName)
end 