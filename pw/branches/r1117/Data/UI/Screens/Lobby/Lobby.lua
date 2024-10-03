-------------------------------------------------------------------------------------------------------------------------------
LobbyMainWnd = LobbyMainWnd or {}

-------------------------------------------------------------------------------------------------------------------------------
function LobbyMainWnd:OnInit( )
  local button = self:GetChild("Btn_StartSession")
  if button then
    button.OnAction = function()  self.context:PlayerReady() end
  end
  
  button = self:GetChild("Btn_LeaveLobby")
  if button then
    button.OnAction = function()  self.context:LeaveLobby() end
  end

  button = self:GetBaseParent():FindChild( "Btn_Team1" )
  if button then
    button.OnAction = function() self.context:ChangeTeam( 0 ) end
  end
  
  button = self:GetBaseParent():FindChild( "Btn_Team2" )
  if button then
    button.OnAction = function() self.context:ChangeTeam( 1 ) end
  end

  button = self:GetBaseParent():FindChild( "Btn_Faction1" )
  if button then
    button.OnAction = function() self.context:ChangeFaction( 0 ) end
  end

  button = self:GetBaseParent():FindChild( "Btn_Faction2" )
  if button then
    button.OnAction = function() self.context:ChangeFaction( 1 ) end
  end

  self:InitPartyButtons(self:GetBaseParent())

  self:SetButtonCap( 0 )
end

-------------------------------------------------------------------------------------------------------------------------------
function LobbyMainWnd:InitPartyButton(ui, index)
  local name = "Btn_Party" .. tostring(index)
  local button = ui:FindChild(name)

  if button then
    button.OnAction = function () self.context:SetDeveloperParty(index) end
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function LobbyMainWnd:InitPartyButtons(ui)
  local partyButtonIndexes = { 0, 1, 2, 3, 4, 5 }

  for _, partyButtonIndex in ipairs(partyButtonIndexes) do
    self:InitPartyButton(ui, partyButtonIndex)
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function LobbyMainWnd:SetButtonCap( heroId )
  local StartButton = self:GetChild( "Btn_StartSession" )
  if nil ~= StartButton then
    local femalePrefix = "priestess"
    local prefix = string.sub( heroId, 0, string.len( femalePrefix ) )
    clog( "Hero prefix: " .. tostring(prefix) )
    local isFemale = ( prefix == femalePrefix )

    local string capId = isFemale and "femaleCap" or "maleCap"
    StartButton:SetCaptionTextW( StartButton:GetRelatedText( capId ) )
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function LobbyMainWnd:OnSelectHero( heroId )
  if heroId then
    self.context:SelectHero( heroId )  
    self:SetButtonCap( heroId );
  end
end

-------------------------------------------------------------------------------------------------------------------------------
Lobby_HeroRadioBtn = Lobby_HeroRadioBtn or {}
function Lobby_HeroRadioBtn:OnAction( action )
  self:GetParent():GetParent():OnSelectHero( self.name )
end
