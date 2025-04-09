include( "GameLogic/Scripts/Debug.lua" )
include( "GameLogic/Scripts/StatesManager.lua" )

LuaDebugTrace( "Test.lua launched!" )

-- serializable variables
eggTimer = 0
eggIsDropped = false
someVar = 1000
empty = nil
-- end of serializables
-- Don not modify __serializables at run-time
__serializables = { "eggTimer", "eggIsDropped", "someVar", "empty" }

function HeroHealthWarn( hero, warnPercent, singular )
	while true do
		local health, maxHealth = LuaHeroGetHealth( hero )
		--LuaDebugTrace( "Test health: " .. health .. " (" .. maxHealth .. ")" )
		if ( health / maxHealth <=  warnPercent / 100 ) then
			LuaMessageToChat( "Watch your health!" )
			if singular then
				return
			end
		end
		SleepState()
	end
end

function HeroManaWarn( hero, warnPercent, singular )
	local warningTriggered = false
	while true do
		local mana, maxMana = LuaHeroGetMana( hero )
		--LuaDebugTrace( "Test mana: " .. mana .. " (" .. maxMana .. ")" )
		if mana / maxMana <=  warnPercent / 100 then
			if not warningTriggered then
				LuaMessageToChat( "Watch your mana!" )
				warningTriggered = true
				if singular then
					return
				end
			end
		else
			warningTriggered = false
		end
		SleepState()
	end
end

function HeroPositionValidate( hero, x, y, accuracy )
	LuaMessageToChat( "Next checkpoint at " .. x .. "," .. y )
	local steps = 0
	while true do
		steps = steps + 1
		local hx, hy = LuaHeroGetPosition( hero )
		--LuaDebugTrace( "Test positions: " .. x .. ":" .. y .. " vs " .. hx .. ":" .. hy )
		if ( math.abs( x - hx ) <= accuracy and math.abs( y - hy) <= accuracy ) then
			LuaDebugTrace( "Point reached! Hero position: " .. hx .. ":" .. hy )
			LuaMessageToChat( "Checkpoint!" )
			return
		end
		if ( steps / 10 ) % 10 == 0 then
			LuaMessageToChat( "Hey! Go to " .. x .. "," .. y )
		end
		SleepState()
	end
end

function Test1(arg1, arg2, arg3, arg4, arg5)
	--LuaCreatureHide( "doct_mg", false )
	--LuaCreatureHide( "local", false )
	--LuaGroupHide( "mission2only", true )
	--LuaGroupHide( "test1", true )
	--LuaCreatureHide( "11", true )
	--LuaSpawnerSpawnWave( "doctsp" )
	--LuaCreatureHide( "01", true )
	--LuaCreatureTeleportTo( "01", 200, 130 )
	--LuaCameraMoveToPos( 200, 130 )
	--LuaCameraLock(true)
	--LuaGameFinish( Freeze )
	--LuaSetAchievmentsEnabled( false )
	--LuaSetVisMapMode(tonumber(arg1))
	--dead, found = LuaUnitIsDead(arg1)
	--LuaDebugTrace( "dead=" .. tostring(dead) .. " found=" .. tostring(found) )
	--LuaHeroUseConsumable(arg1, arg2) -- e.g. call_lua_function Test1 local Items\Consumables\SpeedPotion.ARCT.xdb
	--LuaHeroTakeConsumable(arg1, arg2) -- e.g. call_lua_function Test1 local Items\Consumables\SpeedPotion.ARCT.xdb
	--LuaHeroApplyApplicator(arg1, arg2) -- e.g. call_lua_function Test1 local /GameLogic/GeneralApplicators/ArrowRed.APLR
	--LuaUnitApplyApplicator(arg1, arg2) -- e.g. call_lua_function Test1 local /GameLogic/GeneralApplicators/ArrowRed.APLR
	--LuaUnitClearStates(arg1)
	--LuaHeroActivateTalent( "local", tonumber(arg1), tonumber(arg2), true )
	--LuaHeroActivateTalent( "local", tonumber(arg1), tonumber(arg2), false )
	--LuaUnitApplyApplicatorFromUnit(arg1, arg2, arg3) -- e.g. call_lua_function Test1 local 10 /GameLogic/GeneralApplicators/ArrowRed.APLR
	--LuaDirectionHintSet( "Effects/UI/Arrow/DirectionHint.MTRL", tonumber(arg1), tonumber(arg2) )
	--LuaDirectionHintSet2( "Effects/UI/Arrow/DirectionHint.MTRL", tonumber(arg1), tonumber(arg2), tonumber(arg3), tonumber(arg4) )
	--[[
	isGender = LuaHeroIsGenderTalent( "local", tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "isGender = " .. tostring(isGender) )
	]]--
	--LuaHeroSetForbidRespawn( arg1, true )
	--[[
	local faction = LuaFlagGetFaction( tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "faction = " .. tostring(faction) )
	--]]--
	--LuaHeroUseTalent( arg1, tonumber(arg2), tonumber(arg3) )
	--LuaSetGlobalStatScale2( StatLife, 0.5, UnitTypeCreep, Burn )
	--[[
	isShopOpen = LuaIsShopOpen()
	LuaDebugTrace( "isShopOpen=" .. tostring(isShopOpen) )
	]]--
	--LuaHeroUseTalentPos( arg1, tonumber(arg2), tonumber(arg3), tonumber(arg4), tonumber(arg5) ) -- e.g. for ratchatcher: call_lua_function Test1 local 0 0 20 40 
	--[[
	heroLevel = LuaHeroGetLevel( arg1 )
	LuaDebugTrace( "Hero level = " .. tostring(heroLevel) )
	]]--
	--[[
	file = io.open("output.lua", "w")
	file:write("Hello world!")
	file:close()
	]]--
