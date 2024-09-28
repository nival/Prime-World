

--constants

PRESETS = { 
	{  --preset 1
		--heroReplaces = { heroes = {"heroWerewolfA", "heroWerewolfB"}, talents = { WEREWOLF_TALENT_SET, WEREWOLF_TALENT_SET } },
		heroWaves = { 
			{
				heroes = FIRST_WAVE_HEROES,
				support = { Kikimor2=2, Vodyanoi1=2, Sirin1 = 1, Leshij1=1 },
				supportGroups = 2
			},
			{
				heroes = SECOND_WAVE_HEROES,
				support = { Leshij1=0.5, Leshij2=0.5, Kikimor1=2, DemolitionMan1 = 2, Assassin1 = 1 },
				supportGroups = 3
			},
		},
		soldiers = {
			{Kobolds1 = 2, Rogatiki1 = 2}, -- цыфры это частота появления групп.
			{_prev=true, Assida2 = 1, Satyrs1 = 3 },
			{Kobolds1 = 2, Rogatiki1 = 2, Satyrs1 = 3, Assida2 = 1}, -- кол-во потенциальных спавнов на порядковый номер волны
			{Kobolds1 = 2, Rogatiki1 = 2, Satyrs1 = 3, Assida2 = 2},
			{Kobolds1 = 1, Rogatiki1 = 1, Satyrs1 = 3, Assida2 = 1}
		},
		miniBosses = {
			{ DemolitionMan1 = 1, Assassin1 = 2 },
			{ Vodyanoi1 = 1, DemolitionMan1 = 1, Assassin1 = 1, Assassin2 = 1, Sirin1 = 1},
			{ Vodyanoi1 = 1, DemolitionMan1 = 2, DemolitionMan2 = 2, Assassin1 = 1, Assassin2 = 1, Sirin1 = 1, Sirin2 = 1, SirinHealer = 1},
			{ _prev=true, Assida1 = 1, Zubastik1 = 1 },
			{ _prev=true, Zubastik2 = 1},
			{ Vodyanoi1 = {1,3}, DemolitionMan1 = {1,3}, DemolitionMan2 = {1,3}, Assassin1 = 1, Assassin2 = {1,3}, Sirin1 = {1,3}, Sirin2 = {1,3}, Assida1 = {1,3}, Zubastik1 = {1,3}, Zubastik2 = {1,3}, SirinHealer = {1,3}}
		},
		bosses = {
			{Satyrs1 = 1},
            {Leshij1 = 1, Borovik1 = 1, Kikimor1 = 1 },
            {Leshij1 = {1,3}, Borovik1 = {1,3}, Kikimor1 = {1,3}, Kikimor2 = {1,3} },
            {_prev=true, Leshij2 = {1,3} },
            {_prev=true, Borovik2 = {1,3},  Kikimor3 = {1,3} },
            {LeshijAlone = {1,3}, Leshij2 = {1,3}, BorovikAlone = {1,3}, Borovik2 = {1,3}, KikimorAlone = {1,3}, Kikimor3 = {1,3}, Spriggan1 = {1,3}, Spriggan2 = {1,3} }
		},
		bossesTypes = {"LeshijAlone", "BorovikAlone", "KikimorAlone", "Kikimor3", "Spriggan1"}
	},
	{  --preset 2
		--heroReplaces = { heroes = {"heroFairyA", "heroFairyB"}, talents = { FAIRY_TALENT_SET, FAIRY_TALENT_SET }  },
		heroWaves = { 
			{
				heroes = FIRST_WAVE_HEROES,
				support = { Kikimor2=2, Vodyanoi1=2, Sirin1 = 1, Leshij1=1 },
				supportGroups = 2
			},
			{
				heroes = SECOND_WAVE_HEROES,
				support = { Leshij1=0.5, Leshij2=0.5, Kikimor1=2, DemolitionMan1 = 2, Assassin1 = 1 },
				supportGroups = 3
			},
		},
		soldiers = {
			{Kobolds1 = 2, Rogatiki1 = 2},
			{_prev=true, Trigonometers = 2, Satyrs1 = 3 }, 
			{Kobolds1 = 2, Rogatiki1 = 2, Satyrs1 = 3, Trigonometers = 2}, 
			{Kobolds1 = 2, Rogatiki1 = 2, Satyrs1 = 3, Trigonometers = 2},
			{Kobolds1 = 1, Rogatiki1 = 1, Satyrs1 = 3, Trigonometers = 2}
		},
		miniBosses = {
			{ DemolitionMan1 = 1, Assassin1 = 2 },
			{ Regenerat = 1, DemolitionMan1 = 1, Assassin1 = 1, Ratmaw = 1, Sirin1 = 1}, 
			{ Regenerat = 1, DemolitionMan1 = 2, DemolitionMan2 = 2, Assassin1 = 1, Ratmaw = 1, Sirin1 = 1, Sirin2 = 1, SirinHealer = 1}, 
			{ _prev=true, Assida1 = 1, Zubastik1 = 1 },
			{ _prev=true, Zubastik2 = 1},
			{ Regenerat = {1,3}, DemolitionMan1 = {1,3}, DemolitionMan2 = {1,3}, Assassin1 = 1, Ratmaw = {1,3}, Sirin1 = {1,3}, Sirin2 = {1,3}, Assida1 = {1,3}, Zubastik1 = {1,3}, Zubastik2 = {1,3}, SirinHealer = {1,3}}
		},
		bosses = {
			{Satyrs1 = 1},
            {Leshij1 = 1, Ognedemon = 1, Kikimor1 = 1 },
            {Leshij1 = {1,3}, Ognedemon = {1,3}, Kikimor1 = {1,3}, EvilTree = {1,3} },
            {_prev=true, Leshij2 = {1,3} },
            {_prev=true, Borovik2 = {1,3},  Kikimor3 = {1,3} },
            {LeshijAlone = {1,3}, Leshij2 = {1,3}, BorovikAlone = {1,3}, Ognedemon = {1,3}, EvilTree = {1,3}, Kikimor3 = {1,3}, Spriggan1 = {1,3}, Izbushka = {1,3} }
		},
		bossesTypes = {"LeshijAlone", "Ognedemon", "Kikimor1", "EvilTree", "BorovikAlone", "Spriggan1", "Izbushka"}
	}	
}

