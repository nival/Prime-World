
-- constants
STATS_BUDGET_BY_LEVEL = {}

INIT_CREEP_STAT_MODIFIER = 0.9

HERO_REFINE_RATE = 1
--ENEMY_HERO_TALENT_SET = "enemyTalentSet"
--WITCHER_TALENT_SET = "witcherTalenSet"
--HAGRI_TALENT_SET = "rockmanTalentSet"

CREEP_STAT_BUDGET_PARAMS = CREEP_STAT_BUDGET_PARAMS or 
    {
        x1 = 2,
        y1 = 4,
        x2 = 36,
        y2 = 4,
        x_max = 24,
        
        y_max_per_force = 0.3,
    }

function FillCreepStatsArray( mapForce )
    local y_max = CREEP_STAT_BUDGET_PARAMS.y_max_per_force * mapForce
    
	local a1 = (y_max - CREEP_STAT_BUDGET_PARAMS.y1) / (CREEP_STAT_BUDGET_PARAMS.x_max - CREEP_STAT_BUDGET_PARAMS.x1)
	local b1 = CREEP_STAT_BUDGET_PARAMS.y1 - CREEP_STAT_BUDGET_PARAMS.x1 * a1
	local a2 = (CREEP_STAT_BUDGET_PARAMS.y2 - y_max) / (CREEP_STAT_BUDGET_PARAMS.x2 - CREEP_STAT_BUDGET_PARAMS.x_max)
	local b2 = CREEP_STAT_BUDGET_PARAMS.y2 - CREEP_STAT_BUDGET_PARAMS.x2 * a2
	local peakLevel = CREEP_STAT_BUDGET_PARAMS.x_max
	
	LuaDebugTrace("[FillCreepStatsArray]: a1 = "..a1..", b1 = "..b1)
	LuaDebugTrace("[FillCreepStatsArray]: a2 = "..a2..", b1 = "..b2)
	LuaDebugTrace("[FillCreepStatsArray]: peak level = "..peakLevel)
	
	for level = 1, 36 do 
		if level < peakLevel then
			STATS_BUDGET_BY_LEVEL[ level ] = a1 * level + b1
		else
			STATS_BUDGET_BY_LEVEL[ level ] = a2 * level + b2
		end
	end
	
	LuaDebugTrace("[FillCreepStatsArray]: STATS_BUDGET_BY_LEVEL: ")
	PrintArray( STATS_BUDGET_BY_LEVEL )
end

STAT_COLUMNS = {                                StatLife,       StatStrength,   StatIntellect,  StatWill,       StatStamina,    StatDexterity,   StatAttackSpeed    }
STAT_PERCENTS = {
-- АДОРНИЙЦЫ
 --[[["B/Melee1/PvE"] =               {percents =  { 20,            20,            0,               20,             20,              0,  			 20  }, modifier = 0.4,
							      initStats=   { 400,           20,            0,               37,             37,              40,             60  } },-- Адорнийцы солдаты
 ["B/Melee1/PvE_Ep1_NoControl"] = {percents =  { 20,            20,            0,               20,             20,              0,  			 20  }, modifier = 0.4,
								   initStats=  { 400,           20,            0,               37,             37,              40,             60  } },-- Адорнийцы. Квестодатель квеста про сирин
 ["B/Melee2/PvE1"] =  			  {percents =  { 22,            11,            0,               22,             22,              0,  			 22  }, modifier = 0.3, 
									initStats= { 270,           10,            0,               37,             37,              40,             60  } },-- Адорнийцы. Тигра
 ["B/Range/PvE1"] =   			 {percents =   { 21,            0,             17,              21,             21,              0,  			 21 }, modifier = 0.4,
 									initStats= { 150,           0,             16,              37,             37,              40,             25  } },-- Адорнийцы. Лучник 
-- ДОКТЫ
 ["A/Melee1/PvE"] =               {percents = { 20,             20,            0,               20,             20,              0,  			 20 }, modifier = 0.4,
							      initStats=  { 400,            20,            0,               37,             37,              40,             60  } },-- Докты солдаты
 ["A/Melee1/PvE_Ep1_NoControl"] = {percents = { 20,             20,            0,               20,             20,              0,  			 20  }, modifier = 0.4,
								   initStats= { 400,            20,            0,               37,             37,              40,             60  } },-- Докты. Квестодатель квеста про сирин
 ["A/Melee2/PvE"] =  			  {percents = { 22,             11,            0,               22,             22,              0,  			 22  }, modifier = 0.3, 
									initStats={ 270,            10,            0,               37,             37,              40,             60  } },-- Докты. Кабан
 ["A/Range/PvE"] =   			 {percents =  { 21,             0,             17,              21,             21,              0,  			 21 }, modifier = 0.4, 
 									initStats={ 150,            0,             16,              37,             37,              40,             25  } },-- Докты. Стрелок ]]--
-- Нейтралы									
 ["Normal1/PvE_Ep1_Melee"] =      {percents = { 23,             30,             0,             20,             20,               0,  			 7   }, modifier = 0.62,
 								initStats =   { 700,            33,             0,             30,             30,               50,             40  } },-- Сатир. Melee
 ["Normal1/PvE_Ep1_Range"] =   	{percents =   { 26,             0,              30,            22,             22,               0,  			 0   }, modifier = 0.47,
 								initStats=    { 530,            0,              18,            25,             20,               50,             40  } },-- Сатир. Range
 ["Normal3/PvE_Ep1"] =          {percents =   { 25,             25,             0,             25,             25,               0,  			 0   }, modifier = 0.9,
 								initStats=    { 1500,           30,             0,             40,             40,               50,             50  } },-- Боровик
 ["Normal4/PvE_Ep1"] =          {percents =   { 25,             0,              33,            21,             21,               0,  			 0   }, modifier = 1, 
 								initStats=	  { 1500,           0,              45,            50,             30,               50,             20  } },-- Кикимор
 ["Normal6/PvE_Ep1"] = 			{percents =   { 32,             0,              32,            16,             16,               0,  			 5   }, modifier = 0.35,
 								initStats=    { 400,            0,              20,            20,             20,               50,             40  } },-- Водяной
 ["Champion2/PvE_Ep1"] = 		{percents =   { 19,             0,              33,            24,             24,               0,  			 0   }, modifier = 0.55,
 								initStats=    { 500,            0,              22,            55,             10,               50,             30  } },-- Обычная сирин
 ["Champion2/PVE_Ep1_NoControl"] ={percents = { 19,             0,              33,            24,             24,               0,  			 0    }, modifier = 0.55, 
 								initStats=    { 500,            0,              22,            55,             10,               50,             30  } },-- Квестовая сирин
 ["Champion1/PvE_Ep1"] =          {percents = { 57,             14,             0,             13,             13,               0, 			 4   }, modifier = 0.85, 
 									initStats={ 2500,           28,             0,             50,             50,               50,             50  } },-- Леший
 ["Champion3/PvE_Ep1"] =        {percents =	  { 63,             15,             0,             9,              9,                0, 			 4  }, modifier = 0.9,
 								initStats= 	  { 3000,           25,             0,             40,             40,               50,             50  } },-- Спригган
 ["Minion1/PvE_Ep1"] =          {percents =   { 19,             17,             0,             21,             21,               0,  			 21  }, modifier = 0.37,
 								initStats=    { 300,            14,             0,             30,             30,               50,             35  } },-- Рогатик
 ["Minion2/PvE_Ep1"] =       {percents =      { 17,             31,             0,             17,             17,               17,  			 0   }, modifier = 0.4,
 								initStats= 	  { 200,            15,             0,             20,             20,               50,             50  } },-- Кобольд. Range
 ["Minion5/PvE_Ep1"] = 			 {percents =  { 19,             23,             0,             19,             19,               19,  			 0  }, modifier = 0.45,
 								initStats=    { 350,            17,             0,             24,             24,               50,             50  } }-- Кобольд. Melee
}
                                                                                                              			

