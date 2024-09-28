
include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

--require "pluto"

fountainAx = 20
fountainAy = 175
fountainBx = 384
fountainBy = 166
battleFrontAx = 215
battleFrontAy = 210
battleFrontBx = 205
battleFrontBy = 210

function GlobalCounter()
	SetGlobalVar( "GlobalCounter", 1 )
	while true do
		SleepState()
		currentGlobalCounter = GetGlobalVar( "GlobalCounter" ) + 1
		SetGlobalVar( "GlobalCounter", currentGlobalCounter )
		if currentGlobalCounter % 10 == 0 then
			LuaDebugTrace( "GlobalCounter = " .. tostring(currentGlobalCounter) )
		end
	end
end

function StepsInformer( msg )
	local firstStep = GetGameStep()
	PrintToChatAndTrace( "Start StepsInformer from step " .. tostring(firstStep) )
	while true do
		SleepState()
		local stepsDelta = GetGameStep() - firstStep 
		if stepsDelta % 50 == 0 then
			PrintToChatAndTrace( tostring(stepsDelta) .. " steps from " .. msg )
		end
	end
end

function HealthCare( creature, minHealthPercent, fountainX, fountainY )
	local healed = true
	while true do
		local currentHealth, currentMaxHealth = TestLuaUnitGetHealth( creature )
		if healed then
			if 100 * currentHealth / currentMaxHealth < minHealthPercent then
				AddStateTop2( creature, WaitForHealing, creature )
				AddStateTop2( creature, GoToPosition, creature, fountainX, fountainY, 10 )
				PrintToChatAndTrace( creature .. " is going to heal" )
				healed = false
			end
		else
			if currentHealth == currentMaxHealth then
				PrintToChatAndTrace( creature .. " is healed" )
				healed = true
			end
		end
		SleepState()
	end
end

--[[
function Leveluper( hero )
	while true do
		for level = 0, 5 do
			talentActivated = false
			for slot = 0, 5 do
				if LuaHeroCanActivateTalent( hero, level, slot ) then
					LuaHeroActivateTalent( hero, level, slot, false )
					talentActivated = true
					break
				end
			end
			if talentActivated then
				break
			end
		end
		
		if LuaHeroGetLevel( hero ) == 36 then
			return
		end
		
		SleepState()
	end
end
]]--

function WaitForHealing( creature )
	PrintToChatAndTrace( creature .. " is starting to wait for heal" )
	while true do
		local currentHealth, currentMaxHealth = TestLuaUnitGetHealth( creature )
		if currentHealth == currentMaxHealth then
			PrintToChatAndTrace( creature .. " finished waiting for heal" )
			return
		end
		SleepState()
	end
end


function TestIsUnitInArea( unitName, x, y, range )
	local hx, hy = TestLuaUnitGetPosition( unitName )
	if ( DistanceSquared( hx, hy, x, y ) < range * range ) then
		return true
	end
	return false
end


function GoToPosition( creature, x, y, minRange )
	PrintToChatAndTrace( creature .. " is going to position [" .. tostring(x) .. "," .. tostring(y) .. "]" )
	TestLuaCreatureMoveTo( creature, x, y, 1 )
	while true do
		SleepState()
		if TestIsUnitInArea( creature, x, y, minRange ) then
			PrintToChatAndTrace( creature .. " arrived to [" .. tostring(x) .. "," .. tostring(y) .. "]" )
			return
		else
			if not LuaCreatureIsMoving( creature ) then
				--PrintToChatAndTrace( creature .. " is going again to position [" .. tostring(x) .. "," .. tostring(y) .. "]" )
				TestLuaCreatureMoveTo( creature, x, y, 1 )
			end
		end
	end
end


function WaitForStart( steps )
	local startStep = GetGameStep()
	while true do
		local stepsLeft = steps - (GetGameStep() - startStep)
		PrintToChatAndTrace( tostring(stepsLeft) )
		if  stepsLeft == 0 then
			PrintToChatAndTrace( "Fight!" )
			return
		end
		SleepState()
	end
end


function Fight( creature, battleFrontX, battleFrontY )
	AddStateTop2( creature, GoToPosition, creature, battleFrontX, battleFrontY, 6 )
	PrintToChatAndTrace( creature .. " is going to the battle front" )
	while true do
		SleepState()
		if not TestIsUnitInArea( creature, battleFrontX, battleFrontY, 20 ) then
			if not LuaCreatureIsMoving( creature ) then
				AddStateTop2( creature, GoToPosition, creature, battleFrontX, battleFrontY, 6 )
				PrintToChatAndTrace( creature .. " is going to the battle front" )
			end
		end
	end
end


function Init( isReconnecting )
	if not isReconnecting then
		AddStateTop( GlobalCounter )
		AddLocalTriggerTop( StepsInformer, "game start" )
		for team = 0, 1 do
			for hero = 0, 4 do
				local currentHero = tostring(team) .. tostring(hero)
				--AddStateStack( currentHero )
				if team == 0 then
					AddStateTop2( currentHero, Fight, currentHero, battleFrontAx, battleFrontAy )
					AddTriggerTop( HealthCare, currentHero, 20, fountainAx, fountainAy )
				else
					AddStateTop2( currentHero, Fight, currentHero, battleFrontBx, battleFrontBy )
					AddTriggerTop( HealthCare, currentHero, 20, fountainBx, fountainBy )
				end
				AddStateTop2( currentHero, WaitForStart, 30 )
				--AddTriggerTop( Leveluper, currentHero )
			end
		end
	else
		AddLocalTriggerTop( StepsInformer, "reconnect" )
	end
end