function InitAttackersPresets( reconnecting )
	local presets = #PRESETS
	presetNumber = -1
	if not reconnecting then
		--local p = LuaRandom( 1, presets ) --_NOT_COMMIT
		p = 2
		presetNumber = p
		LuaDebugTrace("Selected preset: ".. p .. " of "..presets )
		SetGlobalVar( "ActiveCreepsPreset", p )
	end
	
	local function MergeArray( arrayFrom, arrayTo )
		for i, v in pairs( arrayFrom ) do
			arrayTo[ i ] = v
		end
	end
	local function PrepareGroups( groups )
		if not groups then return end
		local prev = {}
		for i = 1, #groups do 
			if groups[i]._prev then
				groups[i]._prev = nil
				MergeArray( prev, groups[i] )
			end
			prev = groups[i]
			for spawnerName, weight in pairs(groups[i]) do
				if type(weight) == "table" then
					groups[i][spawnerName] = LuaRandom( weight[1], weight[2] )
				end		
			end
		end
	end
	local preset = PRESETS[ GetGlobalVar( "ActiveCreepsPreset" ) ]
	PrepareGroups( preset.soldiers )
	PrepareGroups( preset.miniBosses )
	PrepareGroups( preset.bosses )
	
	DebugTrace("Preprocessed preset: " )
	PrintTable( preset )

	--local heroesCount = math.min( #enemyHeroes, #preset.heroReplaces.heroes )
	heroesCount = 3
	local heroesNames   = { "Hunter", 		   "Manawyrm",          "WitchDoctor",          "Naga",          "heroFairyB",     "heroWerewolfA",     "heroWerewolfB" }
	local heroesStats = { STATS_HUNTER, STATS_MANAWYRM, STATS_WITCHDOCTOR, STATS_NAGA, STATS_FAIRY, STATS_WEREWOLF, STATS_WEREWOLF }
	local indexes = {}	
	local k=0
	local index
	SetGlobalVar("enemyHeroLevel", 1)
	for i = 1, #enemyHeroes do 
		if #indexes == 0 then
			LuaDebugTrace("[InitAttackersPresets] indexes is empty. Refill")
			for i=1, #heroesNames do indexes[i] = i end 
			PrintArray( indexes )
		end
		k = LuaRandom(1, #indexes)
		index = indexes[k]
		LuaDebugTrace("[InitAttackersPresets] k = "..k..", hero is "..heroesNames[index])
		LuaSetCreepFaction( enemyHeroes[i], factionEnemy )
		LuaHeroReplace( enemyHeroes[i], heroesNames[index] )
		enemyStats[i] = heroesStats[index]
		--LuaLoadTalantSet( enemyHeroes[i], heroesTalents[index] )	
		UnicHeroStats( enemyHeroes[i], heroesStats[index] )		
		table.remove( indexes, k )
		PrintArray( indexes )
	end
	-- for i = 1,heroesCount do 
		-- LuaSetCreepFaction( enemyHeroes[i], factionEnemy )
		-- LuaHeroReplace( enemyHeroes[i], preset.heroReplaces.heroes[i] )
		-- LuaLoadTalantSet( enemyHeroes[i], preset.heroReplaces.talents[i] )
	-- end
end

-- возвращает настройки волны с героями по ее номеру waveNumber
-- returns: список героев, список крипов для ReturnRandomGroup, количество груп
function ReturnHeroWaveParams( waveNumber )
	LuaDebugTrace("ReturnHeroWaveParams for wave "..waveNumber)
	local preset = PRESETS[ GetGlobalVar( "ActiveCreepsPreset" ) ].heroWaves	
	local wave = preset[ math.min( waveNumber, #preset ) ]

	local heroes = {}
	for i = 1, #wave.heroes do
		table.insert( heroes, enemyHeroes[ wave.heroes[i] ] )
	end
	
	return heroes, wave.support, wave.supportGroups
end

function RollRandomGroup( waveNumber, groupType )
	local preset = PRESETS[ GetGlobalVar( "ActiveCreepsPreset" ) ][groupType]
	if not preset then
		LuaDebugTrace("Invalid group type :  ".. groupType )
		return nil
	end
	
	local groups = preset[ math.min( waveNumber, #preset ) ]

	--groups = {Izbushka = 1 } --_NOT_COMMIT	
	
	return ReturnRandomGroup( groups )
end

-- Возвращает случайную группу с учетом ее веса
-- например массив {Assassin = 1, Kobolds = 9}
-- это значит, что ReturnRandomGroup в среднем в 9 случаях из 10-ти будет возвращать кобольдов
-- а в 1-м случае из 10-ти - Убийцу
function ReturnRandomGroup( groups )
	local sum = 0
    local groupNames = {}
	for spawnerName, weight in pairs(groups) do
		sum = sum + weight
        table.insert( groupNames, spawnerName )
	end
    table.sort( groupNames )
    
	local groupIndex = LuaRandom( 1, sum )
	DebugTrace("[ReturnRandomGroup] groupIndex = "..groupIndex..", sum = "..sum)
	sum = 0
	for i, spawnerName in ipairs( groupNames ) do
		sum = sum + groups[spawnerName]
		DebugTrace("[ReturnRandomGroup] sum = "..sum)
		if sum >= groupIndex then
			DebugTrace("[ReturnRandomGroup] spawnerName = "..spawnerName)
			return spawnerName
		end		
	end
end

