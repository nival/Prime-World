------------------------------------------------------------------------
ActionBar = ActionBar or 
{
  Inited       = false,
  BaseWindow   = nil,
}

-------------------------------------------------------------------------------------------------------------------------------
function ActionBar:OnInit(parent)
  self.BaseWindow = parent:GetChild("ActionBar")
  if nil == self.BaseWindow then
     clog("ActionBar window not found")
    return
  end

  local TalentButton = self.BaseWindow:GetChild("ChestButton")
  if nil ~= TalentButton then
    TalentButton.OnAction = function(pWnd, action) self:OnChestButtonAction(pWnd, action) end
  else
     clog("ChestButton not found in ActionBar")
  end

  Talents:OnInit(parent);
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBar:OnChestButtonAction(pWnd, action)
  if action ~= WINDOW_ACTION_MAIN then
    return
  end
  
  if Talents:IsVisible() then
    Talents.context:ShowTalentPanel( false )
  else
    Talents.context:ShowTalentPanel( true )
  end
end



-------------------------------------------------------------------------------------------------------------------------------
ActionBarAbility = ActionBarAbility or {}

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarAbility:OnInit()
  local pControl = self:GetChild("ImproveAbility")
  if pControl then
    pControl.OnMouseOver = function( pWnd, hover ) self:OnHover(pWnd.name, hover) end
    pControl.OnAction = function( pWnd, action ) self:OnImproveSpellClick( action )  end
  end

  pControl = self:GetChild("Button") 
  if nil ~= pControl then
    pControl.OnMouseOver = function( pWnd, hover ) self:OnHover( pWnd.name, hover ) end
    pControl.OnAction  = function( pWnd, action ) self:OnSpellClick( action )  end
    pControl.OnDoubleClick = function( pWnd, action)
      if( WINDOW_ACTION_MAIN == action ) then
        --self.context:SendEventAbilitiesAutoTarget( GetIndexFromString( self.name ) )
      end
    end
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarAbility:OnHover( itemName, hover )  
  --self.context:ShowSpellDesc( GetIndexFromString( self.name ), ( string.find(itemName, "ImproveAbility") ~= nil ), hover )
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarAbility:OnImproveSpellClick( action )
  --self.context:PressImproveSpellButton( GetIndexFromString( self.name ), action )
end

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarAbility:OnSpellClick( action )
  --self.context:PressSpellButton(GetIndexFromString(self.name), action)
end







-------------------------------------------------------------------------------------------------------------------------------
ActionBarItem = ActionBarItem or {}

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarItem:OnInit()
  self.dndSlotType = DND_ORG_CONSUMABLES_BAR

  local button = self:GetChild("Button")
  if button then 
    button.OnMouseOver = function(pWnd, hover)
      self.context:ShowItemDesc( GetIndexFromString( self.name ), hover )
    end

    button.OnAction = function( pWnd, action )
      if( WINDOW_ACTION_MAIN == action ) then
        self.context:PressItemButton( GetIndexFromString( self.name ), action );
      end
    end

    button.OnDoubleClick = function( pWnd, action )
      if( WINDOW_ACTION_MAIN == action ) then
        self.context:SendEventConsumablesAutoTarget( GetIndexFromString( self.name ) )
      end
    end
  end
end





-------------------------------------------------------------------------------------------------------------------------------
ActionBarTalent = ActionBarTalent or {}

-------------------------------------------------------------------------------------------------------------------------------
function ActionBarTalent:OnInit()
  self.dndSlotType = DND_ORG_TALENTS_BAR

  local button = self:GetChild( "Button" ) 
  if button then
    button.OnMouseOver = function( wnd, hover )
      self.context:ShowTalentDesc( GetIndexFromString( self.name ), hover )
    end
    button.OnAction = function( wnd, action )
      self.context:PressTalentButton( GetIndexFromString(self.name), action )
    end
    button.OnDoubleClick = function( wnd, action )
      self.context:SendEventTalentsAutoTarget( GetIndexFromString( self.name ) )
    end
    button:SetActivationBind( "cmd_action_bar_slot" .. tostring( GetIndexFromString( self.name ) + 1 ) )
  end
end









-------------------------------------------------------------------------------------------------------------------------------
BTN_Esc = BTN_Esc or {}
function BTN_Esc:OnAction()	
  self.context:OnOpenGameMenu()
end
