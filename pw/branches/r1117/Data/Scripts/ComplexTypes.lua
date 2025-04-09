------------------------------------------------------------------------------------------------------
-- Complext types transfers helpers
------------------------------------------------------------------------------------------------------

Math = Math or {}

Math['CVector3'] = 
{
  __mt = 
  {
    __index    = 
      function(object, key) 
        if 'r' == key then 
          return rawget(object, 'x') 
        end
        if 'g' == key then 
          return rawget(object, 'y') 
        end
        if 'b' == key then 
          return rawget(object, 'z') 
        end
        
        return rawget(object, key)
      end,
    
    __newindex = 
      function(object, key, value) 
        if 'r' == key or 'x' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'x', value) 
          return
        end
        if 'g' == key or 'y' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'y', value)
          return
        end
        if 'b' == key or 'z' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'z', value) 
          return
        end
      end,
  },
  constructor = 
  function( xValue, yValue, zValue ) 
    local result = { x = xValue or 0, y = yValue or 0, z = zValue or 0}
    setmetatable(result, Math['CVector3'].__mt) 
    return result 
  end
}

Math['CPoint'] =
{ 
  __mt = 
  {
    __index    = 
      function(object, key) 
        if 'u' == key or 'min' == key then 
          return rawget(object, 'x') 
        end
        if 'v' == key or 'max' == key then 
          return rawget(object, 'y') 
        end
             
        return rawget(object, key)
      end,
    
    __newindex = 
      function(object, key, value) 
        if 'u' == key or 'min' == key or 'x' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'x', value) 
          return
        end
        if 'v' == key or 'max' == key or 'y' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'y', value)
          return
        end
      end,
  },
  constructor = 
  function(xValue, yValue) 
    local result = { x = xValue or 0, y = yValue or 0 }
    setmetatable(result, Math['CPoint'].__mt) 
    return result 
  end
}

Math['CRect'] = 
{
  __mt = 
  {
    __index    = 
      function(object, key) 
        if 'left'   == key or 'minx' == key then 
          return rawget(object, 'x1') 
        end
        if 'top'    == key or 'miny' == key then 
          return rawget(object, 'y1') 
        end
        if 'right'  == key or 'maxx' == key then 
          return rawget(object, 'x2') 
        end
        if 'bottom' == key or 'maxy' == key then 
          return rawget(object, 'y2') 
        end
             
        return rawget(object, key)
      end,
    
    __newindex = 
      function(object, key, value) 
        if 'left'   == key or 'minx' == key or 'x1' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'x1', value) 
          return
        end
        if 'top'    == key or 'miny' == key or 'y1' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'y1', value) 
          return
        end
        if 'right'  == key or 'maxx' == key or 'x2' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'x2', value) 
          return
        end
        if 'bottom' == key or 'maxy' == key or 'y2' == key then 
          -- insert here any checks if neccessary
          rawset(object, 'y2', value)
          return
        end  
      end,
  },
    constructor = 
    function( x1Value, y1Value, x2Value, y2Value ) 
      local result = { x1 = x1Value or 0, y1 = y1Value or 0, x2 = x2Value or 0, y2 = y2Value or 0 }
      setmetatable(result, Math['CRect'].__mt) 
      return result 
    end
}

Vector3 = Math['CVector3'].constructor
Color3  = Math['CVector3'].constructor
Point   = Math['CPoint'].constructor
Rect    = Math['CRect'].constructor
