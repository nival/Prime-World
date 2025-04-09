--[[  
--Interface: 
function CreateFlagChain( chainName, flags, polygonArea, polygonNames, faction, callback )
  callback - function( isRaised, chainName, flagName, polygonName )

function SetRaisedFlagsInChain( name, raisedCount, who )

function RaiseAllFlags( who )
  
uses global var isMissonFinished
]]

function CreateFlagChain( name, flags, polygonArea, polygonNames, faction, callback )
	if #flags ~= #polygonNames then
		LuaAssert("CreateFlagChain: flags count must match polygons count!")
		return
	end
	AddTriggerEnd( ControlFlagChain, name, flags, polygonArea, polygonNames, faction, callback );
end

function SetRaisedFlagsInChain( name, raisedCount, who )
	LuaSetRaisedFlagpolesInChain( name, raisedCount, who )
end

function RaiseAllFlags( who )
	SetGlobalVar( "__ScriptFlags_RaiseAll_Step", GetGameStep() + 1 )
	SetGlobalVar( "__ScriptFlags_RaiseAll_Who", who )
	LuaDebugTrace("All flags raise signal sent" )
	
	function Reset()
		while GetGlobalVar( "__ScriptFlags_RaiseAll_Step" ) >= GetGameStep() do SleepState() end
		SetGlobalVar( "__ScriptFlags_RaiseAll_Step", nil )
		SetGlobalVar( "__ScriptFlags_RaiseAll_Who", nil )
		LuaDebugTrace("All flags raise signal reset" )
	end
	AddTriggerEnd( Reset )
end

function ControlFlagChain( name, flags, polygonArea, polygonNames, faction, callback )
	local raised = 0
	local prevRaised = raised
	
	LuaCreateFlagpoleChain( name, flags )
	
	while not GetGlobalVar("isMissonFinished") do 
		if GetGlobalVar( "__ScriptFlags_RaiseAll_Step" ) == GetGameStep() then
			LuaDebugTrace("All flags raise signal to chain "..name )
			LuaSetRaisedFlagpolesInChain( name, #flags,  GetGlobalVar( "__ScriptFlags_RaiseAll_Who" ) )
		end
		
		raised = LuaGetRaisedFlagpolesInChain( name )
		local i;
		if raised > prevRaised then
			for i = prevRaised + 1, raised do 
				LuaDebugTrace("Flag raised in chain "..name.." : "..tostring(i) )
				LuaChangeNatureMapPolyArea( polygonArea, polygonNames[i], 0, faction )
				if callback then
					callback( true, name, flags[i], polygonNames[i] )
				end
			end
		elseif raised < prevRaised then
			for i = prevRaised, raised + 1, -1 do 
				LuaDebugTrace("Flag dropped in chain "..name.." : "..tostring(i) )
				LuaChangeNatureMapPolyArea( polygonArea, polygonNames[i], faction, 0 )
				if callback then
					callback( false, name, flags[i], polygonNames[i] )
				end
			end
		end
		prevRaised = raised
		SleepState()
	end

end

