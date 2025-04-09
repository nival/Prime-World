--------------------------------------------------------------------------------------------------------------------------------
TooltipsScreen = TooltipsScreen or
{
}

--------------------------------------------------------------------------------------------------------------------------------
function TooltipsScreen:OnInit()
  self.window = self:FindChild( "Simple" )
  self.initialWidth = self.window.sw
  self.targetRect = Rect()
  self.targetWindow = nil --Placeholder
end

--Called from C++
function TooltipsScreen:CppShowTooltip( text, mouseCoords, targetWindow, cursorSize, cursorHotSpot )
  local wnd = self.window;
  if not wnd then return end
  
  if self.targetRect ~= nil then --tip already shown
    return
  end
  
  self.targetWindow = targetWindow
  
  self.targetRect = Rect( targetWindow.sx, targetWindow.sy, targetWindow.sx + targetWindow.sw, targetWindow.sy + targetWindow.sh )

  --setup text
  wnd:RedirectNameMap( targetWindow )
  wnd:SetSize( self.initialWidth, -1, false )
  wnd:SetCaptionTextW( text )
  wnd:FixHeightToFitCaption( 0, 0 )
  wnd:FixWidthToFitCaption( 0, 1 )
  
  --first try place tooltip below cursor
  local tipY = mouseCoords.y + ( cursorSize.y - cursorHotSpot.y ) --tip y coord
  if tipY + wnd.h > self.h then --there is no room under cursor, try place it above
    tipY = self.targetRect.top - wnd.h --Replace "self.targetRect.top" by "mouseCoords.y" if yout want tooltip to appear above cursor, not above control
  end;
  
  --fix horizontal position, if needed
  local tipX = mouseCoords.x
  if tipX + wnd.w > self.w then
    tipX = self.w - wnd.w
  end

  --finally move and show tip window
  wnd:SetLocation( tipX, tipY )
  wnd:Show( true )
end

--Called from C++
function TooltipsScreen:CppHideTooltip()
  self.targetRect = nil
  self.targetWindow = nil
  if self.window then
    self.window:Show( false )
  end
end

--Called from C++
function TooltipsScreen:CppCheckTooltip()
  local target = self.targetWindow
  if self.targetRect then
    if ( not target ) or ( not target:IsVisible() ) then
      self:CppHideTooltip()
    end
  end
end


--------------------------------------------------------------------------------------------------------------------------------
function TooltipsScreen:OnMouseMove( mouseX, mouseY )
  if not self.targetRect then
    return false
  end

  if Common_PointInRect( mouseX, mouseY, self.targetRect ) then
    return false
  end

  self:CppHideTooltip();
  return false;
end

--------------------------------------------------------------------------------------------------------------------------------
function TooltipsScreen:OnMouseDown( mbutton, mouseX, mouseY )
  self:CppHideTooltip();
  return false;
end
