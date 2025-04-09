 
 CREEP_STAT_BUDGET_PARAMS = {
	x1 = 2,
	y1 = 4,
	x2 = 36,
	y2 = 2,
	x_max = 23,
	
	y_max = 50, -- основная настройка сложности. 42 - очень просто. 62 - очень сложно
}

TOWER_LIFE_INCREMENT = 5000

 INIT_CREEP_STAT_MODIFIER = 0.8
-- Тут были фиолетовые талантсеты с 2 звездами

 ENEMY_HERO_REFINE_RATE = 1
 STATS_WEREWOLF = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {1508,     117, 			21,			   14,	 		13,		  10, 			 86, 			 0 } }
 STATS_FAIRY = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {1239,     24, 			88,			   32,	 		18,		  94, 			 11, 			 77 }} 
 STATS_NAGA = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {2941,     57, 			3,			   4,	 		78,		  11, 			 41, 			 344 } }
 STATS_WITCHDOCTOR = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {1813,     0, 			143,			   37,	 		25,		  108, 			 0, 			 11 } }
 STATS_MANAWYRM = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {958,     0, 			151,			   30,	 		18,		  43, 			 4, 			 1258 } }
 STATS_HUNTER = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {1265,     135, 			0,			   46,	 		32,		  101, 			 3, 			 0 } }
 
  ENEMY_HERO_STATS_BONUS = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
						   bonus = {0,     0, 			 0,			   0,	 		0,		  0, 			 0, 			 0 } }
 
 FIRST_WAVE_HEROES = {1,2}
 SECOND_WAVE_HEROES = {1,2,3}
 
 include ("Maps/PvE/Series/Coop1/script.lua")

 
