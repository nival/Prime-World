RemovePauseButton = RemovePauseButton or {}

function RemovePauseButton:OnInit()
    self.OnAction = function( pWnd, action )
      if( WINDOW_ACTION_MAIN == action ) then
        self.context:PressRemovePauseButton();
      end
    end
end
