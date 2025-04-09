 
 CREEP_STAT_BUDGET_PARAMS = {
	x1 = 2,
	y1 = 4,
	x2 = 36,
	y2 = 6,
	x_max = 23,
	
	y_max = 58, -- основная настройка сложности. 48 - очень просто. 72 - очень сложно
}
 
 TOWER_LIFE_INCREMENT = 7000
 
 INIT_CREEP_STAT_MODIFIER = 1.1
 
 -- Тут были оранжевые талантсеты, с 7 звездами
 
  ENEMY_HERO_REFINE_RATE = 1
 STATS_WEREWOLF = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {5043,     229, 			85,			    102,	 		101,		  42, 			 191, 			 50 } }
 STATS_FAIRY = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {5525,     70, 			217,			   129,	 		127,		  149, 			 50, 			 630 }} 
 STATS_NAGA = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {6023,     112, 			70,			   78,	 		280,		  58, 			 94, 			 788 } }
 STATS_WITCHDOCTOR = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {5178,     70, 			276,			   106,	 		91,		  152, 			 32, 			 584 } }
 STATS_MANAWYRM = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {3924,     70, 			287,			   83,	 		101,		  119, 			 38, 			 2644 } }
 STATS_HUNTER = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
  bonus = {4905,     265, 			70,			   138,	 		123,		  136, 			 44, 			 56 } }
 
 ENEMY_HERO_STATS_BONUS = { stats = {StatLife, StatStrength, StatIntellect, StatStamina, StatWill, StatDexterity, StatAttackSpeed, StatEnergy }, 
						   bonus = {0,     0, 			 0,			   0,	 		0,		  0, 			 0, 			 0 } }
 
 FIRST_WAVE_HEROES = {1,2}
 SECOND_WAVE_HEROES = {1,2,3}
 
 include ("Maps/PvE/Series/Coop1/script.lua")

 
