-- EaselResultsScreen.lua

------------------------------------------------------------------
PaintPreview = {}
function PaintPreview.OnInit(pWnd)
  local paintStyleName = "UI/Styles/Minigame02/minigame02_paint" .. pWnd:GetContext().paintId .. ".MTRL"
  pWnd:SetBackgroundMaterialByName( paintStyleName )
end


------------------------------------------------------------------
EaselResultsTransferScrollBtn = {}
function EaselResultsTransferScrollBtn:OnAction()
  self.context:TransferScroll()
end



EaselResultsHeroBtn = {}
function EaselResultsHeroBtn:OnAction()
  self.context:SelectHero( GetIndexFromString( self.name ) )
end



EaselResultsRetryBtn = {}
function EaselResultsRetryBtn:OnAction()
  self.context:TryAgain()
end



EaselResultsDiscardBtn = {}
function EaselResultsDiscardBtn:OnAction()
  self.context:DiscardScroll()
end
