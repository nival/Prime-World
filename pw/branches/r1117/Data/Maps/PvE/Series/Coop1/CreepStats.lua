
-- constants
STATS_BUDGET_BY_LEVEL = {}

if INIT_CREEP_STAT_MODIFIER == nil then
	INIT_CREEP_STAT_MODIFIER = 1.1
end


CREEP_STAT_BUDGET_PARAMS = CREEP_STAT_BUDGET_PARAMS or 
    {
        x1 = 2,
        y1 = 4,
        x2 = 36,
        y2 = 4,
        x_max = 24,
        
        y_max = 45, -- основная настройка сложности. 38 - очень просто. 54 - очень сложно
    }

function FillCreepStatsArray()
	local a1 = (CREEP_STAT_BUDGET_PARAMS.y_max - CREEP_STAT_BUDGET_PARAMS.y1) / (CREEP_STAT_BUDGET_PARAMS.x_max - CREEP_STAT_BUDGET_PARAMS.x1)
	local b1 = CREEP_STAT_BUDGET_PARAMS.y1 - CREEP_STAT_BUDGET_PARAMS.x1 * a1
	local a2 = (CREEP_STAT_BUDGET_PARAMS.y2 - CREEP_STAT_BUDGET_PARAMS.y_max) / (CREEP_STAT_BUDGET_PARAMS.x2 - CREEP_STAT_BUDGET_PARAMS.x_max)
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
	
	PrintArray( STATS_BUDGET_BY_LEVEL )
end