STAT_TO_HEALTH = 20

SPAWNEDCREEPS = {}

PAUSE_LEVELUP_AFTER = 30 -- сколько секунд игрок не должен ничего делать, чтобы крипы перестали левелапиться

function UpgradeCreepStats( creep )
	local level = LuaGetUnitStat( creep, StatLevel )
	local dbid = LuaUnitGetDbid( creep )
	
	local distr = nil
	local modifier = 1
	local initStats = nil
	for i, v in pairs( STAT_PERCENTS ) do
		if string.find( dbid, i, 1, true ) then 
			distr = v.percents
			modifier = v.modifier
			initStats = v.initStats
			break
		end
	end
	
	if not distr then
		LuaDebugTrace("UpgradeCreepStats: no creep "..dbid.." in table")
		return 
	end
	
	DebugTrace("[UpgradeCreepStats] creep "..creep..", level= "..level..", modifier = "..modifier)
	--PrintArray( distr )
    
    local budget = 0
    for i = 1, level do
        budget = budget + STATS_BUDGET_BY_LEVEL[ math.min( #STATS_BUDGET_BY_LEVEL, i ) ]
    end
	budget = budget * INIT_CREEP_STAT_MODIFIER 

	local totalVal = 0
	for i, val in ipairs( distr ) do
		totalVal = totalVal + val
	end

	LuaDebugTrace("UpgradeCreepStats: creep name "..dbid)
	for i, val in pairs( distr ) do
		local inc = val / totalVal * budget		
		local stat = STAT_COLUMNS[ i ]
		if stat == StatLife then inc = inc * STAT_TO_HEALTH end
		inc = inc * modifier
		
		local oldVal = initStats[ i ] * INIT_CREEP_STAT_MODIFIER	
        DebugTrace("UpgradeCreepStats: stat "..stat.." : "..oldVal.."->"..oldVal + inc )
		LuaSetUnitStat( creep, stat, oldVal + inc )
	end
	
end

function LevelupTimer()
    local prevPause = false
    while true do
        local stepsToLastCommand = GetGameStep() - LuaGetLastPlayerActivityStep() 
        
        local pause = LuaIsDialogFinished( "" ) and stepsToLastCommand > PAUSE_LEVELUP_AFTER * GetStepsCountInSecond()
        
        if prevPause ~= pause  then
            DebugTrace( "Levelup paused: ".. tostring( pause ) )
            LuaSetCreepsLevelupPaused( pause )
            prevPause = pause
        end
        
        SleepState()
    end
end