end

function Test2(arg1, arg2, arg3, arg4, arg5)
	--LuaCreatureHide( "doct_mg", false )
	--LuaCreatureHide( "local", false )
	--LuaGroupHide( "mission2only", false )
	--LuaGroupHide( "test1", false )
	--LuaCreatureHide( "11", false )
	--LuaCreatureHide( "01", false )
	--LuaCameraMoveToUnit( "dtower1" )
	--LuaCameraMoveToPosTimed2( 100, 100, 200, 100, tonumber(arg1) )
	--LuaCameraMoveToPosTimed( 100, 100, tonumber(arg1) )
	--LuaSetAchievmentsEnabled( true )
	--LuaHeroUseConsumablePos(arg1, arg2, tonumber(arg3), tonumber(arg4) ) -- e.g. call_lua_function Test2 local Items\Consumables\EyeOfSeeing.ARCT.xdb 120 120
	--[[
	hasConsumable = LuaHeroHasConsumable(arg1, arg2) -- e.g. call_lua_function Test1 local Items\Consumables\SpeedPotion.ARCT.xdb
	if hasConsumable then
		LuaDebugTrace( "Hero " .. arg1 .. " has consumable " .. arg2 )
	else
		LuaDebugTrace( "Hero " .. arg1 .. " hasn't consumable " .. arg2 )
	end
	]]--
	--LuaHeroAttackUnit(arg1, arg2)
	--LuaUnitRemoveApplicator(arg1, arg2) -- e.g. call_lua_function Test2 local /GameLogic/GeneralApplicators/ArrowRed.APLR
	--[[
	canActivate = LuaHeroCanActivateTalent( "local", tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "Can activate " .. arg1 .. " " .. arg2 .. " = " .. tostring(canActivate) )
	]]--
	--[[
	isActivated = LuaHeroIsTalentActivated( "local", tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "Is activated " .. arg1 .. " " .. arg2 .. " = " .. tostring(isActivated) )
	]]--
	--LuaUnitApplyApplicatorFromUnit(1, 2, 3)
	--LuaDirectionHintShow( tonumber(arg1), tonumber(arg2) )
	--[[
	talentType = LuaHeroGetTalentType( "local", tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "talentType = " .. tostring(talentType) )
	]]--
	--LuaHeroSetForbidRespawn( arg1, false )
	--[[
	local isRising = LuaFlagIsRising( tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "isRising = " .. tostring(isRising) )
	]]--
	--LuaHeroActivateTalent( arg1, tonumber(arg2), tonumber(arg3), true )
	--LuaSetGlobalStatScale2( StatEnergy, 2, UnitTypeHeroMale, Freeze )
	--[[
	consumablesCount = LuaHeroGetConsumablesCount( arg1 )
	LuaDebugTrace( "consumablesCount=" .. tostring(consumablesCount) )
	]]--
	--LuaHeroUseTalentUnit( arg1, tonumber(arg2), tonumber(arg3), arg4 ) -- e.g. for ratchatcher: call_lua_function Test2 local 0 1 10
	--[[
	local hx, hy = LuaHeroGetPosition( arg1 )
	LuaDebugTrace( arg1 .. " pos: " .. tostring(hx) .. ":" .. tostring(hy) )
	]]--
