----minigame02_lobby.lua

------------------------------------------------------------------
function MG02Lobby_PaintElement( wnd, element, id )
  local needLevel = wnd.context:GetLevelForPaintID( id )
  local radioButton = element:GetChild("radio_button")
  radioButton:Enable( wnd.context.maxLevel >= needLevel );
end

-- searches for preview window from passed screen element and returns it
------------------------------------------------------------------
function MG02Lobby_GetPreviewWindow( pElement )

  local lobbyBase = pElement.base
  local lobbyDialog = lobbyBase:GetChild("lobby dialog")
  local scrollView = lobbyDialog:GetChild("ScrollView")
  
  return scrollView:GetChild("Scroll")
end

-- sets paint preview by paint id
------------------------------------------------------------------
function MG02Lobby_SetPreview(pPreviewWnd, usePaintId)

  -- create paint style name 
  local paintStyleName = "UI/Styles/Minigame02/minigame02_paint" .. usePaintId .. ".MTRL"
  
  -- set background
  pPreviewWnd:SetBackgroundMaterialByName(paintStyleName)
  
end

-- switches paint preview on selection
------------------------------------------------------------------
MG02Lobby_PaintRadioBtn =
{
  OnAction = function( wnd )
    local selectedPaintId = string.sub( wnd:GetParent().name, -1)
    wnd.context.paintId = tonumber(selectedPaintId)
    MG02Lobby_SetPreview( MG02Lobby_GetPreviewWindow(wnd), wnd.context.paintId ) 
  end
}

-- init lobby 
------------------------------------------------------------------
function UpdatePaintSelection( wnd )

  local defaultPaintName = "paint" .. wnd.context.paintId
      
  -- select default radio button
  local defaultChild = wnd:GetChild(defaultPaintName)
  local defaultRadioButton = defaultChild:GetChild("radio_button")
  defaultRadioButton:SetSelected(true, defaultRadioButton:RadioGroup() );
   
  -- set default preview 
  MG02Lobby_SetPreview( MG02Lobby_GetPreviewWindow(wnd), wnd.context.paintId ) 
   
  -- init all childs
  for i = 1, 5 do
    local childName = "paint"..i
    local child = wnd:GetChild(childName)
    MG02Lobby_PaintElement(wnd, child, i);
  end

end

MG02Lobby_PaintSelection =
{
  OnInit = function( wnd )
    UpdatePaintSelection( wnd )
  end
}

------- Level selection window subclass -------
function UpdateLevelSelection( wnd )
  if wnd.context.maxLevel == 1 then
    wnd:GetChild("right button"):Enable(false)
    wnd:GetChild("left button"):Enable(false)
  else
    wnd:GetChild("right button"):Enable(true)
    wnd:GetChild("left button"):Enable(true)
  end

  MG02Lobby_UpdateLevelSelector(wnd)
end

level_selection =
{
  OnInit = function( wnd )
    UpdateLevelSelection(wnd)    
  end
}

----- Level selection buttons -----
------------------------------------------------------------------
RightButton =
{
  OnAction = function( wnd )
    wnd.context.currentLevel = wnd.context.currentLevel + 1
    wnd.context:OnLevelChanged()
    MG02Lobby_UpdateLevelSelector( wnd )
  end
}

------------------------------------------------------------------
LeftButton =
{
  OnAction = function( wnd )
    wnd.context.currentLevel = wnd.context.currentLevel - 1
    wnd.context:OnLevelChanged()
    MG02Lobby_UpdateLevelSelector( wnd )
  end
}

-- changes level text and disables level selection buttons
------------------------------------------------------------------
function MG02Lobby_UpdateLevelSelector( wnd )

  local base = wnd.base
  local lobbyDialog = base:GetChild("lobby dialog")
  local previewBorder = lobbyDialog:GetChild("LevelSelector")
  local levelSelection = previewBorder:GetChild("level selection")
  
  -- set new level text
  local selectionText = levelSelection:GetChild("level")
  selectionText:SetCaptionTextA(wnd.context.currentLevel)
  
  -- disable selection buttons if needed
  local rightButton = levelSelection:GetChild("right button")
  local leftButton = levelSelection:GetChild("left button")
  rightButton:Enable( wnd.context.currentLevel ~= wnd.context.maxLevel )  
  leftButton:Enable( wnd.context.currentLevel ~= 1 )

  --visualize level award
  local goldMedalWnd = lobbyDialog:GetChild( "MedalGold" )
  local silverMedalWnd = lobbyDialog:GetChild( "MedalSilver" )
  local goldMedal = ( wnd.context.currentLevelAward == "Gold" )
  local silverMedal = ( wnd.context.currentLevelAward == "Silver" )
  goldMedalWnd:Show( goldMedal )
  silverMedalWnd:Show( silverMedal )
end

------------------------------------------------------------------
MG02Lobby_PaintRadioBtn =
{
  OnAction = function( wnd )
    local selectedPaintId = string.sub( wnd:GetParent().name, -1)
    wnd.context.paintId = tonumber(selectedPaintId)

    local paintUI = wnd:GetParent()
    local paintregion = paintUI:GetParent()

    UpdatePaintSelection(paintregion)

    -- test 5x5
    wnd.context:OnLevelChanged()
    MG02Lobby_UpdateLevelSelector(wnd)

  end
}

----- Ok/Cancel buttons -----

------------------------------------------------------------------
MG02Lobby_StartButton = 
{
  OnAction = function( wnd )
    wnd.context:Start()
  end
}

------------------------------------------------------------------
MG02Lobby_CancelButton = 
{
  OnAction = function( wnd )
    wnd.context:Exit()
  end
}

------------------------------------------------------------------
RegenerateButton = 
{

  OnAction = function( wnd )
    wnd.context:OnRegenerateClicked()
  end	

}

------------------------------------------------------------------
BoostsGenerator = {}


  -- апдейт статистики (может вызываться на каждом степе)
function BoostsGenerator.UpdateStats( wnd )
  local isCanBuyRegen = wnd.context:IsCanBuyBoostsRegen()
  local regenBtn = wnd.base:FindChild( "regenerate_button" )
  regenBtn:Enable( isCanBuyRegen )
end

------------------------------------------------------------------
LobbyBase = {}

function LobbyBase.UpdateAll( wnd )

  local lobby_dialog = wnd:GetChild("lobby dialog")
  local paint_region = lobby_dialog:GetChild("Paint selection region")

  UpdatePaintSelection(paint_region)

  local level_selector = lobby_dialog:GetChild("LevelSelector")
  local level_selection = level_selector:GetChild("level selection")

  UpdateLevelSelection(level_selection)

end


