function Superability( iva )
	AddQuest( "chargeArtefact" )
	
	for i=1, #allyHeroes do			
		LuaSubscribeUnitEvent( allyHeroes[i], EventDeath, "SuperabilityKillEvent")-- Подписываемся на функцию SuperabilityKillEvent, которая будет запускаться каждый раз, когда кто-то кого-то убил
		LuaSubscribeUnitEvent( allyHeroes[i], EventAbilityStart, "SuperabilityPushButton") -- Подписываемся на функцию SuperabilityPushButton, которая будет запускаться каждый раз, когда кто-то нажал на кнопку
	end
	
	while true do 
		while GetGlobalVar( "PauseBetweenWaves" ) == true do SleepState() end		-- Если между волнами пауза (сразу после взрыва, пока набегают кобольды или приходят вражеские герои), то не считаем трупы	
		local counter = 0
		repeat 
			SleepState()
			counter = GetGlobalVar("superability_killsCounter")-- получаем количество трупов ( считается в функции SuperabilityKillEvent )
		until counter >= SUPERABILITY_KILLS_COUNTER 	-- как только количество покойников достигло лимита артефакта (100), выходим	
				
		for i=1, #DIRECTIONS do
			if not forbiddenDirections[ DIRECTIONS[i] ] then-- по всем доступным направлениям
				local buttonName = DIRECTIONS[i].."Button"
				LuaUnitApplyApplicator( buttonName, "buttonActivateAppl" ) --активируем кнопку, чтобы ее можно было  нажать
				LuaCreatureHide( buttonName, false ) -- показываем кнопку
				local signalX, signalY = LuaUnitGetPosition( buttonName )
				AddTriggerEnd( SpamSignalWhileButtonNotPressed, signalX, signalY, 10 )  -- спамим на минимап сигнал с интервалом в 10 секунд
			end
		end
		
		--AddTriggerEnd( ShowHintWhileAnomalyNotDestroyed )
		
		CompleteQuest( "chargeArtefact" ) -- комплитим квест "зарядите артефакт"
		
		AddQuest( "explodeArtefact", false, false )  -- добавляем квест "взорвите прайм-аномалию"

		SetGlobalVar("superability_triggeredBy", nil)  -- инициализируем переменную, в которой будем хранить имя героя, нажавшего на кнопку
    SetGlobalVar("superability_direction", nil )
		local exploder = nil
		repeat 
			SleepState()
			exploder = GetGlobalVar("superability_triggeredBy") -- получаем имя героя, который нажал на кнопку ( имя присваивается в функции SuperabilityPushButton )
		until exploder ~= nil -- ждем пока в переменную exploder не запишется имя героя, взорвавшего артефакт

		LuaUnitApplyApplicatorFromUnit( exploder,  exploder, "artifactExplodedEvent" ) -- аппликатор artifactExplodedEvent есть в dictinary. Он показывает анонсмент "Прайм-взрыв"

		AddTriggerEnd( SuperabilityExplode, exploder, GetGlobalVar("superability_direction") ) -- Запускаем отображение взрыва артефакта и рассеивания облака
		SetGlobalVar( "stopSpawnStandardWaves", true ) -- Говорим всем заинтересованным функциям, что сейчас не время для спавна стандартных волн мобов

        local timer = 0
		repeat 
			SleepState()
			counter = GetGlobalVar("superability_killsCounter")
			timer = timer + GetStepLengthInSeconds()
		until counter == 0 or timer > 2.5-- ждем пока счетчик трупов не обнулится (это случится после того, как закончится визуализация взрыва в функции SuperabilityExplode)
		
		CompleteQuest( "explodeArtefact" ) -- завершаем квест "Взорвите Прайм-аномалию"
		--AddTriggerEnd( HintLineWait, "hintLine_waveRepealed", 5 )
		SetGlobalVar("superability_triggeredBy", nil)
		SetGlobalVar("AfterExplosionTimeInterval", true)
		SetGlobalVar( "superabilityUsesCount", GetGlobalVar("superabilityUsesCount") + 1 )			-- увеличиваем на 1 счетчик количества взрывов артефакта					
				
		LuaDebugTrace("[Superability] Artefact explode. Rest time")
		
		local TIME_BETWEEN_WAVES = TIME_BETWEEN_WAVES or 30  -- время паузы после взрыва
		AddQuest( "nextWaveIn", "sec", TIME_BETWEEN_WAVES ) -- отображаем "квест" "до следующей атаки осталось:"	
		local n = 0
		repeat 
			WaitState(1)
			n = n + 1
			SetQuestParams( "nextWaveIn", "sec", TIME_BETWEEN_WAVES - n) -- раз в секунду передаем в UI квеста nextWaveIn параметр sec, который равен количеству оставшихся до конца паузы секунд (обратный отсчет)
		until n == TIME_BETWEEN_WAVES -- как только время паузы кончилось, выходим
		CompleteQuest( "nextWaveIn" ) -- удаляем квест "до следующей атаки осталось"
		
		SetGlobalVar( "stopSpawnStandardWaves", false ) -- говорим всем заинтересованным функциям, что стандартные волны мобов снова могут спавнится
		LuaDebugTrace("[Superability] Artefact explode. End of rest")		
        
		if GetGlobalVar("superabilityUsesCount") == 3 then -- выходим из функции, если артефакт взорван 3 раза (перед приходом Горыныча то есть)
			break
		end		
	end
	
end

validVictims = { [UnitTypeHeroMale]=1,[UnitTypeCreep]=1,[UnitTypeSiegeCreep]=1,[UnitTypeNeutralCreep]=1,[UnitTypeNeutralChampion]=1,[UnitTypeNeutralBoss]=1,[UnitTypeFactionChampion]=1 }
-- список типов юнитов, которых можно учитывать в счетике убитых врагов.

