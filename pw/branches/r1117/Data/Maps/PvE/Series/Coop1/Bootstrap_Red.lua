 
 CREEP_STAT_BUDGET_PARAMS = {
	x1 = 2,
	y1 = 4,
	x2 = 36,
	y2 = 6,
	x_max = 23,
	
	y_max = 70, -- основная настройка сложности. 48 - очень просто. 72 - очень сложно
}
 
 TOWER_LIFE_INCREMENT = 8000
 RED_DIFFICULTY = true 
 INIT_CREEP_STAT_MODIFIER = 1.45

  -- Тут были оранжевые талантсеты с 9 звездами
 
  ENEMY_HERO_REFINE_RATE = 1
 STATS_WEREWOLF = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {6702,     282, 			125,			   111,	 		108,		  64, 			 185, 			 50 } }
 STATS_FAIRY = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {7187,     100, 			272,			   166,	 		115,		  183, 			 23, 			 812 }} 
 STATS_NAGA = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {7717,     154, 			100,			   85,	 		312,		  82, 			 74, 			 955 } }
 STATS_WITCHDOCTOR = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {6919,     100, 			334,			   116,	 		97,		  188, 			 56, 			 815 } }
 STATS_MANAWYRM = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {5340,     100, 			349,			   89,	 		112,		  152, 			 10, 			 2842 } }
 STATS_HUNTER = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {6557,     321, 			100,			   152,	 		135,		  170, 			 20, 			 138 } }

ENEMY_HERO_STATS_BONUS = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
						   bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }

 FIRST_WAVE_HEROES = {1,2,3}
 SECOND_WAVE_HEROES = {1,2,3,4}
 
 WAVE_SPAWN_INTERVALS = { 12, 13, 14, 14 }
 WAVE_SPAWN_INTERVALS_MAIN_DIR = { 9, 9, 10, 10 }
 
 LuaDebugTrace("Difficulty is RED")
 
 include ("Maps/PvE/Series/Coop1/script.lua")

 