STAT_COLUMNS = {                                StatLife,       StatStrength,   StatIntellect,  StatWill,       StatStamina,    StatDexterity,   StatAttackSpeed, StatLifeRegenerationAbsolute    }
STAT_PERCENTS = {
 ["Minion1/PvE_Coop1"] =          {percents = { 19,             17,             0,              21,             21,              0,  			 21  }, modifier = 0.37,
								   initStats= { 300,            14,             0,              30,             30,              50,             35  } },-- Рогатики
["Champion1/PvE_Coop1_big"] =     {percents = {  39,            11,             10,              15,             15,              0,  			 10   }, modifier = 1.11,
									initStats={ 3000,           20,             0,              50,             50,              50,             50  } },-- Толстый Леший, для квеста Три толстяка
 ["Champion1/PvE_Coop1"] =        {percents = { 57,             14,             0,              13,             13,              0,  			 4   }, modifier = 1.11,
								   initStats= { 3300,           28,             0,              50,             50,              50,             50  } },-- Леший
 ["Normal1/PvE_Coop1_Support"] =  {percents = { 26,             0,              30,             22,             22,              0,  			 0   }, modifier = 0.47, 
									initStats= {530,            0,              18,             25,             20,              50,             40  } },-- Сатир шаман (Фавн)
 ["Normal1/PvE_Coop1_Melee"] =    {percents = { 23,             30,             0,              20,             20,              0,  			 7  }, modifier = 0.62,
 									initStats= { 700,           33,             0,              30,             30,              50,             40  } },-- Сатир воен 
 ["Champion3/PvE_Coop1"] =        {percents = { 63,             15,             0,              9,              9,               0,  			 4   }, modifier = 1.2,
 									initStats= {3800,           25,             0,              40,             40,              50,             50  } },-- Спригган
 ["Champion3/PvE_Coop1_Tank"] =   {percents = { 18,             32,             0,              25,             25,              0,  			 0   }, modifier = 0.67,
 									initStats= {800,            25,             0,              40,             40,              50,             50  } },-- Черный Спригган
 ["LittleBorovik"] =			  {percents={ 0,              0,             0,              0,              0,               0,  			 0   }, modifier = 1.0,
 									initStats= {1,               0,              0,             0,              0,               0,              0   } },-- Боровик-уменьшитель
 ["Normal3/PvE_Coop1_shrinker"] = {percents = { 35,             28,             14,             9,              9,               0,  			 5   }, modifier = 1.28,
 									initStats= {1700,           70,             50,             40,             40,              50,             50  } },-- Боровик-уменьшитель
 ["Normal3/PvE_Coop1"] =          {percents = { 35,             28,             14,             9,              9,               0,  			 5   }, modifier = 1.28, 
 									initStats= {1700,           70,             50,             40,             40,              50,             50  } },-- Боровик-отравитель
 ["Normal3/PvE_Coop1_ordinary"] = {percents = { 35,             28,             14,             9,              9,               0,  			 5   }, modifier = 1.28,
 									initStats= {1700,           70,             50,             40,             40,              50,             50  } },-- Обычный боровик
 ["Normal4/PvE_Coop1_Summoner"] = {percents = { 32,             0,              32,             18,             18,              0,  			 0   }, modifier = 1.05,
 									initStats= {2000,           0,              45,             50,             30,              50,             20  } },-- Кикимор-цветовод
 ["Normal4/PvE_Coop1"] =          {percents = { 32,             0,              32,             18,             18,              0,  			 0   }, modifier = 1.05, 
 									initStats= {2000,           0,              45,             50,             30,              50,             20  } },-- Обычный кикимор
 ["Normal7/PvE_Coop1"] =          {percents = { 10,             21,             24,             12,             12,              16, 			 6   }, modifier = 1.4, 
 									initStats= { 800,           90,             60,             40,             40,              60,             65  } },-- Руки-ножницы
["Normal8/PvE_Coop1_Regenerat"] = {percents =    { 8,           0,              8,              14,             14,              14,  			 21  }, modifier = 0.8, 
 									initStats= {250,            0,             40,              37,             37,              50,             50  } },-- Регенерат
["Normal8/PvE_Coop1"] =           {percents = {  8,             0,              23,             17,             17,              23, 			 11  }, modifier = 1.2,
 									initStats= { 650,           0,             100,             25,             25,              60,             70  } },-- Призрак									
["Normal5/PvE_Coop1"] =           {percents = { 27,             47,              0,             13,             13,              0,  			 0   }, modifier = 0.85,
 									initStats= {1200,           60,             0,              35,             50,              50,             35  } },-- Зубастик
 ["Normal2/PvE_Coop1_DD"] =       {percents = { 29,             0,              33,             19,             19,              0,  			 0   }, modifier = 0.6,
 									initStats= {800,            0,              25,             30,             30,              50,             40  } },-- Подрывник
 ["Normal6/PvE_Coop1_Support"] =  {percents = { 24,             0,              35,             18,             18,              0,  			 6  }, modifier = 0.7,
 									initStats= {750,            0,              45,             20,             20,              50,             40  } },-- Водяной
 ["Minion2/PvE_Coop1"] =          {percents = { 17,             31,             0,              17,             17,              17,  			 0   }, modifier = 0.4,
 									initStats= { 200,           15,             0,              20,             20,              50,             50  } },-- Кобольд-швыряка
 ["Minion5/PvE_Coop1"] =          {percents = { 19,             23,             0,              19,             19,              19,  			 0   }, modifier = 0.45,
 									initStats= {350,            17,             0,              24,             24,              50,             50  } },-- Кобольд-трудяга
 ["Minion3/PvE_Coop1_Killer"] =   {percents = { 10,             0,              38,             26,             26,              0,  			 0   }, modifier = 0.35, 
 									initStats= {150,            0,              20,             20,             20,              50,             50  } },-- Ассида-комикадзе
 ["Minion3/PvE_Coop1_Killer2"] =  {percents = { 20,             24,             0,              14,             14,              14,			 14  }, modifier = 0.4,
 									initStats= {250,            20,             0,              20,             20,              50,             50  } },-- Ассида-отравитель
 ["Champion2/PvE_Coop1_AntiAoE"] ={percents = { 19,             0,              33,             24,             24,              0,  			 0   }, modifier = 0.55,
 									initStats= {500,            0,              22,             55,             10,              50,             30  } },-- Алконост
 ["Champion2/PvE_Coop1_Suppport"]={percents = { 19,             0,              33,             24,             24,              0,  			 0   }, modifier = 0.55, 
 									initStats= {500,            0,              22,             55,             10,              50,             30  } },-- Сирин
 ["Boss1/PvE_Coop1"] =            {percents = { 63,             31,             0,              1,              1,               2,  			 2   }, modifier = 2.5, 
 									initStats= {22000,          400,            0,              150,            150,             150,            150  } },-- Горыныч
["Normal10/PvE_Coop1"] =          {percents = { 49,             20,             11,              10,              10,               0,  			 9   }, modifier = 1.2, 
 									initStats= {3000,           60,             0,              50,             50,              50,             50  } },-- Огнедемон
["EvilTree/PvE_Coop1"] =          {percents = { 14,             65,             0,              11,              11,               0,  			 0   }, modifier = 3.1, 
 									initStats= {3000,           500,            0,              37,             37,              50,             10  } },-- Злодрево																		
["Minion4/PvE_Coop1"] =          {percents = {  50,             13,             0,              13,             13,              0,  			 13   }, modifier = 1.2, 
 									initStats= {1500,           35,             0,              37,             37,              50,             40 } },-- Крысобрюх																											
["Summons/Whisper/PvE_Coop1"] = {percents = {  30,              0,            50,              10,             10,               0,  			 0    }, modifier = 0.7, 
 									initStats= {800,             0,            30,              37,             37,              50,             50 } },-- Злогоньки																																				
["Champion4/PvE_Coop1"] =       {percents = {  31,              14,            34,             10,              10,               0,  			 0    }, modifier = 1.5, 
 									initStats= {3500,           100,            0,              50,             50,              50,             30 } }, --Избушка
									
["Melee1/PvE_Coop1_Dude"] =          {percents = { 23,             30,             0,              20,             20,              0,  			 7  }, modifier = 0.62,
 									initStats= { 700,           33,             0,              30,             30,              50,             40  } }, -- Беженец Адорнийцев и Доктов (как Сатир воин)																			
}
                                                                                                              			

