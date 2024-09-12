 
 CREEP_STAT_BUDGET_PARAMS = {
	x1 = 2,
	y1 = 4,
	x2 = 36,
	y2 = 4,
	x_max = 24,
	
	y_max = 45, -- основна€ настройка сложности. 38 - очень просто. 54 - очень сложно
}
 
 TOWER_LIFE_INCREMENT = 4000
 
 --WAVE_SPAWN_INTERVALS = { 20, 18, 18, 10 }
 --WAVE_SPAWN_INTERVALS_MAIN_DIR = { 18, 18, 16, 7 }
 --FOREST_CREEP_MIN_SPAWN_INTERVAL = 45
 
 INIT_CREEP_STAT_MODIFIER = 0.7
 
 -- “ут были голубые талантсеты с 2 звездами
 
  ENEMY_HERO_REFINE_RATE = 1
 STATS_WEREWOLF = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {769,     77, 			7,			   6,	 		6,		  6, 			 54, 			 0 } }
 STATS_FAIRY = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {623,     9, 			54,			   17,	 		8,		  6, 			 66, 			 0 }} 
 STATS_NAGA = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {1885,     32, 			2,			   0,	 		46,		  6, 			 27, 			 142 } }
 STATS_WITCHDOCTOR = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {1044,     0, 			96,			   23,	 		16,		  76, 			 0, 			 0 } }
 STATS_MANAWYRM = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {423,     0, 			99,			   18,	 		6,		  28, 			 2, 			 570 } }
 STATS_HUNTER = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {650,     92, 			0,			   28,	 		18,		  71, 			 0, 			 0 } }
 
 FIRST_WAVE_HEROES = {1,2}
 SECOND_WAVE_HEROES = {1,2,3}
 
 include ("Maps/PvE/Series/Coop1/script.lua")

 
