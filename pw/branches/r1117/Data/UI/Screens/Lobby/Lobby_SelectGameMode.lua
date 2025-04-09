-------------------------------------------------------------------------------------------------------------------------------
LobbySelectGameModeMain = LobbySelectGameModeMain or
{
  PLAYERS_COUNT = { MIN = 2, MAX = 10 },
  PlayerNumber = 10,
  CurrentMapId = ""
}

-------------------------------------------------------------------------------------------------------------------------------
function LobbySelectGameModeMain:OnInit()
  self.PlayersNumberScroll = self:GetBaseParent():FindChild( "PlayerCount" )
  self.PlayersNumberOutput = self:GetBaseParent():FindChild( "PlayerNum" )

  if self.PlayersNumberScroll then
    self.PlayersNumberScroll:SetNumPositions( LobbySelectGameModeMain.PLAYERS_COUNT.MAX - LobbySelectGameModeMain.PLAYERS_COUNT.MIN + 1 )
    self.PlayersNumberScroll:SetScrollPosition( LobbySelectGameModeMain.PlayerNumber - LobbySelectGameModeMain.PLAYERS_COUNT.MIN )
  end
  
  self:DisplayPlayersNumber()

  self:SetMsgHandler( "PlayerNumberScroll", "OnPlayerNumberScroll" )
end

------------------------------------------------------------------------------------------------------------------------------
function LobbySelectGameModeMain:OnPlayerNumberScroll()
  if self.PlayersNumberScroll then
    LobbySelectGameModeMain.PlayerNumber = LobbySelectGameModeMain.PLAYERS_COUNT.MIN + self.PlayersNumberScroll:GetScrollPosition()
    self:DisplayPlayersNumber()
  end
end

------------------------------------------------------------------------------------------------------------------------------
function LobbySelectGameModeMain:DisplayPlayersNumber()
  if self.PlayersNumberOutput then
    self.PlayersNumberOutput:SetCaptionTextA( tostring( LobbySelectGameModeMain.PlayerNumber ) )
  end
end









-------------------------------------------------------------------------------------------------------------------------------
LobbyGameMode_StartSingleBtn = {}

function LobbyGameMode_StartSingleBtn:OnAction()
  self.context:CreateCustomGame( 1, LobbySelectGameModeMain.CurrentMapId )
end



-------------------------------------------------------------------------------------------------------------------------------
LobbyGameMode_CreateBtn = {}

function LobbyGameMode_CreateBtn:OnAction()
  self.context:CreateCustomGame( LobbySelectGameModeMain.PlayerNumber, LobbySelectGameModeMain.CurrentMapId )
end





-------------------------------------------------------------------------------------------------------------------------------
LobbyGameMode_Games = LobbyGameMode_Games or {}

-------------------------------------------------------------------------------------------------------------------------------
function LobbyGameMode_Games:CppSessionInfo( id, params )
  local list = self:GetChild( "List" )
  if not list then return end

  local item = list:AddItem( "Item" .. id, "item" )
  if not item then return end
  
  item.sessionId = id
  item.sessionStarted = started

  local nameWnd = item:GetChild( "Name" )
  if nameWnd then
    nameWnd:SetCaptionTextA( params.name )
  end
  
  local idWnd = item:GetChild( "Id" )
  if idWnd then
    idWnd:SetCaptionTextA( string.format( "# %i", id ) )
  end
  
  local plrsWnd = item:GetChild( "Players" )
  if plrsWnd then
    local plrsText = string.format( "%i / %i", params.currentPlayers, params.maxPlayers )
    plrsWnd:SetCaptionTextA( plrsText )
  end

  local mapWnd = item:GetChild( "Map" )
  if mapWnd then
    mapWnd:SetCaptionTextA( tostring( params.mapTitle ) )
  end

  local startedWnd = item:GetChild( "Started" )
  if startedWnd then
    startedWnd:Show( params.started )
  end
end



-------------------------------------------------------------------------------------------------------------------------------
GameModeSessionSlot = GameModeSessionSlot or {}

-------------------------------------------------------------------------------------------------------------------------------
function GameModeSessionSlot:OnMouseDown()
  clog( "Going to session " .. tostring( self.sessionId ) );
--  if not self.sessionStarted then
    self.context:JoinToGame( self.sessionId )
--  end
end

-------------------------------------------------------------------------------------------------------------------------------
function GameModeSessionSlot:OnMouseOver( over )
  local h = self:GetChild( "Hilite" );
  if h then
    h:Show ( over )
  end
end



-------------------------------------------------------------------------------------------------------------------------------
LobbyGameModeRefreshButton = LobbyGameModeRefreshButton or {}

