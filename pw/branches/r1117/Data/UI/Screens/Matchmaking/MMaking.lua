include( "UI/Screens/Combat/Confirment.lua" )

MMakingSelectFaction = MMakingSelectFaction or {}

function MMakingSelectFaction:OnAction()
  self.context:SelectFaction( GetIndexFromString( self.name ) )
end




MMakingHeroImage = MMakingHeroImage or {}

function MMakingHeroImage:OnMouseOver( over, x, y )
  self.context:MouseOverHero( self, over )
end

function MMakingHeroImage:OnMouseDown( mbutton, x, y)
  self.context:MouseClickInHero( self, true )
end

function MMakingHeroImage:OnMouseUp( mbutton, x, y)
  self.context:MouseClickInHero( self, false )
end




MMakingGoButton = MMakingGoButton or {}

function MMakingGoButton:OnAction()
  self.context:StartMMaking()
end



MMakingGoSingleButton = MMakingGoSingleButton or {}

function MMakingGoSingleButton:OnAction()
  self.context:StartSingle()
end



MMakingRejoinButton = MMakingRejoinButton or {}

function MMakingRejoinButton:OnAction()
  self.context:RejoinSession()
end



MMakingCancelButton = MMakingCancelButton or {}

function MMakingCancelButton:OnAction( over, x, y )
  self.context:CancelMMaking()
end



MMakingExitButton = MMakingExitButton or {}

function MMakingExitButton:OnAction()
  self.context:QuitApplication()
end
