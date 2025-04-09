MinigamesLobbyMain =
{
  OnScreenFocus = function( wnd )
    wnd:GetChild( "Clinic" ):Enable( true );
    wnd:GetChild( "Easel" ):Enable( true );
  end
}

MinigamesLobbyGoClinic =
{
  OnAction = function( wnd )
    wnd:Enable( false );
    wnd.context:StartMinigame( 'Clinic' )
  end
}

MinigamesLobbyGoEasel =
{
  OnAction = function( wnd )
    wnd:Enable( false );
    wnd.context:StartMinigame( 'Easel' )
  end
}

MinigamesLobbyExit =
{
  OnAction = function( wnd )
    wnd.context:Exit()
  end
}
