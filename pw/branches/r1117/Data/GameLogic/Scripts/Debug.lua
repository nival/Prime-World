
function PrintToChatAndTrace( message )
	LuaDebugTrace( message )
	LuaMessageToChat( message )
end

function ArgsToString(...)
	argsstr = ""
	for i = 1, select("#",...) do
		argsstr = argsstr .. " " .. tostring(select(i,...))
	end
	return argsstr
end

function DebugTraceGlobals()
	for n,v in pairs(_G) do
		LuaDebugTrace( "_G: " .. tostring(n) .. ", " .. tostring(v) )
	end
end

