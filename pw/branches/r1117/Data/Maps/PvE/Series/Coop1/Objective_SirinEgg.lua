
--constants
 EGGS_TOTAL = 3 -- сколько всего гнезд с яйцами
 EGG_GUARDS_INITIAL = "SirinHealer" -- имя спавнера, который будет использоваться для охраны яиц
 EGG_GUARDS = { Vodyanoi1 = 1, DemolitionMan1 = 1, Assassin1 = 1, Assassin2 = 1, Sirin1 = 3 } -- из этих спавнеров будут выбираться крипы для преследования героя, утащившего яйцо
 EGG_GUARDS_SPAWN_INTERVAL = 9 -- интервал времени между спавнами крипов, которые должны преследовать героя, стащившего яйцо
 SIRIN_QUEST_OBJECTIVE_TIME = 100 -- продолжительность квеста
 
 function QuestSirinEgg()
 
	LuaDebugTrace("STARTED: [QuestSirinEgg]")
 
	local eggs = {}
	local randomPoints = {1,2,3,4,5,6,7,8,9} -- индексы для точек спавна кобольдов
	randomPoints = ShuffleArray( randomPoints ) -- перемешиваем их
	
	for i=1, EGGS_TOTAL do 
		local dirX, dirY = LuaGetScriptArea( "flagkillersSpawner"..randomPoints[i] ) --выбираем случайную точку для спавна яйца
		local name =  "SirinEgg"..tostring(i) -- присваиваем ей имя
		eggs[ name ] = {x = dirX, y = dirY } -- добавляем в массив eggs координаты данной точки с именем name
		if not LuaIsObjectExists( name ) then 
			LuaCreateGlyph( name, "SirinEgg", dirX , dirY ) -- создаем яйцо в этой точке
		end
		LuaCreatureHide( name, false ) 
		AddTriggerEnd( SpawnSirinEggGuards, name ) -- запускаем функцию, которая будет спавнить крипов, защищающих яйцо
	end
	SetGlobalVar( "sirinEgg_eggPositions", eggs ) -- создаем глобальный массив, в котором будем хранить имена точек, в которых наспавнились яйца и их координаты
	local EggEffects = {}
	SetGlobalVar( "Egg_effects", EggEffects)
	
	for i=1, #allyHeroes do
		LuaSubscribeUnitEvent( allyHeroes[i], EventPickup, "OnSirinEggPickup" ) -- подписываемся на функцию OnSirinEggPickup, которая запускается при подборе яйца
	end
	
	local initStep = GetGameStep()
	local stepsCountInSecond = GetStepsCountInSecond()
	local objectiveTime = SIRIN_QUEST_OBJECTIVE_TIME * stepsCountInSecond
	SetGlobalVar( "sirinEgg_takenCount", 0 ) -- здесь храним количество собранных яиц
	
	AddQuest( "sirinEggs", false, false )	
	AddQuest( "questTimer", false, false )
	LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestReceivedEvent") -- показываем анонсмент "Получено задание"
	
	--AddTriggerEnd( HintLineWait, "objectiveActive", 4 )
	SetQuestParams( "questTimer", "sec", objectiveTime / stepsCountInSecond ) -- выдаем дополнительный квест, в котором показываем каунтер с количеством секунд, оставшихся до конца задания
	
	while objectiveTime > 0 and ( GetGlobalVar( "sirinEgg_takenCount" ) < EGGS_TOTAL ) do -- пока время не вышло и яйца не собраны
		SleepState()
		objectiveTime = objectiveTime - 1
		if objectiveTime % stepsCountInSecond == 0 then
			SetQuestParams( "questTimer", "sec", objectiveTime / stepsCountInSecond ) -- обновляем счетчик секунд в интерфейсе квеста
		end
		SetQuestProgress( "sirinEggs", GetGlobalVar( "sirinEgg_takenCount" ) ) -- выставляем значения для количества собранных яиц в интерфейсе квеста
	end
	
	--выдача награды героям 
	if GetGlobalVar( "sirinEgg_takenCount" ) >= EGGS_TOTAL then --если задание выполнено
		SetGlobalVar ("sirinEgg_QuestWin", 1) -- запоминаем, что квест с Сирин выполнен
		for i=1, #allyHeroes do
			--LuaHeroAddPrime( allyHeroes[i], 500 )
			LuaUnitApplyApplicatorFromUnit(allyHeroes[i], allyHeroes[i], "AddNaftaForExplode") -- выдаем прайм героям
		end
	
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestCompletedEvent") --показываем анонсмент "Задание выполнено"
		--AddTriggerEnd( HintLineWait, "objectiveCompleted", 4 )
		local dead, exist = LuaUnitIsDead( "local" )
		if not dead and exist then
			local x, y = LuaUnitGetPosition( "local" )
			LuaPlaceClientEffect( "fireWork", x, y) --показываем эффект фейерверка
		end
	else -- если задание провалено
		LuaUnitApplyApplicatorFromUnit(allyHeroes[1], allyHeroes[1], "QuestFailedEvent") --выдаем аноснмент "Задание провалено"
		SetGlobalVar ("sirinEgg_QuestFail", 1) -- запоминаем, что квест с Сирин провален
	end
	
	-- очистка после завершения квеста
	CompleteQuest("questTimer")
	CompleteQuest("sirinEggs")
	EggEffects = GetGlobalVar( "Egg_effects" )
	
	for egg, pos in pairs( eggs ) do	
		if LuaIsObjectExists( egg ) then
			LuaCreatureHide( egg, true );
		end
	end
	WaitState( 0.5 )
	for i,v in pairs( EggEffects ) do LuaRemoveStandaloneEffect( v ) end
	
	
	

	for i=1, #allyHeroes do
		LuaUnsubscribeUnitEvent( allyHeroes[i], EventPickup )
	end
	
	SetGlobalVar( "sirinEgg_eggPositions", nil )
	SetGlobalVar( "sirinEgg_takenCount", nil )
	
	LuaDebugTrace("FINISHED: [QuestSirinEgg]")
