include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")
include ("Maps/PvE/Series/PvECommon.lua")
include ("Maps/PvE/Series/Coop1/CreepStats.lua") -- настройки статов крипов. Стартовые статы. Приращение от левела.
include ("Maps/PvE/Series/Coop1/spawnersMP.lua") -- спавн крипов
include ("Maps/PvE/Series/scriptFlags.lua") -- функционал кастомных цепочек флагов и соответствующих им зон террейна
include ("Maps/PvE/Series/Coop1/FlagsBehavior.lua") -- инициализация цепочек флагов, захват флагов, крипы спавнящиеся из леса рядом с флагами
include ("Maps/PvE/Series/Coop1/Gorynych.lua") -- все что касается Горыныча
include ("Maps/PvE/Series/Coop1/Superability.lua") -- Зарядка артефакта, взрыв артефакта, подсчет числа убитых крипов, выдача прайма за взрыв артефакта
include ("Maps/PvE/Series/Coop1/Presets.lua") -- Варианты волн крипов и героев
include ("Maps/PvE/Series/Coop1/Objective_DefeatKobolds.lua") -- Задание "Одолей кобольдов"
include ("Maps/PvE/Series/Coop1/Objective_MushroomDay.lua")  -- Задание "Одолей боровиков"
include ("Maps/PvE/Series/Coop1/Objective_ThreeFatmen.lua") -- Задание "Три толстяка"
include ("Maps/PvE/Series/Coop1/Objective_EscortDude.lua") -- Задание "Сопроводи чувака"
include ("Maps/PvE/Series/Coop1/Objective_SirinEgg.lua") -- Задание "ПРинеси яйца сиринов"
include ("Maps/PvE/Series/Coop1/Objective_RatsInvasion.lua") -- Задание "Нашествие крыс"


-- begin ============================     DEBUG SECTION    ===================================================================================
-- все переменные начинающиеся с debug предназначены только для дебага. В релизной версии ВСЕ они должны иметь значение false

debageTraceOn = true -- используется исключительно в функции DebugTrace(). Если выставить в false функция DebugTrace() ничего не будет выводить в консоль

debugSkipKobolds = false -- если true, то пропустить задание про кобольдов, отбивающих флаги после взрыва артефакта
debugSkipEnemyHeroes = false -- если true, то пропустить выход Клыка после первого взрыва артефакта и пропустит выход Когтя и Клыка после второго взрыва артефакта

debugGorynych = false -- если true, то запустить в начале миссии задание про Горыныча. При этом герои будут иметь 29-й уровень.
debugGorynychFast = false -- если true, то в начале миссии не будет паузы в 60 секунд при тестировании Горыныча ( переменная debugGorynych = true)

debugRecaptureFlags = false -- если true, то запустить в начале миссии задание про уничтожение кобольдов, пытающихся отбить флаги (как после взрыва артефакта)

debugRaiseAllFlags = false -- есои true, то в начале миссии все флаги будут подняты

debugBotsAI = false  -- если true, то 4 героя из 5-ти будут управляться АИ.
debugBotsAI2Players = false -- если true, то 3 героя из 5-ти будут управлятся АИ.
debugBotsAIGuardAreaHeroesCount = 1 -- сколько АИ героев будут охранять базу (по умолчанию у них режим follow, то есть они следуют за героями игроков)

debugHeroFirstAttack = false -- если true, то в начале миссии придет Клык со свитой (имитация задания "Одолей Серого")
debugHeroSecondAttack = false -- если true, то в начале миссии придут Клык с Когтем со свитой (имитация задания "Одолей Серого и Полосатого")

debugCreepsStats = false
debugFastStart = false -- если true, пропустить паузу в 60 секунд в начале миссии

debugSkipTime = false -- если true, то принудительно промотать время для крипов на значение из нижней строки
debugSkipTimeMinutesAmount = 30 -- на сколько минут промотать время, если debugSkipTime = true. Все это нужно, чтобы тестить прирост статов крипов например. Какие статы будут на 20-й минуте, например

debugSkipMain = false -- если true, то не запускается функция Main(). То есть по сути ничего на карте не происходит.

debugRatsInvasion = false -- если true, то в начале миссии запустится задание "Нашествие крыс"
debugThreeFatman = false -- если true, то в начале миссии запустится задание "Три толстяка"
debugSirinEgg = false -- если true, то в начале миссии запустится задание "Принеси яйца сиринов"
debugEscortDude = false -- если true, то в начале миссии запустится задание "Сопроводи беженца"
debugMushrromDay = false -- если true, то в начале миссии запустится задание "Одолей боровиков"

-- end ============================     DEBUG SECTION    ===================================================================================



-- begin ==========================     CONSTANS AND VARIABLES =============================================================================
-- Раздел глобальных констант и переменных

FACTION_DOCT = 1
FACTION_ADORN = 2
FACTION_NEUTRAL = 0

TOWERS_DOCT = { "towerLeftDoct", "towerUpDoct", "towerRightDoct", "towerDownDoct", "towerCenterDoct" }
TOWERS_ADORN = { "towerLeftAdorn", "towerUpAdorn", "towerRightAdorn", "towerDownAdorn", "towerCenterAdorn"}
towers = TOWERS_DOCT

DIRECTIONS = {"left", "up", "right", "down"}

BATTLE_START_DELAY = 60

MinmapIconBridgePassable = 22 -- иконка для открытого направления. Выглядит как красные скрещенные мечи. Исчезает после того, как направление закрыто.
-- MinmapIconBridgeImpassable = 23 -- иконка для закрытого направления. В данный момент не используется. Но вдруг понадобится.
MinmapIconCreepsStrong = 11 -- икона для домиков чуди рядом с флагами. 

allyHeroes = {} 
enemyHeroes = {}
enemyStats = {}
heroesWave = 0
ivaCreep = "iva_spawner_w1_c1" -- Ива - это крип. А это ее имя.

SUPERABILITY_KILLS_COUNTER = 100 --_NOT_COMMIT -- Сколько крипов нужно убить, чтобы зарядить артефакт

-- vars
immortalAbilities = {}
forbiddenDirections = { left = false, right = false, up = false, down = false} -- запрещенные направления. После того, как артефакт взорван, одно из направлений становится запрещенным. То есть выставляется в true
currentWaveState =  {}
threadsReport = 0
alreadySpawnedGroups = {} -- здесь храним все группы, которые уже были наспавнены
leaders = 0

-- end ==========================     CONSTANS AND VARIABLES =============================================================================


-- begin ========================         FUNCTIONS          =============================================================================
-- Далее идет код полный ужаса и безысходности

local _enemyHeroes