end

function Test3(arg1, arg2, arg3, arg4, arg5)
	--LuaGroupMoveTo(arg1, 40, 150, 20)
	--LuaCameraObserveUnit( "" ) --drop observed unit
	--LuaCameraObserveUnit( arg1 )
	--LuaCameraLock(false)
	--LuaHeroUseConsumableUnit(arg1, arg2, arg3) -- e.g. call_lua_function Test3 local Items\Consumables\Stunner.ARCT.xdb 10
	--LuaHeroFollowCreature(arg1, arg2) -- e.g. call_lua_function Test3 01 local
	--LuaUnitApplyApplicator(arg1, arg2) -- e.g. call_lua_function Test1 doct_tower1 /GameLogic/GeneralApplicators/ArrowRed.APLR
	--[[
	talentsLevel = LuaHeroGetTalentsLevel( "local" )
	LuaDebugTrace( "Talents level = " .. tostring(talentsLevel) )
	]]--
	--[[
	lastTalentUseStep = LuaHeroGetLastTalentUseStep( "local" )
	LuaDebugTrace( "Last talent use step = " .. tostring(lastTalentUseStep) .. ", current world step = " .. GetGameStep() )
	]]--
	--LuaDirectionHintHide()
	--[[
	useStep = LuaHeroGetTalentUseStep( "local", tonumber(arg1), tonumber(arg2) )
	LuaDebugTrace( "useStep = " .. tostring(useStep) )
	]]--
	--LuaHeroRespawn( arg1 )
	--LuaSetGlobalStatScale( 0, 10, Invalid )
	--LuaSetGlobalStatScale( StatLife, 10, UnitTypeInvalid )
	--[[
	local health, maxHealth = LuaUnitGetHealth( arg1 )
	LuaDebugTrace( arg1 .. " health: " .. tostring(health) .. " from " .. tostring(maxHealth) )
	]]--
end

function Test4(arg1, arg2, arg3, arg4, arg5)
	--[[
	if arg1 == "1" then
		LuaSetPause( true )
	else
		LuaSetPause( false )
	end
	--]]--
end

function Init()

	--AddStateTop( HeroPositionValidate, "local", 40, 60, 5 )
	--AddStateEnd( HeroPositionValidate, "local", 40, 40, 5 )
	
	--AddTriggerTop(HeroHealthWarn, "local", 20, true)
	--AddTriggerTop(HeroManaWarn, "local", 20, false)
	
	--LuaSetHeroInvulnerable( "local" )
	--LuaHeroApplyApplicator( "local", "/GameLogic/GeneralApplicators/Immune2Death.APLR" )
	--LuaHeroAddFlag( "local", ForbidDeath )
	--LuaTest("local")
	
	--LuaHeroActivateTalent( "local", 0, 0 )
	
	--[[
	creepOk = LuaCreateCreep( "creep1", "/Creeps/B/Range/_.CREEP", 40, 60, Neutral )
	if creepOk then
		LuaDebugTrace( "Creep ok!" )
		--LuaCreatureMoveTo( "creep1", 60, 60, 0 )
	end
	--]]--
	--LuaCreatureHide( "doct_mg", true )
	--LuaCreatureHide( "local", true )
	
	--LuaHeroAttackUnit( "local", "creep1" )
	
	--LuaSetSpawnCreeps(false)
	
	--LuaDebugTrace( "TestEnum:" .. tostring(Neutral) .. ", " .. tostring(Freeze) .. ", " .. tostring(Burn) )
	
	--LuaSetManualGameFinish( true )
	
end

function Step( step )

end