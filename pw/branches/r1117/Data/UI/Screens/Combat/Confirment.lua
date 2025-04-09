ConfirmentYesButton = ConfirmentYesButton or {}

function ConfirmentYesButton:OnAction()
  self.context:ConfirmentYesPressed()
end



ConfirmentNoButton = ConfirmentNoButton or {}

function ConfirmentNoButton:OnAction()
  self.context:ConfirmentNoPressed()
end



ConfirmentCancelButton = ConfirmentCancelButton or {}

function ConfirmentCancelButton:OnAction()
  self.context:ConfirmentCancelPressed()
end