function Init( reconnecting )
	-- Здесь инициализируем переменные и настройки карты
	PvECommonInit( reconnecting )
	SpawnersInit( reconnecting )
	FlagsInit( reconnecting )
	
	FillCreepStatsArray() -- заполняем массив STATS_BUDGET_BY_LEVEL из CreepStats.lua 
	
	if LuaGetLocalFaction() == FACTION_DOCT then --если играем за доктов
		factionPlayer = FACTION_DOCT -- наша фракция - докты
		towers = TOWERS_DOCT -- наши башни - доктовские
		CreatureListHide( TOWERS_ADORN, true ) -- адорнийские башни убираем с карты
		_enemyHeroes = { "10", "11", "12", "13", "14" }
	else --если играем за адорнийцев, то все как выше, только наоборот
		factionPlayer = FACTION_ADORN
		towers = TOWERS_ADORN
		CreatureListHide( TOWERS_DOCT, true )
		_enemyHeroes = { "00", "01", "02", "03", "04" }
	end

	enemyHeroes = { unpack(_enemyHeroes, 1, #SECOND_WAVE_HEROES) }

	factionEnemy = FACTION_NEUTRAL
	enemyFactionFlag = 1 

	
	outerTowers = {} -- 4 башни, которые стоят по периметру
	for i=1, #towers-1 do
		outerTowers[i] = towers[i]
	end
	centerTower = towers[#towers] -- центральная башня
	
	TOWER_LIFE_INCREMENT = TOWER_LIFE_INCREMENT or 1000 -- значение TOWER_LIFE_INCREMENT берется из Bootstrap_чо-нибудь.lua. Например для синей сложности в Bootstrap_Blue.lua TOWER_LIFE_INCREMENT = 3000
	-- то есть, к стартовому количеству хит поинтов башни будет прибавлено 3000. Для каждого уровня сложности эта прибавка своя.
	for i=1, #towers do
		LuaSetUnitStat( towers[i], StatLife, LuaGetUnitStat(towers[i], StatLife) + TOWER_LIFE_INCREMENT )
	end	

	AddTriggerEnd( InitHeroes ) -- инициализация героев
	
	InitBonusPoints () -- опредиляем arrayFrom
	
	InitAttackersPresets( reconnect ) -- выбираем вариант атакующих крипов и героев, подменяем на героев из пресета
		
	if not reconnect then
		LuaSetManualGameFinish( true ) -- отключаем стандартное условие победы/поражения
		if factionPlayer == FACTION_DOCT then -- если мы докты, то
			LuaCreatureHide( "bottomAdorn", true ) -- убираем адорнийскую подложку под Ивой
			LuaCreatureHide( "bottom2Adorn", true ) -- убираем адорнийскую подложку рядом с храмом
			LuaCreatureHide( "templeAdorn", true ) -- убираем адорнийский храм
			CreatureListHide( {"10","11","12","13","14" }, true ) -- прячем героев-адорнийцев
		else -- если мы адорнийцы, то, соответственно, все наоборот.
			LuaCreatureHide( "bottomDoct", true ) 
			LuaCreatureHide( "bottom2Doct", true )
			LuaCreatureHide( "templeDoct", true )					
			CreatureListHide( {"00","01","02","03","04" }, true )
		end
		
		-- инициализация глобальных переменных и массивов
		SetGlobalVar("isMissonFinished", false)
		SetGlobalVar("immortalAbilities", immortalAbilities )
		SetGlobalVar( "forbiddenDirections", forbiddenDirections )
		SetGlobalVar( "alreadySpawnedGroups", alreadySpawnedGroups )
		SetGlobalVar( "currentWaveState" , currentWaveState )
		
		SetGlobalVar( "logicMod", 0)
		logicMod = LuaGetGSLogicParam1()
		SetGlobalVar( "logicMod", logicMod)
		
		SetGlobalVar( "stopSpawnStandardWaves", false )
		
		SetGlobalVar( "LastCreepLevel", 0 )
		SetGlobalVar( "superability_killsCounter", 0 )
		SetGlobalVar( "superabilityUsesCount", 0 )
		
		SetGlobalVar( "PauseBetweenWaves", false )
		
		SetGlobalVar( "ObjectiveDefeatKobolds_killedKoboldsCount", 0 )
		
		SetGlobalVar("AfterExplosionTimeInterval", false)
		SetGlobalVar("IvaAnnounceWaitStep", 0 )
		SetGlobalVar( "specialPoints", 0 )
		
		LuaSetSpawnNeutralCreeps(false) -- запрещаем спавнится нейтральным крипам по собственному их разумению
		LuaSetSpawnCreeps(false) -- запрещаем фракционным крипам спавнится по собственному их разумению
		
		if debugSkipMain then return end
		AddStateEnd( Main ) 
	end
end

function InitBonusPoints ()
	COMMON_STATS_BONUS = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy } }
	local distributedBonusPoints = {}
	for i=1, #COMMON_STATS_BONUS["stats"] do table.insert( distributedBonusPoints, 0 ) end
	for i=1, #enemyHeroes do			
		SetGlobalVar( "distributedBonusPoints"..enemyHeroes[i], distributedBonusPoints ) -- для каждого героя заводим глобальный массив, в котором будем запоминать количество очков статов, которые уже ему были выданы ранее.
	end
end

function Reconnect() -- запускается при реконнекте
	immortalAbilities = GetGlobalVar( "immortalAbilities" )
	forbiddenDirections = GetGlobalVar( "forbiddenDirections" )
	alreadySpawnedGroups = GetGlobalVar( "alreadySpawnedGroups" )
	currentWaveState = GetGlobalVar( "currentWaveState" )
	
	PvECommonReconnect()
	SpawnersReconnect()
	FlagsReconnect()
	threadsReport = 2
	InitHeroes()
	
	for i=1, #DIRECTIONS do
		if not forbiddenDirections[ DIRECTIONS[i] ] then
			local minimapIcon = DIRECTIONS[i].."RoanEndIcon"
			local x, y = LuaGetScriptArea( DIRECTIONS[i].."CloudMinimapIcon")
			LuaPlaceMinimapIcon( minimapIcon, MinmapIconBridgePassable, x, y, 0 )
		end
	end	
end

function Main()
	-- В некотором смысле это Init2. Здесь мы продолжаем выставлять настройки карты, но теперь мы уже можем запускать некоторые функции, которые в Init запускать запрещено.
	local startTime = GetGameStep() -- здесь храним степ начала игры. Понадобится в будущем.
	SleepState()

	AddTriggerEnd( FlagsStartup ) --долгая операция инициализации всех флагов (до 2-х секунд). Описание находится в FlagsBehavior.lua
	
	-- прячем кнопки по краям дорог, которые взрывают аномалию и ставим на карту иконки для обозначения опасных направлений
	for i=1, #DIRECTIONS do
		local buttonName = DIRECTIONS[i].."Button"
		LuaCreatureHide( buttonName, true )
		
		local minimapIcon = DIRECTIONS[i].."RoanEndIcon"
		local x, y = LuaGetScriptArea( DIRECTIONS[i].."CloudMinimapIcon")
		LuaPlaceMinimapIcon( minimapIcon, MinmapIconBridgePassable, x, y, 0 ) -- выставвляем иконку опасного направления
	end
	
	
	-- этот код выполняется только в дебажном режиме. Т.е. по крайней мере debugBotsAI = true
	-- Включаем ботам АИ, если хотим потестить карту в одиночку или вдвоем
	if debugBotsAI then			
		BotsAIOn(2)
	end

	local function heroExists(id)
		local _, found = LuaUnitIsDead(id)
		return found
	end
	
	-- получаем координаты точки, в которой будем респавнить вражеских героев
	local x,y,r = LuaGetScriptArea( "enemyHeroRespawnPoint" )

	-- Назначаем им точку респавна в зоне "enemyHeroRespawnPoint" (см. выше)
	-- после чего телепортим в эту всех героев
	for _, id in ipairs(_enemyHeroes) do
		if heroExists(id) then
			LuaApplyPassiveAbility(id, "flagpolesBonus") -- Даем вражеским героям бонус от флагов ( + к воле, стойкости и скорости)
			--LuaCreatureHide(id, true)
			LuaCreatureTeleportTo(id, x, y)
			LuaHeroSetRespawnPoint(id, x, y)
			LuaHeroSetForbidRespawn(id, true) -- Запрещаем вражеским героям респавнится стандартным образом
			LuaHeroSetRefineRate(id, ENEMY_HERO_REFINE_RATE) -- Заточка сета зависит от уровня сложности. Степень заточки хранится в ENEMY_HERO_REFINE_RATE, задается в Bootstrap_<color>.lua			
			LuaKillUnit(id) -- Убиваем их на всякий случай
		end
	end
	
	for _, id in ipairs(enemyHeroes) do
		LuaCreatureHide(id, false)
	end	

	--На уровнях сложности Red и Orange вражеским героям при левелапе выдаются дополнительные статы.
	LuaDebugTrace("XXXX WWWWWW")
	--for i=1, #ENEMY_HERO_STATS_BONUS["stats"] do table.insert( distributedBonusPoints, 0 ) end
	for i=1, #enemyHeroes do			
		--SetGlobalVar( "distributedBonusPoints"..enemyHeroes[i], distributedBonusPoints ) -- для каждого героя заводим глобальный массив, в котором будем запоминать количество очков статов, которые уже ему были выданы ранее.
		LuaSubscribeUnitEvent( enemyHeroes[i], EventResurrect, "UpdateHeroStats") -- подписываемся на событие "возрождение героя". В момент его возрождения, ему будут выданы дополнительные статы.			
	end

	
	-- Всем союзным героям на карте скорость передвижения увеличена на 10%
	-- А скорость регенерации энергии 0.6%
	for i=1, #allyHeroes do
		LuaSetUnitStat( allyHeroes[i], StatMoveSpeed, LuaGetUnitStat( allyHeroes[i], StatMoveSpeed ) * 1.1 )
		LuaSetUnitStat( allyHeroes[i], StatEnergyRegeneration, 0.6 )		
	end	
	
	
	IvaSetup() -- Настройки Ивы
	
	AddTriggerEnd( TowersDestructionChain ) -- Реализация цепочки неуязвимостей для башен
	
	-- begin =====  DEBUG SECTION ======
	-- Код ниже используется только при условии, что какая-то из дебажных переменных выставлена в true
	
	if debugRaiseAllFlags then -- Если вначале надо поднять все флаги, поднимаем их
		while not flagsInitCompleted do SleepState() end
		RaiseAllFlags( allyHeroes[1] ) 
	end
	
	if debugCreepsStats and RED_DIFFICULTY then
		SetGlobalVar( "logicMod", 1)
		logicMod = 1
	end
	
	if debugGorynych then -- Если в начале миссии хотим тестить Горыныча
		for i=1, #allyHeroes do
			AddTriggerEnd( DebugLevelUpHeros, allyHeroes[i], 29 ) -- Левелапим героев до 29-го уровня
		end
		if not debugGorynychFast then -- если не хотим ждать 60 секунд в начале миссии пропускаем их
			WaitState( BATTLE_START_DELAY )
		end
		LuaMakeUnitLevelupsForTimeDelta( 1350 ) -- Проматываем время для крипов, чтобы они полевелапились
		SpawnGorynych() -- Пускаем Горыныча
		
		return 
	end
	
	-- если в начале миссии хотим тестить задание "Нашествие крыс"
	if debugRatsInvasion then
		QuestRatsInvasion()
		return
	end
	
	-- если в начале миссии хотим тестить задание "Три толстяка"
	if debugThreeFatman then
		AddTriggerEnd( Superability ) -- Запущаем функциональность суперабилки
		SetGlobalVar("superability_killsCounter", 100)
		QuestThreeFatman()
		return
	end
	
	-- если в начале миссии хотим тестить задание "Принеси яйца Сирин"
	if debugSirinEgg then
		QuestSirinEgg()
		return
	end
	
	-- если в начале миссии хотим тестить задание "Сопроводи беженца"
	if debugEscortDude then
		forbiddenDirections[ "left" ] = true
		QuestEscortDude()
		return
	end
	
	-- если в начале миссии хотим тестить задание "Одолей боровиков"
	if debugMushrromDay then
		AddTriggerEnd( Superability ) -- Запущаем функциональность суперабилки
		SetGlobalVar("superability_killsCounter", 100)
		QuestLittleBoroviks()
		return
	end
	
	if debugRecaptureFlags then -- Если хотим потестить перезахват флагов кобольдами
		while not flagsInitCompleted do SleepState() end -- ждем пока проинициализируются флаги
		RaiseAllFlags( allyHeroes[1] ) -- Поднимаем все флаги
		WaitState(2)
		AddTriggerEnd( Superability ) -- Запущаем функциональность суперабилки
		AddTriggerEnd( Objective_RecaptureFlags ) --Запущаем кобольдов
		return 
	end
	
	if debugHeroFirstAttack then -- Если хотим потестить приход Клыка
		SpawnEnemyHeroes( 1 )
		return
	end
	
	if debugHeroSecondAttack then -- Если хотим потестить приход Клыка и Когтя
		SpawnEnemyHeroes( 2 )
		return
	end
	
	-- end ==== DEBUG SECTION ===
	
	AddTriggerEnd( Superability )	-- Запускаем функциональность суперабилки (лежит в Superability.lua )
	AddTriggerEnd( SideQuestsManager ) -- Управление выдачей дополнительных квестов в промежутках между взрывами
	AddTriggerEnd( SpawnBossesWhenArtifactFull ) -- Периодически запускать с каждого из доступных направлений босса, если артефакт почти заряжен
	
	AddStateEnd( ObjectiveMain_DefendCastle ) -- Запускаем функциональность волн крипов, накатывающихся на базу	
end

function DebugLevelUpHeros( hero, level ) -- Дебажная функция. Левелапит героя hero до уровня level, когда он зашел в зону StartWaves (рядом с Ивой)
	WaitForUnitInArea( hero, "startWaves")
	LevelUpHero( hero, level )
end

-- Здесь сохраняем в массив allyHeroes героев нашей команды и перекрашиваем террейн в родную землю нашей фракции
function InitHeroes()
	local allyCandidates = { "10","11","12","13","14" }
	if factionPlayer == FACTION_DOCT then 
		allyCandidates = {"00","01","02","03","04" }
		LuaChangeNatureMap("allMap", FACTION_ADORN, FACTION_DOCT)
	end
	
	local i = 0
	for i = 1,#allyCandidates do
		local dead, exist = LuaUnitIsDead( allyCandidates[i] )
		LuaDebugTrace("Hero ".. allyCandidates[i] .. " exists: "..tostring(exist) )
		if exist then 
			--allyHeroes[ allyCandidates[i] ] = {isAlive = not dead } 
			table.insert( allyHeroes, allyCandidates[i] )
		end
	end
	LuaDebugTrace("allyHeroes: ".. #allyHeroes )
end

-- Настройка Ивы
function IvaSetup()
	local spawnerName = "iva_spawner" -- Ива это крип. Это название ее спавнера
	
	LuaSpawnerSpawnWave(spawnerName) -- Спавним ее
	LuaSetCreepFaction( ivaCreep, factionPlayer ) -- Делаем ее союзной
	LuaPlaceAttachedEffect("EffectChargeArtefact", "chargeArtefact", ivaCreep) -- Вешаем не нее эффект зарядки артефакта
	LuaForceAnimation( ivaCreep, "channeling", -1 ) -- Зацикливаем анимацию ченнелинга для зарядки артефакта
	LuaPlaceAttachedEffect( "healEffect", "centerAreaHeal", ivaCreep ) 
	-- Запрещаем Иве атаковать, быть интерактивной, двигаться и быть управляемой игроком
	SetUnitsFlagList( {ivaCreep}, {ForbidAutoAttack, ForbidInteract, ForbidPlayerControl, ForbidAttack, ForbidMove}, true )	
	LuaSetUnitStat( ivaCreep, StatLife, 4000 ) -- Выставляем Иве 4000 здоровья
	LuaSetUnitStat( ivaCreep, StatLifeRegeneration, 2 ) -- Делаем лайфреген 2%
	AddTriggerEnd( IvaMustSurvive, ivaCreep ) -- Запускаем проверку условия поражения. Если Ива погибла - мы проиграли
end

-- Проверка условия поражения.
function IvaMustSurvive( iva )
	LuaSubscribeUnitEvent( iva, EventDamage, "IvaAlarmSistem" ) -- подписываемся на функцию IvaAlarmSistem, которая запускается при получении Ивой урона

	while  LuaUnitIsDead( iva ) == false do
		SleepState()
	end
	LuaDebugTrace("TRACE: IvaMustSurvive: Iva is dead")
	-- Если сюда пришли, значит Иве кранты
	
	local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
	LuaCameraMoveToPosTimed( ivaX, ivaY, 1 );
	LuaGameFinish( factionPlayer ) -- проигрываем
	PrintArray( SPAWNEDCREEPS ) -- дебажный фукнционал. Пишем в конце скрипта, сколько и каких наспавнилось крипов. МОжно отключить.
end

function IvaAlarmSistem (iva)
	local lastAnnounceStep = GetGlobalVar ("IvaAnnounceWaitStep")
	local currentStep = GetGameStep()
	if (currentStep - lastAnnounceStep) * GetStepLengthInSeconds() >= 10 then
		local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
		SetGlobalVar ("IvaAnnounceWaitStep", currentStep)
		LuaUnitApplyApplicatorFromUnit( iva,  iva, "ivaCommingDeadEvent" ) -- сообщаем, что Ива скоро умрет
		LuaCreateMinimapSignal( ivaX, ivaX )
	end
end

function OnPlayersSurrender( surrenderFaction )
	local ivaX, ivaY = LuaUnitGetPosition( ivaCreep )
	LuaCameraMoveToPosTimed( ivaX, ivaY, 1 );
	LuaKillUnit( ivaCreep )
end

-- Формирование цепочек неуязвимостей
-- Пока не разрушена хотя бы одна из 4-х башен периметра, центральная башня неуязвима
-- Пока неуязвима центральная башня, неуязвима Ива.
-- Т.е. крипы вначале должны пронести хотя бы одну башню периметра, потом центральную башню, потом Иву
function TowersDestructionChain()
	LuaUnitAddFlag( centerTower, ForbidTakeDamage ) -- Запрещаем центральной башне получать урон
	LuaUnitAddFlag( ivaCreep, ForbidTakeDamage ) -- Запрещаем Иве получать урон

	local x,y,r = LuaGetScriptArea( "creepIdleZone" )
	local aliveTower = nil -- "произвольная" уцелевшая башная. Нужна нам, чтобы агрить на нее мобов, 
	-- которых закайтили в центр базы и они не знают, что им крушить, если вашню в центре атаковать еще нельзя.
	local controlledCreeps = {}
	
	while not GetGlobalVar( "towerIsDestroyed" ) do -- крутимся в этом цикле пока ни одна башня не разрушена
	   
		for i=1, #outerTowers do -- проверяем для всех башен периметра
			if UnitIsRealyDead( outerTowers[i] ) then -- если какая-то башня уничтожена
				LuaDebugTrace("[TowersDestructionChain] tower "..outerTowers[i].." is destroyed")
				-- Выходим из внешнего while
				SetGlobalVar( "towerIsDestroyed", true )
				break
			end
			-- если никакая башня пока не уничтожена, то первая башня в массиве объявляется "уцелевшей". Понадобится ниже
			aliveTower = outerTowers[i]
		end
		
		-- Смотрим, есть ли в централлной части базы крипы (их могли закайтить туда игроки). Если есть - отправляем на периметр крушить какую-нибудь башню
		local creeps = LuaGetCreepsInArea( x, y, r, enemyFactionFlag )
		for i, creep in ipairs( creeps ) do -- для каждого creep из найденных в зоне
			if LuaUnitIsIdle( creep ) then -- если этот creep бездельничает
				local dbid = LuaUnitGetDbid( creep )
				local x, y;
				if string.find( dbid, "Summons/Whisper/PvE_Coop1", 1, true ) then  
					--особый случай: не может атаковать башни + должен ходить вместе с группой - посылаем всю его волну к ближайшему герою
					local hero = nil;
					local minDist = 100000
					for i=1, #allyHeroes do
						if not LuaUnitCheckFlag( allyHeroes[i], Invisible ) then
							local d = DistanceUU( allyHeroes[i], creep )
							if  d < minDist then
								hero = allyHeroes[i];
								minDist = d;
							end
						 end
					end
					if hero then
						local wavePart = string.match( creep, "[%a%d]+_w%d+_c" )
						for i = 1, 5 do 
							if not LuaUnitIsDead( wavePart..i ) then
								--LuaDebugTrace("[TowersDestructionChain] idle creep "..wavePart..i.." sent to "..hero )
								LuaSetCreepBehavior( wavePart..i, "Chase", hero, 8, 4 )
							end
						end
					end
				else 
					x, y = LuaUnitGetPosition( aliveTower )
					LuaSetCreepBehavior( creep, "MoveTo",  x, y, 8, 4 ) -- отправить его бить "уцелевшую" башню
					table.insert( controlledCreeps, creep ) -- в controlledCreeps храним всех крипов, которых мы запрограммировали таким образом на зло
				end
				
				--LuaDebugTrace("[TowersDestructionChain] idle creep "..creep.." sent to "..aliveTower )
			end
		end
		controlledCreeps = GetOnlyAliveUnits( controlledCreeps )        
		SleepState()
	end
	-- Если мы оказались здесь, значит по крайней мере одна башня периметра разрушена
	LuaUnitRemoveFlag( centerTower, ForbidTakeDamage ) -- снимаем неуязвимость с центральной башни
	
	for i, creep in ipairs( controlledCreeps ) do -- для каждого creep, из тех, что мы отправляли бить башни периметра
		local x, y = LuaUnitGetPosition( centerTower )
		LuaSetCreepBehavior( creep, "MoveTo",  x, y, 8, 12 ) -- отправить бить башню в центре
		--LuaDebugTrace("[TowersDestructionChain] creep "..creep.." sent to "..centerTower )
	end
	controlledCreeps = nil
	
	-- Ничего не делаем, пока башня в центре цела
	while not UnitIsRealyDead( centerTower ) do SleepState() end 
	LuaDebugTrace("[TowersDestructionChain]  center tower is destroyed. Iva is mortal")
	
	-- Здесь оказываемся, если башня в центре уничтожена. Снимаем с Ивы неуязвимость
	LuaUnitRemoveFlag( ivaCreep, ForbidTakeDamage )
end

-- Если счетчик артефакта достиг 90%, то с каждого из доступных направлений начинаем
-- спавнить боссов.
function SpawnBossesWhenArtifactFull()
	local spawned = 0
	local bosses = PRESETS[ presetNumber ]["bossesTypes"] -- Список боссов для каждого пресета хранится в presets.lua
	local directions = {}	
	
	while GetGlobalVar( "superabilityUsesCount" ) < 3 do -- Если взрывов было меньше трех (т.е это еще не Горыныч)
		while GetGlobalVar( "superability_killsCounter" ) < 10 * SUPERABILITY_KILLS_COUNTER / 10  do SleepState() end -- Пока счетчик не достиг 90% спим
		LuaDebugTrace("[SpawnBossesWhenArtifactFull] artifact is almost full. Time to spawn bosses")
		while not GetGlobalVar( "stopSpawnStandardWaves" ) do -- Если сейчас еще идут стандартные волны
			directions = GetAvailableDirections() -- берем доступные направления
			for i=1, #directions do -- с каждого из них
				if GetGlobalVar( "superability_killsCounter" )>=SUPERABILITY_KILLS_COUNTER then
					spawned = SpawnerSpawn( bosses[ LuaRandom(1, #bosses)] ) -- спавним босса
					PushPathAndApplyFlagBonus( spawned, directions[i] ) 
				end -- отправляем его пушить соответствующее направление и выдаем бонус от флагов
				if LuaRandom(1,2) == 1 then -- а чтобы жизнь медом не казалось, побрасываем еще монетку и, если выпал "орел"
					SleepState() 
					if GetGlobalVar( "superability_killsCounter" )>=SUPERABILITY_KILLS_COUNTER then
						spawned = SpawnerSpawn( "Assassin1" ) -- спавним на этом направлении еще и ассассина
						PushPathAndApplyFlagBonus( spawned, directions[i] ) 
					end
				end
				LuaDebugTrace("[SpawnBossesWhenArtifactFull] spawned boss for direction "..directions[i])
			end
			WaitState( 4 * #directions ) -- после спавна ждем. В случае 4-х направлений 16 секунд, в случае 3-х - 12, в случае 2-х - 8 секунд
		end
		SleepState()
	end
	LuaDebugTrace("FINISHED: [SpawnBossesWhenArtifactFull]")
end

-- Управление квестами, которые выдаются в ходе стандартных волн
function SideQuestsManager()
	LuaDebugTrace("STARTED: [SideQuestsManager]")	
	WaitState( BATTLE_START_DELAY ) --_NOT_COMMIT
	local superabilityUsesCounter = GetGlobalVar( "superabilityUsesCount" )
	local questIDs = {1, 2, 3} -- список id квестов. 1 - "одолей боровиков", 2 - "Три толстяка", 3 - "Сопроводи беженца". При добавлении нового квеста следует добавить сюда его id 
	while superabilityUsesCounter < 3 and #questIDs > 0 do
		while GetGlobalVar("AfterExplosionTimeInterval") do SleepState() end -- Если сейчас не время для стандартных волн, ждем
		LuaDebugTrace("Wave in Progress")
		WaitState( LuaRandom( 90, 150 ) ) 
		if not GetGlobalVar("AfterExplosionTimeInterval") then -- если сейчас идут стандартные волны
			local questIDIndex = LuaRandom(1, #questIDs) -- выбираем случайный индекс для элемента массива (понадобится, чтобы потом удалить соответствующий id квеста, чтобы он не выдался повторно)
			local questID = questIDs[ questIDIndex ] -- выбираем случайный id квеста
			--questID = 3 --for debug
			local availableDirections = #GetAvailableDirections()
			LuaDebugTrace("[SideQuestsManager] AvailableDirections: " .. tostring(availableDirections))
			if questID == 1 and availableDirections == 4 then -- если 1, то выдаем квест "Сопроводи беженца" и если нет заблокированной дороги, то этот квест выдать  нельзя. Беженцу некуда отступать.
				questIDIndex = LuaRandom(2, #questIDs) 
				questID = questIDs[ questIDIndex ] 
				LuaDebugTrace("[SideQuestsManager] NoEscortDude next quest: " ..questID)
			end
			if questID == 1 then -- если 1, то выдаем квест "Сопроводи беженца"
				LuaDebugTrace("[SideQuestsManager] QuestEscortDude started")
				AddTriggerEnd( QuestEscortDude ) -- если заблокированная дорога есть, то запускаем квест
			elseif questID == 2 then  -- если 2, то выдаем квест "Три толстяка"
				LuaDebugTrace("[SideQuestsManager] QuestThreeFatman started")
				AddTriggerEnd( QuestThreeFatman ) 
			elseif questID == 3 then -- если 3, то выдаем квест "Одолей боровиков"
				LuaDebugTrace("[SideQuestsManager] QuestLittleBoroviks started")
				AddTriggerEnd( QuestLittleBoroviks ) 
			else
				LuaDebugTrace("ERROR! [SideQuestsManager] unknown quest ID")
			end
			table.remove( questIDs, questIDIndex ) -- удаляем из массива id квестов идентификатор выданного квеста, чтоб не выдался повторно
			superabilityUsesCounter = GetGlobalVar( "superabilityUsesCount" )
			while superabilityUsesCounter == GetGlobalVar( "superabilityUsesCount" ) do SleepState() end --ждем, пока не взорвется артефакт
		end
	end
	if #questIDs == 0 then
		LuaDebugTrace("[SideQuestsManager] no more quests!")
	end
end

-- Здесь мы запускаем волны крипов. В рамках одной волны крипы идут со всех доступных на данный момент сторон
-- После завершения волны следует пауза в 15 секунд. Потом начинается следующая волна.
-- Если произошел прайм-взрыв (одна из дорог оказывается закрыта), запускаем из леса кобольдов, которые будут отбивать флаги.
-- После них после первого взрыва приходить Клык. После второго Коготь и Клык вместе
function ObjectiveMain_DefendCastle()
	LuaDebugTrace("TRACE: Objective2_DefendCastle STARTED")
	
	if not debugFastStart then -- Не ждем 60 секунд, если дебажная переменная debugFastStart = true
		WaitState( BATTLE_START_DELAY ) --В релизной версии ждем 60 секунд
	end
	if debugSkipTime then -- Если debugSkipTime = true, значит проматываем время на количество минут debugSkipTimeMinutesAmount
		LuaMakeUnitLevelupsForTimeDelta( debugSkipTimeMinutesAmount * 60 ) -- В релизной версии не должно работать
	end
	
	local prevSuperabilityUsesCount = GetGlobalVar("superabilityUsesCount") -- Храним здесь сколько уже было произведено взрывов артефакта
	local waveNumber = 0 -- номер волны
	
	local questIDs = {1,2,3} -- массив идентификаторов квестов. 1 - "Одолей кобольдов", 2 - "Принеси яйца Сирин", 3 - "Нашествие крыс", при добавлении нового квеста сюда следует добавить его id
	while true do -- крутимся в этом цикле до скончания веков
		-- Если сейчас пауза между волнами, то ждем
		while GetGlobalVar( "stopSpawnStandardWaves" ) == true do SleepState() end
		-- Если паузы нет, едем дальше
		
		local superabilityUsesCount = GetGlobalVar("superabilityUsesCount") -- смотрим сколько раз взрывался артефакт	

		local TIME_BETWEEN_WAVES = GetTimeInvetval()
		
		if superabilityUsesCount > prevSuperabilityUsesCount then -- Если только что был взрыв (количество взрывов стало больше, чем раньше) 
			
			-- выставляем PauseBetweenWaves=true, чтобы через нее все заинтересованные могли узнать, что настала пауза между волнами
			-- Под паузой здесь подразумевается интервал времени, когда стандартные волны перестают набегать. Наступают кобольды, Клык и Коготь.
			SetGlobalVar("PauseBetweenWaves", true) 
			
			-- увеличиваем спец.очки
			local points = GetGlobalVar( "specialPoints" )
			points = points + 1
			for i = 1, #allyHeroes do
				LuaSetHeroSpecialPoints( allyHeroes[i], points )
			end
			SetGlobalVar( "specialPoints", points )
			
			-- Если не время для Горыныча (было меньше трех взрывов)
			if superabilityUsesCount < 3 then				
				if not debugSkipKobolds then 
					if #questIDs > 0 then
						local questIDIndex = LuaRandom( 1, #questIDs ) -- выбираем случайный индекс для элемента массива (понадобится, чтобы потом удалить соответствующий id квеста, чтобы он не выдался повторно)
						local questID = questIDs[ questIDIndex ] -- выбираем случайный квест
						--questID = 1 --for debug
						if questID == 1 then -- если 1, то выдаем квест про кобольдов-сбивателей флагов. Objective_RecaptureFlags() находится в файле Objective_DefeatKobolds.lua
							Objective_RecaptureFlags()
						elseif questID == 2 then
							QuestSirinEgg() -- если 2, то выдаем квест "Принеси яйца сирин". QuestSirinEgg() находится в файле Objective_SirinEggs.lua
						elseif questID == 3 then
							QuestRatsInvasion() -- если 3, то выдаем квест "Нашествие крыс". QuestRatsInvasion() находится в файле Objective_RatsInvasion.lua
						else 
							LuaDebugTrace("ERROR! [ObjectiveMain_DefendCastle] unknown quest id = "..questID)
						end
						table.remove( questIDs, questIDIndex ) -- удаляем из массива идентификатор выданного квеста
					end
				end 
				-- После того, как квест закончится, выпускаем вражеских героев. 
				if not debugSkipEnemyHeroes then SpawnEnemyHeroes( superabilityUsesCount ) end -- superabilityUsesCount - количество взрывов артефакта. От него зависит количество героев, которые придут атаковать 
				SetGlobalVar("AfterExplosionTimeInterval", false)
			else 
				SpawnGorynych() -- в противном случае выпускаем Горыныча
				return -- и вообще уходим отсюда.
			end
			
			prevSuperabilityUsesCount = superabilityUsesCount -- храним предыдущее количество взрывов
			SetGlobalVar("PauseBetweenWaves", false) -- Конце паузы между волнами
		else	-- если взрыва только что не было	
			waveNumber = waveNumber + 1 -- инкрементим номер волны
		
			SetGlobalVar( "WaveInProgress", true )		-- Сохраняем WaveInProgress=true, чтобы через нее все заинтересованные могли знать, что сейчас набегают "обычные" волгны
			Wave( GetAvailableDirections(), waveNumber ) -- по всем доступным направлениям GetAvailableDirections() запускаем волну с номером waveNumber
			SetGlobalVar( "WaveInProgress", false ) -- Время "обычной" волны закончилось
		end			
		LuaDebugTrace("Wave finished, and time between waves: " ..TIME_BETWEEN_WAVES)		
		WaitState( TIME_BETWEEN_WAVES ) -- ждем интервал
	end
end

logicMod = GetGlobalVar("logicMod")
-- WAVE_CREATURES_COUNT Сколько всего может быть в данной волне крипов. 
-- Т.е. в первой волне 25, во второй 35, в третьей и четвертой по 40. В последующих столько же, сколько в последнем значении. То есть 40.
WAVE_CREATURES_COUNT = { 25, 35, 40, 40 } 

-- WAVE_SPAWN_INTERVALS Интервал в секундах между спавнами групп крипов на одном направлении. 
-- Т.е. в первой волне 12, во второй 11, в третьей и четвертой по 10. В последующих столько же, сколько в последнем значении. То есть 10.
WAVE_SPAWN_INTERVALS = WAVE_SPAWN_INTERVALS or { 12, 11, 10, 10 }

-- WAVE_SPAWN_INTERVALS_MAIN_DIR Интервал в секундах между спавнами групп крипов на ГЛАВНОМ направлении. На главном направлении крипы ходят чаще
-- Т.е. в первой волне 9, во второй 9, в третьей и четвертой по 7. В последующих столько же, сколько в последнем значении. То есть 7.
WAVE_SPAWN_INTERVALS_MAIN_DIR = WAVE_SPAWN_INTERVALS_MAIN_DIR or { 9, 8, 7, 7 }

-- WAVE_MAX_CREATURES_ON_DIRECTION Максимальное количество крипов разрешенное на данном направлении. Остальные крипы не будут спавнится
-- пока количество крипов на данном направлении не станет меньше, чем соответствующее значение.
-- Т.е. в первой волне на одном направлении может быть не более 6-ти крипов. Пока их не станет меньше, другие не наспавнятся
WAVE_MAX_CREATURES_ON_DIRECTION = { 6, 12, 13, 13 }

-- WAVE_MAX_CREATURES_ON_DIRECTION_NEW_CREEP Максимальное количество крипов разрешенное на данном направлении, если нароллилась группа крипов, которой раньше не было
-- Т.е. если нароллился новый крип, то на линии при этом может быть не более 1-го крипа.
WAVE_MAX_CREATURES_ON_DIRECTION_NEW_CREEP = { 1, 1, 1, 1 } -- сколько крипов должно остаться на линии, когда пускаем новых крипов

-- WAVE_MAX_CREATURES_TOTAL Сколько ВСЕГО может быть крипов на карте в данный момент времени.
-- Т.е. на первой не больше 35, на второй не больше 40 и т.д. Новые крипы не спавнятся, пока количество крипов на карте больше, чем указано в массиве
WAVE_MAX_CREATURES_TOTAL = { 35, 40, 35, 32, 30, 25 }

WAVE_MAIN_DIRECTION_COUNT_MUL = 1.5 --насколько увеличивать долю крипов на главном направлении
WAVE_CREATURES_DISP = 3 -- стд отклонение количества крипов в волне от рассчитанной доли. Грубо говоря, плюс-минус 3 крипа.

GREEN_DIFFICULTY = GREEN_DIFFICULTY or false -- зеленая сложность?
RED_DIFFICULTY = RED_DIFFICULTY or false

-- имитация стандартного нормального распределения
-- Смысл этих настроек описан на конфе
WAVE_BOSSES_ROLL_PROB = { 15, 20, 25, 30, 35, 40, 45} -- вероятности прихода боссов в завимости от номера волны. -1 означает отсутствие ограничения.
WAVE_MINIBOSSES_ROLL_PROB = { 30, 35, 35, 35, 35, 40, 40} -- вероятности прихода минибоссов в завимости от номера волны. -1 означает отсутствие ограничения.
WAVE_BOSSES_ROLL_MAX_FAILS =         { -1,  5,  5,  4,  4,  3 } -- максимальное количество неудач ролла босса в зависимости от номера волны. -1 означает отсутствие ограничения.
WAVE_BOSSES_ROLL_MAX_SUCCESSES =     {  1,  3,  2,  1,  1,  -1 } -- максимальное количество подряд боссов в зависимости от номера волны. -1 означает отсутствие ограничения.
WAVE_MINIBOSSES_ROLL_MAX_FAILS =     { -1,  5,  4,  4,  4,  4 } -- то же самое для минибоссов. -1 означает отсутствие ограничения.
WAVE_MINIBOSSES_ROLL_MAX_SUCCESSES = { -1,  -1,  -1,  -1, -1, -1 } -- -1 означает отсутствие ограничения.

function NormalRandom( e, d )
	local x, y, s
	repeat
		x = LuaRandom( -100000, 100000 ) / 100000
		y = LuaRandom( -100000, 100000 ) / 100000
		s = x * x + y * y
	until s < 1
	
	s = math.sqrt( s )
	local z = x * math.sqrt( -2 * math.log( s ) / s )

	return z * d + e 	
end

-- Для волны с номером waveNumber возвращает значения из массива fromTable
-- Например GetWaveParam( 3, WAVE_BOSSES_ROLL_PROB ) вернет для третьей волны вероятность ролла босса
-- то же самое с другими массивами описанными выше. 
function GetWaveParam( waveNumber, fromTable )
	if waveNumber < #fromTable then
		return fromTable[waveNumber]
	end
	return fromTable[#fromTable]
end

-- Здесь мы формируем волны по конкретным направлениям, решаем, какое направление будет главным и сколько на каком направлении будет крипов
function Wave( directionsForAttack, waveNumber )
	LuaDebugTrace("STARTED: [Wave] number: "..waveNumber)

	if GetGlobalVar("superabilityUsesCount") >= 3 then return end	-- если мы здесь оказались после третьего взрыва (время Горыныча) выходим отсюда
	
	if GetGlobalVar("superabilityUsesCount") >= 2 and RED_DIFFICULTY and logicMod > 0 then
		LuaDebugTrace("[Wave]: power difficult mod on!")
		for i=1, #WAVE_MINIBOSSES_ROLL_MAX_FAILS do 
			WAVE_MINIBOSSES_ROLL_MAX_FAILS[i] = WAVE_MINIBOSSES_ROLL_MAX_FAILS[i] * (1-0.3*logicMod)
		end
		for i=1, #WAVE_CREATURES_COUNT do 
			WAVE_CREATURES_COUNT[i] = WAVE_CREATURES_COUNT[i] * (1+0.3*logicMod)
		end
		for i=1, #WAVE_BOSSES_ROLL_PROB do 
			WAVE_BOSSES_ROLL_PROB[i] = WAVE_BOSSES_ROLL_PROB[i] * (1+0.3*logicMod)
		end
		for i=1, #WAVE_MINIBOSSES_ROLL_PROB do 
			WAVE_MINIBOSSES_ROLL_PROB[i] = WAVE_MINIBOSSES_ROLL_PROB[i] * (1+0.3*logicMod)
		end
		for i=1, #WAVE_BOSSES_ROLL_MAX_SUCCESSES do 
			WAVE_BOSSES_ROLL_MAX_SUCCESSES[i] = WAVE_BOSSES_ROLL_MAX_SUCCESSES[i] * (1+0.3*logicMod)
		end
		for i=1, #WAVE_BOSSES_ROLL_MAX_FAILS do 
			WAVE_BOSSES_ROLL_MAX_FAILS[i] = WAVE_BOSSES_ROLL_MAX_FAILS[i] * (1-0.3*logicMod)
		end
		for i=1, #WAVE_MAX_CREATURES_TOTAL do 
			WAVE_MAX_CREATURES_TOTAL[i] = WAVE_MAX_CREATURES_TOTAL[i] * (1+0.3*logicMod)
		end
		for i=1, #WAVE_SPAWN_INTERVALS do 
			WAVE_SPAWN_INTERVALS[i] = WAVE_SPAWN_INTERVALS[i] * (1-0.4*logicMod)
		end
		for i=1, #WAVE_SPAWN_INTERVALS_MAIN_DIR do 
			WAVE_SPAWN_INTERVALS_MAIN_DIR[i] = WAVE_SPAWN_INTERVALS_MAIN_DIR[i] * (1-0.4*logicMod)
		end
	end
	--выдать количество крипов на каждое направление
	local creatureCountByDirection = {}
	local totalCount = GetWaveParam( waveNumber, WAVE_CREATURES_COUNT ) -- столько крипов выделено на волну с данным номером waveNumber
	local mainDir = directionsForAttack[LuaRandom( 1, #directionsForAttack )] -- выбираем случайное направление как главное для данной волны
	LuaDebugTrace("[Wave]: total "..totalCount.." creatures, main dir= "..mainDir)
	
	local mainDirCnt = totalCount * WAVE_MAIN_DIRECTION_COUNT_MUL / #directionsForAttack -- столько будет крипов на главном направлении
	local countLeft = totalCount 
	for i = 1, #directionsForAttack do -- Решаем сколько будет крипов на всех направлениях кроме главного
		if directionsForAttack[i] ~= mainDir then
			creatureCountByDirection[directionsForAttack[i]] = NormalRandom( (totalCount - mainDirCnt) / (#directionsForAttack - 1), WAVE_CREATURES_DISP )
			countLeft = countLeft - creatureCountByDirection[directionsForAttack[i]]
		end
	end
	creatureCountByDirection[mainDir] = countLeft -- на главное направление пускаем остаток крипов
	PrintArray( creatureCountByDirection )
	
	-- запустить волны по всем дорогам
	currentWaveState = { allFinished = false, st = {}, aliveCount = {}, smartRandomStates = { boss = {}, miniboss = {} } }
	SetGlobalVar( "currentWaveState", currentWaveState )
	
	function AddTrigger( dir )
		local spawnInterval = GetWaveParam( waveNumber, WAVE_SPAWN_INTERVALS )
		if GetGlobalVar( "superabilityUsesCount") >= 2 and RED_DIFFICULTY then
			spawnInterval = spawnInterval*(1-0.3*logicMod )
			LuaDebugTrace("[Wave]: main intervals: " ..spawnInterval)
		end
		if dir == mainDir then spawnInterval = GetWaveParam( waveNumber, WAVE_SPAWN_INTERVALS_MAIN_DIR ) end
		LuaDebugTrace("[Wave]: main dir intervals "..table.concat(WAVE_SPAWN_INTERVALS_MAIN_DIR).." other dir intervals "..table.concat(WAVE_SPAWN_INTERVALS))
		AddTriggerEnd( WaveOnDirection, waveNumber, dir, creatureCountByDirection[dir], spawnInterval )
		currentWaveState.st[dir] = 0
		currentWaveState.aliveCount[dir] = 0
	end
	--[[AddTrigger( "right" )
	AddTrigger( "left" )]]--
	
	for dir, cnt in pairs( creatureCountByDirection ) do 
		AddTrigger( dir )
	end
	
	-- ждать, пока все крипы выйдут
	repeat
		SleepState()
		local allDone = true
		for dir, v in pairs( currentWaveState.st ) do 
			if v <= 0 then allDone = false end
		end
	until allDone
	LuaDebugTrace("FINISHED: [Wave]: all scheduled creeps finished. Waiting for harassment groups" )
	
	-- сообщить WaveOnDirection, что пора перестать слать мелочь
	currentWaveState.allFinished = true
	
	-- ждать, пока остатки будут убиты
	repeat
		SleepState()
		local allDone = true
		for dir, v in pairs( currentWaveState.st ) do 
			if v <= 1 then allDone = false end
		end
	until allDone
	LuaDebugTrace("FINISHED: [Wave] number: "..waveNumber)
end

function GetWaveTotalCreatures() -- возвращает количество живых крипов в данной волне
	local ret = 0
	for dir, v in pairs( currentWaveState.aliveCount ) do 
		ret = ret + v
	end
	return ret
end

-- хитрый рандом. 
--       probability - вероятность ролла. 
--       maxFailReps - максимальное разрешенное количество неудач в ряду испытаний. Если -1, то не используется.
--       maxSuccessReps - максимальное количество успехов в ряду испытаний. Если -1, не используется. 
function SmartRandom( state, probability, maxFailReps, maxSuccessReps )
	state.successReps = state.successReps or 0
	state.failReps = state.failReps or 0
	
	if maxSuccessReps > -1 and state.successReps == maxSuccessReps then
		state.successReps = 0
		state.failReps = 1
		return false
	end
	if maxFailReps > -1 and state.failReps == maxFailReps then
		state.failReps = 0
		state.successReps = 1
		return true
	end
	
	local ret = LuaRandom( 0, 99 ) < probability
	if ret then
		state.successReps = state.successReps + 1
		state.failReps = 0
	else
		state.failReps = state.failReps + 1
		state.successReps = 0;
	end
   
	return ret
end

-- Функция, которая не дает спавнится крипам, пока какое-либо из ограничений на спавн в силе.
-- Ждем, если на нашем направлении крипов больше, чем разрешено для данной волны
-- Ждем, если всего на карте крипов больше, чем разрешено для данной волны
function WaitForStartSpawn( waveNumber, dir, group, aliveCreatures )
	local maxCreatures = GetWaveParam( waveNumber, WAVE_MAX_CREATURES_ON_DIRECTION )
	local maxCreaturesNew = GetWaveParam( waveNumber, WAVE_MAX_CREATURES_ON_DIRECTION_NEW_CREEP )
	local maxCreaturesTotal = GetWaveParam( waveNumber, WAVE_MAX_CREATURES_TOTAL )
	
	local maxCr = maxCreatures
	if not alreadySpawnedGroups[group] then 
		alreadySpawnedGroups[group] = true
		maxCr = maxCreaturesNew
	end
	
	if #aliveCreatures > maxCr then
		LuaDebugTrace("[WaveOnDirection] for dir "..dir..": tool many creatures, waiting " )
	end
	if GetWaveTotalCreatures() > maxCreaturesTotal then
		LuaDebugTrace("[WaveOnDirection] for dir "..dir..": tool many creatures on all directions, waiting " )
	end
	
	while #aliveCreatures > maxCr or GetWaveTotalCreatures() > maxCreaturesTotal do
		if currentWaveState.allFinished or GetGlobalVar( "stopSpawnStandardWaves" ) then return end
	
		SleepState()
		aliveCreatures = GetOnlyAliveUnits( aliveCreatures )
		currentWaveState.aliveCount[dir] = #aliveCreatures
	end
end


-- Набегание крипов на данном направлении.
--        waveNumber - номер волны, dir - направление, cnt - количество крипов на данном направлении
--        spawnInterval - интервал между спавнами
--  Вначале выбираем ранг группы (босс, минибосс, солдат). Потом спавним ее на карту. Ждем интервал spawnInterval. Повторяем сначала.
--  Если в процессе был взорван артефакт, выходим из функции
function WaveOnDirection( waveNumber, dir, cnt, spawnInterval )
	LuaDebugTrace("[WaveOnDirection] for dir "..dir..": STARTED")
	LuaDebugTrace("[WaveOnDirection] for dir "..spawnInterval..": interval")
	
	local left2Spawn = cnt
	local aliveCreatures = {}
	
	while left2Spawn > 0 and not GetGlobalVar( "stopSpawnStandardWaves" ) do	
		-- здесь роллим конкретную группу для спавна
		local group;
		do
			local prob = GetWaveParam( waveNumber, WAVE_BOSSES_ROLL_PROB )
			local rollBoss = SmartRandom( currentWaveState.smartRandomStates.boss, prob, GetWaveParam( waveNumber, WAVE_BOSSES_ROLL_MAX_FAILS ), GetWaveParam( waveNumber, WAVE_BOSSES_ROLL_MAX_SUCCESSES ) )
			if  rollBoss then
				LuaDebugTrace("[WaveOnDirection] rolled boss" )
				group = RollRandomGroup( waveNumber, "bosses" )
			else
				prob = GetWaveParam( waveNumber, WAVE_MINIBOSSES_ROLL_PROB )
				local rollMiniBoss = SmartRandom( currentWaveState.smartRandomStates.miniboss, prob, GetWaveParam( waveNumber, WAVE_MINIBOSSES_ROLL_MAX_FAILS ), GetWaveParam( waveNumber, WAVE_MINIBOSSES_ROLL_MAX_SUCCESSES ) )
				if rollMiniBoss then
					group = RollRandomGroup( waveNumber, "miniBosses" )
					LuaDebugTrace("[WaveOnDirection] rolled miniboss" )
				else
					group = RollRandomGroup( waveNumber, "soldiers" )
					LuaDebugTrace("[WaveOnDirection] rolled soldier" )
				end
			end
		end
		
		-- Группа выбрана.
		LuaDebugTrace("[WaveOnDirection] for dir "..dir..": start spawn group ".. group )
		
		-- Если на выбранном направлении или на карте вообще крипов больше, чем разрешено для данной волны, ждем
		WaitForStartSpawn( waveNumber, dir, group, aliveCreatures )
		if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
		
		-- Спавним группу
		local spawned = SpawnerSpawn( group, factionEnemy )				
		left2Spawn = left2Spawn - #spawned
		LuaDebugTrace("[WaveOnDirection] for dir "..dir..": spawned group ".. group..", "..#spawned.." creatures, "..left2Spawn.." left" )
		WaitState( 1 )
		if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
		
		local spawned2 = GetOnlyAliveUnits( spawned ) -- поспавнились
		PushPathAndApplyFlagBonus( spawned2, dir ) -- Вперед!!! В рукопафную! Посылает крипов в атаку на данном направлении dir
		for i=1, #spawned2 do
			table.insert( aliveCreatures, spawned2[i] )
		end		
		currentWaveState.aliveCount[dir] = #aliveCreatures
		
		local waitStartStep = GetGameStep()
		while GetGameStep() - waitStartStep < spawnInterval * GetStepsCountInSecond() do -- Ждем время равное интервалу между спавном групп spawnInterval
			if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end -- Выходим совсем, если произошел взрывв
			SleepState()	
		end		
	end		
	LuaDebugTrace("[WaveOnDirection] for dir "..dir..": waiting units" )
	while #aliveCreatures > 0 do
		if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
		SleepState()
		aliveCreatures = GetOnlyAliveUnits( aliveCreatures )
		currentWaveState.aliveCount[dir] = #aliveCreatures
	end
	
	LuaDebugTrace("[WaveOnDirection] for dir "..dir..": all scheduled creeps dead, entering harassment mode " )
	currentWaveState.st[dir] = 1
	WaitState(1)
	
	-- Если так получилось, что все крипы выделенные на данное направление уже кончились
	-- А на других еще идет махач, то чтобы не оставлять линию в полном забвении, на ней 
	-- начинает спавнится всякая мелочь.
	
	while not currentWaveState.allFinished and not GetGlobalVar( "stopSpawnStandardWaves" ) do
		local group = RollRandomGroup( waveNumber, "soldiers" ) -- роллятся всегда солдаты
		
		LuaDebugTrace("[WaveOnDirection] for dir "..dir..": start spawn harassment group ".. group )
		WaitForStartSpawn( waveNumber, dir, group, aliveCreatures )
		if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
		
		local spawned = SpawnerSpawn( group, factionEnemy )				
		left2Spawn = left2Spawn - #spawned
		LuaDebugTrace("[WaveOnDirection] for dir "..dir..": spawned harassment group ".. group )
		WaitState( 1 )
		if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
		
		local spawned2 = GetOnlyAliveUnits( spawned )
		PushPathAndApplyFlagBonus( spawned2, dir ) -- Вперед! В рукопафную!
		for i=1, #spawned2 do
			table.insert( aliveCreatures, spawned2[i] )
		end		
		currentWaveState.aliveCount[dir] = #aliveCreatures
		
		LuaDebugTrace("[WaveOnDirection] for dir "..spawnInterval..": interval")
			
		local waitStartStep = GetGameStep()
		while GetGameStep() - waitStartStep < spawnInterval * 20 and not currentWaveState.allFinished do 
			if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
			SleepState()
		end	
	end
	
	LuaDebugTrace("[WaveOnDirection] for dir "..dir..": waiting for harassment units" )
	while #aliveCreatures > 0 do
		if GetGlobalVar( "stopSpawnStandardWaves" ) then currentWaveState.st[dir] = 2; return end
		SleepState()
		aliveCreatures = GetOnlyAliveUnits( aliveCreatures )
		currentWaveState.aliveCount[dir] = #aliveCreatures
	end
	currentWaveState.st[dir] = 2
	LuaDebugTrace("[WaveOnDirection] for dir "..dir..": FINISHED" )
end

-- Запуск задания про Горыныча
function SpawnGorynych()
	local directions = GetAvailableDirections()
	if #directions ~= 1 then
		LuaDebugTrace( "SpawnGorynych: more than one direction left!" )
	end
	GorynychObjective( directions[1] )
end

-- Функция, которая выдает задание про Клыка после первого взрыва и задание про Когтя и Клыка после второго взрыва.
-- принимает в качестве параметра heroesNumber. Если 1 - значит только Клык. Если 2 - значит и Коготь и Клык.
-- по счастливому стечению обстоятельств необходимое количество вражеских героев равно количеству произведенных взрывов.
-- так что при вызове в нее передеается именно количество взрывов. 
function SpawnEnemyHeroes( waveNumber )
	LuaDebugTrace("STARTED: [SpawnEnemyHeroes]")	
	local heroes = ReturnHeroWaveParams( waveNumber )	
	
	if  #heroes == 1 then				
		AddQuest("defeatEnemyHero", true, false)
		
		-- Если герой 1, то выдать задание "Одолейте вражеского героя" (одного)
		DefeatEnemyHeroes( ReturnHeroWaveParams( waveNumber ) )
			
		CompleteQuest("defeatEnemyHero", true, false)		
	else 
		AddQuest("defeatEnemyHeroes", true, false)
		
		-- Если героев больше 1-го, то выдать задание "Одолейте вражеских героев" (много)
		DefeatEnemyHeroes( ReturnHeroWaveParams( waveNumber ) )
		
		CompleteQuest("defeatEnemyHeroes", true, false)	
	end
	
	AddQuest( "chargeArtefact" )	-- после того, как герой (герои) уничтожен, снова выдать квест про зарядку артефакта
		
	LuaDebugTrace("FINISHED: [SpawnEnemyHeroes]")
end

-- Здесь мы ставим на карту вражеских героев. Выдаем им свиту. Ждем, когда они будут уничтожены.
-- supportUnits - массив из которого будем роллить свиту. 
-- supportUnitsCount - количество групп, которые надо нароллить из supportUnits
function DefeatEnemyHeroes( heroes, supportUnits, supportUnitsCount )	

	local directions = GetAvailableDirections()
	local direction = directions[LuaRandom( 1, #directions )] -- выбираем случайное направление для атаки
	local heroesWave = superabilityUsesCount -- определяем как волна героев сейчас
	local heroesInterval, supportUnitsInterval
	
	if heroesWave == 1 then
		heroesInterval = 6
		supportUnitsInterval = 12
	else
		heroesInterval = 11
		supportUnitsInterval = 16
	end

	-- Раз в 4 секунды спавним одну случайную группу свиты. 
	local spawned = {}
	if supportUnits ~= nil then
		for i=1, supportUnitsCount do
			local group = ReturnRandomGroup( supportUnits )
			spawned = SpawnerSpawn( group, factionEnemy )
			supportUnits[ group ] = nil
			
			PushPathAndApplyFlagBonus( spawned, direction )
			local supportUnitsInterval = supportUnitsInterval / supportUnitsCount
			WaitState( supportUnitsInterval )	
		end
	end

	-- если герои были дохлые, резурректим
	for k=1, #heroes do
		local dead, exist = LuaUnitIsDead( heroes[k] )	
		if dead then 
			LuaHeroRespawn( heroes[k] ) 
			DebugTrace("[DefeatEnemyHeroes] hero .."..heroes[k].." has respawned")
		end
	end
	
	local x,y,r = LuaGetScriptArea( direction.."EnemySpawnerArea" )
	--local maxLevel = GetMaxAllyHeroesLevel() -- узнаем, какой сейчас левел у самого крутого игрока в команде
	local maxLevel = GetGlobalVar("LastCreepLevel")
	
	SleepState()
	
	for k=1, #heroes do
		LevelUpHero2( heroes[k], maxLevel + heroesInterval )	-- Выдаем героям левел превышающий уровень крипов
		
		LuaCreatureTeleportTo( heroes[k], x, y )
		LuaHeroAIPushPath( heroes[k], direction.."Path", false ) -- отправляем героев пушить выбранную линию
		if not GetGlobalVar( "towerIsDestroyed" ) then
			AddTriggerEnd( DestroyBase, heroes[k] ) -- Костыль от затупа героя в центре заставы. Чтобы шел крушить доступные цели, если они есть.
		end
		LuaDebugTrace("hero "..heroes[k].." choose direction "..direction)
		SleepState()
	end	
	
	WaitState( 2.0 )
	-- Ждем пока герои не сдохнут
	for k=1, #heroes do
		local dead, exist
		repeat 
			SleepState()
			dead, exist = LuaUnitIsDead( heroes[k] ) 
		until dead 
	end
end

-- Заставляет вражеского героя не тупить в центре, а искать на заставе доступные цели
function DestroyBase( hero )
	WaitForUnitInArea( hero, "ruinedCastle" )
	if not GetGlobalVar( "towerIsDestroyed" ) then
		LuaHeroAIGuardScriptArea( hero, "ruinedCastle", false )
		LuaDebugTrace("[DestroyBase]: hero "..hero.." looks for target within base")
	end
end



-- ========================== MISC =============================
-- #############################################################


function Step()
	if threadsReport > 0 then
		threadsReport = threadsReport - 1
		if threadsReport == 0 then
			LuaDebugTrace( "Game state @ step "..GetGameStep().." START-------------------------------------------------------" );
			DumpStates()
			PrintTable( rootobj.globalVars )
			LuaDebugTrace( "Game state @ step "..GetGameStep().." END---------------------------------------------------------" );
		end
	end
end

-- Возвращает количество доступных для атаки направлений
function GetAvailableDirections()
	local directions = {}
	for direction, isForbidden in pairs( forbiddenDirections ) do
		if not isForbidden then
			table.insert( directions, direction )
		end
	end
	table.sort( directions )
	LuaDebugTrace("[AvailableDirections] Directions Count: " .. tostring(#directions) )
	
	return directions
end

function CountKillsTotal()
	local i
	local sum = 0	
	for i = 1, #allyHeroes do
		sum = sum + LuaHeroGetKillsTotal( allyHeroes[i] )
	end
	return sum
end



function GetOnlyAliveUnits( spawned )
	local spawned2 = {}
	for i = 1,#spawned do
		--local dead, exists = LuaUnitIsDead( spawned[i] )
		if not UnitIsRealyDead( spawned[i] )  then
			table.insert( spawned2, spawned[i] )
		end
	end
	return spawned2
end

function ResurrectWaitingHeroes()
	local dead, exist = false, false
	for i=1, #allyHeroes do	
		dead, exist = LuaUnitIsDead( allyHeroes[i] )
		if dead and exist then
			LuaHeroRespawn( allyHeroes[i] )	
		end
	end
end

function ShowHintWhileAnomalyNotDestroyed()
	while GetGlobalVar("superability_killsCounter") ~= 0 do 
		HintLineWait( "timeToDestroyBridge", 5)
		SleepState() 
	end
end

-- спамит на минимап сигналом в местах кнопок, пока кнопка не нежата
function SpamSignalWhileButtonNotPressed( signalX, signalY, delay )
	local signal = {x = signalX, y = signalY}	
	local elapsedSleeps = 0
	local oldCount = GetGlobalVar( "superabilityUsesCount" )

	LuaCreateMinimapSignal( signalX, signalY )
	repeat
		if elapsedSleeps > delay * GetStepsCountInSecond() then
			LuaCreateMinimapSignal( signalX, signalY )
			elapsedSleeps = 0
		end
		elapsedSleeps = elapsedSleeps + 1
		SleepState()
	until GetGlobalVar( "superabilityUsesCount" ) ~= oldCount
end

-- Отправляет юнитов unitList пушить направление direction
function PushPathAndApplyFlagBonus( unitList, direction ) 
	local startPositionX, startPositionY = LuaGetScriptArea( direction.."EnemySpawnerArea" ) -- стартовая зона в начале указанного направления
	local pathName = direction.."Path" -- pathName это объект на карте. Для каждого из направлений он задает траекторию движения по ним. 
	
	TeleportUnitList( unitList, startPositionX, startPositionY ) -- ставим всех юнитов в стартовую зону
	
	for i = 1,#unitList do
		LuaApplyPassiveAbility( unitList[i], "flagpolesBonus" )	-- выдаем юнитам бонус от флагов									
		LuaSetCreepBehavior( unitList[i], "PathMove", pathName, 15 ) -- Отправляем их пушить путь 
	end
end

-- Вызывается при взрыве артефакта. убивает всех крипов на карте.
function KillAllCreeps()
	local enemyCreeps = LuaGetAllUnits( factionEnemy, BitMask( UnitTypeCreep, UnitTypeSiegeCreep, UnitTypeNeutralCreep, UnitTypeNeutralChampion, UnitTypeSummon ) )
	local nafta = 0
	for i=1, #enemyCreeps do 
		nafta = nafta + LuaGetUnitStat(enemyCreeps[i], StatNaftaForKill )
		LuaKillUnit( enemyCreeps[i] ) 		
		DebugTrace("[KillAllCreeps] unit "..enemyCreeps[i].." killed by script")
	end
	WaitState(2.5)
	LuaDebugTrace("[KillAllCreeps] totalNafta = "..nafta)
	if nafta > 5000 then nafta = 5000 end	
	for i=1, #allyHeroes do
		LuaHeroAddPrime( allyHeroes[i], nafta/#allyHeroes )
		LuaDebugTrace("[KillAllCreeps] hero "..allyHeroes[i].." gets "..nafta.." prime for creeps")
		LuaHeroAddPrime( allyHeroes[i], 500 )
		LuaDebugTrace("[KillAllCreeps] hero "..allyHeroes[i].." gets "..nafta.." prime for creeps and "..tostring(500).." for explosion")
	end	
end

-- Получает уровень самого крутого героя в команде игроков
function GetMaxAllyHeroesLevel()
	local maxLevel = LuaHeroGetLevel( allyHeroes[1] )	
	for i=2, #allyHeroes do		
		if LuaHeroGetLevel( allyHeroes[i] ) > maxLevel then
			maxLevel = LuaHeroGetLevel( allyHeroes[i] )
		end
	end	
	return maxLevel
end

-- Апдейтит статы героя в момент его возрождения
function UpdateHeroStats( hero )
	LuaDebugTrace("[UpdateHeroStats] for hero "..hero)
	local index = 0
	for i=1, #enemyHeroes do 
		if hero == enemyHeroes[i] then
			index = i
			break
		end
	end
	LuaDebugTrace("[UpdateHeroStats] index is "..index)	
	if index then
		LuaDebugTrace("[UpdateHeroStats] hero is "..enemyHeroes[index])
		UnicHeroStats (hero, enemyStats [index])
	end
end

function UnicHeroStats( hero, statsData )
	LuaDebugTrace("[UnicHeroStats] for hero "..hero)
	local stats = statsData["stats"]
	local bonus = statsData["bonus"]
	local distributedBonusPoints = CopyArray( GetGlobalVar("distributedBonusPoints"..hero) )
	PrintArray( distributedBonusPoints )
	local points = 0
	local level = GetGlobalVar("LastCreepLevel") or GetGlobalVar("enemyHeroLevel") -- на случай, если крипы еще не вышли берем уровень героев
	for i=1, #stats do
		LuaDebugTrace("level = "..level..", bonus = "..bonus[i]..", distributedBonusPoints = "..distributedBonusPoints[i])
		points = level * bonus[i] / 36 - distributedBonusPoints[i]
		distributedBonusPoints[i] = distributedBonusPoints[i] + points		
		LuaDebugTrace("[UnicHeroStats]: points = "..points..", distributedBonusPoints["..i.."] = "..distributedBonusPoints[i])
		LuaDebugTrace("[UnicHeroStats]: hero ".." init stat "..tostring(stats[i]).." = "..LuaGetUnitStat( hero, stats[i] ))
		LuaSetUnitStat( hero, stats[i], LuaGetUnitStat( hero, stats[i] ) + points)
		LuaDebugTrace("[UnicHeroStats]: hero ".." updated stat "..tostring(stats[i]).." = "..LuaGetUnitStat( hero, stats[i] ))
	end
	SetGlobalVar("distributedBonusPoints"..hero, distributedBonusPoints)
end

function GetTimeInvetval ()
	local TIME_BETWEEN_WAVES = TIME_BETWEEN_WAVES or 0
		if GetGlobalVar( "superabilityUsesCount") >= 2 and RED_DIFFICULTY then -- Интервал между волнами
			TIME_BETWEEN_WAVES = 15*(1-0.3*logicMod) 
			LuaDebugTrace("[GetTimeInvetval]: it's red difficulty!")
		else
			TIME_BETWEEN_WAVES = 15
		end
	return TIME_BETWEEN_WAVES
end

-- Техническая функция. По dbid крипа возвращает его "человеческое" имя
function GetCreepNameByDBID( dbid )
	local name = "unknown"
	if string.find( dbid, "Normal1/PvE_Coop1_Support", 1, true ) then
		name = "Faun"
	elseif string.find( dbid, "Normal1/PvE_Coop1_Melee", 1, true ) then
		name = "Satir-warrior"
	elseif string.find( dbid, "Champion1/PvE_Coop1", 1, true ) then
		name = "Leshij"
	elseif string.find( dbid, "Champion3/PvE_Coop1_Tank", 1, true ) then
		name = "Black Spriggan"
	elseif string.find( dbid, "Champion3/PvE_Coop1", 1, true ) then
		name = "Spriggan"
	elseif string.find( dbid, "Normal3/PvE_Coop1_shrinker", 1, true ) then
		name = "Borovik shrinker"
	elseif string.find( dbid, "Normal3/PvE_Coop1_Ordinary", 1, true ) then
		name = "Borovik ordinary"
	elseif string.find( dbid, "Normal3/PvE_Coop1_Poisoner", 1, true ) then
		name = "Borovik poisoner"
	elseif string.find( dbid, "Normal4/PvE_Coop1_Summoner", 1, true ) then
		name = "Kikimor florist"
	elseif string.find( dbid, "Normal4/PvE_Coop1", 1, true ) then
		name = "Kikimor"
	elseif string.find( dbid, "Normal7/PvE_Coop1", 1, true ) then
		name = "Scissor hands"
	elseif string.find( dbid, "Normal8/PvE_Coop1", 1, true ) then
		name = "Ghost"
	elseif string.find( dbid, "Normal5/PvE_Coop1", 1, true ) then
		name = "Druzhastik"
	elseif string.find( dbid, "Normal2/PvE_Coop1_DD", 1, true ) then
		name = "Demolitioner"
	elseif string.find( dbid, "Normal6/PvE_Coop1_Support", 1, true ) then
		name = "Harpooner"
	elseif string.find( dbid, "Minion2/PvE_Coop1", 1, true ) then
		name = "Kobold range"
	elseif string.find( dbid, "Minion1/PvE_Coop1", 1, true ) then
		name = "Rogatik"
	elseif string.find( dbid, "Minion5/PvE_Coop1", 1, true ) then
		name = "Kobold melee"
	elseif string.find( dbid, "Minion3/PvE_Coop1_Killer", 1, true ) then
		name = "Assida poisoner"
	elseif string.find( dbid, "Minion3/PvE_Coop1_Killer2", 1, true ) then
		name = "Assida kamikazi"
	elseif string.find( dbid, "Champion2/PvE_Coop1_AntiAoE", 1, true ) then
		name = "Alkonost"
	elseif string.find( dbid, "Champion2/PvE_Coop1_Suppport", 1, true ) then
		name = "Sirin"
	elseif string.find( dbid, "Boss1/PvE_Coop1", 1, true ) then
		name = "Gorynych"
	elseif string.find( dbid, "EvilTree/PvE_Coop1", 1, true ) then
		name = "EvilTree"
	elseif string.find( dbid, "Normal10/PvE_Coop1", 1, true ) then
		name = "Ognedemon"
	elseif string.find( dbid, "Minion4/PvE_Coop1", 1, true ) then
		name = "Krysa"
	elseif string.find( dbid, "Summons/Whisper/PvE_Coop1", 1, true ) then
		name = "Trigonometers"	
	elseif string.find( dbid, "Normal8/PvE_Coop1_Regenerat", 1, true ) then
		name = "Regenerat"				
	else 	
		name = "unknown"
		LuaDebugTrace("ERROR! [GetCreepNameByDBID]: unknown creep dbid "..dbid)
	end
	
	return name
end

function ArtifactSuperabilityFull ()
	SetGlobalVar("superability_killsCounter", 100)
end

function BotsAIOn( countBots )

	leaders = tonumber(countBots)
	
	if leaders == nil then 
		leaders = 1 
	elseif leaders >= #allyHeroes-1 then
		leaders = #allyHeroes-1
		debugBotsAIGuardAreaHeroesCount = 0
	end
	
	if debugBotsAI2Players then leaders = 2 end
	for i=2, leaders+1 do
		LuaHeroAIFollowHero( allyHeroes[i], "local" )
		LuaHeroAIReceiveMinimapSignals( allyHeroes[i], true )
	end
	if debugBotsAIGuardAreaHeroesCount > 0 then	
		for i=leaders+2, #allyHeroes do
			LuaHeroAIGuardScriptArea(allyHeroes[i], "ruinedCastle", true)
		end
	end
end