
function DeathManager( heroName, canRevive, canBeRevived )	
	LuaDebugTrace("deathManager for hero "..heroName.." STARTED")
	
	if canRevive then
		LuaApplyPassiveAbility( heroName, "applRevive")
	end
	if canBeRevived then
	   LuaApplyPassiveAbility( heroName, "applRevived")
	   LuaUnitAddFlag( heroName, ForbidDeath )
	end
	
	table.insert(allyHeroes, {name = heroName, isAlive = true, reviver = canRevive})

	while true do
		while LuaUnitGetHealth( heroName ) > 5 do 
			SleepState() 
		end
		
		LuaDebugTrace("DeathManager DEBUG: hero "..heroName.." is dead!")
		allyHeroes[ GetValueIndexByName( heroName, allyHeroes ) ].isAlive = false

		while LuaUnitGetHealth( heroName ) < 50 do
			SleepState()
		end		
		
		LuaDebugTrace("DeathManager DEBUG: Hurrey! I'm alive again!")
		allyHeroes[ GetValueIndexByName( heroName, allyHeroes ) ].isAlive = true
		
		SleepState()
	end
end



