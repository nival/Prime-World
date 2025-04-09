------------------------------------------------------------------------------------------------------
-- Test.lua 
-- used for CxxTest
-- DO NOT MODIFY!
------------------------------------------------------------------------------------------------------
TestLuaClass = TestLuaClass or {}

function TestLuaClass:EnumerateMetatable()
  
  clog("Enumerating class metatble:")
  clog("  class  :" .. self._class)
  clog("  native :" .. self._native)
  clog("  methods:")
   
  DumpTable(getmetatable(self), 3)
end

function TestLuaClass:Function0()
  clog("TestLuaClass:Function0() called!")
end

function TestLuaClass:Function1(arg1)
  clog("TestLuaClass:Function1() called with argument:")
  clog("  arg1")
  clog("  type :" .. type(arg1))
  clog("  value:" .. tostring(arg1))
end

function TestLuaClass:Function2(arg1, arg2)
  clog("TestLuaClass:Function2() called with arguments:")
  clog("  arg1")
  clog("  type :" .. type(arg1))
  clog("  value:" .. tostring(arg1))
  clog("  arg2")
  clog("  type :" .. type(arg2))
  clog("  value:" .. tostring(arg2))
end

function TestLuaClass:CallAnotherFunction(name)
  clog("TestLuaClass:CallAnotherFunction() called:")
  if nil == name then
    clog("TestLuaClass:CallAnotherFunction(): missing required argument!")
    return
  end
    
  if 'string' ~= type(name) then
    clog("TestLuaClass:CallAnotherFunction(): invalid argument!")
    return
  end
  
  local p_method = self[name]
  if nil == p_method then 
    clog("TestLuaClass:CallAnotherFunction(): method <" .. name .. "> not found!")
  else
    clog("-----")
    p_method(self)
    clog("-----")
  end
end

function TestLuaClass:SquareArgument(arg1)
  clog("TestLuaClass:SquareArgument() called:")
  
  if nil == arg1 then
    clog("Missing argument!")
    return 0
  end
  
  local value = tonumber(arg1)
  if nil == value then
    clog("Missing argument!")
    return 0
  end
  
  value = value * value
  clog("result = " .. tostring(value))
  
  return value
end

function TestLuaClass:TestProperties()
  local value = 0
  clog("testing properties ...")
  
  value = self.value
  clog("initial value:" .. tostring(value))
  
  self.value = 10
  value = self.value
  clog("changed value:" .. tostring(value))
end

function TestLuaClass:TestObjectTransfer()
  local pLinked = self:GetLinked()
  if nil ~= pLinked then
    clog("Linked value:" .. pLinked.value)
    pLinked:SetLinked(self)
  end
end

LuaImplementedClass = LuaImplementedClass or {}

function LuaImplementedClass:LuaImplementedMethod()
  clog("LuaImplementedClass:LuaImplementedMethod()")
  return self:GetValue()
end

function LuaImplementedClass:LuaImplementedMethod1(arg)
  clog(string.format("LuaImplementedClass:LuaImplementedMethod1(%s)", tostring(arg)))
  return tostring(arg)
end

function LuaImplementedClass:LuaImplementedMethod2(arg1, arg2)
  clog(string.format("LuaImplementedClass:LuaImplementedMethod2(%s, %s)", tostring(arg1), tostring(arg2)))
  if 'number' == type(arg1) and 'number' == type(arg2) then
    return arg1 * arg2
  end
  
  return 0
end

LuaComplexTypesTestClass = LuaComplexTypesTestClass or {}

function LuaComplexTypesTestClass:TestVector3(arg1, arg2)
  clog("Vector transfer test")
  clog(PrintVector3(arg1))
  clog(PrintColor3(arg2))
  
  local result = Vector3(arg1.x + arg2.r, arg1.y + arg2.g, arg1.z + arg2.b)  
  clog("result: " .. PrintVector3(result))
  
  self:CheckVectorValue(result)
end

function LuaComplexTypesTestClass:TestPoint(arg1, arg2)
  clog("Point transfer test")
  clog(PrintPointUV(arg1))
  clog(PrintPointMM(arg2))
    
  local result = Point(arg1.u * arg2.min, arg1.v * arg2.max) 
  clog(PrintPointXY(result))
  self:CheckPointValue(result)
end

function LuaComplexTypesTestClass:TestRect(arg1, arg2)
  clog("Rect transfer test")
  clog(PrintRectLRTB(arg1))
  clog(PrintRectMM(arg2))
    
  local result = Rect(arg1.x1 < arg2.minx   and arg1.x1     or arg2.minx, 
                      arg1.y1 < arg2.miny   and arg1.y1     or arg2.miny, 
                      arg1.x2 < arg2.right  and arg2.right  or arg1.x2, 
                      arg1.y2 < arg2.bottom and arg2.bottom or arg1.y2) 
  clog(PrintRectXY(result))
  self:CheckRectValue(result)
end