-------------------------------------------------------------------------------------------------------------------------------
function LobbyGameModeRefreshButton:OnAction()
  local list = self:GetBaseParent():FindChild( "List" )
  if list then
    list:ClearItems()
  end
  
  self.context:RefreshList()
end






-------------------------------------------------------------------------------------------------------------------------------
GameModeJoinModePanel = GameModeJoinModePanel or {}

-------------------------------------------------------------------------------------------------------------------------------
function GameModeJoinModePanel:OnInit()
  local defaultButt = self:GetChild( "JoinModeNormal" )
  if defaultButt then
    defaultButt:SetSelected( true, 0 )
  end
end



-------------------------------------------------------------------------------------------------------------------------------
GameModeJoinModeButton = GameModeJoinModeButton or {}

function GameModeJoinModeButton:OnAction()
  self.context:SetJoinMode( self.name )
end








-------------------------------------------------------------------------------------------------------------------------------
LobbyGameMode_Maps = LobbyGameMode_Maps or {}

-------------------------------------------------------------------------------------------------------------------------------
function LobbyGameMode_Maps:CppAddMap( index, id, title, descr )
  local list = self:GetChild( "List" )
  if not list then return end

  local item = list:AddItem( "Item" .. index, "item" )
  if not item then return end

  item.mapId = id
    
  local idWnd = item:GetChild( "Id" )
  if idWnd then
    idWnd:SetCaptionTextA( id )
  end

  local ttlWnd = item:GetChild( "Title" )
  if ttlWnd then
    ttlWnd:SetCaptionTextA( title )
  end
  
  local ttlaWnd = item:GetChild( "TitleActive" )
  if ttlaWnd then
    ttlaWnd:SetCaptionTextA( title )
  end

  local descrWnd = item:GetChild( "Descr" )
  if descrWnd then
    descrWnd:SetCaptionTextA( descr )
  end
  
  local lastMap = self:GetConsoleVariable( "last_map" )
  if id == lastMap then
    LobbySelectGameModeMain.CurrentMapId = id
    item.selected = true
    item:UpdateVisual()
    GameModeMapSlot.prevSelected = item
  end
end



-------------------------------------------------------------------------------------------------------------------------------
GameModeMapSlot = GameModeMapSlot or {}

-------------------------------------------------------------------------------------------------------------------------------
function GameModeMapSlot:UpdateVisual()
  local ttlWnd = self:GetChild( "Title" )
  local ttlaWnd = self:GetChild( "TitleActive" )
  if ttlWnd and ttlaWnd then
    ttlWnd:Show( not self.selected )
    ttlaWnd:Show( self.selected )
  end
  
  local hlWnd = self:GetChild( "Hilite" )
  local aWnd = self:GetChild( "ActiveBorder" )

  if hlWnd and aWnd then
    if self.hilited then
      hlWnd:Show( true )
      aWnd:Show( false )
    elseif self.selected then
      hlWnd:Show( false )
      aWnd:Show( true )
    else
      hlWnd:Show( false )
      aWnd:Show( false )
    end
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function GameModeMapSlot:OnMouseDown()
  local prev = GameModeMapSlot.prevSelected --FIXME: global variable; self.parent.prevSelected does not work :-(
  GameModeMapSlot.prevSelected = self

  if ( not prev ) or ( prev.name ~= self.name ) then
    if prev then
      prev.selected = false
      prev:UpdateVisual()
    end

    self.selected = true
    self:UpdateVisual()

    LobbySelectGameModeMain.CurrentMapId = self.mapId
    self:PostCommand( "last_map " .. tostring( self.mapId ) );
  end
end

-------------------------------------------------------------------------------------------------------------------------------
function GameModeMapSlot:OnMouseOver( over )
  self.hilited = over
  self:UpdateVisual();
end







-------------------------------------------------------------------------------------------------------------------------------
DeveloperSexControl = DeveloperSexControl or {}

function DeveloperSexControl:OnMouseDown( mbutton, x, y )
  if mbutton ~= WINDOW_ACTION_MAIN then
    return nil
  end
  
  local male = self:FindChild( "Male" )
  local female = self:GetChild( "Female" )
  clog( "!@" );
  if ( male == nil ) or ( female == nil ) then
    return nil
  end
  
  if ( male:IsVisible() ) and ( not female:IsVisible() ) then
    male:Show( false )
    female:Show( true )
    self.context:SetDeveloperSex( 2 )
  elseif ( not male:IsVisible() ) and ( female:IsVisible() ) then
    male:Show( true )
    female:Show( false )
    self.context:SetDeveloperSex( 1 )
  end
  return true
end
