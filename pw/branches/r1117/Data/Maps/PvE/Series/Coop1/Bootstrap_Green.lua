 
 CREEP_STAT_BUDGET_PARAMS = {
	x1 = 2,
	y1 = 4,
	x2 = 36,
	y2 = 10,
	x_max = 24,
	
	y_max = 25, -- основная настройка сложности. 28 - очень просто. 42 - очень сложно
}

TOWER_LIFE_INCREMENT = 1000

WAVE_SPAWN_INTERVALS = { 20, 18, 18, 10 }
WAVE_SPAWN_INTERVALS_MAIN_DIR = { 18, 18, 16, 7 }
TIME_BETWEEN_WAVES = 40

GREEN_DIFFICULTY = true 
INIT_CREEP_STAT_MODIFIER = 0.5

FOREST_CREEP_MIN_SPAWN_INTERVAL = 60
ARTIFACT_COUNTER_BONUS = 12

 ENEMY_HERO_REFINE_RATE = 1
 
 STATS_WEREWOLF = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }
 STATS_FAIRY = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }
 STATS_NAGA = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }
 STATS_WITCHDOCTOR = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }
 STATS_MANAWYRM = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }
 STATS_HUNTER = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {0,     0, 			0,			   0,	 		0,		  0, 			 0, 			 0 } }
 
 FIRST_WAVE_HEROES = {1}
 SECOND_WAVE_HEROES = {1,2}
 
 include ("Maps/PvE/Series/Coop1/script.lua")

 
