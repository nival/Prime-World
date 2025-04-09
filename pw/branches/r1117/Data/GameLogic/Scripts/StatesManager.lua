
-- TODO: add some simple OO technique for states containers

localStates = {
	stateStacksIndecies	= { "DefaultStack" },
	stateStacks			= { ["DefaultStack"] = {} },
	triggers			= {},
	triggersOn			= true,
}

rootobj = {
	states = {
		stateStacksIndecies	= { "DefaultStack" },
		stateStacks			= { ["DefaultStack"] = {} },
		triggers			= {},
		triggersOn			= true,
	},
	globalVars			= {},
	gameStep			= -1,
}

stepLength = 100
stepLengthInSeconds = 0.1

function GetStepLength()
	return stepLength
end

function GetStepLengthInSeconds()
	return stepLengthInSeconds
end

function GetStepsCountInSecond()
	return 1 / stepLengthInSeconds
end

function GetGameStep()
	return rootobj.gameStep
end


function SetGlobalVar( name, value )
	rootobj.globalVars[ name ] = value
end

function GetGlobalVar( name )
	return rootobj.globalVars[ name ]
end

function IncGlobalVar( name )
	local v = rootobj.globalVars[ name ] + 1
	rootobj.globalVars[ name ] = v 
	return v
end

function EnableTriggers()
	rootobj.states.triggersOn = true
end

function DisableTriggers()
	rootobj.states.triggersOn = false
end

function IsTriggersEnabled()
	return rootobj.states.triggersOn
end

function EnableLocalTriggers()
	localStates.triggersOn = true
end

function DisableLocalTriggers()
	localStates.triggersOn = false
end

function IsLocalTriggersEnabled()
	return localStates.triggersOn
end


function SleepState()
	coroutine.yield()
end

function CoroutineWraper( func, ... )
	coroutine.yield()	-- Exit to prevent first run on creation
	func( ... )			-- Call coroutine actual logic
end


function InsertState( indx, dest, top, func, ... )

    if type(func) ~= "function" then 
		local s = "InsertState: 'func' should be function ";
		if debug ~= undefined and debug.traceback ~= undefined then 
			s = s .. "\n" .. debug.traceback();
		end
		LuaAssert( s );
	end
	co = coroutine.create( CoroutineWraper )
	coroutine.resume( co, func, ... )
	
	if top then
		table.insert( dest, 1, co )
	else
		table.insert( dest, co )
	end
end


function RemoveTriggerImpl( trigger, dest )
	for i, state in pairs(dest.triggers) do
		if state == trigger then
			table.remove( dest.triggers, i )
		end
	end
end

function RemoveTrigger( trigger )
	RemoveTriggerImpl( trigger, rootobj.states )
end

function RemoveLocalTrigger( trigger )
	RemoveTriggerImpl( trigger, localStates )
end


function AddStateStackImpl( indx, dest )
	if dest.stateStacks[ indx ] == nil then
		table.insert( dest.stateStacksIndecies, indx )
		dest.stateStacks[ indx ] = {}
	end
end

function AddStateStack( indx )
	AddStateStackImpl( indx, rootobj.states )
end

function AddLocalStateStack( indx )
	AddStateStackImpl( indx, localStates )
end


function RemoveStateStackImpl( indx, dest )
	dest.stateStacks[ indx ] = nil
	for i, v in pairs( dest.stateStacksIndecies ) do
		if v == indx then
			table.remove( dest.stateStacksIndecies, i )
			break
		end
	end
end

function RemoveStateStack( indx )
	RemoveStateStackImpl( indx, rootobj.states )
end

function RemoveLocalStateStack( indx )
	RemoveStateStackImpl( indx, localStates )
end


function AddStateTop( func, ... )
	LuaDebugTrace( "AddStateTop:" .. ArgsToString(...) )
	InsertState( "DefaultStack", rootobj.states.stateStacks[ "DefaultStack" ], true, func, ... )
end

function AddLocalStateTop( func, ... )
	LuaDebugTrace( "AddLocalStateTop:" .. ArgsToString(...) )
	InsertState( "DefaultStack", localStates.stateStacks[ "DefaultStack" ], true, func, ... )
end

function AddStateEnd( func, ... )
	LuaDebugTrace( "AddStateEnd:" .. ArgsToString(...) )
	InsertState( "DefaultStack", rootobj.states.stateStacks[ "DefaultStack" ], false, func, ... )
end

function AddLocalStateEnd( func, ... )
	LuaDebugTrace( "AddLocalStateEnd:" .. ArgsToString(...) )
	InsertState( "DefaultStack", localStates.stateStacks[ "DefaultStack" ], false, func, ... )
end

function AddStateTop2( indx, func, ... )
	LuaDebugTrace( "AddStateTop:" .. ArgsToString(...) )
	AddStateStack( indx )
	InsertState( indx, rootobj.states.stateStacks[ indx ], true, func, ... )
