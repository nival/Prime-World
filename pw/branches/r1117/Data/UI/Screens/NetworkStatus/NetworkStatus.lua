
NetworkStatusQuitButton = NetworkStatusQuitButton or {}

function NetworkStatusQuitButton:OnAction()
  self.context:QuitApplication()
end
