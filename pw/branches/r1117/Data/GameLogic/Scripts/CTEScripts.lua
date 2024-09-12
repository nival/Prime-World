------------------------------------------------------------------------------------------------------
-- CTEScripts.lua 
-- Script for CTE map
------------------------------------------------------------------------------------------------------
include ("GameLogic/Scripts/Debug.lua")
include ("GameLogic/Scripts/StatesManager.lua")
include ("GameLogic/Scripts/Common.lua")
include ("GameLogic/Scripts/Consts.lua")

SiegeSpawner_A_Name = "SiegeSpawnerA"
SiegeSpawner_B_Name = "SiegeSpawnerB"

function Init( reconnecting )
	if not reconnecting then
		SetGlobalVar( "dragonDead", false )
		SetGlobalVar( "barrierADead", false )
		SetGlobalVar( "barrierBDead", false )
		SetGlobalVar( "spawnDelay", 0 )
		LuaSetSpawnCreeps( false )
	end
end

function EggNotPickup ( TimeDamage, t, WaitHP )
	--LuaDebugTrace("EggNotPickup")
	if GetGlobalVar( "eggHaveTeam" ) == 0 then
		local step = GetGlobalVar( "localStep" )
		SetGlobalVar( "localStep", step + 1 )
		if step / 10 >= t then
			SetGlobalVar( "localStep", 0 )
			--LuaDebugTrace("TimeDone")
			local healthA, maxHealthA = LuaUnitGetHealth( "AltarA" )
			local healthB, maxHealthB = LuaUnitGetHealth( "AltarB" )
			if  healthA/maxHealthA > WaitHP/100 then
				DamageHealthA = healthA - TimeDamage
				LuaSetUnitHealth ( "AltarA", DamageHealthA)
				--LuaDebugTrace("AltarA have dmg")
			end
			if  healthB/maxHealthB > WaitHP/100 then
				DamageHealthB = healthB - TimeDamage
				LuaSetUnitHealth ( "AltarB", DamageHealthB)
				--LuaDebugTrace("AltarB have dmg")
			end
			if  healthB/maxHealthB <= WaitHP/100 and healthA/maxHealthA <= WaitHP/100 then
			--LuaDebugTrace("Выключили триггер")
			return true
			end
		end
	end
	return false
end

function Step( step )
	if not GetGlobalVar( "barrierADead" ) then
		if CreepsAreDead( "BarrierKeepersA", 2 ) then
			LuaGroupHide( "BarrierA", true )
			SetGlobalVar( "barrierADead", true )
		end
	end
	if not GetGlobalVar( "barrierBDead" ) then
		if CreepsAreDead( "BarrierKeepersB", 2 ) then
			LuaGroupHide( "BarrierB", true )
			SetGlobalVar( "barrierBDead", true )
		end
	end
	if not GetGlobalVar( "dragonDead" ) then
		local dead, found = LuaUnitIsDead("Dragon_w1_c1")
		if dead and found then
			LuaDebugTrace("Горыныч повержен! Step")
			LuaGroupHide ("Monsters", true)
			LuaSetSpawnNeutralCreeps(false)
			LuaSetHeroRespawnParams( "NewRespawnParams" )
			SetGlobalVar( "dragonDead", true )
			SetGlobalVar ( "eggHaveTeam", 0 )
			SetGlobalVar( "localStep", 0 )
			StartTrigger( EggNotPickup, 0.125 , 1, 25)
			for team = 0, 1 do
				for hero = 0, 4 do
					local currentHero = tostring(team) .. tostring(hero)
					local dead, found = LuaUnitIsDead( currentHero )
					if found then
						LuaSubscribeUnitEvent( currentHero, EventPickup, "GlyphPickup" )
						if dead then
							LuaHeroRespawn( currentHero )
						end
					end
				end
			end
		end
	end
end

function NeedRespawn( currentHero )
	local dead, found = LuaUnitIsDead( currentHero )
	if dead and found then
		local isRespawning = LuaHeroIsRespawning( currentHero )
		if not isRespawning then
			return true
		end
	end
	return false
end
 
function GlyphPickup( hero, glyph )
	if glyph == "CTE_Egg" then
		local faction = string.sub( hero, 1, 1 ) -- get hero's team via script name
		local spawnerName
		if faction == "0" then
			spawnerName = SiegeSpawner_A_Name
			local healthB, maxHealthB = LuaUnitGetHealth( "AltarB" )
			DamageHealthB = healthB - 15
			LuaSetUnitHealth ( "AltarB", DamageHealthB)
			--LuaDebugTrace("AltarB have dmg 2")
		else
			spawnerName = SiegeSpawner_B_Name
			local healthA, maxHealthA = LuaUnitGetHealth( "AltarA" )
			DamageHealthA = healthA - 15
			LuaSetUnitHealth ( "AltarA", DamageHealthA)
			--LuaDebugTrace("AltarA have dmg 2")
		end
		local siegeWave, count = LuaSpawnerSpawnWave( spawnerName )
		SetGlobalVar( "spawnDelay", 0 )
		StartTrigger( CreateEggAfterSiegeDeath, spawnerName, siegeWave )
		SetGlobalVar( "eggHaveTeam", 1 )
	end
end

function CreepsAreDead( spawnerName, count )
	for i = 1, count do
		local dead, found = LuaUnitIsDead( spawnerName .. "_w1_c" .. i )
		if not dead or not found then
			return false
		end
	end
	return true
end

function CreateEggAfterSiegeDeath( siegeName, siegeWave )
	local spawnDelay = GetGlobalVar( "spawnDelay" )
	if spawnDelay > 0 then
		spawnDelay = spawnDelay - 1
		SetGlobalVar( "spawnDelay", spawnDelay )
		if spawnDelay <= 0 then
			LuaUnitApplyApplicatorFromUnit ("MainBuildingA", "MainBuildingA", "CreateGlyph")
			SetGlobalVar( "eggHaveTeam", 0 )
			SetGlobalVar( "localStep", 0 )
--			StartTrigger( EggNotPickup, 1 , 1, 20)
			return true
		end	
	else
		local dead, found = LuaUnitIsDead( siegeName .. "_w" .. siegeWave .. "_c1"  )
		if dead and found then
			LuaDebugTrace("сидж умер")
			SetGlobalVar( "spawnDelay", 5 * 10 )
		end
	end
	return false
end