end


-- Функция, которая спавнит охрану яйца и крипов, которые будут преследовать
-- похитителя яйца
function SpawnSirinEggGuards( eggName )
	LuaDebugTrace("STARTED: [SpawnSirinEggGuards] for egg"..eggName)
	
	local function MergeArray( arrayFrom, arrayTo )
		for i = 1, #arrayFrom do
			table.insert( arrayTo, arrayFrom[i] )
		end
	end
	
	local eggs = GetGlobalVar( "sirinEgg_eggPositions" )
	local eggX, eggY = eggs[ eggName ].x, eggs[ eggName ].y
	local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
	
	local guards = {}
	while true do 
		local creeps = {}
		local allCreeps = {}
		local spawned = {}
		local deadGuards = 0 -- в этой переменной храним количество убитых крипов из спавнера охранников яйца
		 -- считаем, сколько охранников было уничтожено.
		local primeCount = 5 -- награда за убийство крипа в прайме.
		for i=1, #guards do
			if UnitIsRealyDead( guards[i] ) then
				deadGuards = deadGuards + 1
			end
		end
		if deadGuards == #guards or not AreUnitsNearPoint( guards, eggX, eggY, 12 ) then -- если вся охрана уничтожена или охрана убежала дальше чем на 12 метров
			spawned = SpawnerSpawn( EGG_GUARDS_INITIAL, factionEnemy ) -- спавнить новую охрану
			guards = CopyArray( spawned ) 
			LuaDebugTrace("[SpawnSirinEggGuards] init guards spawned for egg "..eggName)
			TeleportUnitList( spawned, eggX, eggY )
			for i = 1, #spawned do
				LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" )	-- выдаем юнитам бонус от флагов
				ChangePrimeCount ( spawned[i], primeCount) -- меняем награду, за их убийство	
				LuaSetCreepBehavior( spawned[i], "MoveTo", eggX, eggY, 7, 7 ) -- сторожим яйцо
			end
			MergeArray( spawned, creeps ) -- в creeps храним всех живых наспавнихшихся крипов
			MergeArray( spawned, allCreeps ) -- в allCreeps храним всех наспавнихшихся крипов
		end
		
		while not GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].carrier do -- пока кто-то несет яйцо
			SleepState()
			if not GetGlobalVar( "sirinEgg_eggPositions" ) then --если задание закончилось
				for i = 1, #allCreeps do -- для всех крипов
					if not UnitIsRealyDead( allCreeps[i] ) then -- кто не помер
						LuaSetCreepBehavior( allCreeps[i], "MoveTo", ivaX, ivaY, 3, 20 ) --отправить атаковать Иву
						LuaDebugTrace("[AttackBaseAfterTargetDeath] goto iva " .. tostring(i))
						LuaKillUnit( allCreeps[i] ) 
					end
				end		
				LuaDebugTrace("[AttackBaseAfterTargetDeath]sirinEgg_eggPositions return 1 creeps=" .. tostring(#allCreeps))
				return 
			end;
		end
		LuaDebugTrace("SirinEgg: guards start hunting egg carrier "..GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].carrier );
		local hero = GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].carrier
		local eggFlags = ForbidAttack+Forbid_Ability1+Forbid_Ability2+Forbid_Ability3+Forbid_Ability4+ForbidUseConsumables+ForbidUseTalents+ForbidMoveSpecial
		
		creeps = GetOnlyAliveUnits( creeps )
		
		-- функция, определяющая является ли данный крип охранником яйца (а не преследователем)
		local function IsGuard( unit, guardUnits )
			local isGuard = false
			for k=1, #guardUnits do
				if unit == guardUnits[k] then 
					isGuard = true 
					LuaDebugTrace("SirinEgg: [IsGuard]: " ..unit)
					break
				end
			end
			return isGuard
		end
		
		for i = 1, #creeps do
			LuaSetCreepBehavior( creeps[i], "Chase", GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].carrier, 10, 5 ) -- Отправляем крипов преследовать героев 						
		end
		
		for i=1, #allCreeps do
			local dead, found = LuaUnitIsDead( allCreeps[i] )
			if not dead then
				AddTriggerEnd( AttackBaseAfterTargetDeath, allCreeps[i], hero, eggX, eggY, IsGuard( allCreeps[i], guards ), eggFlags ) -- запускаем функцию, которая отправит всех не охранников атаковать базу, если носитель яйца помер		
			end
		end
		
		local stepsToNextWave = 20	
		while GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].carrier do -- пока кто-то несет яйцо
		
			if stepsToNextWave <= 0 then
				local spawnerName = ReturnRandomGroup( EGG_GUARDS ) -- взять случайный спавнер
				local spawned = SpawnerSpawn( spawnerName, factionEnemy ) -- наспавнить крипов
				
				TeleportUnitList( spawned, eggX, eggY )
				for i = 1, #spawned do
					LuaApplyPassiveAbility( spawned[i], "flagpolesBonus" )	-- выдаем юнитам бонус от флагов		
					LuaSetCreepBehavior( spawned[i], "Chase", GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].carrier, 10, 10 ) -- Отправляем преследовать героев 
					ChangePrimeCount ( spawned[i], primeCount)
					AddTriggerEnd( AttackBaseAfterTargetDeath, spawned[i], hero, eggX, eggY, IsGuard( spawned[i], guards ), eggFlags )-- запускаем функцию, которая отправит всех не охранников атаковать базу, если носитель яйца помер		
				end
				LuaDebugTrace("[AttackBaseAfterTargetDeath] before merge " ..tostring(#allCreeps))
				MergeArray( spawned, creeps )
				MergeArray( spawned, allCreeps )
				LuaDebugTrace("[AttackBaseAfterTargetDeath] after merge " ..tostring(#allCreeps))
				
				stepsToNextWave = EGG_GUARDS_SPAWN_INTERVAL * GetStepsCountInSecond()
			end
		
			stepsToNextWave = stepsToNextWave - 1
			SleepState()
			--LuaDebugTrace("[AttackBaseAfterTargetDeath] wait quest end")
			if not GetGlobalVar( "sirinEgg_eggPositions" ) then  --эта часть скрипта почему-то не работает, будет время правим	
				for i = 1, #allCreeps do
					if not UnitIsRealyDead( allCreeps[i] ) then
						--LuaSetCreepBehavior( allCreeps[i], "MoveTo", ivaX, ivaY, 3, 20 ) 
						--LuaDebugTrace("[AttackBaseAfterTargetDeath] go attack Iva " ..tostring(#allCreeps).. " is quest end")
						LuaKillUnit( allCreeps[i] ) 		
						DebugTrace("[AttackBaseAfterTargetDeath] unit "..allCreeps[i].." killed by script")
					end
				end
				LuaDebugTrace("[AttackBaseAfterTargetDeath] quest end and return")
				return 
			end 
		end
			
		if GetGlobalVar( "sirinEgg_eggPositions" )[ eggName ].taken then -- если яйцо принесли на базу - выходим
			LuaDebugTrace("[AttackBaseAfterTargetDeath] sirinEgg_eggPositions return 2")
			return
		end
		-- яйцо разбито - начинаем по новой
	end
	LuaDebugTrace("FINISHED: [SpawnSirinEggGuards]")
end

-- Функция, отправляющая крипов атаковать базу, если носитель яйца погиб
-- Крипы-охранники яйца (которые непосредственно его охраняли) при этом
-- если они отбежали дальше, чем на 12 метров также пойдут атаковать базу
-- если они не отбежали дальше, чем на 12 метров, они возвращаются на точку 
-- спавна охрянать яйцо
function AttackBaseAfterTargetDeath( chaser, hero, eggX, eggY, isGuard, eggFlags )
	LuaDebugTrace("STARTED: [AttackBaseAfterTargetDeath] for unit "..chaser.." and hero "..hero)
	local dead, found
	local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
	repeat
		if UnitIsRealyDead( chaser ) then -- если крип мертв
			if LuaGetUnitType( chaser ) ~= UnitTypeSummon then -- и он не саммон ( которым он мог стать благодаря крысолову)
				LuaDebugTrace("[AttackBaseAfterTargetDeath] chaser "..chaser.." is dead")
				break -- выходим 
			else -- если он все же саммон (т.е. на самом деле вовсе не мертв, функция UnitIsRealyDead возвратила не совсем правильный результат)
				LuaDebugTrace("[AttackBaseAfterTargetDeath] chaser "..chaser.." is summon")
				local dead, found 
				while true do --крутимся в цикле, пока крип не будет уничтожен или не перестанет быть саммоном
					dead, found = LuaUnitIsDead( chaser )
					if dead then -- если крип мертв
						LuaDebugTrace("[AttackBaseAfterTargetDeath] chaser "..chaser.." is summon and he is dead")
						return --выходим
					end
					if LuaGetUnitType( chaser ) ~= UnitTypeSummon then -- если он перестал быть саммоном ( был благодаря А4 крысолова, но перестал)
						LuaDebugTrace("[AttackBaseAfterTargetDeath] chaser "..chaser.." is no more summon")
						local questFailed = GetGlobalVar ("sirinEgg_QuestFail")
						LuaSetCreepBehavior( chaser, "MoveTo", ivaX, ivaY, 3, 10 ) -- отправляем его атаковать Иву
						if questFailed and not UnitIsRealyDead( chaser ) then
							LuaKillUnit( chaser ) 		
							DebugTrace("[AttackBaseAfterTargetDeath] unit "..chaser.." killed by script")
						end
						break -- выходим
					end
					SleepState() 
				end
			end
		end
		dead, found = LuaUnitIsDead( hero ) --проверяем, жив ли герой, стащивший яйцо
		if dead and found or not LuaUnitCheckFlag( hero, eggFlags ) then -- если мертв
			if not isGuard then -- и наш крип не охранник яйца
				LuaSetCreepBehavior( chaser, "MoveTo", ivaX, ivaY, 3, 10 )  -- отправляем его атаковать базу (Иву)
				LuaDebugTrace("hero "..hero.." is dead. Unit "..chaser.." has been sent to base: x="..ivaX..", y="..ivaY)
			else -- если наш крип охранник яйца
				if not IsUnitInArea( chaser, eggX, eggY, 12 ) then -- и он ушел от точки спавна (где хранилось яйцо) дальше чем на 12 метров
					LuaSetCreepBehavior( chaser, "MoveTo", ivaX, ivaY, 3, 10 ) -- тоже отправляем его атаковать Иву
					LuaDebugTrace("hero "..hero.." is dead. Unit "..chaser.." has been sent to base: x="..ivaX..", y="..ivaY)
					while true do
						if not GetGlobalVar( "sirinEgg_eggPositions" ) then  --если квест кончился - посылаем крипов на базу и выходим	
							dead, found = LuaUnitIsDead( chaser )
							if not dead then -- если крип не мертв
								LuaKillUnit( chaser ) 		
								DebugTrace("FINISHED: [AttackBaseAfterTargetDeath] unit "..chaser.." killed by script")
							end
							return -- выходим
						end
						SleepState()
					end 
				else -- если крип не ушел дальше, чем на 12 метров
					LuaSetCreepBehavior( chaser, "MoveTo", eggX, eggY, 3, 5 ) -- отправляем его обратно стеречь яйцо
					LuaDebugTrace("hero "..hero.." is dead. Unit "..chaser.." has been sent to guard egg")
					while true do
						if not GetGlobalVar( "sirinEgg_eggPositions" ) and not UnitIsRealyDead( chaser ) then  --если квест кончился - посылаем крипов на базу и выходим	
							LuaKillUnit( chaser ) 		
							DebugTrace("[AttackBaseAfterTargetDeath] unit "..chaser.." killed by script")
							return -- выходим
						end
						SleepState()
					end 
				end
			end			
			break
		end
		SleepState()
	until not GetGlobalVar( "sirinEgg_eggPositions" )
		dead, found = LuaUnitIsDead( chaser )
		if not dead then -- если крип не мертв
			LuaKillUnit( chaser ) 		
			DebugTrace("FINISHED: [AttackBaseAfterTargetDeath] unit "..chaser.." killed by script")
		end
	LuaDebugTrace("FINISHED: [AttackBaseAfterTargetDeath] for unit "..chaser.." and hero "..hero)
end

-- Функция, которая смотрит за похитилем яйца
-- вешает на него эффекты яйценосца ( не может атаковать и т.д.)
-- ждет, когда яйцо будет доставлено на базу и 
-- ставит на базу эффект яйца, когда оно будет доставлено
function WatchForGlyphCarrier( hero, glyph )
	LuaDebugTrace("SirinEgg: hero "..hero.." picked up ".. glyph );
	local eggs = GetGlobalVar( "sirinEgg_eggPositions" )
	local EggEffects = GetGlobalVar( "Egg_effects" )
	GetGlobalVar( "sirinEgg_eggPositions" )[ glyph ].carrier = hero
	
	local eggFlags = ForbidAttack+Forbid_Ability1+Forbid_Ability2+Forbid_Ability3+Forbid_Ability4+ForbidUseConsumables+ForbidUseTalents+ForbidMoveSpecial
	
	SleepState()
	local x, y, r = LuaGetScriptArea( "creepIdleZone" )
	-- флаги, которые вешаются на героя, который схватит яйцо
	while LuaUnitCheckFlag( hero, eggFlags ) do -- пока герой несет яйцо (что то же самое, на нем висят указанные выше флаги)
		if not GetGlobalVar( "sirinEgg_eggPositions" ) then --если квест кончился - выходим
			LuaUnitApplyApplicator( hero, "SirinEggCarrierStopAppl" )
			return
		end
		
		if DistanceUP( hero, x, y ) < r then -- если яйцо доставлено на базу
			LuaDebugTrace("SirinEgg: hero "..hero.." bring ".. glyph .. " to base " );
			IncGlobalVar( "sirinEgg_takenCount" )
			GetGlobalVar( "sirinEgg_eggPositions" )[ glyph ].carrier = nil -- обнуляем значение переменной, в которой лежало имя похитителя яйца
			GetGlobalVar( "sirinEgg_eggPositions" )[ glyph ].taken = true 
			LuaUnitApplyApplicator( hero, "SirinEggCarrierStopAppl" ) 
			local heroX, heroY = LuaUnitGetPosition( hero )						
			LuaPlaceStandaloneEffect( "egg"..hero..glyph, "Egg", x + LuaRandom(-2,2), y + LuaRandom(-2,2)) -- ставим эффект яйца на базу
			table.insert( EggEffects, "egg"..hero..glyph )
			SetGlobalVar("Egg_effects", EggEffects)
			return
		end
		SleepState()
	end
	
	LuaDebugTrace("SirinEgg: hero "..hero.." dropped ".. glyph );
	GetGlobalVar( "sirinEgg_eggPositions" )[ glyph ].carrier = nil 
	LuaCreateGlyph( glyph, "SirinEgg", eggs[ glyph ].x , eggs[ glyph ].y )
 end
 
 -- функция, которая запускается в момент подбора яйца
 function OnSirinEggPickup( hero, glyph )
	if not string.find( glyph, "SirinEgg", 1, true ) then
		return 
	end
	AddTriggerEnd( WatchForGlyphCarrier, hero, glyph )
 end
 
 function ChangePrimeCount ( creepName, primeCount)
 	LuaSetUnitStat( creepName, 24, primeCount ) 
	LuaSetUnitStat( creepName, 25, primeCount )	
	LuaDebugTrace("SirinEgg: creepName "..creepName.." reward ".. primeCount )
 end