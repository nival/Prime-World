-------------------------------------------------------------------------------------------------------------------------------
ActionBarDnDLayer = ActionBarDnDLayer or
{
  DRAG_THRESHOLD = 3
}


-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:OnInit()
  --NOTE: parent must set "dndSlotType" to apporiate values!
  self.slotIndex = GetIndexFromString( self.parent.name )
end


-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:OnMouseDown( action, x, y )
  if action == WINDOW_RMBUTTON then
    self.mouseOn = true
    self.dragStartX = x
    self.dragStartY = y
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:OnMouseUp( action )
  if self.mouseOn then
    self:ABStartDrag( self.dragStartX, self.dragStartY, false )
  end
  self:Reset()
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:OnMouseMove( x, y )
  if self.mouseOn then
    local thresh = ActionBarDnDLayer.DRAG_THRESHOLD
    if ( math.abs( self.dragStartX - x ) > thresh ) or ( math.abs( self.dragStartY - y ) > thresh ) then
      self:ABStartDrag( self.dragStartX, self.dragStartY, true )
      self:Reset()
    end
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:OnMouseOver( over )
  if not over then
    self:Reset()
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:OnDropTest( id, dragTarget )
  if id == "action_bar_dnd" then
    return true
  end
  return false
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:Reset()
  self.mouseOn = false
  self.dragStartX = 0
  self.dragStartY = 0
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarDnDLayer:ABStartDrag( x, y, classicMode )
  clog( "ABStartDrag: " .. tostring( self.parent.dndSlotType ) .. "#" .. tostring( self.slotIndex ) )

  if self.parent.dndSlotType then
    if not self.context:IsDnDSlotUsed( self.parent.dndSlotType, self.slotIndex ) then
      return
    end
  end

  local doll = self:CreateChild( "DragNDropDoll", "dragndrop_doll", 0, 0, 0, 0, 0, 0 )
  if doll then
    doll.classicMode = classicMode
    doll.dndSlotType = self.parent.dndSlotType
    doll.slotIndex = self.slotIndex
    doll:SetupImage()
    
    --Sizes of DnDLayer and DnDDoll may differ, so we should scale drag point
    local scaledX = x / self.w * doll.w
    local scaledY = y / self.h * doll.h
    self.context:StartDrag( doll, "action_bar_dnd", scaledX, scaledY )
  end
end
