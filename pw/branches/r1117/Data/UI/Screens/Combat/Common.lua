---------------------------------------------
FinishGameExitButton = FinishGameExitButton or {}

function FinishGameExitButton:OnAction( action )
  self.context:QuitApplication()
end