STAT_TO_HEALTH = 20

SPAWNEDCREEPS = {}
function UpgradeCreepStats( creep )
	local level = LuaGetUnitStat( creep, StatLevel )
	local lastMaxLevel = GetGlobalVar ("LastCreepLevel")
	if level > lastMaxLevel then
		SetGlobalVar("LastCreepLevel", level) -- запоминаем последний проспавнейшися уровень крипа, чтобы передать его героям
	end
	local dbid = LuaUnitGetDbid( creep )
	local creepName = GetCreepNameByDBID( dbid )
	
	if SPAWNEDCREEPS[ creepName ] == nil then 
		SPAWNEDCREEPS[ creepName ] = 1
	else 
		SPAWNEDCREEPS[ creepName ] = SPAWNEDCREEPS[ creepName ] + 1
	end
	
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
	
	PrintArray( distr )
	LuaDebugTrace("[UpgradeCreepStats] modifier = "..modifier)
	
	LuaDebugTrace("UpgradeCreepStats: creep level = "..level)
    local budget = 0
    for i = 1, level do
        budget = budget + STATS_BUDGET_BY_LEVEL[ math.min( #STATS_BUDGET_BY_LEVEL, i ) ]
    end
	budget = budget * INIT_CREEP_STAT_MODIFIER 

	local totalVal = 0
	for i, val in ipairs( distr ) do
		totalVal = totalVal + val
	end
	if totalVal == 0 then totalVal = 1 end
	
	LuaDebugTrace("UpgradeCreepStats: creep name "..creepName)
	for i, val in pairs( distr ) do
		local inc = val / totalVal * budget		
		local stat = STAT_COLUMNS[ i ]
		if stat == StatLife then inc = inc * STAT_TO_HEALTH end
		inc = inc * modifier
		
		local oldVal = initStats[ i ] * INIT_CREEP_STAT_MODIFIER	
        LuaDebugTrace("UpgradeCreepStats: stat "..stat.." : "..oldVal.."->"..oldVal + inc )
		LuaSetUnitStat( creep, stat, oldVal + inc )
	end
	
end