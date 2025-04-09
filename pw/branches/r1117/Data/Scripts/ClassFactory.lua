------------------------------------------------------------------------------------------------------
-- ClassFactory.lua 
-- used for creation of lua subclass instances
-- DO NOT MODIFY!
------------------------------------------------------------------------------------------------------

function PropertyManipulator(object, key, value)
  local p_mt         = getmetatable(object) 
  local p_properties = rawget(p_mt, '__props')
  
  if nil ~= p_properties then
    local p_property = rawget(p_properties, key)
    if nil ~= p_property and nil ~= p_property.set then
      p_property.set(object, value)
      return
    end
  end
      
  rawset(object, key, value)
end

function ProxyIndex(object, key)
  local p_mt         = getmetatable(object) 
  
  -- handle methods
  local p_methods    = rawget(p_mt, '__methods')
  if nil ~= p_methods then
    local p_method   = rawget(p_methods, key)
    if nil ~= p_method then
      return p_method
    end
  end
    
  -- handle mapped properties
  local p_properties = rawget(p_mt, '__props')
  if nil ~= p_properties then
    local p_property = rawget(p_properties, key)
    if nil ~= p_property and nil ~= p_property.get then
      return  p_property.get(object)
    end
  end
  
  -- handle predefined properties
  if '_class' == key or '_native' == key then
    return rawget(p_mt, key)
  end
      
  -- handle simple properties
  return rawget(object, key)
end

Sys = Sys or { }

function Sys:ClassFactory(s_nativeClass, s_luaClass, p_methodsTable)    

  if nil == _G[s_luaClass]  then
    clog(string.format("Script class <%s> not found!", s_luaClass))
    return nil
  end
    
  self.t_classInfo             = self.t_classInfo or {}
  self.t_classInfo[s_luaClass] = self.t_classInfo[s_luaClass] or {} 
  if nil == self.t_classInfo[s_luaClass].p_mt then  
    local p_info = self.t_classInfo[s_luaClass] 
    p_info.p_mt  = 
    {
      _native    = s_nativeClass,
      _class     = s_luaClass,
      
      __methods  = {}, 
      __props    = {},
      
      __gc       = p_methodsTable.__gc
    }
    
    -- attach native methods
    for name, method in pairs(p_methodsTable.__methods) do
      p_info.p_mt.__methods[name] = method
    end
        
    -- attach script methods 
    local p_self = _G[s_luaClass]   
    for name, method in pairs(p_self) do
      if 'function' == type(method) then
        p_info.p_mt.__methods[name] = method
      end
    end
    
    -- attach properties
    for name, handlers in pairs(p_methodsTable.__props) do
      p_info.p_mt.__props[name] = { set = handlers.set, get = handlers.get }
    end
    
    p_info.p_mt.__index    = ProxyIndex
    p_info.p_mt.__newindex = PropertyManipulator
  end
  
  local p_result = {} 
  setmetatable(p_result, self.t_classInfo[s_luaClass].p_mt)
  return p_result
end

