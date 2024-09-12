------------------------------------------------------------------------------------------------------
-- Misc utility functions
------------------------------------------------------------------------------------------------------

function DumpTable(p_table, maxDepth, curDepth)
  if nil ~= p_table or 'table' ~= type(p_table) then
    local depth = curDepth or 0
    for k, v in pairs(p_table) do
      clog(string.format("%s%s:%s", string.rep("    ", depth), tostring(k), tostring(v)))
      if 'table' == type(v) and depth < maxDepth then
        DumpTable(v, maxDepth, depth + 1)
      end
    end
  end
end

function PrintVector3(v3)
  return nil ~= v3 and string.format("{x = %f, y = %f, z = %f}", v3.x, v3.y, v3.z) or ""
end

function PrintColor3(c3)
  return nil ~= c3 and string.format("{r = %f, g = %f, g = %f}", c3.r, c3.g, c3.b) or ""
end

function PrintPointXY(pt)
  return nil ~= pt and string.format("{x = %f, y = %f}", pt.x, pt.y) or ""
end

function PrintPointUV(pt)
  return nil ~= pt and string.format("{u = %f, v = %f}", pt.u, pt.v) or ""
end

function PrintPointMM(pt)
  return nil ~= pt and string.format("{min = %f, max = %f}", pt.min, pt.max) or ""
end

function PrintRectXY(rect)
  return nil ~= rect and string.format("{x1 = %f, y1 = %f, x2 = %f, y2 = %f}", rect.x1, rect.y1, rect.x2, rect.y2) or ""
end

function PrintRectMM(rect)
  return nil ~= rect and string.format("{minx = %f, miny = %f, maxx = %f, maxy = %f}", rect.minx, rect.miny, rect.maxx, rect.maxy) or ""
end

function PrintRectLRTB(rect)
  return nil ~= rect and string.format("{left = %f, top = %f, right = %f, bottom = %f}", rect.left, rect.top, rect.right, rect.bottom) or ""
end
