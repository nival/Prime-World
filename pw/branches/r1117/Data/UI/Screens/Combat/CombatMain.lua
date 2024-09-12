---------------------------------------------------------------------------------------
-- Combat screen main
---------------------------------------------------------------------------------------
Combat = Combat or {}

function Combat:OnInit()
  ActionBar:OnInit( self )
end

function Combat:OnScreenFocus( bFocused )
  clog( "Hiding adventure controls depending on screen focus = " .. tostring( bFocused ) )
  self:GetChild( "ActionBar" ):Show( bFocused )
  self:GetChild( "SelectionInfo" ):Show( bFocused )

  local HeroInfo = self:GetChild("HeroInfo");
  HeroInfo.portraitClicksEnabled = bFocused
end

CombatResources = CombatResources or {}

function CombatResources:OnInit()
  local pControl = self:GetChild("BTN_Convert")
  if nil ~= pControl then
    pControl.OnAction = function( pWnd, action ) self.context:PressButtonConvert( action ) end 
  end
end