end

function AddLocalStateTop2( indx, func, ... )
	LuaDebugTrace( "AddLocalStateTop:" .. ArgsToString(...) )
	AddLocalStateStack( indx )
	InsertState( indx, localStates.stateStacks[ indx ], true, func, ... )
end

function AddStateEnd2( indx, func, ... )
	LuaDebugTrace( "AddStateEnd:" .. ArgsToString(...) )
	AddStateStack( indx )
	InsertState( indx, rootobj.states.stateStacks[ indx ], false, func, ... )
end

function AddLocalStateEnd2( indx, func, ... )
	LuaDebugTrace( "AddLocalStateEnd:" .. ArgsToString(...) )
	AddLocalStateStack( indx )
	InsertState( indx, localStates.stateStacks[ indx ], false, func, ... )
end

function AddTriggerTop( func, ... )
	LuaDebugTrace( "AddTriggerTop:" .. ArgsToString(...) )
	InsertState( "triggers", rootobj.states.triggers, true, func, ... )
end

function AddLocalTriggerTop( func, ... )
	LuaDebugTrace( "AddLocalTriggerTop:" .. ArgsToString(...) )
	InsertState( "triggers", localStates.triggers, true, func, ... )
end

function AddTriggerEnd( func, ... )
	LuaDebugTrace( "AddTriggerEnd:" .. ArgsToString(...) )
	InsertState( "triggers", rootobj.states.triggers, false, func, ... )
end

function AddLocalTriggerEnd( func, ... )
	LuaDebugTrace( "AddLocalTriggerEnd:" .. ArgsToString(...) )
	InsertState( "triggers", localStates.triggers, false, func, ... )
end

function DumpStates()
	if debug == undefined or debug.traceback == undefined then return end

	function TryDumpState( co, pfx )
		if coroutine.status( co ) == "dead" then return end
		
		local s = pfx
		s = s .. debug.traceback( co, "", 2 )
		LuaDebugTrace( s )
	end
	
	do
		local states = rootobj.states
		LuaDebugTrace( "Global states:" )
		for i, indx in ipairs( states.stateStacksIndecies ) do
			stack = states.stateStacks[ indx ]
			if table.getn( stack ) > 0 then
				TryDumpState( stack[ 1 ], "Stack '"..tostring(indx).."':"  )
			end
		end
		LuaDebugTrace( "Global triggers:" )
		for i, trigger in pairs(states.triggers) do
			TryDumpState( trigger, "Trigger: " )
		end
	end
	do
		local states = localStates
		LuaDebugTrace( "Local states:" )
		for i, indx in ipairs( states.stateStacksIndecies ) do
			stack = states.stateStacks[ indx ]
			if table.getn( stack ) > 0 then
				TryDumpState( stack[ 1 ], "Stack "..tostring(i)..":"  )
			end
		end
		LuaDebugTrace( "Local triggers:" )
		for i, trigger in pairs(states.triggers) do
			TryDumpState( trigger, "Trigger: " )
		end
	end
end

function StepStatesStacks( states )
	-- TODO: make dropping of dead state after its last run
	for i, indx in ipairs( states.stateStacksIndecies ) do
		stack = states.stateStacks[ indx ]
		if table.getn( stack ) > 0 then
			co = stack[ 1 ]
			if coroutine.status( co ) ~= "dead" then
				local success,msg = coroutine.resume( co )
				if not success then
					LuaAssert( "State (stack "..indx..") error: "..msg )
				end
			else
				--LuaDebugTrace( "Remove top state from stack " .. tostring(i) )
				table.remove( stack, 1 )
				if table.getn( stack ) == 0 then
					LuaDebugTrace( "States are finished for stack " .. tostring(i) )
				end
			end
		end
	end
end

function StepTriggers( states )
	if states.triggersOn and table.getn( states.triggers ) > 0 then
		for i, trigger in pairs(states.triggers) do
			--LuaDebugTrace( "Step trigger " .. tostring(i) )
			if coroutine.status( trigger ) ~= "dead" then
				local success,msg = coroutine.resume( trigger )
				if not success then
					LuaAssert( "Trigger error: "..msg )
				end
			else
				--LuaDebugTrace( "Remove trigger " .. tostring(i) )
				table.remove( states.triggers, i )
				if table.getn( states.triggers ) == 0 then
					LuaDebugTrace( "Triggers are finished" )
				end
			end
		end
	end
end

function InitStates( isReconnecting, _stepLength, _stepLengthInSeconds )
	stepLength = _stepLength
	stepLengthInSeconds = _stepLengthInSeconds
end

function StepStates( step )
	--LuaDebugTrace( "Lua step: " .. step )
	rootobj.gameStep = step
	StepStatesStacks( localStates )
	StepTriggers( localStates )
	StepStatesStacks( rootobj.states )
	StepTriggers( rootobj.states )
end