-- Функция запускается каждый раз, когда кто-то кого-то убил. Здесь victim - имя жертвы, killer - имя убийцы, qualifiedKiller - имя убийцы, рассчитанное по логике "казуального ластхита"
-- Функция обновляет счетчик трупов в UI и через глобальную переменную superability_killsCounter сообщает другим функциям о количестве трупов
function SuperabilityKillEvent( hero, victim, killer, qualifiedKiller )	
	if string.find( victim, "summon_", 1, true ) then return end  -- если убит саммон, нам это неинтересно, сразу выходим
	if string.match( victim, '^.%d', 1, true ) then return end  -- если убит саммон, нам это неинтересно, сразу выходим
	
	local victimType = LuaGetUnitType( victim ) -- определяем тип жертвы
	if qualifiedKiller ~= hero then return end -- если убийца не герой, то нам это не интересно, выходим
	if not validVictims[victimType] then return	end -- если тип жертвы не входит в список допустимых (массив validVictims ) опять же выходим
	
	if GetGlobalVar("PauseBetweenWaves") then return end -- если жертва убита во время паузы между волнами, выходим. Мы не обновляем счетчик в это время.
	
	local points = 1
	if victimType == UnitTypeNeutralChampion then
		points = 3 -- если жертва - крип типа чемпион, даем 3 очка за убийство
	end
	
	local counter = GetGlobalVar("superability_killsCounter")
	if  counter < SUPERABILITY_KILLS_COUNTER then
		counter = counter + points
		if counter > SUPERABILITY_KILLS_COUNTER then counter = SUPERABILITY_KILLS_COUNTER end  -- если каунтер превысил лимит артефакта, например было 99, был убит леший и стало 102, то значение каунтера насильно выставляем = 100
		SetQuestProgress( "chargeArtefact", counter )		-- обновляем счетчик трупов в UI
		if counter == SUPERABILITY_KILLS_COUNTER then -- если при этом убийстве артефакт зарядился
			LuaUnitApplyApplicatorFromUnit( hero,  hero, "artifactChargedEvent" ) -- показываем анонсмент "Артефакт заряжен"
			LuaUnitApplyApplicatorFromUnit( hero, hero, "AddNaftaForLastKill" ) -- Даем герою прайм за сей подвиг
		end
	end
	LuaDebugTrace( victim )
	SetGlobalVar("superability_killsCounter", counter) -- обновляем глобальную переменную, храняющую количество трупов. Используется другими функциями
end

-- Запускается каждый раз, когда нажата кнопка. hero - имя героя, нажавшего на кнопку
-- записывает в глобальную переменную superability_triggeredBy имя героя, нажавшего на кнопку
function SuperabilityPushButton( hero, ability, target )
	local dbid = LuaGetDbid( "pushTheButtonAblt" )
	if dbid ~= ability then
		return
	end

	local exploder = nil
	exploder = GetGlobalVar("superability_triggeredBy")
	if exploder ~= nil then
		return
	end
	
	local buttonId = target.objectId
	
  -- прячем остальные кнопки сразу, чтобы их нельзя было нажать
	for i = 1, #DIRECTIONS do
    local direction = DIRECTIONS[i]
    if not forbiddenDirections[ direction ] then
      local button = direction.."Button"
      if buttonId ~= LuaGetObjectId( button ) then
        LuaUnitApplyApplicator( button, "buttonDeactivateAppl" ) --деактивируем кнопку
        LuaCreatureHide( button, true ) -- прячем ее
      else
        forbiddenDirections[ direction ] = true -- записываем в массив запрещенных направлений заблокированное направление
        LuaDebugTrace("Button push: "..hero.." uses ".. ability .. " at " .. direction )
        SetGlobalVar("superability_triggeredBy", hero)
        SetGlobalVar("superability_direction", direction )
      end
		end
	end
end

-- Запускается после нажатия на кнопку. hero - имя героя, нажавшего на кнопку
-- Отображает взрыв артефакта, уничтожает всех вражеских крипов, поднимает все флаги на карте
function SuperabilityExplode( hero, direction )
	local x, y = LuaUnitGetPosition( "local" )
	LuaUnitAddFlag( hero, ForbidMove ) -- временно запрещаем "взрывателю" бегать
		
	LuaPlaceClientEffect( "shockWave", x, y) 
	WaitState( 0.65 )

  LuaCreatureHide( direction.."Button", true )
  LuaRemoveMinimapIcon( direction.."RoanEndIcon" )
  
  local cloudX, cloudY = LuaGetScriptArea( direction.."CloudPoint")
	LuaUnitRemoveFlag( hero, ForbidMove ) -- снова разрешаем герою бегать

    LuaPlaceStandaloneEffect(  "cloudEnd", "cloudEnd", cloudX, cloudY )
    WaitState( 0.5 ) 
    LuaCreatureHide( direction.."Cloud", true )
    WaitState (1)
	x, y = LuaUnitGetPosition( hero )
	LuaChangeNatureMapXY( x, y, 100, -1, factionPlayer )		-- меняем террейн на карте на родную землю игрока

	LuaDebugTrace("DEBUG: [SuperabilityExplode] Mega effect")	
	AddTriggerEnd( KillAllCreeps ) -- убиваем всех вражеских крипов
	RaiseAllFlags( hero ) -- поднимаем все флаги
	
	SetGlobalVar( "superability_killsCounter", 0 ) -- выставляем счетчик трупов врагов в 0
	ResurrectWaitingHeroes() --Оживляем всех павших героев
	
	WaitState( 5 )
	--LuaRemoveStandaloneEffect( "explosion"..hero );
    LuaRemoveStandaloneEffect( "cloudEnd" )    
end