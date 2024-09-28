LuaDebugTrace("START")
include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("Maps/PvE/Series/PvECommon.lua")

allyHeroes = {}

function Init()
	PvECommonInit()
    InitHeroes()
    AllyHeroesFollowPlayer()
    
    AddTriggerEnd( GorynychTest )
end

function InitHeroes()
	local allyCandidates = { "10","11","12","13","14" }
	if LuaGetLocalFaction() == FACTION_DOCT then 
		allyCandidates = {"00","01","02","03","04" }
	end
	
	local i = 0
	for i = 1,#allyCandidates do
		local dead, exist = LuaUnitIsDead( allyCandidates[i] )
		if exist then 
			table.insert( allyHeroes, allyCandidates[i] )
		end
	end
	LuaDebugTrace("allyHeroes: ".. #allyHeroes )
end

function AllyHeroesFollowPlayer()
    for i=2, #allyHeroes do
        LuaHeroAIFollowHero( allyHeroes[i], allyHeroes[ 1 ] )
        LuaHeroAIReceiveMinimapSignals( allyHeroes[i], true )
    end
end

function GorynychTest()
    local bossCounter = 1
    
    while true do 
        local x, y, radius = LuaGetScriptArea("gorynychTrigger")
        local bossName = "gorynych_w"..tostring(bossCounter).."_c1"
        local dead, exist
        repeat
            hx, hy = LuaHeroGetPosition("local")
            dead, exist = LuaUnitIsDead( bossName )
            SleepState()	
        until not dead and (math.sqrt(DistanceSquared(hx, hy, x, y)) <= radius)
        
        LuaSetCreepBehavior( bossName, "PathMove", "gorynychPath", 5 )
        
        repeat
            dead, exist = LuaUnitIsDead( bossName )
            SleepState()
        until dead
        bossCounter = bossCounter + 1
    end
end

