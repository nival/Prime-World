-- UISpecific.lua

-------------------------------------------------------------------------------------------------------------------------------
-- Placing
--
function Common_PlaceSmart( obj, scrx,scry,border, rect, sx,sy, A,B )
	local ry = rect.y2 - rect.y1
	if ry < 0 then ry = 0 end
	local ky = ry / scry
	if ky > 1 then ky = 1 end

	local dy = ry * (A - B * ky) / 2
	local my = (rect.y1 + rect.y2) / 2
	local ty = my - sy - dy
	if ty < border then ty = my + dy end

	local ymax = scry - sy - border
	ty = Common_Clamp( ty, border, ymax )

	local tx = (rect.x1 + rect.x2 - sx) / 2

	local xmax = scrx - sx - border
	tx = Common_Clamp( tx, border, xmax )

	obj:SetLocation( tx,ty, 0,BLEND_NONE )
	obj:Show( true )
end

-------------------------------------------------------------------------------------------------------------------------------
function Common_RectOut( rect, scrx,scry )
	if rect.x1 < 0 and rect.x2 < 0 then return true end
	if rect.y1 < 0 and rect.y2 < 0 then return true end
	if rect.x1 > scrx and rect.x2 > scrx then return true end
	if rect.y1 > scry and rect.y2 > scry then return true end
	return false
end

-------------------------------------------------------------------------------------------------------------------------------
function Common_ClipRect( rect, scrx,scry )
	if rect.x1 < 0 then rect.x1 = 0 end
	if rect.y1 < 0 then rect.y1 = 0 end
	if rect.x2 > scrx then rect.x2 = scrx end
	if rect.y2 > scry then rect.y2 = scry end
end

-------------------------------------------------------------------------------------------------------------------------------
function Common_PointInRect( x, y, rect )
	if x < rect.left then return false end
  if x > rect.right then return false end
  if y < rect.top then return false end
  if y > rect.bottom then return false end
  return true
end

-------------------------------------------------------------------------------------------------------------------------------
function SubclassStateOnAction( subclassName, targetWindow, stateName )
  _G[subclassName] = _G[subclassName] or {}
  _G[subclassName].OnAction = function( wnd, mbutt )
    local wnd = wnd:GetBaseParent():FindChild( targetWindow );
    if wnd then
      wnd:SetState( stateName );
    end
  end
end;
